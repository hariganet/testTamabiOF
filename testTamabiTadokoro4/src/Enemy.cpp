//
//  Enemy.cpp
//  testTamabiTadokoro4
//
//  Created by Nobuhiko Asada on 2014/02/05.
//
//

#include "Enemy.h"

Enemy::Enemy(){
    vel = 5;
    isHit = false;
    w = wInit = 200;
    h = hInit = 80;
}

Enemy::~Enemy(){
    
}

void Enemy::update(){
    pos.x += vel;
    
    if(pos.x < posInit.x-300-wInit/2 || pos.x > posInit.x+300-wInit/2){
        vel = -vel;
    }
}

void Enemy::draw(){

    ofRect(pos.x, pos.y, w, h);

}

void Enemy::setInitialCondition(float _x, float _y){
    posInit.x = _x;
    posInit.y = _y;
    pos = posInit;

}

void Enemy::erasing(){
    w *= 0.95;
    h *= 0.95;
    w = ceil(w);
    h = ceil(h);
    
}

void Enemy::checkHit(float _x, float _y){
    
    if(pos.x < _x && _x < pos.x + w && pos.y < _y && _y < pos.y + h){
        isHit = true;
    }
    if(!isHit){
        ;
    }else{
        erasing();
    }

    
}

void Enemy::resetInitialCondition(){
    w = wInit;
    h = hInit;
    isHit = false;
}