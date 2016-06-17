

#include "cvManager.h"



void cvManager::setup(){
    contourFinder.setMinAreaRadius(10);
    contourFinder.setMaxAreaRadius(200);
    contourFinder.setSortBySize(true);
    contourFinder.setInvert(true);
    
    
}

void cvManager::update(ofPixels & pixels){
    
        contourFinder.setThreshold(115);
        contourFinder.findContours(pixels);
    
    
}

void cvManager::draw(){
    contourFinder.draw();
}