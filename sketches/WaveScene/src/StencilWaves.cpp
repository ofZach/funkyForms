//
//  StencilWaves.cpp
//  WaveScene
//
//  Created by Zerc on 7/29/16.
//
//

#include "StencilWaves.hpp"
// -------------- setup
void StencilWaves::setup(){
    // gui
    gui.setup("StencilWavesSettings");
    gui.add(amount.set("amount", 55, 10, 200));
    gui.add(strength.set("strength", 0.55, 0.001, 1));
    gui.add(restLength.set("restLength", 16.92, 0, 18));
    gui.add(invMass.set("invMass", 0.375, 0.1, 3));
    gui.add(force.set("force", 4, 0.1, 20));

    force.addListener(this, &StencilWaves::reload);
    restLength.addListener(this, &StencilWaves::reload);
    strength.addListener(this, &StencilWaves::reload);
    invMass.addListener(this, &StencilWaves::reload);

    gui.loadFromFile("settings.xml");
    
    // fbo
    peopleFbo.allocate(ofGetWidth(), ofGetHeight());
    peopleFbo.begin(); ofClear(0, 0); peopleFbo.end();
    mainWaveFbo.allocate(ofGetWidth(), ofGetHeight());
    mainWaveFbo.begin(); ofClear(0, 0); mainWaveFbo.end();
    
    // meshes
    mainWaveMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    // waves
    addWave(ofGetHeight()-150);
    addWave(ofGetHeight()-100);
    
    // masks
    mask.allocate(ofGetWidth(), ofGetHeight());
    
    // refract
    refract.allocate(ofGetWidth(), ofGetHeight());
    refract.setupParameters(ofGetWidth(), ofGetHeight());
    refract.parameters.setName("Refraction");
    
}
void StencilWaves::reload(float &v){
    waves.clear();
    addWave(ofGetHeight()-150);
    addWave(ofGetHeight()-100);
}
void StencilWaves::addWave(int y){
    class wave wave;
    wave.restLength = restLength;
    wave.strength = strength;
    wave.invMass = invMass;
    wave.amount = amount;
    wave.force = force;
    wave.setup(y, ofGetWidth());
    waves.push_back(wave);
}
// -------------- update
void StencilWaves::update(){
    updateContours();
    updateWaveParameters();
    updateWaves();
    updateMeshes();
    updateFbos();
    updateMasks();
}
void StencilWaves::updateWaves(){
    for(auto &w: waves){
        w.update(IM->targets);
    }
}
void StencilWaves::updateWaveParameters(){
    for(auto &wave: waves){
        wave.restLength = restLength;
        wave.strength = strength;
        wave.invMass = invMass;
        wave.amount = amount;
        wave.force = force;
    }
}
void StencilWaves::updateMeshes(){
    mainWaveMesh.clear();
    for (int i = 0; i < waves[0].polyline.getVertices().size(); i++) {
        ofVec2f p = waves[0].polyline.getVertices()[i];
        ofVec2f p2 = ofVec2f(p.x, ofGetHeight());
        ofVec3f dir = waves[0].polyline.getTangentAtIndex(i);
        float angle = atan2(dir.x, dir.y)*(180)/pi;
        
        ofColor col = ofColor::red;
        ofColor cc = ofColor::black;
        col.setBrightness(ofMap(angle, 90, 120, 0, 255));
        
        mainWaveMesh.addVertex(p);
        mainWaveMesh.addColor(col);
        mainWaveMesh.addVertex(p2);
        mainWaveMesh.addColor(col);
    }
}
void StencilWaves::updateFbos(){
    // draw people
    peopleFbo.begin();
    ofClear(0, 0);
    ofSetColor(ofColor::white);
    ofDrawRectangle(ofGetWindowRect());
    for(auto &p: contours){
        p.draw();
    }
    peopleFbo.end();
    
    // draw mainWave
    mainWaveFbo.begin();
    mainWaveMesh.draw();
    mainWaveFbo.end();
}
void StencilWaves::updateMasks(){
    
    mask.begin(1); // masked img
    ofClear(0, 0);
    ofSetColor(ofColor::white);
    ofDrawRectangle(ofGetWindowRect());
    for(auto &p: contours){
        p.setFillColor(ofColor::black);
        p.draw();
    }
    mask.end(1);
    
    mask.setTexture(mainWaveFbo.getTexture(), 0); // mask
    
    mask.update();
}
void StencilWaves::updateRefract(){
}
void StencilWaves::updateContours(){
    contours.clear();
    
    for (int i = 0; i < IM->getContourFinder()->getPolylines().size(); i++) {
        ofPolyline &l = IM->getContourFinder()->getPolyline(i);
        ofPath path;
        int res = ofMap(l.getPerimeter(), 0, 9, 0, 1);
        for (float i = 0; i < 1.; i += 1.0/res) {
            path.lineTo(l.getPointAtPercent(i));
        }
        path.setFillColor(ofColor::white);
        path.translate(IM->getPos());
        contours.push_back(path);
    }
}
// -------------- draw
void StencilWaves::draw(){
    for(auto &p: contours){
        p.setFillColor(ofColor::white);
        p.draw();
    }
    mask.draw();
    gui.draw();
}
