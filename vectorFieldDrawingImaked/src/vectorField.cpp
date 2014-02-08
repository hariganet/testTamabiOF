//
//  vectorField.cpp
//  VectorField
//
//  Created by Nobuhiko Asada on 2014/02/06.
//
//

#include "vectorField.h"

vectorField::vectorField(){
    
}

vectorField::~vectorField(){
    
}

//ベクトル場の初期化
void vectorField::setupField(int innerW, int innerH, int outerW, int outerH){
    
    fieldWidth = innerW;
    fieldHeight = innerH;
    externalWidth = outerW;
    externalHeight = outerH;
    
    field.clear();
    
    fieldSize = fieldWidth * fieldHeight;
    for (int i=0; i < fieldSize; ++i) {
        ofVec2f pt;
        pt.set(0, 0);
        field.push_back(pt);
    }
}

//消去
void vectorField::clear(){
    for(int i=0; i < fieldSize; ++i){
        field[i].set(0, 0);
    }
}

//徐々に力が弱まるようにする
void vectorField::fadeField(float fadeAmount){
    for (int i=0; i<fieldSize; ++i) {
        field[i].set(field[i].x*fadeAmount, field[i].y*fadeAmount);
    }
}

//全てのベクトルをランダムに生成
void vectorField::randomizeField(float scale){
    for (int i=0; i<fieldSize; ++i) {
        float x = static_cast<float>(ofRandom(-1, 1)) * scale;
        float y = static_cast<float>(ofRandom(-1, 1)) * scale;
        field[i].set(x, y);
    }
}

//ベクトル場の様子を描画
void vectorField::draw(){
    
    float scalex = static_cast<float >(externalWidth) / static_cast<float >(fieldWidth);
    float scaley = static_cast<float >(externalHeight) / static_cast<float >(fieldHeight);
    
    for (int i=0; i<fieldWidth; ++i) {
        for (int j=0; j<fieldHeight; ++j) {
            int pos = j * fieldWidth + i;
            
            //グリッド１マスの幅と高さ
            float px = i * scalex;
            float py = j * scaley;
            
            float px2 = px + field[pos].x * 5;
            float py2 = py + field[pos].y * 5;
            
            ofLine(px, py, px2, py2);
            
            ofVec2f line;
            line.set(px2-px, py2-py);
            float length = line.length();
            line.normalize();
            line.rotate(90);
            ofLine(px - line.x*length*0.2, py - line.y*length*0.2, px + line.x*length*0.2, py + line.y*length*0.2);
        }
    }
}

//座標を指定して、その地点でのベクトル場から受ける力を算出
ofVec2f vectorField::getForceFromPos(float xpos, float ypos){
    ofVec2f frc;
    frc.set(0, 0);
    
    float xPct = xpos / static_cast<float >(externalWidth);
    float yPct = ypos / static_cast<float>(externalHeight);
    
    if((xPct < 0 || xPct > 1) || (yPct < 0 || yPct > 1)){
        return frc;
    }
    
    int fieldPosX = static_cast<int>(xPct * fieldWidth);
    int fieldPosY = static_cast<int>(yPct * fieldHeight);
    
    fieldPosX = MAX(0, MIN(fieldPosX, fieldWidth-1));
    fieldPosY = MAX(0, MIN(fieldPosY, fieldHeight-1));

    int pos = fieldPosY * fieldWidth + fieldPosX;
    
    frc.set(field[pos].x * 0.1, field[pos].y * 0.1);
    return frc;

}

//内向きの力を加える (吸引)
void vectorField::addInwardCircle(float x, float y, float radius, float strength){

    //実空間座標でのx, yをグリッド座標でのfieldx, fieldyに変換する
	float pctx			= x / (float)externalWidth;
	float pcty			= y / (float)externalHeight;
	float radiusPct		= radius / (float)externalWidth;
    
    int fieldPosX		= (int)(pctx * (float)fieldWidth);
    int fieldPosY		= (int)(pcty * (float)fieldHeight);
	float fieldRadius	= (float)(radiusPct * fieldWidth);
	
    //グリッド座標上でのx, yが影響を及ぼす範囲を計算(startx-endx) * (starty * endy)のエリア
	int startx	= MAX(fieldPosX - fieldRadius, 0);
	int starty	= MAX(fieldPosY - fieldRadius, 0);
	int endx	= MIN(fieldPosX + fieldRadius, fieldWidth);
	int endy	= MIN(fieldPosY + fieldRadius, fieldHeight);
	
    //エリア内に働くベクトルの力を計算
    for (int i = startx; i < endx; i++){
        for (int j = starty; j < endy; j++){
			
            int pos = j * fieldWidth + i;
            float distance = (float)sqrt((fieldPosX-i)*(fieldPosX-i) +
                                         (fieldPosY-j)*(fieldPosY-j));
            
			if (distance < 0.0001) distance = 0.0001;
			
            //該当のグリッド座標x, yが半径fieldRadius以下だったとき
			if (distance < fieldRadius){
				
				float pct = 1.0f - (distance / fieldRadius);
				
                float strongness = strength * pct;
                
                //方向の決定と正規化的な奴
                float unit_px = ( fieldPosX - i) / distance;
                float unit_py = ( fieldPosY - j) / distance;
                
                field[pos].x += unit_px * strongness;
                field[pos].y += unit_py * strongness;
            }
        }
    }
}

