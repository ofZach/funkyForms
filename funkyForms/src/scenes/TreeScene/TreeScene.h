
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


class TreeScene : public baseScene {
	
public: 
	
	vector <int> butterFlyColor;
	
	void cleanUpScene();
	void setup();
	void update();
	void draw();
	void drawTop();
	void updateFlocking();
	
	// ---------------------- key and mouse
	void keyPressed(int key);
	void mouseDragged(int wx, int wy, int x, int y, int button);
	void mousePressed(int wx, int wy, int x, int y, int button);
	void mouseReleased(int wx, int wy, int x, int y, int button);
	bool bDebug;

    void blobBorn(int id){ blobOn(0,0,id, 0);}
    void blobDied(int id){ blobOff(0,0,id, 0);}
   
    
	// ---------------------- blob tracking
	void blobOn( int x, int y, int bid, int order );
    void blobMoved( int x, int y, int bid, int order );    
    void blobOff( int x, int y, int bid, int order );
	
	
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

	
};









