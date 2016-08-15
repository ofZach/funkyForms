
#pragma once
#include "ofMain.h"
//#include "ofxVectorMath.h"
#include "TreeConstants.h"
#include "ofCvTrackedBlob.h"
#include "MagicTree.h"


class TreePerson {
	
public:
	
	
	int id;
	ofRectangle		rect;
	ofVec2f		pos;
	float			area;
	
	
	int				age;
	bool			bGrowATree, bFadeOut, bDead;
	MagicTree		tree;
	
	
	ofPoint			colorD, color;
	float			alpha;
	
	float rate;
	
	float treeAge;
	
	
	void cleanUp() {
		
	}
	
	
	
	// --------------------------------------------
	TreePerson() {
		age = 0;
		area = 1.0;
		bGrowATree = false;
		bFadeOut = false;
		bDead = false;
		treeAge = 0;
		
		rate = ofRandom(5, 10);
	}
	
	
	// --------------------------------------------
	void init(ofCvTrackedBlob &blob) {
		
		//randomize();
		pos = blob.centroid;
		rect = blob.boundingRect;
		id = blob.id;
		/*
		 ptsCount   = 2;
		 numTreePts = 30;
		 
		 pts = new ofVec2f[numTreePts];
		 
		 for(int i=2; i<numTreePts; i++) {
		 pts[i] = pos;
		 }
		 */
		
		//string numI = ofToString((int)ofRandom(0, 2));
		//fern.addLeaf("sceneAssets/trees/Fern_Leaf_001.svg");
		
		
		
		color = 0;
		colorD.x = ofRandom(0, 255);
		colorD.y = ofRandom(0, 255);
		colorD.z = ofRandom(0, 255);
		alpha = 255;
	}	
	
	
	// -------------------------------------------- update 
	void update() {
		
		return;
		
		age ++;
		
		if(age > 20 && !bGrowATree) {
			printf("--- start growing the tree [%i]---\n", id);	
			bGrowATree = true;
		//	tree.initTree(pos.x, rect.y + (rect.height/1.3), (int)ofRandom(10, 30));
			
			
		}
		
		// ok we are alive and growing
		if(bGrowATree) {
			
			treeAge += 0.3;
			
			
		}
		
		
		
		color += (colorD-color) / rate;
		if(bFadeOut) {
			
		
			bool allLeavesIn = true;
			for(int i=0; i<tree.theLeaves.size(); i++) {
				if(!tree.theLeaves[i].bDone) allLeavesIn = false;
			}
			
			if(bFadeOut && allLeavesIn) {
				
				alpha -= 10.0;

			}
			
			
		}
		if(alpha <= 0) {
			bDead = true;	
		}
		
		/*
		 pts[0].x = pos.x;
		 pts[0].y = rect.y + rect.height;
		 
		 pts[1] = pts[0];
		 pts[1].x += 0;//pos.x + ofRandom(-0.1, 0.1);
		 pts[1].y += - 0.03;
		 
		 pts[1] *= 0.2;
		 
		 ofVec2f diff;
		 float len;
		 for(int i=2; i<ptsCount; i++) {
		 diff = pts[i] - pts[i-2];
		 len = diff.length();
		 pts[i] = pts[i-1] + (diff * 20) / len;
		 }
		 
		 
		 // time to grow
		 ptsCount ++;
		 if(ptsCount >= ptsCount) ptsCount = numTreePts-1;
		 
		 */
		//tree.update();
	}
	
	// --------------------------------------------
	void draw() {
		
		ofEnableAlphaBlending();
		
		// bounds
		ofNoFill();
		ofSetColor(255, 255, 255);
		ofRect(rect.x, rect.y, rect.width, rect.height);
		
		// tree lovely
		tree.draw();
	
		
		ofSetColor(25, 55, 225);
		ofDrawBitmapString(ofToString(area), pos.x, pos.y);
		//drawTheTree();
		
		ofDisableAlphaBlending();
		
	}
	
	
};