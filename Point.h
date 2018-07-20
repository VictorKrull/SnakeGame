#pragma once
#include <ostream>

class Point
{
private:
	int coordx;
	int coordy;

public:
	Point();
	Point(int);
	Point(int, int);
	int getX();
	int getY();
	void setX(int);
	void setY(int);
	Point add(const Point);
	bool compare(const Point);
	Point substract(const Point);
	friend bool operator == (Point &p1, Point &p2);
	friend bool operator != (Point &p1, Point &p2);
	friend Point operator + (Point &p1, Point &p2);
	friend Point operator - (Point &p1, Point &p2);
	//friend std::ostream& operator << (std::ostream &os, const Point &p);	
};

