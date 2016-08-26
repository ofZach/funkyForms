#include "particleScene.h"


void particleScene::setup(){
    sceneName = "particleScene";
    w = RM->getWidth();
    h = RM->getHeight();

    loadWholeBuilding();
    
    loadParticle();
    
    for (int k = 0; k<particleLightN; k++) {
        lightSource tempLight;
        tempLight.setup(ofPoint(ofRandom(w),ofRandom(h)),
                        int(ofRandom(0,2)),
                        ofPoint(ofRandom(0.4,0.8),ofRandom(0.1,1.2)),
                        ofRandom(0.2,1.2));
        lights.push_back(tempLight);
        
        lightSource upTemp;
        tempLight.setup(ofPoint(ofRandom(RM->getRectForScreen(SCREEN_TOP).width),ofRandom(RM->getRectForScreen(SCREEN_TOP).height)),
                        int(ofRandom(0,2)),
                        ofPoint(ofRandom(0.4,0.8),ofRandom(0.1,1.2)),
                        ofRandom(0.2,1.2));
        
        float temp;
        temp = ofRandom(0.1,1.5);
        forceRscale.push_back(temp);
    }
    
    guiDtl();

    
}

void particleScene::update(){
    
    updateParticle();
    
    if (hideCursor) {
        ofHideCursor();
    } else {
        ofShowCursor();
    }

   
}

void particleScene::draw(){
    
//    drawBuilding();
    
    drawParticleBuilding();
    
    
}


void particleScene::loadWholeBuilding(){
    float scale = RM->getWidth() / 2100;
    for (auto & window : RM->innerWindowsResampled){
        ofPolyline copy = window;
        
        // resize it:
        
        for (auto & pt : copy){
            pt *= scale;
        }
        
        copy.flagHasChanged();
        copy.setClosed(true);
        windowsScaled.push_back(copy);
    }
    
    
    for (auto & outerwindow : RM->outerWindowsResampled){
        ofPolyline copy = outerwindow;
        
        // resize it:
        
        for (auto & pt : copy){
            pt *= scale;
        }
        
        copy.flagHasChanged();
        copy.setClosed(true);
        outerWindowsScaled.push_back(copy);
    }
    
    for (auto & engravings : RM->engravingResampled){
        ofPolyline copy = engravings;
        
        // resize it:
        for (auto & pt : copy){
            pt *= scale;
        }
        
        copy.flagHasChanged();
        copy.setClosed(true);
        engravingScaled.push_back(copy);
    }
    
    for (auto & pillars : RM->pillarResampled){
        ofPolyline copy = pillars;
        
        // resize it:
        for (auto & pt : copy){
            pt *= scale;
        }
        
        copy.flagHasChanged();
        copy.setClosed(true);
        pillarScaled.push_back(copy);
    }
    
    for (auto & edge : RM->edgesResampled){
        ofPolyline copy = edge;
        
        // resize it:
        for (auto & pt : copy){
            pt *= scale;
        }
        
        copy.flagHasChanged();
        copy.setClosed(true);
        edgesScaled.push_back(copy);
    }
   

}




void particleScene::drawBuilding(){
    
    for (int i = 0; i < windowsScaled.size(); i++){
        windowsScaled[i].draw();
    }
    
    for (int i = 0; i < outerWindowsScaled.size(); i++){
        outerWindowsScaled[i].draw();
    }
    
    
    for (int i = 0; i < engravingScaled.size(); i++){
        engravingScaled[i].draw();
    }
    
    
    for (int i = 0; i < pillarScaled.size(); i++){
        pillarScaled[i].draw();
    }
    
    
    for (int i = 0; i < edgesScaled.size(); i++){
        edgesScaled[i].draw();
    }
    

    
}


void particleScene::loadParticle(){

    for (int i = 0; i < windowsScaled.size(); i++){
        ofPolyline tempPoly = windowsScaled[i];
        for(int k = 0; k < windowsScaled[i].size(); k++){
            ofVec3f tempVert = windowsScaled[i][k];
            ParticleNoise myParticle;
            myParticle.setup(tempVert.x,tempVert.y,0,0);
            particles.push_back(myParticle);
        }
    }
    
    
    for (int i = 0; i < outerWindowsScaled.size(); i++){
        ofPolyline tempPoly = outerWindowsScaled[i];
        for(int k = 0; k < outerWindowsScaled[i].size(); k++){
            ofVec3f tempVert = outerWindowsScaled[i][k];
            ParticleNoise myParticle;
            myParticle.setup(tempVert.x,tempVert.y,0,0);
            particles.push_back(myParticle);
        }
    }
    
    for (int i = 0; i < engravingScaled.size(); i++){
        ofPolyline tempPoly = engravingScaled[i];
        for(int k = 0; k < engravingScaled[i].size(); k++){
            ofVec3f tempVert = engravingScaled[i][k];
            ParticleNoise myParticle;
            myParticle.setup(tempVert.x,tempVert.y,0,0);
            particles.push_back(myParticle);
        }
    }
    
    for (int i = 0; i < pillarScaled.size(); i++){
        ofPolyline tempPoly = pillarScaled[i];
        for(int k = 0; k < pillarScaled[i].size(); k++){
            ofVec3f tempVert = pillarScaled[i][k];
            ParticleNoise myParticle;
            myParticle.setup(tempVert.x,tempVert.y,0,0);
            particles.push_back(myParticle);
        }
    }
    
    for (int i = 0; i < edgesScaled.size(); i++){
        ofPolyline tempPoly = edgesScaled[i];
        for(int k = 0; k < edgesScaled[i].size(); k++){
            ofVec3f tempVert = edgesScaled[i][k];
            ParticleNoise myParticle;
            myParticle.setup(tempVert.x,tempVert.y,0,0);
            particles.push_back(myParticle);
        }
    }
    
}


