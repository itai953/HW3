#ifndef ASCIIVIEW_H
#define ASCIIVIEW_H
#include "Geometry.h"
#include <unordered_map>
#include <list>
#include "Model.h"

/* 
 * class AsciiView will print a matrix of ascii characters representing the current status of the map
 * data members:
 * scale: unsigned int, ratio of 1 square in matrix to 100km
 * size: unsigned int, matrix dimensions will be sizeXsize
 * origin: Point, the bottom most left corner of the map, axis origin
 * big 5 default implementations sufficient
 */

using u_int = unsigned int;
class AsciiView{
    u_int scale,size;
    Point origin;

    //a helper function to filter only the objects currently in the map
    vector<shared_ptr<SimObject>> getObjectsInMap();
public:
    //enum for min\max size of map
    enum{MINSIZE = 6, MAXSIZE = 30};
    //c'tor
    AsciiView(u_int _scale = 2, u_int _size = 25, Point _origin = Point(0,0)):scale(_scale),size(_size),origin(_origin){ }
    
    //setters
    void setSize(u_int newSize){size = newSize;}
    void setScale(u_int newScale){scale = newScale;}
    void setOrigin(double x, double y){origin.x = x; origin.y = y;}
    
    //draw map to ostream out
    ostream& draw(ostream& out);

    //return values to default
    void returnDefault(){scale = 2; size = 25; origin.x = 0; origin.y = 0;}
};


#endif