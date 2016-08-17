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
#include "baseScene.h"

class plantsScene : public baseScene {
public:
    // plants
    vector<Plant> plants;
    ofParameter<float> plantScale;
    ofParameter<float> mainBranchStrokeWidth;
    ofParameter<float> childBranchStrokeWidth;
    vector<Plant> bgPlants;
    int pointLinkCount = 4;
    
    // input manager
    vector<ofPolyline> peopleResampled;
    vector<ofVec2f> peoplePoints;
    
    // people
    ofImage glow;
    ofParameter<float> glowRadius;
    ofParameter<float> glowOpacity;
    
    // gui
    ofParameterGroup parameters;
    ofxPanel gui;
    
    // branchcount
    ofParameter<int> mainBranchCountMin;
    ofParameter<int> mainBranchCountMax;
    ofParameter<int> childBranchCountMin;
    ofParameter<int> childBranchCountMax;
    ofParameter<int> bgMainBranchCountMin;
    ofParameter<int> bgMainBranchCountMax;
    ofParameter<int> bgChildBranchCountMin;
    ofParameter<int> bgChildBranchCountMax;

    ofParameter<float> mainBranchWidth;
    ofParameter<float> branchLengthVariation;
    ofParameter<float> mainBranchHeight;
    ofParameter<float> childBranchWidth;
    ofParameter<float> childBranchHeight;
    ofParameter<float> bgmainBranchWidth;
    ofParameter<float> bgmainBranchHeight;
    ofParameter<float> bgchildBranchWidth;
    ofParameter<float> bgchildBranchHeight;
    ofParameter<float> bgmainBranchStrokeWidth;
    ofParameter<float> bgchildBranchStrokeWidth;
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
    
    // background
    ofImage skyImage;
    ofImage hillsImage;
    ofParameterGroup bgParameters;
    ofVec2f bgCenterPos;
    ofMesh bgCircle;
    vector<ofPath> clouds;
    ofParameter<float> bgChangeSpeed;
    ofParameter<ofColor> dayColorBottom;
    ofParameter<ofColor> dayColorTop;
    ofParameter<ofColor> nightColorTop;
    ofParameter<ofColor> nightColorBottom;
    
    void setup();
    void setupBackground();
    void setupGui();
    void addPlant(ofVec2f _pos, int id, bool bLeftSide);
    void addBgPlant(ofVec2f _pos);
    void addBgPlantRandom();
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

    void blobBorn(int id);
    void blobDied(int id);
    
    void start();
    void stop();
    
    inline ofPoint mapPt(ofRectangle src, ofRectangle dst, ofPoint input){
        float newx = ofMap(input.x, src.x, src.x + src.getWidth(), dst.x, dst.x + dst.getWidth());
        float newy = ofMap(input.y, src.y, src.y + src.getHeight(), dst.y, dst.y + dst.getHeight());
        return ofPoint(newx, newy);
    }
    
    ofVec2f getClosestPoint(ofVec2f target, vector<ofVec2f> &points);
    
    void draw();
    void drawHills();
    void drawBackground();
    void drawPlants();
    void drawPeople();
    void drawBgPlants();
    void drawShadow();
    void drawGui();
};

#endif /* PlantManager_hpp */
