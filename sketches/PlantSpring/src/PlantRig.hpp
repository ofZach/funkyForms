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
    // pos, vel
    ofVec2f pos;
    
    // polylines
    ofPolyline mainBranchLine;
    vector<ofPolyline> childBranchLines;

    // points
    vector<ofVec2f> mainBranchPoints;
    vector<ofVec2f> mainBranchInitPoints;
    
    vector<vector<ofVec2f>> childBranchesPoints;
    vector<vector<ofVec2f>> childBranchesInitPoints;
    
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
    
    // mainbranch
    float mbLengthMin;
    float mbLengthMax;
    int mbCount;
    
    // childbranch
    float cbLengthMin;
    float cbLengthMax;
    int cbCount;
    
    void setup();
    void setupRandom();
    void makeMainBranch();
    void makeChildBranches();
    
    void update();
    void updateMainBranch();
    void updateChildBranches();
    void updateMBPolyline();
    void updateCBPolyline();
    void makeBranch(BranchSettings s);
    
    void draw();
    void drawChildBranches();
    void drawMainBranch();
};

#endif /* PlantRig_hpp */
