#include "track.h"


int Track::_elevationWindow = 3;
int Track::_speedWindow = 5;
int Track::_heartRateWindow = 3;
int Track::_cadenceWindow = 3;
int Track::_powerWindow = 3;

bool Track::_automaticPause = true;
qreal Track::_pauseSpeed = 0.5;
int Track::_pauseInterval = 10;

bool Track::_outlierEliminate = true;
bool Track::_useReportedSpeed = false;
bool Track::_useDEM = false;
bool Track::_show2ndElevation = false;
bool Track::_show2ndSpeed = false;


static qreal avg(const QVector<qreal> &v)
{
	qreal sum = 0;

	for (int i = 0; i < v.size(); i++)
		sum += v.at(i);

	return sum/v.size();
}

static qreal median(QVector<qreal> &v)
{
	qSort(v.begin(), v.end());
	return v.at(v.size() / 2);
}

static qreal MAD(QVector<qreal> &v, qreal m)
{
	for (int i = 0; i < v.size(); i++)
		v[i] = qAbs(v.at(i) - m);
	return median(v);
}

/*
   Modified Z-score (Iglewicz and Hoaglin)
   The acceleration data distribution has usualy a (much) higher kurtosis than
   the normal distribution thus a higher comparsion value than the usual 3.5 is
   required.
*/
static QSet<int> eliminate(const QVector<qreal> &v)
{
	QSet<int> rm;

	QVector<qreal> w(v);
	qreal m = median(w);
	qreal M = MAD(w, m);

	for (int i = 0; i < v.size(); i++)
		if (qAbs((0.6745 * (v.at(i) - m)) / M) > 5.0)
			rm.insert(i);

	return rm;
}

Track::Track(const TrackData &data) : _data(data), _pause(0)
{
	qreal ds, dt;

	for (int i = 0; i < _data.size(); i++) {
		const SegmentData &sd = _data.at(i);
		_segments.append(Segment());
		if (sd.isEmpty())
			continue;

		// precompute distances, times, speeds and acceleration
		QVector<qreal> acceleration;

		Segment &seg = _segments.last();

		seg.distance.append(i && !_segments.at(i-1).distance.isEmpty()
		  ? _segments.at(i-1).distance.last() : 0);
		seg.time.append(i && !_segments.at(i-1).time.isEmpty()
		  ? _segments.at(i-1).time.last() :
		  sd.first().hasTimestamp() ? 0 : NAN);
		seg.speed.append(sd.first().hasTimestamp() ? 0 : NAN);
		acceleration.append(sd.first().hasTimestamp() ? 0 : NAN);
		bool hasTime = !std::isnan(seg.time.first());

		for (int j = 1; j < sd.size(); j++) {
			ds = sd.at(j).coordinates().distanceTo(
			  sd.at(j-1).coordinates());
			seg.distance.append(seg.distance.last() + ds);

			if (hasTime && sd.at(j).timestamp().isValid()) {
				if (sd.at(j).timestamp() > sd.at(j-1).timestamp())
					dt = sd.at(j-1).timestamp().msecsTo(
					  sd.at(j).timestamp()) / 1000.0;
				else {
					qWarning("%s: %s: time skew detected", qPrintable(
					  _data.name()), qPrintable(sd.at(j).timestamp().toString(
					  Qt::ISODate)));
					dt = 0;
				}
			} else {
				dt = NAN;
				if (hasTime) {
					qWarning("%s: missing timestamp(s), time graphs disabled",
					  qPrintable(_data.name()));
					hasTime = false;
					for (int k = 0; k < seg.time.size(); k++)
						seg.time[i] = NAN;
					for (int l = 0; l < seg.speed.size(); l++)
						seg.speed[l] = NAN;
				}
			}
			seg.time.append(seg.time.last() + dt);

			if (dt < 1e-3) {
				seg.speed.append(seg.speed.last());
				acceleration.append(acceleration.last());
			} else {
				qreal v = ds / dt;
				qreal dv = v - seg.speed.last();
				seg.speed.append(v);
				acceleration.append(dv / dt);
			}
		}

		if (!hasTime)
			continue;


		// get stop-points + pause duration
		int pauseInterval;
		qreal pauseSpeed;

		if (_automaticPause) {
			pauseSpeed = (avg(seg.speed) > 2.8) ? 0.40 : 0.15;
			pauseInterval = 10;
		} else {
			pauseSpeed = _pauseSpeed;
			pauseInterval = _pauseInterval;
		}

		int ss = 0, la = 0;
		for (int j = 1; j < seg.time.size(); j++) {
			if (seg.speed.at(j) > pauseSpeed)
				ss = -1;
			else if (ss < 0)
				ss = j-1;

			if (ss >= 0 && seg.time.at(j) > seg.time.at(ss) + pauseInterval) {
				int l = qMax(ss, la);
				_pause += seg.time.at(j) - seg.time.at(l);
				for (int k = l; k <= j; k++)
					seg.stop.insert(k);
				la = j;
			}
		}

		if (!_outlierEliminate)
			continue;


		// eliminate outliers
		seg.outliers = eliminate(acceleration);

		// stop-points can not be outliers
		QSet<int>::const_iterator it;
		for (it = seg.stop.constBegin(); it != seg.stop.constEnd(); ++it)
			seg.outliers.remove(*it);

		// recompute distances (and dependand data) without outliers
		int last = 0;
		for (int j = 0; j < sd.size(); j++) {
			if (seg.outliers.contains(j))
				last++;
			else
				break;
		}
		for (int j = last + 1; j < sd.size(); j++) {
			if (seg.outliers.contains(j))
				continue;
			if (discardStopPoint(seg, j)) {
				seg.distance[j] = seg.distance.at(last);
				seg.speed[j] = 0;
			} else {
				ds = sd.at(j).coordinates().distanceTo(
				  sd.at(last).coordinates());
				seg.distance[j] = seg.distance.at(last) + ds;

				dt = seg.time.at(j) - seg.time.at(last);
				seg.speed[j] = (dt < 1e-3) ? seg.speed.at(last) : ds / dt;
			}
			last = j;
		}
	}
}

