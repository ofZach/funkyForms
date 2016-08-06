

#include "inputManager.h"



void inputManager::setup(){
    defaultTarget.pos.set(0, 0);
    defaultTarget.vel.set(0,0);
    defaultTarget.rect.set(0, 0, 0, 0);
    
    player.load("../../../../funkyForms/bin/data/testFootage/bodies0.mov");
    player.play();
    
    CVM.setup();
    
    inputQuad.push_back( cv::Point2f(  15,58 ));
    inputQuad.push_back( cv::Point2f( 308,54  ));
    inputQuad.push_back( cv::Point2f( 317,164  ));
    inputQuad.push_back( cv::Point2f(8,164   ));
    
    float scale = 1.8;
    blah.allocate(600*scale, 250*scale, OF_IMAGE_COLOR);
    pos.set(200, ofGetHeight()-blah.getHeight());
   
    
    
    
    
}
void inputManager::calcAveragePos(){
    ofVec2f p;
    float posY = ofGetHeight();
    for(auto &t: targets){
        p += t.pos;
        if(t.pos.y<posY){
            posY = t.pos.y;
        }
    }
    p = ofVec2f(p.x/(targets.size()+1), posY);
    float s = 0.9;
    averagePos = averagePos*s + (1-s)*p;
}
inputManager::Target &inputManager::getClosesetTo(ofVec2f _pos){
    float distance = 3000;
    int index = 0;
    int i = 0;
    for(auto &t: targets){
        if(t.pos.distance(_pos) < distance){
            distance = t.pos.distance(_pos);
            index = i;
        }
        i++;
    }
    if(targets.size()>0){
        return targets[index];
    }else{
        return defaultTarget;
    }
}

inputManager::Target *inputManager::getFastestTarget(){
    int index = 0;
    ofVec2f zero(0, 0);
    ofVec2f vel(0, 0);
    int i = 0;
    for(auto &t: targets){
        if(t.vel.distance(zero) > vel.distance(zero) ){
            vel = t.vel;
            index = i;
        }
        i++;
    }
    
    return &targets[index];
    
}
void inputManager::updateTargets(){
    targets.clear();
    
    ofxCv::RectTracker& tracker = CVM.getContourFinder()->getTracker();
    for (int i = 0; i < CVM.getContourFinder()->size(); i++) {
        
        float rectX = CVM.getContourFinder()->getBoundingRect(i).x;
        float rectY = CVM.getContourFinder()->getBoundingRect(i).y;
        float rectW = CVM.getContourFinder()->getBoundingRect(i).width;
        float rectH = CVM.getContourFinder()->getBoundingRect(i).height;
        ofPoint center = ofxCv::toOf(CVM.getContourFinder()->getCenter(i));
        ofVec2f vel = ofxCv::toOf(CVM.getContourFinder()->getVelocity(i));
        int label = CVM.getContourFinder()->getLabel(i);
        
        Target t;
        t.pos = center + pos;
        t.vel = vel;
        t.age = tracker.getAge(label);
        t.rect.set(rectX, rectY, rectW, rectH);
        
        targets.push_back(t);
    }
}

void inputManager::update(){
    if(targets.size() > 0){
        isEmpty = false;
    }else{
        isEmpty = true;
    }
    updateTargets();
    calcAveragePos();
    player.update();
    if (player.isFrameNew()){
        
        ofxCv::unwarpPerspective(player, blah, inputQuad);
        blah.update();
        CVM.update(blah.getPixels());
        
    }
}

void inputManager::draw(){
    
    player.draw(0,0);
    
    
    blah.draw(player.getWidth(),0);
    
    ofPushMatrix();
    ofTranslate(pos);
    CVM.draw();
    ofPopMatrix();
}