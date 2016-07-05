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
void Plant::update(ofVec2f _velocity){
    smooth(&velocity, _velocity);
}
void Plant::smooth(ofVec2f *vec , ofVec2f newVec){
    float smoothVal = 0.97;
    ofVec2f smoothVec(smoothVal, smoothVal);
    ofVec2f oneVec(1, 1);
    vec->set(*vec*smoothVec + newVec*(oneVec-smoothVec));
}
Plant::branchSettings Plant::mainBSettings(int i){
    branchSettings s;
    if (mainBranch[i].isLeft) {
        s.leftRect.set(100/(i+1)+min(velocity.x*(20.0/(i+1)), (100.0+1)/(i+1)), 30/(i+1)*size);
        s.topRect.set(30/(i+1)*size, 100/(i+1)-velocity.y*20);
    }else{
        s.leftRect.set(100/(i+1)-min(velocity.x*(20.0/(i+1)), (100.0+1)/(i+1)), 30/(i+1)*size);
        s.topRect.set(30/(i+1)*size, 100/(i+1)-velocity.y*20);
    }
    s.radius = (30+ofNoise(ofGetElapsedTimef()+i*100)*30)*size;
    s.isLeft = true;
    return s;
}
void Plant::draw(int x, int y){
    int i = 0;
    if(mainBranch.size()>0){
        int limit = 3;
        if (velocity.x < -limit || velocity.x>limit ) {
//            ofLog() << "impulse";
            bool b = true;
            mainBranch[0].impulse(b);
        }
    }
    for (int i = 0; i < mainBranch.size(); i++) {
        branchSettings s = mainBSettings(i);
        s.pos.set(x, y);

        if(i>0){
            if(mainBranch[i-1].impulsePercent>1){
//                mainBranch[i].impulse();
            }
            branchSettings b;
            b.radius = (30+ofNoise(ofGetElapsedTimef()+i*100)*30)*size;
            
            ofRectangle *r5 = &mainBranch[i-1].rect5;
            ofRectangle *r6 = &mainBranch[i-1].rect6;
            
            if (mainBranch[i].isLeft) {
                b.leftRect.set(100/(i+1), 30/(i+1)*size);
                b.topRect.set(30/(i+1)+ofNoise(ofGetElapsedTimef()+i*20)*30-min(velocity.x*(20.0/(i+1)), (100.0+1)/(i+1)), 100/(i+1)*size);
                s.pos = r5->getTopRight();
                branches[i-1].isLeft = false;
                b.pos = r5->getTopRight() + ofVec2f(0, r5->getHeight()/(i+1));
            }else{
                b.leftRect.set(100/(i+1), 30/(i+1)*size);
                b.topRect.set(30/(i+1)+ofNoise(ofGetElapsedTimef()+i*20)*30+min(velocity.x*(20.0/(i+1)), (100.0+1)/(i+1)), 100/(i+1)*size);
                s.pos = r5->getTopLeft();
                branches[i-1].isLeft  = true;
                b.pos = r5->getTopLeft() + ofVec2f(0, r5->getHeight()/(i+1));
            }
            branches[i-1].update(b.pos, b.leftRect, b.topRect, b.radius);
            branches[i-1].draw();
//            branches[i-1].drawDebug();
            branches[i-1].drawCenterLine();
        }

        mainBranch[i].update(s.pos, s.leftRect, s.topRect, s.radius);
        
        mainBranch[i].draw();
//        mainBranch[i].drawDebug();
        mainBranch[i].drawCenterLine();
        ofSetColor(ofColor::red);
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
        if (i>0) {
            mainBranch[i].onTrigger = &mainBranch[i-1].onImpulseFinished;
            mainBranch[i].setup();
        }
    }
    for (int i = 0; i < mainBranchCount-1; i++) {
        SvgPlant svgplant;
        svgplant.isCap = (int)ofRandom(2);
        svgplant.color = ofColor::lightGreen;
        branches.push_back(svgplant);
        branches[i].onTrigger = &mainBranch[i].onImpulseFinished;
        branches[i].setup();
    }
    for (int i = 0; i < mainBranch.size(); i++) {
        
    }
    for (int i = 0; i < branches.size(); i++) {
        branches[i].isLeft = (int)ofRandom(2);
    }
}