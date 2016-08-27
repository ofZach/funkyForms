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
    
    
    float currentTime = ofGetElapsedTimef() - startTime;
    float currentTime2 = currentTime - 7;
    
    float timePhase1 = ofMap(sin(currentTime*0.9),-1,1,-5,5);
    
    if(currentTime>=0 && currentTime<=1){
        guiDtl();
    }
    
    else if (currentTime >1 && currentTime <=7 ){
        forceR += timePhase1;
    }  else if(currentTime>7 && currentTime<8){
        addNoise = true;
        indexScale =100;
        timeScale = 0.8;
        
        lightNum = 24;
        angleVel = 0.06;
        amplitude = 276;
        xVel = 8.05;
    }else if(currentTime>8 && currentTime<13){
         if(springBack > 0){
         springBack -= 0.005;
         } else if(springBack <= 0){
             springBack = 0;
         }
     } else if(currentTime>13 && currentTime<17){
         
         if(springBack<0.5){
         springBack += 0.005;
         }
     }
    
//    if(currentTime >= 0 && currentTime<=6){
//        guiDtl();
//    
//    } else if(currentTime > 6 && currentTime < 11 ){
//
//            forceR = 90;
//            springBack = 0.4;
//            lightNum = 28;
//            angleVel = 0.0375;
//            amplitude = 387;
//    }
//    else if (currentTime >= 11 && currentTime < 16 ){
//        forceR = 214;
//        springBack = 0.015;
//        damping = 0.1845;
//        force = 0.1135;
//        addClockWiseRotation = false;
//        
//        addNoise = true;
//        indexScale = 785;
//        timeScale = 1.8;
//
//        
//        lightNum = 28;
//        angleVel = 0.0375;
//        amplitude = 387;
//        xVel = 8.45;
//    }
//    else if (currentTime >= 17 && currentTime < 20 ){
//        forceR = 214;
//        springBack = 0.3;
//        damping = 0.1845;
//        force = 0.1135;
//        addClockWiseRotation = false;
//        
//        addNoise = true;
//        indexScale = 785;
//        timeScale = 1.8;
//        
//
//        lightNum = 28;
//        angleVel = 0.0375;
//        amplitude = 387;
//        xVel = 8.45;
//    }

    

    
    //sin(currentTime);
    //sin(currentTime*0.3);
    
//    if(currentTime>6 && currentTime<12){
//        addNoise = true;
//        addClockWiseRotation = false;
//    }
    
    
    updateParticle();
    
    if (hideCursor) {
        ofHideCursor();
    } else {
        ofShowCursor();
    }

//    forceR+=20;
   
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
    gui.add(forceR.set("Force Radius",223,20,350));
    gui.add(springBack.set("Spring Force", 0.245,0,0.5));
    gui.add(damping.set("Damping", 0.02, 0,0.3));
    gui.add(force.set("Repulsion Force",0.16,0.1,1));
    gui.add(addClockWiseRotation.set("Clockwise R", true));
    gui.add(addCounterClockwiseForce.set("Counterclockwise R", false));
    gui.add(rotateSpeed.set("Rotation Speed",33.15,15,50));
    gui.add(addLine.set("Line Mode", false));
    gui.add(lineNum.set("line Distance",5,3,10));
    gui.add(colorMode.set("Color Mode", false));
    gui.add(hideCursor.set("Hide Cursor", false));
    
    
    noiseGui.setup("NOISE PANEL");
    noiseGui.setPosition(80,280);
    noiseGui.add(addNoise.set("Add Noise", false));
    noiseGui.add(indexScale.set("Noise Index",0,0,1000));
    noiseGui.add(timeScale.set("Noise Scale",0,0,2));
    
    
    lightPanel.setup("LIGHT PANEL");
    lightPanel.setPosition(80,400);
    lightPanel.add(lightNum.set("Light Number", 18,1,particleLightN));
    lightPanel.add(angleVel.set("Angle Vel", 0.0875,0,0.5));
    lightPanel.add(amplitude.set("Amplitude", 165,0,600));
    lightPanel.add(xVel.set("xVel", 8.45,7,12));
    lightPanel.add(drawLight.set("Draw Light",false));
    lightPanel.add(mouseLight.set("Mouse Light",false));


}

void particleScene::drawGui(){
    gui.draw();
    noiseGui.draw();
    lightPanel.draw();
}



