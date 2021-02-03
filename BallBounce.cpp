#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include "BallBounce.h"

int full = 255;
int half = 128;
int empt = 0;

Ball::Ball(int startX, int startY, int type) {
    x = startX;
    y = startY;
    ballType = type;

}



BallLight::BallLight(Adafruit_NeoMatrix* thisMatrix, Ball *pBall1, Ball *pBall2, Ball *pBall3, int interval) { // Ball *pBall

  Serial.println("Initializing objects");
  neonMatrix = thisMatrix;
  
  ball1 = pBall1;
  ball2 = pBall2;
  ball3 = pBall3;
  ball1->neonMatrix = neonMatrix;
  frameInterval = 1000/interval;
  
}

void BallLight::updateBall(Ball *pBall) {
  Ball* ball = pBall;
  ball->x += ball->vX;
  ball->y += ball->vY;
    // randomisation
  int directChangeYN = random(8);
  if(directChangeYN == 1){
    int directChangeXY = random(3);
    if(directChangeXY == 0){
      ball->vX *= -1;
    }
    else if(directChangeXY == 1){
      ball->vY *= -1;
    }
    else if(directChangeXY == 2){
      ball->vX *= -1;
      ball->vY *= -1;
    }
  }
    //bounce phisics
  if (ball->x >= neonMatrix->width() - 1 && ball->vX > 0) {//right
    ball->vX *= -1;
  }
  
  if (ball->x <= 0 && ball->vX < 0) {//left
    ball->vX *= -1;
  }
  
  if (ball->y >= neonMatrix->height()-1 && ball->vY > 0) {//bottom
      ball->vY *= -1;    
  }

  if (ball->y <= 0 && ball->vY < 0) {//top
    ball->vY *= -1;
  }


  //spinner controls
  if (ball->ballType == 1){
    ball->dir++;
    if (ball->dir >= 4){
      ball->dir =0;
    }
    if (ball->dir == 0)      {ball->diffRow1 = -1; ball->diffCol1 = -1; ball->diffRow2 =  1; ball->diffCol2 =  1;  }
    else if (ball->dir == 1) {ball->diffRow1 = -1; ball->diffCol1 =  0; ball->diffRow2 =  1; ball->diffCol2 =  0;  }
    else if (ball->dir == 2) {ball->diffRow1 = -1; ball->diffCol1 =  1; ball->diffRow2 =  1; ball->diffCol2 = -1;  }
    else if (ball->dir == 3) {ball->diffRow1 =  0; ball->diffCol1 =  1; ball->diffRow2 =  0; ball->diffCol2 = -1;  }
    //Color Controls
    
      long randColor = random(3);
    if (randColor == 1) {
      ball->colorCircle++;
    }
    if (ball->colorCircle >=12){
      ball->colorCircle = 0;
    }
   }

  else if (ball->ballType == 2){
    ball->dir++;
    if (ball->dir >= 2){
      ball->dir =0;
    }
    if (ball->dir == 0)      {ball->diffRow1 = -1; ball->diffCol1 = -1; ball->diffRow2 =  1; ball->diffCol2 =  1; ball->diffRow3 = -1; ball->diffCol3 =  1; ball->diffRow4 =  1; ball->diffCol4 = -1;  }
    else if (ball->dir == 1) {ball->diffRow1 = -1; ball->diffCol1 =  0; ball->diffRow2 =  1; ball->diffCol2 =  0; ball->diffRow3 =  0; ball->diffCol3 =  1; ball->diffRow4 =  0; ball->diffCol4 = -1;  }
  
    //Color Control
      long randColor = random(4);
    if (randColor == 1) {
      ball->colorCircle++;
    }
    if (ball->colorCircle >=6){
      ball->colorCircle = 0;
    }
   }
     else {
    ball->dir++;
    if (ball->dir >= 2){
      ball->dir =0;
    }
    if (ball->dir == 0)      {ball->diffRow1 = -1; ball->diffCol1 = -1; ball->diffRow2 =  1; ball->diffCol2 =  1; ball->diffRow3 = -1; ball->diffCol3 =  1; ball->diffRow4 =  1; ball->diffCol4 = -1;  }
    else if (ball->dir == 1) {ball->diffRow1 = -1; ball->diffCol1 =  0; ball->diffRow2 =  1; ball->diffCol2 =  0; ball->diffRow3 =  0; ball->diffCol3 =  1; ball->diffRow4 =  0; ball->diffCol4 = -1;  }
  
    //Color Controls

      long randColor = random(5);
    if (randColor == 1) {
      ball->colorCircle++;
    }
    if (ball->colorCircle >=6){
      ball->colorCircle = 0;
    }
   }
 
}

