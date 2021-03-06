

#include "inputManager.h"



//345,505
//1725,420
//1785,920
//375,1005


//
//351,513
//1854,405
//1884,966
//387,1056


using namespace ofxCv;


void inputManager::setup(){
 
#ifdef USE_LIVE_VIDEO
    
    auto deviceList = ofxBlackmagic::Iterator::getDeviceList();
    
    int count = 0;
    
    
    count = 0;
    for(auto device : deviceList) {
        
        auto input = shared_ptr<ofxBlackmagic::Input>(new ofxBlackmagic::Input());
        
        
        cout << device << " " << input << endl;
        
        
        
        static int index = 0;
        
        if (device.modelName.find("Intensity") == std::string::npos){
            
            auto mode = bmdModeHD1080p30; // switch this mode to match the resolution/refresh of your input stream
            //            if (count > 0){
            //                mode = bmdModeHD1080p2997;
            //            }
            input->startCapture(device, mode);
            this->inputs.push_back(input);
            count ++;
            
            cout << "INTENSITY" << endl;
        }
        
        
    }
    
    for(auto device : deviceList) {
        
        auto input = shared_ptr<ofxBlackmagic::Input>(new ofxBlackmagic::Input());
        
        
        cout << device << " " << input << endl;
        
        
        
        static int index = 0;
        
        if (device.modelName.find("Intensity") != std::string::npos){
            
            auto mode = bmdModeHD1080p2997; // switch this mode to match the resolution/refresh of your input stream
            //            if (count > 0){
            //                mode = bmdModeHD1080p2997;
            //            }
            input->startCapture(device, mode);
            this->inputs.push_back(input);
            count ++;
            
            cout << "INTENSITY" << endl;
        }
        
        
    }
    
    CVM[0].setup();
    CVM[1].setup();
    CVM[2].setup();
    
    inputAsGray.allocate(1920, 1080, OF_IMAGE_GRAYSCALE);
    inputAsGray2.allocate(1920, 1080, OF_IMAGE_GRAYSCALE);
    inputAsGray3.allocate(1920, 1080, OF_IMAGE_GRAYSCALE);
    
    inputWarped.allocate(INPUT_WARP_TO_W,INPUT_WARP_TO_H, OF_IMAGE_GRAYSCALE);
    inputWarped2.allocate(INPUT_WARP_TO_W,INPUT_WARP_TO_H, OF_IMAGE_GRAYSCALE);
    inputWarped3.allocate(INPUT_WARP_TO_W,INPUT_WARP_TO_H, OF_IMAGE_GRAYSCALE);

#else
    
    
    
    player.load("newFootage/leftSide.mp4");
    player.play();
    
    player2.load("newFootage/rightSide.mp4");
    player2.play();
    
    player3.load("newFootage/table.mp4");
    player3.play();

    
    CVM[0].setup();
    CVM[1].setup();
    CVM[2].setup();
    
    inputQuad.push_back( cv::Point2f(  15,58 ));
    inputQuad.push_back( cv::Point2f( 308,54  ));
    inputQuad.push_back( cv::Point2f( 317,164  ));
    inputQuad.push_back( cv::Point2f(8,164   ));
    
    
    inputAsGray.allocate(player.getWidth(), player.getHeight(), OF_IMAGE_GRAYSCALE);
    inputAsGray2.allocate(player2.getWidth(), player2.getHeight(), OF_IMAGE_GRAYSCALE);
    inputAsGray3.allocate(player3.getWidth(), player3.getHeight(), OF_IMAGE_GRAYSCALE);
    
    inputWarped.allocate(INPUT_WARP_TO_W,INPUT_WARP_TO_H, OF_IMAGE_GRAYSCALE);
    inputWarped2.allocate(INPUT_WARP_TO_W,INPUT_WARP_TO_H, OF_IMAGE_GRAYSCALE);
    inputWarped3.allocate(INPUT_WARP_TO_W,INPUT_WARP_TO_H, OF_IMAGE_GRAYSCALE);

#endif

    
    group.add(threshold1.set("threshold1", 150, 0, 255));
    group.add(threshold2.set("threshold2", 150, 0, 255));
    group.add(threshold3.set("threshold3", 150, 0, 255));
    group.add(bTrackTable.set("bTrackTable", false));
    group.add(needsFlow.set("needsFlow", true));
    group.add(bDrawBuilding.set("bDrawBuilding", false));
    group.add(dmxOffValue.set("dmxOffValue", 0, 0, 255));
    
    
    
    
    
    gui.setup("inputSettings", "inputSettings.xml");
    gui.add(group);
    gui.loadFromFile("inputSettings.xml");
    
    
    
}

