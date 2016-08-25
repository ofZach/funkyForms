#include "buildingScene.h"
#include "parallel.h"


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
    //   piece.line.draw();
    }
    
    
    
    
    // tracers
    
//      vector < ofPoint > trackerPts;
//    
//    for (int i = 0; i < pieces.size(); i++){
//        
//        int howMany = 5 + 5 * sin(ofGetElapsedTimef() + i * 0.01);
//        
//        for (int j = 0; j < howMany; j++){
//            
//            ofMesh m;
//            m.setMode(OF_PRIMITIVE_LINE_STRIP);
//            
//            for (int k = 0; k < 10; k++){
//            
//                float pct = ofMap(k, 0, 10, 1, 0);
//                float len = pieces[i].length;
//                float pos = fmod(tracer[i] + len/10.0 * j - k * len*0.005, len);
//                
//                if (k == 0 && j % 3 == 0) trackerPts.push_back(pieces[i].line.getPointAtLength(pos));
//                m.addVertex(pieces[i].line.getPointAtLength(pos));
//                m.addColor(ofColor(255,255,255,255*pct));
//                ofPoint circlePos = pieces[i].line.getPointAtLength(pos);
//            }
//            m.draw();
//            //ofCircle(circlePos, 1);
//        }
//    }
    
    
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
    
    
    // reflection ! cool !
    
