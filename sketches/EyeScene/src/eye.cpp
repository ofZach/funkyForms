//
//  eye.cpp
//  Eye
//
//  Created by Zerc on 6/22/16.
//
//

#include "eye.hpp"
#include "ofApp.h"

void eye::setup(ofVec2f _pos, float _width, float _height){
    lookAtPos.set(ofGetWidth()/2, ofGetHeight()/2);
    width = _width;
    height = _height;
    
    initWidth = _width;
    initHeight = _height;
    
    pos = _pos;
    lids.setup(width, height);
    movePos.set(0, 0);
    
    int resolution = ofMap(width, 10, 500, 2, 40, true);
    ball.setCircleResolution(resolution);
    pupil.setCircleResolution(resolution);
    lids.lidHole.setCurveResolution(resolution);

    open();
    //((ofApp *)ofGetAppPtr())->keyPressed('z');
    delay = ofRandom(0, 120);
    
}
void eye::draw(){
    lids.lidHole.draw();
    
    ball.setFillColor(eyeColor);
    ball.draw();
    
    pupil.setFillColor(ofColor::black);
    pupil.draw();
}
void eye::blink(){
    lids.isBlinking = true;
    float blinkSpeed = ofRandom(1.2, 5);
    lids.blinkSpeed = blinkSpeed;
}
void eye::randomBlink(){
    if(lids.isEyeOpen && ofGetFrameNum()%(int)ofRandom(50, 170)==0){
        lids.setScaleSpeed(ofRandom(0.1, 0.5));
        lids.close();
    }
    if(!lids.isEyeOpen){
        lids.open();
    }
}
void eye::openEye(){
    lids.setScaleSpeed(ofRandom(0.02, 0.05));
    lids.open();
    isBlinking = false;
    blinkCounter = 0;
    isEyeClosing = false;
}
void eye::closeEye(){
    lids.setScaleSpeed(ofRandom(0.02, 0.05));
    lids.close();
    isEyeClosing = true;
    isBlinking = false;
}
void eye::blinking(){
    if(isEyeOpen && delayCounter == delay){
        openEye();
        isEyeOpen = false;
    }
    if(isEyeClose && delayCounter == delay) {
        closeEye();
        isEyeClose = false;
    }
    delayCounter++;
    if(isBlinking){
        randomBlink();
    }
    if(blinkCounter>60 && !isEyeClosing){
        isBlinking = true;
    }
    blinkCounter++;
}
void eye::open(){
    isEyeOpen = true;
    delay = ofRandom(0, 120);
    delayCounter = 0;
}
void eye::close(){
    isEyeClose = true;
    delay = ofRandom(0, 120);
    delayCounter = 0;
}
void eye::createEyeball(){
    ball.clear();
    pupil.clear();

    lids.lidHole.translate(pos);

    float radius = height/5.6;
    
    pupil.circle(eyeballPos, radius/2);
    pupil.setPolyWindingMode(OF_POLY_WINDING_ABS_GEQ_TWO );
    pupil.append(lids.lidHole);
    
    ball.circle(eyeballPos, radius);
    ball.setPolyWindingMode(OF_POLY_WINDING_ABS_GEQ_TWO );
    ball.append(lids.lidHole);
}
void eye::calcEyeballPos(){
    float eyeMaxRadius = width/5.;
    float diffX = lookAtPos.x - pos.x;
    float diffY = lookAtPos.y - pos.y;
    float angleTo = atan2(diffY, diffX);
    
    float r = width/10.;
    ofVec2f offsetPos(ofMap(movePos.x, 0, 1, -r, r),
                      ofMap(movePos.y, 0, 1, -r, r)
                      );
    
    if(pos.distance(lookAtPos)<eyeMaxRadius){
        eyeballPos.set(lookAtPos.x+offsetPos.x, lookAtPos.y);
    }else{
        eyeballPos.set(pos.x + eyeMaxRadius * cos(angleTo)+offsetPos.x,
                       pos.y + eyeMaxRadius * sin(angleTo)+offsetPos.y );
    }
}
void eye::calcEyeballMovements(){
    if(ofGetFrameNum()%(int)ofRandom(50, 170)==0){
        isMove = true;
    }
    if(isMove){
        movePos = ofVec2f(ofNoise(moveCounter/12.0+1000), ofNoise(moveCounter/15.0));
        moveCounter ++;
    }
    if(moveCounter%(int)ofRandom(2, 10)==0){
        isMove = false;
    }
}
void eye::update(ofVec2f _pos){
    // set resolution
    int resolution = ofMap(width, 10, 500, 2, 40, true);
    ball.setCircleResolution(resolution);
    pupil.setCircleResolution(resolution);
    lids.lidHole.setCurveResolution(resolution);
    
    // update parameters
    pos = _pos;
    width = initWidth*scale;
    height = initHeight*scale;
    lids.setSize(width, height);
    lids.update();
    lids.updateScaleForce();
    
    blinking();
    
    // eyeBall
    calcEyeballMovements();
    calcEyeballPos();
    createEyeball();
 }
void eye::addScaleForce(ofVec2f _pos, float _radius, float _speed, float _maxScale){
    if(pos.distance(_pos) < _radius){
        scale += _speed;
        scale = MIN(scale, _maxScale);
    }else{
        scale -= _speed;
        scale = MAX(scale, 1.0);
    }
}
void eye::lookAtNear(ofVec2f _pos){
    if(pos.distance(_pos) < 100){
        lookAtPos = _pos;
    }
}