#include "box2dScene.h"


void box2dScene::setup(){
    sceneName = "box2dScene";
    
    w = RM->getWidth();
    h = RM->getHeight();
    

    
    box2d.init();
    box2d.setGravity(0, 10);
    box2d.createGround();
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
    
    addBoxEdge();
    
    
    for (int i = 0; i<edges.size(); i++) {
        edges[i].setPhysics(0.0, 0.5, 0.5);
        edges[i].create(box2d.getWorld());
    }
    
    for (int k = 0; k<forceN; k++) {
        forceSource tempforce;
        tempforce.setup(ofPoint(ofRandom(w),ofRandom(h)),
                        int(ofRandom(0,2)),
                        ofPoint(ofRandom(0.4,0.8),ofRandom(0.1,1.2)),
                        ofRandom(0.2,1.2));
        forces.push_back(tempforce);
        
        float temp;
        temp = ofRandom(0.1,1.5);
        forceRscale.push_back(temp);
    }
    
    guiDtl();
    addObject();
  
}

//--------------------------------------------------------------
void box2dScene::update(){
    box2d.update();
    
    addMovement();
    // ofRemove(circles, ofxBox2dBaseShape::shouldRemoveOffScreen);
    //     ofRemove(customParticles, ofxBox2dBaseShape::shouldRemoveOffScreen);
    
    box2d.setGravity(gravityH, gravityV);
}

//--------------------------------------------------------------
void box2dScene::draw(){

    drawObject();
    
    for (int l = 0; l < forces.size(); l++) {
        if (l<forceNum) {
            if (drawforce) {
                forces[l].draw();
            }
        }
    }

}


//--------------------------------------------------------------
void box2dScene::addMovement(){
    ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
    //    float minDis = ofGetMousePressed() ? 100 : 60;
    
    ofPoint mousePos = ofPoint(ofGetMouseX(), ofGetMouseY());
    
    vector<ofPoint> forcesPosVector;
    
    for (auto l = forces.begin(); l !=forces.end(); l++) {
        l->addSinMove(h, amplitude, angleVel, xVel, (RM->getRectForScreen(SCREEN_CENTER).y + RM->getRectForScreen(SCREEN_CENTER).height/2));
        l->addBoundary(w,h,forceR*1.2);
        l->update();
        ofPoint temp;
        temp=l->pos;
        forcesPosVector.push_back(temp);
    }
    
    

    for(int i=0; i<customParticles.size(); i++) {
        customParticles[i].get()->setDamping(damping);
        
        vector<float> distances;
        
        for (int l = 0; l<forcesPosVector.size(); l++) {
            ofPoint diff ;
            if (mouseforce) {
                diff = mousePos - customParticles[i].get()->getPosition();
            } else{
                diff = forcesPosVector[l] - customParticles[i].get()->getPosition();
            }
            
            float temp;
            temp = ofDist(0, 0, diff.x, diff.y);
            
            distances.push_back(temp);
            
        }
        
        
        ofPoint forcePosition;
        
        for (int d = 0; d < distances.size(); d++) {
            
            if (d<forceNum) {
                
                if(mouseforce){
                    forcePosition = mousePos;
                } else{
                    forcePosition = ofPoint(forcesPosVector[d].x,forcesPosVector[d].y);
                }
                
                float fR =forceR*forceRscale[d];
                float rotateR = fR*0.4;
                
                if (distances[d]<fR){
                    customParticles[i].get()->addRepulsionForce(forcePosition, repulF*0.5);}
            }
        }
        
        
//        if (customParticles[i].get()->getVelocity() == ofVec2f(0,0)) {
//            customParticles.erase(customParticles.begin()+i);
//        }
//        
//        if (customParticles[i].get()->getPosition().y < RM->getRectForScreen(SCREEN_CENTER).y) {
//            customParticles.erase(customParticles.begin()+i);
//        }

    }
    
    for(int i=customParticles.size()-1; i>=0; i--) {
        if (customParticles[i].get()->getPosition().y < RM->getRectForScreen(SCREEN_CENTER).y) {
            customParticles.erase(customParticles.begin()+i);
        }
        
        if (customParticles[i].get()->getVelocity() == ofVec2f(0,0)) {
                        customParticles.erase(customParticles.begin()+i);
                    }

    }
    
}


//--------------------------------------------------------------

void box2dScene::drawObject(){
    
    for(int i=0; i<customParticles.size(); i++) {
        ofSetColor(255);
        customParticles[i].get()->draw(scale,trail);
    }
    
    
    ofNoFill();
    ofSetHexColor(0x444342);
    for (int i = 0; i<edges.size(); i++) {
        edges[i].updateShape();
        edges[i].draw();
    }
    
}


