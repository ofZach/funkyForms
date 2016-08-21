

#include "inputManager.h"



void inputManager::setup(){
 
    player.load("testFootage/bodies0.mov");
    player.play();
    
    player2.load("testFootage/bodies1.mov");
    player2.play();

    
    CVM[0].setup();
    CVM[1].setup();
    
    inputQuad.push_back( cv::Point2f(  15,58 ));
    inputQuad.push_back( cv::Point2f( 308,54  ));
    inputQuad.push_back( cv::Point2f( 317,164  ));
    inputQuad.push_back( cv::Point2f(8,164   ));
    
    inputWarped.allocate(INPUT_WARP_TO_W,INPUT_WARP_TO_H, OF_IMAGE_COLOR);
    

}

void inputManager::update(){
    
    player.update();
    player2.update();
    
    if (player.isFrameNew()){
        ofxCv::unwarpPerspective(player, inputWarped, inputQuad);
        inputWarped.update();
        CVM[0].update(inputWarped.getPixels());
    }
    
    if (player2.isFrameNew()){
        ofxCv::unwarpPerspective(player2, inputWarped, inputQuad);
        inputWarped.update();
        CVM[1].update(inputWarped.getPixels());
    }
}

void inputManager::draw(){
    
   // player.draw(0,0);
    
    
   // inputWarped.draw(player.getWidth(),0);
    
    ofPushMatrix();
    //ofTranslate(player.getWidth(), inputWarped.getHeight());
    CVM[0].draw();
    ofTranslate(500,0);
    CVM[1].draw();
    ofPopMatrix();
}