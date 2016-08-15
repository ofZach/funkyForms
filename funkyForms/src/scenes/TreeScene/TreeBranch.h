#pragma once
#include "ofMain.h"
//#include "ofxVectorMath.h"

#define NUM_BRANCH_PTS 10

class TreeBranch {
	
public:
	
	float	alpha;	
	bool	bDone;
	bool	bMadeLeave;
	
	int				ptCount;
	ofPoint		pts[NUM_BRANCH_PTS];
	
	ofPoint		pos, des, base;
	float			girth, theta;
	float			step;
	
	// -----------------------------------------
	TreeBranch() {
		step		= 0;
		ptCount		= 0;
		girth		= ofRandom(10, 20);
		alpha		= 255;
		bDone		= false;
		bMadeLeave  = false;
	}
	
	
	// -----------------------------------------	
	void update() {
		
		// add points along
		if(!bDone && ptCount <= NUM_BRANCH_PTS-1) {
			
			// check to be safe
			if(ptCount >= NUM_BRANCH_PTS) ptCount = NUM_BRANCH_PTS-1;
			if(ptCount < 0)				  ptCount = 0;
			
			pts[ptCount].x = pos.x;
			pts[ptCount].y = pos.y;// - theta;			
			
			ptCount ++;
			theta += 2.0;
		}
		else {
			bDone = true;
		}

		
		pos += (des-pos) / 10.0;
		
		
	}
	
	// -----------------------------------------	
	void makeBranch(ofPoint branchPos, int stepIn, float dir) {
		
		base = branchPos;
		pos.set(0,0);
		des  = pos;
		des.y -= 30.0;
		
		
		des.x += (dir * stepIn);
		
		step = stepIn;
		
		girth = stepIn;
		if(girth > 10) girth = 10;
		if(girth < 2) girth = 2;
		
	}
	
	// -----------------------------------------	
	void draw() {
		glPushMatrix();
		glTranslatef(base.x, base.y, 0);
		drawThick();
		glPopMatrix();
	}
	
	// -----------------------------------------	
	void drawThick() {
		
		
		if(ptCount > 2) {
			ofVec3f pos1, pos2;
			ofVec3f perp;
			ofVec3f scr;
			scr.set(0, 0, 1);
			
			glBegin(GL_QUAD_STRIP);
			
			glVertex2f(-3, -3);
			glVertex2f(3, 3);
			
			for(int i=1; i<ptCount; i++) {
				
				pos1 = pts[i];
				pos2 = pts[i-1];
				perp.set(pos1 - pos2);
				perp.perpendicular(scr);
				
				float n			= ofMap((float)i, 1.0, (float)(ptCount-1), 1.0, 0.0);				
				float offx		= perp.x * sin(n) * (girth);
				float offy		= perp.y * sin(n) * (girth);
				
				glVertex2f(pos1.x - offx, pos1.y - offy);
				glVertex2f(pos1.x + offx, pos1.y + offy);
				
			}
			
			glVertex2f(-3, -3);
			glVertex2f(3, 3);
			
			glEnd();
		}
		
	}
	
	
	
};
