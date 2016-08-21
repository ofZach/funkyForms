#include "simpleScene2.h"


void simpleScene2::setup(){
    
    sceneName = "simpleScene2";
    
    
    
}

void simpleScene2::update(){
    
    
    if (ofRandom(0.0,1.0) > 0.8){
        
        ofRectangle rect = RM->getRectForScreen(SCREEN_TOP);
        float yPct = 0.1;
        float xPct = 0.5 + ofRandom(-0.5, 0.5);
        ofPoint pos = ofPoint( rect.x + xPct * rect.width, rect.y + yPct * rect.height);
        
        particle tempParticle;
        tempParticle.setInitialCondition(pos.x, pos.y, 0, 0); //, <#float py#>, <#float vx#>, <#float vy#>)
        particles.push_back(tempParticle);
    }
    
    
    ofRectangle bottomScreen = RM->getRectForScreen(SCREEN_CENTER);
    ofRectangle leftScreen = RM->getRectForScreen(SCREEN_LEFT);
    ofRectangle rightScreen = RM->getRectForScreen(SCREEN_RIGHT);
    
    float time = ofGetElapsedTimef();
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].resetForce();
        particles[i].addDampingForce();
        
        if (!leftScreen.inside(particles[i].pos)
            && !rightScreen.inside(particles[i].pos)){
            particles[i].addForce(0,0.4);
        }
        
        
        float positionOffset = sin(time) * bottomScreen.getHeight() * 0.1;
        float horizOffset = sin(time * 0.6) * bottomScreen.getHeight() * 0.05;
        
        float sizeOffset = sin(time * 0.7) * bottomScreen.getHeight() * 0.2;

        particles[i].addRepulsionForce(bottomScreen.x + bottomScreen.width/2 + horizOffset, bottomScreen.y+bottomScreen.height + positionOffset, bottomScreen.getWidth() + sizeOffset, 1.5);
        
        
 
    }
    
    
    
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].update();
    }
    

}

void simpleScene2::draw(){
    
    
    float time = ofGetElapsedTimef();
    
    for (int i = 0; i < particles.size(); i++){
        ofFill();
        ofCircle(particles[i].pos, 2); //draw();
        
    }
    
    
    ofRectangle bottomScreen = RM->getRectForScreen(SCREEN_CENTER);
    ofRectangle leftScreen = RM->getRectForScreen(SCREEN_LEFT);
    ofRectangle rightScreen = RM->getRectForScreen(SCREEN_RIGHT);
  
    float positionOffset = sin(time) * bottomScreen.getHeight() * 0.1;
    float sizeOffset = sin(time * 0.7) * bottomScreen.getHeight() * 0.2;
    float horizOffset = sin(time * 0.6) * bottomScreen.getHeight() * 0.05;
    
    ofNoFill();
    ofSetColor(255,0,0);
    ofCircle(bottomScreen.x + bottomScreen.width/2 + horizOffset, bottomScreen.y+bottomScreen.height + positionOffset, bottomScreen.getWidth() + sizeOffset);
    
  
    
}


void simpleScene2::blobBorn(int packetId, int id){
  
}

void simpleScene2::blobDied(int packetId, int id){
 
    

}


void simpleScene2::start(){
    // I am starting, show a gui
}

void simpleScene2::stop(){
    // I am stopping, hide a gui
}
