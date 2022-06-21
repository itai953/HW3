#include "AsciiView.h"
#include <cmath>
#include <algorithm>
ostream& AsciiView::draw(ostream& out){
    double max_y = origin.y + scale*size;
    double min_x = origin.x;
    double top,bottom,left,right;
    auto&& objects = getObjectsInMap();
    sort(objects.begin(), objects.end(),[](shared_ptr<SimObject>& a, shared_ptr<SimObject>& b){
        if(a->getLocation().y == b->getLocation().y){
            return a->getLocation().x < b->getLocation().x;
        }
        return a->getLocation().y > b->getLocation().y;
    });
    // top = max_y;
    // bottom = max_y - scale;
    // vector<vector<string>> vec(size,vector<string>(size,string(". ")));
    // while(bottom >= origin.y){
    //     int i=0;
    //     auto it = objects.begin();
    //     while((*it)->getLocation().y >= bottom){
    //         left = min_x;
    //         right = min_x + scale;
    //         while(right <= origin.x + scale*size){
    //             for(auto& o: objects){
    //                 if(o->getLocation().)
    //             }
    //         }
    //     }
    //     top = bottom;
    //     bottom -= scale;
    // }
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
    vector<shared_ptr<SimObject>> res(objects.size());
    copy_if(objects.begin(),objects.end(),res.begin(),[this](const pair<string,shared_ptr<SimObject>>& a){
        Point p = a.second->getLocation();
        return (p.x >= origin.x && p.x <=origin.x + scale*size) && (p.y >= origin.y && p.y <= origin.y + scale*size);
    });
    return res;
}