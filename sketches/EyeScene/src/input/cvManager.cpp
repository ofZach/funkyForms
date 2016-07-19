

#include "cvManager.h"



void cvManager::setup(){
    contourFinder.setMinAreaRadius(10);
    contourFinder.setMaxAreaRadius(200);
    contourFinder.setSortBySize(true);
    contourFinder.setInvert(true);
    contourFinder.getTracker().setPersistence(15);
    contourFinder.getTracker().setMaximumDistance(100);
    
}

void cvManager::update(ofPixels & pixels){
    
        contourFinder.setThreshold(115);
        contourFinder.findContours(pixels);
  
    
   
    
}

void cvManager::draw(){
    ofSetColor(ofColor::grey);
    contourFinder.draw();
    
    ofxCv::RectTracker& tracker = contourFinder.getTracker();

    
    for(int i = 0; i < contourFinder.size(); i++) {
        
        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
        ofPushMatrix();
        ofTranslate(center.x, center.y);
        int label = contourFinder.getLabel(i);
        string msg = ofToString(label) + ":" + ofToString(tracker.getAge(label));
        ofVec2f velocity = ofxCv::toOf(contourFinder.getVelocity(i));

        ofSetColor(ofColor::white);
//        ofDrawBitmapString(msg, 0, 0);

        ofScale(5, 5);
        ofSetColor(ofColor::yellow);
        ofDrawLine(0, 0, velocity.x, velocity.y);
        
        ofPopMatrix();
    }
}