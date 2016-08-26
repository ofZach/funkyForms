


#pragma once


#include "ofMain.h"
#include "baseScene.h"

class sceneManager {
    
    
public:
    
    vector < baseScene * > scenes;
   
    sceneManager();
    
    void setup();
    void update();
    void draw();
    void drawGui();
    
    void blobBorn(int packetId, int id);
    void blobDied(int packetId, int id);
    void blobMoved(int packetId, int id);
    
    int currentScene;
    
    void goToScene(int scene){
        scenes[currentScene]->stop();
        currentScene = scene;
        currentScene %= scenes.size();
        scenes[currentScene]->start();
    }
    
    void advanceScene(){
        scenes[currentScene]->stop();   // hide gui,etc
        currentScene ++;
        currentScene %= scenes.size();
        scenes[currentScene]->start();
    }
    void reverseScene(){
        scenes[currentScene]->stop();   // hide gui,etc
        currentScene --;
        if (currentScene < 0){
            currentScene += scenes.size();
        }
        scenes[currentScene]->start();
        
    }
    
};


