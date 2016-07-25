//
//  Plant.hpp
//  Plant
//
//  Created by Zerc on 6/28/16.
//
//

#ifndef Plant_hpp
#define Plant_hpp

#include "ofMain.h"
#include "Branch.hpp"
#include "iColor.hpp"
#include "Animator.hpp"

class Plant{
public:
    // gui
    float init_bottomW;
    float init_bottomH;
    float init_topW;
    float init_topH;
    float init_radius;

    float init_m_bottomW;
    float init_m_bottomH;
    float init_m_topW;
    float init_m_topH;
    float init_m_radius;
    
    float bottomW = 0;
    float bottomWMax = 30;
    Animator bottomW_animator;
    
    float bottomH = 0;
    float topW = 0;
    float topH = 0;
    float radius = 0;
    float m_bottomW = 0;
    float m_bottomH = 0;
    float m_topW = 0;
    
    float m_topH = 0;
    float m_topHMax = 30;
    Animator m_topH_animator;
    
    float m_radius = 0;
    vector<float> randomNums;

    ofParameterGroup parameters;
    
    vector<Branch> mainBranch;
    vector<Branch> branches;
    vector<ofPolyline> spikes;
    float mainBranchCount = 4;
    ofVec2f pos;
    ofVec2f velocity;
    float scale = 1.0;
    float size = 0.5;
    iColor icolor;
    int colorIndexTotal = 0;
    
    bool isSpike = false;
    float spikePct = 0;
    float spikeLength = 0;
    bool isSpikeFinished = false;
    
    struct branchSettings{
        ofVec2f pos;
        ofVec2f leftRect;
        ofVec2f topRect;
        float radius;
        bool isLeft;
    };
    
    void smooth(ofVec2f *val, ofVec2f newVal, float _speed);
    branchSettings mainBSettings(int counter);

    void setup();
    void update();
    void updateParameters();
    void draw();
    void grow(){icolor.grow();}
    void collapse(){icolor.colapse(); }
    void bottomWIn(){bottomW_animator.in();}
    void bottomWOut(){bottomW_animator.out();}
    void addSpike(){if(icolor.getGrowDone()){isSpike = true; isSpikeFinished = false;}}
    void delSpike(){isSpike = false;};
    void updateSpike();
    void makeSpikes(ofPolyline &p, int counter, bool isRight);

    void setSmoothVelocity ( ofVec2f _vel , float _speed){ smooth(&velocity, _vel, _speed);}
    void setSmoothPosition ( ofVec2f _pos , float _speed){ smooth(&pos, _pos, _speed);}
    void setPosition ( ofVec2f _pos ){ pos = _pos;}
    void setScale (float _scale){ scale = _scale;};
    void setSmoothScale (float _scale, float _speed){ scale = scale*_speed + (1-_speed)*_scale;}
    
    ofVec2f getPosition(){return pos;}
    ofVec2f getVelocity(){return velocity;}
    float getScale(){return scale;}
    bool getFinished(){return icolor.getFinished(); }
    
    void randomize();
    void impulse(int colNum);
    int timer = 0;
    
    ofColor colors[4] = {
        ofColor::violet,
        ofColor::black,
        ofColor::lightGreen,
        ofColor::yellow
    };
    
};

#endif /* Plant_hpp */
