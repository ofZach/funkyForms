//
//  EyeLinker.hpp
//  EyeScene
//
//  Created by Zerc on 7/14/16.
//
//

#ifndef EyeLinker_hpp
#define EyeLinker_hpp

#include "ofMain.h"
#include "eye.hpp"
#include "particle.h"
#include "spring.h"

class EyeLinker{
public:
    vector<eye> eyes;
    vector<particle> particles;
    vector <spring> springsEb;
    vector <particle> particlesEb;
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f velPrev;
    int idleCounter = 0;
    bool isSleep = false;
    
    void updateEbPhysics();
    void addEye();
    void removeEye();
    void setVel(ofVec2f _vel);
    void setup();
    void update(ofVec2f _pos);
    void draw();
    
};

#endif /* EyeLinker_hpp */
