#include "costumeScene.h"


void costumeScene::setup(){
    
    sceneName = "costumeScene";
    
    
    
}

void costumeScene::update(){
    
   
}

void costumeScene::draw(){
    
      
    
}


void costumeScene::blobBorn(int packetId, int id){
  
    trackedContourObj obj;
    trackedObjects.push_back(obj);
    trackedObjects.back().id = id;
    trackedObjects.back().packetId = packetId;
    trackedObjects.back().id = id;
    trackedObjects.back().TC = new trackedContour();
    
}

void costumeScene::blobDied(int packetId, int id){
 
    
    for(int i=trackedObjects.size()-1; i>=0; i--) {
        if (trackedObjects[i].id == id &&
            trackedObjects[i].packetId == packetId){
            
        }
    }
    

}


void costumeScene::start(){
    // I am starting, show a gui
}

void costumeScene::stop(){
    // I am stopping, hide a gui
}
