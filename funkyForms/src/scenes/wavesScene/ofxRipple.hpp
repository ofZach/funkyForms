//
//  ofxRipple.hpp
//  WaveScene
//
//  Created by Zerc on 7/27/16.
//
//

#ifndef ofxRipple_hpp
#define ofxRipple_hpp

#include <stdio.h>
//
//  ofxRipples.h
//  example-waterRipples
//
//  original by Patricio Gonzalez Vivo on 11/24/12.
//
//

#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxFXObject.h"

class ofxRipple : public ofxFXObject {
public:
    ofParameter<float> damping;
    ofParameter<float> s1;
    ofParameterGroup parameters;
    
    ofxRipple(){
        passes = 1;
        internalFormat = GL_RGB ;
        
        damping = 0.995;
        
        fragmentShader = STRINGIFY(uniform sampler2DRect backbuffer;   // previus buffer
                                   uniform sampler2DRect tex0;         // actual buffer
                                   
                                   uniform float damping;
                                   uniform float s1;
                                   
                                   void main(){
                                       vec2 st = gl_TexCoord[0].st;
                                       
                                       //  Grab the information arround the active pixel
                                       //
                                       //      [3]
                                       //
                                       //  [0]  st  [1]
                                       //
                                       //      [2]
                                       
                                       vec3 sum = vec3(0.0, 0.0, 0.0);
                                       
                                       sum += texture2DRect(tex0, st + vec2(-1.0, 0.0)*(s1*6.+1.) ).rgb;
                                       sum += texture2DRect(tex0, st + vec2(1.0, 0.0)*(s1*6.+1.) ).rgb;
                                       sum += texture2DRect(tex0, st + vec2(0.0, 1.0)*(s1*6.+1.) ).rgb;
                                       sum += texture2DRect(tex0, st + vec2(0.0, -1.0)*(s1*6.+1.) ).rgb;
                                       
                                       //  make an average and substract the center value
                                       //
                                       sum = (sum / 2.) - texture2DRect(backbuffer, st).rgb;
                                       sum *= damping;
                                       
                                       gl_FragColor = vec4(sum, 1.0);
                                   } );
    }
    void setupParameters(){
        parameters.setName("Ripples");
        parameters.add(damping.set("damping", 1., 0.8, 0.999999));
        parameters.add(s1.set("pixelOffset", 1., 0., 1.));
    }
    void begin() {
        ofPushStyle();
        ofPushMatrix();
        pingPong.src->begin();
    }
    
    void end() {
        pingPong.src->end();
        ofPopMatrix();
        ofPopStyle();
    }
    
    void update(){
        // Calculate the difference between buffers and spread the waving
        textures[0].begin();
        shader.begin();
        shader.setUniformTexture("backbuffer", pingPong.dst->getTextureReference(), 0);
        shader.setUniformTexture("tex0", pingPong.src->getTextureReference(), 1);
        shader.setUniform1f("damping", (float)damping );
        shader.setUniform1f("s1", s1 );
        renderFrame();
        shader.end();
        textures[0].end();
        
        // TODO: improve this, it's almost non-sense
        pingPong.dst->begin();
        textures[0].draw(0, 0);
        pingPong.dst->end();
        
        pingPong.swap();
    }
    
};

#endif /* ofxRipple_hpp */
