#pragma once

#include "ofMain.h"

enum ofColorMode {
	OF_COLOR_RGB,
	OF_COLOR_HSV
};

enum ofColorAttribute {
	OF_COLOR_RED,
	OF_COLOR_GREEN,
	OF_COLOR_BLUE,
	OF_COLOR_HUE,
	OF_COLOR_SATURATION,
	OF_COLOR_VALUE,
	OF_COLOR_ALPHA
};

class ofxColor : public ofColor {
public:
	float	h, s, v;

	ofxColor();
	ofxColor(const ofxColor& x);
	ofxColor(float x, float y, float z,
		ofColorMode colorMode = ofxColor::defaultColorMode,
		float colorRange = ofxColor::defaultColorRange);
	ofxColor(float x, float y, float z, float a,
		ofColorMode colorMode = ofxColor::defaultColorMode,
		float colorRange = ofxColor::defaultColorRange);

	void set(float x, float y, float z);
	void set(float x, float y, float z, float a);
	ofxColor& operator=(const int& asHex);
	ofxColor& operator=(const ofxColor& x);
	ofxColor& operator=(const string& asHex);

	ofxColor operator+(const ofxColor& x) const;
	ofxColor operator*(float x) const;
	ofxColor operator/(float x) const;
	void operator*=(float x);
	void operator/=(float x);

	int operator==(const ofxColor& x) const;
	bool operator<(const ofxColor& x) const;
	bool operator>(const ofxColor& x) const;

	static void setDefaultColorMode(ofColorMode colorMode);
	static ofColorMode getDefaultColorMode();
	static void setDefaultColorRange(float colorRange);
	static float getDefaultColorRange();
	static void setColorSortMode(ofColorAttribute colorSortMode);
	static ofColorAttribute getColorSortMode();

	void setColorMode(ofColorMode colorMode);
	ofColorMode getColorMode() const;
	void setColorRange(float colorRange);
	float getColorRange() const;

	float distance(const ofxColor& x) const;
	unsigned int asHex() const;
	void setColor() const;

	void update();
	void clear();
	void updateRgb();
	void updateHsv();

	friend ostream &operator<<(ostream &out, const ofxColor& color);
private:
	static ofColorMode defaultColorMode;
	static float defaultColorRange;

	ofColorMode colorMode;
	float colorRange;
	static ofColorAttribute colorSortMode;
};

void ofSetColor(const ofxColor& color);

// <3 kyle mcdonald
