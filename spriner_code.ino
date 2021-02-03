//A spinning light on a pixel addressable LED matrix
//and three 256-pixel WS2812 addressable LED arrays like the ones available at:
//https://www.smart-prototyping.com/WS2812B-flexible-LED-matrix-8x32 or https://www.amazon.com/BTF-LIGHTING-Individual-Addressable-Flexible-Controllers/dp/B088BTXHRG/ref=sr_1_5?dchild=1&keywords=LED%2BArray&qid=1610822861&sr=8-5&th=1
//Written by William Lemon
//Do with it as you will, but I wouldn't recommend running a nuclear power plant, avionics package, or life support system using this code.
//If things go sideways (for instance, if you try to power your LEDs from an inappropriate source and that source catches on fire) I accept no responsibility.

//Requires installation of the Adafruit_GFX, Adafruit_NeoMatrix, and Adafruit_NeoPixel libraries.
//https://github.com/adafruit/Adafruit-GFX-Library
//https://github.com/adafruit/Adafruit_NeoMatrix
//https://github.com/adafruit/Adafruit_NeoPixel
 
//Note:
//An Arduino Uno won't cut it for this sketch, or for driving 768 WS2812s in general. This has been tested and works with NodeMCU.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>   
#include "BallBounce.h"
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PIN 0 //Pin D3 on the NodeMCU
#define FRAMERATE 5

static int frameInterval = 1000 / FRAMERATE;
long nextFrame = 0;
boolean runAsFastAsYouCan = false;

uint16_t range = 0;

// The following matrix declaration information is copied from Adafruit's NeoMatrix tiletest example:
//
// MATRIX DECLARATION:
// Parameter 1 = width of EACH NEOPIXEL MATRIX (not total display)
// Parameter 2 = height of each matrix
// Parameter 3 = number of matrices arranged horizontally
// Parameter 4 = number of matrices arranged vertically
// Parameter 5 = pin number (most are valid)
// Parameter 6 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the FIRST MATRIX; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs WITHIN EACH MATRIX are
//     arranged in horizontal rows or in vertical columns, respectively;
//     pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns WITHIN
//     EACH MATRIX proceed in the same order, or alternate lines reverse
//     direction; pick one.
//   NEO_TILE_TOP, NEO_TILE_BOTTOM, NEO_TILE_LEFT, NEO_TILE_RIGHT:
//     Position of the FIRST MATRIX (tile) in the OVERALL DISPLAY; pick
//     two, e.g. NEO_TILE_TOP + NEO_TILE_LEFT for the top-left corner.
//   NEO_TILE_ROWS, NEO_TILE_COLUMNS: the matrices in the OVERALL DISPLAY
//     are arranged in horizontal rows or in vertical columns, respectively;
//     pick one or the other.
//   NEO_TILE_PROGRESSIVE, NEO_TILE_ZIGZAG: the ROWS/COLUMS OF MATRICES
//     (tiles) in the OVERALL DISPLAY proceed in the same order for every
//     line, or alternate lines reverse direction; pick one.  When using
//     zig-zag order, the orientation of the matrices in alternate rows
//     will be rotated 180 degrees (this is normal -- simplifies wiring).
//   See example below for these values in action.
// Parameter 7 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 pixels)
//   NEO_GRB     Pixels are wired for GRB bitstream (v2 pixels)
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA v1 pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)

// Example with three 10x8 matrices (created using NeoPixel flex strip --
// these grids are not a ready-made product).  In this application we'di
// like to arrange the three matrices side-by-side in a wide display.
// The first matrix (tile) will be at the left, and the first pixel within
// that matrix is at the top left.  The matrices use zig-zag line ordering.
// There's only one row here, so it doesn't matter if we declare it in row
// or column order.  The matrices use 800 KHz (v2) pixels that expect GRB
// color data.

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, 1, 3, PIN,
                            NEO_TILE_TOP   + NEO_TILE_LEFT   + NEO_TILE_ROWS   + NEO_TILE_ZIGZAG +
                            NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB + NEO_KHZ800);

uint16_t textColor = matrix.Color(0, 255, 0);

Ball* ball = new Ball(5,15,1);
Ball* ball2 = new Ball(20,5,2);
Ball* ball3 = new Ball(12,13,3);

BallLight* game = new BallLight(&matrix, ball, ball2, ball3, FRAMERATE);


void setup() {
  Serial.begin(115200);
  
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(20);
  matrix.setTextColor(textColor);
  
  nextFrame = millis() + frameInterval;
 
}

int cursorX    = matrix.width();

int x0 = 16;
int r = 10;



void loop() {

  if (runAsFastAsYouCan || millis() >= nextFrame) {
    if (!runAsFastAsYouCan) {
      if (millis() - nextFrame <= frameInterval) nextFrame = millis() + frameInterval;
      else{
        runAsFastAsYouCan = true;
        Serial.println("Game logic and display cycle exceeds frameInterval.");
        Serial.println("Switching to uncapped framerate.");
      }
    }
    matrix.fillScreen(0);
    nextFrame = game->updateBallLight();
    matrix.show();
    
  }
}