//    if (objects.size() > 0){
//        for (int i = 0; i < objects.size(); i++){
//            delete objects[i];
//        }
//        objects.clear();
//        delete bvh;
//    }
//
//    float pct = ofMap(sin(ofGetElapsedTimef()), -1, 1, 0.03, 1);
//    for (auto & piece : pieces){
//        if (true)
//        for (int i = 0  + ofGetElapsedTimef()*3; i < piece.line.size()*0.3+ ofGetElapsedTimef()*3; i++){
//            ofPoint a = piece.line[i%piece.line.size()];
//            ofPoint b = piece.line[(i+1)%piece.line.size()];
//            lineSeg * temp = new lineSeg( a,b);
//            objects.push_back(temp);
//        }
//    }
//    cout << objects.size() << endl;
//    
//    bvh = new BVH(&objects);
//    
//    typedef struct {
//        BVH * bvh;
//        ofMesh meshes[8];
//    } reflectionPacket;
//    
//    reflectionPacket packet;
//    
//    packet.bvh = bvh;
//    for (int i = 0; i < 8; i++){
//        packet.meshes[i].setMode(OF_PRIMITIVE_LINES);
//    }
//    
//    
//    parallelCap_(8, &packet)
//    {
//        int split = 5000/8;
//        for (int i = thread_num * split; i < (thread_num+1) * split; i++){
//            int tid = thread_num; //omp_get_thread_num();
//            
//            ofPoint pos(ofGetMouseX()*3 + ofRandom(-20, 20), ofGetMouseY()*3+ ofRandom(-20, 20));;
//            ofPoint dir(cos(ofGetElapsedTimef() + i * 0.01),sin(ofGetElapsedTimef() + i * 0.01));
//            dir.normalize();
//            for (int j = 0; j < 10; j++){
//                
//                Ray ray( Vector3(pos.x, pos.y, 0),  Vector3(dir.x, dir.y, 0));
//                
//                IntersectionInfo I;
//                
//                bool hit = packet.bvh->getIntersection(ray, &I, false);
//                
//                if (hit){
//                    
//                    Vector3 normal = ((lineSeg*)I.object)->getNormal(I);;
//                    
//                    packet.meshes[tid].addColor(ofColor(255,255,255,30));
//                    packet.meshes[tid].addVertex(pos);
//                    packet.meshes[tid].addColor(ofColor(255,255,255,30));
//                    packet.meshes[tid].addVertex(ofPoint(I.hit.x, I.hit.y));
//                    
//                    pos.set(I.hit.x, I.hit.y);
//                    dir.set(normal.x, normal.y);
//                    pos += dir * 0.001;                     // so we don't collide with the wall we just bounced off of
//                    
//                } else {
//                    
//                    packet.meshes[tid].addColor(ofColor(255,255,255,30));
//                    packet.meshes[tid].addVertex(pos);
//                    packet.meshes[tid].addColor(ofColor(255,255,255,30));
//                    packet.meshes[tid].addVertex(pos + dir*3000);
//                    
//                    break;
//                }
//            }
//        }
//    }
//    parallel_end
//    
//    
//    
//    float scale = RM->getWidth() / (float)RM->windows.getWidth();
//    
//    ofPushMatrix();
//    
//    ofScale(scale, scale, 1.0);
//    //RM.blocks.draw();
//    //RM.drawBuidling();
//    
//    for (int i = 0; i < 8; i++){
//        packet.meshes[i].draw();
//    }
//
//    
//    ofPopMatrix();
//   
   
    
    
    
    
        if (objects.size() > 0){
            for (int i = 0; i < objects.size(); i++){
                delete objects[i];
            }
            objects.clear();
            delete bvh;
        }
    
        vector < ofPolyline > lineSegsToShootRaysFrom[8];
    
        for (auto & piece : pieces){
            //if (piece.bWindow == true)
             for (int i = 0;  i < piece.line.size(); i++){
                ofPoint a = piece.line[i%piece.line.size()];
                ofPoint b = piece.line[(i+1)%piece.line.size()];
                lineSeg * temp = new lineSeg( a,b);
                objects.push_back(temp);
            }
        }
    
        bvh = new BVH(&objects);
    
        typedef struct {
            BVH * bvh;
            ofMesh meshes[8];
            vector < ofPoint > rayPts[8];
        } reflectionPacket;
    
        reflectionPacket packet;
    
        for (auto & piece : pieces){
            //if (piece.bWindow == true){
                
            ofPolyline temp = piece.line;
            temp.setClosed(true);
            temp = temp.getResampledBySpacing(0.5);
            
            for (int i = 0; i < 8; i++){
                for (auto pt : temp.getVertices()){
                    packet.rayPts[i].push_back(pt);
                }
            }
            //}
        }
    
    
    
    
        packet.bvh = bvh;
        for (int i = 0; i < 8; i++){
            //ofRandomize(packet.rayPts[i]);
            
            packet.meshes[i].setMode(OF_PRIMITIVE_LINES);
        }
    
    
    
        parallelCap_(8, &packet)
        {
            float mouseX = ofGetMouseX();
            float mouseY = ofGetMouseY();
            ofPoint mouse ( mouseX, mouseY);
            int split = 15000/8;
            float time = ofGetElapsedTimef();
            for (int i = thread_num * split; i < (thread_num+1) * split; i++){
                int tid = thread_num; //omp_get_thread_num();
                
                float pct = ofMap(i, 0, 15000.0, 0, 1.0);
                int sz = packet.rayPts[tid].size();
                ofPoint pos = packet.rayPts[tid][ (int)(pct*sz) % sz];
                
                ofPoint diff = pos - mouse;
                
                //ofPoint pos(ofGetMouseX()*3 + ofRandom(-20, 20), ofGetMouseY()*3+ ofRandom(-20, 20));;
                ofPoint dir = diff; //cos(time),sin(time));
                
                dir.normalize();
                pos+= dir*0.01;
                for (int j = 0; j < 1; j++){
    
                    Ray ray( Vector3(pos.x, pos.y, 0),  Vector3(dir.x, dir.y, 0));
    
                    IntersectionInfo I;
    
                    bool hit = packet.bvh->getIntersection(ray, &I, false);
    
                    if (hit){
    
                        Vector3 normal = ((lineSeg*)I.object)->getNormal(I);;
    
                        packet.meshes[tid].addColor(ofColor(255,255,255,255));
                        packet.meshes[tid].addVertex(pos);
                        packet.meshes[tid].addColor(ofColor(255,255,255,0));
                        packet.meshes[tid].addVertex(ofPoint(I.hit.x, I.hit.y));
    
                        pos.set(I.hit.x, I.hit.y);
                        dir.set(normal.x, normal.y);
                        pos += dir * 0.001;                     // so we don't collide with the wall we just bounced off of
    
                    } else {
    
                        packet.meshes[tid].addColor(ofColor(255,255,255,255));
                        packet.meshes[tid].addVertex(pos);
                        packet.meshes[tid].addColor(ofColor(255,255,255,0));
                        packet.meshes[tid].addVertex(pos + dir*3000);
    
                        break;
                    }
                }
            }
        }
        parallel_end
    
    
        
        float scale = RM->getWidth() / 2100.0; //(float)RM->windows.getWidth();
        
        ofPushMatrix();
        
        ofScale(scale, scale, 1.0);
        //RM.blocks.draw();
        //RM.drawBuidling();
        
        for (int i = 0; i < 8; i++){
            
            packet.meshes[i].draw();
        }
    
        
        ofPopMatrix();
    
    
    
}


void buildingScene::blobBorn(int packetId, int id){
    
   
}

void buildingScene::blobDied(int packetId, int id){
    
}


void buildingScene::start(){
    
}

void buildingScene::stop(){
    
    
}
