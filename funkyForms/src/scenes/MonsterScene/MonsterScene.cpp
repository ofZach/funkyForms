

#include "MonsterScene.h"
//#include "ofxVectorMath.h"
#include "ofxBox2dPolygonUtils.h"

//-------------------------------------------------------------- setup
void MonsterScene::setup(){

    sceneName = "monsterScene";
    
    
    gui.setup("settings_monsterScene", "settings_monsterScene.xml");

    
    group.add(monsterAge.set("monsterAge", 1.3, 0, 10));
    group.add(maxBallAge.set("maxBallAge", 5.3, 0, 30));
    group.add(ballGlow.set("ballGlow", 1.0, 0, 1));
    group.add(ballSizePct.set("ballSizePct", 1.0, 0.0, 1.0));
    group.add(rebuildBuilding.set("rebuildBuilding", false));
    group.add(debug.set("debug", false));
    
    gui.add(group);
    gui.loadFromFile("settings_monsterScene.xml");
    
    
	bMonsterTimer	  = true;
	bDebug			  = false;
	bGotMyFirstPacket = false;
	
	//panel.setValueB("DEBUG", 0);
	
	// box2d
	box2d.init();
	box2d.setGravity(0, 10);
	box2d.checkBounds(true);
	box2d.setFPS(30.0);
	printf("monster box2d allocated\n");

	// load the ferry contour
	//ferryBuilding.setupBuilding("buildingRefrences/buidlingFiles/BuildingMonsters_1.xml");
	loadMonsterSettings();
	
    // 2016
    //box2d.getWorld()->SetContactListener(this);



	W = 1.0;
    H = 0; //panel.getValueF("BOTTOM_OFFSET");
    SCALE = 1.0; //panel.getValueF("SCALE");

	// no particles yet
	particleCount		= 0;
	lastTypeofMonster	= -1;
	timeSinceLastBurst	= 0;

	// load all the svg parts
	dotImage.loadImage("sceneAssets/monsters/dot.png");
    
    createBuildingContour();
}

