#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//valores iniciales de la simulacion
	posPelota = new ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
	velPelota = new ofVec2f(150, -200);
}

//--------------------------------------------------------------
void ofApp::update()
{
	//simulacion de movimiento de la pelota
	posPelota->x += velPelota->x * ofGetLastFrameTime();
	posPelota->y += velPelota->y * ofGetLastFrameTime();

	//colision con paredes

	if (posPelota->x < 0)
	{
		velPelota->x *= -1;
		posPelota->x = 0;
	}
	if(posPelota->x > ofGetWidth())
	{
		velPelota->x *= -1;
		posPelota->x = ofGetWidth();
	}


	if (posPelota->y < 0)
	{
		velPelota->y *= -1;
		posPelota->y = 0;
	}
	if(posPelota->y > ofGetHeight())
	{
		velPelota->y *= -1;
		posPelota->y = ofGetHeight();
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(255, 255, 255, 255);

	ofSetColor(255, 0, 0);
	ofCircle(  posPelota->x, posPelota->y , 20);

	ofDrawRectangle(10, 10, 20, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
