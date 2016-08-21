//
//  wavesScene.cpp
//  funkyForms
//
//  Created by Gordey on 8/9/16.
//
//

#include "wavesScene.hpp"
// ------------ Setup
void wavesScene::setup(){
    // size
    int w = RM->getWidth();
    int h = RM->getHeight();
    
    // setup parameters
    stencilWaves.setupGui();
    gradientWaves.setupGui();
    
    // setup gui
    setupGui();
    
    // setup obj
    gradientWaves.setup(w, h);
    stencilWaves.screenLeft = RM->getRectForScreen(SCREEN_LEFT);
    stencilWaves.screenRight = RM->getRectForScreen(SCREEN_RIGHT);
    stencilWaves.screenCenter = RM->getRectForScreen(SCREEN_CENTER);
    stencilWaves.setup(w, h);
}
void wavesScene::setupGui(){
    gui.setup("settings_wavesScene", "settings_wavesScene.xml");
    parameters.add(isStencilWaveMode.set("isStencilWaveMode", true));
    parameters.add(isGradientWavesMode.set("isGradientWavesMode", false));
    parameters.setName("wavesSceneParameters");
    gui.add(parameters);
    gui.add(gradientWaves.parameters);
    gui.add(stencilWaves.parameters);
    gui.loadFromFile("settings_wavesScene.xml");
}
// ------------ Update
void wavesScene::update(){
    updateParticles();
    updateInput();
    if(isGradientWavesMode) gradientWaves.update();
    if(isStencilWaveMode) stencilWaves.update();
}
void wavesScene::updateParticles(){
    for(int z = 0; z < 2; z++){
        for (int i = 0; i < cvData[z]->blobs.size(); i++){
            
            ofPoint avgVelSmoothed = cvData[z]->blobs[i].avgVelSmoothed;
            
            
            ofPolyline & line = cvData[z]->blobs[i].blob;
            
            // different ways to use it...
            //if (avgVelSmoothed.getNormalized().dot(ofPoint(0,-1)) > 0.7){
            if (avgVelSmoothed.y < -1){
                
                float mapMe = ofMap(avgVelSmoothed.y, -1, -3, 0.99, 0.9);
                for (int j = 0; j < line.size(); j++){
                    ofPoint pt = line[j];
                    pt = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
                    ofPoint vel = cvData[z]->blobs[i].vel[j];
                    ofPoint velNorm = vel.getNormalized();
                    float dot = velNorm.dot(ofPoint(0,-1)); // up
                    
                    if (dot > 0.44 && vel.length() > 3.1 && ofRandom(0,1) > mapMe){
                        
                        // is this FACING up ?
                        ofPoint tan = cvData[z]->blobs[i].blob.getTangentAtIndex(j).rotate(90, ofPoint(0,0,1));
                        if (tan.dot(ofPoint(0,-1)) > 0.1){
                            
                            particleWithAge temp;
                            temp.age = ofGetElapsedTimef();
                            temp.setInitialCondition(pt.x, pt.y, vel.x * 0.1, vel.y*0.5); // reduce the x vel
                            temp.damping = 0.01;
                            particles.push_back(temp);
                            if (particles.size() > 1000){
                                particles.erase(particles.begin());
                            }
                        }
                    }
                }
            }
            
            //line.draw();
        }
    }
    
    
    
    ofRectangle target = cvData[0]->getScreenRemapRectangle(SCREEN_LEFT);
    ofRectangle screenCenter = RM->getRectForScreen(SCREEN_CENTER);
    ofRectangle screenTop = RM->getRectForScreen(SCREEN_TOP);
    ofRectangle screenLeft = RM->getRectForScreen(SCREEN_LEFT);
    ofRectangle screenRight = RM->getRectForScreen(SCREEN_RIGHT);
    
    ofRectangle deadRectLeft;
    deadRectLeft.set(screenLeft.x, screenTop.y+300, screenLeft.getWidth(), screenLeft.y - screenTop.y);
    
    ofRectangle deadRectRight;
    deadRectRight.set(screenRight.x, screenTop.y+300, screenLeft.getWidth(), screenLeft.y - screenTop.y);
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].resetForce();
        particles[i].addDampingForce();
        
        float r = screenLeft.getWidth()/2;
        float x = screenLeft.getCenter().x;
        float y = screenTop.getCenter().y+300;
        if(deadRectLeft.inside(particles[i].pos)){
          ///  particles[i].addForce(0.2, 0);
        }
        if(deadRectRight.inside(particles[i].pos)){
           // particles[i].addForce(-0.2, 0);
        }
        if(screenCenter.inside(particles[i].pos)){
           // particles[i].addForce(particles[i].vel.x*0.005, particles[i].vel.y*0.005);
        }
        
