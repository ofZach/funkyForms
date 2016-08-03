//
//  Plant.cpp
//  PlantSpring
//
//  Created by Zerc on 8/1/16.
//
//

#include "Plant.hpp"
// ----------- setup
void Plant::setup(){
    rig.setup();
    setupChildBranches();
    mbMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
}
void Plant::setupChildBranches(){
    for (int i = 0; i < rig.childBranchesPoints.size(); i++) {
        ofPolyline line;
        childLines1.push_back(line);
        childLines2.push_back(line);
    }
}
// ----------- udpate
void Plant::update(){
    rig.update();
    updatePolylines();
}
void Plant::updatePolylines(){

}
void Plant::updateMesh(){
    mbMesh.clear();
    for (float i = 0; i < 1; i += 0.01) {
        mbMesh.addVertex(mbLine1.getPointAtPercent(i));
        mbMesh.addVertex(mbLine2.getPointAtPercent(i));
    }
//    for (int i = 0; i < rig.childBranchesPoints.size(); i++) {
//        for (int j = 0; j < rig.childBranchesPoints[i].size(); j++) {
//            <#statements#>
//        }
//    }
}
void Plant::makeCorner(ofPolyline *line, ofPolyline &l, int i, float angle, float length){
    ofVec2f v = l.getTangentAtIndex(i);
    ofVec2f p = l.getVertices()[i] + v.rotate(angle)*length;
    ofVec2f v1 = l.getTangentAtIndex(i-1);
    ofVec2f pp = l.getVertices()[i-1] + v1.rotate(angle)*length;
    ofVec2f v2 = l.getTangentAtIndex(i+1);
    ofVec2f pn = l.getVertices()[i+1] + v2.rotate(angle)*length;
    ofVec2f deltaPP = p - pp;
    ofVec2f deltaPN = pn - p;
    float radius = MIN(pp.distance(p)/3, p.distance(pn)/3);
    ofVec2f rad = deltaPP.normalize()*radius;
    ofVec2f rad2 = deltaPN.normalize()*radius;
    ofVec2f b1 = p + (deltaPP-rad);
    ofVec2f b2 = p + rad2;
    
    line->lineTo(b1);
    line->bezierTo(b1, p, b2);
    line->lineTo(b2);

    // debug points
    
//    ofSetColor(ofColor::red);
//    ofDrawCircle(b2, 2);
//    
//    ofSetColor(ofColor::yellow);
//    ofDrawCircle(b1, 2);
    
//    ofSetColor(ofColor::blue);
//    ofDrawCircle(pp, 2);
//    
//    ofSetColor(ofColor::green);
//    ofDrawCircle(pn, 5);
    
}
// ----------- draw
void Plant::draw(){
    rig.draw();
    drawPolylines();
//    updateMesh();
//    mbMesh.draw();
}
void Plant::drawPolylines(){
    mbLine1.clear();
    mbLine2.clear();
    ofPolyline &l = rig.mainBranchLine;
    for (int i = 0; i < l.size(); i++) {
        ofVec2f v = l.getTangentAtIndex(i);
        float length = ofMap(i, 0, l.size()-1, 50, 10) ;
        ofVec2f p = l.getVertices()[i] + v.rotate(90)*length;
        ofVec2f p2 = l.getVertices()[i] + v.rotate(180)*length;
        if(i==0 || i==l.size()-1){
            mbLine1.lineTo(p);
            mbLine2.lineTo(p2);
        }
        if(i>0 && i<l.size()-1){
            makeCorner(&mbLine1, l, i, 90, length);
            makeCorner(&mbLine2, l, i, -90, length);
        }

    }
    ofSetColor(ofColor::white);
    mbLine1.draw();
    mbLine2.draw();
    
    for(auto &b: childLines1){
        b.clear();
    }
    for(auto &b: childLines2){
        b.clear();
    }
    for (int i = 0; i < rig.childBranchLines.size(); i++) {
        ofPolyline &l = rig.childBranchLines[i];
        ofSetColor(ofColor::red);
        l.draw();
        for (int j = 0; j < l.size(); j++) {
            ofVec2f v = l.getTangentAtIndex(j);
            float length = ofMap(j, 0, l.size()-1, 20, 10) ;
            ofVec2f p = l.getVertices()[j] + v.rotate(90)*length;
            ofVec2f p2 = l.getVertices()[j] + v.rotate(-180)*length;

            if(j==0 || j==l.size()-1){
                childLines1[i].lineTo(p);
                childLines2[i].lineTo(p2);
            }
            if(j>0 && j<l.size()-1){
                makeCorner(&childLines1[i], l, j, 90, length);
                makeCorner(&childLines2[i], l, j, -90, length);
            }
        }
    }
    for(auto &b: childLines1){
        b.draw();
    }
    for(auto &b: childLines2){
        b.draw();
    }
    
}