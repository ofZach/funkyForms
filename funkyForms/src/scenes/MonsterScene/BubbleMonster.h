

#pragma once
#include "BaseMonster.h"
#include "MonsterEye.h"
#include "MonsterSVGParts.h"
//#include "ofxDaito.h"
#include "MonsterConst.h"
#include "MonsterHair.h"

#include "appSettings.h"    //2016

enum {

	BUBBLE_MONSTER,
	SPIKER_MONSTER,
	MEGA_SPIKER,
	MEGA_SPIKER_SOFT

};


//-------------------------------------------------------------- a giggle bubble
class GiggleBubble {
public:
	int		 id;
	bool	 matched;
	ofVec2f pos, des;
	float    radius;
	float    radiusD;
	float    radiusV;
};

//-------------------------------------------------------------- Bouncy Shape
typedef struct {
	int		 id;
	bool     bMatched;
	ofVec2f pos;
	ofVec2f vel;
	ofVec2f acc;
} BouncyShape;

//-------------------------------------------------------------- Monster
class BubbleMonster : public BaseMonster {


public:
	float				initAge;
	float				monsterDelayAge, monsterAge;
	float				age, area;
	int					monsterMode;


	// settings
	bool				bMonster;
	bool				bDebug;
	bool				bJustBecameMonster;

	// monster
	int					id;
    int                 packetId;
	ofVec2f             points;
	GiggleBubble		bubbles[NUM_BUBBLE_PNTS];
	MonsterSVGParts *   parts;


	// contours
	vector <ofPoint>	normals;
	vector <ofPoint>	contourSimple;
	vector <ofPoint>	contourSmooth;
	vector <ofPoint>	contourConvex;

	BouncyShape			contour[NUM_CONTOUR_PNTS];
	MonsterHair			hair[NUM_CONTOUR_PNTS];


	// eyes
	int					eyeID; // <--- heheh get it
	int					colorID;
	int					spikeMode; // temp;

	int					numEyes;
	MonsterEye			eyes[MAX_NUM_EYS];

	// spikes
	float				spikeLength[MAX_NUM_SPIKES];

	//-------------------------------------------------------------- init
	BubbleMonster() {
		
		bJustBecameMonster = false;
		bMonster  = false;
		id          = -1;
        packetId    = -1;
		bDebug	  = false;
		parts	  = NULL;
		eyeID	  = 0;
		spikeMode = 0;

		vel.set(0,0);
		pos.set(0,0);
		prePos.set(0,0);
		age = 0;

		monsterDelayAge = 1.7;
		monsterAge = 0;
		initAge = 0;
	}

	//-------------------------------------------------------------- init
	//void init(ofCvTrackedBlob &blob) {
    void init(ofPolyline &blob, int _packetId, int _id) {

        float scalex = 1;
        float scaley = 1;

		age = 0;
		area = 1.0;
		spikeMode    = (int)ofRandom(0, 2);
		numEyes		 = (int)ofRandom(1, 3);//MAX_NUM_EYS);
		eyeID		 = 5;//(int)ofRandom(0, parts->eyes.size());
		colorID		 = (int)ofRandom(0, NUM_MONSTER_COLOR);

		//monsterMode  = (int)ofRandom(0, 2);

		pos.x			 = blob.getCentroid2D().x;
		pos.y			 = blob.getCentroid2D().y;
        
        
		id    = _id;
        packetId = _packetId;

		//printf("	monster %i made\n", monsterID);

		// init the points
		updateContourPnts(blob.getVertices());

		// set initial radius
		for(int i=0; i<NUM_BUBBLE_PNTS; i++) {
			bubbles[i].radius  = 1.0;
			bubbles[i].radiusD = ofRandom(16.0, 20.0);
			bubbles[i].radiusV = 0;

			bubbles[i].id = -1;
			bubbles[i].matched = false;
			bubbles[i].pos = pos;
			bubbles[i].des = pos;
		}

		for(int i=0; i<NUM_CONTOUR_PNTS; i++) {

			// the contour
			contour[i].pos.set(0,0);
			contour[i].vel.set(0,0);
			contour[i].acc.set(0,0);
			contour[i].id = -1;
			contour[i].bMatched = false;


			// star hair in center
			hair[i].pos1 = pos;
			hair[i].pos2 = pos;
			hair[i].p = pos;
		}

		for(int i=0; i<MAX_NUM_SPIKES; i++) {
			spikeLength[i] = ofRandom(10.0, 60.0);
		}

		// set the eyes
		for(int i=0; i<numEyes; i++) {
			eyes[i].init(pos.x, pos.y);
		}
	}


