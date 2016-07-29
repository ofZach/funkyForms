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



    for (int i = 0; i < 5; i++) {
        pos += 10*i;
        addWave(pos, swatch[i%5], swatchBase[i%5]);
    }
    
    // box2d
    box2d.init();
    box2d.setGravity(0, 20);
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
    
    // shader
    bumpmap.allocate(ofGetWidth(), ofGetHeight());
    bumpmap.setup();
    
    gui.setup("waveSettings");
    gui.add(waveCount.set("waveCount", 5, 1, 20));
    gui.add(waveDistance.set("waveDistance", 10, 5, 200));
    gui.add(amount.set("amount", 55, 10, 200));
    gui.add(strength.set("strength", 0.55, 0.001, 1));
    gui.add(restLength.set("restLength", 16.92, 0, 18));
    gui.add(invMass.set("invMass", 0.375, 0.1, 3));
    gui.add(force.set("force", 4, 0.1, 20));
    gui.add(density.set("density", 3, 0, 20));
    gui.add(bounce.set("bounce", 0.5, 0, 3));
    gui.add(friction.set("friction", 0.1, 0, 2));
    gui.add(shadowRadius.set("shadowRadius", 100, 0, 500));
    gui.add(energyHighlightSize.set("energyHighlightSize", 100, 0, 500));
    gui.add(shadowOpacity.set("shadowOpacity", 100, 0, 255));
    gui.add(bumpmap.parameters);
    
    waveCount.addListener(this, &WaveManager::reloadInt);
    amount.addListener(this, &WaveManager::reloadInt);

    waveDistance.addListener(this, &WaveManager::reload);
    force.addListener(this, &WaveManager::reload);
    restLength.addListener(this, &WaveManager::reload);
    strength.addListener(this, &WaveManager::reload);
    invMass.addListener(this, &WaveManager::reload);
    
    gui.loadFromFile("settings.xml");
}
void WaveManager::reloadInt(int &value){
    float val = 0;
    reload(val);
}
void WaveManager::reload(float &value){
    waves.clear();
    for (int i = 0; i < waveCount; i++) {
        addWave(waveDistance*i+ofGetHeight()-waveDistance*waveCount, swatch[i%5], swatchBase[i%5]);
    }
}
void WaveManager::addWave( int ypos, ofFloatColor col, ofColor baseCol){
    FishWave wave;
    wave.restLength = restLength;
    wave.strength = strength;
    wave.invMass = invMass;
    wave.amount = amount;
    wave.force = force;
    wave.color = col;
    wave.baseColor = baseCol;
    wave.setup(ypos, ofGetWidth());
    wave.setupFishWave();
    waves.push_back(wave);
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
// -------------- update
void WaveManager::update(int x, int y){
    updateWaveParameters();
//    updateBox2d();
    for (int i = 0; i < waves.size(); i++) {
        waves[i].update(IM->targets);
        waves[i].updateFishWave();
    }
}
void WaveManager::updateWaveParameters(){
    for(auto &w: waves){
        w.shadowRadius = shadowRadius;
        w.shadowOpacity = shadowOpacity;
        w.energyHighlightSize = energyHighlightSize;
    }

}
void WaveManager::updateBox2d(){
    for(int i = 0; i<circles.size(); i++){
        if(ofxBox2dBaseShape::shouldRemoveOffScreen(circles[i])){
            circles.erase(circles.begin()+i);
            colors.erase(colors.begin()+i);
        }
    }
    
    box2d.update();
    ground.clear();
    ground.addVertexes(waves[waves.size()-1].polyline);
    ground.create(box2d.getWorld());
    
    if(ofGetFrameNum()%10 == 0){
        float r = ofRandom(4, 20);		// a random radius 4px - 20px
        circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
        colors.push_back(swatch[(int)ofRandom(5)]);
        ofxBox2dCircle * circle = circles.back().get();
        circle->setPhysics(density, bounce, friction);
        circle->setup(box2d.getWorld(), ofRandomWidth(), 20, r);
    }
    
    ground.updateShape();
}
void WaveManager::updateRipples(){
    bumpmap.begin();
    ofPushMatrix();
    ofTranslate(IM->pos);
    for (int i = 0; i < IM->getContourFinder()->getPolylines().size(); i++) {
        ofPolyline &l = IM->getContourFinder()->getPolyline(i);
        ofPath path;
        int res = ofMap(l.getPerimeter(), 0, 1900, 1, 200);
        for (float i = 0; i < 1.; i += 1.0/res) {
            path.lineTo(l.getPointAtPercent(i));
        }
        //        path.setFilled(false);
        path.setStrokeColor(ofColor::white);
        path.setStrokeWidth(5);
        path.draw();
    }
    ofPopMatrix();
    bumpmap.end();
    bumpmap.update();
}
// -------------- draw
void WaveManager::draw(){
    for (int i = 0; i < waves.size(); i++) {
        waves[i].draw();
    }
//    drawBox2d();
    ofSetColor(255, 255);
    gui.draw();
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
void WaveManager::drawBox2d(){
    for(int i=0; i<circles.size(); i++) {
        ofFill();
        ofSetColor(colors[i]);
        ofDrawCircle(circles[i].get()->getPosition(), circles[i].get()->getRadius());
    }
}
void WaveManager::drawRipples(){
    bumpmap.draw();
}




