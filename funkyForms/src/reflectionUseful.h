#pragma once

typedef struct {
    
    //-------------------------------------
    BVH * bvh;
    ofMesh meshes[16];
    vector < ofPoint > pos[16];
    vector < ofPoint > dir[16];
    int nLightRays;
    
} reflectionPacket;