//-------------------------------------------------------------- update
void MonsterScene::update(){

	
    //cout << "body count " << box2d.getBodyCount() << endl;
    
    //float scalex = 1;
    //float scaley = 1;
	
	
//	bDebug = panel.getValueB("DEBUG");
//	if(panel.getValueB("REBUILD")) {
//		createBuildingContour();
//		panel.setValueB("REBUILD", 0);
//	}

//	panel.update();
	box2d.update();



	// add some balls
    if(ballCounter >= 20 && ofGetFrameRate() > 30) {


		// Add Ball every 20 times
		for(int i=0; i<(int)ofRandom(1, 5); i++) {

			float bx = (RM->getWidth()/2) + ofRandom(-20, 20);
			float by = (100 + ofRandom(-20, 20));

			//bx -= ((RM->getWidth() - W)/2);
			//by -= (RM->getHeight() - H);
			//MonsterBall bub;
			
            shared_ptr<MonsterBall> bub =  shared_ptr<MonsterBall> (new MonsterBall());
            
            
			balls.push_back(bub);
            
            balls.back()->initTime = ofGetElapsedTimef();
             balls.back()->setPhysics(1.0, 0.93, 0.1); // mass - bounce - friction
             balls.back()->setup(box2d.getWorld(), bx, by, ofRandom(5, 15));
             balls.back()->img = &dotImage;
            
            
		}
		ballCounter = 0;


		// 0 - 50 probality to add a ton of particles
		// ok add a bunch
		if((int)ofRandom(0, 20) == 10 && timeSinceLastBurst > 30) {

			for(int i=0; i<(int)ofRandom(20, 100); i++) {
				
				float bx = ofRandom(0, RM->getWidth());// ofRandom(-520, 520);
				float by = 500;

				//bx -= ((RM->getWidth() - W)/2);
				//by -= (RM->getHeight() - H);

                //MonsterBall bub;
                shared_ptr<MonsterBall> bub =  shared_ptr<MonsterBall> (new MonsterBall());
            
                bub->initTime = ofGetElapsedTimef();
				bub->setPhysics(1.0, 0.93, 0.1); // mass - bounce - friction
				bub->setup(box2d.getWorld(), bx, by, ofRandom(5, 35));
				bub->img = &dotImage;
				balls.push_back(bub);
			}
			
			if((int)ofRandom(0, 10) == 5) {
				
				for(int i=0; i<(int)ofRandom(80, 100); i++) {
					
					float bx = ofRandom(0, RM->getWidth());// ofRandom(-520, 520);
					float by = 500;
					
					//bx -= ((RM->getWidth() - W)/2);
					//by -= (RM->getHeight() - H);
					
					//MonsterBall bub;
                    shared_ptr<MonsterBall> bub =  shared_ptr<MonsterBall> (new MonsterBall());
                    
                    bub->initTime = ofGetElapsedTimef();
					bub->setPhysics(1.0, 0.93, 0.1); // mass - bounce - friction
					bub->setup(box2d.getWorld(), bx, by, ofRandom(5, 6));
					bub->img = &dotImage;
					balls.push_back(bub);
				}
				
			}

			timeSinceLastBurst = 0;
		}

	}

	timeSinceLastBurst ++;
	ballCounter ++;


	// --------------------- particles
	for(int i = 0; i < monsterParticles.size(); i++) {
		monsterParticles[i]->update();

	}
	for(int i=monsterParticles.size()-1; i>=0; i--) {
		// sorry time to go away
		if(monsterParticles[i]->bDead) {
            //cout << "------------------------------------------" << endl;
			monsterParticles[i]->cleanUp();
            monsterParticles[i]->destroy();   // 2016;
			monsterParticles.erase(monsterParticles.begin() + i);
		}

		ofPoint mpos = monsterParticles[i]->getPosition();
		if(mpos.y > RM->getHeight()) {
			monsterParticles[i]->bDead = true;
		}
	}
	for(int i=balls.size()-1; i>=0; i--) {

		ofPoint ps = balls[i]->getPosition();
		
		balls[i]->age = ofGetElapsedTimef() - balls[i]->initTime;
        balls[i]->alphaPct = ballGlow; //panel.getValueF("BALL_GLOW");
        balls[i]->sizePct  = ballSizePct; //panel.getValueF("BALL_SIZE_PCT");
		
        if(balls[i]->age > maxBallAge){  // 2016  ///panel.getValueF("BALL_AGE")) {
			balls[i]->color.a -= 10.0;
			
		}
		
		if(ps.y > RM->getHeight() || balls[i]->color.a <= 0.0 ||
           ps.x < 0 || ps.x >= RM->getWidth()) {

			balls[i]->destroy();
			balls.erase(balls.begin() + i);
		}
		
	}




	// --------------------- update the monster contour pnts
    for (int packetId = 0; packetId < 2; packetId++){
        for(int i=0; i<cvData[packetId]->blobs.size(); i++) {

            int lookID = cvData[packetId]->blobs[i].id;

            for(int j=monsters.size()-1; j>=0; j--) {

                // yes we match
                if(monsters[j].id == lookID &&
                   monsters[j].packetId == packetId) {
                    
                    ofPolyline line  = cvData[packetId]->blobs[i].blob;
                    for (auto & pt : line){
                        pt = cvData[packetId]->remapForScreen(packetId == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
                    }
                    
                    //line.flagHasChanged();
                    
                    ofRectangle newRec = line.getBoundingBox();
                    
    //				newRec.x		*= scalex;
    //				newRec.y		*= scaley;
    //				newRec.width	*= scalex;
    //				newRec.height	*= scaley;
                    
                    /*
                    sclContour.assign(tracker->blobs[i].pts.size(), ofPoint());
                    for(int e=0; e<tracker->blobs[i].pts.size(); e++) {
                        sclContour[e].x = tracker->blobs[i].pts[e].x * scalex;
                        sclContour[e].y = tracker->blobs[i].pts[e].y * scaley;
                    }*/

                    
                    // the contour (fixed)
                    line.flagHasChanged();
                    
                    monsters[j].pos.x  = line.getCentroid2D().x;
                    monsters[j].pos.y  = line.getCentroid2D().y;
                    
                    monsters[j].rect = newRec;
                    
                    //cout << "adding " << newRec << " " << line.getCentroid2D() << endl;
                    
                    // a simple contour
                    //monsters[j].contourSimple.assign(tracker->blobs[i].pts.size(), ofPoint());
                    
                    ofPolyline simp;
                    ofPolyline smooth;
                    ofPolyline convex;
                    simp.addVertices(line.getVertices());
                    smooth.addVertices(line.getVertices());
                    convex.addVertices(line.getVertices());
            
                    simp.simplify(0.5);
                    smooth = smooth.getSmoothed(3);
                    
                    
                    monsters[j].contourSimple = simp.getVertices();
                    monsters[j].contourSmooth = smooth.getVertices();
                    monsters[j].contourConvex = getConvexHull(convex.getVertices()).getVertices();
                    
                    //contourAnalysis.simplify(tracker->blobs[i].pts, monsters[j].contourSimple, 0.50);

                    // a smooth contour
                    //monsters[j].contourSmooth.assign(monsters[j].contourSimple.size(), ofPoint());
                    //contourAnalysis.smooth(monsters[j].contourSimple, monsters[j].contourSmooth, 0.2);

                    // a convex contour
                    //monsters[j].contourConvex.assign(monsters[j].contourSimple.size(), ofPoint());
                    //contourAnalysis.convexHull(monsters[j].contourSimple, monsters[j].contourConvex);

                    monsters[j].updateContourPnts(line.getVertices());

                    
                }
            }
        }
    }



	// --------------------- Monsters
	for(int i = 0; i < monsters.size(); i++) {
		//monsters[i].SCALE = panel.getValueF("SCALE");
        
		monsters[i].bDebug = bDebug;
        monsters[i].monsterDelayAge = monsterAge; //panel.getValueF("MONSTER_AGE");
		monsters[i].update();

	}


	// --------------------- packet info
//	if(packet.frameNumber >= 0 && !bGotMyFirstPacket) {
//		printf("got my first packet - %i\n", packet.frameNumber);
//		bGotMyFirstPacket = true;
//
//		contourAnalysis.setSize(packet.width, packet.height);
//		//createBuildingContour();
//	}


}

////-------------------------------------------------------------- get monster by id
//BubbleMonster& MonsterScene::getMonsterById( int monsterId ) {
//
//	for( int i=0; i<monsters.size(); i++ ) {
//		if( monsters[i].monsterID == monsterId ) {
//			return monsters[i];
//		}
//	}
//
//}

//-------------------------------------------------------------- blob events
void MonsterScene::blobBorn( int packetId, int id ) {

    int bid = id;
    
	if(!bMonsterTimer) return;
	
	printf("monster on - %i\n", bid);
    
    
    ofPolyline line = cvData[packetId]->blobs[cvData[packetId]->idToBlobPos[bid]].blob;
    for (auto & pt : line){
        pt = cvData[packetId]->remapForScreen(packetId == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
    }
	//ofxCvBlob blober = tracker->getById(bid);

	// if i am hole make a shape instead
	if(true) {

		BubbleMonster monster;
		monster.id = bid;

		// set a new monster type each time
		monster.monsterMode = (int)ofRandom(0, 2);
		if(monster.monsterMode == lastTypeofMonster) {
			int newMonsMode = monster.monsterMode ++;
			newMonsMode %= 2;
			monster.monsterMode = newMonsMode;
		}
		lastTypeofMonster = monster.monsterMode;

		// set a new monster color



		// set the parts
		
		monster.parts = &parts;
        monster.init( line, packetId, bid ) ;//tracker->getById(bid) );
		monster.area = (float)(line.getBoundingBox().height*line.getBoundingBox().width) / (float)(cvData[0]->width*cvData[0]->height);
		monster.initAge = ofGetElapsedTimef();
		monsters.push_back(monster);


//		ofxOscMessage msg;
//		msg.setAddress("/bang");							//	bang
//		msg.addStringArg("newMonster");						//	new monster
//		msg.addIntArg(3);									//	SCENE 3
//		msg.addIntArg(monsters.back().monsterMode);					//  what kind of monster are we
//		msg.addIntArg(bid);									//	monster ID
//		msg.addFloatArg((float)x/(float)packet.width);		// centroid x (normalize)
//		msg.addFloatArg((float)y/(float)packet.height);		// centroid y (normalize)
//		msg.addFloatArg((float)blober.boundingRect.width/(float)packet.width);		// width (normalize)
//		msg.addFloatArg((float)blober.boundingRect.height/(float)packet.height);		// hieght (normalize)
//		msg.addIntArg(monster.numEyes);
//		msg.addIntArg(monster.colorID);
//
//		ofxDaito::sendCustom(msg);

	}



//	ofxOscMessage msg2;
//	msg2.setAddress("/bang");
//	msg2.addStringArg("totalMonsters");
//	msg2.addIntArg((int)monsters.size());
//	ofxDaito::sendCustom(msg2);


}

//--------------------------------------------------------------
void MonsterScene::blobMoved(int packetId, int id){
    
	
    int bid = id;
	
	if(!bMonsterTimer) return;
	
    
	//float scalex = (float)RM->getWidth() / (float)cvData[0]->width;
	//float scaley = (float)RM->getHeight() / (float)cvData[0]->height;
	
    
    ofPolyline line = cvData[packetId]->blobs[cvData[packetId]->idToBlobPos[bid]].blob;
    ofPoint centroid = line.getCentroid2D();
    ofPoint newPT  = cvData[packetId]->remapForScreen(packetId == 0 ? SCREEN_LEFT : SCREEN_RIGHT, centroid);
    
    
	
	for(int i=monsters.size()-1; i>=0; i--) {
		if(monsters[i].id == bid &&
           monsters[i].packetId == packetId) {

			// tell daito that the monster just moved
			
//            ofPolyline line = cvData[0]->blobs[cvData[0]->idToBlobPos[bid]].blob;
//            for (auto & pt : line){
//                pt = cvData[0]->remapForScreen(SCREEN_LEFT, pt);
//            }
            
            //ofxCvBlob blober = tracker->getById(bid);

//			ofxOscMessage msg;
//			msg.setAddress("/bang");														//	bang
//			msg.addStringArg("monsterMove");												//	new monster
//			msg.addIntArg(3);																//	SCENE 3
//			msg.addIntArg(monsters[i].monsterMode);											//  what kind of monster are we
//			msg.addIntArg(bid);																//	monster ID
//			msg.addFloatArg((float)x/(float)packet.width);									// centroid x (normalize)
//			msg.addFloatArg((float)y/(float)packet.height);									// centroid y (normalize)
//			msg.addFloatArg((float)blober.boundingRect.width/(float)packet.width);			// width (normalize)
//			msg.addFloatArg((float)blober.boundingRect.height/(float)packet.height);		// hieght (normalize)
//			ofxDaito::sendCustom(msg);

			monsters[i].genNewRadius();
			monsters[i].area = (float)(line.getBoundingBox().height*line.getBoundingBox().width) / (float)(cvData[packetId]->width*cvData[packetId]->height);

            // 2016
			//---------- add some particle love -- ewww
			if(monsterParticles.size() < MAX_MONSTER_PARTICLES) {

				float bx = (newPT.x) + ofRandom(-30, 30);
				float by = (newPT.y) + ofRandom(-30, 30);

				monsterParticles.push_back(shared_ptr<MonsterParticles> (new MonsterParticles()));
				monsterParticles.back()->setPhysics(3.0, 0.93, 0.1); // mass - bounce - friction
				monsterParticles.back()->setup(box2d.getWorld(), bx, by, ofRandom(4, 30));
				monsterParticles.back()->img = &dotImage;
				monsterParticles.back()->init();
                monsterParticles.back()->enableGravity(false);

			}
		}
	}

}

//--------------------------------------------------------------
void MonsterScene::blobDied(int packetId, int id){
    
    
    int bid = id;
	//if(!bMonsterTimer) return;
	
	printf("monster off - %i\n", bid);
	for(int i=monsters.size()-1; i>=0; i--) {
		if(monsters[i].id == bid &&
           monsters[i].packetId == packetId) {
			monsters.erase(monsters.begin() + i);


			// tell daito that the monster is dead
//			ofxOscMessage msg;
//			msg.setAddress("/bang");							//	bang
//			msg.addStringArg("deadMonster");					//	new monster
//			msg.addIntArg(3);									//	SCENE 3
//			msg.addIntArg(monsters[i].monsterMode);				//  what kind of monster are we
//			msg.addIntArg(bid);									//	monster ID
//			msg.addFloatArg((float)x/(float)packet.width);		//  centroid x (normalize)
//			msg.addFloatArg((float)y/(float)packet.height);		//  centroid y (normalize)
//			msg.addFloatArg(0);									//  width (normalize)
//			msg.addFloatArg(0);									//  hieght (normalize)
//
//			ofxDaito::sendCustom(msg);

		}
	}
}

void MonsterScene::drawGui(){
    gui.draw();
}

//-------------------------------------------------------------- debug drawing
void MonsterScene::drawTop() {

	if(!bDebug) return;

//	panel.draw();

	glPushMatrix();
	glTranslatef(0, 100, 0);

	ofSetColor(255, 0, 0);
	string info = "Monsters Rule!\n";
	info += "Num Eyes: "+ofToString((int)parts.eyes.size())+"\n";
	ofDrawBitmapString(info, 20, 20);
	glPopMatrix();
}


//-------------------------------------------------------------- draw
void MonsterScene::draw() {

	ofPushStyle();
	ofEnableAlphaBlending();

	
	//float scalex = (float)RM->getWidth() / (float)cvData[0]->width;
	//float scaley = (float)RM->getHeight() / (float)cvData[0]->height;
	
	if(bDebug) {
	//	ofSetColor(0, 25, 255);
	//	ofFill();
	//	ofRect(-300, -500, 10000, 10000);
	}
	
	
	// --------------------- People
	glPushMatrix();
	glTranslatef(0 , 0, 0);
	//glTranslatef(((RM->getWidth() - W)/2), (RM->getHeight()-H), 0);

	bool bDrawPeople = false;
	if(bDrawPeople) {
        
        for (int packetId = 0; packetId < 2; packetId++){
            for(int i=0; i<cvData[packetId]->blobs.size(); i++) {
                ofSetColor(255, i*20, 255-(i*40), 100);
                ofFill();

                ofBeginShape();
                for (int j = 0; j < cvData[packetId]->blobs[i].blob.size(); j++) {

                    float x = cvData[packetId]->blobs[i].blob[j].x;
                    float y = cvData[packetId]->blobs[i].blob[j].y;

                    ofPoint pt(x,y);
                    cvData[packetId]->remapForScreen(packetId == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
                    ofVertex(pt.x, pt.y);
                }
                ofEndShape(true);
            }
        }
	}



	for(int i=0; i<dust.size(); i++) {
		dust[i].draw();
	}

	for(int i=0; i<balls.size(); i++) {
		balls[i]->draw();
	}


	// --------------------- particles
	for(int i=0; i<monsterParticles.size(); i++) {
		monsterParticles[i]->draw();
	}


	// --------------------- Monsters
	for(int i = 0; i < monsters.size(); i++) {
		monsters[i].draw();
	}


	// --------------------- building shape
	if(bDebug) {
//		for(int i=0; i<box2dBuilding.size(); i++) {
//			//box2dBuilding[i].draw();
//		}
	}


	// --------------------- building shape
	if(bDebug) {
		for(int i=0; i<windowPnts.size(); i++) {
			windowPnts[i].draw();
		}
	}
	glPopMatrix();



	// ferry building only for setup (hide when live)
//	if(bDebug) {
//		ferryBuilding.drawContour();
//		ferryBuilding.drawInfo();
//	}
	ofDisableAlphaBlending();
	ofPopStyle();
    
    
    for (int i=0; i<edges.size(); i++) {
        //edges[i].get()->draw();
    }
}


//--------------------------------------------------------------
void MonsterScene::createBuildingContour() {

    float scale = RM->getWidth() / 2100.0; //(float)RM->windows.getWidth();
    
     for (int j=0; j< RM->innerWindows.size(); j++) {
         shared_ptr <ofxBox2dEdge> edge = shared_ptr<ofxBox2dEdge>(new ofxBox2dEdge);
         
        ofPolyline line = RM->innerWindows[j];
        for (int k = 0; k < 2; k++){
            edge.get()->addVertex(line[k] * scale);
        }
        edge.get()->setClosed(true);
        edge.get()->create(box2d.getWorld());
        edges.push_back(edge);
    }
   
    
    shared_ptr <ofxBox2dEdge> edge = shared_ptr<ofxBox2dEdge>(new ofxBox2dEdge);
    edge.get()->addVertex(ofPoint(0, RM->getHeight()));
    edge.get()->addVertex(ofPoint(RM->getWidth(), RM->getWidth()));
    edge.get()->create(box2d.getWorld());
    edges.push_back(edge);
    
//	for(int i=0; i<box2dBuilding.size(); i++) {
//		box2dBuilding[i].destroyShape();
//	}
//	box2dBuilding.clear();
    

    // 2016
//	// build the building for box2d
//	for(int i=0; i<ferryBuilding.shapes.size(); i++) {
//
//		box2dBuilding.push_back(MonsterLine());
//		box2dBuilding.back().setWorld(box2d.getWorld());
//		box2dBuilding.back().clear();
//
//		for(int j=0; j<ferryBuilding.shapes[i].pnts.size(); j++) {
//			float bx = ferryBuilding.shapes[i].pnts[j].x;
//			float by = ferryBuilding.shapes[i].pnts[j].y;
//
//			//bx -= ((RM->getWidth() - W)/2);
//			//by -= (RM->getHeight() - H);
//
//			box2dBuilding.back().addPoint(bx, by);
//		}
//		box2dBuilding.back().createShape();
//
//	}
//
//	printf("-- building shape made --\n");
}


//--------------------------------------------------------------
void MonsterScene::keyPressed(int key) {

	if(bDebug) {
		
		//ferryBuilding.keyPressed(key);

		if(key == ' ') {
		//	createBuildingContour();
		}

		if(key == 'M') {
			saveMonsterSettings();
		}
		
//		if(key == '1') {
//			ferryBuilding.setupBuilding("buildingRefrences/buidlingFiles/BuildingMonsters_0.xml");
//			createBuildingContour();
//		}
//		if(key == '2') {
//			ferryBuilding.setupBuilding("buildingRefrences/buidlingFiles/BuildingMonsters_1.xml");
//			createBuildingContour();
//		}
//		if(key == '3') {
//			ferryBuilding.setupBuilding("buildingRefrences/buidlingFiles/BuildingMonsters_2.xml");
//			createBuildingContour();
//		}
		
	}

	if(key == 'd') {
		bDebug = !bDebug;
		//panel.setValueB("DEBUG", bDebug);
	}

	// add some
	if(key == 't') {
		float bx = ofGetMouseX();
		float by = ofGetMouseY();

		//bx -= ((RM->getWidth() - W)/2);
		//by -= (RM->getHeight() - H);


        //shared_ptr<ofxBox2dRect>(new ofxBox2dRect)
        
        shared_ptr<MonsterBall> bub =  shared_ptr<MonsterBall> (new MonsterBall());
		//MonsterBall bub;
		bub->initTime = ofGetElapsedTimef();
		bub->setPhysics(30.0, 0.93, 0.1); // mass - bounce - friction
		bub->setup(box2d.getWorld(), bx, by, ofRandom(10, 20));
		bub->img = &dotImage;
		balls.push_back(bub);

	}

//	if(key == 'b') {
//		for(int i=0; i<box2dBuilding.size(); i++) {
//			box2dBuilding[i].destroyShape();
//		}
//		box2dBuilding.clear();
//	}

//	if(key == 'v'){
//		createBuildingContour();
//	}
	
	//if(key == 'p') bMonsterTimer = !bMonsterTimer;
}

//--------------------------------------------------------------
void MonsterScene::mousePressed(int wx, int wy, int x, int y, int button) {

	//panel.mousePressed(wx, wy, button);

	//float bx = mouseX;
	//float by = mouseY;

	if(bDebug) {
		//ferryBuilding.mousePressed(x, y, button);


		//bx -= ((RM->getWidth() - W)/2);
	//	by -= (RM->getHeight() - H);

		//printf("windddddddddd = %i, %i", x, y);
		//windowPnts.push_back(MonsterWindow());
		//windowPnts.back().pos.set(x, y);
		//windowPnts.back().img = &dotImage;


	}

	//printf("--------------  %f    %f", bx, by);

}

//--------------------------------------------------------------
void MonsterScene::mouseDragged(int wx, int wy, int x, int y, int button){
//	panel.mouseDragged(wx, wy, button);
}

//--------------------------------------------------------------
void MonsterScene::mouseReleased(int wx, int wy, int x, int y, int button){
//	panel.mouseReleased();
}




//--------------------------------------------------------------
void MonsterScene::loadMonsterSettings() {

	string theFile = "settings/monsterSettings.xml";


	printf("--- loading: %s ---\n", theFile.c_str());

	xmlSaver.clear();

	if(xmlSaver.loadFile(theFile)) {

		int numTags = xmlSaver.getNumTags("windowPnts:wnd");
		if(numTags > 0) {

			xmlSaver.pushTag("windowPnts");

			int numShapes = xmlSaver.getNumTags("wnd:pnt");
			for(int i=0; i<numShapes; i++) {

				xmlSaver.pushTag("wnd", i);

				float x = xmlSaver.getValue("pnt:x", 0.0, 0);
				float y = xmlSaver.getValue("pnt:y", 0.0, 1);
			//	windowPnts.push_back(MonsterWindow());
			//	windowPnts.back().pos.set(x, y);
			//	windowPnts.back().img = &dotImage;
				xmlSaver.popTag();

			}
			xmlSaver.popTag();
		}

	}

}

//--------------------------------------------------------------

void MonsterScene::saveMonsterSettings() {

	string fileToSave = "settings/monsterSettings.xml";

	xmlSaver.clear();

	xmlSaver.addTag("windowPnts");
	xmlSaver.pushTag("windowPnts");
	for(int i=0; i<windowPnts.size(); i++) {
		xmlSaver.addTag("wnd");
		xmlSaver.pushTag("wnd", i);

		xmlSaver.setValue("pnt:x", windowPnts[i].pos.x, 0);
		xmlSaver.setValue("pnt:y", windowPnts[i].pos.y, 1);

		xmlSaver.popTag();
	}

	xmlSaver.popTag();
	xmlSaver.saveFile(fileToSave);

	printf("--- monster settings saved [%s]---\n", fileToSave.c_str());
}







////--------------------------------------------------------------
//void MonsterScene::Add(const b2ContactPoint* point){
//
//	b2Vec2 p = point->position;
//	p *= OFX_BOX2D_SCALE;
//
//
//	b2Body * body_1 = point->shape1->GetBody();
//	MonsterData * theData = (MonsterData*)body_1->GetUserData();
//	if(theData) {
//		//printf("-- this is a window %i\n", theData->bIsWindow);
//
//		if(dust.size() < MAX_MONSTER_DUST) {
//			//dust.push_back(MonsterDust(p.x, p.y));
//		//	dust.back().img = &dotImage;
//
//			/*
//			 // particle dust hit
//			 ofxOscMessage msg;
//			 msg.setAddress("/bang");							    //	bang
//			 msg.addStringArg("particleHit");					    //	hit
//			 msg.addIntArg(3);									    //	SCENE 3
//			 msg.addFloatArg((float)p.x/(float)RM->getWidth());		//  x (normalize)
//			 msg.addFloatArg((float)p.y/(float)RM->getHeight());	// centroid y (normalize)
//
//			 ofxDaito::sendCustom(msg);
//			 */
//		}
//
//	}
//}
//
//void MonsterScene::Remove(const b2ContactPoint* point){
//}

void MonsterScene::cleanUpScene() {


	for(int i=monsters.size()-1; i>=0; i--) {
		monsters.erase(monsters.begin() + i);
	}
	monsters.clear();


	for(int i=monsterParticles.size()-1; i>=0; i--) {
		monsterParticles[i]->destroy();
		monsterParticles.erase(monsterParticles.begin() + i);
	}
	monsterParticles.clear();


	for(int i=balls.size()-1; i>=0; i--) {
		balls[i]->destroy();
		balls.erase(balls.begin() + i);
	}
	balls.clear();

}
