void particleScene::updateParticle(){
    
    float ratio;
    float brightness;
    
    ofPoint mousePos = ofPoint(ofGetMouseX(), ofGetMouseY());
    
    vector<ofPoint> lightsPosVector;
    
    for (auto l = lights.begin(); l !=lights.end(); l++) {
        l->addSinMove(h, amplitude, angleVel, xVel,
                      (RM->getRectForScreen(SCREEN_CENTER).y + RM->getRectForScreen(SCREEN_CENTER).height/2)
                      );
        l->addBoundary(w,h,forceR*1.2);
        l->update();
        ofPoint temp;
        temp=l->pos;
        lightsPosVector.push_back(temp);
    }
    
    
    float timef = ofGetElapsedTimef();
    float noiseIndex = 0;
    
    vector<float> velVec;
    
    
    for(auto p = particles.begin(); p != particles.end(); p++)
    {
        
        //  velVec.push_back(p->vel.length());
        
        noiseIndex ++;
        
        p->addDampingForce(damping);
        p->resetForce();
        
        vector<float> distances;
        
        for (int l = 0; l<lightsPosVector.size(); l++) {
            ofPoint diff ;
            if (mouseLight) {
                diff = mousePos - p->pos;
            } else{
                diff = lightsPosVector[l] - p->pos;
            }
            
            float temp;
            temp = ofDist(0, 0, diff.x, diff.y);
            
            distances.push_back(temp);
            
        }
        
        ofPoint lightPosition;
        
        for (int d = 0; d < distances.size(); d++) {
            
            if (d<lightNum) {
                
                if(mouseLight){
                    lightPosition = mousePos;
                } else{
                    lightPosition = ofPoint(lightsPosVector[d].x,lightsPosVector[d].y);
                }
                
                float fR =forceR*forceRscale[d];
                float rotateR = fR*0.4;
                
                if (distances[d]<fR){
                    if (addClockWiseRotation) {
                        p->addClockwiseForce(lightPosition.x,lightPosition.y,fR, force, rotateSpeed, rotateR);
                        
                    } else if (addCounterClockwiseForce){
                        p->addCounterClockwiseForce(lightPosition.x,lightPosition.y,fR, force, rotateSpeed, rotateR);
                    } else {
                        p->addRepulsionForce(lightPosition.x,lightPosition.y,fR, force);
                    }
                }
            }
        }
        
        
        if (addNoise) {
            float x = p->pos.x / 100.0;
            float y = p->pos.y / 100.0;
            
            float xForce = ofSignedNoise(x, y, 0 + noiseIndex/indexScale, timef*timeScale);
            float yForce = ofSignedNoise(x, y, 100000 + noiseIndex/indexScale, timef*timeScale);
            
            p->addForce(xForce*4, yForce*4);
        }
        
        p->addSpringBackForce(p->pos,springBack);
        p->update();
        
    }
    
    for(auto p = particles.begin(); p != particles.end(); p++)
    {
        
        velVec.push_back(p->vel.length());
        
    }
    
    auto maxVel = max_element(std::begin(velVec), std::end(velVec));
    auto minVel = min_element(std::begin(velVec), std::end(velVec));
    
    
    for(auto pr = particles.begin(); pr != particles.end(); pr++){
        pr->addColor(addClockWiseRotation, mousePos, colorMode, *maxVel, *minVel);
    }
    
}


void particleScene::drawParticleBuilding(){
    for(auto p = particles.begin(); p!=particles.end();p++){
        p->draw();
    }

}

void particleScene::guiDtl(){
  
    gui.setup("FORCE PANEL");
    gui.setPosition(80,30);
    gui.add(forceR.set("Force Radius",20,10,250));
    gui.add(springBack.set("Spring Force", 0.245,0,0.5));
    gui.add(damping.set("Damping", 0.02, 0,0.3));
    gui.add(force.set("Repulsion Force",0.3,0.1,4));
    gui.add(addClockWiseRotation.set("Clockwise R", true));
    gui.add(addCounterClockwiseForce.set("Counterclockwise R", false));
    gui.add(rotateSpeed.set("Rotation Speed",50,30,135));
    gui.add(addLine.set("Line Mode", false));
    gui.add(lineNum.set("line Distance",5,3,10));
    gui.add(colorMode.set("Color Mode", false));
    gui.add(hideCursor.set("Hide Cursor", false));
    
    
    noiseGui.setup("NOISE PANEL");
    noiseGui.setPosition(80,280);
    noiseGui.add(addNoise.set("Add Noise", false));
    noiseGui.add(indexScale.set("Noise Index",215,0,1000));
    noiseGui.add(timeScale.set("Noise Scale",0.88,0,2));
    
    
    lightPanel.setup("LIGHT PANEL");
    lightPanel.setPosition(80,400);
    lightPanel.add(lightNum.set("Light Number", 15,1,particleLightN));
    lightPanel.add(angleVel.set("Angle Vel", 0.05,0,0.5));
    lightPanel.add(amplitude.set("Amplitude", 80,0,600));
    lightPanel.add(xVel.set("xVel", 2.3,0,10));
    lightPanel.add(drawLight.set("Draw Light",false));
    lightPanel.add(mouseLight.set("Mouse Light",false));

}

void particleScene::drawGui(){
    gui.draw();
    noiseGui.draw();
    lightPanel.draw();
}



