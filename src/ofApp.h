#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxGui.h"

#define BUFFER_SIZE 100
#define PORT 14871

class ofApp : public ofBaseApp
{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//listeners de los botones
		void createServer(); //crea un servidor
		void connectClient(); //conecta el cliente a un servidor

		//variables de los objetos de pong
		ofVec2f *posPelota;
		ofVec2f *velPelota;
		ofVec2f *posPaletaP1;
		ofVec2f *posPaletaP2;
		ofVec2f *sizePaleta;
		//estado de las teclas
		bool w, s;

		//elementos del GUI
		ofxPanel mainPanel;
		ofxButton btnServer;
		ofxButton btnClient;

		//estado de la aplicación
		enum EState
		{
			menu, server, client
		} AppState;

		//variables para red
		ofxUDPManager udpManager;
		char Buffer[BUFFER_SIZE];
};
