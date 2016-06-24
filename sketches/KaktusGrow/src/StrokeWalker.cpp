//
//  StrokeWalker.cpp
//  KaktusGrow
//
//  Created by Zerc on 6/17/16.
//
//

#include "StrokeWalker.hpp"
void StrokeWalker::setup(){
    parameters.add(growCounter.set("growCounter", 10, 3, 800));
    parameters.add(strokeWidth.set("strokeWidth", 20, 0, 500));
    parameters.add(radius.set("radius", 0, -100, 100));
    parameters.add(step.set("step", 1, 1, 20));
    parameters.add(turnCount.set("turnCount", 5, 1, 20));
    parameters.add(minDist.set("minDist", 12, 10, 200));
    parameters.add(maxDist.set("maxDist", 12, 10, 200));
    timeOffset = ofRandom(0, 300);
    turnCount.addListener(this, &StrokeWalker::addTurns);
    int dist = 0;
    for (int i = 0; i < turnCount; i++) {
        int r = (int)ofRandom(2) % 2 * 2 - 1;
        randomTurns.push_back(r);
        dist += (int)ofRandom(minDist, maxDist);
        randomDist.push_back(dist);
    }
}
void StrokeWalker::randomize(){
    int dist = 0;
    randomTurns.clear();
    randomDist.clear();
    for (int i = 0; i < turnCount; i++) {
        int r = (int)ofRandom(2) % 2 * 2 - 1;
        randomTurns.push_back(r);
        dist += (int)ofRandom(minDist, maxDist);
        randomDist.push_back(dist);
    }
}
void StrokeWalker::addTurns(int &p){
    randomize();
}
void StrokeWalker::addPointsToMesh(ofMesh *m, ofNode l, ofNode r, int i){
    ofFloatColor col = ofFloatColor(0.5, 0.58, 0.1, opacity);
    
    float mix = cos(i);
    ofFloatColor temp = ofColor::lightGreen;
    ofFloatColor temp2 = ofColor::darkMagenta;
    
    col.set( mix * temp.r + (1-mix) * temp2.r,
             mix * temp.g + (1-mix) * temp2.g,
             mix * temp.b + (1-mix) * temp2.b,
            opacity
            ); //setHueAngle(360*ofNoise(i/100.0));
    m->addVertex(l.getGlobalPosition());
    m->addColor(col);
    m->addVertex(r.getGlobalPosition());
    m->addColor(col);
    endColor = col;
}
void StrokeWalker::draw(){
    mesh.draw();
    ofSetColor(endColor);
    ofDrawCircle(curPos, endWidth);
}
void StrokeWalker::drawDebug(){
    ofSetLineWidth(1);
    line.draw();
}
void StrokeWalker::update(){
    if (isGrow) {
        growCounter += growSpeed;
        if(growCounter>maxGrowCount){
            isGrow = false;
        }
    }

    ofNode root;
    ofNode mover;
    ofNode left;
    ofNode right;
    
    root.setParent(mover);
    left.setParent(root);
    right.setParent(root);
    
    mover.setPosition(initPos);
    root.setPosition(radius, 0, 0);
    left.setPosition(-strokeWidth, 0, 0);
    right.setPosition(strokeWidth, 0, 0);
    
    mesh.clear();
    line.clear();
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    walker walker;
    walker.setup();
    
    int distance = 0;
    int curTurn = 0;
    float curWidth = strokeWidth;
    
    for (int i = 0; i < growCounter; i++) {
        if(distance==randomDist[curTurn]){
            walker.turn(randomTurns[curTurn]);
            curTurn++;
        }
        distance++;
        walker.go(&mover, timeOffset);
        curWidth -= 0.02;
        
        left.setPosition(-curWidth, 0, 0);
        right.setPosition(curWidth,0, 0);
        
        ofVec3f zero(0, -1, 0);
        float angle = atan2(walker.curDir.x, walker.curDir.y)*(-180)/pi;
        ofQuaternion q = ofQuaternion(0, ofVec3f(1, 0, 0), 0, ofVec3f(0, 1, 0), angle, ofVec3f(0, 0, 1));
        root.setGlobalOrientation(q);
        
        line.addVertex(mover.getPosition());
        
        addPointsToMesh(&mesh, left, right, i);
        
        if(isTrackPoint){
            trackingPoint = mover.getPosition();
            for (int j = 0; j < trackingIndexs.size(); j++) {
                if (i == trackingIndexs[j]) {
                    trackingPoints[j] = mover.getPosition();
                    trackingWidth[j] = curWidth;
                }
            }
        }
    }
    endWidth = curWidth;
    curPos = mover.getGlobalPosition();
}
void StrokeWalker::startTrackPointAt(int index){
    isTrackPoint = true;
    trackingIndexs.push_back(index);
    trackingPoints.push_back(ofVec3f(0, 0, 0));
    trackingWidth.push_back(strokeWidth);
}
void StrokeWalker::grow(int speed){
    
    growSpeed = speed;
    growCounter = 1;
    isGrow = true;
    randomize();
}
