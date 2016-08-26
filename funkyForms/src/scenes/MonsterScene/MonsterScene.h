

#pragma once

#include "ofMain.h"
#include "baseScene.h"

// the funky monsters
#include "BubbleMonster.h"
//#include "ofxContourAnalysis.h"
#include "MonsterParticles.h"
#include "ofxBox2d.h"
#include "MonsterSVGParts.h"
//#include "ofxFBOTexture.h"
#include "MonsterBall.h"
//#include "ofxDaito.h"
#include "MonsterConst.h"
#include "MonsterData.h"
#include "MonsterLine.h"
#include "ofxXmlSettings.h"
#include "MonsterWindow.h"
#include "MonsterDust.h"
//#include "ofxControlPanel.h"

#include "ofxGui.h"




/*
 OSC setup:
 
 EVENT: 
 newMonster
 monsterMove
 deadMonster
 
 DATA:
 scene			 = int
 type of monster = int
 id				 = int
 center x		 = float <-- normailized
 center y	     = float <-- normailized
 width			 = flaot <-- normailized
 height			 = float <-- normailized
 
 
 Particle Events:
 
 EVENT:
 particleHit
 
 DATA:
 scene			 = int
 x				 = float <-- normailized
 y				 = float <-- normailized
 
 
 */


class MonsterScene : public baseScene , public b2ContactListener{
	
public:
    
    void registerVideoSettings(){
        vidSettings = STAGE_VIDEO;
       
    }
	
	// ---------------------- 
	void setup();
	void update();
	void draw();
    void drawGui();
	
	void saveMonsterSettings();
	void loadMonsterSettings();
	void cleanUpScene();
	
	// ---------------------- mouse & keyboard
	void mousePressed(int wx, int wy, int x, int y, int button);
	void keyPressed(int key);
	void mouseDragged(int wx, int wy, int x, int y, int button);
	void mouseReleased(int wx, int wy, int x, int y, int button);
	
    
    void blobBorn(int packetId, int id);
    void blobDied(int packetId, int id);
    void blobMoved(int packetId, int id);
    
//	// ---------------------- blob tracking
//	void blobOn( int x, int y, int bid, int order );
//    void blobMoved( int x, int y, int bid, int order );     // blob moved??????
//    void blobOff( int x, int y, int bid, int order );
//
    void start(){
        //ofSetFrameRate(30);
        
    }
    void stop(){
        cleanUpScene();
        //ofSetFrameRate(60);
    }
	// ---------------------- box2d bump ---- !a bit of a hack
//	void Add(const b2ContactPoint* point);  // 2016
//	void Remove(const b2ContactPoint* point);
	
	//ofxControlPanel				panel;  // 2016
	ofPoint OFFSET;
	float W, H, SCALE;
	
	
	// get a monster here
	BubbleMonster&				getMonsterById( int monsterId );
	
	// colors
	int							monsterColor[NUM_MONSTER_COLOR];
	int							ballCounter;
	int							timeSinceLastBurst;
	
	
	// ---------------------- utils
	void createBuildingContour();
	void drawTop();
	
	ofFbo                       FBO;    // 2016
	ofImage						dotImage;
	
	// ---------------------- settings
	bool						bMonsterTimer;
	bool						bDebug;
	ofxXmlSettings				xmlSaver;
	vector <MonsterWindow>		windowPnts;
	bool						bGotMyFirstPacket;
	
	// ---------------------- 
	// Ferry Building
//	FerryBuilding				ferryBuilding;/
    //vector <MonsterLine>		box2dBuilding;
	
    vector <shared_ptr<ofxBox2dEdge> >   edges;
    
	
	// tracking
	int							lastFrameRendered;
	int							lastTypeofMonster;
    
	// particles
	ofxBox2d					box2d;
	int							particleCount;
	vector <shared_ptr<MonsterParticles>>	monsterParticles;
	vector <MonsterDust>		dust;
	
	// monsters
	MonsterSVGParts				parts;
	//ofxContourAnalysis			contourAnalysis;       //2016
	vector <BubbleMonster>		monsters;
	vector <shared_ptr<MonsterBall>>		balls;
	//vector <MonsterRect>		rects;
	vector <ofPoint>			sclContour;
    
    
    ofParameterGroup group;
    ofParameter<float> monsterAge;
    ofParameter<float> maxBallAge;
    ofParameter<float> ballGlow;
    ofParameter<float> ballSizePct;
    ofParameter<bool> rebuildBuilding;
    ofParameter<bool> debug;
    
    ofxPanel gui;
   
    
    
};





