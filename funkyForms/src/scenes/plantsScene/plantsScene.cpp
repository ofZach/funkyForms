//
//  PlantManager.cpp
//  PlantSpring
//
//  Created by Zerc on 8/5/16.
//
//

#include "plantsScene.hpp"
// --------------- setup
void plantsScene::setup(){
    setupGui();
    setupBackground();
    for (int i = 0; i < 4; i++) {
        addBgPlantRandom();
    }
    for (int i = 0; i < 40; i++) {
        randSwatchIndex.push_back((int)ofRandom(4));
    }
    glow.load("assets/glow.png");
}
void plantsScene::setupBackground(){
    skyImage.load("sceneAssets/plants/sky.png");
    hillsImage.load("sceneAssets/plants/hills.png");
    // set center
    float x = RM->getWholeRectangle().getCenter().x;
    float y = RM->getWholeRectangle().getBottom();
    bgCenterPos.set(x, y);
}
void plantsScene::addBgPlantRandom(){
    ofRectangle r = RM->getWholeRectangle();
    float x = ofRandom(r.getX(), r.getRight());
    float y = RM->getRectForScreen(SCREEN_LEFT).getBottom();
    addBgPlant(ofVec2f(x,y));
}
void plantsScene::addBgPlant(ofVec2f _pos){
    Plant plant;
    bgPlants.push_back(plant);
    int i = bgPlants.size()-1;
    
    bgPlants[i].rig.cbCount = ofRandom(bgChildBranchCountMin, bgChildBranchCountMax) ;
    bgPlants[i].rig.mbCount = ofRandom(bgMainBranchCountMin, bgMainBranchCountMax) ;
    
    bgPlants[i].rig.dir = ofVec2f(0, -1);
    bgPlants[i].rig.mbWidth = bgmainBranchWidth ;
    bgPlants[i].rig.mbHeight = bgmainBranchHeight ;
    bgPlants[i].rig.cbHeight = bgchildBranchHeight ;
    bgPlants[i].rig.cbWidth = bgchildBranchWidth ;
    bgPlants[i].rig.lengthVariation = branchLengthVariation;
    
    bgPlants[i].rig.timeSpeed = 0.01;
    
    bgPlants[i].mbWidth = bgmainBranchStrokeWidth;
    bgPlants[i].cbWidth = bgchildBranchStrokeWidth;
    bgPlants[i].rig.pos = _pos;
    
    ofFloatColor col = swatch[(int)ofRandom(4)];
    col.setBrightness(col.getBrightness()/2);
    bgPlants[i].color = col;
    
    bgPlants[i].setup();
    bgPlants[i].ageMax = ofRandom(600, 1000);
    bgPlants[i].fadeIn();
}



