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
    
//    map <string, vector<jointSettings> > 
    struct jointSettings{
        int jointId;
        shapeType type;
        int width;
        int height;
    };

    void setup(){
        skeleton.addLimb(ofVec2f(0, 0), 180, 2, 80, "torso", &skeleton.root); // torso 0
        ofNode *torso = skeleton.getLimb("torso")->getNodeAt(1);
        skeleton.getLimb("torso")->setPivot(0, ofVec2f(0, -10));
        skeleton.addLimb(ofVec2f(-60, 0), 120, 4, 120, "l_hand", torso);
        skeleton.getLimb("l_hand")->setPos(3, ofVec2f(0, 30));
        skeleton.addLimb(ofVec2f(60, 0), -120, 4, 120, "r_hand", torso);
        skeleton.getLimb("r_hand")->setPos(3, ofVec2f(0, 30));
        skeleton.addLimb(ofVec2f(-40, 0), 0, 3, 150, "l_leg", &skeleton.root);
        skeleton.addLimb(ofVec2f(40, 0), 0, 3, 150, "r_leg", &skeleton.root);
        skeleton.addLimb(ofVec2f(0, 20), 0, 3, 80, "head", torso);
        skeleton.addLimb(ofVec2f(-20, -40), 0, 2, 30, "l_eye", skeleton.getLimb("head")->getNodeAt(1));
        skeleton.addLimb(ofVec2f(20, -40), 0, 2, 30, "r_eye", skeleton.getLimb("head")->getNodeAt(1));
        skeleton.addLimb(ofVec2f(0, 20), 90, 2, 80, "mouth", skeleton.getLimb("head")->getNodeAt(0));

        attachShapes();
    }
    void attachShapes(){
        shapes.clear();
        for (auto &pair: *skeleton.getLimbs()) {
            limb *limb = &pair.second;
            string name = pair.first;
            for (int j = 0; j < limb->getChainCount()-1; j++) {
                int width = 50;
                int height = 0;
                ofColor col = colors[(int)ofRandom(4)];
                if(name == "torso"){
                    width = 300;
                    height = 20;
                }else if(name == "head" && j==0){
                    width = 300;
                }else if(name == "l_eye" || name == "r_eye" ){
                    width = 20;
                    col = ofColor::black;
                }
                shapeType type = static_cast<shapeType>(rand() % shape_last);
                ShapeBase* shape = ShapeFactory(type);
                shape->setup(width, height, limb, j);
                shape->setColor(col);
                shapes[name+ofToString(j)] = shape;
            }
        }
    }
    void update(){
        for(auto &pair: shapes){
            pair.second->update();
        }
    }
    void draw(float velocity){
//        ofLog() << "______";
        for(auto &pair: shapes){
//            ofLog() << pair.first;
            pair.second->draw();
        }
        skeleton.draw(velocity);
    }
};
#endif /* Character_hpp */
