//
//  FishWave.hpp
//  WaveScene
//
//  Created by Zerc on 7/29/16.
//
//

#ifndef FishWave_hpp
#define FishWave_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "Spring.hpp"
#include "inputManager.h"
#include "particle.h"
#include "particleWithAge.hpp"
#include "Shapes.hpp"
#include "wave.hpp"
#include "Animator.hpp"
#include "renderManager.h"

class particle2 : public particle {
public:
    float radius = 2;
    ofColor color;
};
class particleShape : public particle {
public:
    float radius = 2;
    ofVec2f shapePos;
    ofColor color;
    ofMesh mesh;
    float age = 0;
    float ageMax;
    int lifeTime = 0;
    int lifeTimeMax;
    
    void drawSpikes(){
        mesh.draw();
    }
};

class FishWave: public wave {
public:
    // Input
    float sf = RENDER_SCALE_FACTOR;
    
    // w, h
    int screenW, screenH;
    
    // particles
    vector <particle2> particles;
    
    // parameters
    float shapeInRadius = 100;
    float shapeOutRadius = 20;
    int spikeCountMin = 10;
    int spikeCountMax = 30;
    float floatAge = 500;

    vector <particleShape> particlesBouey;
    
    ofImage img;
    ofMesh m;
    ofMesh strokeMesh;

    ofParameter<float> colorHueOffset;
    ofParameter<float> shadowRadius = 100;
    ofParameter<float> shadowOpacity = 100;
    ofParameter<float> energyHighlightSize = 100;
    
    ofColor baseColor;

    ofFloatColor color;

    float fishGravity;
    float fishDirection;
    float fishRepulseRadius;
    ofVec2f fishPos;
    
    // Fade
    Animator fadeAnimator;
    float shapeOpacity = 255;
    
    void setupFishWave();
    void setSize(int w, int h){screenW = w; screenH = h;}
    void setBaseColor(ofColor _baseColor){baseColor = _baseColor;};
    
    void fadeIn(){fadeAnimator.in();}
    void fadeOut(){fadeAnimator.out();}

    void updateFishWave();
    void updateFade();
    void updateFishRemoval();
    void updateFishCreation();
    void updateFishParticles();
    void updateSplashes();
    void updateMesh();
    
    void addSplash();
    void addFishParticle();
    void addFish();
    void addShape();
    
    void drawSplashes();
    void drawShapes();
    void draw();
};


#endif /* FishWave_hpp */
