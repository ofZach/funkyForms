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
void wave::update(){
    updateForces();
    updatePolyline();
    targets.clear();
}
void wave::addForceTo(Point_ *p, float _force){
    if(!p->isFixed){
        p->p.y += _force*force;
    }
}
void wave::updateForces(){
    float force2 = 1 - friction * timeStep * timeStep;
    
    for (int i = 0; i < points.size(); i++) {
        float dy = (points[i].p.y - points[i].pp.y) * force2;
        points[i].pp = points[i].p;
        if(!points[i].isFixed){
            points[i].p.y = ofClamp(points[i].p.y + dy, 0, points[i].p.y + dy);
        }
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
