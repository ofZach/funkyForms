#include "costumeScene2.h"


void costumeScene2::setup(){
    
    sceneName = "costumeScene2";
    
    
    shader.load("sceneAssets/costume/LinearGradient_vert.glsl", "sceneAssets/costume/LinearGradient_frag.glsl");
    
    
}

void costumeScene2::update(){
    
   
    if (ofGetFrameNum() % 100 == 0){
        shader.load("sceneAssets/costume/LinearGradient_vert.glsl", "sceneAssets/costume/LinearGradient_frag.glsl");
        

    }
}


class intersectionPoint {
public:
    ofPoint pos;
    ofPoint avgVel;
    float pct;
    
    
};


bool bSortFunc(intersectionPoint & a, intersectionPoint & b){
    return a.pos.x < b.pos.x ? true : false;
}





void costumeScene2::draw(){
    
    
    ofCamera cam;
    cam.setupPerspective();
    cam.enableOrtho();
    cam.begin();
    ofSetCircleResolution(100);
    
    float ff =ofGetElapsedTimef();
    
    ofEnableDepthTest();
    
    for (int packetId = 0; packetId < 2; packetId++){
        for (int i = 0; i < cvData[packetId]->blobs.size(); i++){
            
            ofPolyline line = cvData[packetId]->blobs[i].blob;
            
            int id  = cvData[packetId]->blobs[i].id;
            
            for (auto & pt : line){
                pt = cvData[0]->remapForScreen(packetId == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
            }
            line.flagHasChanged();
            
            //line.draw();
            
            float avgVelSmoothed = cvData[packetId]->blobs[i].avgVelSmoothed.y;
            if (avgVelSmoothed < 0) avgVelSmoothed = 0;
            // let's fucking roll.....
            
            ofRectangle bounds = line.getBoundingBox();
            
            float div = 5.0;
            bounds.scaleFromCenter(1.2);
            int steps= bounds.height/div;
            
            ofSeedRandom(id*100000);
            
            for (int z = steps; z >= 0; z--){
                ofPoint a = ofPoint(bounds.x, bounds.y + z * div);
                ofPoint b = ofPoint(bounds.x + bounds.width, bounds.y + z * div);
                
                ofColor color(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
                ofSetColor(255);
                //ofLine(a,b);
                
                vector < intersectionPoint > intersections;
                
                for (int j = 0; j < line.size(); j++){
                    
                    ofPoint toTestA = line[j];
                    ofPoint toTestB = line[(j+1)%line.size()];
                    
                    ofPoint intersection;
                    
                    if (ofLineSegmentIntersection(a, b, toTestA, toTestB, intersection)){
                        intersectionPoint pt;
                        pt.pos = intersection;
                        pt.avgVel = toTestB- toTestA +
                            ((cvData[packetId]->blobs[i].vel[j] +
                                    cvData[packetId]->blobs[i].vel[(j+1)%line.size()])*0.5)*0.01;
                        pt.pct = ofMap(z, steps, 0, 0.0, 1.0);

                        intersections.push_back(pt);
                                            }
                }
                
                ofSort(intersections, bSortFunc);
                
                
                vector < ofColor > colors;
                
                ofVec4f aColor;
                ofVec4f bColor;
                
                aColor.set(0,0,0,1);
                bColor.set(0,0,0,0.0);
                
                
                
                
                for (int i = 0; i < intersections.size(); i+=2){
                    
                    ofPoint aa = intersections[i].pos;
                    ofPoint bb = intersections[i+1].pos;

                    

                    
                    ofPoint vel = intersections[i].avgVel;
                    
                    
                    //vel.rotate(ff * 10, ofPoint(0,0,1));
                    
                    ofPoint vel2 = intersections[i+1].avgVel;
                    
                   // vel2.rotate(ff * 20, ofPoint(0,0,1));
                    
                    
                    float angle = atan2(vel.y, vel.x);
                    float angle2 = atan2(vel2.y, vel2.x);
//                    
                    ofColor c;
                    c.setHsb(ofMap(angle, -PI, PI, 0, 255), 255, 255);
                    
                    ofColor c2;
                    c2.setHsb(ofMap(angle2, -PI, PI, 0, 255), 255, 255);
                    
                    
                    //aColor.set(c.r/ 255.0, c.g/255.0, c.b/255.0, 1.0);
                    //bColor.set(c2.r/ 255.0, c2.g/255.0, c2.b/255.0, 1.0);
                    
                    
                    
                   
                    
                    
                    
                    ofPoint midPt = (aa + bb)/2.0;
                    
                    //midPt.y -= intersections[i].pct * ofMap(avgVelSmoothed, 1, 3, 0, 300, true);
                    float radius = (aa - bb).length() * 0.5;
                    
                    shader.begin();
                    shader.setUniform1f("windowHeight", RM->getHeight() );
                    
                    shader.setUniform2f("gradientStartPos", aa);
                    shader.setUniform2f("gradientEndPos", bb);
                    shader.setUniform1i("numStops", 2);
                    shader.setUniform4f("colorA", aColor);
                    shader.setUniform4f("colorB", bColor);
                    
                    ofFill();
                    //ofSetColor(c);
                    ofPushMatrix();
                    ofTranslate(midPt);
                    ofRotate(ofGetMouseX(), 1,0,0);
                    ofCircle(ofPoint(0,0,0), radius);
                    
                    shader.end();
                    
                    ofNoFill();
                    ofSetColor(255,255,255,255 );
                    ofCircle(ofPoint(0,0,0), radius);

                    ofPopMatrix();
                    
                    //ofCircle(intersections[i], 4);
                }
                
                

            }
            
            
            
        }
    }
    
    
    ofSetCircleResolution(20);
    cam.end();
    
    ofDisableDepthTest();
    
}


void costumeScene2::blobBorn(int packetId, int id){
    
   
}

void costumeScene2::blobDied(int packetId, int id){
    
}


void costumeScene2::start(){
    
}

void costumeScene2::stop(){
    
    
}
