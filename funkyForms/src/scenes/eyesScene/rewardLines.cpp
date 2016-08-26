//
//  rewardLines.cpp
//  RewardLine
//
//  Created by Gordey on 8/25/16.
//
//

#include "rewardLines.hpp"
// setup
void rewardLines::setup(){
    
}
void rewardLines::clear(){
    rewardCircles.clear();
}
void rewardLines::reward(ofPoint pos){
    vector<rewardLine> rewLines;
    
    float length = ofRandom(lineLength/5, lineLength);
    float speed = ofRandom(0.009, 0.02);
    int pattern = ofRandom(2, 5);
    float delay = ofRandom(0.2, 0.25);
    int lineCount = (int)ofRandom(10, 60);
    lineCount = (lineCount/pattern) * pattern;
    
    for (int i = 0; i < lineCount; i++) {
        rewardLine l;
        l.lineAnim.setSpeed(speed);
        l.lineLength = length * ((i+1)%pattern);
        l.lineWidth = 2.0 * ((i+1)%pattern);
        l.delay = delay * ((i+1)%pattern);
        l.setup();
        l.fadeIn();
        
        rewLines.push_back(l);
    }
    rewardCircle r;
    r.lines = rewLines;
    r.pos = pos;
    r.radius = ofRandom(lineRadius/2, lineRadius);
    
    rewardCircles.push_back(r);
}
// update
void rewardLines::update(){
    updateLines();
    updateRemoval();
}
void rewardLines::updateLines(){
    for(auto &r : rewardCircles){
        for(auto &line : r.lines){
            line.update();
        }
    }
}
void rewardLines::updateRemoval(){
    rewardCircles.erase(std::remove_if(
                               rewardCircles.begin(),
                               rewardCircles.end(),
                               
                               [&](rewardCircle & rewardCircle){
                                   bool isDead = true;
                                   for(auto &line : rewardCircle.lines){
                                       if (!line.isFinished){
                                           isDead = false;
                                           break;
                                       }
                                   }
                                   return isDead;
                               }
                               ),
                rewardCircles.end()
                );
}
// draw
void rewardLines::draw(){
    drawLines();
}
void rewardLines::drawLines(){
    for(auto &r : rewardCircles){
        float radius = r.radius;
        ofPushMatrix();
        ofTranslate(r.pos);
        for (int i = 0; i < r.lines.size(); i++) {
            float angleStep = 360.0/r.lines.size();
            ofPushMatrix();
            ofRotateZ(angleStep*i);
            ofTranslate(radius, 0);
            r.lines[i].draw();
            ofPopMatrix();
        }
        ofPopMatrix();
    }
}

