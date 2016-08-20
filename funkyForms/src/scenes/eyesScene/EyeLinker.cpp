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
    initValues();
    eye eye;
    eyes.push_back(eye);
    eyes[0].closeEyeSpeed = 0.2;
    eyes[0].openEyeSpeed = 0.2;
//    eyes[0].delay = 2;
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
    glow.load("assets/glow.png");
}
void EyeLinker::initValues(){
    vel.set(0, 0);
}
void EyeLinker::setPos(ofVec2f _pos){
    float s = 0.9;
    if(counter==0){
        posPrev = _pos;
    }
    pos = pos * s + (1-s) * _pos;
    counter++;
    updateVelocity();
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
void EyeLinker::addFireworksParticle(ofVec2f _pos){
    gParticle p;
    p.id = curParticleId;
    float angle = ofRandom(-PI, PI);
    float x = sin(angle);
    float y = cos(angle);
    p.setInitialCondition(_pos.x, _pos.y, x, y);
    fireParticles.push_back(p);
}
void EyeLinker::addFireObject(){
    ofPolyline line;
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    fireObject f;
    f.mesh = mesh;
    f.color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255) );
    f.line = line;
    f.isDead = false;
    f.radius = ofRandom(1, 5);
    f.id = curParticleId;
    fireObjects.push_back(f);
}
// ------------- update
void EyeLinker::update(){
    updateVelocity();
    updateParameters();
    updatePhysics();
    updateEye();
    updateFading();
    updateFireworks();
}
void EyeLinker::updateFireworks(){
    // add particles
    if(vel.length() > 0.5){
        addFireworksParticle(pos);
        addFireObject();
    }
    curParticleId++;
    
    updateTrailParticles();
    updateTrailLines();
    updateTrailMeshes();
    updateFireObjectRemoval();
}
void EyeLinker::updateFireObjectRemoval(){
    // clear particles
    fireObjects.erase(std::remove_if(
                                       fireObjects.begin(),
                                       fireObjects.end(),
                                       
                                       [&](fireObject & f){
                                           return f.isDead;
                                       }
                                       ),
                        fireObjects.end()
                        );
}
void EyeLinker::updateTrailLines(){
    // create line
    for (auto &f : fireObjects){
        for(auto &p : fireParticles){
            if ( p.id == f.id ) {
                f.line.lineTo(p.pos);
            }
        }
    }
}
void EyeLinker::updateTrailMeshes(){
    for (auto &f : fireObjects){
        
        // create trail mesh
        f.mesh.clear();
        int index = ofMap(f.fadePct, 0, 1, 0, f.line.size()-1);
        for (int i = index; i < f.line.size(); i++) {
            ofVec2f tangent = f.line.getTangentAtIndex(i);
            ofVec2f p = f.line.getPointAtIndexInterpolated(i);
            
            float radius = ofMap(i, index, f.line.size()-1, 0, f.radius);

            ofVec2f p1 = p + tangent.getRotated(90)*radius;
            ofVec2f p2 = p + tangent.getRotated(-90)*radius;
            
            f.mesh.addVertex(p1);
            f.mesh.addVertex(p2);
        }
        
        // update fade
        f.fadePct += 0.01;
        if(f.fadePct > 1){
            f.fadePct = 1;
            f.isDead = true;
        }
    }
}
void EyeLinker::updateTrailParticles(){
    
    // update particles
    for(auto &p : fireParticles){
        p.resetForce();
    }
    for(auto &p : fireParticles){
        for(auto &p2 : fireParticles){
//            p.addRepulsionForce(p2, 10, 0.2);
            p.addClockwiseForce(p2, 50, 0.1);
        }
    }
    for(auto &p : fireParticles){
        p.addDampingForce();
        p.update();
    }
    
    // clear particles
    fireParticles.erase(std::remove_if(
                                       fireParticles.begin(),
                                       fireParticles.end(),
                                       
                                       [&](particle & p){
                                           return (p.vel.length() < 0.5);
                                       }
                                       ),
                        fireParticles.end()
                        );

}
void EyeLinker::updateEye(){
    for (int i = 0; i < eyes.size(); i++){
        eyes[i].update(pos);
        eyes[i].lookAt(particles[particles.size()-1].pos);
        if(fabsf(vel.y)>5){
            eyes[i].setUpdateBlink(false);
//            eyes[i].addAngryForce(true, 0.2, 0.6);
            eyes[i].lookAt(pos+ofVec2f(0, 100));
        }else{
            if(isSleep){
                eyes[i].setUpdateBlink(false);
                eyes[i].lookAt(pos+ofVec2f(0, 100));
//                eyes[i].addAngryForce(true, 0.01, 0.99);
            }else{
                eyes[i].setUpdateBlink(true);
//                eyes[i].addAngryForce(false, 0.1, 0.6);
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
void EyeLinker::updateVelocity(){
    vel = velSmooth * vel + (1-velSmooth) * (pos - posPrev);
    posPrev = pos;
}
bool EyeLinker::isFinished(){
    return  eyes[0].isCloseFinished();
}
// ------------- draw
void EyeLinker::draw(){
    drawFireworks();
    if(isGlow) drawGlow();
    for(auto eye: eyes){
        eye.draw();
    }
//    drawParticles();
}
void EyeLinker::drawFireworks(){
    ofFill();
    for(auto &p : fireParticles){
//        p.draw();
    }
    for (auto &f : fireObjects){
        float opacity = ofMap(f.fadePct, 0.5, 1, 255, 0, true);
        ofSetColor(f.color, opacity);
        f.mesh.draw();
        if(f.line.size()>0){
//            ofDrawCircle(f.line.getVertices()[f.line.size()-1], f.radius);
        }
    }
}
void EyeLinker::drawGlow(){
    ofPushMatrix();
    ofTranslate(eyes[0].getPos());
    ofPolyline l = eyes[0].lids.contour.getResampledByCount(glowResolution);
    for (int i = 0; i < l.size(); i++) {
        ofSetColor(255, glowOpacity);
        float x = l.getVertices()[i].x - glowRadius;
        float y = l.getVertices()[i].y - glowRadius;
        glow.draw(x, y, glowRadius*2, glowRadius*2);
    }
    ofPopMatrix();
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
