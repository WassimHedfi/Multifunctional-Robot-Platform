#include <SoftwareSerial.h>
#define BT_NAME "BT_Master"
#define SLAVE_ADDRESS "0022,12,0237DF"  //98d3:31:8095c3

SoftwareSerial mySerial(9, 10);  // RX, TX

int leftButton = 5;         // D
int rightButton = 3;        // B
int higherSpeedButton = 2;  // A
int lowerSpeedButton = 4;   // C
int buzzerButton = 8;       // K
int xAxis = A0;
int yAxis = A1;
int buttons[] = { leftButton, rightButton, lowerSpeedButton, higherSpeedButton, buzzerButton };
char message;

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
    digitalWrite(buttons[i], HIGH);
  }
//  Serial.begin(38400);
  mySerial.begin(38400);
}

void loop() {
  int xVal = analogRead(xAxis);
  int yVal = analogRead(yAxis);

  if (600 <= yVal) {
    message = 'F';
    mySerial.write(message);
  } else if (yVal <= 400) {
    message = 'B';
    mySerial.write(message);
  } else if (xVal <= 400) {
    message = 'L';
    mySerial.write(message);
  } else if (600 <= xVal) {
    message = 'R';
    mySerial.write(message);
  } else if (digitalRead(higherSpeedButton) == LOW) {
    message = 'P';
    mySerial.write(message);
  } else if (digitalRead(lowerSpeedButton) == LOW) {
    message = 'M';
    mySerial.write(message);
  } else if (digitalRead(leftButton) == LOW) {
    message = 'l';
    mySerial.write(message);
  } else if (digitalRead(rightButton) == LOW) {
    message = 'r';
    mySerial.write(message);
  } else if (digitalRead(buzzerButton) == LOW) {
    message = 'K';
    mySerial.write(message);
  } else mySerial.write("S");
}
