#include "ofxColor.h"

ofColorMode ofxColor::defaultColorMode = OF_COLOR_RGB;
float ofxColor::defaultColorRange = 255;
ofColorAttribute ofxColor::colorSortMode = OF_COLOR_VALUE;

ofxColor::ofxColor() {
	colorMode = defaultColorMode;
	colorRange = defaultColorRange;
	clear();
}

ofxColor::ofxColor(float x, float y, float z, ofColorMode colorMode, float colorRange) {
	this->colorMode = colorMode;
	this->colorRange = colorRange;
	set(x, y, z);
}

ofxColor::ofxColor(float x, float y, float z, float a, ofColorMode colorMode, float colorRange) {
	this->colorMode = colorMode;
	this->colorRange = colorRange;
	set(x, y, z, a);
}

ofxColor::ofxColor(const ofxColor& x) {
	(*this) = x;
}

void ofxColor::set(float x, float y, float z) {
	set(x, y, z, colorRange);
}

void ofxColor::set(float x, float y, float z, float a) {
	if(colorMode == OF_COLOR_RGB) {
		r = x;
		g = y;
		b = z;
		updateHsv();
	} else if(colorMode == OF_COLOR_HSV) {
		h = x;
		s = y;
		v = z;
		updateRgb();
	}
	this->a = a;
}

#define getByte(x, y) ((x >> (8 * y)) & 0xff)

ofxColor& ofxColor::operator=(const int& asHex) {
	float resize = colorRange / 255.;
	a = getByte(asHex, 3) * resize;
	if(colorMode == OF_COLOR_RGB) {
		r = getByte(asHex, 2) * resize;
		g = getByte(asHex, 1) * resize;
		b = getByte(asHex, 0) * resize;
		updateHsv();
	} else if(colorMode == OF_COLOR_HSV) {
		r = getByte(asHex, 2) * resize;
		g = getByte(asHex, 1) * resize;
		b = getByte(asHex, 0) * resize;
		updateRgb();
	}
	a = colorRange;
	return *this;
}

ofxColor& ofxColor::operator=(const ofxColor& x) {
	colorMode = x.colorMode;
	colorRange = x.colorRange;
	r = x.r;
	g = x.g;
	b = x.b;
	h = x.h;
	s = x.s;
	v = x.v;
	a = x.a;
	return *this;
}

ofxColor& ofxColor::operator=(const string& asHex) {
	int offset = 0;
	if(asHex[0] == '#' || asHex[0] == 'x')
		offset = 1;
	if(asHex[1] == 'x')
		offset = 2;
	istringstream xStream(asHex.substr(offset + 0, 2));
	istringstream yStream(asHex.substr(offset + 2, 2));
	istringstream zStream(asHex.substr(offset + 4, 2));
	unsigned int x, y, z;
	xStream >> hex >> x;
	yStream >> hex >> y;
	zStream >> hex >> z;
	set(x, y, z);
	return *this;
}

void ofxColor::setColorMode(ofColorMode colorMode) {
	this->colorMode = colorMode;
}

ofColorMode ofxColor::getColorMode() const {
	return colorMode;
}

void ofxColor::setColorRange(float colorRange) {
	this->colorRange = colorRange;
}

float ofxColor::getColorRange() const {
	return colorRange;
}

void ofxColor::setDefaultColorMode(ofColorMode colorMode) {
	defaultColorMode = colorMode;
}

ofColorMode ofxColor::getDefaultColorMode() {
	return defaultColorMode;
}

void ofxColor::setDefaultColorRange(float colorRange) {
	defaultColorRange = colorRange;
}

float ofxColor::getDefaultColorRange() {
	return defaultColorRange;
}

void ofxColor::setColorSortMode(ofColorAttribute colorSortMode) {
	ofxColor::colorSortMode = colorSortMode;
}

ofColorAttribute ofxColor::getColorSortMode() {
	return colorSortMode;
}

ofxColor ofxColor::operator+(const ofxColor& x) const {
	ofxColor both;
	if(colorMode == OF_COLOR_RGB) {
		both.r = r + x.r;
		both.g = g + x.g;
		both.b = b + x.b;
		both.updateHsv();
	} else if(colorMode == OF_COLOR_HSV) {
		both.h = h + x.h;
		both.s = s + x.s;
		both.v = v + x.v;
		both.updateRgb();
	}
	return both;
}

ofxColor ofxColor::operator*(float x) const {
	ofxColor both = (*this);
	both *= x;
	return both;
}

ofxColor ofxColor::operator/(float x) const {
	return (*this) * (1 / x);
}

void ofxColor::operator*=(float x) {
	if(colorMode == OF_COLOR_RGB) {
		r *= x;
		g *= x;
		b *= x;
		updateHsv();
	} else if(colorMode == OF_COLOR_HSV) {
		h *= x;
		s *= x;
		v *= x;
		updateRgb();
	}
}

void ofxColor::operator/=(float x) {
	(*this) *= (1 / x);
}

