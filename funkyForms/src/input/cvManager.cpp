

#include "cvManager.h"



using namespace ofxCv;
using namespace cv;




void cvManager::setup(){

    
    tracker.setListener(this);
 
    packet.opticalFlow.resize(INPUT_WARP_TO_W*INPUT_WARP_TO_H);

    //packet.trackedContours = &trackedContours;
}


void cvManager::blobOn( int x, int y, int bid, int order ) {
   
    bornThisFrame.push_back(bid);
    
    //cout << "on " << bid << " " << order << endl;
    
}
void cvManager::blobMoved( int x, int y, int bid, int order ) {
    movedThisFrame.push_back(bid);
}

void cvManager::blobOff( int x, int y, int bid, int order ) {
    
    
    diedThisFrame.push_back(bid);
    
    auto itr = startTimes.begin();
    while (itr != startTimes.end()) {
        int label = itr->first;
        if (label == bid) {
            itr = startTimes.erase(itr);
        } else {
            ++itr;
        }
    }
    
    //cout << "off " << bid << " " << order << endl;
}



void cvManager::update(ofPixels & pixels){

    
   // why do we have color here?
    //frame.currentFrame = pixels;
    frame.currentFrame = pixels;
    frame.currentFrame.setImageType(OF_IMAGE_GRAYSCALE);
    
    if (OFT.bInSomething == false){
        OFT.analyze(frame);
    }
    OFT.update();
    
    
    if (OFT.resultSmooth.flow.size() > 0){
        packet.opticalFlow = OFT.resultSmooth.flow;  // this has a bit of temporal smoothing...
    }
    
    bornThisFrame.clear();
    diedThisFrame.clear();
    movedThisFrame.clear();
    existThisFrame.clear();
    
    
     
    for (int i = 0; i < packet.blobs.size(); i++){
        prevPacketVelSmooth[packet.blobs[i].id] = packet.blobs[i].avgVelSmoothed;
        prevPacketCentroidSmooth[packet.blobs[i].id] = packet.blobs[i].centroidSmoothed;
    }
    
    packet.blobs.clear();
    packet.idsThisFrame.clear();
    packet.idToBlobPos.clear();


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

    tracker.trackBlobs(blobs);
    
    for (int i = 0; i < tracker.blobs.size(); i++){
        ofPolyline line(tracker.blobs[i].pts);
        
        
        cvBlob blob;
        blob.blob = line;
        blob.id = tracker.blobs[i].id;
        
        auto stIt = startTimes.find(blob.id);
        if (stIt != startTimes.end()){
            blob.age = ofGetElapsedTimef() - startTimes[ tracker.blobs[i].id ];
        } else {
            startTimes[blob.id] = ofGetElapsedTimef();
        }
        
        for (auto & pt : line){
            blob.vel.addVertex( OFT.getFlowForPt(pt.x, pt.y));
        }
        
        ofPoint avgVel;
        for (int j = 0; j < blob.blob.size(); j++){
            avgVel += blob.vel[j];
        }
        
        avgVel /= (float)max((int)blob.blob.size(), 1);
        
        blob.avgVel = avgVel;
        
        auto it = prevPacketVelSmooth.find(blob.id);
        if (it != prevPacketVelSmooth.end()){
            blob.avgVelSmoothed = 0.98f * it->second + 0.02 * blob.avgVel;
        } else {
            blob.avgVelSmoothed = blob.avgVel;
        }
        
        auto it2 = prevPacketCentroidSmooth.find(blob.id);
        if (it2 != prevPacketCentroidSmooth.end()){
            blob.centroidSmoothed = 0.98f * it2->second + 0.02 * blob.blob.getCentroid2D();
        } else {
            blob.centroidSmoothed = blob.blob.getCentroid2D();

        }
    
        packet.blobs.push_back(blob);
        packet.idsThisFrame.push_back(blob.id);
        packet.idToBlobPos[blob.id] = i;
        
        //startTimes[ tracker.blobs[i].id ].analyze(line);
        //startTimes[ tracker.blobs[i].id ].update();
    }
    
    packet.width = INPUT_WARP_TO_W;
    packet.height = INPUT_WARP_TO_H;
    

    
}

void cvManager::draw(){
    

    
    ofPushMatrix();
    finder.draw();
    
    for (auto & blob : packet.blobs){
        
        for (int i = 0; i < blob.blob.size(); i++){
            
            ofPoint pt = blob.blob[i];
            ofPoint vel = blob.vel[i];
            
            ofLine(pt, pt+vel);
            
        }
    }
    

    
    // this is slow but helpful for seeing the optical flow. 
    //OFT.draw(0,0);

    ofPopMatrix();

}

    
    
    
