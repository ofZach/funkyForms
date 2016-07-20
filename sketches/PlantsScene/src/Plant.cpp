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
    for(auto &i: randomNums){
        i = ofRandom(1);
    }
}
void Plant::updateSpike(){
    isSpike ? spikePct+=0.1 : spikePct-=0.1;
    if(spikePct<0){isSpikeFinished = true;}
    spikePct = ofClamp(spikePct, 0, 1);
    spikeLength = ofInterpolateCosine(0, 40, spikePct);
}
void Plant::update(){
    updateSpike();
    int i = 0;
    int limit = 3;
    //    if (velocity.x < -limit || velocity.x > limit ) {
    //        if(timer>10){
    //            timer = 0;
    //            impulse();
    //        }
    //    }
    timer++;
    icolor.update();
    if(!icolor.getGrowDone()) isSpike = false;
    for (int i = 0; i < mainBranch.size(); i++) {
        branchSettings s = mainBSettings(i);
        s.pos = pos;
        
        if(i>0){
            branchSettings b;
            b.radius = (30+ofNoise(ofGetElapsedTimef()+i*velocity.x*20)*30)*scale;
            
            float top_wMin = 60/(i+1)*scale ;
            float top_wVel = (velocity.x*(100.0/(i+1))*40 +ofNoise(ofGetElapsedTimef()+i*200)*30)*scale;
            float top_w = (top_wMin + max( top_wVel*3.0, top_wMin/5.0))*scale; //
            float top_h = velocity.y*700/(i+1)*scale;
            float left_w = velocity.x*100/(i+1)*scale;
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
            branches[i-1].setColorOffset(i+1);
            branches[i-1].update(b.pos, b.leftRect, b.topRect, b.radius, icolor);
        }
        mainBranch[i].setColorOffset(i+1);
        mainBranch[i].update(s.pos, s.leftRect, s.topRect, s.radius, icolor);
        
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
    float left_wMin = 100/(i+1)*scale-velocity.x*20;
    float left_wVel = velocity.x*(20.0/((i%2)+1))*scale*40;
    float left_w = velocity.x;
    float left_h = 30/(i+1)*scale;
    float top_w = 30/(i+1)*scale;
    float top_h = velocity.y*800+i*scale;
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
    icolor.grow();
}
void Plant::makeSpikes(ofPolyline &line, int counter, bool isRight){
    int index = 5;
    int i = 0;
    while (index < line.getVertices().size()) {
        ofVec2f dir = line.getTangentAtIndex(index);
        ofVec2f p1 = line.getPointAtIndexInterpolated(index);
        float length = spikeLength*ofMap(cos(counter*100.0+index*100.0), -1, 1, 0, 1)*scale;
        ofVec2f p2 = isRight? dir.getPerpendicular()*length+p1 : dir.getPerpendicular().rotate(180)*length+p1;
        ofVec2f p3 = dir*2 + p1;
        ofVec2f p4 = p1 - dir*2;
        ofDrawTriangle(p2, p3, p4);
        index+= ofMap(randomNums[i], 0, 1, 6, 20);
        i++;
    }
}
void Plant::draw(){
    for(auto b: branches){
        b.draw();
    }
    for(auto b: mainBranch){
        b.draw();
    }
    if(!isSpikeFinished){
        for (int i = 0; i < mainBranch.size(); i++) {
            ofSetColor(ofColor::white);
            if(mainBranch[i].isLeft){
                makeSpikes(mainBranch[i].stroke1, i, true);
                makeSpikes(mainBranch[i].stroke2, i, false);
            }else{
                makeSpikes(mainBranch[i].stroke1, i, false);
                makeSpikes(mainBranch[i].stroke2, i, true);
            }
            if(i<mainBranch.size()-1){
                if(branches[i].isLeft){
                    makeSpikes(branches[i].stroke1, i, true);
                    makeSpikes(branches[i].stroke2, i, false);
                }else{
                    makeSpikes(branches[i].stroke1, i, false);
                    makeSpikes(branches[i].stroke2, i, true);
                }
            }
        }
    }
}
void Plant::randomize(){
    mainBranch.clear();
    branches.clear();
    mainBranchCount = (int)ofRandom(3, 7);
    
    for (int i = 0; i < mainBranchCount; i++) {
        Branch Branch;
        Branch.color = ofColor(0, 0);
        Branch.isLeft = (int)ofRandom(2);
        Branch.isCap = (int)ofRandom(2);
        Branch.isTopRound = (int)ofRandom(2);
        mainBranch.push_back(Branch);
        mainBranch[i].setup();
        colorIndexTotal += mainBranch[i].resolution;
    }
    for (int i = 0; i < mainBranchCount-1; i++) {
        Branch Branch;
        Branch.isCap = (int)ofRandom(2);
        Branch.color = ofColor(0, 0);
        branches.push_back(Branch);
        branches[i].setup();
        colorIndexTotal += branches[i].resolution;
    }
    for (int i = 0; i < branches.size(); i++) {
        branches[i].isLeft = (int)ofRandom(2);
    }
    icolor.setup(colorIndexTotal, ofColor(0, 0));
    icolor.grow();
}