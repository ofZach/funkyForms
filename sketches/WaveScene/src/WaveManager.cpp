//
//  waves.cpp
//  Wave
//
//  Created by Zerc on 6/21/16.
//
//

#include "WaveManager.hpp"
void WaveManager::setup(){
    int pos = ofGetHeight()-150;
    ofFloatColor colors[5] = {
        ofColor(190,44,119),
        ofColor(30,210,255),
        ofColor(184,241,253),
        ofColor(223,195,68),
        ofColor(42,42,42)
    };
    gui.setup("waveSettings");
    gui.add(amount.set("amount", 55, 10, 200));
    gui.add(strength.set("strength", 0.55, 0.001, 1));
    gui.add(restLength.set("restLength", 16.92, 0, 18));
    gui.add(invMass.set("invMass", 0.375, 0.1, 3));
    
    restLength.addListener(this, &WaveManager::reload);
    strength.addListener(this, &WaveManager::reload);
    invMass.addListener(this, &WaveManager::reload);
//    amount.addListener(this, &WaveManager::reload);

    gui.loadFromFile("settings.xml");

    for (int i = 0; i < 4; i++) {
        pos += 10*i;
        addWave(pos, colors[i]);
    }
}
void WaveManager::reload(float &value){
    waves.clear();
    int pos = ofGetHeight()-150;
    ofFloatColor colors[4] = {
        ofColor::cadetBlue,
        ofColor::red,
        ofColor::goldenRod,
        ofColor::yellow
    };
    for (int i = 0; i < 5; i++) {
        pos += 10*i;
        addWave(pos, colors[i]);
    }
}
void WaveManager::addWave( int ypos, ofFloatColor col){
    wave wave;
    wave.restLength = restLength;
    wave.strength = strength;
    wave.invMass = invMass;
    wave.amount = amount;
    wave.setup(ypos, col, ofGetWidth());
    waves.push_back(wave);
}
void WaveManager::update(int x, int y){
    for (int i = 0; i < waves.size(); i++) {
        waves[i].update(IM->targets);
    }
}
void WaveManager::drawSpikes(){
    for (int i = 0; i < waves.size(); i++) {
        ofPolyline *line = &waves[i].polyline;
        float index  = 5.0;
        for (int j = 0; j < 50; j++) {
            index = ofMap(ofNoise(ofGetElapsedTimef()/j + j*100.0 + i*10.0), 0.2, 0.8, 0, waves[0].amount );
            ofVec2f p = line->getPointAtIndexInterpolated(index);
            ofVec3f dir = line->getTangentAtIndex(index);
            float angle = atan2(dir.x, dir.y)*(180)/pi;
            ofSetColor(ofColor::white);
            ofSetLineWidth(ofNoise(index/20.0)*5);
            ofNode node;
            ofNode child;
            child.setParent(node);
            child.setPosition(-ofNoise(index/2.)*20, 0, 0);
            
            node.setPosition(p);
            ofQuaternion q = ofQuaternion(0, ofVec3f(1, 0, 0), 0, ofVec3f(0, 1, 0), angle, ofVec3f(0, 0, 1));
            node.setOrientation(q);
            float vel = 0;
            for(auto &t: IM->targets){
                if(p.distance(t.pos)<30){
                    vel = t.vel.y;
                }
            }
//            ofDrawLine(node.getGlobalPosition(), child.getGlobalPosition());
            ofSetColor(255, 255);
            ofDrawCircle(ofVec2f(p.x, p.y+vel*10), ofMap(p.y, 0, ofGetHeight(), 10, 1, true));
            
            //        ofDrawCircle(child.getGlobalPosition(), ofNoise(index/20.0)*10);
            
        }
    }
}
void WaveManager::drawCircles(ofPolyline *line, int i){
    int index  = 5;
    while (index < waves[0].amount) {
        ofVec2f p = line->getPointAtIndexInterpolated(index);
        ofVec3f dir = line->getTangentAtIndex(index);
        float angle = atan2(dir.x, dir.y)*(180)/pi;
        ofNode node;
        ofNode child;
        child.setParent(node);
        child.setPosition(-ofNoise(index/2.)*300, 0, 0);
        
        node.setPosition(p);
        ofQuaternion q = ofQuaternion(0, ofVec3f(1, 0, 0), 0, ofVec3f(0, 1, 0), angle, ofVec3f(0, 0, 1));
        node.setOrientation(q);
        
        ofSetLineWidth(ofNoise(index/20.0)*5);
        ofSetColor(ofColor::gray);
        ofVec2f pos = node.getGlobalPosition()+ofVec2f(0, cos(ofGetElapsedTimef()*i)*40+100);
        float size = ofNoise(index/2.)*100;
        if(i!=waves.size()-1)
            ofDrawCircle(pos, size);
        
        index += ofNoise((i*index)/20.01)*60;
    }
}
void WaveManager::draw(){
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (int i = 0; i < waves.size(); i++) {
        
        waves[i].draw();
//        drawCircles(&waves[i].polyline, i);
    }
//    ofDisableBlendMode();
    gui.draw();
}
void WaveManager::addPointsToMesh(ofMesh *m, ofNode l, ofNode r, int i){
    ofFloatColor col = ofColor::white;
    
    float mix = cos(i*3);
    ofFloatColor temp = ofColor::lightGreen;
    ofFloatColor temp2 = ofColor::darkMagenta;
    
    m->addVertex(l.getGlobalPosition());
    m->addColor(col);
    m->addVertex(r.getGlobalPosition());
    
    m->addColor(col);
}