#include "tableScene2.h"
#include "boundsHelp.h"
#include "reflectionUseful.h"

void tableScene2::setup(){
    sceneName = "tableScene2";
}




void reflection3(int L, int R, int tid, reflectionPacket2 * packet){
    
    for (int i = L; i < R; i++){
        ofPoint pos = packet->pos[tid][i];
        ofPoint dir = packet->dir[tid][i];
        ofColor c = packet->colors[tid][i];
        for (int j = 0; j < 10; j++){
            Ray ray( Vector3(pos.x, pos.y, 0),  Vector3(dir.x, dir.y, 0));
            IntersectionInfo I;
            bool hit = packet->bvh->getIntersection(ray, &I, false);
            
            
            if (hit){
                
                Vector3 normal = ((lineSeg*)I.object)->getNormal(I);;
                
               
                packet->meshes[tid].addColor(ofColor(c.r,c.g,c.b,255));
                packet->meshes[tid].addVertex(pos);
                packet->meshes[tid].addColor(ofColor(c.r,c.g,c.b,255));
                packet->meshes[tid].addVertex(ofPoint(I.hit.x, I.hit.y));
                
                pos.set(I.hit.x, I.hit.y);
                dir.set(normal.x, normal.y);
                pos += dir * 0.001;                     // so we don't collide with the wall we just bounced off of
                
            } else {
                
                packet->meshes[tid].addColor(ofColor(c.r,c.g,c.b,255));
                packet->meshes[tid].addVertex(pos);
                packet->meshes[tid].addColor(ofColor(c.r,c.g,c.b,255));
                packet->meshes[tid].addVertex(pos + dir*4000);
                
                break;
            }
        }
    }
    
}


void tableScene2::update(){
    
    
    
    
    //ofPopMatrix();
    
    
    
}


void tableScene2::draw(){
    
    
    for (int i = 0; i < cvData[2]->blobs.size(); i++){
        
        ofPolyline line = cvData[2]->blobs[i].blob;
        for (auto & pt : line){
            pt = cvData[2]->remapForScreen(SCREEN_TABLE, pt, false);
            pt.y *= 0.7;
            pt.y += 500;
       
        }
        
        line = line.getResampledBySpacing(3);
        line = line.getSmoothed(3);
        //line.draw();
        
    }
    
    
    if (objects.size() > 0){
        for (int i = 0; i < objects.size(); i++){
            delete objects[i];
        }
        objects.clear();
        delete bvh;
    }
    
    vector < ofPolyline > lineSegsToShootRaysFrom[8];
    
    for (int i = 0; i < cvData[2]->blobs.size(); i++){
        
        ofPolyline line = cvData[2]->blobs[i].blob;
        for (auto & pt : line){
            pt = cvData[2]->remapForScreen(SCREEN_TABLE, pt, false);
            pt.y *= 0.7;
            pt.y += 500;
        }
        
        line = line.getResampledBySpacing(3);
        line = line.getSmoothed(3);
        //line.draw();
        for (int j = 0; j < line.size(); j++){
            ofPoint a = line[j];
            ofPoint b = line[(j+1) % line.size()];;
            lineSeg * temp = new lineSeg( a,b);
            objects.push_back(temp);
        }
    }
    
    
    lineSeg * temp = new lineSeg( ofPoint(-1,-1), ofPoint(-2,-2));
    objects.push_back(temp);
    
    bvh = new BVH(&objects);
    //    if (objects.size() > 0){
    //        bvh = new BVH(&objects);
    //    } else {
    //        // no lines no light
    //        //return;
    //
    //    }
    
    
    
    reflectionPacket2 packet;
    
    float timeff = ofGetElapsedTimef();
    
    packet.nLightRays = 5000;
    vector < ofPoint > positions;
    vector < ofPoint > directions;
    vector < ofColor > colors;
    ofPoint center = RM->getRectForScreen(SCREEN_CENTER).getCenter();
    
    int nRaysPerType = packet.nLightRays;
    
    
    
    for (int i = 0; i < packet.nLightRays; i++){
        
        int type = i % 3;
        ofPoint centerPos = ofPoint(center.x, center.y) + 2000 * ofPoint(cos(timeff * (1+type*0.1)), sin(timeff* (1+type*0.1)));
        ofPoint dir  = (center -centerPos).normalize();
        ofPoint dirAngle = dir.getRotated(90, ofPoint(0,0,1));
        ofPoint pos = centerPos + dirAngle * ofMap(i, 0, packet.nLightRays, -500,500);
        //ofPoint dir(cos(timeff + i*0.001), sin(timeff + i*0.001));
        dir.normalize();
        positions.push_back(pos);
        directions.push_back(dir);
        if (type == 0){
            colors.push_back(ofColor::red);
            
        } else if (type == 1){
            colors.push_back(ofColor::green);

        } else if (type == 2){
            colors.push_back(ofColor::blue);

        }
    }
    
    for (int i = 0; i < 16; i++){
        packet.pos[i] = positions;
        packet.dir[i] = directions;
        packet.colors[i] = colors;
        packet.meshes[i].setMode(OF_PRIMITIVE_LINES);
    }
    
    
    packet.bvh = bvh;
    
    int nr_threads = 16;
    std::vector<std::thread> threads;
    std::vector<int> limits = bounds(nr_threads,  packet.nLightRays );
    
    //Launch nr_threads threads:
    for (int i = 0; i < nr_threads; ++i) {
        
        threads.push_back(std::thread(reflection3, limits[i], limits[i+1], i, &packet));
    }
    
    
    for(auto &t : threads){
        t.join();
    }
    
    
    
    //float scale = RM->getWidth() / 2100.0; //(float)RM->windows.getWidth();
    
    //ofPushMatrix();
    
    //ofScale(scale, scale, 1.0);
    //RM.blocks.draw();
    //RM.drawBuidling();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (int i = 0; i < 16; i++){
        cout << packet.meshes[i].getNumVertices() << endl;
        
        packet.meshes[i].draw();
    }
    
    ofEnableAlphaBlending();
    
    
}


void tableScene2::blobBorn(int packetId, int id){
    
}

void tableScene2::blobDied(int packetId, int id){
    
    
}


void tableScene2::start(){
    // I am starting, show a gui
}

void tableScene2::stop(){
    // I am stopping, hide a gui
}
