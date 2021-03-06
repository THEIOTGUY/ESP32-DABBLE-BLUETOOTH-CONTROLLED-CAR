# ESP32 CONTROLLED BLUETOOTH CAR USING "DABBLE" ANDROID APP

##DESCRIPTION

Here we are using DABBLE app to control a esp32 bluetooth controlled car

## COMPONENTS REQUIRED

1. ESP32
2. 4WD CAR KIT (CAN ALSO USE 2WD CAR)
3. 4 LITHIUM ION BATTERIES
4. L298N MOTOR DRIVER 
5. ON/OFF SWITCH (SPST)
6. JUMPER WIRES

## DABBLE APP
![Screenshot_2022-07-06-22-14-34-65_b5a5c5cb02ca09c784c5d88160e2ec24](https://user-images.githubusercontent.com/102857010/177601706-05436d73-1647-422d-bf55-32cbf79b5b4e.jpg)

![2](https://user-images.githubusercontent.com/102857010/177602322-a4666f51-267a-4c4e-b76e-c9cc277f8696.jpg)

![3](https://user-images.githubusercontent.com/102857010/177602450-ab5a7ab3-741d-4437-98c4-4d4abf276e30.jpg)

## CODE

````
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
````
