#include "TreeScene.h"
#include "appSettings.h"


// ------------------------------------------
void TreeScene::setup() {
	
    
    sceneName = "treeScene";
    
	bDebug = false;
	butterFlyColor.push_back(0xd1007e);
	butterFlyColor.push_back(0x00a3c4);
	butterFlyColor.push_back(0x6ac539);
	butterFlyColor.push_back(0xff5500);
	butterFlyColor.push_back(0xff0009);
	
	theDot.loadImage("sceneAssets/monsters/dot.png");
	theDotS.loadImage("sceneAssets/trees/littleDot.png");
	
	

    gui.setup("settings_treeScene", "settings_treeScene.xml");
    
    
    
    
    
    
    
    
    group.add(treeDelay.set("treeDelay", 1.3, 0.0, 10.0 ));
    group.add(peopleGlow.set("peopleGlow", 20.4, 0.0, 255.0 ));
    group.add(treeBottomOffset.set("treeBottomOffset", 20.4, -800, 800.0 ));
    //	
    group.add(treeGrowW.set("treeGrowW", 100.0, 0.0, 1000.0 ));
    group.add(treeGrowH.set("treeGrowH", 100.0, 0.0, 1000.0 ));
    group.add(treeMin.set("treeMin", 10.0, 0.0, 20.0 ));
    group.add(treeMax.set("treeMax", 20.0, 20.0, 100.0 ));
    group.add(growRate.set("growRate", 0.98, 0.0, 2.0 ));
    //	
    group.add(curveX.set("curveX", 10.98, 0.0, 30.0 ));
    group.add(curveY.set("curveY", 10.98, 0.0, 30.0 ));
    group.add(thetaG.set("thetaG", 0.08, 0.0, 2.0 ));
    group.add(fadeRate.set("fadeRate", 6.0, 1.0, 40.0 ));
    group.add(butterFlyScale.set("butterFlyScale", 0.09, 0.0, 2.0 ));
    group.add(butterFlySpeed.set("butterFlySpeed", 0.09, 0.0, 2.0 ));
    group.add(peopleColor.set("peopleColor", 0.0, 0.0, 255.0 ));
    group.add(treeAddingTime.set("treeAddingTime", 1.0, 0.0, 2.0 ));
    group.add(bDoPeopleGlow.set("bDoPeopleGlow", true));
    
    gui.add(group);
    gui.loadFromFile("settings_treeScene.xml");
    
//	
//	
//	panel.addToggle("do people glow", "BPEOPLE_GLOW", 1);
//	
//	
//	panel.loadSettings("settings/panels_xml/treeScenePanel.xml");
//	
	
	// ------------ The Ferr Contour
	//building.setupBuilding("buildingRefrences/buidlingFiles/treeFerryContour.xml");
	
	
	
	// ------------ Load some SVG Files for the Ferns 
	RandomFern tempFern;
	tempFern.addLeaf("sceneAssets/trees/Fern_Leaf_001.svg");
	tempFern.addLeaf("sceneAssets/trees/Fern_Leaf_002.svg");
	tempFern.addLeaf("sceneAssets/trees/Fern_Leaf_003.svg");
	
	
	
	// ------------ Settins 
	bGotMyFirstPacket	= false;
	
	// ------------ Get some Flocling butterflys in
	ButterflyAnimation tempButterFly;
	tempButterFly.addFile("sceneAssets/trees/Butterfly_001.svg");
	tempButterFly.addFile("sceneAssets/trees/Butterfly_002.svg");
	tempButterFly.addFile("sceneAssets/trees/Butterfly_003.svg");
	tempButterFly.addFile("sceneAssets/trees/Butterfly_004.svg");
	
	// make the butterflys
	if(butterflys.size() < MAX_BUTTERFLYS) {
		for (int i = 0; i < MAX_BUTTERFLYS; i++){
			ButterFlyParticle bf;
			bf.setInitialCondition(ofRandom(200, RM->getWidth()), ofRandom(0, RM->getHeight()), 0,0);
			bf.setupButterfly();
            bf.scale = butterFlyScale; //panel.getValueF("BUTTERFLY_SCALE");
			butterflys.push_back(bf);
			butterflys.back().img = &theDot;
			butterflys.back().color = butterFlyColor[(int)ofRandom(0, butterFlyColor.size()-1)];
		}
	}
	
	
}


