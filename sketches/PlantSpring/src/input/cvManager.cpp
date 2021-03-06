

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
    updateTracked();
}
void cvManager::updateTracked(){
    
    ofxCv::RectTracker& tracker = contourFinder.getTracker();
//    for(auto &c: trackedContours){
//        int label = c.first;
//        if(tracker.existsPrevious(label)){
//            ofLog() << "exist : " <<  label;
//        }else{
//            ofLog() << "not exist : " <<  label;
//            trackedContours.erase(label);
//        }
//    }

    for(int i = 0; i < contourFinder.size(); i++) {
        int label = contourFinder.getLabel(i);
        trackedContours[ label ].update(contourFinder.getPolyline(i));
    }
    
    // clear unused countours
    std::map<int, trackedContour>::iterator itr = trackedContours.begin();
    while (itr != trackedContours.end()) {
        int label = itr->first;
        if (!tracker.existsCurrent(label)) {
            itr = trackedContours.erase(itr);
        } else {
            ++itr;
        }
    }
}
void cvManager::drawPeopleFill(){
    for (int i = 0; i < contourFinder.getPolylines().size(); i++) {
        ofPolyline &l = contourFinder.getPolyline(i);
        ofPath path;
        int res = ofMap(l.getPerimeter(), 0, 1900, 1, 200);
        for (float i = 0; i < 1.; i += 1.0/res) {
            path.lineTo(l.getPointAtPercent(i));
        }
        path.setFillColor(ofColor::gray);
        path.draw();
    }
}
void cvManager::draw(){
    contourFinder.draw();
    
    ofxCv::RectTracker& tracker = contourFinder.getTracker();
    

    for(int i = 0; i < contourFinder.size(); i++) {
        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
        ofPushMatrix();
        ofTranslate(center.x, center.y);
        int label = contourFinder.getLabel(i);
        
        tracker.existsCurrent(label);
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