//
//  eyePairMode.hpp
//  EyeScene
//
//  Created by Zerc on 7/15/16.
//
//

#ifndef eyePairMode_hpp
#define eyePairMode_hpp

#include "ofMain.h"
#include "eye.hpp"
#include "modeBase.hpp"
#include "renderManager.h"
#include "rewardLines.hpp"

class eyePairMode : public modeBase {
private:
public:
    
    // Input
    float sf = RENDER_SCALE_FACTOR;
    
    ofVec2f pos;
    vector<eye> eyes;
    bool isEyeBig;
    
    float scaleL = 1.;
    float scaleR = 1.;
    float angleL = 0.;
    float angleR = 0.;
    bool isHit = false;
    float scaleMin = 0.5;
    float scaleMax = 2;
    
    // fading
    bool isFadeOut = false;
    bool isFadeIn = false;
    
    // EyePair
    ofParameter<float> eyeDistance = 200;
    ofParameterGroup parameters;
    ofParameter<float> posOffsetY;
    ofParameter<float> maxScale;
    ofParameter<float> minScale;
    ofParameter<float> posOffsetX;
    ofParameter<float> eyeSize;
    ofParameter<float> scaleSmooth;
    ofParameter<float> rewLineLength;
    ofParameter<float> rewLineRadius;
    ofParameter<float> rewTreshold;
    ofParameter<int> rewAmount;

    
    // Input
    float leftEnergy = 0;
    float rightEnergy = 0;
    ofParameter<float> energyRange = 20;
    ofParameter<float> smooth = 0.98;
    
    // Effects
    rewardLines reward;
    
    void setup();
    void triggerInit(float &v);
    void init();
    void setupGui();
    void setEnergy(float left, float right){ leftEnergy = left; rightEnergy = right; };
    
    void fadeIn();
    void fadeOut();
    void addScaleForce();
    void setPos(ofVec2f _pos){pos = _pos;}
    void setLookAt(ofVec2f _pos);
    void hitStart(){isHit = true;}
    void hitEnd(){isHit = false;}
    void lookAtSmart(ofVec2f _pos){for(auto &e: eyes){ e.lookAtSmart(_pos);}};
    
    void updateScale();
    void updateReward();
    void update(ofVec2f posL, ofVec2f posR);
    void updateFadeCheck();

    void draw();
};

#endif /* eyePairMode_hpp */
