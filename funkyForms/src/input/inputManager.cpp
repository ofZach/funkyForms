

#include "inputManager.h"



void inputManager::setup(){
 
    player.load("testFootage/bodies0.mov");
    player.play();
    
    CVM.setup();
    
    inputQuad.push_back( cv::Point2f(  15,58 ));
    inputQuad.push_back( cv::Point2f( 308,54  ));
    inputQuad.push_back( cv::Point2f( 317,164  ));
    inputQuad.push_back( cv::Point2f(8,164   ));
    
    inputWarped.allocate(600,250, OF_IMAGE_COLOR);
    

}

void inputManager::update(){
    
    player.update();
    if (player.isFrameNew()){
        
        ofxCv::unwarpPerspective(player, inputWarped, inputQuad);
        inputWarped.update();
        CVM.update(inputWarped.getPixels());
        
    }
}

void inputManager::draw(){
    
    player.draw(0,0);
    
    
    inputWarped.draw(player.getWidth(),0);
    
    ofPushMatrix();
    ofTranslate(player.getWidth(), inputWarped.getHeight());
    CVM.draw();
    ofPopMatrix();
    
}