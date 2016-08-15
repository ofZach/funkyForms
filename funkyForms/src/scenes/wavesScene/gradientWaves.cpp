//
//  waves.cpp
//  Wave
//
//  Created by Zerc on 6/21/16.
//
//

#include "gradientWaves.hpp"
void gradientWaves::setup(int w, int h){
    screenW = w;
    screenH = h;
    
    float v = 0;
    reload(v);
    
    // shader
//    bumpmap.allocate(screenW, screenH);
}
void gradientWaves::setupGui(){
    bumpmap.setupParameters();
    parameters.setName("gradientWavesParameters");
    parameters.add(waveCount.set("waveCount", 5, 1, 20));
    parameters.add(waveDistance.set("waveDistance", 10, 5, 200));
    parameters.add(amount.set("amount", 55, 10, 200));
    parameters.add(strength.set("strength", 0.55, 0.001, 1));
    parameters.add(restLength.set("restLength", 16.92, 0, 18));
    parameters.add(invMass.set("invMass", 0.375, 0.1, 3));
    parameters.add(force.set("force", 4, 0.1, 20));
    parameters.add(shadowRadius.set("shadowRadius", 100, 0, 500));
    parameters.add(energyHighlightSize.set("energyHighlightSize", 100, 0, 500));
    parameters.add(shadowOpacity.set("shadowOpacity", 100, 0, 255));
    parameters.add(bumpmap.parameters);
    
    waveCount.addListener(this, &gradientWaves::reloadInt);
    amount.addListener(this, &gradientWaves::reloadInt);
    
    waveDistance.addListener(this, &gradientWaves::reload);
    force.addListener(this, &gradientWaves::reload);
    restLength.addListener(this, &gradientWaves::reload);
    strength.addListener(this, &gradientWaves::reload);
    invMass.addListener(this, &gradientWaves::reload);
}
void gradientWaves::reloadInt(int &value){
    float val = 0;
    reload(val);
}
void gradientWaves::reload(float &value){
    waves.clear();
    for (int i = 0; i < waveCount; i++) {
        addWave(waveDistance*i+screenH-waveDistance*waveCount, swatch[i%5], swatchBase[i%5]);
    }
}
void gradientWaves::addWave( int ypos, ofFloatColor col, ofColor baseCol){
    FishWave wave;
    
    wave.restLength = restLength;
    wave.strength = strength;
    wave.invMass = invMass;
    wave.amount = amount;
    wave.force = force;
    wave.color = col;
    wave.baseColor = baseCol;
    wave.setup(ypos, screenW);
    wave.setupFishWave();
    waves.push_back(wave);
}
void gradientWaves::addPointsToMesh(ofMesh *m, ofNode l, ofNode r, int i){
    ofFloatColor col = ofColor::white;
    
    float mix = cos(i*3);
    ofFloatColor temp = ofColor::lightGreen;
    ofFloatColor temp2 = ofColor::darkMagenta;
    
    m->addVertex(l.getGlobalPosition());
    m->addColor(col);
    m->addVertex(r.getGlobalPosition());
    
    m->addColor(col);
}
// -------------- update
void gradientWaves::update(){
    updateWaveParameters();
    for (int i = 0; i < waves.size(); i++) {
        waves[i].update();
        waves[i].updateFishWave();
    }
}
void gradientWaves::updateWaveParameters(){
    for(auto &w: waves){
        w.shadowRadius = shadowRadius;
        w.shadowOpacity = shadowOpacity;
        w.energyHighlightSize = energyHighlightSize;
    }

}
void gradientWaves::updateRipples(){
    bumpmap.begin();
    ofPushMatrix();
//    ofTranslate(IM->pos);
//    for (int i = 0; i < IM->getContourFinder()->getPolylines().size(); i++) {
//        ofPolyline &l = IM->getContourFinder()->getPolyline(i);
//        ofPath path;
//        int res = ofMap(l.getPerimeter(), 0, 1900, 1, 200);
//        for (float i = 0; i < 1.; i += 1.0/res) {
//            path.lineTo(l.getPointAtPercent(i));
//        }
//        //        path.setFilled(false);
//        path.setStrokeColor(ofColor::white);
//        path.setStrokeWidth(5);
//        path.draw();
//    }
    ofPopMatrix();
    bumpmap.end();
    bumpmap.update();
}
// -------------- draw
void gradientWaves::draw(){
    for (int i = 0; i < waves.size(); i++) {
        waves[i].draw();
    }
//    drawBox2d();
    ofSetColor(255, 255);
}
void gradientWaves::drawSpikes(){
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
//            for(auto &t: IM->targets){
//                if(p.distance(t.pos)<30){
//                    vel = t.vel.y;
//                }
//            }
            ofSetColor(255, 255);
            ofDrawCircle(ofVec2f(p.x, p.y+vel*10), ofMap(p.y, 0, screenH, 10, 1, true));
        }
    }
}
void gradientWaves::drawCircles(ofPolyline *line, int i){
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
void gradientWaves::drawRipples(){
    bumpmap.draw();
}




