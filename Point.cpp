#include "Point.h"

Point::Point()
{
	coordx = 0;
	coordy = 0;
}

Point::Point(int x)
{
	coordx = x;
	coordy = 0;
}

Point::Point(int x, int y)
{
	coordx = x;
	coordy = y;
}

int Point::getX()
{
	return coordx;
}

int Point::getY()
{
	return coordy;
}

void Point::setX(int x)
{
	coordx = x;
}

void Point::setY(int y)
{
	coordy = y;
}

Point Point::add(Point p)
{
	return Point(coordx + p.coordx, coordy + p.coordy);
}

Point Point::substract(Point p)
{
	return Point(coordx - p.coordx, coordy - p.coordy);
}

bool Point::compare(Point p)
{
	return (coordx == p.coordx && coordy == p.coordy);
}

bool operator==(Point & p1, Point & p2)
{
	return p1.compare(p2);
}

bool operator!=(Point & p1, Point & p2)
{
	return !(p1 == p2);
}

Point operator+(Point & p1, Point & p2)
{
	return p1.add(p2);
}

Point operator-(Point & p1, Point & p2)
{
	return p1.substract(p2);
}
/*
std::ostream & operator<<(std::ostream & os, const Point & p)
{
	os << "(" << p.coordx << ", " << p.coordy << ")";

	return os;
}
*/