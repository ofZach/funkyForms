//
//  Particle.hpp
//  funkyForms
//
//  Created by Qinzi Tan on 8/25/16.
//
//

#ifndef Particle_hpp
#define Particle_hpp

#include "ofMain.h"

class ParticleNoise
{
public:
    ofPoint pos;
    ofPoint vel;
    ofPoint frc;
    ofPoint originalPos;
    ofColor color;
    
    
    void setup(float px, float py, float vx, float vy);
    
    void resetForce();
    void addForce(float x, float y);
    void addDampingForce(float _damping);
    void update();
    
    void addColor(bool _addR, ofVec2f _mouse,bool _colorMode,  float _maxDistV, float _minDistV);
    void draw();
    
    void addNoise();
    void addRepulsionForce( float px, float py, float radius, float strength);
    void addAttractionForce( float px, float py, float radius, float strength);
    void addClockwiseForce( float px, float py, float radius, float strength,  float _rotateSpeed, float _rotateR);
    void addCounterClockwiseForce(float px, float py, float radius, float strength,  float _rotateSpeed, float _rotateR);
    void addSpringBackForce(ofPoint _currPos, float _springBack);
    
    
protected:
private:
};

#endif // PARTICLE_H
