#include "AsciiView.h"
#include <cmath>
#include <algorithm>
ostream& AsciiView::draw(ostream& out){
    double y1,y2,x1,x2;
    y1 = origin.y + scale*size;
    y2 = y1 - scale;
    x1 = origin.x;
    x2 = x1 + scale;
    auto&& objects = getObjectsInMap();
    sort(objects.begin(), objects.end(),[](shared_ptr<SimObject>& a, shared_ptr<SimObject>& b){
        if(a->getLocation().y == b->getLocation().y){
            return a->getLocation().x < b->getLocation().x;
        }
        return a->getLocation().y > b->getLocation().y;
    });
    auto it = objects.begin(), end = objects.end();
    int lineCount = 0;
    int divisor = (size%2 == 0) ? 2 : 3;
    if(divisor == 2 && (size%4) == 0) divisor = 4;
    if(divisor == 3 && (size%5) == 0) divisor = 5;
    for(int i=0; i<size; i++)
    {
        if(lineCount%divisor == 0)
        {
            out << setprecision(0) << setw(4) << y1;
        }
        else
        {
            out << "    ";
        }
        out << " ";
        lineCount++;
        while(it != objects.end() && (*it)->getLocation().y > y1)
            it++;
        x1 = origin.x;
        x2 = x1 + scale;
        for(int j=0; j<size; j++)
        {
            while(it != end && (*it)->getLocation().x < x1 && (*it)->getLocation().y > y2)
                it++;
            if
            (
                it == end ||
                (*it)->getLocation().x >= x2 ||
                (*it)->getLocation().y <= y2
            )
            {
                out << "._";
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
    // lineCount = 0;
    // cout << setw(6) << origin.x;
    // for(int i=1; i<size; i++)
    // {
    //     if(lineCount % divisor == 0)
    // }
    return out;
}

// void AsciiView::push(Point prev, Point cur,string s){
//     map[floor(cur.y)][floor(cur.x)].push_front(s);
//     map[floor(prev.y)][floor(prev.x)].remove(s);
//     if(map[floor(prev.y)][floor(prev.x)].empty()){
//         map[floor(prev.y)].erase(floor(prev.x));
//     }
//     if(map[floor(prev.y)].empty()){
//         map.erase(floor(prev.y));
//     }
// }

vector<shared_ptr<SimObject>> AsciiView::getObjectsInMap(){
    auto objects = Model::getInstance().getSimObjList();
    vector<shared_ptr<SimObject>> res;
    // copy_if(objects.begin(),objects.end(),res.begin(),[this](const pair<string,shared_ptr<SimObject>>& a){
    //     Point p = a.second->getLocation();
    //     return (p.x >= origin.x && p.x <=origin.x + scale*size) && (p.y >= origin.y && p.y <= origin.y + scale*size);
    // });
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