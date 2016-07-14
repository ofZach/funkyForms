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
        t.counter = (int)ofRandom(0, dataCount-1);
        targets.push_back(t);
    }
}
void Targets::update(){
    for(auto &t: targets){
        settings.pushTag("data");
        settings.pushTag("pos", t.counter);
        t.pos.x = settings.getValue("x", 0.0);
        t.pos.y = settings.getValue("y", 0.0);
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
    }
}
void Targets::draw(){
    ofSetColor(ofColor::salmon);
    for(auto &t: targets){
        ofDrawRectangle(t.pos, 50, 100);
    }
}
