#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <iostream>
#include <iomanip>
using namespace std;
// angle units conversion functions
double to_radians(double theta_d);
double to_degrees(double theta_r);
// class declarations
typedef struct Point {
	double x;
	double y;
	Point(double x, double y);
	Point();
	void print() const;
	bool operator==(const Point& rhs);
	friend ostream& operator<<(ostream& os, const Point& p);
} Point;
struct Polar_vector;
typedef struct Cartesian_vector {
	Cartesian_vector(const struct Polar_vector & pv);
	Cartesian_vector();
	void operator=(const struct Polar_vector & pv);
	double delta_x;
	double delta_y;
} Cartesian_vector;
typedef struct Polar_vector {
	Polar_vector(const Cartesian_vector & cv);
	Polar_vector();
	void operator=(const Cartesian_vector & cv);
	double r;
	double theta;
} Polar_vector;

// double calculateCourse(const Point& p1,const Point& p2);
double calculateSpeed(const Point& p1, const Point& p2, double time);
double calculateAngle(const Point& p1, const Point& p2);
double normalizeAngle(double theta);
double getDistance(const Point& p1, const Point& p2);


#endif