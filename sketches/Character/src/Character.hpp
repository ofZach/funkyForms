//
//  Character.hpp
//  Character
//
//  Created by Zerc on 6/24/16.
//
//

#ifndef Character_hpp
#define Character_hpp

#include "ofMain.h"
#include "Skeleton.hpp"
#include "Shape.hpp"
#include "ofxGui.h"

class Character{
public:
    map<string, ShapeBase *> shapes;
    
    Skeleton skeleton;
    
    ofFloatColor colors[4] = {
        ofColor::lightGreen,
        ofColor::red,
        ofColor::mistyRose,
        ofColor::yellow
    };
    
    struct jointSettings{
        int id;
        shapeType type;
        int width;
        int height;
        ofColor color;
        ofVec2f pivot;
    };
    string legName =    "1leg";
    string handName =   "2hand";
    string torsoName =  "3torso";
    string headName =   "4head";
    string eyeName =    "5eye";
    string mouthName =  "6mouth";

    map <string, vector<jointSettings>> limbSettings;

    void setup(){
        skeleton.addLimb(ofVec2f(0, 0), 180, 2, 80, torsoName, &skeleton.root); // torso 0
        ofNode *torso = skeleton.getLimb(torsoName)->getNodeAt(1);
        skeleton.getLimb(torsoName)->setPivot(0, ofVec2f(0, -10));
        skeleton.addLimb(ofVec2f(-60, 0), 120, 4, 120, handName+"_l", torso);
        skeleton.getLimb(handName+"_l")->setPos(3, ofVec2f(0, 30));
        skeleton.addLimb(ofVec2f(60, 0), -120, 4, 120, handName+"_r", torso);
        skeleton.getLimb(handName+"_r")->setPos(3, ofVec2f(0, 30));
        skeleton.addLimb(ofVec2f(-40, 0), 0, 3, 150, legName+"_l", &skeleton.root);
        skeleton.addLimb(ofVec2f(40, 0), 0, 3, 150, legName+"_r", &skeleton.root);
        skeleton.addLimb(ofVec2f(0, 20), 0, 3, 80, headName, torso);
        skeleton.addLimb(ofVec2f(0, 20), 90, 2, 80, mouthName, skeleton.getLimb(headName)->getNodeAt(0));
        skeleton.addLimb(ofVec2f(-20, -40), 0, 2, 30, eyeName+"_l", skeleton.getLimb(headName)->getNodeAt(1));
        skeleton.addLimb(ofVec2f(20, -40), 0, 2, 30, eyeName+"_r", skeleton.getLimb(headName)->getNodeAt(1));

        attachShapes();
    }
    void attachShapes(){
        shapes.clear();
        limbSettings.clear();
        for (auto &pair: *skeleton.getLimbs()) {
            limb *limb = pair.second;
            string name = pair.first;
            string partName = name.substr(0, name.find("_", 0)); // get full name: `eye_l` to `eye`
            
            bool isSamePart = false;
            if(limbSettings.find(partName) == limbSettings.end()){
                // partName not found: create settings
                vector<jointSettings> settings;
                limbSettings[partName] = settings;
            }else{
                // partName found: apply settings to left/right body part
                isSamePart = true;
            }
            for (int j = 0; j < limb->getChainCount(); j++) {
                if(j != limb->getChainCount()-1){
                    // default settings
                    jointSettings s;
                    s.id = j;
                    s.width = ofRandom(20, 50);
                    s.height =  ofRandom(20, 50);
                    s.type = static_cast<shapeType>(rand() % shape_last);
                    s.color = (colors[(int)ofRandom(4)]);
                    s.pivot = ofVec2f(0, ofRandom(-30, 20));
                    if(partName == torsoName){
                        s.width = ofRandom(100, 300);
                        s.type = shape_rectangle;
                        if(j == 0){ // first joint
                            limb->setPos(j, ofVec2f(0, ofRandom(10, 30)));
                        }else{
                            limb->setPos(j, ofVec2f(0, ofRandom(-100, -300)));
                        }
                        s.height = 20;
                    }else if(partName == headName){
                        if(j==0)
                            s = limbSettings[torsoName][0];
//                            s.width = ofRandom(100, 300);
                    }else if(partName == eyeName){
                        s.width = 20;
                        s.color = ofColor::black;
                    }else if(partName == handName ){
                        if(j==0){ // root node
                            if(name == handName+"_l"){
//                                limb->setPos(0, ofVec2f(-limbSettings[torsoName][0].width/2, 0));
                            }
                            if(name == handName+"_r"){
//                                limb->setPos(0, ofVec2f(limbSettings[torsoName][0].width/2, 0));
                            }
                        }
                        
                        if(j==limb->getChainCount()-2){
                            s.type = shape_claw;
                            s.color = ofColor::white;
                        }
//                        s.width = 20;
                    }
                    
                    if(isSamePart){
                        // get settings
                        s = limbSettings[partName][j];
                    }else{
                        // add settings
                        limbSettings[partName].push_back(s);
                    }
                    limb->setPivot(j, s.pivot);
                    limb->update();
                    // set settings to shape
                    ShapeBase* shape = ShapeFactory(s.type);
                    shape->setup(s.width, s.height, limb, j);
                    shape->setColor(s.color);
                    shapes[name+ofToString(j)] = shape;
                }else { // change last joint pos
                    if(partName == torsoName){
                        limb->setPos(j, ofVec2f(0, ofRandom(100, 300)));
                    }else if(partName == headName){

                    }else if(partName == eyeName){
                        
                    }
                }
            }
        }
    }
    void update(){
        for(auto &pair: shapes){
            pair.second->update();
            if(pair.first == "torso0"){
//                ofLog() << pair.second->rect.getHeight();
            }
        }
    }
    void draw(float velocity){
        for(auto &pair: shapes){
            pair.second->draw();
        }
        skeleton.draw(velocity);
    }
};
#endif /* Character_hpp */
