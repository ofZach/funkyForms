//
//  springyShape.cpp
//  springyShapes
//
//  Created by zach on 11/17/15.
//
//

#include "springyShape.h"


void springyShape::setup(ofPoint ptToStartFrom){
    
    targetAngle = PI;
    
    for (int i = 0; i < 10; i++){
        particle myParticle;
        
        float x = ptToStartFrom.x + 10 * cos ( (i / 20.0) * TWO_PI);
        float y = ptToStartFrom.y + 10 * sin ( (i / 20.0) * TWO_PI);
        myParticle.damping = 0.04;
        myParticle.setInitialCondition(x,y ,0,0);
        particles.push_back(myParticle);
    }
    
    // change this to
    // for (int i = 0; i < 10; i++){
    // to see a chain
    
    float springy = ofRandom(0.3, 0.6);
    float distance = ofRandom(2, 3.6);
    
    for (int i = 0; i < particles.size()-1; i++){
        springWidthIndex mySpring;
        mySpring.distance		= 20;
        mySpring.springiness	= springy;
        mySpring.aindex = i;// = & (particles[i  ]);
        mySpring.bindex = (i+1) % particles.size();// = & (particles[(i+1) % particles.size()]);
        springs.push_back(mySpring);
    }
    
}

void springyShape::update(){
    
//    for (int i = 0; i < springs.size(); i++){
//        springs[i].distance		= ofMap(mouseX, 0, ofGetWidth(), 0, 30, true);
//    }
    
    
    // on every frame
    // we reset the forces
    // add in any forces on the particle
    // perfom damping and
    // then update
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].resetForce();
    }
    
    for (int i = 0; i < particles.size(); i++){
        
        //particles[i].addRepulsionForce(mouseX, mouseY, 200, 0.7f);
        
        for (int j = 0; j < i; j++){
            particles[i].addRepulsionForce(particles[j], 200, 0.4);
        }
    }
    
    for (int i = 0; i < springs.size(); i++){
        springs[i].update(particles);
    }
    
    ofPoint diff = particles[particles.size()-1].pos - particles[0].pos;
    float angle = atan2(diff.y, diff.x);
    //cout << angle << endl;
    
    //float targetAngle = PI;
    float diffAngle = targetAngle - angle;
    while (diffAngle < -PI) diffAngle += TWO_PI;
    while (diffAngle > PI) diffAngle -= TWO_PI;
    
    float amount = ofMap(fabs(diffAngle), PI, 0, 3.0, 0.2, true);
    if (diffAngle < 0){
        particles[particles.size()-1].addCounterClockwiseForce(particles[0], 1000,amount);
    } else {
        particles[particles.size()-1].addClockwiseForce(particles[0], 1000, amount);
    }
    
    
    for (int i = 0; i < particles.size(); i++){
        //particles[i].bounceOffWalls();
        particles[i].addDampingForce();
        particles[i].update();
    }
    
    particles[0].bFixed = true;
    
    line.clear();
    for (int i = 0; i < particles.size(); i++){
        line.addVertex( particles[i].pos);
    }
    
    line = line.getResampledByCount(20);
    line = line.getSmoothed(11);
//    line = line.getSmoothed(11);
    
}

void springyShape::draw(){
    
    
    
    
   
   
    
    ofFill();
    
    if (line.size() > 0){
        ofCircle(line[0], 2);
        ofMesh m;
        m.setMode(OF_PRIMITIVE_LINE_STRIP);
        for (int i = 0; i < line.size(); i++){
            m.addVertex(line[i]);
            m.addColor(ofColor(255,255,255,ofMap(i, 0, line.size(), 255,0)));
        }
        m.draw();
        line.draw();
         ofCircle(line[line.size()-1], 2);
    }
    
//    for (int i = 0; i < line.size(); i++){
//        float size = ofMap(i, 0, line.size()-1, 0, 1);
//        
//        //float rad = 3 + powf(size, 1.3) * 10;
//        //sin(-i/10.0 + ofGetElapsedTimef() * 4.0) * 5
//        ofCircle(line[i], 3 + powf(size, 1.3) * 15 );
//    }
    
}

void springyShape::dragTo(ofPoint pt){
    particles[0].pos = pt;
}