//--------------------------------------------------------------
void TreeScene::cleanUpScene() {
	
	
	for(int i=treeBlobs.size()-1; i>=0; i--) {
		treeBlobs.erase(treeBlobs.begin() + i);
	}
	treeBlobs.clear();
	
	
	for(int i=trees.size()-1; i>=0; i--) {
		trees.erase(trees.begin() + i);
	}
	trees.clear();
	
	
}


//--------------------------------------------------------------
void TreeScene::keyPressed(int key) {
	// keys for the ferry
	//building.keyPressed(key);
	
	if(key == 'd') bDebug = !bDebug;
}

//--------------------------------------------------------------
void TreeScene::mouseDragged(int wx, int wy, int x, int y, int button){
	//panel.mouseDragged(wx, wy, button);
}

//--------------------------------------------------------------
void TreeScene::mousePressed(int wx, int wy, int x, int y, int button){
	//panel.mousePressed(wx, wy, button);
	
	// events for the ferry building
	//building.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void TreeScene::mouseReleased(int wx, int wy, int x, int y, int button){
	//panel.mouseReleased();
}




//--------------------------------------------------------------
void TreeScene::updateFlocking() {
//	
//    float scalex =  1; //(float)RM->getWidth() / (float)packet.width;
//    float scaley = 1; //(float)RM->getHeight() / (float)packet.height;
//	
    ofRectangle src(0,0,cvData->width, cvData->height);
    ofRectangle target = RM->getRectForScreen(SCREEN_LEFT);
    ofRectangle dst = src;    dst.scaleTo(target);
    float scaleCoordinates = dst.getWidth() / src.getWidth();
    
	for (int i = 0; i < butterflys.size(); i++){
		
        butterflys[i].scale = butterFlySpeed; //panel.getValueF("BUTTERFLY_SCALE");
        butterflys[i].damping = butterFlySpeed; //panel.getValueF("BUTTERFLY_SPEED");
		butterflys[i].resetForce();
	}
	
	for (int i = 0; i < butterflys.size(); i++){
		for (int j = 0; j < butterflys.size(); j++){
			if (i != j){
				butterflys[i].addForFlocking(butterflys[j]);	
			}
		}
		
		
		for(int q=0; q<cvData->blobs.size(); q++) {
			
			ofRectangle newRec = cvData->blobs[q].blob.getBoundingBox();
			
            ofPoint a = newRec.getTopLeft();
            ofPoint b = newRec.getBottomRight();
            
            a =cvData->remapForScreen(SCREEN_LEFT, a);
            b =cvData->remapForScreen(SCREEN_LEFT, b);
//
            ofRectangle newRecScaled;
            newRecScaled.set(a.x, a.y, b.x-a.x, b.y-a.y);
            
#pragma mark tofix
            float forceFactor = 1.0; // (newRec.width * newRec.height) / ((cvPacket->width)*(cvPacket->height));
			
//			newRec.x		*= scalex;
//			newRec.y		*= scaley;
//			newRec.width	*= scalex;
//			newRec.height	*= scaley;
			ofPoint center;
			center.x =cvData->remapForScreen(SCREEN_LEFT, cvData->blobs[q].blob.getCentroid2D()).x;
			center.y =cvData->remapForScreen(SCREEN_LEFT, cvData->blobs[q].blob.getCentroid2D()).y;
			
			butterflys[i].addAttractionForce(center.x, center.y - 20, 300, 1.5);
			
			
		}
	}
	
	for (int i = 0; i < butterflys.size(); i++){
		butterflys[i].addFlockingForce();
		butterflys[i].addDampingForce();
		butterflys[i].update();
	}
	
	// wrap torroidally.
	for (int i = 0; i < butterflys.size(); i++){
		ofVec2f pos = butterflys[i].pos;
		
		float screenW = 0;
		float screenH = 0;
		
		float offx = 0;//((RM->getWidth() - screenW)/2);
		float offy = 0;//(RM->getHeight() - screenH);
		float gap  = 20;
		if (pos.x < 0)							pos.x = RM->getWidth();
		if (pos.x > RM->getWidth())			pos.x = 0;
		if (pos.y < 0)							pos.y = RM->getHeight()*3;
		if (pos.y > RM->getHeight()*3)			pos.y = 0;
		
		butterflys[i].pos = pos;
	}
	
	
	
}