	//-------------------------------------------------------------- normals
	void getNormals() {
		/*
		 // normal
		 ofVec2f	norml;
		 ofVec2f	diff;
		 ofPoint	mid;
		 ofPoint	normalScaled;

		 for(int k=1; k<monsters[j].contourSmooth.size(); k++) {

		 diff = monsters[j].contourSmooth[k] - monsters[j].contourSmooth[k-1];
		 diff.normalize();
		 norml.set(delta.y, -delta.x);

		 normalScaled = monsters[j].contourSmooth[k] + (norml * 40);
		 monsters[j].contourSmooth[k] = normalScaled;


		 }
		 */

	}


	//-------------------------------------------------------------- update contour pnts
	void updateContourPnts(vector <ofPoint> &cntPoints) {

		/*
		 for(int i=0; i<NUM_CONTOUR_PNTS; i++) {


		 float minDis = 999999.0;
		 int   minID  = -1;
		 for(int j=0; j<cntPoints.size(); j++) {


		 ofVec2f diff = bubbles[i].pos - cntPoints[j];
		 float	 len  = diff.length();

		 if(len < minDis) {
		 minID = j;
		 minDis = len;
		 }


		 }

		 bubbles[i].pos = cntPoints[minID];

		 }
		 */



	}
	//-------------------------------------------------------------- new radius
	void genNewRadius() {
		for(int i=0; i<NUM_BUBBLE_PNTS; i++) {
			bubbles[i].radiusD = ofRandom(16.0, 30.0);
		}
	}