void plantsScene::addPlant(ofVec2f _pos, int id, bool bLeftSide){
    
    ofRectangle src(0,0,cvData->width, cvData->height);
    ofRectangle dst = src;
    ofRectangle target = RM->getRectForScreen(SCREEN_LEFT);
    dst.scaleTo(target);
    
    
    Plant plant;
    plants.push_back(plant );
    int i = plants.size()-1;
    
    plants[i].id = id;
    plants[i].pointLinkId = ofRandom(pointLinkCount);
    
    // calc direction
    ofPolyline line = (*(cvData->trackedContours))[id].data.resampleSmoothed;
    for (auto & pt : line){
        pt =cvData->remapForScreen(SCREEN_LEFT, pt);
    }
    
    ofVec2f *point = new ofVec2f[pointLinkCount];
    int step = line.size()/pointLinkCount;
    int k = 0;
    ofVec2f a(0, 0);
    for (int j = 0; j < line.size(); j += step ) {
        point[k] = line.getVertices()[j];
        a += point[k];
        k++;
    }
    ofVec2f centroid = a/pointLinkCount;
    // find centroid
    
    ofVec2f &p1 = point[plants[i].pointLinkId];
    ofVec2f delta = p1 - centroid;
    float x = delta.x;
    float y = delta.y;
    
    ofVec2f dir;
    if (abs(y) > abs(x)) {
        dir.set(0, -1); // up or down
    } else {
        if (!bLeftSide){ // right
            dir.set(1, 0);
        } else{ // left
            dir.set(-1, 0);
        }
    }
    
    plants[i].rig.dir = dir;
    
    plants[i].rig.cbCount = ofRandom(childBranchCountMin, childBranchCountMax);
    plants[i].rig.mbCount = ofRandom(mainBranchCountMin, mainBranchCountMax) ;
    
    plants[i].rig.mbWidth = mainBranchWidth ;
    plants[i].rig.mbHeight = mainBranchHeight ;
    plants[i].rig.cbWidth = childBranchWidth ;
    plants[i].rig.cbHeight = childBranchHeight ;
    plants[i].rig.lengthVariation = branchLengthVariation ;
    
    plants[i].mbWidth = mainBranchStrokeWidth;
    plants[i].cbWidth = childBranchStrokeWidth;
    plants[i].rig.pos = _pos;
    
    plants[i].color = swatch[(int)ofRandom(4)];

    plants[i].setup();
    //plants[i].fadeIn();
    plants[i].bLeftSide = bLeftSide;
    
}
void plantsScene::setupGui(){
    parameters.setName("plantsSceneParameters");
    // plant
    parameters.add(plantScale.set("plantScale", 1.0, 0.1, 2));
    
    parameters.add(mainBranchCountMin.set("mainBranchCountMin", 5, 1, 20));
    parameters.add(mainBranchCountMax.set("mainBranchCountMax", 5, 1, 20));
    
    parameters.add(childBranchCountMin.set("childBranchCountMin", 5, 1, 20));
    parameters.add(childBranchCountMax.set("childBranchCountMax", 5, 1, 20));

    parameters.add(bgMainBranchCountMin.set("bgMainBranchCountMin", 5, 1, 20));
    parameters.add(bgMainBranchCountMax.set("bgMainBranchCountMax", 5, 1, 20));
    
    parameters.add(bgChildBranchCountMin.set("bgChildBranchCountMin", 5, 1, 20));
    parameters.add(bgChildBranchCountMax.set("bgChildBranchCountMax", 5, 1, 20));
    
    parameters.add(branchLengthVariation.set("branchLengthVariation", 5, 1, 200));
    parameters.add(mainBranchStrokeWidth.set("mainBranchStrokeWidth", 5, 1, 50));
    parameters.add(childBranchStrokeWidth.set("childBranchStrokeWidth", 5, 1, 50));
    parameters.add(mainBranchHeight.set("mainBranchHeight", 5, 1, 200));
    parameters.add(mainBranchWidth.set("mainBranchWidth", 5, 1, 200));
    parameters.add(childBranchWidth.set("childBranchWidth", 5, 1, 200));
    parameters.add(childBranchHeight.set("childBranchHeight", 5, 1, 200));
    // bgPlant
    parameters.add(bgchildBranchStrokeWidth.set("bgchildBranchStrokeWidth", 5, 1, 50));
    parameters.add(bgmainBranchStrokeWidth.set("bgmainBranchStrokeWidth", 5, 1, 50));
    parameters.add(bgmainBranchHeight.set("bgmainBranchHeight", 5, 1, 200));
    parameters.add(bgmainBranchWidth.set("bgmainBranchWidth", 5, 1, 200));
    parameters.add(bgchildBranchWidth.set("bgchildBranchWidth", 5, 1, 200));
    parameters.add(bgchildBranchHeight.set("bgchildBranchHeight", 5, 1, 200));
    parameters.add(createBgPlant.set("createBgPlant", false));
    // people glow
    parameters.add(glowRadius.set("glowRadius", 10, 1, 50));
    parameters.add(glowOpacity.set("glowOpacity", 100, 0, 255));
    // shadow
    parameters.add(shadowRadius.set("shadowRadius", 5, 1, 300));
    parameters.add(shadowOpacity.set("shadowOpacity", 100, 0, 255));
    // background
    bgParameters.setName("bgParameters");
    bgParameters.add(bgChangeSpeed.set("bgChangeSpeed", 0.5, 0.1, 1.0));

    createBgPlant.addListener(this, &plantsScene::triggerBgPlant);
    
    gui.setup("settings_plantsScene", "settings_plantsScene.xml");
    gui.add(parameters);
    gui.add(bgParameters);
    gui.loadFromFile("settings_plantsScene.xml");

}
void plantsScene::remove(int id){
    for(auto &p : plants){
        if(p.id == id){
            p.fadeOut();
            p.setPos(getClosestPoint(p.getPos(), peoplePoints), 0.5);
        }
    }
}
void plantsScene::reset(){
    bgPlants.clear();
    plants.clear();
    for (int i = 0; i < 4; i++) {
        addBgPlantRandom();
    }
}
void plantsScene::triggerBgPlant(bool &b){
    if(plants.size()>0){
        addBgPlantRandom();
        bgPlants.erase(bgPlants.begin());
    }
}
ofVec2f plantsScene::getClosestPoint(ofVec2f target, vector<ofVec2f> &points){
    float mindist = 2000;
    int index = 0;
    for(int i = 0; i < points.size(); i++){
        float dist = target.distance(points[i]);
        if(dist < mindist){
            mindist = dist;
            index = i;
        }
    }
    return points[index];
}
// --------------- update
void plantsScene::update(){
    updatePlantsParameters();
    updateBgPlants();
    updateBgPlantsRemoval();
    updatePlants();
    updatePlantRemoval();
    
    
    // are there any people without plants???
    
    for (int i = 0; i < cvData->blobs.size(); i++){
        int id = cvData->blobs[i].id;
       
        bool bAny = false;
        for (auto & plant : plants){
            if (plant.id == id){
                bAny = true;
            }
        }
        if (!bAny){
            ofPoint centroid = cvData->blobs[i].blob.getCentroid2D();
            centroid = cvData->remapForScreen(SCREEN_LEFT, centroid);
            addPlant(centroid, id, true);
            addPlant(centroid, id, false);
            
        }
    }
}
void plantsScene::updatePlants(){
    
    ofRectangle src(0,0,cvData->width, cvData->height);
    ofRectangle dst = src;
    ofRectangle target = RM->getRectForScreen(SCREEN_LEFT);
    dst.scaleTo(target);
    
    
    peoplePoints.clear();
    for(auto &id: cvData->idsThisFrame){
        ofPolyline line = (*(cvData->trackedContours))[id].data.resampleSmoothed;
        if(line.size() > 0){
            for (auto & pt : line){
                pt =cvData->remapForScreen(SCREEN_LEFT, pt);
            }
            for (int j = 0; j < line.size(); j += line.size()/10 ) {
                peoplePoints.push_back(line.getVertices()[j]);
            }
        }
    }
    for(auto &p: plants){
        p.update();
        int id = p.id;
        int whichBlob = cvData->idToBlobPos[id];
        ofPolyline line = (*(cvData->trackedContours))[id].data.resampleSmoothed;
        
        bool bUseHighestPt = true;
        
        if(line.size() > 0){
            for (auto & pt : line){
                pt =cvData->remapForScreen(SCREEN_LEFT, pt);
            }
            
            ofPoint highestPt;
            
            if (bUseHighestPt){
                highestPt.x = 0;
                highestPt.y = 10000000;
                
                for (auto pt : line){
                    if (pt.y < highestPt.y){
                        highestPt = pt;
                    }
                }
            }
            
            ofVec2f *point = new ofVec2f[pointLinkCount];
            int step = line.size()/pointLinkCount;
            int k = 0;
            for (int j = 0; j < line.size(); j += step ) {
                point[k] = line.getVertices()[j];
                k++;
            }
            if(!p.isFading){
                
                //p.setPos(highestPt, 0.4);
                //p.setPos(point[p.pointLinkId], 0.5);
            }else{
                
                //p.setPos(getClosestPoint(p.getPos(), peoplePoints), 0.5);
            }
        }
    }
}
void plantsScene::updateBgPlants(){
    for(auto &p: bgPlants){
        p.update();
    }
}
void plantsScene::updateBgPlantsRemoval(){
    for (int i =0; i < bgPlants.size(); i++) {
        if(bgPlants[i].isFadeFinished()){
            // add bg plant behind the person
//            int pId = (int)ofRandom(plants.size());
//            int id = plants[pId].id;
//            float x = plants[pId].getPos().x;
            addBgPlantRandom();
            bgPlants.erase(bgPlants.begin()+i);
        }
    }
}
void plantsScene::updatePlantsParameters(){
    for(auto &p: plants){
        p.scale = plantScale;
        p.shadowRadius = shadowRadius;
        p.shadowOpacity = shadowOpacity;
    }
}
void plantsScene::updatePlantCreation(){

}
void plantsScene::updatePlantRemoval(){
    for (int i =0; i<plants.size(); i++) {
        if(plants[i].isFadeFinished()){
            plants.erase(plants.begin()+i);
        }
    }
}
// --------------- draw
void plantsScene::draw(){
    ofFill();
    drawBackground();
    drawBgPlants();
    drawHills();
    
    ofFill();
    ofSetColor(0,0,0, 230);
    ofRect(0,0,RM->getWidth(), RM->getHeight());
    
    drawPlants();
    drawPeople();
    
}
void plantsScene::drawGui(){
    gui.draw();
}
//void plantsScene::drawParticles(){
//    for (int i = 0; i < particles.size(); i++){
//        particles[i].draw();
//    }
//}
void plantsScene::drawBackground(){
    ofRectangle rect = RM->getWholeRectangle();
    // draw gradient
    ofSetRectMode(OF_RECTMODE_CENTER);
    float skyRadius = rect.getHeight();
    
    ofPushMatrix();
    ofTranslate(rect.getCenter().x, rect.getBottom());
    ofRotateZ(ofGetFrameNum()*bgChangeSpeed);
    
    ofSetColor(ofColor::white);
    skyImage.draw(0, 0, skyRadius*2, skyRadius*2);
    
    ofPopMatrix();
    
    ofSetRectMode(OF_RECTMODE_CORNER);

}
void plantsScene::drawHills(){
    ofRectangle rect = RM->getWholeRectangle();
    
    float k = rect.getWidth() / hillsImage.getWidth();
    float h = k * hillsImage.getHeight();
    
    hillsImage.draw(0, rect.getBottomLeft().y - h, rect.getWidth(), h);
}
void plantsScene::drawShadow(){
    for(auto &p: plants){
        p.drawShadow();
    }
}
void plantsScene::drawPlants(){
    for(auto &p: plants){
        p.draw();
    }
}
void plantsScene::drawBgPlants(){
    for(auto &p: bgPlants){
        p.draw();
    }
}


