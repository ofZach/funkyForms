
#pragma once

#include "ofMain.h"
#include "baseScene.h"
#include "springyShape.h"
#include "boundsHelp.h"

typedef struct {
    
    vector < springyShape > shapes;
    
} bData;

void blah(int L, int R, bData* data); //{ //, vector < springyShape > * tempShapes){
    
class trackedContourObj {

    public:
    
    int id;
    int packetId;
    trackedContour * TC;            // I need to be more manual about this since the copy contstructor of ofThread is smartly deleted :) 
    
    vector < springyShape > shapes;
    
    
    void setup( ofPoint target){
        
    }
    
    void update( ofPolyline & resampleSmoothed){
        
        if (shapes.size() == 0){
            for (int i = 0; i < 100; i++){
                springyShape s;
                shapes.push_back(s);
                shapes.back().setup(resampleSmoothed[i]);
            }
        } else {
            if (resampleSmoothed.size() >= shapes.size()){
                for (int i = 0; i < shapes.size(); i++){
                    ofPoint to = resampleSmoothed.getTangentAtIndex(i).rotate(90, ofPoint(0,0,1));
                    shapes[i].targetAngle = atan2(to.y, to.x);
                    shapes[i].dragTo( resampleSmoothed[i]  );
                }
            }
            
            
            
            int nr_threads = 16;
            std::vector<std::thread> threads;
            std::vector<int> limits = bounds(nr_threads,  shapes.size() );
            
            bData data;
            
            for (int i = 0; i < shapes.size(); i++){
                data.shapes.push_back(shapes[i]);
            }
            
            //Launch nr_threads threads:
            for (int i = 0; i < nr_threads; ++i) {
                //cout << limits[i] << " ? " <<  limits[i+1] << endl;
                
                threads.push_back(std::thread(blah, limits[i], limits[i+1], &data));
            }
            
            
            
            for(auto &t : threads){
                t.join();
            }

            
            for (int i = 0; i < shapes.size(); i++){
                shapes[i] = data.shapes[i];
            }
            
            
            for (int i = 0; i < shapes.size(); i++){
                //shapes[i].draw();
            }
            
            
            

//            for (int i = 0; i < shapes.size(); i++){
//                springyShape temp;
//                temp = shapes[i];
//                temp.update();
//                
//                shapes[i] = temp; //.update();
//            }
        }
        
        
    }
    
    void draw(float alpha){
        if (shapes.size() == 0) return;
        ofSetColor(255,255,255,255*alpha);
        for (int i = 0; i < shapes.size(); i++){
            shapes[i].draw();
        }
    }
        
        

    
};

class costumeScene : public baseScene {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void start();
    void stop();
    
    void blobBorn(int packetId, int id);
    void blobDied(int packetId, int id);
    
    vector < trackedContourObj > trackedObjects;
    
    
};


