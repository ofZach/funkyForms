
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
    makeMainBranch();
    makeChildBranches();
}
void PlantRig::setupRandom(){
    for(int i = 0; i< 100; i++){
        randomBools.push_back((int)rand()%2);
        randomFloats.push_back(ofRandom(1));
    }
}
void PlantRig::makeMainBranch(){
    mainBranchPoints.clear();
    mainBranchInitPoints.clear();
    
    BranchSettings s;
    s.points = &mainBranchPoints;
    s.pos = ofVec2f(ofGetWidth()/2, ofGetHeight());
    s.dir = ofVec2f(0, -1);
    s.lengthMin = 50;
    s.lengthMax = 100;
    s.branchCount = 10;
    
    makeBranch(s);
    
    mainBranchInitPoints = mainBranchPoints;
}
void PlantRig::makeChildBranches(){
    childBranchesPoints.clear();
    childBranchesInitPoints.clear();
    
    int bCount = mainBranchPoints.size()/2;
    
    for(int i = 0; i < bCount; i++){
        vector<ofVec2f> points;
        
        ofVec2f p1 = mainBranchPoints[i*2];
        ofVec2f p2 = mainBranchPoints[i*2+1];
        
        ofVec2f p3 = p2+ofVec2f(1, 0);
        if((i*2+2) < mainBranchPoints.size()-1){
            p3 = mainBranchPoints[i*2+2];
        }
        
        ofVec2f dir = -(p3-p2);
        dir.normalize();
        
        ofVec2f delta = p2-p1;
        
        BranchSettings s;
        s.points = &points;
        s.pos = p1 + delta / ofMap(randomFloats[i], 0, 1, 1, 5);
        s.dir = dir;
        s.lengthMin = 20;
        s.lengthMax = 100;
        s.branchCount = 3;
        
        makeBranch(s);
        childBranchesPoints.push_back(points);
        childBranchesInitPoints.push_back(points);
    }

}
// ----------- update
void PlantRig::update(){
    updateMainBranch();
    updateMBPolyline();
    
    updateChildBranches();
    updateCBPolyline();
}
void PlantRig::updateCBPolyline(){
    for(auto &b: childBranchesPoints){
        ofPolyline l;
        for(auto &p: b){
            l.lineTo(p);
        }
        childBranchLines.push_back(l);
    }
}
void PlantRig::updateMBPolyline(){
    mainBranchLine.clear();
    childBranchLines.clear();
    
    for(auto &p: mainBranchPoints){
        mainBranchLine.lineTo(p);
    }

}
void PlantRig::updateMainBranch(){
    mainBranchPoints[0] = pos;
    for(int i = 0; i < mainBranchPoints.size(); i++){
        if(i>0){
            ofVec2f *p = &mainBranchPoints[i];
            ofVec2f *pp = &mainBranchPoints[i-1];
            ofVec2f delta = mainBranchInitPoints[i] - mainBranchInitPoints[i-1];
            ofVec2f newPos = *pp + delta;
            float s = 0.7;
            p->x = p->x * s + newPos.x * (1 - s);
            p->y = p->y * s + newPos.y * (1 - s);
        }
    }
}
void PlantRig::updateChildBranches(){
    for (int i = 0; i < childBranchesPoints.size(); i++) {
        ofVec2f p1 = mainBranchPoints[i*2];
        ofVec2f p2 = mainBranchPoints[i*2+1];
        
        ofVec2f p3 = p2+ofVec2f(1, 0);
        if((i*2+2) < mainBranchPoints.size()-1){
            p3 = mainBranchPoints[i*2+2];
        }
        
        ofVec2f dir = -(p3-p2);
        dir.normalize();
        
        ofVec2f delta = p2-p1;
        
        childBranchesPoints[i][0] = p1 + delta / ofMap(randomFloats[i], 0, 1, 1, 5);
        
        for (int j = 0; j < childBranchesPoints[i].size(); j++) {
            if(j>0){
                ofVec2f *p = &childBranchesPoints[i][j];
                ofVec2f *pp = &childBranchesPoints[i][j-1];
                ofVec2f delta = childBranchesInitPoints[i][j] - childBranchesInitPoints[i][j-1];
                ofVec2f newPos = *pp + delta;
                float s = 0.7;
                p->x = p->x * s + newPos.x * (1 - s);
                p->y = p->y * s + newPos.y * (1 - s);
            }
        }
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
    drawMainBranch();
    drawChildBranches();
}
void PlantRig::drawMainBranch(){
    ofSetColor(255);
    mainBranchLine.draw();
    
    ofSetColor(ofColor::green);
    for(auto &p: mainBranchPoints){
//        ofDrawCircle(p, 5);
    }
}
void PlantRig::drawChildBranches(){
     ofSetColor(255);
    for(auto &l: childBranchLines){
        l.draw();
    }
    ofSetColor(ofColor::green);
    for(auto &b: childBranchesPoints){
        for(auto &p: b){
            ofDrawCircle(p, 5);
        }
    }
}

