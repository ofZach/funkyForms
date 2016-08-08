#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    SM.scenes.push_back(new simpleScene());
    SM.scenes.push_back(new plantsScene());
    
    IM.setup();

    
    for (int i = 0; i < SM.scenes.size(); i++){
        SM.scenes[i]->cvData = &IM.CVM.packet;
    }
    SM.setup();
    
    bDrawDebug = true;
}

//--------------------------------------------------------------
void ofApp::update(){

    IM.update();
    
    //-----------------------------------------------------------
    // check for new or dead blobs;
        for (auto a : IM.CVM.bornThisFrame){
            SM.blobBorn(a);
        }
        
        for (auto a : IM.CVM.diedThisFrame){
            SM.blobDied(a);
        }
        IM.CVM.diedThisFrame.clear();
        IM.CVM.bornThisFrame.clear();
    
    //-----------------------------------------------------------
    
    SM.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    if (bDrawDebug){
        IM.draw();
    } else {
//        IM.draw();
        SM.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == 'd'){
        bDrawDebug = !bDrawDebug;
    }
    
    if (key  == ' '){
        SM.advanceScene();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
