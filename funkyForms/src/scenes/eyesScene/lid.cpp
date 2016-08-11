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
    contour.clear();

    // create rig
    topLidPos = ofMap(topLidPercent, 0, 1, -height/2, height/2, true);
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
    
    ofVec2f scale(scaleX, scaleY);
    ofVec3f zero(0, 0, 1);
    
    p0 = p0*scale;
    p1 = p1*scale;
    p2 = p2*scale;
    p3 = p3*scale;
    
    p0.rotate(angle, zero);
    p1.rotate(angle, zero);
    p2.rotate(angle, zero);
    p3.rotate(angle, zero);
    
    contour.lineTo(p0);
    contour.bezierTo(p0, p1, p2);
    contour.lineTo(p2);
    contour.bezierTo(p2, p3, p0);
}
void lid::draw(){
    contour.draw();
}
void lid::setTopLidPos(float percent){
    topLidPercent = percent;
}
