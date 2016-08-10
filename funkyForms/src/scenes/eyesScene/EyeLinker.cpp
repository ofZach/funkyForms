//
//  EyeLinker.cpp
//  EyeScene
//
//  Created by Zerc on 7/14/16.
//
//

#include "EyeLinker.hpp"
// ------------- setup
void EyeLinker::setup(){
    eyes.push_back(*new eye);
    eyes[0].setup(pos, width, height);
    eyes[0].setEyeColor(ofColor::darkGreen);
    for (int i = 0; i < 2; i++){
        particle myParticle;
        myParticle.setInitialCondition(pos.x, pos.y ,0,0);
        particles.push_back(myParticle);
    }
    
    for (int i = 0; i < (particles.size()-1); i++){
        spring mySpring;
        mySpring.distance		= 0;
        mySpring.springiness	= 0.03f;
        mySpring.particleA = & (particles[i]);
        mySpring.particleB = & (particles[(i+1)%particles.size()]);
        springs.push_back(mySpring);
    }
}
void EyeLinker::setPos(ofVec2f _pos){
    float s = 0.9;
    pos = pos * s + (1-s) * _pos;
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
void EyeLinker::setScale(float scale){
    scale = scale;
    for(auto &e : eyes){
        e.setScale(scale);
    }
}
void EyeLinker::setSize(float w, float h){
    width = w;
    height = h;
}
void EyeLinker::out(){
    for (auto &e : eyes){
        e.close();
    }
}
// ------------- update
void EyeLinker::update(){
    updateParameters();
    updatePhysics();
    updateEye();
    updateFading();
}
void EyeLinker::updateEye(){
    for (int i = 0; i < eyes.size(); i++){
        eyes[i].update(pos);
        eyes[i].lookAt(particles[particles.size()-1].pos);
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
//        eyes[i].setScale(ofMap(vel.y, 20, -20, 0.5, 3., true));
    }
}
void EyeLinker::updatePhysics(){
    
    particles[0].pos.set(pos.x, pos.y);
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].resetForce();
    }
    for (int i = 0; i < springs.size(); i++){
        springs[i].update();
    }
    for (int i = 0; i < particles.size(); i++){
        particles[i].addDampingForce();
        particles[i].update();
    }
}
void EyeLinker::updateFading(){
    if(isFading){
        // todo: fading
    }
}
void EyeLinker::updateParameters(){
    for(auto &e : eyes){
        e.width = width;
        e.height = height;
    }
}
bool EyeLinker::isFinished(){
    return  eyes[0].isCloseFinished();
}
// ------------- draw
void EyeLinker::draw(){
    for(auto eye: eyes){
        eye.draw();
    }
//    drawParticles();
}
void EyeLinker::drawParticles(){
    ofFill();
    int i = 0;
    ofColor colors[3] = {ofColor::blue, ofColor::green, ofColor::red};
    for(auto &p : particles){
        ofSetColor(colors[i%2]);
        ofDrawCircle(p.pos, 5);
        p.draw();
        i++;
    }
}