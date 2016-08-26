
#pragma once

#include "ofMain.h"
#include "particle.h"
#include "spring.h"


class springWidthIndex : public spring {
    
public:
    
    int aindex;
    int bindex;
    
    
    //---------------------------------------------------------------------
    void update(vector < particle > & particles){
        
        ofVec2f pta = particles[aindex].pos;
        ofVec2f ptb = particles[bindex].pos;
        
        float theirDistance = (pta - ptb).length();
        float springForce = (springiness * (distance - theirDistance));
        ofVec2f frcToAdd = (pta-ptb).normalized() * springForce;
        
        particles[aindex].addForce(frcToAdd.x, frcToAdd.y);
        particles[bindex].addForce(-frcToAdd.x, -frcToAdd.y);
    }

};

class springyShape {


public:
    
    
    void setup(ofPoint ptToStartFrom);
    void update();
    void draw();
    
    void dragTo(ofPoint pt);
    
    
    // let's make a vector of them
    vector <particle> particles;
    vector <springWidthIndex> springs;
    
    float targetAngle;
    
     ofPolyline line;
};