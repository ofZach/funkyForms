//
//  StencilWaves.cpp
//  WaveScene
//
//  Created by Zerc on 7/29/16.
//
//

#include "StencilWaves.hpp"
// -------------- setup
void StencilWaves::setup(int w, int h){
    screenW = w;
    screenH = h;
    
    // refract
    refract.allocate(screenW*screenScale, screenH*screenScale);
    refract.setup(screenW*screenScale, screenH*screenScale);
    
    // fbo
    peopleFbo.allocate(screenW*screenScale, screenH*screenScale);
    peopleFbo.begin(); ofClear(0, 0); peopleFbo.end();
    mainWaveFbo.allocate(screenW*screenScale, screenH*screenScale);
    mainWaveFbo.begin(); ofClear(0, 0); mainWaveFbo.end();
    
    // meshes
    mainWaveMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    strokeMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    // waves
    float v;
    reload(v);
    
    // masks
    mask.allocate(screenW*screenScale, screenH*screenScale);
    
    // colors
    peopleColor = ofColor::lavender;
    
    // images
    glowImg.load("assets/glow.png");
}
void StencilWaves::setupGui(){
    refract.setupParameters();
    parameters.setName("stencilWavesParameters");
    parameters.add(screenScale.set("screenScale", 1.0, 0.05, 1.0));
    parameters.add(amount.set("amount", 55, 10, 200));
    parameters.add(strength.set("strength", 0.55, 0.001, 1));
    parameters.add(restLength.set("restLength", 16.92, 0, 18));
    parameters.add(invMass.set("invMass", 0.375, 0.1, 3));
    parameters.add(force.set("force", 4, 0.1, 20));
    parameters.add(glowRadius.set("glowRadius", 200, 10, 500));
    parameters.add(glowOpacity.set("glowOpacity", 120, 0, 255));
    parameters.add(peopleOpacity.set("peopleOpacity", 120, 0, 255));
    parameters.add(refract.parameters);
    
    force.addListener(this, &StencilWaves::reload);
    restLength.addListener(this, &StencilWaves::reload);
    strength.addListener(this, &StencilWaves::reload);
    invMass.addListener(this, &StencilWaves::reload);
}
void StencilWaves::reload(float &v){
    waves.clear();
    addWave(screenH*screenScale-150);
    addWave(screenH*screenScale-100);
}
void StencilWaves::addWave(int y){
    class wave wave;
    wave.restLength = restLength;
    wave.strength = strength;
    wave.invMass = invMass;
    wave.amount = amount;
    wave.force = force;
    wave.setup(y, screenW*screenScale);
    waves.push_back(wave);
}
// -------------- update
void StencilWaves::update(){
    updateWaveParameters();
    updateWaves();
    updateMeshes();
    updateFbos();
    updateMasks();
    updateRefract();
}
void StencilWaves::updateWaves(){
    for(auto &w: waves){
        w.update();
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
    ofFill();
    mainWaveMesh.clear();
    strokeMesh.clear();
    for (int i = 0; i < waves[0].polyline.getVertices().size(); i++) {
        ofVec2f p = waves[0].polyline.getVertices()[i];
        ofVec2f p2 = ofVec2f(p.x, screenH*screenScale);
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
    ofFill();
    peopleFbo.begin();
    ofClear(0, 0);
    for(auto &p: paths){
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
    ofFill();
    
    mask.begin(1); // img to be masked
    ofClear(0, 0);
    for(auto &p: paths){
        p.setFillColor(ofColor(peopleColor, peopleOpacity));
        p.draw();
    }
    mask.end(1);
    
    mask.begin(0); // mask
    ofClear(0, 0);
    ofSetColor(ofColor::white);
    drawPlainWaveMesh();
    mask.end(0);
    
    mask.update();
}
void StencilWaves::updateRefract(){
    refract.setTexture(mask.getTexture(), 0);
//    refract.setTexture(peopleFbo.getTexture(), 0);
    refract.setTexture(mainWaveFbo.getTexture(), 1);
    refract.update();
}
void StencilWaves::addPath(ofPolyline &contour){
    ofPath path;
    for (auto &p : contour) {
        path.lineTo(p);
    }
    path.setFillColor(ofColor::white);
    paths.push_back(path);
}
// -------------- draw
void StencilWaves::draw(){
    ofFill();
    mainWaveMesh.draw();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    refract.draw(0, 0);
    drawGlow();
    ofDisableBlendMode();
    drawUpperPeople();
    paths.clear();
}
void StencilWaves::drawUpperPeople(){
    for(auto &p: paths){
        p.draw();
    }
}
void StencilWaves::drawPlainWaveMesh(){
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    for (int i = 0; i < waves[0].polyline.getVertices().size(); i++) {
        ofVec2f p = waves[0].polyline.getVertices()[i];
        ofVec2f p2 = ofVec2f(p.x, screenH*screenScale);
        
        mesh.addVertex(p);
        mesh.addVertex(p2);
    }
    mesh.draw();
}
void StencilWaves::drawGlow(){
    for (int i = 0; i < waves[0].polyline.getVertices().size(); i++) {
        ofVec2f p = waves[0].polyline.getVertices()[i];
        float r = 0;
//        for(auto &id : cvData->idsThisFrame){
//            ofVec2f pos = cvData->getCentoidAt(id);
//            if(pos.distance(p)<glowRadius){
//                r = ofMap(pos.distance(p), 0, glowRadius, glowRadius, 0);
//            }
//        }
        ofSetColor(255, glowOpacity);
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
        float x1 = screenW*screenScale/count*i;
        float y1 = 0;
        float y2 = screenH*screenScale;
        mesh.addVertex(ofVec2f(x1, y1));
        mesh.addColor(ofColor::lightBlue);
        mesh.addVertex(ofVec2f(x1, y2));
        mesh.addColor(ofColor::black);
    }
    mesh.draw();
}
