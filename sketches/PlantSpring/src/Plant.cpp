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
    updateMesh();
}
void Plant::updatePolylines(){
    mbLine1.clear();
    mbLine2.clear();
    ofPolyline &l = rig.mainBranchLine;
    for (int i = 0; i < l.size(); i++) {
        makeStroke(i, 20, 50, l, &mbLine1, &mbLine2);
    }

    for(auto &b: childLines1){
        b.clear();
    }
    for(auto &b: childLines2){
        b.clear();
    }
    for (int i = 0; i < rig.childBranchLines.size(); i++) {
        ofPolyline &l = rig.childBranchLines[i];
        ofSetColor(ofColor::red);
        for (int j = 0; j < l.size(); j++) {
            makeStroke(j, 20, 10, l, &childLines1[i], &childLines2[i]);
        }
    }
}
void Plant::makeStroke(int i,
                       float min,
                       float max,
                       ofPolyline &centerLine,
                       ofPolyline *line1,
                       ofPolyline *line2
                       ){
    ofVec2f v = centerLine.getTangentAtIndex(i);
    float length = ofMap(i, 0, centerLine.size()-1, max, min) ;
    ofVec2f p = centerLine.getVertices()[i] + v.rotate(90)*length;
    ofVec2f p2 = centerLine.getVertices()[i] + v.rotate(180)*length;
    if(i==0 || i== centerLine.size()-1){
        line1->lineTo(p);
        line2->lineTo(p2);
    }
    if(i>0 && i < centerLine.size()-1){
        makeCorner(line1, centerLine, i, 90, length);
        makeCorner(line2, centerLine, i, -90, length);
    }
}
void Plant::updateMesh(){
    mbMesh.clear();
    float step = 0.01;
    for (float i = 0; i < 1; i += step) {
        mbMesh.addVertex(mbLine1.getPointAtPercent(i));
        mbMesh.addVertex(mbLine2.getPointAtPercent(i));
    }
    childMeshes.clear();
    for (int i = 0; i < childLines1.size(); i++) {
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        for (float j = 0; j < 1; j += step) {
            mesh.addVertex(childLines1[i].getPointAtPercent(j));
            mesh.addVertex(childLines2[i].getPointAtPercent(j));
        }
        childMeshes.push_back(mesh);
    }
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
    drawMeshes();
}
void Plant::drawPolylines(){
    ofSetColor(ofColor::white);
    mbLine1.draw();
    mbLine2.draw();
    for(auto &b: childLines1){
        b.draw();
    }
    for(auto &b: childLines2){
        b.draw();
    }
}
void Plant::drawMeshes(){
    mbMesh.draw();
    for(auto &m: childMeshes){
        m.draw();
    }
}