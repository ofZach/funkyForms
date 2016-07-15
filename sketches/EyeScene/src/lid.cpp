//
//  lid.cpp
//  EyeScene
//
//  Created by Zerc on 7/12/16.
//
//

#include "lid.hpp"
void lid::setup(int _width, int _height){
    width = _width;
    height = _height;
    
    lidHole.setCurveResolution(6);
    scaleY = 0; // eye closed
    randomDelay = (int) ofRandom(0, 120);
    topLidPos = -height/2;
}
void lid::open(){
    scaleVel = scaleSpeed;
}
void lid::close(){
    scaleVel = -scaleSpeed;
}
void lid::updateScaleForce(){
    // open/close eye
    scaleY += scaleVel;
    if(scaleY > 1.) isEyeOpen = true;
    if(scaleY < 0.) isEyeOpen = false;
    scaleY = ofClamp(scaleY, 0, 1);
}
void lid::update(){
    lidHole.clear();

    // create rig
    ofPoint p0(-width/2, 0);
    ofPoint p1(0, topLidPos);
    ofPoint p2(width/2, 0);
    ofPoint p3(0, height/2);
    
    lidHole.lineTo(p0);
    lidHole.bezierTo(p0, p1, p2);
    lidHole.lineTo(p2);
    lidHole.bezierTo(p2, p3, p0);
    
    lidHole.scale(scaleX, scaleY);
    lidHole.rotate(angle, ofVec3f(0, 0, 1));
}
void lid::setTopLidPos(float percent){
    topLidPos = ofMap(percent, 0, 1, -height/2, height/2);
}
