//
//  StencilWaves.cpp
//  WaveScene
//
//  Created by Zerc on 7/29/16.
//
//

#include "StencilWaves.hpp"
// -------------- setup
void StencilWaves::setup(){

    // fbo
    peopleFbo.allocate(ofGetWidth(), ofGetHeight());
    peopleFbo.begin(); ofClear(0, 0); peopleFbo.end();
}
// -------------- update
void StencilWaves::update(){
    updateContours();
    updateFbos();
}
void StencilWaves::updateFbos(){
    peopleFbo.begin();
    ofClear(0, 0);
    for(auto &p: contours){
        p.draw();
    }
    peopleFbo.end();
}
void StencilWaves::updateContours(){
    contours.clear();
    
    for (int i = 0; i < IM->getContourFinder()->getPolylines().size(); i++) {
        ofPolyline &l = IM->getContourFinder()->getPolyline(i);
        ofPath path;
        int res = ofMap(l.getPerimeter(), 0, 20, 0, 1);
        for (float i = 0; i < 1.; i += 1.0/res) {
            path.lineTo(l.getPointAtPercent(i));
        }
        path.setFilled(false);
        path.setStrokeWidth(5);
        path.setStrokeColor(ofColor::white);
        contours.push_back(path);
    }
}
// -------------- draw
void StencilWaves::draw(){
    peopleFbo.draw(0, 0);
}
