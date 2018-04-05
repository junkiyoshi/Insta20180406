#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(39);
	ofSetWindowTitle("Insta");

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	float radius = 500 * ofNoise(ofGetFrameNum() * 0.05);
	ofColor line_color;

	this->cam.begin();

	for (int i = 0; i < 64; i++){

		line_color.setHsb(ofRandom(255), 239, 239);

		int z = ofRandom(-15, 15);
		ofPoint start = this->make_rect_point(ofGetWidth(), ofRandom(360) + ofNoise((ofRandom(360) + ofGetFrameNum()) * 0.003) * 360, z);
		ofPoint target = this->make_rect_point(ofGetWidth(), ofRandom(360) + ofNoise((ofRandom(360) + ofGetFrameNum()) * 0.003) * 360, z);
		ofPoint direction = target - start;
		float len = direction.length();
		direction.normalize();

		ofPoint point = start;
		for (int l = 0; l <= len; l++) {

			float noise_value = ofNoise(i * 0.5 + l * 0.005 + ofGetFrameNum() * 0.05);
			if (noise_value > 0.5) {
				
				point += direction;
				continue;
			}
			ofSetColor(line_color);

			if (point.distance(ofPoint()) <= radius) {

				ofPoint p1 = point.normalized() * radius;
				ofPoint p2 = (point + direction).normalized() * radius;
				if (p1.distance(p2) < radius) {
				
					ofDrawLine(p1, p2);
				}
			}
			else {

				ofDrawLine(point, point + direction);
			}
			point += direction;
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
ofPoint ofApp::make_rect_point(int len, int deg, int z) {

	deg += 45;
	int param = deg / 90;
	len = len / 2;

	switch (param % 4) {

	case 0:

		return ofPoint(len, ofMap(deg % 90, 0, 89, -len, len), z);
	case 1:

		return ofPoint(ofMap(deg % 90, 0, 89, len, -len), len, z);
	case 2:

		return ofPoint(-len, ofMap(deg % 90, 0, 89, len, -len), z);
	case 3:

		return ofPoint(ofMap(deg % 90, 0, 89, -len, len), -len, z);
	}

	return ofPoint();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}