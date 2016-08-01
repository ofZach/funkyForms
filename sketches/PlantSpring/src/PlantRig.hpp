//
//  PlantRig.hpp
//  PlantSpring
//
//  Created by Zerc on 8/1/16.
//
//

#ifndef PlantRig_hpp
#define PlantRig_hpp

#include "ofMain.h"
class PlantRig{
public:
    // polylines
    ofPolyline mainBranchLine;
    vector<ofPolyline> childBranchLines;

    // points
    vector<ofVec2f> mainBranchPoints;
    vector<vector<ofVec2f>> childBranchesPoints;
    
    // randoms
    vector<int> randomBools;
    vector<float> randomFloats;
    
    // settings
    struct BranchSettings{
        vector<ofVec2f> *points;
        ofVec2f pos;
        ofVec2f dir;
        float lengthMin;
        float lengthMax;
        int branchCount;
    };
    
    void setup();
    void setupRandom();
    
    void update();
    void updateMainBranch();
    void updateChildBranches();
    void updatePolylines();
    void makeBranch(BranchSettings s);
    
    void draw();
};

#endif /* PlantRig_hpp */
