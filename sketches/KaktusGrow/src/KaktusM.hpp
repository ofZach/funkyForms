//
//  KaktusM.hpp
//  KaktusGrow
//
//  Created by Zerc on 6/20/16.
//
//

#ifndef KaktusM_hpp
#define KaktusM_hpp

#include "ofMain.h"
#include "Kaktus.hpp"
#include "ofxGui.h"

class KaktusM{
public:
    vector<Kaktus> plants;
    ofxPanel gui;
    void setup(ofVec3f pos){
        addKaktus(pos);
    }
    void addKaktus(ofVec3f pos){
        Kaktus k;
        k.setup(pos);
        plants.push_back(k);
    }
    void fadeKaktus(){
        int last = plants.size()-1;
        plants[0].fade();
    }
    void update(){
        for (int i = 0; i < plants.size(); i++) {
            plants[i].update();
            if(plants[0].opacity<0){
                plants.erase(plants.begin());
            }
        }
    }
    void drawGui(){
        
    }
    void draw(){
        for (int i = 0; i < plants.size(); i++) {
            plants[i].draw();
        }
    }
};
#endif /* KaktusM_hpp */
