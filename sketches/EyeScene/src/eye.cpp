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
    //((ofApp *)ofGetAppPtr())->keyPressed('z');
    
}
void eye::draw(){
    lids.lidHole.draw();
    
    ball.setFillColor(eyeColor);
    ball.draw();
    
    pupil.setFillColor(ofColor::black);
    pupil.draw();
}
void eye::blink(){
    lids.isBlink = true;
    float blinkSpeed = ofRandom(1.2, 5);
    lids.blinkSpeed = blinkSpeed;
}
void eye::update(ofVec2f _pos){
    // set resolution
    int resolution = ofMap(width, 10, 500, 2, 40, true);
    ball.setCircleResolution(resolution);
    pupil.setCircleResolution(resolution);
    lids.lidHole.setCurveResolution(resolution);
    
    pos = _pos;
    width = initWidth*scale;
    height = initHeight*scale;
    
    ball.clear();
    pupil.clear();
    
    lids.setSize(width, height);
    lids.update();
    
    if(ofGetFrameNum()%(int)ofRandom(50, 170)==0){
        lids.isBlink = true;
        float blinkSpeed = ofRandom(1.2, 5);
        lids.blinkSpeed = blinkSpeed;
    }
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
    
    ofVec2f offsetPos(ofMap(movePos.x, 0, 1, -width/2., width/2.),
                      ofMap(movePos.y, 0, 1, -height/2., height/2.)
                      );
    
    float eyeMaxRadius = width/5.;
    float diffX = lookAtPos.x - pos.x;
    float diffY = lookAtPos.y - pos.y;
    float angleTo = atan2(diffY, diffX);
    
    ofVec2f ballPos;
    if(pos.distance(lookAtPos)<eyeMaxRadius){
        ballPos.set(lookAtPos.x, lookAtPos.y);
    }else{
        ballPos.set(pos.x + eyeMaxRadius * cos(angleTo), pos.y + eyeMaxRadius * sin(angleTo) );
    }
        
    lids.lidHole.translate(pos);
    
    float radius = height/5.6;
    
    pupil.circle(ballPos, radius/2);
    pupil.setPolyWindingMode(OF_POLY_WINDING_ABS_GEQ_TWO );
    pupil.append(lids.lidHole);
    
    ball.circle(ballPos, radius);
    ball.setPolyWindingMode(OF_POLY_WINDING_ABS_GEQ_TWO );
    ball.append(lids.lidHole);
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