




#pragma once
#include "ofMain.h"
//#include "ofxVectorMath.h"
#include "ofxBox2dCircle.h"
#include "MonsterConst.h"


typedef struct {
	ofPoint a, b;
	float r;
	ofPoint bits[3];
} PopBits;

class MonsterParticles : public ofxBox2dCircle {
	
	
public:
	
	bool		bGoPop;
	bool		bDead;
	ofColor		clr;
	
	int			numPopBits;
	float		deadDate, age;
	float		r;
	
	PopBits	    *popBits;
	ofImage *img;
    
    
         void addAttractionPoint(ofPoint pt, float amt, float minDis=NULL) {
            if(body != NULL) {
                b2Vec2 P(pt.x/OFX_BOX2D_SCALE, pt.y/OFX_BOX2D_SCALE);
                b2Vec2 D = P - body->GetPosition();
                if(D.LengthSquared() < minDis) {;
                    P.Normalize();
                    b2Vec2 F = amt * D;
                    body->ApplyForce(F, P, true);

                }
            }
        }
         void addAttractionPoint(float x, float y, float amt, float minDis=NULL) {
            addAttractionPoint(ofPoint(x, y), amt, minDis);
        }
    
    
    
	// ----------------------------------------
	MonsterParticles() {
		img    = NULL;
		bDead  = true;
		bGoPop = false;
		
		
		popBits = NULL;
		
		
	
		
		enableGravity(false);
	}
	
	// ----------------------------------------
	void cleanUp() {
		delete[] popBits;
		popBits = NULL;
	}
	
	// ----------------------------------------
	void init() {
		
		bDead = false;
		
		int hex = particleColor[(int)ofRandom(0, NUM_PARTICLE_COLOR)];
		clr.r = (hex >> 16) & 0xff;
		clr.g = (hex >> 8)  & 0xff;
		clr.b = (hex >> 0)  & 0xff;
		clr.a = 255;
		
		age			= 0;
		deadDate	= ofRandom(30, 120);
		numPopBits  = (int)ofRandom(10, 20);
		
		
		
		popBits		= new PopBits[numPopBits];
		// set the pop bits
		for(int i=0; i<numPopBits; i++) {
			if(popBits == NULL) continue;
			popBits[i].r = 0;
			popBits[i].a.set(0,0);
			popBits[i].b.set(0,0);
			for(int j=0; j<3; j++) {
				float br = getRadius() / 2.2;///1.3;
				popBits[i].bits[j].set(ofRandom(-br,br), ofRandom(-br, br));
			}
		}
	}
	
	// ----------------------------------------
	void update() {
		
		
		age ++;
		if(age >= deadDate && !bGoPop) {
			bGoPop = true;	
			
			for(int i=0; i<numPopBits; i++) {
				if(popBits == NULL) continue;

				float n = (float)i/ (float)(numPopBits-1);
				
				popBits[i].a.x  = cos(n * TWO_PI) * (r+10);
				popBits[i].a.y  = sin(n * TWO_PI) * (r+10);
				
				popBits[i].b.x  = cos(n * TWO_PI) * (r+ofRandom(12, 45));
				popBits[i].b.y  = sin(n * TWO_PI) * (r+ofRandom(12, 45));
			
				popBits[i].r = ofRandom(3.0, 5.0);
				
			}
		}
		
		
		// time to pop !
		if(bGoPop) {
			
			r += (getRadius() / 3.3);
			clr.a -= 50.0;
			if(r <= 2 || clr.a <= 0.0) {
				bDead = true;
			}
			
			for(int i=0; i<numPopBits; i++) {
				if(popBits == NULL) continue;

				popBits[i].a += (popBits[i].b-popBits[i].a) / popBits[i].r;
			}
		}
		
		
		// monster farts fly up duhh
		addAttractionPoint(ofPoint(0, 0), 1.0, 100);
		
//        //------------------------------------------------


	}
	
	// ----------------------------------------
	void draw() {
		
		ofEnableAlphaBlending();
		if(bDead) return;
		
		//ofEnableAlphaBlending();
		ofPoint		pos = getPosition();
		
		glPushMatrix();
		glTranslatef(pos.x, pos.y, 0);
		
		if(!bGoPop) r   = getRadius();
		
		
		// the spary
		if(bGoPop) {
			ofSetColor(clr.r, clr.g, clr.b, clr.a);
			for(int i=0; i<numPopBits; i++) {
				if(popBits == NULL) continue;

				glPushMatrix();
				glTranslatef(popBits[i].a.x, popBits[i].a.y, 0);
				ofBeginShape();
				
				for(int j=0; j<3; j++) {
					ofVertex(popBits[i].bits[j].x, popBits[i].bits[j].y);
				}
				ofEndShape();
				glPopMatrix();
				
			}
		}
		
		ofSetColor(clr.r, clr.g, clr.b, clr.a);

		
		
		ofFill();
		if(img) {
			ofSetRectMode(OF_RECTMODE_CENTER);
			img->draw(0, 0, r*5, r*5);
			ofSetRectMode(OF_RECTMODE_CORNER);
		}
		
		ofFill();
		ofCircle(0, 0, r);
		glPopMatrix();
		ofDisableAlphaBlending();
	}
};