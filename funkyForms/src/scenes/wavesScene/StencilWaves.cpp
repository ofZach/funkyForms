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
    float sw = screenLeft.getWidth()+screenCenter.getWidth()+screenRight.getWidth();
    refract.allocate(sw,screenLeft.getHeight());
    refract.setup(sw, screenLeft.getHeight());
    
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
    mask.allocate(screenW, screenH);
    
    // colors
    peopleColor = ofColor::lavender;
    
    // images
    glowImg.load("assets/glow.png");
    
    // fade
    fadeAnimator.setSpeed(0.006);
}
void StencilWaves::setupGui(){
    refract.setupParameters();
    parameters.setName("stencilWavesParameters");
    parameters.add(wavePos.set("wavePos", 150, 10, 300));
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
    addWave(screenH*screenScale-wavePos);
    addWave(screenH*screenScale-wavePos);
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
void StencilWaves::chillWave(){
    isWaveRelax = true;
}
void StencilWaves::runWave(){
    isWaveRelax = false;
}
// -------------- update
void StencilWaves::update(){
    updateFade();
    updateWaveParameters();
    updateWaves();
    updateMeshes();
    updateFbos();
    updateMasks();
    updateRefract();
}
void StencilWaves::updateFade(){
    fadeOpacity = ofMap(fadeAnimator.getValue(), 1, 0, 0, 255);
    if(isWaveRelax){
        for(auto &p : waves[0].points){
            p.p.y = p.p.y*0.9 + 0.1*(waves[0].points[0].p.y);
        }
    }
    fadeAnimator.update();
    if(fadeAnimator.isIn || fadeAnimator.isOut){
        isWaveRelax = false;
    }
    if(!fadeAnimator.isIn && !fadeAnimator.isOut){
        isWaveRelax = true;
        for(auto &p : waves[0].points ){
            if(p.isFixed){
                float v = ofMap(fadeAnimator.getValue(), 0, 1, screenLeft.getBottom()-wavePos, screenLeft.getBottom()+wavePos);
                p.p.y = v;
            }
        }
    }
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
        p.setFillColor(ofColor(p.getFillColor(), fadeOpacity));
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
    float sw = screenLeft.getWidth()+screenCenter.getWidth()+screenRight.getWidth();

    refract.begin(0);
    mask.getTexture().drawSubsection(0, 0,  sw ,  screenLeft.getHeight(), screenLeft.getTopLeft().x, screenLeft.getTopLeft().y);
    refract.end(0);
    
    refract.begin(1);
    mainWaveFbo.getTexture().drawSubsection(0, 0,  sw ,  screenLeft.getHeight(), screenLeft.getTopLeft().x, screenLeft.getTopLeft().y);
    refract.end(1);
  
    refract.update();
}
void StencilWaves::addPath(ofPolyline &contour){
    ofPath path;
    ofVec2f centroid  = contour.getCentroid2D();
    for (auto &p : contour) {
        path.lineTo(p);
    }
    path.setFillColor(ofColor::white);
    paths.push_back(path);
    centroids.push_back(centroid);
}
// -------------- draw
void StencilWaves::draw(){
    ofFill();
    drawUpperPeople();
    mainWaveMesh.draw();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    drawGlow();
    ofDisableBlendMode();
 
    refract.draw(screenLeft.getTopLeft().x, screenLeft.getTopLeft().y);
    
    paths.clear();
    centroids.clear();
    ofSetColor(255);
    waves[0].polyline.draw();
}
void StencilWaves::drawUpperPeople(){
    for(auto &p: paths){
        p.setFillColor(ofColor(p.getFillColor(), fadeOpacity));
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
        for(auto &c : centroids){
            if(c.distance(p)<glowRadius){
                r = ofMap(c.distance(p), 0, glowRadius, glowRadius, 0);
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
