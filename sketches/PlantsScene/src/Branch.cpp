//
//  Branch.cpp
//  Plant
//
//  Created by Zerc on 6/28/16.
//
//

#include "Branch.hpp"
void Branch::setup(){
    currColor = ofColor(0, 0);
    prevColor = ofColor(0, 0);
    topRectHeightSmooth = ofRandom(0.9, 0.9999);
    leftRectWidthSmooth = ofRandom(0.9, 0.9999);
}
void Branch::drawDebug(){
    ofSetColor(ofColor::cadetBlue);
    ofDrawRectangle(rect1);
    ofSetColor(ofColor::lightCyan);
    ofDrawRectangle(rect2);
    ofSetColor(ofColor::lightSteelBlue);
    ofDrawRectangle(rect3);
    ofSetColor(ofColor::lightCyan);
    ofDrawRectangle(rect4);
    ofSetColor(ofColor::lightYellow);
    ofDrawRectangle(rect5);
    ofSetColor(ofColor::lightGreen);
    ofDrawRectangle(rect6);
}
void Branch::drawCenterLine(){
    ofSetColor(ofColor::white);
    centerLine.draw();
    float r = 3;
}
void Branch::draw(){
  
    mesh.draw();

}
void Branch::impulse( ofColor &color){
    isImpulse = true;
    currColor = color;
}
void Branch::update( ofVec2f pos, ofVec2f leftRectSize, ofVec2f topRectSize, float radius, iColor &icolor){
    
    //--------------- centerline
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

    //--------------- impulse
    if(isImpulse){
        impulsePercent +=0.02;
    }
    if(impulsePercent > 1){
        prevColor = currColor;
        impulsePercent = 0;
        isImpulse = false;
    }
    
    //--------------- rectangle update
    float topRectWidth = topRectSize.x;
    topRectHeight = topRectHeightSmooth * topRectHeight + (1 - topRectHeightSmooth) * topRectSize.y;
    leftRectWidth = leftRectWidthSmooth * leftRectWidth + (1 - leftRectWidthSmooth) * leftRectSize.x;
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
    ofPath path;
    ofPath path2;
    path.setColor(color);
    path2.setColor(color);
    
    if(isLeft){
        points[0] = rect6.getBottomRight();
        points[1] = rect6.getTopRight();
        points[2] = rect1.getTopRight();
        points[3] = rect2.getTopRight();
        points[4] = rect3.getTopRight();
        points[5] = rect4.getTopRight();
        points[6] = rect5.getTopRight();
        points[7] = rect5.getTopLeft();
        points[8] = rect4.getTopLeft();
        points[9] = rect3.getTopLeft();
        points[10] = rect3.getBottomLeft();
        points[11] = rect2.getBottomLeft();
        points[12] = rect1.getBottomLeft();
        points[13] = rect6.getBottomLeft();
    }else{
        points[0] = rect6.getBottomLeft();
        points[1] = rect6.getTopLeft();
        points[2] = rect1.getTopLeft();
        points[3] = rect2.getTopLeft();
        points[4] = rect3.getTopLeft();
        points[5] = rect4.getTopLeft();
        points[6] = rect5.getTopLeft();
        points[7] = rect5.getTopRight();
        points[8] = rect4.getTopRight();
        points[9] = rect3.getTopRight();
        points[10] = rect3.getBottomRight();
        points[11] = rect2.getBottomRight();
        points[12] = rect1.getBottomRight();
        points[13] = rect6.getBottomRight();
    }
    stroke1.clear();
    stroke2.clear();
    
    if(isTopRound){
        stroke1.lineTo(points[0]);
        stroke1.bezierTo(points[0], points[1], points[2]);
    }else{
        stroke1.lineTo(points[0]);
        stroke1.lineTo(points[1]);
    }
    
    stroke1.lineTo(points[2]);
    stroke1.lineTo(points[3]);
    stroke1.bezierTo(points[3], points[4], points[5]);
    stroke1.lineTo(points[5]);
    stroke1.lineTo(points[6]);
    
    stroke2.lineTo(points[0]);
    stroke2.lineTo(points[13]);
    stroke2.lineTo(points[12]);
    stroke2.bezierTo(points[12], points[10], points[8]);
    stroke2.lineTo(points[8]);
    stroke2.lineTo(points[7]);
    
    float y = rect5.getTop()-rect5.getWidth()/2;
    
    if(isCap && !isTopRound){
        ofPoint p1, p2, p3;
        if (isLeft) {
            p1.set(rect5.getTopRight());
            p2.set(rect5.getTopRight().x, y);
            p3.set(rect5.getCenter().x, y);
        }else{
            p1.set(rect5.getTopLeft());
            p2.set(rect5.getTopLeft().x, y);
            p3.set(rect5.getCenter().x, y);
        }
        stroke1.bezierTo(p1, p2, p3);
    }else{
        stroke1.lineTo(rect5.getCenter().x, rect5.getTop());
    }
    if(isCap && !isTopRound){
        ofPoint p1, p2, p3;
        if (isLeft) {
            p1.set(rect5.getTopLeft());
            p2.set(rect5.getTopLeft().x, y);
            p3.set(rect5.getCenter().x, y);
        }else{
            p1.set(rect5.getTopRight());
            p2.set(rect5.getTopRight().x, y);
            p3.set(rect5.getCenter().x, y);
        }
        stroke2.bezierTo(p1, p2, p3);
    }else{
        stroke2.lineTo(rect5.getCenter().x, rect5.getTop());
    }
    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    int j = 0;
    for (float i = 0; i < 1; i+=1.0/resolution) {
        ofColor col = icolor.getColorAt(j + colorOffsetMult*resolution);
        mesh.addVertex(stroke1.getPointAtPercent(i));
        mesh.addColor(col);
        mesh.addVertex(stroke2.getPointAtPercent(i));
        mesh.addColor(col);
        j++;
    }
}