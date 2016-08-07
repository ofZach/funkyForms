

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
    
    typedef struct {
        int label;
        ofPoint pos;
    } centerppp;
    
    vector < centerppp > centers;
    
    
    for(int i = 0; i < contourFinder.size(); i++) {
        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
        ofPushMatrix();
        ofTranslate(center.x, center.y);
        int label = contourFinder.getLabel(i);
        string msg = ofToString(label) + ":" + ofToString(tracker.getAge(label));
        //ofDrawBitmapString(msg, 0, 0);
        ofVec2f velocity = ofxCv::toOf(contourFinder.getVelocity(i));
        ofScale(5, 5);
        
        ofPopMatrix();
        
        trackedContours[ label ].update(contourFinder.getPolyline(i));
        
        centerppp cent;
        cent.label = contourFinder.getLabel(i);
        cent.pos = center;
        centers.push_back(cent);
        
//        for (int j = 0; j < trackedContours[label].resampleSmoothed.size(); j++){
//            
//            //ofPoint diff =  trackedContours[label].velPts[j];
////            //if (diff.length() > ofGetMouseX()*0.1){
////            float angle = atan2(diff.y, diff.x);
////            ofColor c;
////            c.setHsb(ofMap(angle, -PI, PI, 0, 255), 255,255);
////            ofSetColor(c);
////            ofLine(trackedContours[label].resampleSmoothed[j], trackedContours[label].resampleSmoothed[j] + trackedContours[label].velPts[j] * 20);
////            ofCircle( trackedContours[label].resampleSmoothed[j], 3);
////            
//        }
        
        ofSetColor(255);
        ofLine(contourFinder.getPolyline(i).getCentroid2D(), contourFinder.getPolyline(i).getCentroid2D() + trackedContours[label].velAvgSmooth * 50);
        
        ofDrawBitmapStringHighlight(ofToString(cent.label), contourFinder.getPolyline(i).getCentroid2D() + ofPoint(0,30), ofColor::darkCyan, ofColor::white);
        //}
    }


//std::sort(centers.begin(), centers.end(), [](centerppp a, centerppp b){ return a.pos.x < b.pos.x; });

//
//if (centers.size() > 1){
//    
//    ofPolyline lines[100];
//  
//    
//    for (int i = 0; i < centers.size(); i++){
//        int who1 = centers[i].label;
//        //int who2 = centers[i+1].label;
//        
//        for (int j = 0; j < 100; j++){
//            lines[j].addVertex( trackedContours[who1].resampleSmoothed[j]);
//            
//            //ofLine( trackedContours[who1].resampleSmoothed[j],
//              //     trackedContours[who2].resampleSmoothed[j]);
//            
//        }
//        
//    }
//    for (int i = 0; i < 100; i++){
//        lines[i] = lines[i].getResampledBySpacing(10);
//        for (int z = 0; z < 10; z++){
//            lines[i] = lines[i].getSmoothed(3);
//        }
//        lines[i].draw();
//    }
}
   
    
    
    
