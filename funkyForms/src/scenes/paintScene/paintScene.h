
#pragma once

#include "ofMain.h"
#include "baseScene.h"
#include "particle.h"
#include "trackedContour.hpp"
#include "spring3f.h"
#include "particle3f.h"


typedef struct {
    string name;
    ofColor color;
} colorNameMapping;


class paintScene : public baseScene {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void start();
    void stop();
    
    void blobBorn(int packetId, int id);
    void blobDied(int packetId, int id);
    
    
    ofFbo       lineFbo;
    ofFbo       lineFbo2;
    ofImage     rockImage;
    ofPolyline  line;
    ofShader    shader;
    ofImage     noiseImage;
    
    ofImage     opticalFlowImage;
    
    
    
    
    
    
    map < string, ofColor > colorNameMap;
    
    vector < colorNameMapping > colorNames;
    
    ofImage simplexImage;
    ofImage simplexImage2;
    
    ofImage colorPalette[3];
    
    
    
    vector < ofVboMesh > meshes;
    vector < ofColor > colors;
    
    //paint/stone_rocky_surface_texture.jpg
};


