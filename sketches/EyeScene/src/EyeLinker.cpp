//
//  EyeLinker.cpp
//  EyeScene
//
//  Created by Zerc on 7/14/16.
//
//

#include "EyeLinker.hpp"

void EyeLinker::addEye(){
    
}
void EyeLinker::updateEbPhysics(){
    particlesEb[0].pos.set(pos.x, pos.y);
    for (int i = 0; i < particlesEb.size(); i++){
        particlesEb[i].resetForce();
    }
    for (int i = 0; i < particlesEb.size(); i++){
        particlesEb[i].addForce(0, 0.6);
    }
    for (int i = 0; i < springsEb.size(); i++){
        springsEb[i].update();
    }
    for (int i = 0; i < particlesEb.size(); i++){
        particlesEb[i].addDampingForce();
        particlesEb[i].update();
    }
}
void EyeLinker::setup(){
    eyes.push_back(*new eye);
    eyes[0].setup(ofVec2f(100, 100), 200, 200);
    eyes[0].setEyeColor(ofColor::darkGreen);
    particles.push_back(*new particle);
    particles[0].setInitialCondition(ofRandom(500,550),ofRandom(500,550),0,0);
    
    for (int i = 0; i < 2; i++){
        particle myParticle;
        myParticle.setInitialCondition(ofRandom(500,550),ofRandom(500,550),0,0);
        particlesEb.push_back(myParticle);
    }
    
    for (int i = 0; i < (particlesEb.size()-1); i++){
        spring mySpring;
        mySpring.distance		= 5;
        mySpring.springiness	= 0.03f;
        mySpring.particleA = & (particlesEb[i]);
        mySpring.particleB = & (particlesEb[(i+1)%particlesEb.size()]);
        springsEb.push_back(mySpring);
    }
}
void EyeLinker::update(ofVec2f _pos){
    float s = 0.9;
    pos = pos*s+(1-s)*_pos;
    for (int i = 0; i < particles.size(); i++){
        eyes[i].update(pos);
        eyes[i].lookAt(particlesEb[particlesEb.size()-1].pos);
        if(fabsf(vel.y)>5){
            eyes[i].setUpdateBlink(false);
            eyes[i].addAngryForce(true, 0.2, 0.6);
            eyes[i].lookAt(pos+ofVec2f(0, 100));
        }else{
            if(isSleep){
                eyes[i].setUpdateBlink(false);
                eyes[i].lookAt(pos+ofVec2f(0, 100));
                eyes[i].addAngryForce(true, 0.01, 0.99);
            }else{
                eyes[i].setUpdateBlink(true);
                eyes[i].addAngryForce(false, 0.1, 0.6);
            }
        }
        
        eyes[i].setScale(ofMap(vel.y, 20, -20, 0.5, 3., true));
        particles[i].resetForce();
    }
    updateEbPhysics();

    for (int i = 0; i < particles.size(); i++){
        particles[i].addDampingForce();
        particles[i].update();
    }
    

}
void EyeLinker::draw(){
    for(auto eye: eyes){
        eye.draw();
    }
}
void EyeLinker::setVel(ofVec2f _vel){
    vel = vel*0.9 + 0.1*_vel;
    if(vel.match(velPrev, 0.9)){
        idleCounter++;
    }else{
        idleCounter = 0;
        isSleep = false;
    }
    if(idleCounter>120){
        isSleep = true;
    }
    velPrev = vel;
}