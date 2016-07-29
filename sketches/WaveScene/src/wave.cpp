//
//  wave.cpp
//  Wave
//
//  Created by Zerc on 6/21/16.
//
//

#include "wave.hpp"
// ------- setup
void wave::setup(int _ypos, int _width){
    width = _width;
    ypos = _ypos;
    setupSpring();
}
void wave::setupSpring(){
    points.clear();
    springs.clear();
    for (int i = 0; i < amount; i++) {
        Spring spring;
        spring.setup( strength, restLength, invMass);
        springs.push_back( spring );
        
        Point_ point;
        
        float step = width/(amount*1.0-1.0);
        
        ofVec2f pos(i*step , ypos);
        
        point.p = pos;
        point.pp = pos;
        if(i == 0 || i == amount-1 ){
            point.isFixed = true;
        }else{
            point.isFixed = false;
        }
        points.push_back(point);
    }
}
// ------- update
void wave::update(vector<inputManager::Target> &targets){
    updateForces(targets);
    updatePolyline();
}
void wave::updateForces(vector<inputManager::Target> &targets){
    float force2 = 1 - friction * timeStep * timeStep;
    
    for (int i = 0; i < points.size(); i++) {
        for(auto &t: targets ){
            if(t.pos.distance(points[i].p)<30){
                if (!points[i].isFixed) {
                    points[i].p.y += t.vel.normalize().y*force;
                }
            }
        }
        float dy = (points[i].p.y - points[i].pp.y) * force2;
        points[i].pp = points[i].p;
        points[i].p.y = MAX(points[i].p.y + dy, 0);
    }
    for (int i = 0; i < springs.size(); i++) {
        if(i>0){
            springs[i].update(&points[i-1], &points[i]);
        }
    }
}
void wave::updatePolyline(){
    polyline.clear();
    for (int i = 0; i < points.size(); i++) {
        polyline.addVertex(points[i].p);
    }
}
// ------- draw
