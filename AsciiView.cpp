#include "AsciiView.h"
#include <cmath>
#include <algorithm>


ostream& AsciiView::draw(ostream& out){
    double y1,y2,x1,x2; //these mark the limits for each iteration in the drawing loop
    y1 = origin.y + scale*size; //upper boundary
    y2 = y1 - scale;
    x1 = origin.x; //leftmost boundary
    x2 = x1 + scale;
    auto&& objects = getObjectsInMap(); //get vector of objects that appear in the map

    //sort the vector by descending y value, secondary sort by ascending x value of locations
    sort(objects.begin(), objects.end(),[](shared_ptr<SimObject>& a, shared_ptr<SimObject>& b){
        if(a->getLocation().y == b->getLocation().y){
            return a->getLocation().x < b->getLocation().x;
        }
        return a->getLocation().y > b->getLocation().y;
    });

    //iterator to first object
    auto it = objects.begin(), end = objects.end();
    int lineCount = 0; //for printing
    int divisor = (size%2 == 0) ? 2 : 3; //find a number that divides the size
    if(divisor == 2 && (size%4) == 0) divisor = 4;
    if(divisor == 3 && (size%5) == 0) divisor = 5;
    out << "Display size: " << size << ", scale: " << scale << ", origin: "<<origin << endl;
    for(int i=0; i<size; i++)
    {
        if(lineCount%divisor == 0)
        {
            out << setprecision(0) << setw(4) << y1;
        }
        else if(i == size-1)
        {
            out << setprecision(0) << setw(4) << y2;
        }
        else
        {
            out << "    ";
        }
        out << " ";
        lineCount++;
        while(it != objects.end() && (*it)->getLocation().y > y1) //advance iterator while possible and the y value is greater than current upper bound
            it++;
        x1 = origin.x; //reset x1 and x2
        x2 = x1 + scale;
        for(int j=0; j<size; j++)
        {
            //advance iterator while x coordinate is less than x1 and y coordinate greater than y2
            while(it != end && (*it)->getLocation().x < x1 && (*it)->getLocation().y > y2)
                it++;
            if
            (
                it == end ||
                (*it)->getLocation().x >= x2 ||
                (*it)->getLocation().y <= y2
            )
            {
                out << ". ";
            }
            else
            {
                out << (*it)->getName().substr(0,2);
                it++;
            }
            x1 = x2;
            x2 = x2 + scale;
        }
        out << endl;
        y1 = y2;
        y2 = y1 - scale;
    }
    /*print bottom line x coordinates */
    lineCount = 1;
    out << setw(6) << origin.x;
    for(int i=1; i<size; i++)
    {
        if(lineCount % divisor == 0)
        {
            out << origin.x + i*scale;
        }
        else
        {
            out << "  ";
        }
        lineCount++;
    }
    out << origin.x + size*scale;
    out << endl;
    return out;
}



vector<shared_ptr<SimObject>> AsciiView::getObjectsInMap(){
    auto objects = Model::getInstance().getSimObjList();
    vector<shared_ptr<SimObject>> res;
    for(auto& obj : objects)
    {
        if(
               (obj.second->getLocation().x >= origin.x)
            && (obj.second->getLocation().x <= origin.x + scale*size)
            && (obj.second->getLocation().y >= origin.y)
            && (obj.second->getLocation().y <= origin.y + scale*size)
          )
        {
            res.push_back(obj.second);
        }
    }
    return res;
}