//
//  eyePairMode.cpp
//  EyeScene
//
//  Created by Zerc on 7/15/16.
//
//

#include "eyePairMode.hpp"
void eyePairMode::setup(){
    for (int i = 0; i < 2; i++) {
        eye eye;
        eye.setup(ofVec2f(100, 100), eyeSize * sf, eyeSize * sf);
        eye.setEyeColor(ofColor::lightSkyBlue);
        eyes.push_back(eye);
    }
    eyes[1].setSyncEye(&eyes[0]);

}
void eyePairMode::setupGui(){
    parameters.setName("eyePairParameters");
    parameters.add(eyeDistance.set("eyeDistance", 200, 10, 800));
    parameters.add(posOffsetY.set("posOffsetY", 200, -500, 500));
    parameters.add(posOffsetX.set("posOffsetX", 200, -500, 500));
    parameters.add(minScale.set("minScale", 0.5, 0.1, 7));
    parameters.add(maxScale.set("maxScale", 2, 0.1, 7));
    parameters.add(scaleSmooth.set("scaleSmooth", 0.9, 0.5, 0.99));
    parameters.add(energyRange.set("energyRange", 20, 5, 300));
    parameters.add(eyeSize.set("eyeSize", 200, 50, 300));
    parameters.add(smooth.set("smooth", 0.98, 0.5, 0.99));
    parameters.add(rewLineLength.set("rewLineLength", 100, 30, 2000));
    parameters.add(rewLineRadius.set("rewLineRadius", 100, 30, 500));
    parameters.add(rewTreshold.set("rewTreshold", 5, 0.5, 20));
    parameters.add(rewAmount.set("rewAmount", 20, 1, 100));
    eyeSize.addListener(this, &eyePairMode::triggerInit);
}
void eyePairMode::triggerInit(float &val){
    init();
}
void eyePairMode::init(){
    eyes.clear();
    for (int i = 0; i < 2; i++) {
        eye eye;
        eye.setup(ofVec2f(0, 0), eyeSize * sf, eyeSize * sf);
        eye.setEyeColor(ofColor::lightSkyBlue);
        eyes.push_back(eye);
    }
    eyes[1].setSyncEye(&eyes[0]);
}
void eyePairMode::fadeIn(){
    reward.clear();
    isFadeFinished = false;
    init();
    for(auto &e : eyes){
        e.open();
    }
}
void eyePairMode::clear(){
    bool isEnabled = false;
    bool isFadeFinished = false;
    bool isFading = false;
    init();
}
void eyePairMode::fadeOut(){
    for(auto &e : eyes){
        e.close();
    }
}
void eyePairMode::addScaleForce(){
    float diff = leftEnergy - rightEnergy;
    float mid = (scaleMax+scaleMin)/2;
    float sL = ofMap(diff, -energyRange, energyRange, scaleMin, scaleMax, true);
    float angle = ofMap(diff, -energyRange, energyRange, -40, 40, true);
    float s = smooth;

    if(fabsf(diff)<20){
        sL = (scaleMax+scaleMin)/2;
        angle = 0;
    }
    
    // smooth values
    scaleL = scaleL*s + (1-s)*sL;
    scaleR = (scaleMax+scaleMin)-scaleL;

    if(scaleL>mid){
        // left is bigger
        angleR = angleR * s + (1-s)*angle;
        float eyeLidScale = ofMap(scaleL, scaleMax, mid, 1, 0.2, true);
        eyes[1].getLids()->setTopLidPos(eyeLidScale);
        float pupilScale = ofMap(scaleL, mid, scaleMax, 1.0, 2.0);
        eyes[0].setPupulScale(pupilScale);
    }else{
        // right is bigger
        angleL = angleL*s + (1-s)*angle;
        float eyeLidScale = ofMap(scaleL, scaleMin, mid, 1, 0.2, true);
        eyes[0].getLids()->setTopLidPos(eyeLidScale);
        float pupilScale = ofMap(scaleL, mid, scaleMin, 1.0, 2.0);
        eyes[1].setPupulScale(pupilScale);
    }
    if(scaleL > mid*1.2 || scaleR > mid*1.2 ){
        isEyeBig = true;
    }else{
        isEyeBig = false;
    }
    eyes[0].setScale(scaleL);
    eyes[1].setScale(scaleR);
    eyes[0].setAngle(angleL);
    eyes[1].setAngle(angleR);
}