map < int, ofColor > colorMap;

void plantsScene::drawPeople(){
    // rempap the contour data:
    // baseScene::mapPt takes an input rectangle, an output rectangle
    // and a pt and remaps the pt
    
    
    
    for (int i = 0; i < cvData->blobs.size(); i++){
    
        float age = cvData->blobs[i].age;
        ofPolyline line = cvData->blobs[i].blob;
        for (auto & pt : line.getVertices()){
            pt = cvData->remapForScreen(SCREEN_LEFT, pt);
        }
        
        int id = cvData->blobs[i].id;
        
        auto inThere = colorMap.find(id);
        if (inThere ==colorMap.end()){
            colorMap[id] = ofColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255), 0);
        }
        
        
        ofPoint firstPt;
        ofPoint lastPt;
        
        ofSetColor(255,255,255, 50);
        line.draw();
        
        
        ofRectangle bounds = line.getBoundingBox();
        
        float div = 15; //(float)max(ofGetMouseX(), 3);
        //cout << div << endl;
        int divisions = ceil(bounds.width / div);
        
        vector < ofPoint > pts;
        
        ofPolyline tempLine = line.getResampledBySpacing(1);
        
        float w = div; //bounds.getWidth()/(float)divisions;
        
        
        float startX = bounds.x;
        
        
        vector < ofPoint > circlePositions;
        for (int j = 0; j < divisions; j++){
            
            
            ofRectangle tempRect(startX + j * w, bounds.y, w, bounds.height);
            bool bAny = false;
            float minY = bounds.y + bounds.height;
            for (auto & pt : tempLine){
                if (tempRect.inside(pt)){
                    if (pt.y < minY){
                        minY = pt.y;
                        bAny= true;
                    }
                }
            }
            if (!bAny){
                //minY = bounds.y;
            }
            
            minY -= 10;
            
            ofFill();
            ofRectangle tempRect2(startX + j * w, minY, w, bounds.height - (minY- bounds.y));
            
            //ofCircle(ofPoint(bounds.x + j * w + w/2, minY), w/2);
            //ofRect(tempRect2);
            
            ofPoint circlePos = ofPoint(startX + j * w + w/2, minY);
            
            
            circlePositions.push_back(circlePos);
            
            
            //pts.push_back( ofPoint(bounds.x + j * w + w/2, minY));
        }
        
        
        
        ofPolyline hmm;
        bool bSkip = false;
        
        
        firstPt = circlePositions[0];
        lastPt = circlePositions[circlePositions.size()-1];
        
        for (int j = 0; j < circlePositions.size(); j++){
            
            if (bSkip == true){
                bSkip = false;
                continue;
            }
            ofPoint circlePos = circlePositions[j];
            float angle = PI;
            float angleStep = PI/9.0;
            float width = w/2;
            
            float flipMe = 1;
            
            
            if (j < circlePositions.size()-1){
                if ( fabs(circlePositions[j+1].y - circlePositions[j].y) < 10){
                    bSkip = true;
                    circlePos = (circlePositions[j] + circlePositions[j+1])/2;
                    width = w;
                }
            }
            
            if (j > 0 && j < circlePositions.size()-1 && bSkip != true){
                
                if (circlePositions[j-1].y < circlePositions[j].y &&
                    circlePositions[j+1].y < circlePositions[j].y){
                    flipMe = -1;
                    
                }
            }
            
            for (int k = 0; k < 10; k++){
                ofPoint pt = circlePos + width * ofPoint(cos(angle), sin(angle));
                angle += angleStep * flipMe;
                hmm.addVertex(pt);
            }
        }
        
        
        ofSetColor(255);
        ofPolyline lineTemp(pts);
        
        
        hmm.addVertex( hmm[hmm.size()-1].x, bounds.y + bounds.height);
        hmm.addVertex( hmm[0].x, bounds.y + bounds.height);
        
        
        ofPoint centroid = hmm.getCentroid2D();
        for (auto & pp : hmm){
            pp = (pp - centroid) * ofPoint(1.1, 1.2) + centroid;
        }
        
        line = line.getSmoothed(5);
        
        if (age > 0.8){
            
            colorMap[id].a = 0.9f * colorMap[id].a + 0.1 * 255;
            ofSetColor(colorMap[id]);
            ofBeginShape();
            for (auto & pp : hmm){
                ofVertex(pp);
            }
    //        ofNextContour();
    //        for (auto & pp : line){
    //            ofVertex(pp);
    //        }
            ofEndShape();
            
            ofSetColor(0,0,0);
            ofBeginShape();
            for (auto & pp : line){
                ofVertex(pp);
            }
            ofEndShape();
            
            
            for (int j = 0; j < plants.size(); j++){
                if(plants[j].id == id){
                    if (plants[j].bGrewUp == false){
                        plants[j].fadeIn();
                    }
                }
            }
        }
        
        for (int j = 0; j < plants.size(); j++){
            if(plants[j].id == id){
                if (plants[j].bLeftSide == true){
                    plants[j].setPos(firstPt, 0.5);
                    plants[j].color = colorMap[id];
                } else {
                    plants[j].setPos(lastPt, 0.5);
                    plants[j].color = colorMap[id];
                }
            }
        }
        
        //hmm.draw();
        
        //lineTemp.draw();
        
        
        
    }
    
    
    