// ------------------------------------------
void TreeScene::update() {
	
	//panel.update();
	
    //float scalex = 1; //(float)RM->getWidth() / (float)packet.width;
    //float scaley = 1; //(float)RM->getHeight() / (float)packet.height;
	
    ofRectangle src(0,0,cvData->width, cvData->height);
    ofRectangle target = RM->getRectForScreen(SCREEN_LEFT);
    ofRectangle dst = src;    dst.scaleTo(target);
    float scaleCoordinates = dst.getWidth() / src.getWidth();
    
	
	// --------------------- Tree Blobs
	for(int i=0; i<cvData->blobs.size(); i++) {
		
		int lookID = cvData->blobs[i].id;
		
		ofRectangle newRec = cvData->blobs[i].blob.getBoundingBox();
        
        ofPoint a = newRec.getTopLeft();
        ofPoint b = newRec.getBottomRight();
    
        a =cvData->remapForScreen(SCREEN_LEFT, a);
        b =cvData->remapForScreen(SCREEN_LEFT, b);
        ofRectangle newRecScaled;
        newRec.set(a.x, a.y, b.x-a.x, b.y-a.y);
        
//		newRec.x		*= scalex;
//		newRec.y		*= scaley;
//		newRec.width	*= scalex;
//		newRec.height	*= scaley;
		
		ofPoint center = cvData->remapForScreen(SCREEN_LEFT, cvData->blobs[i].blob.getCentroid2D());
//		center.x		= center.x * scalex;
//		center.y		= center.y * scaley;
		
		
		for(int j=0; j<treeBlobs.size(); j++) {
			
			// found you :)
			if(lookID == treeBlobs[j].id) {
				
				treeBlobs[j].age		= ofGetElapsedTimef() - treeBlobs[j].initTime; // getting older
				treeBlobs[j].rect	    = newRec;
				treeBlobs[j].center     = center;
				
				// ok we are old enough lets make a blob
                if(treeBlobs[j].age >= treeDelay){ //panel.getValueF("TREE_DELAY")) {
					
					treeBlobs[j].initTime = ofGetElapsedTimef();
					treeBlobs[j].numTreesMade ++;
					treeBlobs[j].bAlive = true;
					
					// time to grow a tree
					printf("--- time to grow a tree:%i---\n", treeBlobs[j].id);
					trees.push_back(MagicTree());
					
                    trees.back().initTree(0, 0, ofRandom( treeMin,treeMax)); // /*(int)ofRandom(panel.getValueF("TREE_MIN")*/ /* panel.getValueF("TREE_MAX")*/));	// <--- i need a init pos
					trees.back().img	= &theDot;
					trees.back().id		= treeBlobs[j].id; 
					trees.back().rect	= treeBlobs[j].rect;
					trees.back().center = treeBlobs[j].center;
					
					// init the tree pos
					trees.back().treeBaseD   = trees.back().center;
					trees.back().treeBaseD.y = (newRec.y + newRec.height);
					trees.back().treeBase	 = trees.back().treeBaseD;
					
//					// new tree hit
//					ofxOscMessage msg;
//					msg.setAddress("/bang");							    //	bang
//					msg.addStringArg("newTree");					    //	hit
//					msg.addIntArg(2);									    //	SCENE 3
//					msg.addIntArg(trees.back().id);									    //	SCENE 3
//					
//					msg.addFloatArg((float)center.x/(float)RM->getWidth());		//  x (normalize)
//					msg.addFloatArg((float)center.y/(float)RM->getHeight());	// centroid y (normalize)
//					
//					ofxDaito::sendCustom(msg);
					
				}
				
			}
		}
		
	}
	
	
	// --------------------- Tree People
	for(int i=0; i<trees.size(); i++) {
		
        trees[i].curveRateX = curveX; //panel.getValueF("GROW_C_X");
        trees[i].curveRateY = curveY; //panel.getValueF("GROW_C_Y");
        trees[i].thetaRate = thetaG; //panel.getValueF("GROW_T");
        trees[i].fadeRate = fadeRate; //panel.getValueF("FADE_RATE");
        trees[i].addTime = treeAddingTime; //panel.getValueF("TREE_ADD_TIME");
        trees[i].growRate = growRate; //panel.getValueF("GROW_RATE");
		trees[i].update();	
	}
	// clean up the trees
	for(int i=trees.size()-1; i>=0; i--) {
		
		if(trees[i].bDead) {
			trees[i].cleanUp();
			trees.erase(trees.begin() + i);
			printf("tree deleted \n");
		}
	}
	
	
	
	
	
	// --------------------- the butterfly flocking 
	updateFlocking();
	
	
	// --------------------- packet info
//	if(packet.frameNumber >= 0 && !bGotMyFirstPacket) {
//		printf("got my first packet - %i\n", packet.frameNumber);
//		bGotMyFirstPacket = true;
//		
//	}
	
}


