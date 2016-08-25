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
#include "gParticle.hpp"
#include "renderManager.h"


class EyeLinker {
public:
    // Pos, Vel, ID, Size
    float age = 0;
    ofVec2f pos;
    ofVec2f posPrev;
    float velSmooth = 0.9;
    ofVec2f vel;
    ofVec2f velPrev;
    int packetId;
    int id;
    float width = 100;
    float height = 100;
    float scale = 1.0;
    int counter = 0;
    
    // Input
    float sf = RENDER_SCALE_FACTOR;
    cvPacket * cvData;
    
    // Eyes
    vector<eye> eyes;

    // Effects
    ofImage glow;
    int glowResolution = 10;
    float glowRadius = 20;
    float glowOpacity = 120;
    bool isGlow;
    
    // Particles
    vector <spring> springs;
    vector <particle> particles;
    
    // Timing
    int idleCounter = 0;
    bool isSleep = false;
    
    // Fading
    bool isFading = false;
    bool isFinished();
    
    // Fireworks
    struct fireObject{
        ofPolyline line;
        ofColor color;
        ofMesh mesh;
        float fadePct = 0;
        bool isDead = false;
        float radius;
        int id;
    };
    
    vector <gParticle> fireParticles;
    vector <fireObject> fireObjects;
    int curParticleId = 0;
    
    void setup();
    void fadeIn();
    void fadeOut();
    void initValues();
    void setupGui();
    void setVel(ofVec2f _vel);
    void setPos(ofVec2f _pos);
    void setSize(float w, float h);
    void setScale(float scale);
    void addFireworksParticle(ofVec2f _pos);
    void addFireObject();
    
    void out();

    void update();
    void updateFireworks();
    void updateFireObjectRemoval();
    void updateTrailParticles();
    void updateTrailLines();
    void updateTrailMeshes();
    void updateEye();
    void updateParameters();
    void updateVelocity();
    void updateFading();
    void updatePhysics();
    
    void draw();
    void drawParticles();
    void drawGlow();
    void drawFireworks();
    
};

#endif /* EyeLinker_hpp */
