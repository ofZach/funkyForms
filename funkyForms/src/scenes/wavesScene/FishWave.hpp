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
#include "Shapes.hpp"
#include "wave.hpp"
class particle2 : public particle {
public:
    float radius = 2;
    ofColor color;
};

class FishWave: public wave {
public:
    // particles
    vector <particle2> particles;
    vector <particle> fishes;
    
    // shapes
    vector <ShapeBase *> shapes;
    vector <ShapeType> shapeTypes;

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
    
    void setupFishWave();
    void setBaseColor(ofColor _baseColor){baseColor = _baseColor;};
    
    void updateFishWave();
    void updateSplashes();
    void updateMesh();
    
    void addSplash();
    void addFish();
    
    void drawSplashes();
    void draw();
};


#endif /* FishWave_hpp */