void TreeScene::drawGui(){
    gui.draw();
}
// ---------------------------------------------------------
void TreeScene::drawTop() {
	//if(bDebug) panel.draw();
}

// ---------------------------------------------------------
void TreeScene::draw() {
    
    
    ofRectangle src(0,0,cvData->width, cvData->height);
    ofRectangle target = RM->getRectForScreen(SCREEN_LEFT);
    ofRectangle dst = src;    dst.scaleTo(target);
    float scaleCoordinates = dst.getWidth() / src.getWidth();
    
	
//    float scalex = 1;// (float)RM->getWidth() / (float)packet.width;
//    float scaley = 1; //(float)RM->getHeight() / (float)packet.height;
	
	if(bDebug) {
		ofSetColor(0, 25, 255);
		ofFill();
		ofRect(-300, -500, 10000, 10000);
	}
	
	ofEnableAlphaBlending();
	glPushMatrix();
	glTranslatef(0, 0, 0);
	
	// the big trees - funky style
	glPushMatrix();
	glTranslatef(0, treeBottomOffset /*panel.getValueF("TREE_OFF")*/, 0);
	for (int i = 0; i < trees.size(); i++){
		trees[i].draw();
	}
	glPopMatrix();
	
	// draw the people
	for(int i=0; i< cvData->blobs.size(); i++) {
		
		
        if(true){ //panel.getValueB("BPEOPLE_GLOW")) {
			// drop shadow
			ofEnableAlphaBlending();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			for (int j = 0; j < cvData->blobs[i].blob.size(); j+=2) {
				float x =  cvData->remapForScreen(SCREEN_LEFT, cvData->blobs[i].blob[j]).x;
                float y =  cvData->remapForScreen(SCREEN_LEFT, cvData->blobs[i].blob[j]).y;  //cvData->blobs[i].blob[j].y * scaley;
				
				ofSetRectMode(OF_RECTMODE_CENTER);
                ofSetColor(255, 255, 255, peopleGlow); //panel.getValueF("PEOPLE_GLOW"));
				theDotS.draw(x, y, 55, 55);
				ofSetRectMode(OF_RECTMODE_CORNER);
			}
			glDisable(GL_BLEND);
			ofDisableAlphaBlending();
		}
		
		// people
        float bc = peopleColor; //panel.getValueF("PEOPLE_COLOR");
		ofSetColor(bc, bc, bc);
		ofFill();
		ofBeginShape();
		for (int j = 0; j < cvData->blobs[i].blob.size(); j++) {
			
            float x =cvData->remapForScreen(SCREEN_LEFT, cvData->blobs[i].blob[j]).x; //cvData->blobs[i].blob[j].x * scalex;
            float y =cvData->remapForScreen(SCREEN_LEFT, cvData->blobs[i].blob[j]).y; //cvData->blobs[i].blob[j].y * scaley;
			
			ofVertex(x, y);
		}
		ofEndShape(true);
//		
//		if(bDebug) {
//			ofNoFill();
//			ofSetColor(255, 35, 0);
//			ofRect(packet.rect[i].x * scalex, 
//				   packet.rect[i].y * scaley, 
//				   packet.rect[i].width * scalex, 
//				   packet.rect[i].height * scaley);
//			
//			
//			ofDrawBitmapString("w:"+ofToString(packet.rect[i].width)+"\n"+
//							   "h:"+ofToString(packet.rect[i].height)+"\n", 
//							   20+packet.rect[i].x * scalex, 
//							   20+packet.rect[i].y * scaley);
//		}
//		
	}
	
	
	// draw the butter flys
	
	for(int i = 0; i < butterflys.size(); i++){
		butterflys[i].draw();
	}
	
	
	if(bDebug) {	
		// The Tree Blobs
		for(int i=0; i<treeBlobs.size(); i++) {
			glPushMatrix();
			glTranslatef(treeBlobs[i].center.x, treeBlobs[i].center.y, 0);
			ofFill();
			ofSetColor(200, 40, 255);
			ofCircle(0, 0, 40);
			ofSetColor(255, 255, 255);
			ofDrawBitmapString("id: "+ofToString(treeBlobs[i].id) +"\n"+
							   ofToString(treeBlobs[i].age), 0, 0);
			glPopMatrix();
		}
	}
	

	
	glPopMatrix();
	
	if(bDebug) {
		float screenW = 0;
		float screenH = 0;
		ofNoFill();
		ofSetColor(245, 2, 2);
		ofRect(((RM->getWidth() - screenW)/2), (RM->getHeight()-screenH), screenW, screenH);
	}
}







