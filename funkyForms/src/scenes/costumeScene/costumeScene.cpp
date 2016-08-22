#include "costumeScene.h"


void costumeScene::setup(){
    
    sceneName = "costumeScene";
    
    
    
}

void costumeScene::update(){
    
    for (int packetId = 0; packetId < 2; packetId++){
        for (int i = 0; i < cvData[packetId]->blobs.size(); i++){
            
            int id = cvData[packetId]->blobs[i].id;
            bool bAssociated = false;
            
            //------------------------------------------ check....
            for (auto & to : trackedObjects){
                
                if (to.id == id &&
                    to.packetId == packetId){
                    
                    
                    ofPolyline line = cvData[packetId]->blobs[i].blob;
                    
                    for (auto & pt : line){
                        pt = cvData[packetId]->remapForScreen(packetId == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
                    }
                    line.flagHasChanged();
                    to.TC->analyze(line);
                    bAssociated = true;
                }
            }
            //------------------------------------------ else jam
            
            if (!bAssociated){
                trackedContourObj obj;
                trackedObjects.push_back(obj);
                trackedObjects.back().id = id;
                trackedObjects.back().packetId = packetId;
                trackedObjects.back().id = id;
                trackedObjects.back().TC = new trackedContour();
                ofPolyline line = cvData[packetId]->blobs[i].blob;
                for (auto & pt : line){
                    pt = cvData[packetId]->remapForScreen(packetId == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
                }
                line.flagHasChanged();
                trackedObjects.back().TC->analyze(line);
            }
        }
    }
    
    
    // try to update!
    
    for (auto & to : trackedObjects){
        to.TC->update();
        to.TC->smoothingRate = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 1, true);
    }
    
    for (auto & to : trackedObjects){
        if (to.TC->data.resampleSmoothed.size() > 0){
            to.update(to.TC->data.resampleSmoothed);
        }
    }
    
}

void costumeScene::draw(){
    
//    for (auto & to : trackedObjects){
//        if (to.TC->data.resampleSmoothed.size() > 0){
//            
//            float alpha = ofMap(ofGetElapsedTimef() - to.TC->startTime, 1, 3, 0, 255, true);
//            ofSetColor(255, 255, 255, alpha);
//            
//            to.TC->data.resampleSmoothed.draw();
//            
//            ofPolyline tempLine = to.TC->data.resampleSmoothed;
//            //tempLine = tempLine.getResampledBySpacing(5);
//            
//            for (int i = 0; i < tempLine.size(); i++){
//                
//                ofPoint a = tempLine[i];
//                ofPoint b = tempLine[(i + 3) % tempLine.size() ];
//                ofPoint midPt = (a+b)/2.0;
//                ofPoint diff = (b-a);
//                diff.rotate(90, ofPoint(0,0,1));
//                float radius = (a-b).length()*0.5;
//                ofNoFill();
//                ofLine(midPt, midPt + diff * 1);
//            }
//            
//        }
//        
//    }
    
    for (auto & to : trackedObjects){
        float alpha = ofMap(ofGetElapsedTimef() - to.TC->startTime, 0.8, 2.1, 0, 1, true);
            to.draw(alpha);
        
    }
    
}


void costumeScene::blobBorn(int packetId, int id){
    
    ofPoint pt = cvData[packetId]->blobs[cvData[packetId]->idToBlobPos[id]].blob.getCentroid2D();
    
    pt = cvData[packetId]->remapForScreen(packetId == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
    
    trackedContourObj obj;
    trackedObjects.push_back(obj);
    trackedObjects.back().id = id;
    trackedObjects.back().packetId = packetId;
    trackedObjects.back().id = id;
    trackedObjects.back().TC = new trackedContour();
    trackedObjects.back().setup(pt);
}

void costumeScene::blobDied(int packetId, int id){
    for(int i=trackedObjects.size()-1; i>=0; i--) {
        if (trackedObjects[i].id == id &&
            trackedObjects[i].packetId == packetId){
            delete trackedObjects[i].TC;
            trackedObjects.erase(trackedObjects.begin() + i);
        }
    }
}


void costumeScene::start(){
    // I am starting, show a gui
}

void costumeScene::stop(){
    // I am stopping, hide a gui
    
    for(int i=trackedObjects.size()-1; i>=0; i--) {
        delete trackedObjects[i].TC;
        trackedObjects.erase(trackedObjects.begin() + i);
    }
    
    
    
}