//    for (int i = 0; i < cvData->blobs.size(); i++){
//        
//        int id = cvData->blobs[i].id;
//        ofPoint firstPt;
//        
//        ofPolyline line = cvData->blobs[i].blob;
//        for (auto & pt : line.getVertices()){
//            pt = cvData->remapForScreen(SCREEN_LEFT, pt);
//        }
//        
//        ofSetColor(255,255,255, 50);
//        line.draw();
//        
//        
//        ofRectangle bounds = line.getBoundingBox();
//        
//        float div = (float)max(ofGetMouseX(), 3);
//        
//        int divisions = ceil(bounds.width / div);
//        
//        vector < ofPoint > pts;
//        
//        line = line.getResampledBySpacing(1);
//        
//        float w = div; //bounds.getWidth()/(float)divisions;
//        
//        ofPolyline hmm;
//        
//        float startX = bounds.x + bounds.width/2.0 - (float)divisions*0.5*10.0;
//        
//        
//        
//        for (int j = 0; j < divisions; j++){
//            
//            
//            ofRectangle tempRect(startX + j * w, bounds.y, w, bounds.height);
//            bool bAny = false;
//            float minY = bounds.y + bounds.height;
//            for (auto & pt : line){
//                if (tempRect.inside(pt)){
//                    if (pt.y < minY){
//                        minY = pt.y;
//                        bAny= true;
//                    }
//                }
//            }
//            if (!bAny){
//                //minY = bounds.y;
//            }
//            
//            minY -= 20;
//            
//            ofFill();
//            ofRectangle tempRect2(startX + j * w, minY, w, bounds.height - (minY- bounds.y));
//            
//            //ofCircle(ofPoint(bounds.x + j * w + w/2, minY), w/2);
//            //ofRect(tempRect2);
//            
//            ofPoint circlePos = ofPoint(startX + j * w + w/2, minY);
//            float angle = PI;
//            float angleStep = PI/10.0;
//            float width = w/2;
//            
//            if (j == 0){
//                firstPt = circlePos;
//            }
//            
//            for (int k = 0; k < 10; k++){
//                ofPoint pt = circlePos + width * ofPoint(cos(angle), sin(angle));
//                angle += angleStep;
//                hmm.addVertex(pt);
//            }
//            
//            //pts.push_back( ofPoint(bounds.x + j * w + w/2, minY));
//        }
//        
//        ofSetColor(ofColor::darkGreen);
//        ofPolyline lineTemp(pts);
//        
//        hmm.addVertex( hmm[hmm.size()-1].x, bounds.y + bounds.height);
//        hmm.addVertex( hmm[0].x, bounds.y + bounds.height);
//        
//        
//        
//        ofPoint centroid = hmm.getCentroid2D();
//        for (auto & pp : hmm){
//            pp = (pp - centroid) * 1.3 + centroid;
//        }
//        
//        ofBeginShape();
//        for (auto & pp : hmm){
//            ofVertex(pp);
//        }
//        ofNextContour();
//        for (auto & pp : line){
//            ofVertex(pp);
//        }
//        ofEndShape();
//        
//        
//        for (int j = 0; j < plants.size(); j++){
//            if(plants[j].id == id){
//                plants[j].setPos(firstPt, 0.8);
//            }
//        }
//        
//        //hmm.draw();
//        
//        //lineTemp.draw();
//        
//        
//        
//    }
    
    
    
   
    