void inputManager::update(){
    
    
    #ifdef USE_LIVE_VIDEO
    for(int i = 0; i < this->inputs.size(); i++) {
        inputs[i]->update();
        
        if (!bTrackTable){
        if (i == 0 && inputs[0]->isFrameNew()){
            
            
            
            
            cv::Mat from = toCv(inputs[0]->getPixels());
            cv::Mat to = toCv(inputAsGray);
            ofxCv::copyGray(from, to);
            

            //ofxCv::copyGray(toCv(inputs[0]->getPixels()), toCv(inputAsGray));
            

//            125,175
//            1825,145
//            1910,735
//            65,805
            
//            2180,270
//            3620,360
//            3660,890
//            2085,790
            
            
            
            ofPoint a(125,175);
            ofPoint b(1825,145);
            ofPoint c(1910,735);
            ofPoint d(65,805);
            
            
            
            inputQuad.clear();
            inputQuad.push_back( cv::Point2f(  a.x  , a.y ));
            inputQuad.push_back( cv::Point2f(  b.x  , b.y ));
            inputQuad.push_back( cv::Point2f(  c.x  , c.y ));
            inputQuad.push_back( cv::Point2f(  d.x  , d.y ));
            
            ofxCv::unwarpPerspective(to, inputWarped, inputQuad);
            inputWarped.update();
            CVM[0].update(inputWarped.getPixels(), threshold1, needsFlow);
            

        } else if (i == 1 && inputs[1]->isFrameNew()){
            

            cv::Mat from = toCv(inputs[1]->getPixels());
            cv::Mat to = toCv(inputAsGray2);
            ofxCv::copyGray(from, to);
            
            
            
//            for (int j = 0; j < 1920*1080; j++){
//                inputAsGray.getPixels()[j] = inputs[1]->getPixels()[j*4];
//            }
//            //            ofImage img;
//            //            img.setFromPixels(inputs[0]->getPixels());
//            //            img.setImageType(OF_IMAGE_GRAYSCALE);
//            cv::Mat to = toCv(inputAsGray);
//            //            2220,460
//            //            3600,225
//            //            3770,695
//            //            2255,980
            
            
//            2180,270
//            3620,360
//            3660,890
//            2085,790
            
            ofPoint a( 2180-1920*1,270);
            ofPoint b(3620-1920*1,360);
            ofPoint c(3660-1920*1,890);
            ofPoint d(2085-1920*1,790);
            
            inputQuad.clear();
            inputQuad.push_back( cv::Point2f(  a.x  , a.y ));
            inputQuad.push_back( cv::Point2f(  b.x  , b.y ));
            inputQuad.push_back( cv::Point2f(  c.x  , c.y ));
            inputQuad.push_back( cv::Point2f(  d.x  , d.y ));
            
            ofxCv::unwarpPerspective(to, inputWarped2, inputQuad);
            inputWarped2.update();
            CVM[1].update(inputWarped2.getPixels(), threshold2, needsFlow);


            
        }
        }
        
            if (bTrackTable){
                if (i == 2 && inputs[2]->isFrameNew()){
                    
                    
//                    cv::Mat from = toCv(inputs[2]->getPixels());
//                    cv::Mat to = toCv(inputAsGray);
//                    ofxCv::copyGray(from, to);

                    
                    cv::Mat from = toCv(inputs[2]->getPixels());
                    cv::Mat to = toCv(inputAsGray3);
                    ofxCv::copyGray(from, to);
                    
                    
                    //            4070,265
                    //            5590,155
                    //            5635,690
                    //            4110,780
                    
//                    4090,310
//                    5610,220
//                    5655,770
//                    4125,870
//                    
                    
                    ofPoint a( 4090-1920*2,310);
                    ofPoint b(5610-1920*2,220);
                    ofPoint c( 5655-1920*2,770);
                    ofPoint d(4125-1920*2,870);
                    
                    inputQuad.clear();
                    inputQuad.push_back( cv::Point2f(  a.x  , a.y ));
                    inputQuad.push_back( cv::Point2f(  b.x  , b.y ));
                    inputQuad.push_back( cv::Point2f(  c.x  , c.y ));
                    inputQuad.push_back( cv::Point2f(  d.x  , d.y ));
                    
                    ofxCv::unwarpPerspective(to, inputWarped3, inputQuad);
                    inputWarped3.update();
                    CVM[2].update(inputWarped3.getPixels(), threshold3, needsFlow);
                    
                    
                    
                }
            }
        
        //cout << input->isFrameNew() << endl;
        
    }
#else
    

    player.update();
    player2.update();
    player3.update();
    

    if (!bTrackTable || ofGetFrameNum() < 120){
        if (player.isFrameNew()){
            
            cv::Mat from = toCv(player.getPixels());
            cv::Mat to = toCv(inputAsGray);
            ofxCv::copyGray(from, to);
            
            ofPoint a(190,275);
            ofPoint b(1715,300);
            ofPoint c(1810,865);
            ofPoint d(135,850);

            inputQuad.clear();
            inputQuad.push_back( cv::Point2f(  a.x  , a.y ));
            inputQuad.push_back( cv::Point2f(  b.x  , b.y ));
            inputQuad.push_back( cv::Point2f(  c.x  , c.y ));
            inputQuad.push_back( cv::Point2f(  d.x  , d.y ));
            
            ofxCv::unwarpPerspective(to, inputWarped, inputQuad);
            inputWarped.update();
            CVM[0].update(inputWarped.getPixels(), threshold1, needsFlow);
        }
        
        if (player2.isFrameNew()){
            
            
            cv::Mat from = toCv(player2.getPixels());
            cv::Mat to = toCv(inputAsGray2);
            ofxCv::copyGray(from, to);
            
            ofPoint a(3925-1920*2,180);
            ofPoint b(5595-1920*2,280);
            ofPoint c(5620-1920*2,875);
            ofPoint d(3865-1920*2,780);
            
            inputQuad.clear();
            inputQuad.push_back( cv::Point2f(  a.x  , a.y ));
            inputQuad.push_back( cv::Point2f(  b.x  , b.y ));
            inputQuad.push_back( cv::Point2f(  c.x  , c.y ));
            inputQuad.push_back( cv::Point2f(  d.x  , d.y ));
            
            ofxCv::unwarpPerspective(to, inputWarped2, inputQuad);
            inputWarped2.update();
            CVM[1].update(inputWarped2.getPixels(), threshold2, needsFlow);
        }
    }
    
    if (bTrackTable)
    if (player3.isFrameNew()){
        
        
        cv::Mat from = toCv(player3.getPixels());
        cv::Mat to = toCv(inputAsGray3);
        ofxCv::copyGray(from, to);
        
        
        //351,513
        //1854,405
        //1884,966
        //387,1056
     
        ofPoint c(303,465);
        ofPoint d(1677,354);
        ofPoint a(1713,858);
        ofPoint b(345,927);
        
        inputQuad.clear();
        inputQuad.push_back( cv::Point2f(  a.x  , a.y ));
        inputQuad.push_back( cv::Point2f(  b.x  , b.y ));
        inputQuad.push_back( cv::Point2f(  c.x  , c.y ));
        inputQuad.push_back( cv::Point2f(  d.x  , d.y ));
        
        ofxCv::unwarpPerspective(to, inputWarped3, inputQuad);
        inputWarped3.update();
        CVM[2].update(inputWarped3.getPixels(), threshold3, needsFlow);
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
    #endif
  
    inputWarped.draw(0,400);
    inputWarped2.draw(inputWarped.getWidth(),400);
    inputWarped3.draw(inputWarped.getWidth()*2,400);
    
    
    ofPushMatrix();
    //ofTranslate(player.getWidth(), inputWarped.getHeight());
    CVM[0].draw();
    ofTranslate(500,0);
    CVM[1].draw();
    ofTranslate(1000,0);
    CVM[2].draw();
    
    if (bTrackTable){
        ofTranslate(1000,0);
        CVM[2].draw();
    }
    ofPopMatrix();
    
    gui.draw();
    
   // player3.draw(0,0, player3.getWidth()*0.33333, player3.getHeight()*0.3333);
}