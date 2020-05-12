#ifndef POLYGON_H
#define POLYGON_H

#include <QList>
#include <QVector>
#include "../Common/coordinates.h"
#include "../Common/rectc.h"

class Polygon : public QList<QVector<Coordinates> >
{
public:
	bool isValid() const {return !isEmpty() && first().size() >= 3;}

	RectC boundingRect() const;
};

#endif // POLYGON_H
