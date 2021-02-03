#ifndef BallBounce_h
#define BallBounce.h
#endif
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <pins_arduino.h>
#include "BallBounce.h"
#endif

class Ball {

  public:


    Ball(int startX, int startY, int type);
    int vX = -1;
    int vY = -1;
    int x = 0;
    int y = 0;
    int ballType = 1;
    void deflect();
    Adafruit_NeoMatrix* neonMatrix;
    int dir = 0;
    int colorCircle = 0;
    int diffRow1;
    int diffCol1;
    int diffRow2;
    int diffCol2;
    int diffRow3;
    int diffCol3;
    int diffRow4;
    int diffCol4;
    
};


class BallLight {

  public:

    BallLight(Adafruit_NeoMatrix *thisMatrix, Ball *pBall1, Ball *pBall2, Ball *pBall3, int interval);
    Adafruit_NeoMatrix* neonMatrix;
    int updateBallLight();
    uint8_t numPlayers;
    Ball* ball1;
    Ball* ball2;
    Ball* ball3;
    void updateBall(Ball* pBall);
    void drawBall(Ball* pBall);
    int frameInterval;
    long nextFrame = 0;
};
