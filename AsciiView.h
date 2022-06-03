#ifndef ASCIIVIEW_H
#define ASCIIVIEW_H
#include "Model.h"
#include "Geometry.h"

/* 
 * class AsciiView will print a matrix of ascii characters representing the current status of the map
 * data members:
 * scale: unsigned int, ratio of 1 square in matrix to 100km
 * size: unsigned int, matrix dimensions will be sizeXsize
 * origin: Point, the bottom most left corner of the map, axis origin
 */

using u_int = unsigned int;
class AsciiView{
    u_int scale,size;
    Point origin;
    enum{MINSIZE = 6, MAXSIZE = 30};
public:
    //c'tor
    AsciiView(u_int _scale = 2, u_int _size = 25, Point _origin = Point(0,0)):scale(_scale),size(_size),origin(_origin){ }
    
    //setters
    void setSize(u_int newSize){size = newSize;}
    void setScale(u_int newScale){scale = newScale;}
    void setOrigin(double x, double y){origin.x = x; origin.y = y;}
    
    //draw map to ostream out
    ostream& draw(ostream& out);
    
    //clear map
    void clear();
};


#endif