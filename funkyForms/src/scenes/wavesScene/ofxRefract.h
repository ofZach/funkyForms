//
//  ofxRefract.h
//  Ripples
//
//  Created by Zerc on 9/5/15.
//
//

#pragma once
#define STRINGIFY(A) #A
#include "ofMain.h"
#include "ofxFXObject.h"

class ofxRefract : public ofxFXObject {
public:
    ofxRefract(){
        passes = 1;
        internalFormat = GL_RGBA;
        
        fragmentShader = STRINGIFY(uniform sampler2DRect tex0; // input
                                   uniform sampler2DRect tex1; // image to be warped
                                   uniform vec2 size;
                                   uniform float s1;
                                   uniform float s2;
                                   uniform float s3;
                                   uniform float s4;
                                   uniform float time;
                                   uniform float noiseOffset;
                                   uniform float noiseAmountX;
                                   uniform float noiseAmountY;
                                   uniform float noisePeriodX;
                                   uniform float noisePeriodY;
                                   uniform float noiseSpeedX;
                                   uniform float noiseSpeedY;
                                   
                                   vec2 hash( vec2 p ) {
                                        p = vec2( dot(p,vec2(127.1,311.7)),
                                        dot(p,vec2(269.5,183.3)) );
                                        return -1.0 + 2.0*fract(sin(p)*43758.5453123);
                                    }
                                                               
                                    float noise( in vec2 p ){
                                        vec2 i = floor( p );
                                        vec2 f = fract( p );
                                        vec2 u = f*f*(3.0-2.0*f);
                                        return mix( mix( dot( hash( i + vec2(0.0,0.0) ), f - vec2(0.0,0.0) ),
                                                        dot( hash( i + vec2(1.0,0.0) ), f - vec2(1.0,0.0) ), u.x),
                                                   mix( dot( hash( i + vec2(0.0,1.0) ), f - vec2(0.0,1.0) ), 
                                                       dot( hash( i + vec2(1.0,1.0) ), f - vec2(1.0,1.0) ), u.x), u.y);
                                    }
                                   void main(void){
                                       vec3 bump = texture2DRect(tex1, gl_FragCoord.xy).rgb;
                                       float disp = dot(bump, vec3(s1, s2, s3));
                                       vec2 uv = gl_FragCoord.xy/size.xy;
                                       vec2 d;
                                       vec2 n = vec2(uv.x, uv.y);
                                       vec2 n2 = vec2(uv.y, uv.y);
                                       float tX = noise(uv*noisePeriodX+time*noiseSpeedX);
                                       float tY = noise(uv*noisePeriodY+time*noiseSpeedY+noiseOffset);
                                       vec2 wave = vec2(tX*noiseAmountX, tY*noiseAmountY);
                                       d.x = (disp*s4)*size.x;
                                       d.y = (disp*s4)*size.y;
                                       gl_FragColor = texture2DRect(tex0, gl_FragCoord.xy + vec2(d.x, d.y)+wave);
                                   }
                                   );
    }
    void update(){
        pingPong.dst->begin();
        shader.begin();
        ofClear(0, 0);
        shader.setUniformTexture( "tex0" , textures[0].getTexture(), 0 );
        shader.setUniformTexture( "tex1" , textures[1].getTexture(), 1 );
        shader.setUniform1f("time", ofGetElapsedTimef());
        shader.setUniform2f("size", 640., 480);
        shader.setUniform1f("s1", s1);
        shader.setUniform1f("s2", s2);
        shader.setUniform1f("s3", s3);
        shader.setUniform1f("s4", s4);
        shader.setUniform1f("noiseOffset", noiseOffset);
        shader.setUniform1f("noiseAmountX", noiseAmountX);
        shader.setUniform1f("noiseAmountY", noiseAmountY);
        shader.setUniform1f("noisePeriodX", noisePeriodX);
        shader.setUniform1f("noisePeriodY", noisePeriodY);
        shader.setUniform1f("noiseSpeedX", noiseSpeedX);
        shader.setUniform1f("noiseSpeedY", noiseSpeedY);
        
        renderFrame();
        
        shader.end();
        pingPong.dst->end();
    };
    void setup(int w, int h){
        width = w;
        height = h;
    }
    void setupParameters(){
        parameters.add(s1.set("offsetX", 1., 0., 1.));
        parameters.add(s2.set("offsetY", 1., 0., 1.));
        parameters.add(s3.set("offsetZ", 1., 0., 1.));
        parameters.add(s4.set("multiply", 1., 0., 1.));
        parameters.add(noiseOffset.set("noiseOffset", 1., 0., 3000.));
        parameters.add(noiseAmountX.set("noiseAmountX", 1., 0., 50.));
        parameters.add(noiseAmountY.set("noiseAmountY", 1., 0., 50.));
        parameters.add(noisePeriodX.set("noisePeriodX", 1., 0., 20.));
        parameters.add(noisePeriodY.set("noisePeriodY", 1., 0., 20.));
        parameters.add(noiseSpeedX.set("noiseSpeedX", 1., 0., 7.));
        parameters.add(noiseSpeedY.set("noiseSpeedY", 1., 0., 7.));

    }
    int width;
    int height;
    ofParameterGroup parameters;
    ofParameter<float> s1;
    ofParameter<float> s2;
    ofParameter<float> s3;
    ofParameter<float> s4;
    ofParameter<float> s5;
    ofParameter<float> s6;
    ofParameter<float> noiseOffset;
    ofParameter<float> noiseAmountX;
    ofParameter<float> noiseAmountY;
    ofParameter<float> noisePeriodX;
    ofParameter<float> noisePeriodY;
    ofParameter<float> noiseSpeedX;
    ofParameter<float> noiseSpeedY;
};