	//-------------------------------------------------------------- update
	void update() {


        float scalex = 1;
        float scaley = 1;


		age ++;

		if(!bMonster) monsterAge = ofGetElapsedTimef() - initAge;
		if(monsterAge < monsterDelayAge && !bMonster) {

			for(int i=0; i<NUM_BUBBLE_PNTS; i++) {
				bubbles[i].radiusD = ofRandom(10, 30);
				bubbles[i].radius = 2;
				bubbles[i].pos = pos;
				bubbles[i].des = pos;
			}


		}

		// ITS MONSTER TIME
		else {
			bMonster = true;


		}



		ofPoint highestPnt;
		if(bMonster) {


			for(int i=0; i<NUM_BUBBLE_PNTS; i++) {

				// make the bubble bouncy
				bubbles[i].radiusV = (bubbles[i].radiusV * 0.6) + (bubbles[i].radiusD-bubbles[i].radius) / 10.0;
				bubbles[i].radius += bubbles[i].radiusV;

				//if(bubbles[i].pos.y < highestPnt.y) {
				//	highestPnt = bubbles[i].pos;
				//}
				bubbles[i].pos += (bubbles[i].des-bubbles[i].pos) / 1.02;
			}

			// just became a monster
			if(!bJustBecameMonster) {
//				ofxOscMessage msg;
//				msg.setAddress("/bang");							//	bang
//				msg.addStringArg("becameMonster");						//	new monster
//				msg.addIntArg(3);									//	SCENE 3
//				msg.addIntArg(monsterMode);					//  what kind of monster are we
//				msg.addIntArg(monsterID);									//	monster ID
//				msg.addIntArg(numEyes);
//				ofxDaito::sendCustom(msg);
				bJustBecameMonster = true;
				//printf("--- just bacame a monster --\n");
			}

			highestPnt.x = 0;
			highestPnt.y = 9999999;
			for(int i=0; i<contourSmooth.size(); i++) {


				float px = contourSmooth[i].x * scalex;
				float py = contourSmooth[i].y * scaley;
				if(py < highestPnt.y) {
					highestPnt.x = px;
					highestPnt.y = py;
				}

			}




			// do a conoutr match
			// now try and do a cnt match
			/*for(int i=0; i<NUM_BUBBLE_PNTS; i++) {

			 if(bubbles[i].matched == false) {

			 ofPoint p1 = bubbles[i].pos;

			 for(int j=0; j<contourSmooth.size(); j++) {

			 float dis = p1.distance(contourSmooth[j]);
			 if(dis < 100.0) {
			 bubbles[i].pos = contourSmooth[j];
			 bubbles[i].matched = true;
			 }

			 }
			 }
			 }
			 */

			for(int i=0; i<contourSmooth.size(); i++) {
				float ni  = (float)i / (float)(contourSmooth.size()-1);
				int	  ind = ni * NUM_BUBBLE_PNTS;

				if(ind < 0) ind = 0;
				if(ind >= NUM_BUBBLE_PNTS) ind = NUM_BUBBLE_PNTS-1;

				bubbles[ind].des = contourSmooth[i];

			}




		}

		// ---------------------------------- will come back to this
		/*
		 float minDistance = 1000000;
		 int minIndex = -1;

		 for (int j = 0; j < nBlobs; j++){

		 if (bFoundThisFrame[j]) continue;
		 // try to find the closest "hand" to this object, withing a range
		 float diffx = HOBJ[i].center.x - packet.centroid[j].x;
		 float diffy =  HOBJ[i].center.y - packet.centroid[j].y;
		 float distance = sqrt(diffx * diffx + diffy*diffy);

		 if (minDistance > distance){
		 minDistance = distance;
		 minIndex = j;
		 }
		 }
		 */
		/*
		 float minDis = 1000000; // start big
		 int	  minInd = -1;		// start false

		 // find the contour point closest to me
		 for(int i=0; i<contourConvex.size(); i++) {

		 if(contour[i].bMatched) continue;



		 }
		 */


		// ---------------------------------- move the eyes into position
		if(bMonster) {
//			float dy = rect.y+pos.y;
//            cout << "why " << dy << rect << " " << pos << endl;
//            
//			highestPnt.y = dy/2;

			// update the eyes
			for(int i=0; i<numEyes; i++) {
				eyes[i].update();
			}

			if(numEyes == 2) {
				eyes[0].pos = highestPnt;
				eyes[1].pos = highestPnt;

				eyes[0].pos.x -= 30;
				eyes[1].pos.x += 30;
			}

			if(numEyes == 1) {
				eyes[0].pos = highestPnt;
				eyes[0].pos.x = pos.x;
			}

		}


		// history of centroid
		vel    = pos-prePos;
		prePos = pos;


		//--------------------------- match up the giggle buble points ( --- well try to --- )
		/*float scalex = (float)OFFSCREEN_WIDTH / (float)packetW;
		 float scaley = (float)OFFSCREEN_HEIGHT / (float)packetH;

		 for(int j=0; j<cntPoints.size(); j++) {

		 //if(cntPoints[i].bMatched) continue;
		 float pct    = (float)j / (float)(cntPoints.size()-1);
		 int   ind = pct * NUM_BUBBLE_PNTS;
		 if(ind < 0) ind = 0;
		 if(ind >= NUM_BUBBLE_PNTS) ind = NUM_BUBBLE_PNTS-1;


		 bubbles[ind].pos.x = cntPoints[j].x * scalex;// * 2.0;
		 bubbles[ind].pos.y = cntPoints[j].y * scaley;// * 2.0;


		 }
		 */


	}


