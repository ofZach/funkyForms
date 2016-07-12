
//
//  Block.cpp
//  BlocksOrtho
//
//  Created by Zerc on 7/7/16.
//
//

#include "Block.hpp"
void Block::setup(ofVec2f _pos, int _w, int _h){
    icolor.setup(1, colors[(int)ofRandom(9)]);
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
    for (int i = 0; i < 5; i++) {
        Box box;
        for (int i = 0; i < 6; i++) {
            ofMesh m;
            m.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
            box.meshes[i] = m;
        }
        boxes.push_back(box);
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
            runOnce = false;
            icolor.grow();
        }
        finDist = maxDist; // + 50 * sin(ofGetElapsedTimef() + randomOffset);
    }else{
        isOver = false;
        if(runOnce){ // out
            runOnce = false;
            icolor.colapse();
        }
        finDist = 0;// 5 + 4 * sin(ofGetElapsedTimef() + randomOffset);
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
            face.lineT.lineTo(face.points[0]);
            face.lineT.lineTo(face.points[3]);
            face.lineB.lineTo(face.points[1]);
            face.lineB.lineTo(face.points[2]);
        }
        i++;
    }
    
    // update Colors
    icolor.update();
    
    // build mesh
    for (int i = 0; i < icolor.getColorCount(); i++) { // i - box count
        boxes[i].color = icolor.getColor(i)->color;
        ofPoint p(i, i, 1);
        boxes[i].pos = p+randomOffset*cos(ofGetFrameNum()/20.0+i*10);
        for (int j = 0; j < 6; j++) {
            boxes[i].meshes[j].clear();
            ofColor col = icolor.getColor(i)->color;
            if(j<4){ // linked faces
                if(j%3==0){
                    col.setBrightness(col.getBrightness()-50);
                }else{
                    col.setBrightness(col.getBrightness()-10);
                }
                if(icolor.getColor(i)->rect.getWidth()>0){
                    boxes[i].meshes[j].addVertex(faces[j].lineT.getPointAtPercent(icolor.getColor(i)->start+0.01));
                    boxes[i].meshes[j].addColor(col);
                    boxes[i].meshes[j].addVertex(faces[j].lineB.getPointAtPercent(icolor.getColor(i)->start+0.01));
                    boxes[i].meshes[j].addColor(col);
                    boxes[i].meshes[j].addVertex(faces[j].lineT.getPointAtPercent(icolor.getColor(i)->end));
                    boxes[i].meshes[j].addColor(col);
                    boxes[i].meshes[j].addVertex(faces[j].lineB.getPointAtPercent(icolor.getColor(i)->end));
                    boxes[i].meshes[j].addColor(col);
                }
            }else{ // caps
                if(icolor.getColor(i)->rect.getWidth()>0){
                    boxes[i].meshes[j].addVertex(faces[0].lineT.getPointAtPercent(icolor.getColor(i)->start+0.01));
                    boxes[i].meshes[j].addColor(col);
                    boxes[i].meshes[j].addVertex(faces[0].lineB.getPointAtPercent(icolor.getColor(i)->start+0.01));
                    boxes[i].meshes[j].addColor(col);
                    boxes[i].meshes[j].addVertex(faces[3].lineT.getPointAtPercent(icolor.getColor(i)->end));
                    boxes[i].meshes[j].addColor(col);
                    boxes[i].meshes[j].addVertex(faces[3].lineB.getPointAtPercent(icolor.getColor(i)->end));
                    boxes[i].meshes[j].addColor(col);
                }
            }
        }
    }
}
void Block::draw(){
    int i = 0;
    int j = 0;
    ofSetColor(ofColor::white);
    for(auto &box: boxes){
//        ofSetColor(box.color);
        ofPushMatrix();
        ofTranslate(box.pos);
//        if(isCrazy){
//            if(isOver){
//            }
//        }
        for (auto &mesh: box.meshes){
            mesh.draw();
            j++;
        }
        ofPopMatrix();
        i++;
    }

}