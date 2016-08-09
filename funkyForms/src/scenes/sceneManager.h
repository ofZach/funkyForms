


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
    
    void blobBorn(int id);
    void blobDied(int id);
    
    int currentScene;
    
    void advanceScene(){
        currentScene ++;
        currentScene %= scenes.size();
    }
    void reverseScene();
    
};


