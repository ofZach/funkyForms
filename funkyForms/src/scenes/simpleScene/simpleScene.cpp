#include "simpleScene.h"


void simpleScene::setup(){
    sceneName = "simpleScene";
}

void simpleScene::update(){
    
    
    
    if (ofGetFrameNum() % 200 == 0 || particles.size() == 0){
        
        particles.clear();
        
        ofRectangle r = cvData->getScreenRemapRectangle(SCREEN_LEFT);
        
        for (int i = 0; i < 1000; i++){
            
            float x = ofRandom(0.0, 1.0);
            float y = ofRandom(0.0, 1.0);
            
            ofPoint pos (r.x + r.width * x, r.y + r.height * y);
            
            particle p;
            p.setInitialCondition(pos.x, pos.y, 0,0);
            particles.push_back(p);
            
        }
        
        
    }
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].resetForce();
        particles[i].addDampingForce();
    }
    
    for (int i = 0; i < particles.size(); i++){
    
        ofPoint vel = cvData->getFlowAtScreenPos(SCREEN_LEFT, particles[i].pos);
        particles[i].addForce(vel.x*0.1, vel.y*0.1);
    //    particles[i].pos;
        
    }
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].update();
    }
    
    // erase particles that are 1 second old...
    
    
//    particles.erase(
//                    std::remove_if(
//                                   particles.begin(),
//                                   particles.end(),
//                                   [&](bornParticle & i){return ((ofGetElapsedTimef() - i.age) > 1.0);}),
//                    particles.end());
}

void simpleScene::draw(){
    
    
    for (int i = 0; i < particles.size(); i++){
        ofCircle(particles[i].pos, 2); //draw();
    }
    
    for (int i = 0; i < cvData->blobs.size(); i++){
        ofPolyline line = cvData->blobs[i].blob;
        for (auto & pt : line.getVertices()){
            pt = cvData->remapForScreen(SCREEN_LEFT, pt);
        }
        line.draw();
    }
    
    
//    ofDrawRectangle(0,0,100,100);
//    
//    ofSetColor(255);
//    
//    
//
//    
//    for (int i = 0; i < cvData->blobs.size(); i++){
//        ofPolyline line = cvData->blobs[i].blob;
//        for (auto & pt : line.getVertices()){
//            pt = cvData->remapForScreen(SCREEN_LEFT, pt);
//        }
//        
//        ofSetColor(255,255,255, 50);
//        line.draw();
//        
//        
//        ofRectangle bounds = line.getBoundingBox();
//        
//        float div = 15; //(float)max(ofGetMouseX(), 3);
//        //cout << div << endl;
//        int divisions = ceil(bounds.width / div);
//        
//        vector < ofPoint > pts;
//        
//        ofPolyline tempLine = line.getResampledBySpacing(1);
//        
//        float w = div; //bounds.getWidth()/(float)divisions;
//        
//        
//        float startX = bounds.x;
//        
//        
//        vector < ofPoint > circlePositions;
//        for (int j = 0; j < divisions; j++){
//            
//            
//            ofRectangle tempRect(startX + j * w, bounds.y, w, bounds.height);
//            bool bAny = false;
//            float minY = bounds.y + bounds.height;
//            for (auto & pt : tempLine){
//                if (tempRect.inside(pt)){
//                    if (pt.y < minY){
//                        minY = pt.y;
//                        bAny= true;
//                    }
//                }
//            }
//            if (!bAny){
//                //minY = bounds.y;
//            }
//            
//            minY -= 10;
//            
//            ofFill();
//            ofRectangle tempRect2(startX + j * w, minY, w, bounds.height - (minY- bounds.y));
//            
//            //ofCircle(ofPoint(bounds.x + j * w + w/2, minY), w/2);
//            //ofRect(tempRect2);
//            
//            ofPoint circlePos = ofPoint(startX + j * w + w/2, minY);
//           
//            
//            circlePositions.push_back(circlePos);
//
//            
//            //pts.push_back( ofPoint(bounds.x + j * w + w/2, minY));
//        }
//        
//        
//        
//        ofPolyline hmm;
//        bool bSkip = false;
//        
//        for (int j = 0; j < circlePositions.size(); j++){
//            
//            if (bSkip == true){
//                bSkip = false;
//                continue;
//            }
//            ofPoint circlePos = circlePositions[j];
//            float angle = PI;
//            float angleStep = PI/9.0;
//            float width = w/2;
//            
//            float flipMe = 1;
//            
//            
//            if (j < circlePositions.size()-1){
//                if ( fabs(circlePositions[j+1].y - circlePositions[j].y) < 10){
//                    bSkip = true;
//                    circlePos = (circlePositions[j] + circlePositions[j+1])/2;
//                    width = w;
//                }
//            }
//            
//            if (j > 0 && j < circlePositions.size()-1 && bSkip != true){
//                
//                if (circlePositions[j-1].y < circlePositions[j].y &&
//                    circlePositions[j+1].y < circlePositions[j].y){
//                    flipMe = -1;
//                    
//                }
//            }
//            
//            for (int k = 0; k < 10; k++){
//                ofPoint pt = circlePos + width * ofPoint(cos(angle), sin(angle));
//                angle += angleStep * flipMe;
//                hmm.addVertex(pt);
//            }
//        }
//        
//        
//        ofSetColor(255);
//        ofPolyline lineTemp(pts);
//        
//        hmm.addVertex( hmm[hmm.size()-1].x, bounds.y + bounds.height);
//        hmm.addVertex( hmm[0].x, bounds.y + bounds.height);
//        
//        
//        ofPoint centroid = hmm.getCentroid2D();
//        for (auto & pp : hmm){
//            pp = (pp - centroid) * ofPoint(1.1, 1.2) + centroid;
//        }
//        
//        line = line.getSmoothed(11);
//        
//        ofBeginShape();
//        for (auto & pp : hmm){
//            ofVertex(pp);
//        }
//        ofNextContour();
//        for (auto & pp : line){
//            ofVertex(pp);
//        }
//        ofEndShape();
//        
//        //hmm.draw();
//        
//        //lineTemp.draw();
//        
//        
//        
//    }
//    
//    
//    
//    
//    
//    
////    for (int i = 0; i < particles.size(); i++){
////        int id = particles[i].id;
////        float age = ofGetElapsedTimef() - particles[i].age;
////        
////        int whichBlob = cvData->idToBlobPos[id];
////        
////        ofPoint centroid = cvData->blobs[whichBlob].blob.getCentroid2D();
////        
////        centroid = cvData->remapForScreen(SCREEN_LEFT, centroid);
////        
////        ofNoFill();
////        
////        ofDrawBitmapStringHighlight( ofToString(id) + " " +  ofToString(age), centroid);
////        
////        ofCircle(centroid, age * 100);
////    }
//    
//    
    
    
    
}


void simpleScene::blobBorn(int id){
    
//    bornParticle p;
//    p.id = id;
//    p.age = ofGetElapsedTimef();
//    particles.push_back(p);
}

void simpleScene::blobDied(int id){
 
    
    
//    particles.erase(
//                   std::remove_if(
//                                  particles.begin(),
//                                  particles.end(),
//                                  [&](bornParticle & i){return i.id == id;}),
//                   particles.end());
}


void simpleScene::start(){
    // I am starting, show a gui
}

void simpleScene::stop(){
    // I am stopping, hide a gui
}