void Track::elevation(qreal & ele) const
{
	ele = 0;
	for (int i = 0; i < _data.size(); i++) {
		const SegmentData &sd = _data.at(i);
		if (sd.size() < 2)
			continue;
		qreal e;
		const Segment &seg = _segments.at(i);
		for (int j = 1; j < sd.size(); j++) {
			if (!sd.at(j).hasElevation() || seg.outliers.contains(j))
				continue;			
				e = sd.at(j).elevation();
				qreal cur = sd.at(j).elevation();
				qreal prev = sd.at(j-1).elevation();
				if (cur > prev)
					ele += cur - prev;
		}
	}
}

void Track::speed(qreal & max, qreal & moyenne) const
{
	max = 0;
	moyenne = 0;
	int count = 0;
	for (int i = 0; i < _data.size(); i++) {
		const SegmentData &sd = _data.at(i);
		if (sd.size() < 2)
			continue;
		const Segment &seg = _segments.at(i);		
		qreal v;

		for (int j = 0; j < sd.size(); j++) {
			if (seg.stop.contains(j) && !std::isnan(seg.speed.at(j))) {
				v = 0;
			}
			else if (!std::isnan(seg.speed.at(j)) && !seg.outliers.contains(j)) {
				v = seg.speed.at(j);
				count++;
				moyenne += v;
				if (v > max)
					max = v;
			}
			else
				continue;

		}
	}
	moyenne = moyenne / count;

}

void Track::heartRate(qreal &max, qreal &moyenne) const
{
	max = 0;
	moyenne = 0;
	int count = 0;
	for (int i = 0; i < _data.size(); i++) {
		const SegmentData &sd = _data.at(i);
		if (sd.size() < 2)
			continue;
		const Segment &seg = _segments.at(i);
		qreal c;
		for (int j = 0; j < sd.size(); j++) {
			if (sd.at(j).hasHeartRate() && !seg.outliers.contains(j)) {
				count++;
				c = sd.at(j).heartRate();
				moyenne += c;
				if (c > max)
					max = c;
			}
		}
	}
	moyenne = moyenne / count;

}

void Track::cadence(qreal &max, qreal &moyenne) const
{
	moyenne = 0;
	 max = 0;
	int count = 0;
	for (int i = 0; i < _data.size(); i++) {
		const SegmentData &sd = _data.at(i);
		if (sd.size() < 2)
			continue;
		qreal c;
		for (int j = 0; j < sd.size(); j++) {	
			if (sd.at(j).hasCadence()) {
				count++;
				c = sd.at(j).cadence();
				moyenne += c;
				if (c > max)
					max = c;
			}
		}
	}
	moyenne = moyenne / count;
}

qreal Track::distance() const
{
	for (int i = _segments.size() - 1; i >= 0; i--) {
		const Segment &seg = _segments.at(i);

		for (int j = seg.distance.size() - 1; j >= 0; j--)
			if (!seg.outliers.contains(j))
				return seg.distance.at(j);
	}

	return 0;
}

qreal Track::time() const
{
	for (int i = _segments.size() - 1; i >= 0; i--) {
		const Segment &seg = _segments.at(i);

		for (int j = seg.time.size() - 1; j >= 0; j--)
			if (!seg.outliers.contains(j))
				return seg.time.at(j);
	}

	return 0;
}

qreal Track::movingTime() const
{
	return (time() - _pause);
}

QDateTime Track::date() const
{
	return (_data.size() && _data.first().size())
	  ? _data.first().first().timestamp() : QDateTime();
}

Path Track::path() const
{
	Path ret;

	for (int i = 0; i < _data.size(); i++) {
		const SegmentData &sd = _data.at(i);
		if (sd.size() < 2)
			continue;
		const Segment &seg = _segments.at(i);
		ret.append(PathSegment());
		PathSegment &ps = ret.last();

		for (int j = 0; j < sd.size(); j++)
			if (!seg.outliers.contains(j) && !discardStopPoint(seg, j))
				ps.append(PathPoint(sd.at(j).coordinates(),
				  seg.distance.at(j)));
	}

	return ret;
}

bool Track::discardStopPoint(const Segment &seg, int i) const
{
	return (seg.stop.contains(i) && seg.stop.contains(i-1)
	  && seg.stop.contains(i+1) && i > 0 && i < seg.distance.size() - 1);
}

bool Track::isValid() const
{
	for (int i = 0; i < _data.size(); i++)
		if (_data.at(i).size() >= 2)
			return true;
	return false;
}