//    ofSetColor(0);
//    line.draw();
    
    
//        ofRectangle src(0,0,cvData->width, cvData->height);
//        ofRectangle dst = src;
//        ofRectangle target = RM->getRectForScreen(SCREEN_LEFT);
//        dst.scaleTo(target);
//    
//        for (int i = 0; i < cvData->blobs.size(); i++){
//            ofPath p;
//            p.setFillColor(ofColor(0,0,0,10));
//            ofPolyline line = cvData->blobs[i].blob;
//    
//            for (auto & pt : line){
//                pt = cvData->remapForScreen(SCREEN_LEFT, pt);
//            }
//    
//            line.simplify();
//            for(auto &l : line){
//                p.lineTo(l);
//                float x = l.x - glowRadius;
//                float y = l.y - glowRadius;
//                ofSetColor(255, glowOpacity);
//                //glow.draw(x, y, glowRadius*2, glowRadius*2);
//            }
//            
//            p.draw();
//        }

}
// --------------- events
void plantsScene::blobBorn(int id){
    int whichBlob = cvData->idToBlobPos[id];
    ofPoint centroid = cvData->blobs[whichBlob].blob.getCentroid2D();
    
    //-------------------------------------
//        ofRectangle src(0,0,cvData->width, cvData->height);
//        ofRectangle dst = src;
//        ofRectangle target = RM->getRectForScreen(SCREEN_LEFT);
//        dst.scaleTo(target);
        centroid = cvData->remapForScreen(SCREEN_LEFT, centroid);
    //-------------------------------------
    
    addPlant(centroid, id, true);
    addPlant(centroid, id, false);
}
void plantsScene::blobDied(int id){
    remove(id);
}
void plantsScene::start(){
    reset();
}
void plantsScene::stop(){
}


