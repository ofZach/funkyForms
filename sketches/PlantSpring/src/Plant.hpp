//
//  Plant.hpp
//  PlantSpring
//
//  Created by Zerc on 8/1/16.
//
//

#ifndef Plant_hpp
#define Plant_hpp

#include "ofMain.h"
#include "PlantRig.hpp"

class Plant{
public:
    // rig
    PlantRig rig;
    
    // Polylines
    ofPolyline mbLine, mbLine1, mbLine2;
    vector<ofPolyline> childLines1;
    vector<ofPolyline> childLines2;
    
    // meshes
    ofMesh mbMesh;
    vector<ofMesh> childMeshes;
    
    void setup();
    void setupChildBranches();
    
    void update();
    void updatePolylines();
    void updateMesh();
    void makeCorner(ofPolyline *line, ofPolyline &l, int i, float angle, float lenght);
    
    void draw();
    void drawPolylines();
};

#endif /* Plant_hpp */
