//
//  wavesScene.cpp
//  funkyForms
//
//  Created by Gordey on 8/9/16.
//
//

#include "wavesScene.hpp"
// ------------ Setup
void wavesScene::setup(){
    // size
    int w = RM->getWidth();
    int h = RM->getHeight();
    
    // setup parameters
    stencilWaves.setupGui();
    gradientWaves.setupGui();
    
    // setup gui
    setupGui();
    
    // setup obj
    gradientWaves.setup(w, h);
    stencilWaves.screenLeft = RM->getRectForScreen(SCREEN_LEFT);
    stencilWaves.screenRight = RM->getRectForScreen(SCREEN_RIGHT);
    stencilWaves.setup(w, h);
}
void wavesScene::setupGui(){
    gui.setup("settings_wavesScene", "settings_wavesScene.xml");
    parameters.add(isStencilWaveMode.set("isStencilWaveMode", true));
    parameters.add(isGradientWavesMode.set("isGradientWavesMode", false));
    parameters.setName("wavesSceneParameters");
    gui.add(parameters);
    gui.add(gradientWaves.parameters);
    gui.add(stencilWaves.parameters);
    gui.loadFromFile("settings_wavesScene.xml");
}
// ------------ Update
void wavesScene::update(){
    updateInput();
    if(isGradientWavesMode) gradientWaves.update();
    if(isStencilWaveMode) stencilWaves.update();
}
void wavesScene::updateInput(){
    for (int z = 0; z < 2; z++){
        for(int i=0; i< cvData[z]->blobs.size(); i++) {
            ofPolyline line = cvData[z]->blobs[i].blob;
    
            ofVec2f pt = cvData[z]->blobs[i].centroidSmoothed;
            pt = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
    
            for (auto & p : line.getVertices()){
                p = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, p);
            }
            if(isStencilWaveMode){
                stencilWaves.addPath(line);
    
                ofVec2f vel = cvData[z]->blobs[i].avgVel;
    
                for(auto &w: stencilWaves.waves){
                    for(auto &p: w.points){
                        if(p.p.distance(pt)<100 && vel.dot(ofVec2f(0, -1)) > 0){
                            w.addForceTo(&p, vel.normalize().y);
                        }
                    }
                }
                
            }
            
        }
    }
//    for (int i = 0; i < cvData->blobs.size(); i++){
//        ofPolyline line = cvData->blobs[i].blob;
//        
//        ofVec2f pt = cvData->blobs[i].centroidSmoothed;
//        pt = cvData->remapForScreen(SCREEN_LEFT, pt);
//
//        for (auto & p : line.getVertices()){
//            p = cvData->remapForScreen(SCREEN_LEFT, p);
//        }
//        if(isStencilWaveMode){
//            stencilWaves.addPath(line);
//            
//            ofVec2f vel = cvData->blobs[i].avgVel;
//
//            for(auto &w: stencilWaves.waves){
//                for(auto &p: w.points){
//                    if(p.p.distance(pt)<100 && vel.dot(ofVec2f(0, -1)) > 0){
//                        w.addForceTo(&p, vel.normalize().y);
//                    }
//                }
//            }
//            
//        }
//
//    }



        // NOTE: since this is threaded, there's sometimes a frame where resampledSmooth might not
        // have any vertices... adding a check.
//        if ((*(cvData[0]->trackedContours))[id].data.resampleSmoothed.size() > 0){
//            ofPolyline &line =  (*(cvData[0]->trackedContours))[id].data.resampleSmoothed;
//            
//            for (int i = 0; i < line.size(); i += line.size()/10 ) {
//                ofPoint pt = line.getVertices()[i];
//                pt =  cvData[0]->remapForScreen(SCREEN_LEFT, pt);
//                ofVec2f vel = (*(cvData[0]->trackedContours))[id].data.velPts[i];
//                if(isGradientWavesMode){
//                    for(auto &w: gradientWaves.waves){
//                        w.addTarget(pt, vel);
//                    }
//                }
//                if(isStencilWaveMode){
//                    for(auto &w: stencilWaves.waves){
//                        w.addTarget(pt, vel);
//                    }
//                }
//            }
//            if(isStencilWaveMode){
//                ofPolyline line2 = cvData[0]->getResampledLineAt(id, 2);
//                ofPolyline lineOffset;
//                for(auto &p : line2 ){
//                    ofPoint point = p;
//                    point = cvData[0]->remapForScreen(SCREEN_LEFT, point);
//                    lineOffset.lineTo(point);
//                }
//                stencilWaves.addPath(lineOffset);
//            }
//        }

}
// ------------ Draw
void wavesScene::draw(){

    if(isGradientWavesMode) gradientWaves.draw();
    if(isStencilWaveMode) stencilWaves.draw();

//    drawPeople();
}
void wavesScene::drawGui(){
     gui.draw();
}
void wavesScene::drawPeople(){
    for (int i = 0; i < cvData[0]->blobs.size(); i++){
        ofSetColor(255);
        ofPolyline line = cvData[0]->blobs[i].blob;
        for (auto & pt : line){
            pt = cvData[0]->remapForScreen(SCREEN_LEFT, pt);
        }
        line.draw();
    }
}
// ------------ Events
void wavesScene::start(){
}
void wavesScene::stop(){
    
}
void wavesScene::blobBorn(int packetId, int id){
    
}
void wavesScene::blobDied(int packetId, int id){
    
}