//
//  Particle.cpp
//  funkyForms
//
//  Created by Qinzi Tan on 8/25/16.
//
//

#include "ParticleNoise.hpp"


//------------------------------------------------------------
void ParticleNoise::setup(float px, float py, float vx, float vy){
    
    pos.set(px,py);
    vel.set(vx,vy);
    originalPos.set(px, py);
    color=ofColor::fromHsb(0, 0, 0);
    
}

//------------------------------------------------------------
void ParticleNoise::resetForce(){
    
    frc.set(0,0);
    
}

//------------------------------------------------------------
void ParticleNoise::addForce(float x, float y){
    
    frc.x = frc.x + x;
    frc.y = frc.y + y;
    
}

//------------------------------------------------------------
void ParticleNoise::addDampingForce(float _damping){
    
    vel *= _damping;
    
}

//------------------------------------------------------------
void ParticleNoise::addRepulsionForce(float px, float py, float radius, float strength){
    
    ofVec2f posOfForce;
    posOfForce.set(px, py);
    
    ofVec2f diff = pos - posOfForce;
    
    if (diff.length() < radius){
        float pct = 1 - (diff.length() / radius);
        ofPoint perp;
        
        perp = diff.getNormalized();
        frc += perp * pct * strength;
    }
    
}

//------------------------------------------------------------
void ParticleNoise::addAttractionForce(float px, float py, float radius, float strength){
    
    ofVec2f posOfForce;
    posOfForce.set(px, py);
    
    ofVec2f diff = posOfForce - pos;
    
    if (diff.length() < radius){
        float pct = (diff.length() / radius)-1;
        diff.normalize();
        frc.x -= diff.x * pct * strength;
        frc.y -= diff.y * pct * strength;
    }
    
}

//------------------------------------------------------------
void ParticleNoise::addSpringBackForce(ofPoint _currPos, float _springBack){
    
    ofPoint currPos = _currPos;
    float springBack = _springBack;
    
    frc.x += springBack*(originalPos.x - currPos.x);
    frc.y += springBack*(originalPos.y - currPos.y);
    
}

//------------------------------------------------------------
void ParticleNoise::addClockwiseForce( float px, float py, float radius, float strength,  float _rotateSpeed, float _rotateR){
    
    ofVec2f posOfForce;
    posOfForce.set(px, py);
    
    ofVec2f diff = posOfForce - pos;
    
    if (diff.length() < radius){
        float pct = (diff.length() / radius)-1;
        ofPoint perp;
        
        perp = diff.getNormalized().rotate(_rotateSpeed,ofPoint(0,0,1));
        frc += perp* pct * strength * _rotateR ;
    }
}

//------------------------------------------------------------
void ParticleNoise::addCounterClockwiseForce(float px, float py, float radius, float strength,  float _rotateSpeed, float _rotateR){
    
    ofVec2f posOfForce;
    posOfForce.set(px, py);
    
    ofVec2f diff = posOfForce - pos;
    
    if (diff.length() < radius){
        float pct = (diff.length() / radius)-1;
        ofPoint perp;
        
        perp = diff.getNormalized().rotate(_rotateSpeed,ofPoint(0,0,1));
        frc -= perp* pct * strength * _rotateR ;
    }
}

//------------------------------------------------------------
void ParticleNoise::update(){
    
    vel += frc;
    pos += vel;
    
}

//------------------------------------------------------------
void ParticleNoise::addColor(bool _addR, ofVec2f _mouse, bool _colorMode, float _maxDistV, float _minDistV){
    
    float distV = ofDist(0,0, vel.x, vel.y);
    
    float brightness;
    
    if (!_colorMode) {
        brightness = ofMap(distV, _maxDistV, _minDistV, 1, 0.0);
        brightness = powf(brightness, 0.2);
        //brightness = ofMap(distV, 0.15,0, 1, 0, true);
        
        
        if (vel.x == 0 && vel.y == 0) {
            brightness = 0;
        }
        
        color.set(255*brightness, 255);
        
    } else {
        
        float angle = vel.angle(_mouse);
        float hueAngle = ofMap(angle, 0, 180, 0, 360);
        
        ofVec2f posOfForce;
        posOfForce.set(_mouse);
        
        brightness = ofMap(distV, _maxDistV, _minDistV, 1, 0.0);
        ofVec2f diff = posOfForce - pos;
        
        color.setHsb(0, 255, 255);
        color.setHueAngle(hueAngle);
        
        float hueMix = ofMap(angle, 0, 180, 0, 1);
        
        ofColor colorA = ofColor::lightBlue;
        ofColor colorB = ofColor::mediumAquaMarine;
        
        color.r = colorA.r * hueMix + colorB.r * (1-hueMix);
        color.g = colorA.g * hueMix + colorB.g * (1-hueMix);
        color.b = colorA.b * hueMix + colorB.b * (1-hueMix);
    }
}


//------------------------------------------------------------
void ParticleNoise::addNoise(){
    
    float noiseX = ofNoise(pos.x/100,0,ofGetElapsedTimef());
    float noiseY = ofNoise(pos.y/100,10000,ofGetElapsedTimef());
    
}

//------------------------------------------------------------
void ParticleNoise::draw(){
    ofSetColor(255,255,255);
    
    float size;
    float distV = ofDist(0,0, vel.x, vel.y);
    size = ofMap(distV, 1.0,0, 1, 0.1, true);
    
    ofDrawCircle(pos.x, pos.y, size*1.1);
    
}

