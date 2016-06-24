//
//  wave.hpp
//  Wave
//
//  Created by Zerc on 6/21/16.
//
//

#ifndef wave_hpp
#define wave_hpp

#include "ofMain.h"
#include "ofxGui.h"
class Point_{
public:
    ofVec2f p;
    ofVec2f pp;
    bool isFixed;
};
class Spring{
public:
    
    float strength;
    float restLength;
    float mamb;
    float invMass;
    
    void setup(float _strength, float _restLength, float _invMass){
        
        restLength = restLength || 80;
        strength = _strength ? _strength : 0.55;
        invMass = _invMass;
        mamb = invMass * invMass;
    }
    void update(Point_ *prevPoint, Point_ *point){
        ofVec2f delta = ofVec2f(point->p.x, point->p.y) - ofVec2f(prevPoint->p.x, prevPoint->p.y) ;
        float dist = delta.length();
        float normDistStrength = (dist - restLength) / (dist * mamb) * strength;
        delta.y *= normDistStrength * invMass * 0.2;
        if(!prevPoint->isFixed){
            prevPoint->p.y += delta.y;
        }
        if(!point->isFixed){
            point->p.y -= delta.y;
        }
    }

};

class wave{
public:
    ofxPanel gui;
    ofImage tex;
    
    ofParameter<float> friction = 0.8;
    ofParameter<float> timeStep = 0.01;
    ofParameter<float> amount = 50;
    ofParameter<float> mass = 2;
    ofParameter<float> count = 0;
    ofParameter<float> step = 4;
    ofParameter<float> invMass = 1.0/mass;
    ofParameter<float> strength;
    ofParameter<float> restLength;
    ofParameter<float> p1;
    ofParameter<float> p2;
    ofParameter<float> p3;
    ofParameter<float> p4;
    int ypos;
    vector<Spring> springs;
    vector<Point_> points;
    ofFbo fbo;
    bool isTexture;
    ofFloatColor color;
    ofPolyline polyline;
    
    void setup(int _ypos, ofFloatColor _color){
        color = _color;
        ypos = _ypos;
        tex.load("texture.png");

        fbo.allocate(100, 100);
        fbo.begin();
        fbo.end();
        
        gui.setup("waveSettings");
        gui.add(amount.set("amount", 55, 10, 200));
        gui.add(strength.set("strength", 0.55, 0.001, 1));
        gui.add(restLength.set("restLength", 16.92, 1, 200));
        gui.add(invMass.set("invMass", 0.375, 0.1, 3));
        gui.add(step.set("step", 20, 1, 300));
  
//        restLength.addListener(this, &wave::reload);
//        strength.addListener(this, &wave::reload);
//        invMass.addListener(this, &wave::reload);
//        amount.addListener(this, &wave::reload);

//        gui.loadFromFile("settings.xml");
        setupSpring();
    }
    void reload(float &p){
        setupSpring();
    }
    void setupSpring(){
        points.clear();
        springs.clear();
        for (int i = 0; i < amount; i++) {
            Spring spring;
            spring.setup( strength, restLength, invMass);
            springs.push_back( spring );
            
            Point_ point;
            ofVec2f pos(i*step, ypos);
            point.p = pos;
            point.pp = pos;
            if(i < 1 || i > amount-2 ){
                point.isFixed = true;
            }else{
                point.isFixed = false;
            }
            points.push_back(point);
        }
    }
    void update(int x , int y){
        ofVec2f m(x, y);
        float force = 1 - friction * timeStep * timeStep;

        for (int i = 0; i < points.size(); i++) {
            if(m.distance(points[i].p)<20){
                if (!points[i].isFixed) {
                    points[i].p.y = m.y;
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
    void draw(){
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
            m.addColor(ofFloatColor(color, ofNoise(i/8.01)/2.));
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
};

#endif /* wave_hpp */