// --------------------------------------------------------- blob events
void TreeScene::blobOn( int x, int y, int bid, int order ) {
	
    
    
    ofPolyline line = cvData->blobs[ cvData->idToBlobPos[bid] ].blob;//&tracker->getById(bid);
	
    for (auto & pt: line){
        pt = cvData->remapForScreen(SCREEN_LEFT, pt);
    }
    
	// if i am hole make a shape instead
    if(true){
		
		if(line.getBoundingBox().width >= 100 /*panel.getValueI("TREE_GROW_W")*/ ||
		   line.getBoundingBox().height >= 100 /* panel.getValueI("TREE_GROW_H")*/ ) {
			
			treeBlobs.push_back(TreeBlob());
			treeBlobs.back().id = bid;
			treeBlobs.back().age = 0;
			treeBlobs.back().bAlive = false;
			
			treeBlobs.back().initTime = ofGetElapsedTimef();
			
			printf("new tree blob  - %i\n", treeBlobs.back().id);
		}
	}
}

// ---------------------------------------------------------
void TreeScene::blobMoved( int x, int y, int bid, int order ) {
	
}

// ---------------------------------------------------------
void TreeScene::blobOff( int x, int y, int bid, int order ) {	
	
	for(int i=trees.size()-1; i>=0; i--) {
		if(trees[i].id == bid) {
			
			trees[i].id = -1;
			trees[i].bNoBlobAnymore = true;
			printf("tree off - %i\n", bid);
			
		}
	}
	
	// clean up the tree blobs
	for(int i=treeBlobs.size()-1; i>=0; i--) {
		if(treeBlobs[i].id == bid) {
			
			treeBlobs.erase(treeBlobs.begin() + i);
			printf("--- tree blob removed [%i] -- \n", bid);
		}
	}
}
















