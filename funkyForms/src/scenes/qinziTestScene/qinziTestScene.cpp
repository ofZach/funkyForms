#include "qinziTestScene.h"


void qinziTestScene::setup(){
    sceneName = "qinziTestScene";
    
    
    for (auto & window : RM->innerWindows){
        ofPolyline copy = window;
        
        // resize it:
        
        float scale = RM->getWidth() / 2100;
        
        for (auto & pt : copy){
            pt *= scale;
        }
        
        copy.flagHasChanged();
        copy.setClosed(true);
        windowsScaled.push_back(copy);
        
    }
    
}

void qinziTestScene::update(){
    
    
    
   
}

void qinziTestScene::draw(){
    
    
    ofRect(0,0,100,100);
    
    for (int i = 0; i < windowsScaled.size(); i++){
        windowsScaled[i].draw();
    }
    
    
    
}


void qinziTestScene::blobBorn(int packetId, int id){
    

}

void qinziTestScene::blobDied(int packetId, int id){
 
  
}


void qinziTestScene::start(){
    // I am starting, show a gui
}

void qinziTestScene::stop(){
    // I am stopping, hide a gui
}
