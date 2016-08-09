
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
    makeChild2();
    timeOffset = ofRandom(0, 100);
}
void PlantRig::setupRandom(){
    for(int i = 0; i< 100; i++){
        randomBools.push_back((int)rand()%2);
        randomFloats.push_back(ofRandom(1));
    }
}
void PlantRig::makeChild2(){
    child2Initpts.clear();
    child2pts.clear();
    int bCount = childBranchesPoints.size()/ofRandom(1, 2);

    int i = 0;
    
    while(i < childBranchesPoints.size()){
        vector<ofVec2f> points;
        
        
        ofVec2f *p1 = &childBranchesPoints[i][1];
        ofVec2f *p2 = &childBranchesPoints[i][2];
        
        ofVec2f p0 = childBranchesPoints[i][0];
//        links.push_back(&childBranchesPoints[i][1]);
//        links.push_back(&childBranchesPoints[i][2]);
        
        child2links.push_back(i);
        
        ofVec2f p3 = *p2+ofVec2f(1, 0);
        
        ofVec2f dir = *p1-p0;
        dir.normalize();
        
        ofVec2f delta = *p2-*p1;
        
        BranchSettings s;
        s.points = &points;
        s.pos = *p1 + delta / ofMap(randomFloats[i], 0, 1, 1, 5);
        s.dir = dir;
        s.lengthMin = cbLengthMin;
        s.lengthMax = cbLengthMax;
        s.branchCount = ofRandom(3, 5);
        
        makeBranch(s);
        child2pts.push_back(points);
        child2Initpts.push_back(points);
        
        i += ofRandom(1, 2);
    }
}
void PlantRig::makeMainBranch(){
    mainBranchPoints.clear();
    mainBranchInitPoints.clear();
    
    BranchSettings s;
    s.points = &mainBranchPoints;
    s.pos = pos;
    s.dir = dir;
    s.lengthMin = mbLengthMin;
    s.lengthMax = mbLengthMax;
    s.branchCount = mbCount;
    
    makeBranch(s);
    
    mainBranchInitPoints = mainBranchPoints;
}
void PlantRig::makeChildBranches(){
    childBranchesPoints.clear();
    childBranchesInitPoints.clear();
    
    int bCount = mainBranchPoints.size()/2;
    
    for(int i = 0; i < bCount; i++){
        vector<ofVec2f> points;
        
        ofVec2f p1 = mainBranchPoints[i*2+1];
        ofVec2f p2 = mainBranchPoints[i*2+2];
        
        ofVec2f p3 = p2+ofVec2f(1, 0);
        if((i*2+3) < mainBranchPoints.size()-1){
            p3 = mainBranchPoints[i*2+3];
        }
        
        ofVec2f dir = -(p3-p2);
        dir.normalize();
        
        ofVec2f delta = p2-p1;
        
        BranchSettings s;
        s.points = &points;
        s.pos = p1 + delta / ofMap(randomFloats[i], 0, 1, 1, 5);
        s.dir = dir;
        s.lengthMin = cbLengthMin;
        s.lengthMax = cbLengthMax;
        s.branchCount = ofRandom(3, cbCount);
        
        makeBranch(s);
        childBranchesPoints.push_back(points);
        childBranchesInitPoints.push_back(points);
    }

}
void PlantRig::makeBranch(BranchSettings s){
    ofVec2f curdir = ofVec2f(0, 0);
    ofVec2f curPos = s.pos;
    for(int i = 0; i< s.branchCount; i++ ){
        curPos = curPos+curdir * (s.lengthMin + ofRandom(1) * s.lengthMax);
        
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
// ----------- update
void PlantRig::update(){
    updateMainBranch();
    updateMBPolyline();
    updateChildBranches();
    updateCBPolyline();
    updateChild2();
}

void PlantRig::updateCBPolyline(){
    for(auto &b: childBranchesPoints){
        ofPolyline l;
        for(auto &p: b){
            l.lineTo(p);
        }
        childBranchLines.push_back(l);
    }
    for(auto &b: child2pts){
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
void PlantRig::updateC2Polyline(){
    
}

void PlantRig::updateMainBranch(){
    mainBranchPoints[0] = pos;
    for(int i = 0; i < mainBranchPoints.size(); i++){
        if(i>0){
            ofVec2f *p = &mainBranchPoints[i];
            ofVec2f *pp = &mainBranchPoints[i-1];
            ofVec2f delta = mainBranchInitPoints[i] - mainBranchInitPoints[i-1];
            float t = ofGetElapsedTimef() + timeOffset;
            float offsetX = ofMap(ofSignedNoise(t*timeSpeed+i*100.0, (int)(t*0.3) * 100, 0), -1, 1, 1,1.5);
            float offsetY = ofMap(ofSignedNoise(t*timeSpeed+i*300.0, (int)(t*0.3) * 100, 10000), -1, 1, 1, 1.5);
            ofVec2f newPos = *pp + ofVec2f(delta.x * offsetX, delta.y * offsetY) ;
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
                float t = ofGetElapsedTimef() + timeOffset;
                float offsetX = ofMap(ofSignedNoise(t*timeSpeed+i*100.0, (int)(t*0.3) * 100, 0), -1, 1, 1,1.5);
                float offsetY = ofMap(ofSignedNoise(t*timeSpeed+i*300.0, (int)(t*0.3) * 100, 10000), -1, 1, 1, 1.5);
                ofVec2f newPos = *pp + ofVec2f(delta.x * offsetX, delta.y * offsetY) ;
                float s = 0.7;
                p->x = p->x * s + newPos.x * (1 - s);
                p->y = p->y * s + newPos.y * (1 - s);
            }
        }
    }
}
void PlantRig::updateChild2(){
    for (int i = 0; i < child2pts.size(); i++) {
        ofVec2f *p1 = &childBranchesPoints[child2links[i]][1];
        ofVec2f *p2 = &childBranchesPoints[child2links[i]][2];
        ofVec2f p3 = *p2+ofVec2f(1, 0);
        
        ofVec2f dir = -(p3-*p2);
        dir.normalize();
        
        ofVec2f delta = *p2-*p1;
        
        child2pts[i][0] = *p1 + delta / ofMap(randomFloats[i], 0, 1, 1, 5);
        
        for (int j = 0; j < child2pts[i].size(); j++) {
            if(j>0){
                ofVec2f *p = &child2pts[i][j];
                ofVec2f *pp = &child2pts[i][j-1];
                ofVec2f delta = child2Initpts[i][j] - child2Initpts[i][j-1];
                float offsetX = ofMap(ofSignedNoise(ofGetElapsedTimef()*0.93+i*100.0, (int)(ofGetElapsedTimef()*0.3) * 100, 0), -1, 1, 1,1.5);
                float offsetY = ofMap(ofSignedNoise(ofGetElapsedTimef()*0.93+i*300.0, (int)(ofGetElapsedTimef()*0.3) * 100, 10000), -1, 1, 1, 1.5);
                ofVec2f newPos = *pp + ofVec2f(delta.x * offsetX, delta.y * offsetY) ;
                float s = 0.7;
                p->x = p->x * s + newPos.x * (1 - s);
                p->y = p->y * s + newPos.y * (1 - s);
            }
        }
    }

}

// ----------- draw
void PlantRig::draw(){
    drawMainBranch();
    drawChildBranches();
    drawChild2();
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
void PlantRig::drawChild2(){
    for(auto &b: child2pts){
        for(auto &p: b){
            ofDrawCircle(p, 5);
        }
    }
}

