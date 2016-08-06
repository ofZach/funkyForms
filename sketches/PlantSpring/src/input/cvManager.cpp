

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
    contourFinder.draw();
    
    ofxCv::RectTracker& tracker = contourFinder.getTracker();
    
    for(int i = 0; i < contourFinder.size(); i++) {
        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
        ofPushMatrix();
        ofTranslate(center.x, center.y);
        int label = contourFinder.getLabel(i);
        string msg = ofToString(label) + ":" + ofToString(tracker.getAge(label));
        //ofDrawBitmapString(msg, 0, 0);
        ofVec2f velocity = ofxCv::toOf(contourFinder.getVelocity(i));
        ofScale(5, 5);
        //ofDrawLine(0, 0, velocity.x, velocity.y);
        ofPopMatrix();
        
        trackedContours[ label ].update(contourFinder.getPolyline(i));
        
        for (int j = 0; j < trackedContours[label].resampleSmoothed.size(); j++){
            
            ofPoint diff =  trackedContours[label].velPts[j];
            float angle = atan2(diff.y, diff.x);
            ofColor c;
            c.setHsb(ofMap(angle, -PI, PI, 0, 255), 255,255);
            ofSetColor(c);
         //   ofLine(trackedContours[label].resampleSmoothed[j], trackedContours[label].resampleSmoothed[j] + trackedContours[label].velPts[j] * 20);
            //ofCircle( trackedContours[label].resampleSmoothed[j], 3);
            
        }
        
        ofSetColor(255);
        ofLine(contourFinder.getPolyline(i).getCentroid2D(), contourFinder.getPolyline(i).getCentroid2D() + trackedContours[label].velAvgSmooth * 50);
        
        
    }
}