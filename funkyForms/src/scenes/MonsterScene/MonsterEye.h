

#pragma once
#include "ofMain.h"
//#include "ofxVectorMath.h"
#include "ofxSvg.h"


class MonsterEye {


public:
	float	 size, sizeD, sizeV;

	ofVec2f pos, p, v, a;
	ofVec2f eb, ev;


	MonsterEye() {
		size = 0;
		sizeD = 0;
		sizeV = 0;
		eb.set(0,0);
		p.set(0,0); v.set(0,0); a.set(0,0);
		ev.set(0,0);
		size = ofRandom(20, 30);
        pos.set(0,0);
        
        cout << "eye cons" << p << " " << pos << endl;
        
	}


	void init(float _x, float _y) {
		pos.set(_x, _y);
		p.set(_x, _y);
		eb.set(_x, _y);
        
        cout << "eye init" << p << " " << pos << endl;
        
	}

	void update() {
		/* to springy
		// Spring
		float M = 1.8;   // Mass
		float K = 1.2;   // Spring constant
		float D = 0.92;  // Damping

		ofVec2f force = -K * (p - pos);    // f=-ky
		a = force / M;
		v = D * (v + a);
		p = p + v;
		*/
        cout << "eye update" << p << " " << pos << endl;
        
        
		p += (pos-p) / 3.0;

		ev = (ev * 0.7) + (ofPoint(pos.x, pos.y+10)-eb) / 8.0;
		eb += ev;

	}


	void draw() {

        
		ofFill();
		ofSetColor(255);
		ofCircle(p.x, p.y, size);
		ofSetColor(0);
		ofCircle(eb.x, eb.y, size/3.5);
        ofNoFill();
		ofSetColor(40, 40, 40);
		ofCircle(p.x, p.y, size);
	}

};
