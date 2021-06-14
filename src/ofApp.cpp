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
	posPaletaP1 = new ofVec2f(20, 20);
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
		//calcular el input
		if (w)
			posPaletaP1->y -= 10;
		if (s)
			posPaletaP1->y += 10;

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

		//enviar datos al cliente
		memset(Buffer, 0, BUFFER_SIZE);
		//serialización
		//  [pelotaX,pelotaY,player1.y]
		sprintf(Buffer, "%f,%f,%f", posPelota->x, posPelota->y, posPaletaP1->y ) ;
		udpManager.SendAll(Buffer, BUFFER_SIZE);

		//recibir datos enviados por el cliente
		memset(Buffer, 0, BUFFER_SIZE);
		if (udpManager.Receive(Buffer, BUFFER_SIZE) > 0)
		{
			//deserializar la posicion de la paleta del jugador 2
			posPaletaP2->y = atof(Buffer);
		}
	}

	if (AppState == EState::client)
	{
		//calcular el input
		if (w)
			posPaletaP2->y -= 10;
		if (s)
			posPaletaP2->y += 10;

		//serializar y enviar la posicion de la paleta de jugador 2
		memset(Buffer, 0, BUFFER_SIZE);
		sprintf(Buffer, "%f", posPaletaP2->y);
		udpManager.Send(Buffer, BUFFER_SIZE);
		
		//recibir y deserializar la posicion del P1 y la pelota
		memset(Buffer, 0, BUFFER_SIZE);
		if (udpManager.Receive(Buffer, BUFFER_SIZE) > 0)
		{
			//deserializar
			char* valor;
			valor = strtok(Buffer, ",");
			//el primer valor corresponde a la x de la pelota
			posPelota->x = atof(valor);
			valor = strtok(NULL, ",");
			//el segundo valor corresponde a la y de la pelota
			posPelota->y = atof(valor);
			valor = strtok(NULL, ",");
			//el tercer valor corresponde a la y del jugador 1
			posPaletaP1->y = atof(valor);
		}
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
		ofSetColor(255, 0, 0);
		ofDrawRectangle(posPaletaP1->x, posPaletaP1->y, sizePaleta->x, sizePaleta->y);
		ofSetColor(255, 255, 255);
		ofDrawRectangle(posPaletaP2->x, posPaletaP2->y, sizePaleta->x, sizePaleta->y);
	}
	else if (AppState == EState::server)
	{
		ofDrawBitmapString("SERVIDOR", ofGetWidth() / 2, 20);
		ofSetColor(255, 0, 0);
		//dibujar pelota
		ofCircle(posPelota->x, posPelota->y, 20);
		//dibujar paletas
		ofSetColor(255, 255, 255);
		ofDrawRectangle(posPaletaP1->x, posPaletaP1->y, sizePaleta->x, sizePaleta->y);
		ofSetColor(255, 0, 0);
		ofDrawRectangle(posPaletaP2->x, posPaletaP2->y, sizePaleta->x, sizePaleta->y);
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
