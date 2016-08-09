

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
    

    ofxCv::RectTracker& tracker = contourFinder.getTracker();
    
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

void cvManager::draw(){
    contourFinder.draw();
    
    
    typedef struct {
        int label;
        ofPoint pos;
    } centerppp;
    
    vector < centerppp > centers;
    
    
    ofxCv::RectTracker& tracker = contourFinder.getTracker();
    
    
    for(int i = 0; i < contourFinder.size(); i++) {
        
        int label = contourFinder.getLabel(i);
        
        ofSetColor(255);
        ofLine(contourFinder.getPolyline(i).getCentroid2D(), contourFinder.getPolyline(i).getCentroid2D() + trackedContours[label].velAvgSmooth * 50);
        
        ofDrawBitmapStringHighlight(ofToString(label), contourFinder.getPolyline(i).getCentroid2D() + ofPoint(0,30), ofColor::darkMagenta, ofColor::white);
        
        ofDrawBitmapStringHighlight("age: " + ofToString(tracker.getAge(label)), contourFinder.getPolyline(i).getCentroid2D() + ofPoint(0,46), ofColor::darkCyan, ofColor::white);
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
   
    
    
    
