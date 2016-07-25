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
    bottomW_animator.setup(0, bottomWMax);
    m_topH_animator.setup(0, m_topHMax);
}
void Plant::updateParameters(){
    bottomW = init_bottomW * scale;
    bottomH = init_bottomH * scale;
    topW = init_topW * scale;
    topH = init_topH * scale;
    radius = init_radius * scale;
    
    m_bottomW = init_m_bottomW * scale;
    m_bottomH = init_m_bottomH * scale;
    m_topW = init_m_topW * scale;
    m_topH = init_m_topH * scale;
    m_radius = init_m_radius * scale;
}
void Plant::updateSpike(){
    isSpike ? spikePct+=0.1 : spikePct-=0.1;
    if(spikePct<0){isSpikeFinished = true;}
    spikePct = ofClamp(spikePct, 0, 1);
    spikeLength = ofInterpolateCosine(0, 40, spikePct);
}
void Plant::update(){
    
    updateParameters();
    updateSpike();
    
    // animate side branches
    if(velocity.x>0.02){
        bottomW_animator.in();
    }
    if(velocity.x<-0.02){
        bottomW_animator.out();
    }
    bottomW_animator.setSpeed(0.005);
    
    // animate main branch
    if(velocity.y>0.02){
        m_topH_animator.out();
    }
    if(velocity.y<-0.02){
        m_topH_animator.in();
    }
    m_topH_animator.setSpeed(0.005);

    // color grow
    icolor.update();
    if(!icolor.getGrowDone()) isSpike = false;
    
    
    // build plant
    for (int i = 0; i < mainBranch.size(); i++) {
        branchSettings s = mainBSettings(i);
        s.pos = pos;
        
        if(i>0){
            branchSettings b;
            b.radius = radius/(i+1);
        
            bottomW_animator.setPctOffset(2.2*randomNums[i]);
            float top_wMin = 10;
            float top_wVel = velocity.x;
            float top_w = topW + bottomW_animator.getValue() * scale; //
            float top_h = topH;
            float bottom_w = bottomW+bottomW_animator.getValue();
            float bottom_h = bottomH;
            
            ofRectangle *r5 = &mainBranch[i-1].rect5;
            ofRectangle *r6 = &mainBranch[i-1].rect6;
            
            if (mainBranch[i].isLeft) {
                b.leftRect.set(bottom_w, bottom_h);
                b.topRect.set(top_w, top_h);
                s.pos = r5->getTopRight();
                branches[i-1].isLeft = false;
                b.pos = r5->getCenter() ; //+ ofVec2f(0, r5->getHeight()/(i+1));
            }else{
                bottom_w = bottomW+ofMap(bottomW_animator.getValue(), 0, bottomWMax, bottomWMax, 0);
                topW = topW+ofMap(bottomW_animator.getValue(), 0, bottomWMax, bottomWMax, 0)*scale;
                b.leftRect.set(bottom_w, bottom_h);
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
    float bottom_w = m_bottomW/(i+1);
    float bottom_h = m_bottomH;
    float top_w = m_topW;
    float top_h = m_topH * randomNums[i] * scale + m_topH_animator.getValue();
    
    if (mainBranch[i].isLeft) {
        s.leftRect.set(bottom_w, bottom_h);
        s.topRect.set(top_w, top_h);
    }else{
//        bottom_w = left_wMin - min( left_wVel*1.0, left_wMin*1.0 );
        s.leftRect.set(bottom_w, bottom_h);
        s.topRect.set(top_w, top_h);
    }
    s.radius = m_radius;
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
//        b.drawDebug();
        b.draw();
    }
    for(auto b: mainBranch){
        b.draw();
//        b.drawDebug();
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
    randomNums.clear();
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
        randomNums.push_back(ofRandom(1));
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