//
//  PlantManager.cpp
//  PlantSpring
//
//  Created by Zerc on 8/5/16.
//
//

#include "PlantManager.hpp"
// --------------- setup
void PlantManager::setup(){
    setupGui();
//    for (int i = 0; i < 6; i++) {
//        addPlant(ofVec2f(ofRandomWidth(), ofRandom(100, ofGetHeight())));
//    }
//    for (int i = 0; i < 4; i++) {
//        addBgPlant( ofVec2f(ofRandomWidth(), ofGetHeight() ) );
//    }
    for (int i = 0; i < 40; i++) {
        randSwatchIndex.push_back((int)ofRandom(4));
    }
}
void PlantManager::setupParticles(){
    particles.clear();
    for (int i = 0; i < particleCount; i++){
        particle myParticle;
        float x = ofRandom(0,ofGetWidth());
        float y = ofRandom(0,ofGetHeight());
        myParticle.setInitialCondition(x,y,0,0);
        particles.push_back(myParticle);
//        addPlant(ofVec2f(x, y));
    }
}
void PlantManager::onNewPlant(){
//    addPlant(IM->getNewTarget().pos);
}
void PlantManager::addBgPlant(ofVec2f _pos){
    bgPlants.push_back( *new Plant );
    int i = bgPlants.size()-1;
    
    bgPlants[i].rig.cbCount = ofRandom(5, 7) ;
    bgPlants[i].rig.mbCount = ofRandom(4, 6) ;
    
    bgPlants[i].rig.dir = ofVec2f(0, -1);
    bgPlants[i].rig.mbLengthMax = 200 ;
    bgPlants[i].rig.mbLengthMin = 100 ;
    bgPlants[i].rig.cbLengthMax = 70 ;
    bgPlants[i].rig.cbLengthMin = 20 ;
    bgPlants[i].rig.timeSpeed = 0.01;
    
    bgPlants[i].mbWidth = 50;
    bgPlants[i].cbWidth = 10;
    bgPlants[i].rig.pos = _pos;
    
    ofFloatColor col = swatch[(int)ofRandom(4)];
    col.setBrightness(col.getBrightness()/2);
    bgPlants[i].color = col;
    
    bgPlants[i].setup();
    bgPlants[i].ageMax = ofRandom(600, 1000);
    bgPlants[i].fadeIn();
}
void PlantManager::addPlant(ofVec2f _pos, int id){
    plants.push_back( *new Plant );
    int i = plants.size()-1;
    
    ofVec2f dir[2] = { ofVec2f(-1, 0), ofVec2f(1, 0)};
    plants[i].id = id;
    plants[i].rig.dir = dir[(int)ofRandom(1)];
    
    plants[i].rig.cbCount = ofRandom(3, 6) ;
    plants[i].rig.mbCount = ofRandom(5, 6) ;
    
    plants[i].rig.mbLengthMax = mainBranchWMax ;
    plants[i].rig.mbLengthMin = mainBranchWMin ;
    plants[i].rig.cbLengthMax = childBranchWMax ;
    plants[i].rig.cbLengthMin = childBranchWMin ;
    
    plants[i].mbWidth = mainBranchWMin;
    plants[i].cbWidth = childBranchWMin;
    plants[i].rig.pos = _pos;
    
    plants[i].color = swatch[(int)ofRandom(4)];

    plants[i].setup();
    plants[i].fadeIn();
        
    
}
void PlantManager::setupGui(){
    parameters.setName("PlantManager");
    parameters.add(plantScale.set("plantScale", 1.0, 0.1, 2.0));
    parameters.add(mainBranchWMin.set("mainBranchWMin", 5, 1, 200));
    parameters.add(mainBranchWMax.set("mainBranchWMax", 5, 1, 200));
    parameters.add(childBranchWMin.set("childBranchWMin", 5, 1, 200));
    parameters.add(childBranchWMax.set("childBranchWMax", 5, 1, 200));
    parameters.add(particleRepulseRadius.set("particleRepulseRadius", 10, 5, 500));
    parameters.add(particleRepulseForce.set("particleRepulseForce", 0.5, 0.01, 1.0));
    parameters.add(particleAttractRadius.set("particleAttractRadius", 100, 5, 500));
    parameters.add(particleAttractForce.set("particleAttractForce", 0.5, 0.01, 1.0));
    gui.setup(parameters);
    gui.loadFromFile("settings.xml");
}
void PlantManager::remove(int id){
    for(auto &p : plants){
        if(p.id == id){
            p.fadeOut();
            float mindist = 2000;
            int index = 0;
            for(int i = 0; i < peoplePoints.size(); i++){
                float dist = p.getPos().distance(peoplePoints[i]);
                if(dist < mindist){
                    mindist = dist;
                    index = i;
                }
            }
            ofVec2f &closestP = peoplePoints[index];
            p.setPos(closestP, 0.5);
        }
    }
//    plants.erase(
//                    std::remove_if(
//                                   plants.begin(),
//                                   plants.end(),
//                                   [&](Plant & p){return p.id == id;}),
//                    plants.end());
}
// --------------- update
void PlantManager::update(){
    updatePlantsParameters();
    updateBgPlants();
//    updateBgPlantsRemoval();
    updatePlants();
    updatePlantRemoval();
    updatePeoples();
}
void PlantManager::updateParticles(){
    for (int i = 0; i < particles.size(); i++){
        particles[i].resetForce();
    }
    for (int i = 0; i < particles.size(); i++){
        for (int j = 0; j < i; j++){
            particles[i].addRepulsionForce(particles[j], particleRepulseRadius, particleRepulseForce);
        }
        
    }
    for (int i = 0; i < particles.size(); i++){
        particles[i].addDampingForce();
        particles[i].update();
    }
}
void PlantManager::updatePlants(){
    peoplePoints.clear();
    for(auto &id: cvData->idsThisFrame){
        ofPolyline line = (*(cvData->trackedContours))[id].resampleSmoothed;

        int size = 4;
        ofVec2f point[4];
        float pctStep = 1.0/(size*1.0);
        float pct = 0;
        
        for (int i = 0; i < size; i++) {
            point[i] = line.getPointAtPercent(pct);
            
            pct += pctStep;
            peoplePoints.push_back(point[i]);
        }
    }
    for(auto &p: plants){
        p.update();
        int id = p.id;
        int whichBlob = cvData->idToBlobPos[id];
        ofPolyline line = (*(cvData->trackedContours))[id].resampleSmoothed;
        
        int size = 4;
        ofVec2f point[4];
        float pctStep = 1/size;
        float pct = 0;
        
        for (int i = 0; i < size; i++) {
            point[i] = line.getPointAtPercent(pct);
            pct+=pctStep;
        }
//        ofPoint centroid = cvData->blobs[whichBlob].blob.getCentroid2D();
        if(!p.isFading){
            p.setPos(point[2], 0.5);
        }
    }
}
void PlantManager::updateBgPlants(){
    for(auto &p: bgPlants){
        p.update();
    }
}
void PlantManager::updateBgPlantsRemoval(){
//    for (int i =0; i < bgPlants.size(); i++) {
//        if(bgPlants[i].isFadeFinished()){
//            ofVec2f pos = ofVec2f(IM->targets[(int)ofRandom(IM->targets.size()-1)].pos.x, ofGetHeight());
//            addBgPlant(pos);
//            bgPlants.erase(bgPlants.begin()+i);
//        }
//    }
}
void PlantManager::updatePlantsParameters(){
    for(auto &p: plants){
        p.scale = plantScale;
    }
}
void PlantManager::updatePlantCreation(){
//    for(auto &t: IM->targets){
//        if(!t.isBusy && t.vel.length() > 2){
//            addPlant(t.pos);
//            t.pointIndex = ofRandom(t.points.size()-1);
//        }
//    }
//    IM->onNewTarget(this, &PlantManager::onNewPlant);
}
void PlantManager::updatePlantRemoval(){
    for (int i =0; i<plants.size(); i++) {
        if(plants[i].isFadeFinished()){
            plants.erase(plants.begin()+i);
        }
    }
//    for (int i =0; i<plants.size(); i++) {
//        if(plants[i].isFadeFinished()){
//            ofVec2f pos = ofVec2f(IM->targets[(int)ofRandom(IM->targets.size()-1)].pos.x, ofRandom( 300, ofGetHeight()));
//            addPlant(pos);
//            plants.erase(plants.begin()+i);
//        }
//    }
}
void PlantManager::updatePeoples(){
//    ofxCv::ContourFinder *finder = IM->CVM.getContourFinder();
//    ofxCv::RectTracker& tracker = finder->getTracker();
//    peopleResampled.clear();
//    for (int i = 0; i <  finder->size(); i++) {
//        int label =  finder->getLabel(i);
//        ofPolyline &line = IM->getTrackedContours()[label].resampleSmoothed;
//        ofPolyline l;
//        for(auto &p : line){
//            l.lineTo(p+IM->pos);
//        }
//        peopleResampled.push_back(l);
//    }
}
// --------------- draw
void PlantManager::draw(){
    drawBgPlants();
    drawPlants();
//    drawPeoples();
    gui.draw();
}
void PlantManager::drawParticles(){
    for (int i = 0; i < particles.size(); i++){
        particles[i].draw();
    }
}
void PlantManager::drawPlants(){
    for(auto &p: plants){
        p.draw();
    }
}
void PlantManager::drawBgPlants(){
    for(auto &p: bgPlants){
        p.draw();
    }
}
void PlantManager::drawPeoples(){
    int j = 0;
    for(auto &p: peoplePoints){
        ofFill();
        ofSetColor(ofColor::white);
        ofDrawCircle(p, 5);
    }
}
