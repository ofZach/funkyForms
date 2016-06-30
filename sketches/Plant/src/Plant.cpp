//
//  Plant.cpp
//  Plant
//
//  Created by Zerc on 6/28/16.
//
//

#include "Plant.hpp"
void Plant::setup(){

    randomize();
}
void Plant::update(){

}
void Plant::draw(){
    int i = 0;
    for (int i = 0; i < mainBranch.size(); i++) {
        branchSettings s;
        s.pos.set(ofGetWidth()/2, ofGetHeight());
        s.leftRect.set(100/(i+1), 30/(i+1)+ofNoise(ofGetElapsedTimef()+i*500)*30);
        s.topRect.set(30/(i+1), 100/(i+1));
        s.radius = 30+ofNoise(ofGetElapsedTimef()+i*100)*30;
        s.isLeft = true;
        
        if(i>0){
            branchSettings b;
            b.leftRect.set(100/(i+1), 30/(i+1));
            b.topRect.set(30/(i+1)+ofNoise(ofGetElapsedTimef()+i*20)*30, 100/(i+1));
            b.radius = +ofNoise(ofGetElapsedTimef()+i*100)*30;
            
            ofRectangle *r5 = &mainBranch[i-1].rect5;
            ofRectangle *r6 = &mainBranch[i-1].rect6;
            
            if (mainBranch[i].isLeft) {
                s.pos = r5->getTopRight();
                branches[i-1].isLeft = false;
                b.pos = r5->getTopRight() + ofVec2f(0, r5->getHeight()/(i+1));
            }else{
                s.pos = r5->getTopLeft();
                branches[i-1].isLeft  = true;
                b.pos = r5->getTopLeft() + ofVec2f(0, r5->getHeight()/(i+1));
            }
            branches[i-1].update(b.pos, b.leftRect, b.topRect, b.radius);
            branches[i-1].draw();
//            branches[i-1].drawDebug();
        }

        mainBranch[i].update(s.pos, s.leftRect, s.topRect, s.radius);
        mainBranch[i].draw();
//        mainBranch[i].drawDebug();
        ofSetColor(ofColor::red);
//        ofDrawCircle(500, 500, 10);
    }
}
void Plant::randomize(){
    mainBranch.clear();
    branches.clear();
    mainBranchCount = (int)ofRandom(3, 6);
    for (int i = 0; i < mainBranchCount; i++) {
        SvgPlant svgplant;
        svgplant.color = ofColor::lightGreen;
        svgplant.isLeft = (int)ofRandom(2);
        svgplant.isCap = (int)ofRandom(2);
        svgplant.isTopRound = (int)ofRandom(2);
        mainBranch.push_back(svgplant);
    }
    for (int i = 0; i < mainBranchCount-1; i++) {
        SvgPlant svgplant;
        svgplant.isCap = (int)ofRandom(2);
        svgplant.color = ofColor::lightGreen;
        branches.push_back(svgplant);
    }
    for (int i = 0; i < mainBranch.size(); i++) {
    }
    for (int i = 0; i < branches.size(); i++) {
        branches[i].isLeft = (int)ofRandom(2);
    }
}