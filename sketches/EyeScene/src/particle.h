#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"

class flockingForce {
	public:
	
	int			count;
	ofVec2f	sum;
	float		distance;
	float		strength;
	
};

class particle
{
public:
    flockingForce cohesion;
    flockingForce seperation;
    flockingForce alignment;
    
    ofVec2f pos;
    ofVec2f vel;
    float angle = 0;
    ofVec2f frc;   // frc is also know as acceleration (newton says "f=ma")
    float prtRadius;
    particle();
    virtual ~particle(){};
    

    void resetForce();
    void addForce(float x, float y);
    void addRepulsionForce(float x, float y, float radius, float scale);
    void addAttractionForce(float x, float y, float radius, float scale);
    void addRepulsionForce(particle &p, float radius, float scale);
    void addAttractionForce(particle &p, float radius, float scale);
    
    void addForFlocking(particle &p);
    void addFlockingForce();
    
    void addDampingForce();
    
    void setInitialCondition(float px, float py, float vx, float vy);
    void setParticleRadius(float _prtRadius);
    void update();
    void draw();
    
    void bounceOffWalls();
    bool isCollide;
    bool isCollidePrev;
    
    ofVec2f getPos(){return pos;}
    float getAngle();
    ofVec2f getVel(){return vel;}
    float damping;
    
protected:
private:
};

#endif // PARTICLE_H
