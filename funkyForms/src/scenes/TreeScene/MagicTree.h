#pragma once
#include "ofMain.h"
//#include "ofxVectorMath.h"
#include "TreeLeaf.h"
#include "TreeBranch.h"

#define MAX_TREE_PNTS 10


class MagicTree {
	
public:
	
	float curveRateX, curveRateY;
	float thetaRate;
	float growRate;
	
	float				addTime;
	int					growMod;
	float				trunkGirth;
	int					totalTreePts;
	int					treePtsCount;
	
	bool				bReadyToFadeOut;
	bool				bDoneDrowing;
	bool				bMadeLeaves;
	ofImage	*			img;
	int					numLeaves;
	vector <TreeLeaf>	theLeaves;
	
	
	// blob information
	int					frameAge;
	int					id;
	bool				bDead;
	bool				bNoBlobAnymore;
	ofVec2f			center;
	ofRectangle			rect;
	
	// tree position
	ofVec2f			root, rootD;
	ofVec2f			treeBase, treeBaseD;
	
	
	// the fade in and out
	float alpha;
	
	
	
	// Branches
	int						numBranches;
	vector <TreeBranch>		children;
	
	
	
	
	
	
	int pid;
	
	// ref of main tree branches
	//vector <MagicTree> children;
	
	bool	spawn;
	
	//
	float	 growInc, growSpeed;
	//int		 cnt;
	
	float		angle;
	
	ofVec2f	* pnts;
	//int			length;
	
	
	float		life;
	float		theta;
	ofVec2f	dir;
	ofVec2f	pos, vel, des;
	
	float fadeRate;
	
	// ------------------------------------------------------ The Magic Tree
	MagicTree() {
		fadeRate = 7;
		thetaRate = 0.02;
		curveRateX = 10.0;
		curveRateY = 10.0;
		growRate = 0.09;
		// the base of the trees
		treeBase.set(0,0);
		treeBaseD.set(0,0);
		
		trunkGirth		= ofRandom(8, 23);
		totalTreePts	= 0;
		treePtsCount	= 0;
		growMod			= 4;
		
		// blob information
		frameAge		= 0;
		bNoBlobAnymore  = false;
		bDead			= false;
		id				= -1;
		
		bReadyToFadeOut = false;
		// color & alpha
		alpha = 255;
		
		
		// num of brack i can have
		numBranches = 3;
		addTime = 1.0;
	}
	
	
	// ------------------------------------------------------ take a shower
	void cleanUp() {
		
	}
	
	
	// ------------------------------------------------------ init
	void initTree(float x, float y, int numPnts) {
		
		trunkGirth   = numPnts / 2.0;
		totalTreePts = numPnts;
		treePtsCount = 1;
		
		bDoneDrowing = false;
		spawn			= false;
		life			= 10.0;
		
		
		theta			= ofRandomf();
		angle			= 0;
		
		pnts			= new ofVec2f[totalTreePts];
		
		// tree point zero is the root
		growInc			= 0;
		
		
		//cnt				= 1;	// zero is the root start at 1
		root.x			= x;
		root.y			= y;
		rootD			= root;
		
		// the base of the tree
		treeBase.set(x, y);
		treeBaseD = treeBase;
		
		
		
		pos				= root;
		des				= root;
		
		setAngle(0, 1);
		
		printf("--- new branch[%i] ---\n", pid);
		
		
		
		
	}
	
	
	// ------------------------------------------------------ set angle to grow
	void setAngle(float theAngle, bool theDirection) {
		
		if(theAngle > 5.0 && theAngle < 5.0) theAngle = ofRandom(-45, 45);
		
		ofVec2f	norml;
		ofVec2f	delta = root - ofVec2f(root.x, root.y - 20);
		angle			  = theAngle;
		
		delta.normalize();
		delta.rotate(90+angle);
		
		// which way do we want to go
		if(theDirection)	norml.set(-delta.y, delta.x);
		else				norml.set(-delta.y, delta.x);
		
		dir = (norml * ofRandom(26.0, 50.0));
		
	}
	
