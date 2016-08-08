//
//  plantsScene.cpp
//  funkyForms
//
//  Created by Gordey on 8/8/16.
//
//

#include "plantsScene.hpp"
void plantsScene::setup(){
    plantManager.setup();
}
void plantsScene::update(){
    plantManager.update();
}
void plantsScene::draw(){
    plantManager.draw();
}
void plantsScene::blobBorn(int id){
}
void plantsScene::blobDied(int id){
}
void plantsScene::start(){
}
void plantsScene::stop(){
}