int ofxColor::operator==(const ofxColor& x) const {
	if(r == x.r &&
		g == x.g &&
		b == x.b)
		return 0;
	switch(colorSortMode) {
		case OF_COLOR_RED: return r < x.r ? -1 : +1;
		case OF_COLOR_GREEN: return g < x.g ? -1 : +1;
		case OF_COLOR_BLUE: return b < x.b ? -1 : +1;
		case OF_COLOR_HUE: return h < x.h ? -1 : +1;
		case OF_COLOR_SATURATION: return s < x.s ? -1 : +1;
		case OF_COLOR_VALUE: return v < x.v ? -1 : +1;
		case OF_COLOR_ALPHA: return a < x.a ? -1 : +1;
	}
	return 0;
}

bool ofxColor::operator<(const ofxColor& x) const {
	return (*this == x) < 0;
}

bool ofxColor::operator>(const ofxColor& x) const {
	return (*this == x) > 0;
}

float ofxColor::distance(const ofxColor& x) const {
	float maxDistance = sqrtf(3 * colorRange * colorRange);
	if(colorMode == OF_COLOR_RGB) {
		float rr = r - x.r;
		float gg = g - x.g;
		float bb = b - x.b;
		return sqrtf(rr * rr + gg * gg + bb * bb) / maxDistance;
	} else if(colorMode == OF_COLOR_HSV) {
		float hh = h - x.h;
		float ss = s - x.s;
		float bb = v - x.v;
		return sqrtf(hh * hh + ss * ss + bb * bb) / maxDistance;
	}
}

#define makeColor(a, x, y, z, r) \
	((((unsigned char) (a * r) & 0xff) << 24) | \
	(((unsigned char) (x * r) & 0xff) << 16) | \
	(((unsigned char) (y * r) & 0xff) << 8) | \
	((unsigned char) (z * r) & 0xff))

unsigned int ofxColor::asHex() const {
	float resize = 255. / colorRange;
	if(colorMode == OF_COLOR_RGB) {
		return makeColor(a, r, g, b, resize);
	} else if(colorMode == OF_COLOR_HSV) {
		return makeColor(a, h, s, v, resize);
	}
}

void ofxColor::clear() {
	r = g = b = h = s = v = 0;
	a = colorRange;
}

void ofxColor::update() {
	if(colorMode == OF_COLOR_RGB)
		updateHsv();
	else if(colorMode == OF_COLOR_HSV)
		updateRgb();
}

void ofxColor::setColor() const {
	float resize = 255. / colorRange;
	if(a != 0)
		ofSetColor(
			(int) (r * resize),
			(int) (g * resize),
			(int) (b * resize),
			(int) (a * resize));
	else
		ofSetColor(
			(int) (r * resize),
			(int) (g * resize),
			(int) (b * resize));
}

void ofSetColor(const ofxColor& color) {
	color.setColor();
}

void ofxColor::updateRgb() {
	if(v == 0) {
		r = 0;
		g = 0;
		b = 0;
	} else if(s == 0) {
		r = v;
		g = v;
		b = v;
	} else {
		float normalHue = (float) h / (colorRange / 6.);
		float normalSaturation = (float) s / colorRange;
		int hCategory = (int) floor(normalHue);
		float hRemainder = normalHue - hCategory;
		float pv = (1. - normalSaturation) * v;
		float qv = (1. - normalSaturation * hRemainder) * v;
		float tv = (1. - normalSaturation * (1. - hRemainder)) * v;
		switch(hCategory) {
			case 0: // r
				r = v;
				g = tv;
				b =  pv;
				break;
			case 1: // g
				r = qv;
				g = v;
				b = pv;
				break;
			case 2:
				r = pv;
				g = v;
				b = tv;
				break;
			case 3: // b
				r = pv;
				g = qv;
				b = v;
				break;
			case 4:
				r = tv;
				g = pv;
				b = v;
				break;
			case 5: // back to r
				r = v;
				g = pv;
				b = qv;
				break;
		}
	}
}
void ofxColor::updateHsv() {
	float nr = r / colorRange;
	float ng = g / colorRange;
	float nb = b / colorRange;

	float max = nr;
	if(ng > max)
		max = ng;
	if(nb > max)
		max = nb;

	float min = nr;
	if(ng < min)
		min = ng;
	if(nb < min)
		min = nb;

	if(max == min) { // greys
		h = 0;
		s = 0;
		v = max * colorRange;
		return;
	} else {
		v = max;
		s = (max - min) / max;
	}

	if(nr == max) {
		h = 0. + (ng - nb) / (max - min);
		if(h < 0)
			h += 6.;
	} else if (ng == max) {
		h = 2. + (nb - nr) / (max - min);
	} else {
		h = 4. + (nr - ng) / (max - min);
	}

	h *= (colorRange / 6.);
	s *= colorRange;
	v *= colorRange;
}

ostream &operator<<(ostream &out, const ofxColor& color) {
	if(color.getColorMode() == OF_COLOR_RGB)
		out << "(" << color.r << ", " << color.g << ", " << color.b << ")";
	else if(color.getColorMode() == OF_COLOR_HSV)
		out << "(" << color.h << ", " << color.s << ", " << color.v << ")";
}

