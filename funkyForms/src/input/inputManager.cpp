

#include "inputManager.h"



void inputManager::setup(){
 
#ifdef USE_LIVE_VIDEO
    cout << "video " << endl;
    auto deviceList = ofxBlackmagic::Iterator::getDeviceList();
    
    int count = 0;
    for(auto device : deviceList) {
        
        auto input = shared_ptr<ofxBlackmagic::Input>(new ofxBlackmagic::Input());
        
        auto mode = bmdModeHD1080p30; // switch this mode to match the resolution/refresh of your input stream
        //            if (count > 0){
        //                mode = bmdModeHD1080p2997;
        //            }
        input->startCapture(device, mode);
        this->inputs.push_back(input);
        count ++;

        
    }
#endif
    
    
    
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
    
    #ifdef USE_LIVE_VIDEO
    for(auto input : this->inputs) {
        input->update();
        cout << input->isFrameNew() << endl;
        
    }
#endif
    
}

void inputManager::draw(){
    
    #ifdef USE_LIVE_VIDEO
    int count = 0;
    for(auto input : this->inputs) {
        ofSetColor(255);
        input->draw(count * 1920*0.2,0, 1920*0.2, 1080*0.2);
        count++;
    }

#endif;
    
   // player.draw(0,0);
    
    
   // inputWarped.draw(player.getWidth(),0);
    
    ofPushMatrix();
    //ofTranslate(player.getWidth(), inputWarped.getHeight());
    CVM[0].draw();
    ofTranslate(500,0);
    CVM[1].draw();
    ofPopMatrix();
}