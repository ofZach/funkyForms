//
//  Plant.cpp
//  Plant
//
//  Created by Zerc on 6/28/16.
//
//

#include "Plant.hpp"
void Plant::setup(){
    for (int i = 0; i < 10; i++) {
        SvgPlant svgplant;
        svgplant.setup("shape.svg", 74.769, 42.134);
        svgplants.push_back(svgplant);
    }
}
void Plant::update(){
    for(auto svgplant: svgplants){
        svgplant.update();
    }
}
void Plant::draw(){
    int i = 0;
    ofPushMatrix();
    ofTranslate(100, 500);
    for (int i = 0; i < svgplants.size(); i++) {
        if(i>0){
            svgplants[i].draw(0, 200*i);
        }else{
            svgplants[i].draw(0, 0);
        }
    }
    ofPopMatrix();
}