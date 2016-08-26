//
//  forceSource.cpp
//  funkyForms
//
//  Created by Qinzi Tan on 8/25/16.
//
//

#include "forceSource.hpp"


//------------------------------------------------
void forceSource::setup(ofPoint _pos, int _direction, ofPoint _acc, float _angleAcc){
    
    pos.set(_pos);
    angleAcc = _angleAcc;
    direction = _direction;
    acc =  _acc;
    angle = 0;
    originPos = _pos;
    
}

//------------------------------------------------
void forceSource::addSinMove(float h,int _amplitude, float _angleVel, float _xVel, float _centerY){
    
    float angleVel = _angleVel;
    int amplitude = _amplitude;
    float xVel = _xVel;
    
    float centerY = _centerY;
    pos.y = amplitude * sin(angle)+30 * acc.y + centerY;

    
    xVel += acc.x;
    
    if (direction == 0){
        pos.x += xVel* (-1);
    } else if (direction == 1){
        pos.x += xVel * 1;
    }
    
    angleVel *= angleAcc;
    angle += angleVel;
    
}

//------------------------------------------------
void forceSource::addBoundary(float _w,float _h,float _r){
    
    float r = _r;
    if (pos.x>_w+r/2 && direction == 1) {
        pos.x = 0;
    }
    else if (pos.x<-r/2 && direction == 0){
        pos.x = _w;
    }
    
}

//------------------------------------------------
void forceSource::update(){
    //    vel += acc;
    //    pos += vel;
}

//------------------------------------------------
void forceSource::draw(){
    ofSetColor(255);
    ofDrawCircle(pos,5);
}
