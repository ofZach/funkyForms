

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
 
    
    
    
    gui.setup();
    
    gui.add(lkMaxLevel.set("lkMaxLevel", 3, 0, 8));
    gui.add(lkMaxFeatures.set("lkMaxFeatures", 200, 1, 1000));
    gui.add(lkQualityLevel.set("lkQualityLevel", 0.01, 0.001, .02));
    gui.add(lkMinDistance.set("lkMinDistance", 4, 1, 16));
    gui.add(lkWinSize.set("lkWinSize", 8, 4, 64));
    gui.add(usefb.set("Use Farneback", true));
    gui.add(fbPyrScale.set("fbPyrScale", .5, 0, .99));
    gui.add(fbLevels.set("fbLevels", 4, 1, 8));
    gui.add(fbIterations.set("fbIterations", 2, 1, 8));
    gui.add(fbPolyN.set("fbPolyN", 7, 5, 10));
    gui.add(fbPolySigma.set("fbPolySigma", 1.5, 1.1, 2));
    gui.add(fbUseGaussian.set("fbUseGaussian", false));
    gui.add(fbWinSize.set("winSize", 32, 4, 64));
    
    
    
    curFlow = &fb;
    
    
     packet.trackedContours = &trackedContours;
}


#ifdef USE_OLDER_BLOB_TRACKER

void cvManager::blobOn( int x, int y, int bid, int order ) {
   
    bornThisFrame.push_back(bid);
    
    //cout << "on " << bid << " " << order << endl;
    
}
void cvManager::blobMoved( int x, int y, int bid, int order ) {
    movedThisFrame.push_back(bid);
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



void cvManager::update(ofPixels & pixels){
    
    
//    if(usefb) {
//        curFlow = &fb;
//        fb.setPyramidScale(fbPyrScale);
//        fb.setNumLevels(fbLevels);
//        fb.setWindowSize(fbWinSize);
//        fb.setNumIterations(fbIterations);
//        fb.setPolyN(fbPolyN);
//        fb.setPolySigma(fbPolySigma);
//        fb.setUseGaussian(fbUseGaussian);
//    } else {
//        curFlow = &lk;
//        lk.setMaxFeatures(lkMaxFeatures);
//        lk.setQualityLevel(lkQualityLevel);
//        lk.setMinDistance(lkMinDistance);
//        lk.setWindowSize(lkWinSize);
//        lk.setMaxLevel(lkMaxLevel);
//    }
//    
//    // you can use Flow polymorphically
//    curFlow->calcOpticalFlow(pixels);
    
    
    
    bornThisFrame.clear();
    diedThisFrame.clear();
    movedThisFrame.clear();
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
    
    
    
    
    
    
    finder.findContours(imgGray, 300, 10000000, 20, false);
    
    
    vector<ofxCvBlob> blobs = finder.blobs;
    
//    for (auto & a : blobs){
//        
//        a.centroid = mapPt(inputRect, inputRectScaled, a.centroid);
//        
//        for (auto & b : a.pts){
//            b = mapPt(inputRect, inputRectScaled, b);
//        }
//    
//    }
    
    tracker.trackBlobs(blobs);
    
    for (int i = 0; i < tracker.blobs.size(); i++){
        ofPolyline line(tracker.blobs[i].pts);
        
        cvBlob blob;
        blob.blob = line;
        blob.id = tracker.blobs[i].id;
        blob.age = ofGetElapsedTimef() - trackedContours[ tracker.blobs[i].id ].startTime;
        
        packet.blobs.push_back(blob);
        packet.idsThisFrame.push_back(blob.id);
        packet.idToBlobPos[blob.id] = i;
        
        trackedContours[ tracker.blobs[i].id ].analyze(line);
        trackedContours[ tracker.blobs[i].id ].update();
    }
    
    packet.width = INPUT_WARP_TO_W;
    packet.height = INPUT_WARP_TO_H;
    
    

    
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
    
    
    for (auto it=trackedContours.begin(); it!=trackedContours.end(); ++it){
        it->second.data.resampleSmoothed.draw();
        string str = ofToString(it->first);
        if (it->second.data.resampleSmoothed.size() > 0){
            ofDrawBitmapString(str, it->second.data.resampleSmoothed[0].x, it->second.data.resampleSmoothed[0].y);
        }
    }
    
    //curFlow->draw(0,0);
    
    gui.draw();
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

    
    
    
