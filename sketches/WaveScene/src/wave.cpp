//
//  wave.cpp
//  Wave
//
//  Created by Zerc on 6/21/16.
//
//

#include "wave.hpp"
void wave::setup(int _ypos, ofFloatColor _color, int _width){
    width = _width;
    color = _color;
    ypos = _ypos;
    tex.load("texture.png");
    
    fbo.allocate(100, 100);
    fbo.begin();
    fbo.end();
//
//            restLength.addListener(this, &wave::reload);
//            strength.addListener(this, &wave::reload);
//            invMass.addListener(this, &wave::reload);
//            amount.addListener(this, &wave::reload);
//    
//            gui.loadFromFile("settings.xml");
    setupSpring();
}
void wave::setupSpring(){
    points.clear();
    springs.clear();
    for (int i = 0; i < amount; i++) {
        Spring spring;
        spring.setup( strength, restLength, invMass);
        springs.push_back( spring );
        
        Point_ point;
        
        float step = width/(amount*1.0-1.0);
        
        ofVec2f pos(i*step , ypos);
        
        point.p = pos;
        point.pp = pos;
        if(i == 0 || i == amount-1 ){
            point.isFixed = true;
        }else{
            point.isFixed = false;
        }
        points.push_back(point);
    }
}
void wave::update(vector<inputManager::Target> &targets){
    
    float force = 1 - friction * timeStep * timeStep;
    
    for (int i = 0; i < points.size(); i++) {
        
        for(auto &t: targets ){
//            ofVec2f pos = ofVec2f(t.pos.x + t.vel.normalize().x*100, t.pos.y);
            if(t.pos.distance(points[i].p)<30){
                if (!points[i].isFixed) {
                    points[i].p.y += t.vel.normalize().y*20;
                }
            }
        }
        float dy = (points[i].p.y - points[i].pp.y) * force;
        points[i].pp = points[i].p;
        points[i].p.y = MAX(points[i].p.y + dy, 0);
    }
    for (int i = 0; i < springs.size(); i++) {
        if(i>0){
            springs[i].update(&points[i-1], &points[i]);
        }
    }
}
void wave::draw(){
    ofMesh m;
    m.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    int stepLength = 4;
    float texPixWidth = tex.getWidth()/points.size();
    int stepCounter = 0;
    
    polyline.clear();
    
    for (int i = 0; i < points.size(); i++) {
        ofVec2f p2 (points[i].p.x, ofGetHeight());
        
        ofVec2f leftTop;
        leftTop.x = i*texPixWidth;
        leftTop.y = 0;
        
        ofVec2f leftBottom;
        leftBottom.x = i*texPixWidth;
        leftBottom.y = tex.getHeight();
        
        polyline.addVertex(points[i].p);
        
        m.addVertex(points[i].p);
        m.addColor(ofFloatColor(color, 1));
        m.addTexCoord(leftTop);
        m.addVertex(p2);
        m.addColor(ofFloatColor(color, 1));
        m.addTexCoord(leftBottom);
        
        stepCounter++;
        
    }
    if(isTexture) tex.bind();
    m.draw();
    if(isTexture) tex.unbind();
    //        tex.draw(0, 0);
}