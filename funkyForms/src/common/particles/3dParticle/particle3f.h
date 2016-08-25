#pragma once

#include "ofMain.h"

class particle3f
{
    public:
        ofPoint pos;
        ofPoint vel;
        ofPoint frc;   // frc is also know as acceleration (newton says "f=ma")
			
    float lon, lat;
    
        particle3f();
		virtual ~particle3f(){};

        void resetForce();
		void addForce(float x, float y, float z);
		void addRepulsionForce(float x, float y, float z, float radius, float scale);
		void addAttractionForce(float x, float y, float z, float radius, float scale);
		
    
        ofPoint addRepulsionForceOffline(particle3f &p, float radius, float scale);
    
    
		void addRepulsionForce(particle3f &p, float radius, float scale);
		void addAttractionForce(particle3f &p, float radius, float scale);
		void addClockwiseForce(particle3f &p, float radius, float scale);
		void addCounterClockwiseForce(particle3f &p, float radius, float scale);
	
		
		void addDampingForce();
        
		void setInitialCondition(float px, float py, float pz, float vx, float vy, float vz);
        void update();
        void draw();
	
		void bounceOffWalls();
	
		bool  bFixed;
	
		float damping;
    
    ofPoint smoothedPos;

    protected:
    private:
};
