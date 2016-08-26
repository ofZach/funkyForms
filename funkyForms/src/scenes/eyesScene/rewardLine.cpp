//
//  rewardLine.cpp
//  funkyForms
//
//  Created by Gordey on 8/24/16.
//
//

#include "rewardLine.hpp"
// setup
void rewardLine::setup(){
    lineAnim.in();
}
// update
void rewardLine::update(){
    lineAnim.update();
    lineAnim.onFadeInEnd(this, &rewardLine::onLineFadeInEnd);
    lineAnim.onEventEnd();
}
void rewardLine::draw(){
    ofSetLineWidth(lineWidth);
    drawLine();
//    drawCircle();
}
// fade
void rewardLine::fadeIn(){
    lineAnim.in();
}
void rewardLine::fadeOut(){
    lineAnim.out();
}
void rewardLine::onLineFadeInEnd(){
    isFinished = true;
}
// draw
void rewardLine::drawLine(){
    ofPoint p1(0, 0);
    ofPoint p2(0, 0);
    p1.x = ofMap(lineAnim.getValue(), 0, 1, 0, lineLength, true);
    p2.x = ofMap(lineAnim.getValue(), delay, 1, 0, lineLength, true);

//    ofDrawCircle(p1, r);
//    ofDrawCircle(p2, 10);

    polyline.clear();
    polyline.lineTo(p1);
    polyline.lineTo(p2);
    
    polyline.draw();
    
//    ofDrawRectangle(line);
}