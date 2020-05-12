#ifndef TRACK_H
#define TRACK_H

#include <QVector>
#include <QSet>
#include <QDateTime>
#include <QDir>
#include "trackdata.h"
#include "path.h"


class Track
{
public:
	Track(const TrackData &data);

	Path path() const;
	void elevation(qreal &ele) const;
	void speed(qreal &max, qreal &moyenne) const;
	void heartRate(qreal &max, qreal &moyenne) const;
	void cadence(qreal &max, qreal &moyenne) const;

	qreal distance() const;
	qreal time() const;
	qreal movingTime() const;
	QDateTime date() const;

	const QString &name() const {return _data.name();}
	const QString &description() const {return _data.description();}
	const QString &comment() const {return _data.comment();}
	const QVector<Link> &links() const {return _data.links();}

	bool isValid() const;

	static void setElevationFilter(int window) {_elevationWindow = window;}
	static void setSpeedFilter(int window) {_speedWindow = window;}
	static void setHeartRateFilter(int window) {_heartRateWindow = window;}
	static void setCadenceFilter(int window) {_cadenceWindow = window;}
	static void setPowerFilter(int window) {_powerWindow = window;}
	static void setAutomaticPause(bool set) {_automaticPause = set;}
	static void setPauseSpeed(qreal speed) {_pauseSpeed = speed;}
	static void setPauseInterval(int interval) {_pauseInterval = interval;}
	static void setOutlierElimination(bool eliminate)
	  {_outlierEliminate = eliminate;}
	static void useReportedSpeed(bool use) {_useReportedSpeed = use;}
	static void useDEM(bool use) {_useDEM = use;}
	static void showSecondaryElevation(bool show)
	  {_show2ndElevation = show;}
	static void showSecondarySpeed(bool show)
	  {_show2ndSpeed = show;}

private:
	struct Segment {
		QVector<qreal> distance;
		QVector<qreal> time;
		QVector<qreal> speed;
		QSet<int> outliers;
		QSet<int> stop;
	};

	bool discardStopPoint(const Segment &seg, int i) const;
	TrackData _data;
	QList<Segment> _segments;
	qreal _pause;

	static bool _outlierEliminate;
	static int _elevationWindow;
	static int _speedWindow;
	static int _heartRateWindow;
	static int _cadenceWindow;
	static int _powerWindow;
	static bool _automaticPause;
	static qreal _pauseSpeed;
	static int _pauseInterval;
	static bool _useReportedSpeed;
	static bool _useDEM;
	static bool _show2ndElevation;
	static bool _show2ndSpeed;
};

#endif // TRACK_H
