#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
	ofSetBackgroundAuto(false);
    

    
    //パーティクルを10000個生成
	for (int i = 0; i < 10000; i++){
		particle myParticle;
		myParticle.setInitialCondition
		(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
		particles.push_back(myParticle);
	}
	
    //ベクトル場の初期化（画面一杯に、横102個、縦76個のベクトル）
    VF.setupField(102, 76, ofGetWidth(), ofGetHeight());
	
   	

}

//--------------------------------------------------------------
void testApp::update(){
    
    for (int i = 0; i < particles.size(); i++){
		
		//particleの力をリセット
		particles[i].resetForce();
		
		//ベクトル場から、それぞれのparticleにかかる力を算出
		ofVec2f frc;
		frc = VF.getForceFromPos(particles[i].pos.x, particles[i].pos.y);
		
		//Particleの状態を更新
		particles[i].addForce(frc.x, frc.y);
		particles[i].addDampingForce();
		particles[i].bounceOffWalls();
		particles[i].update();
	}
    
    //VF.fadeField(0.998f);
}

//--------------------------------------------------------------
void testApp::draw(){
	
	//ベクトル場を描画
//	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofEnableAlphaBlending();
	ofSetColor(0,0,0,15);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
	
	//VF.draw();
    
    //ベクトル場に配置されたparticleを描画
	ofSetColor(31, 200, 255)	;
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}
	
    
	ofDisableAlphaBlending();
//	ofDisableBlendMode();
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	// 1 - 4のキーでベクトル場のモードを変更
	switch (key) {
		case 'c':
			VF.clear();
			break;

		case ' ':
			//パーティクルの場所を初期化
			for (int i = 0; i < particles.size(); i++){
				particles[i].setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
			}
            break;
			
		default:
			break;
	}
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    float diffx = x -preMouse.x;
	float diffy = y -preMouse.y;
	
	VF.addVectorCircle(static_cast<float>(x), static_cast<float>(y), diffx*0.3, diffy*0.3, 60, 0.3f);
 	
	
    preMouse.x = x;
    preMouse.y = y;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
	
}
