#include "sceneManager.h"



sceneManager::sceneManager(){
    currentScene = 0;
}


void sceneManager::setup(){
    for (int i = 0; i < scenes.size(); i++){
        scenes[i]->registerVideoSettings();
        scenes[i]->setup();
    }
}

void sceneManager::update(){
    scenes[currentScene]->update();
}


void sceneManager::draw(){
    scenes[currentScene]->draw();
}

void sceneManager::drawGui(){
    scenes[currentScene]->drawGui();
}

void sceneManager::blobBorn(int packetId, int id){
    scenes[currentScene]->blobBorn(packetId, id);
}

void sceneManager::blobDied(int packetId, int id){
    scenes[currentScene]->blobDied(packetId, id);
}

void sceneManager::blobMoved(int packetId, int id){
    scenes[currentScene]->blobMoved(packetId, id);
}