	//-------------------------------------------------------------- draw
	void draw() {

        float scalex = 1;
        float scaley = 1; 


		if(!bMonster) {

			// draw the shape of the body
			ofSetHexColor(monsterColor[colorID]);
			ofFill();
			ofBeginShape();
			for(int i=0; i<contourSimple.size(); i++) {
				ofVertex(contourSimple[i].x * scalex, contourSimple[i].y * scaley);
			}
			ofEndShape(true);

			return;

		}



		// ------------------------------------  a bubble monster
		if(monsterMode == BUBBLE_MONSTER) {

			for(int i=0; i<NUM_BUBBLE_PNTS; i++) {
				ofFill();
				ofSetHexColor(monsterColor[colorID]);
				ofCircle(bubbles[i].pos.x * scalex, bubbles[i].pos.y * scaley, bubbles[i].radius);
			}


			// draw the shape of the body
			ofSetHexColor(monsterColor[colorID]);
			ofFill();
			ofBeginShape();
			for(int i=0; i<contourSmooth.size(); i++) {
				ofCurveVertex(contourSmooth[i].x*scalex, contourSmooth[i].y*scaley);
			}
			ofEndShape(true);

		}

		/*
		 // ------------------------------------ MEGA a spiker monster (SMOOTHER)
		 if(monsterMode == MEGA_SPIKER || monsterMode == MEGA_SPIKER_SOFT) {

		 ofVec2f	norml, normlIn;
		 ofVec2f	diff;
		 ofPoint	mid;
		 ofPoint	normalScaled;

		 // draw the shape of the body
		 ofFill();
		 ofBeginShape();
		 for(int i=0; i<contourSmooth.size(); i++) {
		 ofCurveVertex(contourSmooth[i].x, contourSmooth[i].y);
		 }
		 ofEndShape(true);



		 // the spike HELL YA
		 for(int k=1; k<contourSimple.size(); k+=5) {

		 diff = contourSimple[k] - contourSimple[k-1];
		 diff.normalize();
		 norml.set(diff.y, -diff.x);

		 normlIn.set(-diff.y, diff.x);

		 normalScaled  = contourSimple[k] + (norml * (50+(area*60)));


		 if(monsterMode == MEGA_SPIKER) {
		 glLineWidth(6.0);
		 ofLine(contourSimple[k].x, contourSimple[k].y,
		 normalScaled.x, normalScaled.y);
		 glLineWidth(1.0);
		 } else {


		 float offset = 10;
		 if(normalScaled.x > pos.x) offset = -10;

		 glPushMatrix();
		 glTranslatef(contourSimple[k].x+offset, contourSimple[k].y-20, 0);
		 ofEllipse(0, 0, 10, 40);
		 glPopMatrix();
		 }

		 }
		 }
		 */

		// ------------------------------------  a spiker monster (convex)
		if(monsterMode == SPIKER_MONSTER) {

			// convex shape of the monster
			ofSetHexColor(monsterColor[colorID]);
			ofFill();
			ofBeginShape();
			for(int i=0; i<contourConvex.size(); i++) {
				ofVertex(contourConvex[i].x*scalex, contourConvex[i].y*scaley);
			}
			ofEndShape(true);

			// spikes
			ofFill();
			ofVec2f	norml, normlIn;
			ofVec2f	diff;
			ofPoint	mid;
			ofPoint	normalScaled, normalScaleIn;

			for(int k=1; k<contourConvex.size(); k++) {

				diff = contourConvex[k] - contourConvex[k-1];
				diff.normalize();
				norml.set(diff.y, -diff.x);

				normlIn.set(-diff.y, diff.x);

				normalScaled  = (norml * spikeLength[k]);

				//normalScaleIn = (normlIn * 40);

				if(spikeMode) {
					ofPushStyle();
					glLineWidth(10.0 * 1.0);
					ofLine(contourConvex[k].x*scalex, contourConvex[k].y*scaley,
						   (contourConvex[k].x*scalex) + normalScaled.x,
						   (contourConvex[k].y*scaley) + normalScaled.y);
					ofPopStyle();
				} else {


					float offset = 10;
					if((contourConvex[k].x*scalex) + normalScaled.x > pos.x) offset = -10;

					ofTriangle((contourConvex[k].x*scalex) + offset,
							   (contourConvex[k].y*scaley) - 20,
							   (contourConvex[k].x*scalex) + normalScaled.x,
							   (contourConvex[k].y*scaley) + normalScaled.y,
							   (contourConvex[k].x*scalex) + offset,
							   (contourConvex[k].y*scaley) + 20);
				}

			}


		}


		//	ofNoFill();
		//	ofRect(rect.x, rect.y, rect.width, rect.height);



		if(bDebug) {
			// draw the vel of the monster
			float len = vel.length() * 20.0;
			float arrowsize = 30;
			ofVec2f v;
			float ang = v.angle(vel);
			ofSetColor(255, 0, 0);
			glPushMatrix();
			glTranslatef(pos.x, pos.y, 0);
			glRotatef(ang, 0, 0, 1);
			ofLine(0,0,len,0);
			ofLine(len,0,len-arrowsize,+arrowsize/2);
			ofLine(len,0,len-arrowsize,-arrowsize/2);
			glPopMatrix();
		}

		// draw the eyes
		for(int i=0; i<numEyes; i++) {
			eyes[i].draw();
		}



		if(bDebug) {

			ofEnableAlphaBlending();
			ofFill();
			ofSetColor(255, 25, 0, 100);
			ofCircle(pos.x, pos.y, 30);
			ofSetColor(255, 255, 250);
			ofDrawBitmapString(ofToString(monsterAge), pos.x, pos.y);
			ofDisableAlphaBlending();

		}


	}

};
