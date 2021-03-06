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
    setupMeshRes();
    setupChildBranches();
    mbMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    setupAnimators();
    ageMax = 100000000; //(int)ofRandom(300, 600);
    shadow.load("assets/glow.png");
    bGrewUp = false;
}
void Plant::setupAnimators(){
    fadeAnimator.setup(0, 1);
    fadeAnimator.pctSpeed = 0.2;
    fadeAnimator.setIn();
    
    mbGrowAnimator.setup(0, 1);
    fadingDelay = 0;//ofRandom(20, 50);
    for (int i = 0; i < rig.childBranchesPoints.size()  + rig.child2pts.size(); i++) {
        Animator animator;
        cbGrowAnimators.push_back(animator);
        cbGrowAnimators[i].setup(0, 1);
    }
}
void Plant::setupMeshRes(){
//    rig.mainBranchLine.getl
}
void Plant::setupChildBranches(){
    for (int i = 0; i < rig.childBranchesPoints.size() + rig.child2pts.size() ; i++) {
        ofPolyline line;
        childLines1.push_back(line);
        childLines2.push_back(line);
        cbWidths.push_back(ofRandom(cbWidth/2, cbWidth));
    }
}
// ----------- udpate
void Plant::update(){
    rig.update();
    updatePolylines();
    updateAnimators();
    updateMesh();
    updateAge();
}
void Plant::updateAnimators(){
    fadeAnimator.update();
    mbGrowAnimator.update();
    if(isFading){
        fadingCounter++;
    }
    if(fadingCounter>fadingDelay){
        fadeAnimator.out();
    }
    for(auto &a:cbGrowAnimators ){
        a.update();
    }
    for (int i = 0; i < rig.mainBranchPcts.size(); i++) {
        if (mbGrowAnimator.getValue()>rig.mainBranchPcts[i]) {
            cbGrowAnimators[i].in();
        }
    }
}
void Plant::updateAge(){
    age++;
    if(age > ageMax){fadeAnimator.out();}
}
void Plant::updatePolylines(){
    mbLine1.clear();
    mbLine2.clear();
    ofPolyline &l = rig.mainBranchLine;
    for (int i = 0; i < l.size(); i++) {
        makeStroke(i, mbWidth*scale, mbWidth*scale, l, &mbLine1, &mbLine2);
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
            makeStroke(j, cbWidths[i]*scale, cbWidths[i]*scale, l, &childLines1[i], &childLines2[i]);
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
    float angle = 90;
    float hackValue = 0.8;
    if(i==0 || i == centerLine.size()-1){
        ofVec2f p = centerLine.getVertices()[i] + v.rotate(angle)*length*hackValue;
        ofVec2f v2 = centerLine.getTangentAtIndex(i);
        ofVec2f p2 = centerLine.getVertices()[i] + v2.rotate(-angle)*length*hackValue;
        line1->lineTo(p);
        line2->lineTo(p2);
    }
    if(i>0 && i < centerLine.size()-1){
        makeCorner(line1, centerLine, i, angle, length);
        makeCorner(line2, centerLine, i, -angle, length);
    }
    if(i == centerLine.size()-1){
        ofVec2f v = centerLine.getTangentAtIndex(i);
        float length = ofMap(i, 0, centerLine.size()-1, min, min) ;
        ofVec2f _p2 = centerLine.getVertices()[i] + v.rotate(90)*length*hackValue;
        ofVec2f _p1 = centerLine.getVertices()[i] + v.rotate(180)*length*hackValue;
        ofVec2f _p3 = _p1 + (_p2 - _p1)/2;
        ofVec2f _delta = _p2 - _p1;
        ofVec2f pCenter = _p3 - _delta.getPerpendicular()*min;
        ofVec2f pLeft = pCenter - _delta/2;
        ofVec2f pRight = pCenter + _delta/2;
        
        line2->bezierTo(_p1, pLeft, pCenter);
        line1->bezierTo(_p2, pRight, pCenter);
        
        //                ofSetColor(ofColor::yellow);
        //                ofDrawCircle(p1, 5);
        //                ofSetColor(ofColor::red);
        //                ofDrawCircle(p2, 5);
        //                ofSetColor(ofColor::blueViolet);
        //                ofDrawCircle(p3, 5);
        //                ofSetColor(ofColor::darkMagenta);
        //                ofDrawCircle(pCenter, 5);
        //                ofSetColor(ofColor::lightPink);
        //                ofDrawCircle(pLeft, 5);
        //                ofSetColor(ofColor::lightSkyBlue);
        //                ofDrawCircle(pRight, 5);
    }

}
void Plant::updateMesh(){
    mbMesh.clear();
    float perimeter = mbLine1.getPerimeter();
    float distance = 10;
    float step = 0.02;
    
    for (float i = 0; i < 1; i += step) {
        float opacity;
        if(mbGrowAnimator.getValue()>i){
            opacity = fadeAnimator.getValue();
        }else{
            opacity = 0;
        }
        ofVec2f dir1 = mbLine1.getTangentAtIndexInterpolated(ofMap(i, 0, 1, 0, mbLine1.size()-1));
        ofColor col = color;
        mbMesh.addVertex(mbLine1.getPointAtPercent(i));
        mbMesh.addColor(ofFloatColor(col, opacity));
        col.setBrightness(ofMap(col.getBrightness(), 0, 255, 0, 200));
        mbMesh.addVertex(mbLine2.getPointAtPercent(i));
        mbMesh.addColor(ofFloatColor(col, opacity));
    }
    
    childMeshes.clear();
    childShadows.clear();
    
    for (int i = 0; i < childLines1.size(); i++) {
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        ofMesh shadow;
        shadow.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        

        Animator &a = cbGrowAnimators[i];
        if(i>rig.childBranchesPoints.size()-1){
            int parentIndex = i-rig.childBranchesPoints.size();
            if(cbGrowAnimators[parentIndex].getValue()>0.5){
                a.in();
            }
        }
        for (float j = 0; j < 1; j += step) {
            float opacity = 1;
            ofColor col = color;
            if(a.getValue()>j){
                opacity = ofMap(j, 0, step*8, 0, 1, true) * fadeAnimator.getValue();
            }else{
                opacity = 0;
            }
//            float opacity = ofMap(j, 0, step*8, 0, 1, true) * fadeAnimator.getValue();
            mesh.addVertex(childLines1[i].getPointAtPercent(j));
            mesh.addColor(ofFloatColor(col, opacity));
            mesh.addVertex(childLines2[i].getPointAtPercent(j));
            col.setBrightness(ofMap(j, 0, 1, col.getBrightness(), 120));
            mesh.addColor(ofFloatColor(col, opacity));
        }
        childMeshes.push_back(mesh);
        // add shadow
//        ofVec2f dir = rig.childBranchLines[i].getTangentAtIndex(0);
//        ofVec2f p = rig.childBranchLines[i].getVertices()[0];
//        ofVec2f p1 = p + dir*10;
//        ofVec2f p2 = p + ofVec2f(0, 1)*40;
//        ofColor col = ofColor::black;
//        shadow.addVertex(p);
//        shadow.addColor(ofFloatColor(col, 0.2));
//        shadow.addVertex(p1);
//        shadow.addColor(ofFloatColor(col, 0));
//        shadow.addVertex(p2);
//        shadow.addColor(ofFloatColor(col, 0));
//
//        childShadows.push_back(shadow);
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
//    rig.draw();
//    drawPolylines();
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
    for(auto &m: childShadows){
        m.draw();
    }
    for(auto &m: childMeshes){
        m.draw();
    }
}
void Plant::drawShadow(){
    for(auto &p : rig.mainBranchLine.getResampledBySpacing(2)){
        float x = p.x - shadowRadius;
        float y = p.y - shadowRadius;
        ofSetColor(0, shadowOpacity);
        shadow.draw(x, y, shadowRadius*2, shadowRadius*2);
    }
}