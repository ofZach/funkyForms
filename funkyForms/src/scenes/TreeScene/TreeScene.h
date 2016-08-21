
#pragma once

#include "ofMain.h"
#include "baseScene.h"

#include "TreeConstants.h"

//#include "ofxDaito.h"
#include "RandomFern.h"
//#include "ofxControlPanel.h"
#include "TreeBlob.h"
#include "MagicTree.h"
#include "particle.h"
#include "ButterFlyParticle.h"
#include "ButterflyAnimation.h"
#include "ofxGui.h"

class TreeScene : public baseScene {
	
public: 
	
	vector <int> butterFlyColor;
	
	void cleanUpScene();
	void setup();
	void update();
	void draw();
    void drawGui();
	void drawTop();
	void updateFlocking();
	
	// ---------------------- key and mouse
	void keyPressed(int key);
	void mouseDragged(int wx, int wy, int x, int y, int button);
	void mousePressed(int wx, int wy, int x, int y, int button);
	void mouseReleased(int wx, int wy, int x, int y, int button);
	bool bDebug;

    void blobBorn(int packetId, int id);
    void blobDied(int packetId, int id);
    void blobMoved(int packetId, int id);
    
   
	// ---------------------- key and mouse
	int						curStem;
	ofImage					theDot, theDotS;
	
	// ---------------------- Tree People
	vector <TreeBlob>				treeBlobs;
	vector <ButterFlyParticle>		butterflys;
	vector <MagicTree>				trees;
	
	// ---------------------- Ferns
	vector <RandomFern>				ferns;
	int								fernTimer;
	
	
	
	// ---------------------- Pcket info
	bool					bGotMyFirstPacket;
	//ofxControlPanel			panel;
    ofxPanel gui;
	
    ofParameter<float> treeDelay;
    ofParameter<float> peopleGlow;
    ofParameter<float> butterFlyGlow;
    ofParameter<float> treeBottomOffset;
    ofParameter<float> treeGrowW;
    ofParameter<float> treeGrowH;
    ofParameter<float> treeMin;
    ofParameter<float> treeMax;
    ofParameter<float> growRate;
    ofParameter<float> curveX;
    ofParameter<float> curveY;
    ofParameter<float> thetaG;
    ofParameter<float> fadeRate;
    ofParameter<float> butterFlyScale;
    ofParameter<float> butterFlySpeed;
    ofParameter<float> peopleColor;
    ofParameter<float> treeAddingTime;
    ofParameter<bool> bDoPeopleGlow;
    
    ofParameterGroup group;
    
};