//          particles[i].addAttractionForce(screenCenter.getCenter().x, screenCenter.getCenter().y, 10000, 0.02);
    }
    
    // add some noise!
    
    float time = ofGetElapsedTimef();
    
    for (int i = 0; i < particles.size(); i++){
        ofPoint pos = particles[i].pos;
        float speed = ofMap(time-particles[i].age, 1, 5, 1, 0, true);
        float xNoise = ofSignedNoise(pos.x * 0.1, pos.y * 0.1, i, time * 0.1);
        float yNoise = ofSignedNoise(pos.x * 0.1, pos.y * 0.1, i, time * 0.1 + 100000);
        
        particles[i].addForce(xNoise*0.2 * speed, -fabs(yNoise) * 0.2 * speed);
    }
    
    
    // get flow from the field:
    for (int i = 0; i < particles.size(); i++){
        ofPoint vel = cvData[0]->getFlowAtScreenPos(SCREEN_LEFT, particles[i].pos);
        particles[i].addForce(vel.x*0.03, vel.y*0.03);
    }
    
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].update();
    }
    
}
void wavesScene::updateInput(){
    for (int z = 0; z < 2; z++){
        for(int i=0; i< cvData[z]->blobs.size(); i++) {
            ofPolyline line = cvData[z]->blobs[i].blob;
    
            ofVec2f pt = cvData[z]->blobs[i].centroidSmoothed;
            pt = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
    
            for (auto & p : line.getVertices()){
                p = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, p);
            }
            if(isStencilWaveMode){
                stencilWaves.addPath(line);
    
                ofVec2f vel = cvData[z]->blobs[i].avgVel;
                for(auto &w: stencilWaves.waves){
                    for(auto &p: w.points){
                        if(p.p.distance(pt)<100 && vel.length()> 1.1 && vel.dot(ofVec2f(0, -1)) > 0){
                            w.addForceTo(&p, vel.normalize().y);
                        }
                    }
                }
            }
            if(isGradientWavesMode){
                ofVec2f vel = cvData[z]->blobs[i].avgVel;
                for(auto &w: gradientWaves.waves){
                    for(auto &p: w.points){
                        if(p.p.distance(pt)<100 && vel.dot(ofVec2f(0, -1)) > 0){
                            w.addForceTo(&p, vel.normalize().y);
                        }
                    }
                }
            }
        }
    }
}
// ------------ Draw
void wavesScene::draw(){

    if(isGradientWavesMode) gradientWaves.draw();
    if(isStencilWaveMode) stencilWaves.draw();
    drawParticles();
//    drawPeople();
}
void wavesScene::drawParticles(){

    ofSetCircleResolution(5);
    for(auto &p : particles){
        p.draw();
    }
    ofSetCircleResolution(20);
}
void wavesScene::drawGui(){
     gui.draw();
}
void wavesScene::drawPeople(){
    for (int i = 0; i < cvData[0]->blobs.size(); i++){
        ofSetColor(255);
        ofPolyline line = cvData[0]->blobs[i].blob;
        for (auto & pt : line){
            pt = cvData[0]->remapForScreen(SCREEN_LEFT, pt);
        }
        line.draw();
    }
}
// ------------ Events
void wavesScene::start(){
}
void wavesScene::stop(){
    
}
void wavesScene::blobBorn(int packetId, int id){
    
}
void wavesScene::blobDied(int packetId, int id){
    
}