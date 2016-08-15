


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
    
    void blobBorn(int id);
    void blobDied(int id);
    void blobMoved(int id);
    
    int currentScene;
    
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


