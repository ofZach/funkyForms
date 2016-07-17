//
//  Targets.cpp
//  EyeScene
//
//  Created by Zerc on 7/14/16.
//
//

#include "Targets.hpp"
void Targets::setup(){
    targets.clear();
   
    settings.loadFile("data.xml");
    
    settings.pushTag("data");
    dataCount = settings.getNumTags("pos");
    settings.popTag();
    
    for (int i = 0; i < 4; i++) {
        Target t;
        t.posOffset = ofVec2f(ofRandomWidth(), 0);
        t.counter = (int)ofRandom(0, dataCount-1);
        targets.push_back(t);
    }
    fstPosSmoothed.set(0, 0);
}
void Targets::calcEnergy(){
    float le = 0;
    float re = 0;
    ofVec2f zero(0, 0);
    for(auto &t: targets){
        if(t.pos.x<ofGetWidth()/2){
            le += zero.distance(t.vel);
        }else{
            re += zero.distance(t.vel);
        }
    }
    leftEnergy = le;
    rightEnergy = re;
}
void Targets::update(int x, int y){
    int i = 0;
    for(auto &t: targets){
        settings.pushTag("data");
        settings.pushTag("pos", t.counter);
        if(i==0){
            t.pos.x = x;
            t.pos.y = y;
        }else{
            t.pos.x = settings.getValue("x", 0.0) + t.posOffset.x;
            t.pos.y = settings.getValue("y", 0.0);
        }
        settings.popTag();
        settings.popTag();
        
        t.vel = t.pos - t.prevPos;
        
        t.prevPos = t.pos;
        if(t.counter == dataCount-1){
            t.counterVel = -1;
        }
        if(t.counter == 0){
            t.counterVel = 1;
        }
        t.counter += t.counterVel;
        i++;
    }

    calcEnergy();
}
Targets::Target *Targets::getFastest(){
    int index = 0;
    ofVec2f zero(0, 0);
    ofVec2f vel(0, 0);
    int i = 0;
    for(auto &t: targets){
        if(t.vel.distance(zero) > vel.distance(zero) ){
            vel = t.vel;
            index = i;
        }
        i++;
    }
    return &targets[index];
}
void Targets::draw(){
    ofSetColor(ofColor::salmon);
    for(auto &t: targets){
        ofDrawRectangle(t.pos, 50, 100);
    }
    ofSetColor(ofColor::white);
    float s = 0.7;
    fstPosSmoothed.x = fstPosSmoothed.x*s + (1-s)*getFastest()->pos.x;
    fstPosSmoothed.y = fstPosSmoothed.y*s + (1-s)*getFastest()->pos.y;
//    ofDrawCircle(fstPosSmoothed, 20);
}
