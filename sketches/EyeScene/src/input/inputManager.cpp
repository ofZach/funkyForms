

#include "inputManager.h"



void inputManager::setup(){
 
    player.load("../../../../funkyForms/bin/data/testFootage/bodies0.mov");
    player.play();
    
    CVM.setup();
    
    inputQuad.push_back( cv::Point2f(  15,58 ));
    inputQuad.push_back( cv::Point2f( 308,54  ));
    inputQuad.push_back( cv::Point2f( 317,164  ));
    
    inputQuad.push_back( cv::Point2f(8,164   ));
    
    blah.allocate(600,250, OF_IMAGE_COLOR);
    pos.set(250, ofGetHeight()-player.getHeight());
    
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
    for (int i = 0; i < CVM.getContourFinder()->size(); i++) {
        Target t;
        ofPoint center = ofxCv::toOf(CVM.getContourFinder()->getCenter(i));
        ofVec2f vel = ofxCv::toOf(CVM.getContourFinder()->getVelocity(i));

        t.pos = center + pos;
        t.vel = vel;
        targets.push_back(t);
    }
}
void inputManager::update(){
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
    
//    player.draw(0,0);
    
    
//    blah.draw(player.getWidth(),0);
    
    ofPushMatrix();
    ofTranslate(pos);
    CVM.draw();
    ofPopMatrix();
    
}