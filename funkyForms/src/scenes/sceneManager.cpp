#include "sceneManager.h"



sceneManager::sceneManager(){
    currentScene = 0;
}


void sceneManager::setup(){
    for (int i = 0; i < scenes.size(); i++){
        scenes[i]->setup();
    }
}

void sceneManager::update(){
    scenes[currentScene]->update();
}

void sceneManager::draw(){
    scenes[currentScene]->draw();
}

void sceneManager::blobBorn(int id){
    scenes[currentScene]->blobBorn(id);
}

void sceneManager::blobDied(int id){
    scenes[currentScene]->blobDied(id);

}