//外向きの力を加える (噴出)
void vectorField::addOutwardCircle(float x, float y, float radius, float strength){
	
	float pctx			= x / (float)externalWidth;
	float pcty			= y / (float)externalHeight;
	float radiusPct		= radius / (float)externalWidth;
	
    int fieldPosX		= (int)(pctx * (float)fieldWidth);
    int fieldPosY		= (int)(pcty * (float)fieldHeight);
	float fieldRadius	= (float)(radiusPct * fieldWidth);
	
	int startx	= MAX(fieldPosX - fieldRadius, 0);
	int starty	= MAX(fieldPosY - fieldRadius, 0);
	int endx	= MIN(fieldPosX + fieldRadius, fieldWidth);
	int endy	= MIN(fieldPosY + fieldRadius, fieldHeight);
	
    for (int i = startx; i < endx; i++){
        for (int j = starty; j < endy; j++){
            
            int pos = j * fieldWidth + i;
            float distance = (float)sqrt((fieldPosX-i)*(fieldPosX-i) +
                                         (fieldPosY-j)*(fieldPosY-j));
            
			if (distance < 0.0001) distance = 0.0001;
			
			if (distance < fieldRadius){
                
				float pct = 1.0f - (distance / fieldRadius);
                float strongness = strength * pct;
                float unit_px = ( fieldPosX - i) / distance;
                float unit_py = ( fieldPosY - j) / distance;
                field[pos].x -= unit_px * strongness;
                field[pos].y -= unit_py * strongness;
            }
        }
    }
}

//時計回りの渦巻き
void vectorField::addClockwiseCircle(float x, float y, float radius, float strength){
	
	float pctx			= x / (float)externalWidth;
	float pcty			= y / (float)externalHeight;
	float radiusPct		= radius / (float)externalWidth;
	
	// then, use them here:
    int fieldPosX		= (int)(pctx * (float)fieldWidth);
    int fieldPosY		= (int)(pcty * (float)fieldHeight);
	float fieldRadius	= (float)(radiusPct * fieldWidth);
	
	int startx	= MAX(fieldPosX - fieldRadius, 0);
	int starty	= MAX(fieldPosY - fieldRadius, 0);
	int endx	= MIN(fieldPosX + fieldRadius, fieldWidth);
	int endy	= MIN(fieldPosY + fieldRadius, fieldHeight);
	
	
    for (int i = startx; i < endx; i++){
        for (int j = starty; j < endy; j++){
			
            int pos = j * fieldWidth + i;
            float distance = (float)sqrt((fieldPosX-i)*(fieldPosX-i) +
                                         (fieldPosY-j)*(fieldPosY-j));
            
            
			if (distance < 0.0001) distance = 0.0001;
			
			if (distance < fieldRadius){
                //std::cout << "fieldRadius : " << fieldRadius << ", distance : " << distance << std::endl;
				
				float pct = 1.0f - (distance / fieldRadius);
				
                float strongness = strength * pct;
                float unit_px = ( fieldPosX - i) / distance;
                float unit_py = ( fieldPosY - j) / distance;
                field[pos].x += unit_py * strongness;
                field[pos].y -= unit_px * strongness;
            }
        }
    }
}

//反時計回りの渦巻き
void vectorField::addCounterClockwiseCircle(float x, float y, float radius, float strength){
    
	float pctx			= x / (float)externalWidth;
	float pcty			= y / (float)externalHeight;
	float radiusPct		= radius / (float)externalWidth;
	
    int fieldPosX		= (int)(pctx * (float)fieldWidth);
    int fieldPosY		= (int)(pcty * (float)fieldHeight);
	float fieldRadius	= (float)(radiusPct * fieldWidth);
	
	int startx	= MAX(fieldPosX - fieldRadius, 0);
	int starty	= MAX(fieldPosY - fieldRadius, 0);
	int endx	= MIN(fieldPosX + fieldRadius, fieldWidth);
	int endy	= MIN(fieldPosY + fieldRadius, fieldHeight);
	
	
    for (int i = startx; i < endx; i++){
        for (int j = starty; j < endy; j++){
			
            int pos = j * fieldWidth + i;
            float distance = (float)sqrt((fieldPosX-i)*(fieldPosX-i) +
                                         (fieldPosY-j)*(fieldPosY-j));
            
			if (distance < 0.0001) distance = 0.0001;
			
			if (distance < fieldRadius){
				
				float pct = 1.0f - (distance / fieldRadius);
				
                float strongness = strength * pct;
                float unit_px = ( fieldPosX - i) / distance;
                float unit_py = ( fieldPosY - j) / distance;
                field[pos].x -= unit_py * strongness;
                field[pos].y += unit_px * strongness;
            }
        }
    }
}

//円形の力を加える
void vectorField::addVectorCircle(float x, float y, float vx, float vy, float radius, float strength){
	
	float pctx			= x / (float)externalWidth;
	float pcty			= y / (float)externalHeight;
	float radiusPct		= radius / (float)externalWidth;
	
    int fieldPosX		= (int)(pctx * (float)fieldWidth);
    int fieldPosY		= (int)(pcty * (float)fieldHeight);
	float fieldRadius	= (float)(radiusPct * fieldWidth);
	
	int startx	= MAX(fieldPosX - fieldRadius, 0);
	int starty	= MAX(fieldPosY - fieldRadius, 0);
	int endx	= MIN(fieldPosX + fieldRadius, fieldWidth);
	int endy	= MIN(fieldPosY + fieldRadius, fieldHeight);
	
    for (int i = startx; i < endx; i++){
        for (int j = starty; j < endy; j++){
			
            int pos = j * fieldWidth + i;
            float distance = (float)sqrt((fieldPosX-i)*(fieldPosX-i) +
                                         (fieldPosY-j)*(fieldPosY-j));
            
			if (distance < 0.0001) distance = 0.0001;
			
			if (distance < fieldRadius){
				
				float pct = 1.0f - (distance / fieldRadius);
                float strongness = strength * pct;
                field[pos].x += vx * strongness;
                field[pos].y += vy * strongness;
            }
        }
    }
}

