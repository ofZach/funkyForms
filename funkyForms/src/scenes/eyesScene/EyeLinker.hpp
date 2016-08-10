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
#include "cvManager.h"

class EyeLinker{
public:
    // Pos, Vel, ID, Size
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f velPrev;
    int id;
    float width = 100;
    float height = 100;
    float scale = 1.0;
    
    // Input
    cvPacket * cvData;
    
    // Eyes
    vector<eye> eyes;
    
    // Particles
    vector <spring> springs;
    vector <particle> particles;
    
    // Timing
    int idleCounter = 0;
    bool isSleep = false;
    
    // Fading
    bool isFading = false;
    bool isFinished();
    
    // Gui
    
    void setup();
    void setupGui();
    void setVel(ofVec2f _vel);
    void setPos(ofVec2f _pos);
    void setSize(float w, float h);
    void setScale(float scale);
    void out();

    void update();
    void updateEye();
    void updateParameters();
    void updateFading();
    void updatePhysics();
    
    void draw();
    void drawParticles();
    
};

#endif /* EyeLinker_hpp */