	// ------------------------------------------------------
	void update() {
		
		
		// ease the tree around
		treeBaseD   = center;
		treeBaseD.y = rect.y + rect.height;
		treeBase = treeBaseD;//(treeBaseD-treeBase) / 40.0;
		
	
		
		
		if(treePtsCount < totalTreePts-1) {
			
			
			pnts[0] = root;			// keep attached to root
			growInc += growRate;		// simulate people moving
			
			
			theta += thetaRate;
			
			if(growInc >= addTime) {
				
				des += dir;
				des.x += cos(theta) * curveRateX;
				des.y += sin(theta) * curveRateY;
				growInc = 0;
				
				
			}
			
			// this needs to be here
			// we hit zero at this point
			// and need to add a new point
			if(growInc == 0) {
				
				treePtsCount ++;
				
				//	if(treePtsCount % growMod == 0) {
				//printf("-- add a branch here ---\n");
				
				
				// Right
				children.push_back(TreeBranch());
				children.back().pos = pos;
				children.back().makeBranch(pos, totalTreePts - treePtsCount, 10);
				
				// Left
				children.push_back(TreeBranch());
				children.back().pos = pos;
				children.back().makeBranch(pos, totalTreePts - treePtsCount, -10);
		
			}
		
			// springy growing -- or not - hehe
			//vel = (vel * 0.87) + (des - pos) / 8.0;
			pos += (des-pos) / 8.0;
			pnts[treePtsCount]	  = pos;
			
		}
		else {
			dir.set(0,0);
			bDoneDrowing = true;
		}
		
		
		
		// update all the children
		bool allBranchesDone = true;
		for(int i=0; i<children.size(); i++) {
			
			children[i].update();
		
			if(children[i].bDone == false) {
				allBranchesDone = false;
			}
			
			if(bReadyToFadeOut) {
				children[i].alpha = alpha;
			}
			
			// if we are done growing lets blow the
			// leaves off <-- nahhh looks cheap
			if(allBranchesDone) {
				//children[i].base.x -= 12;
				//children[i].base.y += 12;
			}
		
		}
		
		// start fading out
		if (allBranchesDone && bDoneDrowing) {
			//printf("-- tree Done --\n");
			bReadyToFadeOut = true;
			
			alpha -= fadeRate;
			
			if(alpha <= 0.0) {
				
				bDead = true;
				// new tree hit
//				ofxOscMessage msg;
//				msg.setAddress("/bang");									//	bang
//				msg.addStringArg("treeDone");								//	hit
//				msg.addIntArg(2);											//	SCENE 3
//				msg.addIntArg(id);											//	tree ID
//				msg.addFloatArg((float)center.x/(float)OFFSCREEN_WIDTH);	//  x (normalize)
//				msg.addFloatArg((float)center.y/(float)OFFSCREEN_HEIGHT);	//  centroid y (normalize)
//				
//				ofxDaito::sendCustom(msg);
			}
			
		}
		
	}
	
	// ------------------------------------------------------
	void draw() {
		
		ofEnableAlphaBlending();		
		glPushMatrix();
		glTranslatef(treeBase.x, treeBase.y, 0);
		
		
		int count = treePtsCount+1;
		if(count >= totalTreePts) count = totalTreePts-1;
		
		
		ofVec3f pos1, pos2;
		ofVec3f perp;
		ofVec3f scr;
		scr.set(0, 0, 1);
		ofSetColor(255,255,255, alpha);
	
		// draw the trunk
		glBegin(GL_QUAD_STRIP);
		for(int i=1; i<count; i++) {
			
			pos1 = pnts[i];
			pos2 = pnts[i-1];
			perp.set(pos1 - pos2);
			perp.perpendicular(scr);
			
			float n			= ofMap((float)i, 1.0, (float)count, 0.0, 1.0);
			float thickness = trunkGirth - (n * trunkGirth);
			float offx		= (perp.x * thickness);
			float offy		= perp.y * thickness;
			
			glVertex3f(pos1.x - offx, pos1.y - offy, 0);
			glVertex3f(pos1.x + offx, pos1.y + offy, 0);
			
		}
		glEnd();
		
		
		
		for(int i=0; i<children.size(); i++) {
			children[i].draw();
		}
		
		glPopMatrix();
		
	
	}
	
};
