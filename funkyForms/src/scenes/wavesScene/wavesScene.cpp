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
    gradientWaves.screenLeft =  RM->getRectForScreen(SCREEN_LEFT);
    stencilWaves.screenLeft = RM->getRectForScreen(SCREEN_LEFT);
    stencilWaves.screenRight = RM->getRectForScreen(SCREEN_RIGHT);
    stencilWaves.screenCenter = RM->getRectForScreen(SCREEN_CENTER);
    stencilWaves.setup(w, h);
    
    
    // who is first
    gradientWaves.setIn();
    stencilWaves.setIn();
    stencilWaves.isEnabled = false;
    gradientWaves.fadeIn();
    
    // glow
    ofDisableArbTex();
    glow.load("assets/glow.png");
    ofEnableArbTex(); 
}
void wavesScene::setupGui(){
    gui.setup("settings_wavesScene", "settings_wavesScene.xml");
    parameters.add(modeChangeMinute.set("modeChangeMinute",  1, 0.01, 5));
    parameters.add(changeMode.set("changeMode", true));
    parameters.add(glowRadius.set("glowRadius", 20, 5, 200));
    parameters.add(glowOpacity.set("glowOpacity", 120, 0, 255));
    parameters.add(glowSpacing.set("glowSpacing", 5, 0, 100));
    parameters.add(isStencilWaveMode.set("isStencilWaveMode", true));
    parameters.add(isGradientWavesMode.set("isGradientWavesMode", false));
    parameters.add(mapVelmin.set("mapVelmin", -1, -1, -0.2));
    parameters.add(mapVelmax.set("mapVelmax", -3, -1,  -8));
    parameters.add(dotValue.set("dotValue", 0.44, 0.1,  1));
    parameters.add(velLength.set("velLength", 4.44, 1.0, 10));
    parameters.setName("wavesSceneParameters");
    gui.add(parameters);
    gui.add(gradientWaves.parameters);
    gui.add(stencilWaves.parameters);
    gui.loadFromFile("settings_wavesScene.xml");
    
    changeMode.addListener(this, &wavesScene::triggerChangeMode);
}
void wavesScene::triggerChangeMode(bool &b){
    advanceMode();
}
// ------------ Update
void wavesScene::advanceMode(){
    isFade ^= true;
    if(isFade){
        stencilWaves.fadeIn();
        gradientWaves.fadeOut();
        stencilWaves.updateFade();
    }else{
        stencilWaves.fadeOut();
        gradientWaves.fadeIn();
        stencilWaves.updateFade();
    }
}
void wavesScene::update(){
    updateModeChange();
    updateParticles();
    updateInput();
    gradientWaves.update();
    stencilWaves.update();
    updateFade();
}
void wavesScene::updateModeChange(){
    modeChangeCounter++;
    int k = modeChangeMinute*3600;
    if( modeChangeCounter%k == 0){
        advanceMode();
    }
}
void wavesScene::updateFade(){
}
void wavesScene::updateParticles(){
    for(int z = 0; z < 2; z++){
        for (int i = 0; i < cvData[z]->blobs.size(); i++){
            ofPoint avgVelSmoothed = cvData[z]->blobs[i].avgVelSmoothed;
            
            ofPolyline & line = cvData[z]->blobs[i].blob;
            
            // different ways to use it...
            //if (avgVelSmoothed.getNormalized().dot(ofPoint(0,-1)) > 0.7){
            if (avgVelSmoothed.y < -1){
                float mapMe = ofMap(avgVelSmoothed.y, mapVelmin, mapVelmax, 0.99, 0.9);
                for (int j = 0; j < line.size(); j++){
                    ofPoint pt = line[j];
                    pt = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
                    ofPoint vel = cvData[z]->blobs[i].vel[j];
                    ofPoint velNorm = vel.getNormalized();
                    float dot = velNorm.dot(ofPoint(0,-1)); // up
                    
                    if (dot > dotValue && vel.length() > velLength && ofRandom(0,1) > mapMe){
                        
                        // is this FACING up ?
                        ofPoint tan = cvData[z]->blobs[i].blob.getTangentAtIndex(j).rotate(90, ofPoint(0,0,1));
                        if (tan.dot(ofPoint(0,-1)) > 0.1){
                            
                            particleWithAge temp;
                            temp.age = ofGetElapsedTimef();
                            temp.radius = ofRandom(1 * sf, 30 * sf);
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
        
        // check underwater particles by setting its id: underwater: 0
        ofVec2f pPos = particles[i].pos;
        for (int k = 0; k < stencilWaves.waves[0].points.size(); k++){
            ofVec2f wPos = stencilWaves.waves[0].points[k].p;
            int i_n = min(k+1, (int)stencilWaves.waves[0].points.size()-1);
            ofVec2f wPosNext = stencilWaves.waves[0].points[i_n].p;
            if(pPos.x > wPos.x && pPos.x < wPosNext.x){
                if(pPos.y<wPos.y){
                    particles[i].id = 1;
                }else{
                    particles[i].id = 0;
                }
            }
        }
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
    updateParticlesMesh();
}
void wavesScene::updateParticlesMesh(){
    particlesMesh.clear();
     particlesMesh.setMode(OF_PRIMITIVE_POINTS);
    for(auto &p : particles){
        if(p.id==1){
            particlesMesh.addVertex(p.pos);
        }
    }
}
void wavesScene::updateInput(){
    for (int z = 0; z < 2; z++){
        for(int i=0; i< cvData[z]->blobs.size(); i++) {
            ofPolyline line = cvData[z]->blobs[i].blob;
    
            ofVec2f pt = cvData[z]->blobs[i].centroidSmoothed;
            pt = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
    
            ofVec2f vel = cvData[z]->blobs[i].avgVel;
            
            for (auto & p : line.getVertices()){
                p = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, p);
            }
            if(stencilWaves.isEnabled){
                stencilWaves.addPath(line);
                for(auto &w: stencilWaves.waves){
                    for(auto &p: w.points){
                        if(p.p.distance(pt)<100 && vel.length()> 1.1 && vel.dot(ofVec2f(0, -1)) > 0){
                            w.addForceTo(&p, vel.normalize().y);
                        }
                    }
                }
            }
            if(gradientWaves.isEnabled){
                for (auto & linePoint : line.getResampledBySpacing(10 * sf)){
                    int firstWaveIndex = gradientWaves.waves.size()-1;
                    for(auto &p: gradientWaves.waves[firstWaveIndex].points){
                        if(p.p.distance(linePoint)<100 && vel.dot(ofVec2f(0, -1)) > 0){
                            gradientWaves.waves[firstWaveIndex].addForceTo(&p, vel.normalize().y);
                        }
                    }
                }
            }
        }
    }
}
// ------------ Draw
void wavesScene::draw(){
    if(gradientWaves.isEnabled) {
        gradientWaves.draw();
        drawPeople();
    }
    if(stencilWaves.isEnabled) stencilWaves.draw();
    ofEnableAlphaBlending();
    if(stencilWaves.isEnabled) drawParticles();
}
void wavesScene::drawParticles(){
//      glPointSize(100);
//        ofEnablePointSprites();
//        glow.getTexture().bind();
//    glBegin(GL_POINTS); //starts drawing of points
//    for(auto &p : particles){
//      
//        glVertex3f(p.pos.x, p.pos.y ,0.0f);//upper-right corner
//    }
//    glEnd();//end drawing of points
//        glow.getTexture().unbind();
//        ofDisablePointSprites();
    
    
//    ofSetColor(255);
//    ofEnablePointSprites();
//    glow.getTexture().bind();
//    particlesMesh.drawFaces();
//    glow.getTexture().unbind();
//    ofDisablePointSprites();
    
    ofSetCircleResolution(5);
    float fadeVal = stencilWaves.fadeAnimator.getValue();
    float opacity = ofMap(fadeVal, 0, 1, 0, 255);
    for(auto &p : particles){
        ofSetColor(255, opacity);
        if(p.id == 1){
            float x = p.pos.x - p.radius;
            float y = p.pos.y - p.radius;
            glow.draw(x, y, p.radius*2, p.radius*2);
        }else{
            p.draw();
        }
        
    }
    ofSetCircleResolution(20);
}
void wavesScene::drawGui(){
     gui.draw();
}
void wavesScene::drawPeople(){
    float fadeVal = gradientWaves.fadeAnimator.getValue();
    float opacity = ofMap(fadeVal, 0, 1, 0, 255);
    // glow
    for (int z = 0; z < 2; z++){
        for(int i=0; i< cvData[z]->blobs.size(); i++) {
            ofPolyline line = cvData[z]->blobs[i].blob.getResampledBySpacing(glowSpacing * sf);
            
            for (auto & p : line.getVertices()){
                p = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, p);
                float op = min(opacity*1.0, glowOpacity*1.0);
                ofSetColor(255, op);
                glow.draw(p.x - glowRadius * sf, p.y - glowRadius * sf , glowRadius * 2 * sf, glowRadius * 2 * sf );
            }
        }
    }
    // people
    for (int z = 0; z < 2; z++){
        for(int i=0; i< cvData[z]->blobs.size(); i++) {
            ofPolyline &line = cvData[z]->blobs[i].blob;
            
            ofVec2f pt = cvData[z]->blobs[i].centroidSmoothed;
            pt = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
            
            for (auto & p : line.getVertices()){
                p = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, p);
            }
            ofVec2f vel = cvData[z]->blobs[i].avgVel;
            ofPath path;
            for(auto &p : line){
                path.lineTo(p);
            }
            path.setFillColor(ofColor(0, opacity));
            path.draw();
        }
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