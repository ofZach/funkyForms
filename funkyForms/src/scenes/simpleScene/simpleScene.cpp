#include "simpleScene.h"


void simpleScene::setup(){
    sceneName = "simpleScene";
}

void simpleScene::update(){
    
    
    
    for (int i = 0; i < cvData->blobs.size(); i++){
        
        ofPoint avgVel;
        
        for (int j = 0; j < cvData->blobs[i].vel.size(); j++){
            avgVel += cvData->blobs[i].vel[j];
        }
        
        avgVel /= (float)max((int)cvData->blobs[i].vel.size(), 1);
        
        
        
        ofPolyline & line = cvData->blobs[i].blob;
        
        if (avgVel.getNormalized().dot(ofPoint(0,-1)) > 0.7){
        for (int j = 0; j < line.size(); j++){
            ofPoint pt = line[j];
            pt = cvData->remapForScreen(SCREEN_LEFT, pt);
            ofPoint vel = cvData->blobs[i].vel[j];
            ofPoint velNorm = vel.getNormalized();
            float dot = velNorm.dot(ofPoint(0,-1)); // up
            if (dot > 0.44 && vel.length() > 1.1 && ofRandom(0,1) > 0.9){
                
                // is this FACING up
                ofPoint tan = cvData->blobs[i].blob.getTangentAtIndex(j).rotate(90, ofPoint(0,0,1));
                if (tan.dot(ofPoint(0,-1)) > 0.1){
                
                    particleWithAge temp;
                    temp.age = ofGetElapsedTimef();
                    temp.setInitialCondition(pt.x, pt.y, vel.x * 0.1, vel.y*2); // reduce the x vel
                    temp.damping = 0.05;
                    particles.push_back(temp);
                    if (particles.size() > 4000){
                        particles.erase(particles.begin());
                    }
                }
            }
        }
        }
        
        //line.draw();
    }

    
    
    ofRectangle target = cvData->getScreenRemapRectangle(SCREEN_LEFT);
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].resetForce();
        particles[i].addDampingForce();
        
        
      //  particles[i].addAttractionForce(target.getCenter().x, target.getCenter().y, 10000, 0.02);
    }
    
    // add some noise!
    
    float time = ofGetElapsedTimef();
    
    for (int i = 0; i < particles.size(); i++){
        ofPoint pos = particles[i].pos;
        float speed = ofMap(time-particles[i].age, 1, 5, 1, 0, true);
        float xNoise = ofSignedNoise(pos.x * 0.1, pos.y * 0.1, i, time * 0.1);
        float yNoise = ofSignedNoise(pos.x * 0.1, pos.y * 0.1, i, time * 0.1 + 100000);
        
        particles[i].addForce(xNoise*0.2 * speed, -fabs(yNoise) * 0.2 * speed);
    }
    
    
    // get flow from the field:
    for (int i = 0; i < particles.size(); i++){
        ofPoint vel = cvData->getFlowAtScreenPos(SCREEN_LEFT, particles[i].pos);
        particles[i].addForce(vel.x*0.03, vel.y*0.03);
    }
    
    // alternatively search for the closest pt...  we can simplify things by looking in a thin way:
    
//    vector < ofPolyline > blobsRemapped;
//    for (auto & blob : cvData->blobs){
//        ofPolyline temp;
//        for (auto & pt : blob.blob){
//            ofPoint newPt = cvData->remapForScreen(SCREEN_LEFT, pt);
//            temp.addVertex(newPt);
//        }
//        blobsRemapped.push_back(temp);
//    }
//    
//    
//     for (int i = 0; i < particles.size(); i++){
//         ofPoint pos = particles[i].pos;
//         ofPoint closestVel;
//         float minDistance = 1000000;
//         for (int j = 0; j < blobsRemapped.size(); j++){ // : blobsRemapped){
//             for (int k = 0; k < blobsRemapped[j].size(); k+=10){
//                 float dist = (    blobsRemapped[j][k] - pos).length();
//                 if (dist < minDistance){
//                     minDistance = dist;
//                     closestVel = cvData->blobs[j].vel[k];
//                 }
//             }
//             
//         }
//         float invScale = ofMap(minDistance, 0, 50, 1, 0, true);
//         //cout << closestVel << endl;
//         particles[i].addForce(closestVel.x*0.3 * invScale, closestVel.y*0.3 * invScale);
//    
//     }


    
    
    
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
    
    
    float time = ofGetElapsedTimef();
    
    for (int i = 0; i < particles.size(); i++){
        
        float alpha = ofMap(time - particles[i].age, 0,4, 1, 0, true);
        if (alpha > 0){
            ofSetColor(255,255, 255, powf(alpha, 5)*255);
            
            float startScale = ofMap(time-particles[i].age, 0, 1, 0, 1, true);
            
            ofLine(particles[i].pos, particles[i].pos - particles[i].vel * 10 * startScale);
            ofFill();
            ofCircle(particles[i].pos, 2); //draw();
        }
    }
    
    ofSetColor(255,255,255);
    
    for (int i = 0; i < cvData->blobs.size(); i++){
        
        ofPoint avgVel;
        
        for (int j = 0; j < cvData->blobs[i].vel.size(); j++){
            avgVel += cvData->blobs[i].vel[j];
        }
        
        avgVel /= (float)max((int)cvData->blobs[i].vel.size(), 1);
        
        
        ofPolyline line = cvData->blobs[i].blob;
        for (auto & pt : line.getVertices()){
            pt = cvData->remapForScreen(SCREEN_LEFT, pt);
        }
        line.draw();
        
        ofPoint centroid = cvData->blobs[i].blob.getCentroid2D();
        centroid = cvData->remapForScreen(SCREEN_LEFT, centroid);
        
        ofLine(centroid, centroid + avgVel * 10);
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
