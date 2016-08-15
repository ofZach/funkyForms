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
}
void wave::updateForces(){
    float force2 = 1 - friction * timeStep * timeStep;
    
    for (int i = 0; i < points.size(); i++) {
        for(auto &id: cvData->idsThisFrame){
            // NOTE: since this is threaded, there's sometimes a frame where resampledSmooth might not
            // have any vertices... adding a check.
            if ((*(cvData->trackedContours))[id].data.resampleSmoothed.size() > 0){
                ofVec2f pos = (*(cvData->trackedContours))[id].data.resampleSmoothed.getVertices()[0];
                pos = cvData->remapForScreen(SCREEN_LEFT, pos);
                ofVec2f vel =  (*(cvData->trackedContours))[id].velAvgSmooth;
                if(pos.distance(points[i].p)<30){
                    if (!points[i].isFixed) {
                        points[i].p.y += vel.normalize().y*force;
                    }
                }
            }
        }
        float dy = (points[i].p.y - points[i].pp.y) * force2;
        points[i].pp = points[i].p;
        points[i].p.y = ofClamp(points[i].p.y + dy, 0, points[i].p.y + dy);
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