void eyePairMode::update(ofVec2f posL, ofVec2f posR){
    updateFadeCheck();
    eyes[0].update(posL + ofVec2f(posOffsetX * sf, posOffsetY * sf));//_pos-ofVec2f(eyeDistance * sf, posOffsetY * sf));
    eyes[1].update(posR + ofVec2f(posOffsetX * sf, posOffsetY * sf));//_pos+ofVec2f(eyeDistance * sf, -posOffsetY * sf));
//    addScaleForce();
    updateScale();
    if(isEnabled) updateReward();
}
void eyePairMode::updateReward(){
    reward.update();

    float s =  maxScale-(maxScale - minScale)/rewTreshold;
    
    for(auto &e : eyes){
        if(e.getScale() > s && ofGetFrameNum()%rewAmount == 0 ){
            reward.lineLength = rewLineLength * sf;
            reward.lineRadius = rewLineRadius * sf;
            reward.reward(e.getPos());
        }
    }
}
void eyePairMode::updateScale(){
    float sL = ofMap(leftEnergy, 0, 20, minScale, maxScale, true);
    float sR = ofMap(rightEnergy, 0, 20, minScale, maxScale, true);
    eyes[0].setScaleSmoothed(sL, scaleSmooth);
    eyes[1].setScaleSmoothed(sR, scaleSmooth);
//        e.setScale(s);

}
void eyePairMode::updateFadeCheck(){
    for(auto &eye: eyes){
        if(eye.isCloseFinished()){
            ofLog() << "fin";
            isFadeFinished = true;
        }
    }
}
void eyePairMode::setLookAt(ofVec2f _pos){
    for(auto &e: eyes){
        e.lookAt(_pos);
    }
}

void eyePairMode::draw(){
    ofSetColor(255, 255);
    reward.draw();
    for(auto &e: eyes){
        e.draw();
    }
    if (isEyeBig) {
        int count  = 20;
        ofVec2f pos;
        float radius;
        float opacity;
        if(scaleL>scaleR){
            pos = eyes[0].getPos();
            float mid = (scaleMax+scaleMin)/2;
            radius = ofMap(scaleL, mid*1.2, scaleMax, 100, 300);
            opacity = ofMap(scaleL, mid*1.2, mid*1.25, 0, 255, true);
        }else{
            pos = eyes[1].getPos();
            float mid = (scaleMax+scaleMin)/2;
            radius = ofMap(scaleR, mid*1.2, scaleMax, 100, 300);
            opacity = ofMap(scaleR, mid*1.2, mid*1.25, 0, 255, true);

        }
        for (int i = 0; i < count; i++) {
            ofNode root;
            ofNode p1;
            ofNode p2;
            root.setPosition(pos);
            p1.setParent(root);
            p2.setParent(root);
            p1.setPosition(radius+ofNoise((ofGetFrameNum()+i*20)/7.)*30, cos(ofGetFrameNum()/9.)*10, 0);
            p2.setPosition(radius+ofNoise((ofGetFrameNum()+i*102)/15.)*130, 0, 0);
            root.setOrientation(ofVec3f(0, 0, 360.0/count*i+ofGetFrameNum()/2.));
            ofSetColor(ofColor(255, opacity));
            ofDrawLine(p1.getGlobalPosition(), p2.getGlobalPosition());
        }
        
    }
    if(isHit){
        for (int i = 0; i < 5; i++) {
            float d = 10;
            ofSetColor(ofColor::yellow);
            
            ofVec2f r(ofRandom(-d, d), ofRandom(-d, d));
            ofVec2f r2(ofRandom(-d, d), ofRandom(-d, d));
            ofDrawLine(eyes[0].getEyeBalPos()+r, eyes[0].getLookAtPos()+r2);
            ofDrawLine(eyes[1].getEyeBalPos()+r, eyes[0].getLookAtPos()+r2);
            ofSetColor(ofColor::white, ofNoise(ofGetElapsedTimef()*3)*255);
            ofDrawCircle(eyes[0].getLookAtPos(), ofRandom(100));
        }
    }

}
