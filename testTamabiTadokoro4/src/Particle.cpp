//
//  Particle.cpp
//  testTamabiTadokoro4
//
//  Created by Nobuhiko Asada on 2014/02/05.
//
//

#include "Particle.h"

Particle::Particle(){
    setInitialCondition(0, 0, 0, 0);
    damping = 0.01f;
}

void Particle::resetForce(){
    frc.set(0, 0);
}

void Particle::addForce(float x, float y){
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}

void Particle::addDampingForce(){
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}

void Particle::setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px, py);
    vel.set(vx, vy);
}

void Particle::update(){
    vel = vel + frc;
    pos = pos + vel;
}

void Particle::draw(){
    ofCircle(pos.x, pos.y, 3);
}

void Particle::bounceOffWalls(){
	//壁の範囲を設定
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();
	//左右の壁でのバウンド
	if (pos.x > maxx){
		pos.x = maxx;
		vel.x *= -1;
	} else if (pos.x < minx){
		pos.x = minx;
		vel.x *= -1;
	}
	//上下の壁でのバウンド
	if (pos.y > maxy){
		pos.y = maxy;
		vel.y *= -1;
	} else if (pos.y < miny){
		pos.y = miny;
		vel.y *= -1;
	}
}
