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
    // refract
    refract.allocate(ofGetWidth(), ofGetHeight());
    refract.setupParameters(ofGetWidth(), ofGetHeight());
    refract.parameters.setName("Refraction");
    
    // gui
    gui.setup("StencilWavesSettings");
    gui.add(amount.set("amount", 55, 10, 200));
    gui.add(strength.set("strength", 0.55, 0.001, 1));
    gui.add(restLength.set("restLength", 16.92, 0, 18));
    gui.add(invMass.set("invMass", 0.375, 0.1, 3));
    gui.add(force.set("force", 4, 0.1, 20));
    gui.add(refract.parameters);

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
    strokeMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    // waves
    addWave(ofGetHeight()-150);
    addWave(ofGetHeight()-100);
    
    // masks
    mask.allocate(ofGetWidth(), ofGetHeight());
    
    // colors
    peopleColor = ofColor::lavender;
    
    // images
    glowImg.load("glow.png");
    
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
    updateRefract();
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
    strokeMesh.clear();
    for (int i = 0; i < waves[0].polyline.getVertices().size(); i++) {
        ofVec2f p = waves[0].polyline.getVertices()[i];
        ofVec2f p2 = ofVec2f(p.x, ofGetHeight());
        ofVec3f dir = waves[0].polyline.getTangentAtIndex(i);
        float angle = atan2(dir.x, dir.y)*(180)/pi;
        
        ofColor col = ofColor::lightSkyBlue;
        ofColor cc = ofColor::darkBlue;
        col.setBrightness((int)ofMap(angle, 90, 120, 0, 255)%255);
        col.setHueAngle(ofMap(angle, 90, 120, 0, 360, true));
        
        mainWaveMesh.addVertex(p);
        mainWaveMesh.addColor(col);
        mainWaveMesh.addVertex(p2);
        mainWaveMesh.addColor(cc);
        
        ofNode node;
        ofNode child;
        child.setParent(node);

        child.setPosition(ofVec3f(0, ofMap(angle, 90, 120, 0, 20)+cos(ofGetFrameNum()/20.0)*10, 0));

        node.setPosition(p);
        ofQuaternion q = ofQuaternion(0, ofVec3f(1, 0, 0), 0, ofVec3f(0, 1, 0), angle, ofVec3f(0, 0, 1));
        node.setOrientation(q);

        strokeMesh.addVertex(node.getGlobalPosition());
        strokeMesh.addVertex(child.getGlobalPosition());
    }
}
void StencilWaves::updateFbos(){
    // draw people
    peopleFbo.begin();
    ofClear(0, 0);
//    ofSetColor(ofColor::white);
//    ofDrawRectangle(ofGetWindowRect());
    for(auto &p: contours){
        p.draw();
    }
    peopleFbo.end();
    
    // draw mainWave
    mainWaveFbo.begin();
    ofClear(0, 0);
    mainWaveMesh.draw();
    mainWaveFbo.end();
}
void StencilWaves::updateMasks(){
    
    mask.begin(1); // masked img
    ofClear(0, 0);
    ofSetColor(ofColor::white);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    mainWaveMesh.draw();
    ofColor col = peopleColor;
    col.setBrightness(120);
    for(auto &p: contours){
        p.setFillColor(col);
        p.draw();
    }
    ofDisableBlendMode();
    mask.end(1);
    
    mask.begin(0); // masked img
    ofClear(0, 0);
    ofSetColor(ofColor::red);
    drawWaveMesh();
    mask.end(0);
    
    mask.update();
}
void StencilWaves::updateRefract(){
    refract.setTexture(mask.getTexture(), 0);
//    refract.setTexture(peopleFbo.getTexture(), 0);
    refract.setTexture(mainWaveFbo.getTexture(), 1);
    refract.update();
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
//    drawBg();
    for(auto &p: contours){
        p.setFillColor(peopleColor);
        p.draw();
    }
//    mask.draw();
//    waves[0].polyline.draw();
    refract.draw(0, 0);
    strokeMesh.draw();
    drawGlow();
    gui.draw();
    
}
void StencilWaves::drawWaveMesh(){
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    for (int i = 0; i < waves[0].polyline.getVertices().size(); i++) {
        ofVec2f p = waves[0].polyline.getVertices()[i];
        ofVec2f p2 = ofVec2f(p.x, ofGetHeight());
        
        mesh.addVertex(p);
        mesh.addVertex(p2);
    }
    mesh.draw();


}
void StencilWaves::drawGlow(){
    for (int i = 0; i < waves[0].polyline.getVertices().size(); i++) {
        ofVec2f p = waves[0].polyline.getVertices()[i];
        float dist  = 100;
        float r = 0;
        for(auto &t: IM->targets ){
            if(t.pos.distance(p)<dist){
                r = ofMap(t.pos.distance(p), 0, dist, dist, 0);
            }
        }
        ofSetColor(255);
        r *= 3;
//        ofDrawCircle(p-ofVec2f(r, r), r*2);
        glowImg.draw(p-ofVec2f(r, r), r*2, r*2);
    }
}
void StencilWaves::drawBg(){
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    int count = 5;
    for (int i = 0; i < count; i++) {
        float x1 = ofGetWidth()/count*i;
        float y1 = 0;
        float y2 = ofGetHeight();
        mesh.addVertex(ofVec2f(x1, y1));
        mesh.addColor(ofColor::lightBlue);
        mesh.addVertex(ofVec2f(x1, y2));
        mesh.addColor(ofColor::black);
    }
    mesh.draw();
}
