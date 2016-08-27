#include "light2dScene.h"

#define SCALAR 0.5

void light2dScene::setup(){
    sceneName = "light2dScene";
    
    w = RM->getWidth();
    h = RM->getHeight();
    
    
    lightSystem.setup(w*SCALAR,h*SCALAR);
    
    for (auto & window : RM->innerWindows){
        ofPolyline copy = window;

        // resize it:        
        float scale = RM->getWidth() / 2100;
        
        for (auto & pt : copy){
            pt *= scale * SCALAR;
        }
        
        copy.flagHasChanged();
        copy.setClosed(true);
        windowsScaled.push_back(copy);
    }
    
    makeShapes();
    makeLights();
    
    guiDetail();
}


void light2dScene::update(){
    

    
    float currentTime = ofGetElapsedTimef() - startTime;
    float sinTime = ofMap(sin(currentTime),-1,1,-1.7,2);
    
        if(radius<600){
        radius += sinTime;
        }
    
        amplitude += sinTime*1.3;
        xVel += sinTime*0.003;
    


 
    updateLights();
    
}


void light2dScene::draw(){
    
    ofPushMatrix();
    ofScale(1.0/SCALAR, 1.0/SCALAR);
    lightSystem.draw();
    ofPopMatrix();
    
}


void light2dScene::updateLights(){
    for(int i = 0; i<lights.size(); i++){
        lights[i].addSinMove(h*SCALAR, amplitude, angleVel, xVel,
                             (RM->getRectForScreen(SCREEN_CENTER).y*SCALAR + SCALAR*RM->getRectForScreen(SCREEN_CENTER).height/2)
                             );
        lights[i].addBoundary(w*SCALAR,h*SCALAR,80);
        lights[i].update();
        
        if(!mouseLight){
            rLightVector[i]->setPosition(lights[i].pos);
        } else {
            rLightVector[i]->setPosition(ofPoint(ofGetMouseX(),ofGetMouseY()));
        }
        
        rLightVector[i]->setRadius(radius);
        rLightVector[i]->setBleed(bleed);
    }
    lightSystem.update();
}


void light2dScene::guiDetail(){
    
    movePanel.setup("Movement PANEL");
    movePanel.setPosition(80, 10);
    movePanel.add(angleVel.set("Angle Vel", 0.0565,0,0.1));
    movePanel.add(amplitude.set("Amplitude", 31,0,170));
    movePanel.add(xVel.set("xVel", 1.5,0,2));
    movePanel.add(mouseLight.set("Mouse Ligh0t",false));
    
    lightPanel.setup("LIGHT PANEL");
    lightPanel.setPosition(80, 170);
    lightPanel.add(radius.set("Radius", 290,200,600));
    lightPanel.add(bleed.set("bleed", 0,0,2));

}


void light2dScene::makeLights(){
    for (int k = 0; k<lightN; k++) {
        Light tempPos;
        tempPos.setup(ofPoint(ofRandom(w),1000),
                      int(ofRandom(0,2)),
                      ofPoint(ofRandom(0.4,0.8),ofRandom(0.1,1.2)),
                      ofRandom(0.2,1.2));
        lights.push_back(tempPos);
        
        int counter = (int)ofRandom(0,5);
        
        ofColor lightC;
        
        if(counter == 0){
            lightC.set(39,45,147);
        } else if(counter == 1){
            lightC.set(255,16,165);
        } else if(counter == 2){
            lightC.set(0,204,162);
        } else if(counter == 3){
            lightC.set(249,189,63);
        } else if(counter == 4){
            lightC.set(0,208,212);
        }
        
        
        rotatingLight = std::make_shared<ofx::Light2D>();
        rotatingLight->setPosition(tempPos.pos);
        rotatingLight->setViewAngle(ofDegToRad(360));
        rotatingLight->setColor(lightC);
        rotatingLight->setRadius(240);
        rLightVector.push_back(rotatingLight);
        lightSystem.add(rotatingLight);
    }
}


void light2dScene::drawGui(){
    movePanel.draw();
    lightPanel.draw();
}


void light2dScene::makeShapes(){
    for (int i = 0; i < windowsScaled.size(); ++i)
    {
        ofx::Shape2D::SharedPtr shape = std::make_shared<ofx::Shape2D>();
        
        shape->setColor(0);
        shape->setShape(windowsScaled[i]);
        
        lightSystem.add(shape);
    }
}

