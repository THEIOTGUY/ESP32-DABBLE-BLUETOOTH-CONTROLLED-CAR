// Code for joystick mode.

#define l1 27 //left motor 1
#define l2 26 //left motor 2
#define r1 33 //right motor 1
#define r2 32 //right motor 2
#define e1 14 //left enable pin for left motor
#define e2 25 //right enable pin for right motor

int lm = 0; //speed of left motor
int rm = 0; //speed of right motor

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

const int freq = 30000;
const int pwmChannel = 0;
const int pwmChannel2 = 1;
const int resolution = 8;
int dutyCycle = 200;

void setup() {

Dabble.begin(“ESP32”);

pinMode(l1, OUTPUT);
pinMode(l2, OUTPUT);
pinMode(r1, OUTPUT);
pinMode(r2, OUTPUT);
pinMode(e1, OUTPUT);
pinMode(e2, OUTPUT);

ledcSetup(pwmChannel, freq, resolution);
ledcAttachPin(e1, pwmChannel);
ledcAttachPin(e2, pwmChannel2);
}

void loop() {
Dabble.processInput();

ledcWrite(pwmChannel, lm);
ledcWrite(pwmChannel2, rm);

float xval = GamePad.getXaxisData();
float yval = GamePad.getYaxisData();

if(yval < 0){
digitalWrite(l1, HIGH);
digitalWrite(l2, LOW);
digitalWrite(r1, HIGH);
digitalWrite(r2, LOW);
lm = map(yval, 0, -7, 0, 200);
rm = map(yval, 0, -7, 0, 200);
}
else if(yval > 0) {
digitalWrite(l1, LOW);
digitalWrite(l2, HIGH);
digitalWrite(r1, LOW);
digitalWrite(r2, HIGH);

lm = map(yval, 0, 7, 0, 200);
rm = map(yval, 0, 7, 0, 200);
}
else {
lm = 0;
rm = 0;
}
if(xval < 0) {
int xMapped = map(xval, 0, -7, 0, 200);
lm = lm - xMapped;
rm = rm + xMapped;
if(lm < 0) {
lm = 0;
}
if(rm > 200) {
rm = 200;
}
}
    if(xval > 0) {
int xMapped = map(xval, 0, 7, 0, 200);

lm = lm + xMapped;
rm = rm - xMapped;

if(lm > 200) {
lm = 200;
}

if(rm < 0) {
rm = 0;
}
}

}
