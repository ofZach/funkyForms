#include "simpleScene.h"


void simpleScene::setup(){
    sceneName = "simpleScene";
}

void simpleScene::update(){
    
    
    // erase particles that are 1 second old...
    
    
    particles.erase(
                    std::remove_if(
                                   particles.begin(),
                                   particles.end(),
                                   [&](bornParticle & i){return ((ofGetElapsedTimef() - i.age) > 1.0);}),
                    particles.end());
}

void simpleScene::draw(){
    
    ofDrawRectangle(0,0,100,100);
    
    ofSetColor(255);
    
    
    //---------------------------------------------------------  rempping
    // note:
    // rempap the contour data:
    // baseScene::mapPt takes an input rectangle, an output rectangle
    // and a pt and remaps the pt
    
    ofRectangle src(0,0,cvData->width, cvData->height);
    ofRectangle dst = src;
    ofRectangle target = RM->getRectForScreen(SCREEN_LEFT);
    dst.scaleTo(target);
    
    for (int i = 0; i < cvData->blobs.size(); i++){
        ofPolyline line = cvData->blobs[i].blob;
        for (auto & pt : line.getVertices()){
            pt = mapPt(src, dst, pt);
        }
        line.draw();
    }
    
    
    for (int i = 0; i < particles.size(); i++){
        int id = particles[i].id;
        float age = ofGetElapsedTimef() - particles[i].age;
        
        int whichBlob = cvData->idToBlobPos[id];
        
        ofPoint centroid = cvData->blobs[whichBlob].blob.getCentroid2D();
        
        centroid = mapPt(src, dst, centroid);
        
        ofNoFill();
        
        ofDrawBitmapStringHighlight( ofToString(id) + " " +  ofToString(age), centroid);
        
        ofCircle(centroid, age * 100);
    }
    
    
    
    
    
}


void simpleScene::blobBorn(int id){
    
    bornParticle p;
    p.id = id;
    p.age = ofGetElapsedTimef();
    particles.push_back(p);
}

void simpleScene::blobDied(int id){
 
    
    
    particles.erase(
                   std::remove_if(
                                  particles.begin(),
                                  particles.end(),
                                  [&](bornParticle & i){return i.id == id;}),
                   particles.end());
}


void simpleScene::start(){
    // I am starting, show a gui
}

void simpleScene::stop(){
    // I am stopping, hide a gui
}
