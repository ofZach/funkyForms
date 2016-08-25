#include "buildingScene.h"


void buildingScene::setup(){
    
    sceneName = "buildingScene";
    
    
    
    for (auto & piece : RM->innerWindows){
        buildingPiece bp;
        pieces.push_back(bp);
        pieces.back().bWindow = true;
        
        pieces.back().line = piece;
        pieces.back().length = piece.getPerimeter();
        pieces.back().bounds = piece.getBoundingBox();
        pieces.back().centroid = piece.getCentroid2D();
        pieces.back().bIsLoop = (piece[0] - piece[piece.size()-1]).length() < 10 ? true : false;
    }
    
    for (auto & piece : RM->pillar){
        buildingPiece bp;
        pieces.push_back(bp);
        pieces.back().bWindow = false;
        
        pieces.back().line = piece;
        pieces.back().length = piece.getPerimeter();
        pieces.back().bounds = piece.getBoundingBox();
        pieces.back().centroid = piece.getCentroid2D();
        pieces.back().bIsLoop = (piece[0] - piece[piece.size()-1]).length() < 10 ? true : false;
    }
    
    for (auto & piece : RM->edges){
        buildingPiece bp;
        pieces.push_back(bp);
        pieces.back().bWindow = false;
        
        pieces.back().line = piece;
        pieces.back().length = piece.getPerimeter();
        pieces.back().bounds = piece.getBoundingBox();
        pieces.back().centroid = piece.getCentroid2D();
        pieces.back().bIsLoop = (piece[0] - piece[piece.size()-1]).length() < 10 ? true : false;
    }
    
    for (int i = 0; i < pieces.size(); i++){
        tracer.push_back(0);
    }
}

void buildingScene::update(){
    
    for (int i = 0; i < pieces.size(); i++){
        tracer[i] += pieces[i].length*0.005;
    }
    
}




void buildingScene::draw(){
    
    
    for (auto & piece : pieces){
       // piece.line.draw();
    }
    
    
    
    
    // tracers
    
      vector < ofPoint > trackerPts;
    
    for (int i = 0; i < pieces.size(); i++){
        
        int howMany = 5 + 5 * sin(ofGetElapsedTimef() + i * 0.01);
        
        for (int j = 0; j < howMany; j++){
            
            ofMesh m;
            m.setMode(OF_PRIMITIVE_LINE_STRIP);
            
            for (int k = 0; k < 10; k++){
            
                float pct = ofMap(k, 0, 10, 1, 0);
                float len = pieces[i].length;
                float pos = fmod(tracer[i] + len/10.0 * j - k * len*0.005, len);
                
                if (k == 0 && j % 3 == 0) trackerPts.push_back(pieces[i].line.getPointAtLength(pos));
                m.addVertex(pieces[i].line.getPointAtLength(pos));
                m.addColor(ofColor(255,255,255,255*pct));
                ofPoint circlePos = pieces[i].line.getPointAtLength(pos);
            }
            m.draw();
            //ofCircle(circlePos, 1);
        }
    }
    
    
//    
//    // cob web effect:
//    
//    for (int i = 0; i < trackerPts.size(); i++){
//        float minDist = 10000000;
//        int index = -1;
//        for (int j = 0; j < i; j++){
//            float dist = (trackerPts[i] - trackerPts[j]).length();
//            if (dist < 100){
//                ofLine(trackerPts[i], trackerPts[j]);
//            }
//        }
//        
//    }
//    
//    ofPoint center = RM->getRectForScreen(SCREEN_CENTER).getCenter();
//    
//    for (int i = 0; i < pieces.size(); i++){
//        
//        
//        if (pieces[i].bWindow == true){
//        
//            ofPolyline tempLine = pieces[i].line;
//            float dist = (center - pieces[i].centroid).length();
//            float scale = ofMap(sin(ofGetElapsedTimef()*10 - dist * 0.01), -1, 1, 1, 5.0);
//            
//            for (auto & pt : tempLine){
//            //pt -= pieces[i].centroid;
//            //pt *= scale;
//            //pt += pieces[i].centroid;
//        }
//            tempLine.draw();
//        }
//        
//    }
    
//    
//    ofPoint center = RM->getRectForScreen(SCREEN_CENTER).getCenter();
//    ofPoint offset = ofPoint(ofGetWidth()*0.5, ofGetHeight()*0.5) - ofPoint(ofGetMouseX(), ofGetMouseY());
//    
//    
//    for (int i = 0; i < pieces.size(); i++){
//        
//        float dist = ( ofPoint(ofGetMouseX(), ofGetMouseY())*1.4 - pieces[i].centroid).length();
//        float scale = sin(center.x * 0.01 + ofGetElapsedTimef()) * 0.5 + 0.5; //ofMap(dist, 0, 800, 3.0, 0.0, true);
//        
//        // from moust!
//        offset = ofPoint(pieces[i].centroid) - ofPoint(ofGetMouseX(), ofGetMouseY())*1.4;
//        
//        if (pieces[i].bWindow == true){
//            
//            ofPolyline tempLine = pieces[i].line;
//            
//            ofPoint offsetScaled = offset.getNormalized() * 200*scale;
//            for (auto & pt : tempLine){
//                pt += offsetScaled;
//            }
//            tempLine.flagHasChanged();
//            ofPoint centroid = tempLine.getCentroid2D();
//            for (auto & pt : tempLine){
//                pt -= centroid;
//                //pt *= scale;
//                pt += centroid;
//
//            }
//            
//            
//            tempLine.draw();
//            //pieces[i].line.draw();
//            for (int j = 0; j < tempLine.size(); j++){
//                ofLine(tempLine[j], pieces[i].line[j]);
//            }
//        }
//        
//    }
//    
    
    
    
    
}


void buildingScene::blobBorn(int packetId, int id){
    
   
}

void buildingScene::blobDied(int packetId, int id){
    
}


void buildingScene::start(){
    
}

void buildingScene::stop(){
    
    
}
