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
void SvgPlant::drawDebug(){
    ofSetColor(color);
    ofDrawRectangle(rect1);
    ofSetColor(ofColor::lightCyan);
    ofDrawRectangle(rect2);
    ofSetColor(ofColor::lightSteelBlue);
    ofDrawRectangle(rect3);
    ofSetColor(ofColor::lightCyan);
    ofDrawRectangle(rect4);
    ofSetColor(ofColor::lightYellow);
    ofDrawRectangle(rect5);
}
void SvgPlant::draw(){
    ofSetColor(color);
    ofDrawRectangle(rect1);
    ofDrawRectangle(rect5);
    ofPath path;
    path.setColor(color);
    if(isLeft){
        path.lineTo(rect2.getBottomRight());
        path.bezierTo(rect2.getBottomRight(), rect3.getBottomLeft() , rect4.getTopLeft() );
        path.lineTo(rect4.getTopRight());
        path.bezierTo(rect4.getTopRight(), rect4.getBottomRight(), rect2.getTopRight());
    }else{
        path.lineTo(rect2.getBottomLeft());
        path.bezierTo(rect2.getBottomLeft(), rect3.getBottomRight() , rect4.getTopRight() );
        path.lineTo(rect4.getTopLeft());
        path.bezierTo(rect4.getTopLeft(), rect4.getBottomLeft(), rect2.getTopLeft());
        
    }
    path.draw();
    if(isCap){
        ofDrawCircle(rect5.getCenter().x, rect5.getTop(), rect5.getWidth()/2);
    }
}
void SvgPlant::update( ofVec2f pos, ofVec2f leftRectSize, ofVec2f topRectSize, float radius){
    float topRectWidth = topRectSize.x;
    float topRectHeight = topRectSize.y;
    float leftRectWidth = leftRectSize.x;
    float leftRectHeight = leftRectSize.y;

    if(isLeft){
        rect1.set(0, 0, leftRectWidth, leftRectHeight);
        rect1.alignTo(pos, OF_ALIGN_HORZ_RIGHT, OF_ALIGN_VERT_TOP);
        
        rect2.set(0, 0, radius, rect1.getHeight());
        rect2.alignTo(rect1.getTopLeft(), OF_ALIGN_HORZ_RIGHT, OF_ALIGN_VERT_TOP);
        
        rect3.set(0, 0, topRectWidth, rect1.getHeight());
        rect3.alignTo(rect2.getTopLeft(), OF_ALIGN_HORZ_RIGHT, OF_ALIGN_VERT_TOP);
        
        rect4.set(0, 0, topRectWidth, radius);
        rect4.alignTo(rect3.getTopLeft(), OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_BOTTOM);
        
        rect5.set(0, 0, topRectWidth, topRectHeight);
        rect5.alignTo(rect4.getTopLeft(), OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_BOTTOM);
    }else{
        rect1.set(0, 0, leftRectWidth, leftRectHeight);
        rect1.alignTo(pos, OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_TOP);
        
        rect2.set(rect1.getTopRight(), radius, rect1.getHeight());
        
        rect3.set(rect2.getTopRight(), topRectWidth, rect1.getHeight());
        
        rect4.set(0, 0, topRectWidth, radius);
        rect4.alignTo(rect3.getTopLeft(), OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_BOTTOM);
        
        rect5.set(0, 0, topRectWidth, topRectHeight);
        rect5.alignTo(rect4.getTopLeft(), OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_BOTTOM);
    }
}