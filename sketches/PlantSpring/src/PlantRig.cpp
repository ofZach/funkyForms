
//
//  PlantRig.cpp
//  PlantSpring
//
//  Created by Zerc on 8/1/16.
//
//

#include "PlantRig.hpp"
// ----------- setup
void PlantRig::setup(){
    setupRandom();
}
void PlantRig::setupRandom(){
    for(int i = 0; i< 100; i++){
        randomBools.push_back((int)rand()%2);
        randomFloats.push_back(ofRandom(1));
    }
}

// ----------- update
void PlantRig::update(){
    updateMainBranch();
    updateChildBranches();
    updatePolylines();
}
void PlantRig::updatePolylines(){
    mainBranchLine.clear();
    childBranchLines.clear();
    
    for(auto &p: mainBranchPoints){
        mainBranchLine.lineTo(p);
    }
    for(auto &b: childBranchesPoints){
        ofPolyline l;
        for(auto &p: b){
            l.lineTo(p);
        }
        childBranchLines.push_back(l);
    }
}
void PlantRig::updateMainBranch(){
    mainBranchPoints.clear();
    
    BranchSettings s;
    s.points = &mainBranchPoints;
    s.pos = ofVec2f(ofGetWidth()/2, ofGetHeight());
    s.dir = ofVec2f(0, -1);
    s.lengthMin = 50;
    s.lengthMax = 100;
    s.branchCount = 10;
    
    makeBranch(s);
}
void PlantRig::updateChildBranches(){
    childBranchesPoints.clear();
    
    int bCount = mainBranchLine.getVertices().size()/2;

    for(int i = 0; i < bCount; i++){
        
        vector<ofVec2f> points;
        
        ofPolyline line;
        childBranchLines.push_back(line);
        
        ofVec2f p1 = mainBranchLine.getPointAtIndexInterpolated(i*2);
        ofVec2f p2 = mainBranchLine.getPointAtIndexInterpolated(i*2+1);
        
        ofVec2f p3 = p2+ofVec2f(1, 0);
        if((i*2+2) < mainBranchLine.size()-1){
           p3 = mainBranchLine.getPointAtIndexInterpolated(i*2+2);
        }

        ofVec2f dir = -(p3-p2);
        dir.normalize();
        
        ofVec2f delta = p2-p1;
        
        BranchSettings s;
        s.points = &points;
        s.pos = p1 + delta / ofMap(randomFloats[i], 0, 1, 1, 5);
        s.dir = dir;
        s.lengthMin = 20;
        s.lengthMax = 70;
        s.branchCount = ofMap(randomFloats[i], 0, 1, 3, 5);
        
        makeBranch(s);
        childBranchesPoints.push_back(points);
    }
}
void PlantRig::makeBranch(BranchSettings s){
    ofVec2f curdir = ofVec2f(0, 0);
    ofVec2f curPos = s.pos;
    for(int i = 0; i< s.branchCount; i++ ){
        curPos = curPos+curdir * (s.lengthMin + randomFloats[i] * s.lengthMax);
       
        s.points->push_back(curPos);
        
        // grow branch UP or LEFT/RIGHT
        if(i>0){
            if(curdir == ofVec2f(0, -1)){
                if(randomBools[i] == 1){ // right
                    curdir = ofVec2f(1, 0);
                }else{ // left
                    curdir = ofVec2f(-1, 0);
                }
            }else if(curdir == ofVec2f(-1, 0) || curdir == ofVec2f(1, 0) ){
                curdir = ofVec2f(0, -1);
            }
        }else{
           curdir = s.dir;
        }
    }
}
// ----------- draw
void PlantRig::draw(){
    ofSetColor(255);
    mainBranchLine.draw();
    for(auto &l: childBranchLines){
        l.draw();
    }
    ofSetColor(ofColor::green);
    for(auto &p: mainBranchPoints){
        ofDrawCircle(p, 5);
    }
    for(auto &b: childBranchesPoints){
        for(auto &p: b){
            ofDrawCircle(p, 5);
        }
    }
}

