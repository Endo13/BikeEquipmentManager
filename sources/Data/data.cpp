#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QLineF>
#include "gpxparser.h"
#include "tcxparser.h"
#include "fitparser.h"
#include "data.h"


static GPXParser gpx;
static TCXParser tcx;
static FITParser fit;

static QMap<QString, Parser*> parsers()
{
	QMap<QString, Parser*> map;

	map.insert("gpx", &gpx);
	map.insert("tcx", &tcx);
	map.insert("fit", &fit);
	return map;
}

QMap<QString, Parser*> Data::_parsers = parsers();

void Data::processData(QList<TrackData> &trackData, QList<RouteData> &routeData)
{
	for (int i = 0; i < trackData.count(); i++)
		_tracks.append(Track(trackData.at(i)));
	for (int i = 0; i < routeData.count(); i++)
		_routes.append(Route(routeData.at(i)));
}

Data::Data(const QString &fileName)
{
	QFile file(fileName);
	QFileInfo fi(fileName);
	QList<TrackData> trackData;
	QList<RouteData> routeData;

	_valid = false;
	_errorLine = 0;

	if (!file.open(QFile::ReadOnly)) {
		_errorString = qPrintable(file.errorString());
		return;
	}

	QMap<QString, Parser*>::iterator it;
	if ((it = _parsers.find(fi.suffix().toLower())) != _parsers.end()) {
		if (it.value()->parse(&file, trackData, routeData, _polygons,
		  _waypoints)) {
			processData(trackData, routeData);
			_valid = true;
			return;
		} else {
			_errorLine = it.value()->errorLine();
			_errorString = it.value()->errorString();
		}
	} else {
		for (it = _parsers.begin(); it != _parsers.end(); it++) {
			if (it.value()->parse(&file, trackData, routeData, _polygons,
			  _waypoints)) {
				processData(trackData, routeData);
				_valid = true;
				return;
			}
			file.reset();
		}

		qWarning("Error loading data file: %s:", qPrintable(fileName));
		for (it = _parsers.begin(); it != _parsers.end(); it++)
			qWarning("%s: line %d: %s", qPrintable(it.key()),
			  it.value()->errorLine(), qPrintable(it.value()->errorString()));

		_errorLine = 0;
		_errorString = "Unknown format";
	}
}

QString Data::formats()
{
	return
		qApp->translate("Data", "Supported files") + " (" + filter().join(" ") + ");;"
		+ qApp->translate("Data", "FIT files") + " (*.fit);;"
		+ qApp->translate("Data", "GPX files") + " (*.gpx);;"
		+ qApp->translate("Data", "TCX files") + " (*.tcx);;";
}

QStringList Data::filter()
{
	QStringList filter;

	for (QMap<QString, Parser*>::iterator it = _parsers.begin();
	  it != _parsers.end(); it++)
		filter << "*." + it.key();

	return filter;
}
