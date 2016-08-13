#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    eyePair.setup();
    eyeParticles.setup();
    eyeLinker.setup();
    
    eyeParticles.setTargets(&targets.targets);
    eyePair.setTargetManager(&targets);
    eyePair.setTargets(&targets.targets);
    
    targets.setup();
    IM.setup();

}

//--------------------------------------------------------------
void ofApp::update(){
    IM.update();
    targets.update(mouseX, mouseY);

    ofVec2f m(mouseX, mouseY);
    ofVec2f vel = m - prevPos;
    prevPos = m;
    
    eyeLinker.setVel(vel);
    eyePair.update(IM.getAveragePos()+ofVec2f(0, -300));
    eyePair.lookAtSmart(IM.getFastestPos());
    eyeLinker.update(ofVec2f(mouseX, mouseY));
    eyeParticles.update(mouseX, mouseY);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
//    eyeParticles.draw();
    eyeLinker.draw();
//    eyePair.draw();
    
    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth()-50, 20);

    IM.draw();
    
    if(isRecord){
        settings.addTag("pos");
        settings.pushTag("pos", counter);
        settings.addValue("x", mouseX);
        settings.addValue("y", mouseY);
        settings.popTag();
        counter++;
    }
    ofSetColor(ofColor::red);
    ofDrawRectangle(IM.getFastestPos(), 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '1'){
        settings.addTag("data");
        settings.pushTag("data");
        isRecord = true;
    }
    if(key == '2'){
        settings.popTag();
        settings.saveFile("data.xml");
        isRecord = false;
    }
    if(key == 'w'){
        eyeParticles.setBehavior(EyeParticles::B_WAIT);
    }
    if(key == 'a'){
        eyeParticles.setBehavior(EyeParticles::B_ATTACK);
    }
    if(key == 'r'){
        eyeParticles.setBehavior(EyeParticles::B_RANDOM);
    }
    if(key == 'o'){
        eyeParticles.open();
    }
    if(key == 'c'){
        eyeParticles.close();
    }
    if(key == 'h'){
        eyePair.hitStart();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'h'){
        eyePair.hitEnd();
    }
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
