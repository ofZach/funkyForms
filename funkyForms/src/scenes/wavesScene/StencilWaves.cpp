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
    refract.setup(ofGetWidth(), ofGetHeight());
    
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
    glowImg.load("assets/glow.png");
}
void StencilWaves::setupGui(){
    refract.setupParameters();
    parameters.setName("stencilWavesParameters");
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
    addWave(ofGetHeight()-150);
    addWave(ofGetHeight()-100);
}
void StencilWaves::addWave(int y){
    class wave wave;
    wave.cvData = cvData;
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
    ofFill();
    peopleFbo.begin();
    ofClear(0, 0);
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
    ofFill();
    
    mask.begin(1); // img to be masked
    ofClear(0, 0);
    for(auto &p: contours){
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
void StencilWaves::updateContours(){
    contours.clear();
    for(auto &id : cvData->idsThisFrame){
        ofPolyline l = cvData->getResampledLineAt(id, 2);
        ofPath path;
        for (auto &p : l) {
            path.lineTo(p);
        }
        path.setFillColor(ofColor::white);
        contours.push_back(path);
    }
}
// -------------- draw
void StencilWaves::draw(){

//    mainWaveMesh.draw();
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
//    refract.draw(0, 0);
//    drawGlow();
//    ofDisableBlendMode();
    drawUpperPeople();
}
void StencilWaves::drawUpperPeople(){
    for(auto &id : cvData->idsThisFrame){
        ofPolyline l = cvData->getResampledLineAt(id, 50);
        ofPath path;
        for (int i = 0; i < l.size(); i++){
            int i_n = ofClamp(i+1, 0, l.size()-1);
            int i_p = ofClamp(i-1, 0, l.size()-1);
            ofVec2f pp = l.getVertices()[i_p];
            ofVec2f pc = l.getVertices()[i];
            ofVec2f pn = l.getVertices()[i_n];
            ofVec2f deltaP1 = pc - pp;
            ofVec2f deltaP2 = pn - pc;
            
            if(deltaP1.dot(deltaP2)>0){
                
            }
        }
        path.setFillColor(ofColor::white);
        path.draw();
    }
}
void StencilWaves::drawPlainWaveMesh(){
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
        float r = 0;
        for(auto &id : cvData->idsThisFrame){
            ofVec2f pos = cvData->getCentoidAt(id);
            if(pos.distance(p)<glowRadius){
                r = ofMap(pos.distance(p), 0, glowRadius, glowRadius, 0);
            }
        }
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