//--------------------------------------------------------------
void box2dScene::addObject(){
    
    for(int i = 0; i < 600; i ++){
        customParticles.push_back(shared_ptr<CustomParticle>(new CustomParticle));
        CustomParticle * p = customParticles.back().get();
        //        float r = ofRandom(size-1, size);
        p->setPhysics(density,bounce,friction);
        p->setup(box2d.getWorld(),ofRandom(w),ofRandom(RM->getRectForScreen(SCREEN_LEFT).y, RM->getRectForScreen(SCREEN_LEFT).y + 300),scale);
        
        p->color = 180;
        
    }
    
}


//--------------------------------------------------------------
void box2dScene::addBoxEdge(){
    float scale = RM->getWidth() / 2100;
   
    for (auto & window : RM->innerWindows){
        ofPolyline copy = window;
        ofxBox2dEdge temp;
        
        
        // resize it:
        
        for (auto & pt : copy){
            pt *= scale;
        }
        
        copy.flagHasChanged();
        copy.setClosed(true);
        
        temp.addVertexes(copy);
        edges.push_back(temp);
        windowsScaled.push_back(copy);
    }
    
    
//    for (auto & outerwindow : RM->outerWindows){
//        ofPolyline copy = outerwindow;
//        ofxBox2dEdge temp;
//        
//        // resize it:
//        
//        for (auto & pt : copy){
//            pt *= scale;
//        }
//        
//        copy.flagHasChanged();
//        copy.setClosed(true);
//        
//        temp.addVertexes(copy);
//        edges.push_back(temp);
//        outerWindowsScaled.push_back(copy);
//    }

//    for (auto & engravings : RM->engraving){
//        ofPolyline copy = engravings;
//        ofxBox2dEdge temp;
//        // resize it:
//        for (auto & pt : copy){
//            pt *= scale;
//        }
//        
//        copy.flagHasChanged();
//        copy.setClosed(true);
//        
//        temp.addVertexes(copy);
//        edges.push_back(temp);
//        engravingScaled.push_back(copy);
//    }
    
//    for (auto & pillars : RM->pillar){
//        ofPolyline copy = pillars;
//        ofxBox2dEdge temp;
//        // resize it:
//        for (auto & pt : copy){
//            pt *= scale;
//        }
//        
//        copy.flagHasChanged();
//        copy.setClosed(true);
//        
//        temp.addVertexes(copy);
//        edges.push_back(temp);
//        pillarScaled.push_back(copy);
//    }
    
    for (auto & edge : RM->edges){
        ofPolyline copy = edge;
        ofxBox2dEdge temp;
        // resize it:
        for (auto & pt : copy){
            pt *= scale;
        }
        
        copy.flagHasChanged();
        copy.setClosed(true);
        
        temp.addVertexes(copy);
        edges.push_back(temp);
        edgesScaled.push_back(copy);
    }
    
}

//--------------------------------------------------------------
void box2dScene::guiDtl(){
    gui.setup("BOX2D PANEL");
    gui.setPosition(80,50);
    gui.add(gravityV.set("Vertical Gravity",0.04,-5,5));
    gui.add(gravityH.set("Horizontal Gravity",0.01,-5,5));
    gui.add(damping.set("Damping",1.0,0.9,1.2));
    gui.add(density.set("Density",3.16,1.0,5.0));
    gui.add(bounce.set("Bounce",0.3,0.0,0.6));
    gui.add(friction.set("Friction",0.1,0.0,1.2));
    gui.add(size.set("Circle Size", 4, 0,8));
    gui.add(rDis.set("Radius", 80, 40, 180));
    
    
    forcePanel.setup("FORCE PANEL");
    forcePanel.setPosition(80,200);
    forcePanel.add(forceNum.set("Force Number", 7,1,forceN));
    forcePanel.add(angleVel.set("Angle Vel", 0.027,0,0.1));
    forcePanel.add(amplitude.set("Amplitude", 155,80,180));
    forcePanel.add(xVel.set("xVel", 1.0,0,5.0));
    forcePanel.add(drawforce.set("Draw Force",false));
    forcePanel.add(mouseforce.set("Mouse Force",false));
    forcePanel.add(forceR.set("Force Radius",133,100,250));
    forcePanel.add(repulF.set("Repulsion Force",-0.24,-1,1));
    forcePanel.add(scale.set("Object Size",0.7,0,6));
    forcePanel.add(trail.set("Trail Length",40,0,100));
}


//--------------------------------------------------------------
void box2dScene::drawGui(){
    
    gui.draw();
    forcePanel.draw();
}
