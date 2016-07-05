//
//  SvgPlant.cpp
//  Plant
//
//  Created by Zerc on 6/28/16.
//
//

#include "SvgPlant.hpp"
void SvgPlant::setup(){
    ofAddListener(*onTrigger, this, &SvgPlant::impulse);
}
void SvgPlant::drawDebug(){
    ofSetColor(color);
    ofDrawRectangle(rect1);
    ofSetColor(ofColor::lightCyan);
    ofDrawRectangle(rect2);
    ofSetColor(ofColor::lightSteelBlue);
    ofDrawRectangle(rect3);
    ofSetColor(ofColor::lightCyan);
    ofDrawRectangle(rect4);
    ofSetColor(ofColor::lightYellow);
    ofDrawRectangle(rect5);
}
void SvgPlant::drawCenterLine(){
    ofPoint p1, p2, p3, p4, p5, p6, p7;
    centerLine.clear();
    if(isLeft){
        p1.set(rect6.getCenter().x, rect6.getBottom());
        p2.set(rect6.getCenter());
        p3.set(rect1.getRight(), rect1.getCenter().y);
        p4.set(rect2.getRight(), rect2.getCenter().y);
        p5.set(rect3.getCenter());
        p6.set(rect4.getCenter().x, rect4.getTop());
        p7.set(rect5.getCenter().x, rect5.getTop());
    }else{
        p1.set(rect6.getCenter().x, rect6.getBottom());
        p2.set(rect6.getCenter());
        p3.set(rect1.getLeft(), rect1.getCenter().y);
        p4.set(rect2.getLeft(), rect2.getCenter().y);
        p5.set(rect3.getCenter());
        p6.set(rect4.getCenter().x, rect4.getTop());
        p7.set(rect5.getCenter().x, rect5.getTop());
    }
    centerLine.lineTo(p1);
    centerLine.bezierTo(p1, p2, p3);
    centerLine.lineTo(p3);
    centerLine.lineTo(p4);
    centerLine.bezierTo(p4, p5, p6);
    centerLine.lineTo(p7);
    ofSetColor(ofColor::white);
    centerLine.draw();
    float r = 3;
//    ofDrawCircle(p1, r);
//    ofDrawCircle(p2, r);
//    ofDrawCircle(p3, r);
//    ofDrawCircle(p4, r);
//    ofDrawCircle(p5, r);
//    ofDrawCircle(p6, r);
//    ofDrawCircle(p7, r);
}
void SvgPlant::draw(){

    ofPath path;
    ofPath path2;
    path.setColor(color);
    path2.setColor(color);
    
    if(isLeft){
        path.lineTo(rect2.getBottomRight());
        path.bezierTo(rect2.getBottomRight(), rect3.getBottomLeft() , rect4.getTopLeft() );
        path.lineTo(rect4.getTopRight());
        path.bezierTo(rect4.getTopRight(), rect4.getBottomRight(), rect2.getTopRight());
        if (isTopRound) {
            path2.lineTo(rect6.getTopLeft());
            path2.bezierTo(rect6.getTopLeft(), rect6.getTopRight(), rect6.getBottomRight());
            path2.lineTo(rect6.getBottomLeft());
        }else{
            path2.rectangle(rect6);
        }
    }else{
        path.lineTo(rect2.getBottomLeft());
        path.bezierTo(rect2.getBottomLeft(), rect3.getBottomRight() , rect4.getTopRight() );
        path.lineTo(rect4.getTopLeft());
        path.bezierTo(rect4.getTopLeft(), rect4.getBottomLeft(), rect2.getTopLeft());
        if (isTopRound) {
            path2.lineTo(rect6.getTopRight());
            path2.bezierTo(rect6.getTopRight(), rect6.getTopLeft(), rect6.getBottomLeft());
            path2.lineTo(rect6.getBottomRight());
        }else{
            path2.rectangle(rect6);
        }
    }
    
    path.draw();
    path2.draw();
    ofSetColor(color);
    ofDrawRectangle(rect1);
    ofDrawRectangle(rect5);
    
    if(isCap && !isTopRound){
        ofDrawCircle(rect5.getCenter().x, rect5.getTop(), rect5.getWidth()/2);
    }
    if(isImpulse){
        ofSetColor(ofColor::white);
        ofDrawCircle(centerLine.getPointAtPercent(impulsePercent), rect2.getHeight());
    }

}
void SvgPlant::impulse( bool &b){
    isImpulse = true;
    ofLog() << "notify";
    
}
void SvgPlant::update( ofVec2f pos, ofVec2f leftRectSize, ofVec2f topRectSize, float radius){
    if(isImpulse){
        impulsePercent +=0.05;
    }
    if(impulsePercent > 1){
        impulsePercent = 0;
        isImpulse = false;
        ofNotifyEvent(onImpulseFinished, isImpulse);
    }
    float topRectWidth = topRectSize.x;
    float topRectHeight = topRectSize.y;
    float leftRectWidth = leftRectSize.x;
    float leftRectHeight = leftRectSize.y;

    if(isLeft){
        rect6.set(0, 0, leftRectHeight, leftRectHeight);
        rect6.alignTo(pos, OF_ALIGN_HORZ_RIGHT, OF_ALIGN_VERT_BOTTOM);
        
        rect1.set(0, 0, leftRectWidth, leftRectHeight);
        rect1.alignTo(rect6.getTopLeft(), OF_ALIGN_HORZ_RIGHT, OF_ALIGN_VERT_TOP);
        
        rect2.set(0, 0, radius, rect1.getHeight());
        rect2.alignTo(rect1.getTopLeft(), OF_ALIGN_HORZ_RIGHT, OF_ALIGN_VERT_TOP);
        
        rect3.set(0, 0, topRectWidth, rect1.getHeight());
        rect3.alignTo(rect2.getTopLeft(), OF_ALIGN_HORZ_RIGHT, OF_ALIGN_VERT_TOP);
        
        rect4.set(0, 0, topRectWidth, radius);
        rect4.alignTo(rect3.getTopLeft(), OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_BOTTOM);
        
        rect5.set(0, 0, topRectWidth, topRectHeight);
        rect5.alignTo(rect4.getTopLeft(), OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_BOTTOM);

    }else{
        rect6.set(0, 0, leftRectHeight, leftRectHeight);
        rect6.alignTo(pos, OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_BOTTOM);

        rect1.set(0, 0, leftRectWidth, leftRectHeight);
        rect1.alignTo(rect6.getTopRight(), OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_TOP);
        
        rect2.set(rect1.getTopRight(), radius, rect1.getHeight());
        
        rect3.set(rect2.getTopRight(), topRectWidth, rect1.getHeight());
        
        rect4.set(0, 0, topRectWidth, radius);
        rect4.alignTo(rect3.getTopLeft(), OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_BOTTOM);
        
        rect5.set(0, 0, topRectWidth, topRectHeight);
        rect5.alignTo(rect4.getTopLeft(), OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_BOTTOM);
    }
}