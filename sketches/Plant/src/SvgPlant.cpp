//
//  SvgPlant.cpp
//  Plant
//
//  Created by Zerc on 6/28/16.
//
//

#include "SvgPlant.hpp"
void SvgPlant::setup(string file, int l_size, int r_size){
    leftRectH = l_size;
    topRectW = r_size;
    svg.load(file);
    w = svg.getWidth();
    h = svg.getHeight();
    for (int i = 0; i < svg.getNumPath(); i++){
        ofPath p = svg.getPathAt(i);
        // svg defaults to non zero winding which doesn't look so good as contours
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        vector<ofPolyline>& lines = const_cast<vector<ofPolyline>&>(p.getOutline());
        for(int j=0; j<(int)lines.size();j++){
            ofLog() << lines.size() ;
            outlines.push_back(lines[j].getResampledBySpacing(1));
        }
    }
    tess.tessellateToMesh(outlines, OF_POLY_WINDING_ODD, mesh);
    
}
void SvgPlant::update(){
    
}
void SvgPlant::draw(float x, float y){
    float sine = (cos(ofGetFrameNum()/10.)*0.5+0.5);
    leftRectW = sine*100;
    topRectH = sine*100;
    
    rectLeft.set(x, h - leftRectH+y+topRectH, leftRectW, leftRectH);
    rectTop.set(w - topRectW +leftRectW+x, y, topRectW, topRectH);

    ofDrawRectangle(rectLeft);
    ofDrawRectangle(rectTop);
    
    ofPushMatrix();
    ofTranslate(leftRectW+x, topRectH+y);
    mesh.draw();
    ofPopMatrix();
}