void BallLight::drawBall(Ball *pBall) {
  Ball* ball = pBall;
  if (ball->ballType == 1){
    if (ball->colorCircle == 0){//Red
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(full, empt, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(full, empt, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(full, empt, empt));
    }
  
    else if (ball->colorCircle == 1){//Rose
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(full, empt, half));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(full, empt, half));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(full, empt, half));
    }
    else if (ball->colorCircle == 2){//Mangneta
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(full, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(full, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(full, empt, full));
    }
    else if (ball->colorCircle == 3){//Violet
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(half, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(half, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(half, empt, full));
    }
    else if (ball->colorCircle == 4){//Blue
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(empt, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(empt, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(empt, empt, full));
    }
    else if (ball->colorCircle == 5){//Asure
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(empt, half, full));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(empt, half, full));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(empt, half, full));
    }
    else if (ball->colorCircle == 6){//Cyan
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(empt, full, full));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(empt, full, full));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(empt, full, full));
    }
    else if (ball->colorCircle == 7){//SpringGreen
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(empt, full, half));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(empt, full, half));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(empt, full, half));
    }
    else if (ball->colorCircle == 8){//Green
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(empt, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(empt, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(empt, full, empt));
    }
    else if (ball->colorCircle == 9){//Chartreuse
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(half, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(half, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(half, full, empt));
    }
    else if (ball->colorCircle == 10){//Yellow
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(full, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(full, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(full, full, empt));
    }
    else if (ball->colorCircle == 11){//Orange
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(full, half, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(full, half, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(full, half, empt));
    }
  }
  
  if (ball->ballType == 2){
    if (ball->colorCircle == 0){//Red
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(full, empt, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(full, empt, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(full, empt, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow3, ball->y + ball->diffCol3, neonMatrix->Color(full, empt, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow4, ball->y + ball->diffCol4, neonMatrix->Color(full, empt, empt));
    }
    else if (ball->colorCircle == 1){//Mangneta
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(full, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(full, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(full, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow3, ball->y + ball->diffCol3, neonMatrix->Color(full, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow4, ball->y + ball->diffCol4, neonMatrix->Color(full, empt, full));
    }
    else if (ball->colorCircle == 2){//Blue
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(empt, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(empt, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(empt, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow3, ball->y + ball->diffCol3, neonMatrix->Color(empt, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow4, ball->y + ball->diffCol4, neonMatrix->Color(empt, empt, full));
    }
    else if (ball->colorCircle == 3){//Cyan
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(empt, full, full));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(empt, full, full));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(empt, full, full));
      neonMatrix->writePixel(ball->x + ball->diffRow3, ball->y + ball->diffCol3, neonMatrix->Color(empt, full, full));
      neonMatrix->writePixel(ball->x + ball->diffRow4, ball->y + ball->diffCol4, neonMatrix->Color(empt, full, full));
    }
    else if (ball->colorCircle == 4){//Green
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(empt, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(empt, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(empt, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow3, ball->y + ball->diffCol3, neonMatrix->Color(empt, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow4, ball->y + ball->diffCol4, neonMatrix->Color(empt, full, empt));
    }
    else if (ball->colorCircle == 5){//Yellow
      neonMatrix->writePixel(ball->x, ball->y, neonMatrix->Color(full, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(full, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(full, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow3, ball->y + ball->diffCol3, neonMatrix->Color(full, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow4, ball->y + ball->diffCol4, neonMatrix->Color(full, full, empt));
    }

  }
  if (ball->ballType == 3){
    if (ball->colorCircle == 0){//Red
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(full, empt, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(full, empt, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow3, ball->y + ball->diffCol3, neonMatrix->Color(full, empt, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow4, ball->y + ball->diffCol4, neonMatrix->Color(full, empt, empt));
    }
    else if (ball->colorCircle == 1){//Mangneta
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(full, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(full, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow3, ball->y + ball->diffCol3, neonMatrix->Color(full, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow4, ball->y + ball->diffCol4, neonMatrix->Color(full, empt, full));
    }
    else if (ball->colorCircle == 2){//Blue
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(empt, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(empt, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow3, ball->y + ball->diffCol3, neonMatrix->Color(empt, empt, full));
      neonMatrix->writePixel(ball->x + ball->diffRow4, ball->y + ball->diffCol4, neonMatrix->Color(empt, empt, full));
    }
    else if (ball->colorCircle == 3){//Cyan
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(empt, full, full));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(empt, full, full));
      neonMatrix->writePixel(ball->x + ball->diffRow3, ball->y + ball->diffCol3, neonMatrix->Color(empt, full, full));
      neonMatrix->writePixel(ball->x + ball->diffRow4, ball->y + ball->diffCol4, neonMatrix->Color(empt, full, full));
    }
    else if (ball->colorCircle == 4){//Green
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(empt, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(empt, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow3, ball->y + ball->diffCol3, neonMatrix->Color(empt, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow4, ball->y + ball->diffCol4, neonMatrix->Color(empt, full, empt));
    }
    else if (ball->colorCircle == 5){//Yellow
      neonMatrix->writePixel(ball->x + ball->diffRow1, ball->y + ball->diffCol1, neonMatrix->Color(full, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow2, ball->y + ball->diffCol2, neonMatrix->Color(full, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow3, ball->y + ball->diffCol3, neonMatrix->Color(full, full, empt));
      neonMatrix->writePixel(ball->x + ball->diffRow4, ball->y + ball->diffCol4, neonMatrix->Color(full, full, empt));
    }
  }
  
}

int BallLight::updateBallLight() {
  updateBall(ball1);
  drawBall(ball1);
  updateBall(ball2);
  drawBall(ball2);
  updateBall(ball3);
  drawBall(ball3);
  nextFrame = millis() + frameInterval;
  return nextFrame;
}
