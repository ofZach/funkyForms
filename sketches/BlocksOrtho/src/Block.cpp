
//
//  Block.cpp
//  BlocksOrtho
//
//  Created by Zerc on 7/7/16.
//
//

#include "Block.hpp"
void Block::setup(ofVec2f _pos, int _w, int _h){
    pos = _pos;
    w = _w;
    h = _h;
    direction = LEFT;
    for (int i = 0; i < 6; i++) {
        Face face;
        ofPolyline line;
        ofMesh m;
        face.line = line;
        face.mesh = m;
        face.color = colors[(int)ofRandom(10)];
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
            rectPos = pos+rectDistance;
            distPos = pos+maxDist;
            break;
        case TOPRIGHT:
            rectPos = pos+ofVec2f(-rectDistance, rectDistance);
            distPos = pos+ofVec2f(-maxDist, maxDist);
            break;
        default:
            rectPos = pos-rectDistance;
            distPos = pos-maxDist;
            break;
    };
//    if(isLeft){
//        rectPos = pos-rectDistance;
//        distPos = pos-maxDist;
//    }else{
//        rectPos = (pos+ofVec2f(rectDistance, -rectDistance));
//        distPos = (pos+ofVec2f(maxDist, -maxDist));
//    }
    float dist = pointer.distance(pos);
    
    float finDist = 0;
    if ( dist > maxRadius ) {
        finDist = maxDist;
    }else{
        finDist = -0.02;
    }
    float brightness = ofMap(dist, 0, lightRadius, 255, 0);
    rectDistance = smooth*rectDistance + (1-smooth)*finDist;
    
    // rectangle setup

    // set front block brightness
    ofClamp(brightness, 0, 255);

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
    
    // build mesh
    int i = 0;
    for(auto &face: faces){
        face.mesh.clear();
        face.mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        int j = 0;
        for (auto &point: face.points) {
            ofColor col = face.color;
            if(j<2){ //
                col.setBrightness(120);
            }else{
                col.setBrightness(255);
            }
            if(i==4){
                col = face.color;
            }
            if(i==5){ // front and back face
                col = ofColor::black;
//                if(j>1){
//                    col.setBrightness(200);
//                }
            }
            face.mesh.addVertex(point);
            face.mesh.addColor(col);
            j++;
        }
        i++;
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