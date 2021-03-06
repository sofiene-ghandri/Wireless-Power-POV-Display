#include <xc.h>
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define IR PORTEbits.RE0

//Constant arrays forming the images
char ImgToShow=0;
int ImageTimer=0;
int ImageTimerOverflow=30; //Ticks (of ~300ms) for the timer to overflow
const char MaxImages=4; //max images -1
//--------------------WORLD--------------------
const char WORLDD[]={0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x38,0x3C,0x34,0x30,0x30,0x30,0x30,0x30,0x32,0x3A,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x37,0x37,0x3B,0x1F,0x1F,0x1F,0x0B,0x03,0x03,0x03,0x06,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x30,0x30,0x30,0x30,0x20,0x00,0x02,0x06,0x06,0x06,0x2F,0x37,0x3F,0x2F,0x3F,0x0F,0x07,0x07,0x37,0x06,0x27,0x27,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3E,0x3E,0x3C,0x3C,0x38,0x38,0x38,0x30,0x30,0x30,0x30,0x30,0x38,0x38,0x38,0x38,0x30,0x30,0x00,0x00,0x00,0x00,0x20};
const char WORLDC[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x30,0x30,0x30,0x3C,0x3C,0x3E,0x3E,0x3E,0x3F,0x3E,0x3F,0x3F,0x3F,0x3F,0x3F,0x3E,0x3E,0x3E,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3F,0x3F,0x1F,0x1F,0x3F,0x3F,0x3F,0x1F,0x1E,0x1F,0x17,0x17,0x37,0x27,0x27,0x27,0x07,0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x2F,0x2F,0x3F,0x3F,0x3F,0x07,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x30,0x38,0x3C,0x38,0x38,0x39,0x38,0x38,0x3C,0x3F,0x3F,0x3F,0x3E,0x3C,0x3C,0x3C,0x38,0x38,0x30,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const char WORLDB[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x02,0x00,0x00,0x00,0x00,0x22,0x00,0x06,0x06,0x02,0x0E,0x3C,0x33,0x26,0x34,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x28,0x30,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x38,0x2C,0x3C,0x3C,0x1E,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3E,0x3C,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x03,0x07,0x07,0x07,0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x03,0x00,0x10,0x10,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const char WORLDA[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x03,0x07,0x0F,0x1F,0x0F,0x0F,0x1F,0x3F,0x1F,0x0F,0x0F,0x1F,0x07,0x07,0x07,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00,0x10,0x30,0x38,0x3E,0x3E,0x3F,0x3F,0x3F,0x3F,0x3F,0x3E,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x30,0x38,0x3C,0x3C,0x3E,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x30,0x30,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

//--------------------ARROW--------------------
const char ARROWD[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x03,0x03,0x03,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x03,0x03,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x03,0x03,0x03,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const char ARROWC[]={0x00,0x03,0x03,0x03,0x07,0x07,0x0F,0x0F,0x0F,0x1F,0x1F,0x1F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x07,0x07,0x07,0x0F,0x0F,0x0F,0x1F,0x1F,0x1F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x07,0x07,0x0F,0x0F,0x0F,0x1F,0x1F,0x1F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const char ARROWB[]={0x00,0x00,0x00,0x00,0x20,0x20,0x20,0x30,0x30,0x30,0x38,0x38,0x3C,0x3C,0x3C,0x3E,0x3E,0x3E,0x3F,0x3F,0x3F,0x3F,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x20,0x30,0x30,0x30,0x38,0x38,0x3C,0x3C,0x3C,0x3E,0x3E,0x3E,0x3F,0x3F,0x3F,0x3F,0x3F,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x20,0x30,0x30,0x30,0x38,0x38,0x3C,0x3C,0x3C,0x3E,0x3E,0x3E,0x3F,0x3F,0x3F,0x3F,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const char ARROWA[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

//--------------------SMILE--------------------
const char SMILED[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x07,0x0F,0x1E,0x1C,0x3C,0x39,0x39,0x39,0x39,0x39,0x39,0x3C,0x1C,0x1E,0x0F,0x07,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x07,0x0F,0x1E,0x1C,0x1C,0x38,0x38,0x38,0x38,0x38,0x38,0x1C,0x1C,0x0E,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x07,0x0F,0x1E,0x1C,0x1C,0x38,0x38,0x38,0x38,0x38,0x38,0x1C,0x1C,0x0E,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x07,0x0F,0x1E,0x1C,0x1C,0x38,0x38,0x38,0x38,0x38,0x38,0x1C,0x1C,0x0E,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const char SMILEC[]={0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x3F,0x3F,0x38,0x20,0x00,0x00,0x18,0x18,0x38,0x30,0x20,0x20,0x20,0x30,0x38,0x18,0x18,0x00,0x20,0x38,0x3F,0x3F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x3F,0x3F,0x38,0x20,0x00,0x00,0x1C,0x1C,0x1C,0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x00,0x00,0x20,0x38,0x3F,0x3F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x3F,0x3F,0x38,0x20,0x00,0x00,0x1C,0x1C,0x1C,0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x00,0x00,0x20,0x38,0x3F,0x3F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x3F,0x3F,0x38,0x20,0x00,0x00,0x1C,0x1C,0x1C,0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x00,0x00,0x20,0x38,0x3F,0x3F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const char SMILEB[]={0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x3E,0x3F,0x0F,0x03,0x01,0x00,0x1C,0x1C,0x1C,0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x00,0x01,0x03,0x0F,0x3F,0x3E,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x3E,0x3F,0x0F,0x03,0x01,0x06,0x06,0x1E,0x1C,0x18,0x18,0x18,0x1C,0x0E,0x06,0x06,0x00,0x01,0x03,0x0F,0x3F,0x3E,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x3E,0x3F,0x0F,0x03,0x01,0x00,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x00,0x01,0x03,0x0F,0x3F,0x3E,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x3E,0x3F,0x0F,0x03,0x01,0x0C,0x0C,0x0E,0x07,0x03,0x03,0x03,0x07,0x0F,0x0C,0x0C,0x00,0x01,0x03,0x0F,0x3F,0x3E,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const char SMILEA[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x30,0x38,0x38,0x1C,0x1C,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x1C,0x1C,0x3C,0x38,0x30,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x38,0x3C,0x1C,0x1E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x1E,0x1C,0x3C,0x38,0x30,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x38,0x3C,0x1C,0x1E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x1E,0x1C,0x3C,0x38,0x30,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x38,0x3C,0x1C,0x1E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x1E,0x1C,0x3C,0x38,0x30,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

//--------------------CUBE--------------------
const char CUBED[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x0F,0x07,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x03,0x03,0x07,0x07,0x0E,0x0E,0x1E,0x1C,0x38,0x3C,0x1C,0x1C,0x0E,0x0E,0x0F,0x07,0x07,0x03,0x03,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00};
const char CUBEC[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x0F,0x1F,0x3F,0x3C,0x38,0x30,0x30,0x38,0x3E,0x3F,0x1F,0x0F,0x03,0x00,0x00,0x00,0x3F,0x3F,0x3F,0x3F,0x3F,0x00,0x00,0x00,0x3F,0x3F,0x3F,0x3F,0x3F,0x30,0x31,0x31,0x31,0x31,0x3F,0x3F,0x3F,0x3F,0x00,0x00,0x3F,0x3F,0x3F,0x3F,0x01,0x01,0x01,0x3F,0x3F,0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x0E,0x1E,0x3C,0x38,0x30,0x20,0x38,0x3F,0x3F,0x37,0x38,0x3C,0x3E,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x3F,0x3F,0x38,0x38,0x3C,0x1C,0x1E,0x0E,0x0F,0x07,0x07,0x03,0x03,0x01,0x01,0x03,0x03,0x03,0x27,0x27,0x27,0x3E,0x3E,0x3F,0x3F,0x1F,0x00,0x00,0x00};
const char CUBEB[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x3E,0x3F,0x3F,0x07,0x03,0x01,0x01,0x03,0x0F,0x3F,0x3F,0x3E,0x39,0x01,0x01,0x01,0x3F,0x3F,0x3F,0x3F,0x3F,0x01,0x01,0x01,0x3F,0x3F,0x3F,0x3F,0x3F,0x01,0x21,0x21,0x21,0x21,0x3F,0x3F,0x3F,0x3F,0x00,0x00,0x3F,0x3F,0x3F,0x3F,0x20,0x20,0x20,0x3F,0x3F,0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x1F,0x3F,0x3B,0x33,0x21,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x3F,0x3F,0x01,0x00,0x00,0x00,0x20,0x30,0x38,0x3C,0x3E,0x1F,0x0F,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x3E,0x3F,0x07,0x07,0x03,0x03,0x01,0x01,0x00,0x00,0x20,0x20,0x3F,0x3F,0x3F,0x20,0x20,0x20,0x00,0x00,0x01,0x01,0x03,0x3F,0x3F,0x3F,0x00,0x00,0x00};
const char CUBEA[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x30,0x30,0x30,0x38,0x38,0x38,0x3C,0x1C,0x1C,0x0E,0x0E,0x3E,0x3F,0x3F,0x0E,0x0E,0x1C,0x1C,0x1C,0x38,0x38,0x38,0x30,0x30,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x30,0x30,0x38,0x38,0x3C,0x1C,0x1E,0x3E,0x3E,0x3E,0x1C,0x1C,0x3C,0x38,0x38,0x30,0x30,0x30,0x20,0x20,0x20,0x00,0x00,0x00};

//--------------------GOODBYE--------------------
const char BYEBYED[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const char BYEBYEC[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x3F,0x3F,0x3F,0x00,0x00,0x00,0x00,0x30,0x3F,0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0x1F,0x1E,0x1E,0x1F,0x0F,0x01,0x00,0x00,0x00,0x00,0x0F,0x1F,0x1F,0x19,0x10,0x10,0x1F,0x1F,0x1F,0x00,0x00,0x00,0x11,0x11,0x11,0x11,0x11,0x1F,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F,0x00,0x00,0x00,0x00,0x03,0x0F,0x1F,0x1E,0x1E,0x1F,0x0F,0x01,0x00,0x00,0x00,0x00,0x08,0x18,0x10,0x10,0x10,0x10,0x18,0x1C,0x0F,0x0F,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x1F,0x1F,0x0F,0x00,0x00,0x07,0x1F,0x1F,0x1F,0x1F,0x03,0x00,0x01,0x0F,0x1F,0x1F,0x18,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x1F,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const char BYEBYEB[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x36,0x36,0x00,0x00,0x00,0x00,0x00,0x36,0x36,0x36,0x00,0x00,0x00,0x06,0x3E,0x3E,0x3C,0x38,0x18,0x18,0x38,0x3C,0x3E,0x3E,0x06,0x00,0x02,0x0E,0x1E,0x3E,0x38,0x20,0x20,0x3E,0x3E,0x3E,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x3E,0x3E,0x3E,0x00,0x02,0x02,0x02,0x02,0x02,0x3E,0x3E,0x3E,0x00,0x00,0x06,0x3E,0x3E,0x3C,0x38,0x18,0x18,0x38,0x3C,0x3E,0x3E,0x06,0x00,0x00,0x3C,0x3E,0x3E,0x22,0x22,0x22,0x06,0x0E,0x3C,0x3C,0x3C,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x3E,0x3E,0x3E,0x3E,0x3C,0x20,0x20,0x3C,0x3E,0x1E,0x3E,0x3E,0x38,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x3E,0x3E,0x3E,0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x3E,0x3E,0x3E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const char BYEBYEA[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

//Variables
//Timer variables
char Prev_IR_State=0;
char Pixel_Column_Time=120;  
char Pixel_Column_Count=0;

//Timer control
const char Desired_Pixel_Column_Count=150;
char Last_Pixel_Column_Count=150;
char delta=0;   //Delta to cause rotation
char ArrayIndex=0;  //Actual array index to be retrieved

int diff;
float newTimeDelta;
float Kp=0.2;
int timeNow;


void main(void) {
    
    TRISA=0b00000000; //Outputs 0-5 (first 6 bits) are used only.
    TRISB=0b00000000;
    TRISC=0b00000000;
    TRISD=0b00000000;
    TRISE=0b00000011; //PortE is input
       
    ADCON0=0b00000000;// No analog
    ADCON1=0b00001110;// No analog
    OPTION_REG=0b00000010; //Sets the timer prescaler
    INTCON=0b10100000;
    
    PORTA=0b00000000;
    PORTB=0b00000000;
    PORTC=0b00000000;
    PORTD=0b00000000;    
    
    delta=Desired_Pixel_Column_Count-1;
    
    while (1) {     
        //control loop
      if (!(Last_Pixel_Column_Count==Desired_Pixel_Column_Count)) {
          //Needs to update the timer
          diff = Desired_Pixel_Column_Count-Last_Pixel_Column_Count;
          timeNow=255-Pixel_Column_Time;
          newTimeDelta = (double) timeNow * ((double) diff/ (double) Desired_Pixel_Column_Count);
          newTimeDelta = newTimeDelta * Kp; //That's gonna be the delta applied
             
          if (abs(newTimeDelta)>1) {
              Pixel_Column_Time += newTimeDelta;
              if  (Pixel_Column_Time > 250) {
                  Pixel_Column_Time=250 ;
              }
          }
      }
      
      for (int i=0; i<30; i++) {
          __delay_ms(10); //300ms delay
      }   
      
      ImageTimer++;
      if (ImageTimer>ImageTimerOverflow) {
          ImageTimer=0;
          
          ImgToShow++;
          if (ImgToShow > MaxImages) {
              ImgToShow=0;
          }
      }
        
    }       
    
}


void interrupt LEDColumn(void) {
    if (Prev_IR_State==0 && IR==1) {
        //Complete turn = 1 frame
        delta--; //Causes rotation by 1 pixel column
        if (delta==-1) {
            delta=Desired_Pixel_Column_Count-1;
        }
        
        Last_Pixel_Column_Count=Pixel_Column_Count; //Stores for control purposes
        Pixel_Column_Count=0; //Resets the column count
        
     }
    if (Pixel_Column_Count<Desired_Pixel_Column_Count) { //Don't overflow the array
        ArrayIndex=Pixel_Column_Count+delta;
        if (ArrayIndex>=Desired_Pixel_Column_Count) {
            //overflow, wrap around
            ArrayIndex=ArrayIndex-Desired_Pixel_Column_Count;
        }
        if (ImgToShow==0) {
            PORTA=WORLDA[ArrayIndex];
            PORTB=WORLDB[ArrayIndex];
            PORTC=WORLDC[ArrayIndex];
            PORTD=WORLDD[ArrayIndex];
        } else if(ImgToShow==1) {
            PORTA=BYEBYEA[ArrayIndex];
            PORTB=BYEBYEB[ArrayIndex];
            PORTC=BYEBYEC[ArrayIndex];
            PORTD=BYEBYED[ArrayIndex];
        } else if(ImgToShow==2) {
            PORTA=ARROWA[ArrayIndex];
            PORTB=ARROWB[ArrayIndex];
            PORTC=ARROWC[ArrayIndex];
            PORTD=ARROWD[ArrayIndex];
        } else if(ImgToShow==3) {
            PORTA=SMILEA[ArrayIndex];
            PORTB=SMILEB[ArrayIndex];
            PORTC=SMILEC[ArrayIndex];
            PORTD=SMILED[ArrayIndex];
        } else if(ImgToShow==4) {
            PORTA=CUBEA[ArrayIndex];
            PORTB=CUBEB[ArrayIndex];
            PORTC=CUBEC[ArrayIndex];
            PORTD=CUBED[ArrayIndex];
        } 
    }
    Prev_IR_State=IR; //Updates the state of the IR detector
    INTCONbits.T0IF=0; //Timer didn't overflow
    TMR0=Pixel_Column_Time;   //Sets the timer
    Pixel_Column_Count++; //Updates the pixel column count
}