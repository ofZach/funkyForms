//
//  PlantManager.hpp
//  PlantSpring
//
//  Created by Zerc on 8/5/16.
//
//

#ifndef PlantManager_hpp
#define PlantManager_hpp

#include "ofMain.h"
#include "Plant.hpp"
#include "cvManager.h"
#include "ofxGui.h"
#include "renderManager.h"


class PlantManager{
public:
    // plants
    vector<Plant> plants;
    ofParameter<float> plantScale;
    vector<Plant> bgPlants;
    int pointLinkCount = 4;
    
    // input manager
    cvPacket * cvData;
    vector<ofPolyline> peopleResampled;
    vector<ofVec2f> peoplePoints;
    
    // gui
    ofParameterGroup parameters;

    ofParameter<float> mainBranchWMax;
    ofParameter<float> mainBranchWMin;
    ofParameter<float> childBranchWMin;
    ofParameter<float> childBranchWMax;
    ofParameter<float> bgMainBranchWMax;
    ofParameter<float> bgMainBranchWMin;
    ofParameter<float> bgChildBranchWMin;
    ofParameter<float> bgChildBranchWMax;
    ofParameter<bool> createBgPlant;
    
    // colors
    ofFloatColor swatch[4] = {
        ofFloatColor(0.367864,0.692656,0.469682),
        ofFloatColor(0.938711,0.923981,0.347339),
        ofFloatColor(0.732369,0.920703,0.257683),
        ofFloatColor(0.872385,0.169879,0.152076)
    };
    
    // random
    vector<int> randSwatchIndex;
    
    // shadow
    ofImage shadow;
    ofParameter<float> shadowRadius;
    ofParameter<float> shadowOpacity;
    
    void setup();
    void setupGui();
    void addPlant(ofVec2f _pos, int id);
    void addBgPlant(ofVec2f _pos);
    void onNewPlant();
    void remove(int id);
    void reset();
    void triggerBgPlant(bool &b);
    
    void update();
    void updatePlants();
    void updateBgPlants();
    void updateBgPlantsCreation();
    void updateBgPlantsRemoval();
    void updatePlantCreation();
    void updatePlantsParameters();
    void updatePlantRemoval();

    
    inline ofPoint mapPt(ofRectangle src, ofRectangle dst, ofPoint input){
        float newx = ofMap(input.x, src.x, src.x + src.getWidth(), dst.x, dst.x + dst.getWidth());
        float newy = ofMap(input.y, src.y, src.y + src.getHeight(), dst.y, dst.y + dst.getHeight());
        return ofPoint(newx, newy);
    }

    
    ofVec2f getClosestPoint(ofVec2f target, vector<ofVec2f> &points);
    
    void draw();
    void drawPlants();
    void drawBgPlants();
    void drawShadow();
    
    renderManager * RM;
    
};

#endif /* PlantManager_hpp */
