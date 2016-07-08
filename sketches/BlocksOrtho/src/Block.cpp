
//
//  Block.cpp
//  BlocksOrtho
//
//  Created by Zerc on 7/7/16.
//
//

#include "Block.hpp"
void Block::setup(ofVec2f _pos, int _w, int _h){
    icolor.setup(faceResolution, colors[(int)ofRandom(9)]);
    randomOffset = ofRandom(0,100);
    pos = _pos;
    w = _w;
    h = _h;
    for (int i = 0; i < 6; i++) {
        Face face;
        ofPolyline lT, lB;
        ofMesh m;
        face.lineT = lT;
        face.lineB = lB;
        face.mesh = m;
        face.color = colors[0];
        if(i%3==0){
            float satRange = 10;
            face.color.setSaturation(face.color.getSaturation()+ofRandom(-satRange, satRange) );
            face.color.setBrightness(ofRandom(200, 255));
        }
        float hangle = face.color.getHueAngle();
        face.color.setHueAngle(hangle+i*10.);
        faces.push_back(face);
    }
    rectDistance = maxDist;
}
void Block::update(int x, int y){
    // distance calculation
    ofVec2f pointer(x, y);
    float smooth = 0.9;
    ofVec2f rectPos(0, 0);
    ofVec2f distPos(0, 0);

    switch (direction) {
        case LEFT:
            rectPos = pos-rectDistance;
            distPos = pos-maxDist;
            break;
        case RIGHT:
            rectPos = pos+ofVec2f(rectDistance, -rectDistance);
            distPos = pos+ofVec2f(maxDist, -maxDist);
            break;
        case TOPLEFT:
            rectPos = pos+ofVec2f(-rectDistance, rectDistance);
            distPos = pos+ofVec2f(-maxDist, maxDist);
            break;
        case TOPRIGHT:
            rectPos = pos+rectDistance;
            distPos = pos+maxDist;
            break;
        default:
            rectPos = pos-rectDistance;
            distPos = pos-maxDist;
            break;
    };
    float dist = pointer.distance(pos);
    
    float finDist = 0;

    if ( dist < maxRadius ) {
        isOver = true;
        if(runOnce){ // over
            ofLog() << "over";
            runOnce = false;
            icolor.grow();
        }
        finDist = maxDist + 50 * sin(ofGetElapsedTimef() + randomOffset);
    }else{
        isOver = false;
        if(runOnce){ // out
            ofLog() << "out";
            runOnce = false;
            icolor.colapse();
        }
        finDist = 5 + 4 * sin(ofGetElapsedTimef() + randomOffset);
    }
    if(isOverPast != isOver){
        runOnce = true;
    }
    isOverPast = isOver;
    float brightness = ofMap(dist, 0, lightRadius, 255, 0);
    rectDistance = smooth*rectDistance + (1-smooth)*finDist;
    

    // set front block brightness
    ofClamp(brightness, 0, 255);

    // rectangle setup
    rectFront.setPosition(rectPos);
    rectBack.setPosition(pos);
    
    rectFront.setWidth(w);
    rectFront.setHeight(h);
    rectBack.setWidth(w);
    rectBack.setHeight(h);
    
    // setup points
    float rectFrontZ = rectDistance;

    faces[0].points[0] = ofVec3f(rectBack.getTopLeft().x, rectBack.getTopLeft().y, 0) ;
    faces[0].points[1] = ofVec3f(rectBack.getBottomLeft().x, rectBack.getBottomLeft().y, 0) ;
    faces[0].points[2] = ofVec3f(rectFront.getBottomLeft().x, rectFront.getBottomLeft().y, rectFrontZ) ;
    faces[0].points[3] = ofVec3f(rectFront.getTopLeft().x, rectFront.getTopLeft().y, rectFrontZ) ;
    
    faces[1].points[0] = ofVec3f(rectBack.getBottomLeft().x, rectBack.getBottomLeft().y, 0) ;
    faces[1].points[1] = ofVec3f(rectBack.getBottomRight().x, rectBack.getBottomRight().y, 0) ;
    faces[1].points[2] = ofVec3f(rectFront.getBottomRight().x, rectFront.getBottomRight().y, rectFrontZ) ;
    faces[1].points[3] = ofVec3f(rectFront.getBottomLeft().x, rectFront.getBottomLeft().y, rectFrontZ) ;
    
    faces[2].points[0] = ofVec3f(rectBack.getTopLeft().x, rectBack.getTopLeft().y, 0) ;
    faces[2].points[1] = ofVec3f(rectBack.getTopRight().x, rectBack.getTopRight().y, 0) ;
    faces[2].points[2] = ofVec3f(rectFront.getTopRight().x, rectFront.getTopRight().y, rectFrontZ) ;
    faces[2].points[3] = ofVec3f(rectFront.getTopLeft().x, rectFront.getTopLeft().y, rectFrontZ) ;
    
    faces[3].points[0] = ofVec3f(rectBack.getTopRight().x, rectBack.getTopRight().y, 0) ;
    faces[3].points[1] = ofVec3f(rectBack.getBottomRight().x, rectBack.getBottomRight().y, 0) ;
    faces[3].points[2] = ofVec3f(rectFront.getBottomRight().x, rectFront.getBottomRight().y, rectFrontZ) ;
    faces[3].points[3] = ofVec3f(rectFront.getTopRight().x, rectFront.getTopRight().y, rectFrontZ) ;

    faces[4].points[0] = ofVec3f(rectFront.getTopLeft().x, rectFront.getTopLeft().y, rectFrontZ) ;
    faces[4].points[1] = ofVec3f(rectFront.getTopRight().x, rectFront.getTopRight().y, rectFrontZ) ;
    faces[4].points[2] = ofVec3f(rectFront.getBottomRight().x, rectFront.getBottomRight().y, rectFrontZ) ;
    faces[4].points[3] = ofVec3f(rectFront.getBottomLeft().x, rectFront.getBottomLeft().y, rectFrontZ) ;
    
    faces[5].points[0] = ofVec3f(rectBack.getTopLeft().x, rectBack.getTopLeft().y, 0) ;
    faces[5].points[1] = ofVec3f(rectBack.getTopRight().x, rectBack.getTopRight().y, 0) ;
    faces[5].points[2] = ofVec3f(rectBack.getBottomRight().x, rectBack.getBottomRight().y, 0) ;
    faces[5].points[3] = ofVec3f(rectBack.getBottomLeft().x, rectBack.getBottomLeft().y, 0) ;
    
    // build polyline
    int i = 0;
    for(auto &face: faces){
        if(i < 4){
            face.lineT.clear();
            face.lineB.clear();
            face.lineT.lineTo(face.points[3]);
            face.lineT.lineTo(face.points[0]);
            face.lineB.lineTo(face.points[2]);
            face.lineB.lineTo(face.points[1]);
        }
        i++;
    }
    
    // update Colors
    icolor.update();
    
    // build mesh
    int curFaceNum = 0;
    for(auto &face: faces){
        face.mesh.clear();
        if (curFaceNum<4) { // build linked faces
            face.mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
            for (int i = 0; i<faceResolution; i++) {
                float percent = ofMap(i, 0, faceResolution-1, 0, 1);
                ofColor col = icolor.getColorAt(i);
                if(curFaceNum%3==0){
                    col.setBrightness(col.getBrightness()-70);
                }
                face.mesh.addVertex(face.lineT.getPointAtPercent(percent));
                face.mesh.addColor(col);
                face.mesh.addVertex(face.lineB.getPointAtPercent(percent));
                face.mesh.addColor(col);
            }
        }else{ // build main faces
            face.mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
            for (auto &point: face.points) {
                ofColor col = face.color;
                face.mesh.addVertex(point);
                face.mesh.addColor(icolor.getColorAt(0));
            }
        }
        curFaceNum++;
    }
}
void Block::draw(){
    int i = 0;
    ofSetColor(ofColor::white);
    for(auto &face: faces){
        face.mesh.draw();
        i++;
    }

}