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
    int i = 0;
    int limit = 3;
    //    if (velocity.x < -limit || velocity.x > limit ) {
    //        if(timer>10){
    //            timer = 0;
    //            impulse();
    //        }
    //    }
    timer++;
    for (int i = 0; i < mainBranch.size(); i++) {
        branchSettings s = mainBSettings(i);
        s.pos = pos;
        
        if(i>0){
            branchSettings b;
            b.radius = (30+ofNoise(ofGetElapsedTimef()+i*100)*30)*scale;
            
            float top_wMin = 60/(i+1)*scale ;
            float top_wVel = (velocity.x*(20.0/(i+1)) +ofNoise(ofGetElapsedTimef()+i*20)*30)*scale;
            float top_w = (top_wMin + max( top_wVel*1.0, top_wMin/5.0))*scale; //
            float top_h = 100/(i+1)*scale;
            float left_w = 100/(i+1)*scale;
            float left_h = 30/(i+1)*scale;
            
            ofRectangle *r5 = &mainBranch[i-1].rect5;
            ofRectangle *r6 = &mainBranch[i-1].rect6;
            
            if (mainBranch[i].isLeft) {
                b.leftRect.set(left_w, left_h);
                b.topRect.set(top_w, top_h);
                s.pos = r5->getTopRight();
                branches[i-1].isLeft = false;
                b.pos = r5->getCenter() ; //+ ofVec2f(0, r5->getHeight()/(i+1));
            }else{
                float top_w = top_wMin - min( top_wVel*1.0, top_wMin/5.0); //+ofNoise(ofGetElapsedTimef()+i*20)*30
                
                b.leftRect.set(left_w, left_h);
                b.topRect.set(top_w, top_h);
                s.pos = r5->getTopLeft();
                branches[i-1].isLeft  = true;
                b.pos = r5->getCenter(); //+ ofVec2f(0, r5->getHeight()/(i+1));
            }
            
            branches[i-1].update(b.pos, b.leftRect, b.topRect, b.radius);
        }
        
        mainBranch[i].update(s.pos, s.leftRect, s.topRect, s.radius);
        
        ofSetColor(ofColor::red);
    }
   
}
void Plant::smooth(ofVec2f *vec , ofVec2f newVec, float _speed){
    ofVec2f smoothVec(_speed, _speed);
    ofVec2f oneVec(1, 1);
    vec->set(*vec*smoothVec + newVec*(oneVec-smoothVec));
}
Plant::branchSettings Plant::mainBSettings(int i){
    branchSettings s;
    float left_wMin = 100/(i+1)*scale;
    float left_wVel = velocity.x*(20.0/(i+1))*scale;
    float left_w = left_wMin + min( left_wVel*1.0, left_wMin*1.0 )*scale;
    float left_h = 30/(i+1)*scale;
    float top_w = 30/(i+1)*scale;
    float top_h = (100/(i+1)-velocity.y*20)*scale;
    if (mainBranch[i].isLeft) {
        s.leftRect.set(left_w, left_h);
        s.topRect.set(top_w, top_h);
    }else{
        left_w = left_wMin - min( left_wVel*1.0, left_wMin*1.0 );
        s.leftRect.set(left_w, left_h);
        s.topRect.set(top_w, top_h);
    }
    s.radius = (30+ofNoise(ofGetElapsedTimef()+i*100)*30)*scale;
    s.isLeft = true;
    return s;
}
void Plant::impulse(int colNum){
    mainBranch[0].impulse(colors[(int)ofRandom(4)]);
}
void Plant::draw(){
    for(auto b: branches){
        b.draw();
    }
    for(auto b: mainBranch){
        b.draw();
    }
}
void Plant::randomize(){
    mainBranch.clear();
    branches.clear();
    mainBranchCount = (int)ofRandom(3, 6);
    
    for (int i = 0; i < mainBranchCount; i++) {
        Branch *b = new Branch();
        b->color = ofColor::lightGreen;
        b->isLeft = (int)ofRandom(2);
        b->isCap = (int)ofRandom(2);
        b->isTopRound = (int)ofRandom(2);
        mainBranch.push_back(*b);
        mainBranch[i].setup();

    }
    for (int i = 0; i < mainBranchCount-1; i++) {
        Branch *b = new Branch();
        b->isCap = (int)ofRandom(2);
        b->color = ofColor::lightGreen;
        branches.push_back(*b);
        branches[i].setup();
    }
    for (int i = 0; i < mainBranchCount; i++) {
        if(i < mainBranchCount-1){
            mainBranch[i].setNextBranch( &mainBranch[i+1] );
            mainBranch[i].setNextBranch( &branches[i] );
        }
    }
    for (int i = 0; i < branches.size(); i++) {
        branches[i].isLeft = (int)ofRandom(2);
    }
}