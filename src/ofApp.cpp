#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//el estado inicial de la app es menu
	AppState = EState::menu;

	//configurar el menu
	mainPanel.setup();
	mainPanel.add(btnServer.setup("Crear partida"));
	mainPanel.add(btnClient.setup("Conectar a partida"));
	mainPanel.setPosition(ofGetWidth() / 2 - mainPanel.getWidth() / 2,
		ofGetHeight() / 2 - mainPanel.getHeight() / 2);
	btnClient.addListener(this, &ofApp::connectClient);
	btnServer.addListener(this, &ofApp::createServer);

	//pos y tamano de las paletas
	sizePaleta = new ofVec2f(20, 100);
	posPaletaP2 = new ofVec2f(ofGetWidth() - 40, 20);

	//valores iniciales de la simulacion
	posPelota = new ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
	velPelota = new ofVec2f(150, -200);


}

//setup para cliente
void ofApp::connectClient()
{
	AppState = EState::client;
	udpManager.Create();
	udpManager.Connect("127.0.0.1", PORT);
	udpManager.SetNonBlocking(true);
}


//setup para servidor
void ofApp::createServer()
{
	AppState = EState::server;
	udpManager.Create();
	udpManager.Bind(PORT);
	udpManager.SetNonBlocking(true);
}

//--------------------------------------------------------------
void ofApp::update()
{
	if (AppState == EState::server)
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
		if (posPelota->x > ofGetWidth())
		{
			velPelota->x *= -1;
			posPelota->x = ofGetWidth();
		}


		if (posPelota->y < 0)
		{
			velPelota->y *= -1;
			posPelota->y = 0;
		}
		if (posPelota->y > ofGetHeight())
		{
			velPelota->y *= -1;
			posPelota->y = ofGetHeight();
		}

		//limpiar buffer
		memset(Buffer, 0, BUFFER_SIZE);
		if (udpManager.Receive(Buffer, BUFFER_SIZE) > 0)
		{
			printf(Buffer);
		}
	}

	if (AppState == EState::client)
	{
		//calcular el input
		if (w)
			posPaletaP2->y -= 10;
		if (s)
			posPaletaP2->y += 10;


		memset(Buffer, 0, BUFFER_SIZE);
		sprintf(Buffer, "P2: %f \n", posPaletaP2->y);
		udpManager.Send(Buffer, BUFFER_SIZE);
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(ofColor::black);
	if (AppState == EState::menu)
	{
		ofDrawBitmapString(" PONG ", ofGetWidth() / 2, ofGetHeight() * 0.25);
		mainPanel.draw();
	}
	else if( AppState== EState::client)
	{
		ofDrawBitmapString("CLIENTE", ofGetWidth() / 2, 20);
		ofSetColor(255, 0, 0);
		//dibujar pelota
		ofCircle(posPelota->x, posPelota->y, 20);
		//dibujar paletas
		ofDrawRectangle(posPaletaP2->x, posPaletaP2->y, sizePaleta->x, sizePaleta->y);
	}
	else if (AppState == EState::server)
	{
		ofDrawBitmapString("SERVIDOR", ofGetWidth() / 2, 20);
		ofSetColor(255, 0, 0);
		//dibujar pelota
		ofCircle(posPelota->x, posPelota->y, 20);
		//dibujar paletas
		ofDrawRectangle(10, 10, 20, 100);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'w')
	{
		w = true;
	}
	if (key == 's')
	{
		s = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	if (key == 'w')
	{
		w = false;
	}
	if (key == 's')
	{
		s = false;
	}
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
