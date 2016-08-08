

#include "cvManager.h"



using namespace ofxCv;
using namespace cv;




void cvManager::setup(){
    
#ifndef USE_OLDER_BLOB_TRACKER
    contourFinder.setMinAreaRadius(10);
    contourFinder.setMaxAreaRadius(200);
    contourFinder.setSortBySize(true);
    contourFinder.setInvert(true);
    contourFinder.getTracker().setPersistence(15);
    contourFinder.getTracker().setMaximumDistance(100);
    
    
   
    
#else 
    
    tracker.setListener(this);

#endif
 
    
    
     packet.trackedContours = &trackedContours;
}


#ifdef USE_OLDER_BLOB_TRACKER

void cvManager::blobOn( int x, int y, int bid, int order ) {
   
    bornThisFrame.push_back(bid);
    
    //cout << "on " << bid << " " << order << endl;
    
}
void cvManager::blobMoved( int x, int y, int bid, int order ) {
    
}
void cvManager::blobOff( int x, int y, int bid, int order ) {
    
    
    diedThisFrame.push_back(bid);
    
    auto itr = trackedContours.begin();
    while (itr != trackedContours.end()) {
        int label = itr->first;
        if (label == bid) {
            itr = trackedContours.erase(itr);
        } else {
            ++itr;
        }
    }
    
    //cout << "off " << bid << " " << order << endl;
}

#endif


inline ofPoint mapPt(ofRectangle src, ofRectangle dst, ofPoint input){
    
    float newx = ofMap(input.x, src.x, src.x + src.getWidth(), dst.x, dst.x + dst.getWidth());
    float newy = ofMap(input.y, src.y, src.y + src.getHeight(), dst.y, dst.y + dst.getHeight());
    
    return ofPoint(newx, newy);
}

void cvManager::update(ofPixels & pixels){
    
    bornThisFrame.clear();
    diedThisFrame.clear();
    existThisFrame.clear();
    
    packet.blobs.clear();
    packet.idsThisFrame.clear();
    packet.idToBlobPos.clear();

    
#ifdef USE_OLDER_BLOB_TRACKER
    if (imgColor.getWidth() != pixels.getWidth()){
        imgColor.allocate(pixels.getWidth(), pixels.getHeight());
        imgGray.allocate(pixels.getWidth(), pixels.getHeight());
    }
    
    imgColor.setUseTexture(false);
    imgColor.setFromPixels(pixels);
    imgColor.flagImageChanged();
    
    imgGray.setUseTexture(false);
    imgGray = imgColor;
    imgGray.flagImageChanged();
    
    imgGray.invert();
    imgGray.threshold(255-115);
   // cout << ofGetMouseX() << endl;
    
    
    
    ofRectangle inputRect(0,0,INPUT_WARP_TO_W, INPUT_WARP_TO_H);
    ofRectangle inputRectScaled(0,0,INPUT_WARP_TO_W, INPUT_WARP_TO_H);
    ofRectangle targetRect(OUTPUT_TARGET_X, OUTPUT_TARGET_Y, OUTPUT_TARGET_W, OUTPUT_TARGET_H);
    
    inputRectScaled.scaleTo(targetRect);
    
    
    
    finder.findContours(imgGray, 300, 10000000, 20, false);
    
    
    vector<ofxCvBlob> blobs = finder.blobs;
    
    for (auto & a : blobs){
        
        a.centroid = mapPt(inputRect, inputRectScaled, a.centroid);
        
        for (auto & b : a.pts){
            b = mapPt(inputRect, inputRectScaled, b);
        }
    
    }
    
    tracker.trackBlobs(blobs);
    
    for (int i = 0; i < tracker.blobs.size(); i++){
        ofPolyline line(tracker.blobs[i].pts);
        trackedContours[ tracker.blobs[i].id ].update(line);
        
        cvBlob blob;
        blob.blob = line;
        blob.id = tracker.blobs[i].id;
        blob.age = ofGetElapsedTimef() - trackedContours[ tracker.blobs[i].id ].startTime;
        packet.blobs.push_back(blob);
        packet.idsThisFrame.push_back(blob.id);
        packet.idToBlobPos[blob.id] = i;
        
    }
    
    

    
#else
    
    contourFinder.setThreshold(115);
    contourFinder.findContours(pixels);
    
    ofxCv::RectTracker& tracker = contourFinder.getTracker();
    
    
    
    for(int i = 0; i < contourFinder.size(); i++) {
        int label = contourFinder.getLabel(i);
        
        auto foundMe = trackedContours.find(label);
        if (foundMe == trackedContours.end()){
            bornThisFrame.push_back(label);
        }
        trackedContours[ label ].update(contourFinder.getPolyline(i));
        
        cvBlob blob;
        blob.blob = contourFinder.getPolyline(i);
        blob.id = label;
        blob.age = ofGetElapsedTimef() - trackedContours[ label ].startTime;
        packet.blobs.push_back(blob);
        packet.idsThisFrame.push_back(label);
        packet.idToBlobPos[label] = packet.blobs.size()-1;      // id to pos
    }
    
    
//    for (int i = 0; i < tracker.getDeadLabels().size(); i++){
//        cout << "dead " << tracker.getDeadLabels()[i] << endl;
//        
//    }
    
    
    //tracker.getLastSeen(<#unsigned int label#>)
    
    auto itr = trackedContours.begin();
    while (itr != trackedContours.end()) {
        int label = itr->first;
        
        if (std::find(tracker.getDeadLabels().begin(), tracker.getDeadLabels().end(), label) != tracker.getDeadLabels().end()) {
            itr = trackedContours.erase(itr);
            diedThisFrame.push_back(label);
        } else {
            ++itr;
        }
    }
    
    

    // clear unused countours
//    auto itr = trackedContours.begin();
//    while (itr != trackedContours.end()) {
//        int label = itr->first;
//        
//        
//        if (!tracker.existsCurrent(label)) {
//            itr = trackedContours.erase(itr);
//            diedThisFrame.push_back(label);
//        } else {
//            ++itr;
//        }
//    }
    
    
    itr = trackedContours.begin();
    while (itr != trackedContours.end()) {
        int label = itr->first;
        existThisFrame.push_back(label);
        ++itr;
    }
    

    
#endif
    

    
}

void cvManager::draw(){
    

#ifdef USE_OLDER_BLOB_TRACKER
    
    ofPushMatrix();
    finder.draw();
    //ofTranslate(0,300);
    //tracker.draw(0, 0);
    ofPopMatrix();
#else
    
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
    

    
    
    
    //watershedResults.draw(0,0);


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
    
#endif
}

    
    
    
