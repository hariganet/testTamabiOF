#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
    
    //ベクトル場の初期化（画面一杯に、横102個、縦76個のベクトル）
    VF.setupField(102, 76, ofGetWidth(), ofGetHeight());
    
    //パーティクルを10000個生成
	for (int i = 0; i < 10000; i++){
		particle myParticle;
		myParticle.setInitialCondition
		(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
		particles.push_back(myParticle);
	}

    
    //初期状態は内向きの力
    addMode = 2;

    preMouse.set(0, 0);
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
    
    VF.fadeField(0.998f);
}

//--------------------------------------------------------------
void testApp::draw(){
	//現在のモードを画面に表示
	string msg;
	switch (addMode) {
            
		case 1:
			msg = "mode : Outward";
			break;
			
		case 2:
			msg = "mode : Inward";
			break;
			
		case 3:
			msg = "mode : Clockwise";
			break;
			
		case 4:
			msg = "mode : Counter Clockwise";
			break;
			
		case 5:
			msg = "mode : Circle";
			break;
			
		default:
			break;
	}
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("key 1 - 4 : change vector mode", 20, 20);
	ofDrawBitmapString(msg, 20, 40);
	
	//ベクトル場を描画
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofSetColor(0,130,130, 200);
	VF.draw();
    
    //ベクトル場に配置されたparticleを描画
	ofSetColor(0, 127, 255)	;
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}

    
	ofDisableBlendMode();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	// 1 - 4のキーでベクトル場のモードを変更
	switch (key) {
		case '1':
			//外向き
			addMode = 1;
			break;
			
		case '2':
			//内向き
			addMode = 2;
			break;
			
		case '3':
			//時計回り
			addMode = 3;
			break;
			
		case '4':
			//反時計回り
			addMode = 4;
			break;
		case '5':
			//円形の力
			addMode = 5;
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
    
    ofVec2f nowMouse, tmp;
    nowMouse.set(x, y);
    
    tmp.set(nowMouse-preMouse);
    tmp.normalize();
    
	//モードに応じてベクトル場に力を加える
	switch (addMode) {
            
		case 1:
			//外向き
			VF.addOutwardCircle(x,y, 100, 0.5);
			break;
			
		case 2:
			//内向き
			VF.addInwardCircle(x,y, 100, 0.5);
			break;
			
		case 3:
			//時計回り
			VF.addClockwiseCircle(x, y, 200, 0.5);
			break;
			
		case 4:
			//反時計回り
			VF.addCounterClockwiseCircle(x, y, 200, 0.5);
			break;
        case 5:
            //円形の力
            VF.addVectorCircle(x, y, tmp.x, tmp.y, 200, 0.5);
			
		default:
			break;
	}

    preMouse = nowMouse;
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
