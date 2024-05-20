#include <SoftwareSerial.h>

#define BT_NAME "BT_Slave"

SoftwareSerial mySerial(3, 4);  // RX, TX



char received;

int speed = 220;
#define ENABLE_1_PIN 6  // This should be a pwm (~) pin
#define MOTOR_1_INPUT_2 PB14
#define MOTOR_1_INPUT_1 PB15
#define MOTOR_2_INPUT_2 PB1
#define MOTOR_2_INPUT_1 PB2
#define ENABLE_2_PIN 5

#define ENABLE_4_PIN 9  // This should be a pwm (~) pin
#define MOTOR_4_INPUT_2 PC2
#define MOTOR_4_INPUT_1 PC3
#define MOTOR_3_INPUT_2 PB7
#define MOTOR_3_INPUT_1 PH1
#define ENABLE_3_PIN 10  // This should be a pwm (~) pin




void setup() {
  Serial.begin(38400);

  mySerial.begin(38400);
  Serial.println("Arduino receiver");

  mySerial.print("AT\r\n");
  delay(200);
  mySerial.print("AT+RMAAD\r\n");
  delay(200);
  mySerial.print("AT+ADDR?\r\n");
  delay(200);

  mySerial.print("AT+NAME=" + String(BT_NAME) + "\r\n");
  delay(200);
  mySerial.print("AT+PSWD=\"1234\"\r\n");
  delay(200);
  mySerial.print("AT+ROLE?\r\n");
  delay(200);
  mySerial.print("AT+UART=38400,0,0\r\n");

  delay(500);

  pinMode(MOTOR_1_INPUT_1, OUTPUT);  // DEFINE
  pinMode(MOTOR_1_INPUT_2, OUTPUT);  // MOTOR

  pinMode(MOTOR_2_INPUT_1, OUTPUT);  // DRIVER
  pinMode(MOTOR_2_INPUT_2, OUTPUT);  // PINS

  pinMode(ENABLE_1_PIN, OUTPUT);  // AS
  pinMode(ENABLE_2_PIN, OUTPUT);

  pinMode(MOTOR_3_INPUT_1, OUTPUT);  // DEFINE
  pinMode(MOTOR_3_INPUT_2, OUTPUT);  // MOTOR

  pinMode(MOTOR_4_INPUT_1, OUTPUT);  // DRIVER
  pinMode(MOTOR_4_INPUT_2, OUTPUT);  // PINS

  pinMode(ENABLE_3_PIN, OUTPUT);  // AS

  pinMode(ENABLE_4_PIN, OUTPUT);  // OUTPUT
}

void loop() {
  if (mySerial.available()) {
    received = mySerial.read();
    Serial.println(received);
  }

  switch (received) {
    case 'F':
      forward(speed);
      break;

    case 'B':
      reverse(speed);
      break;

    case 'R':
      sharp_right(speed);
      break;

    case 'L':
      sharp_left(speed);
      break;

    case 'P':
      slide_right(speed);
      break;

    case 'M':
      slide_left(speed);
      break;

    case 'l':
      lateral_left(speed);
      break;

    case 'r':
      lateral_right(speed);
      break;

    case 'S':
     stop();
      break;
  }
}



void forward(uint8_t speed) {
  analogWrite(ENABLE_1_PIN, speed - 20);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed - 20);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);       //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);       //Right Motor Speed

  digitalWrite(MOTOR_1_INPUT_1, LOW);
  digitalWrite(MOTOR_1_INPUT_2, HIGH);

  digitalWrite(MOTOR_2_INPUT_1, LOW);
  digitalWrite(MOTOR_2_INPUT_2, HIGH);

  digitalWrite(MOTOR_3_INPUT_1, LOW);
  digitalWrite(MOTOR_3_INPUT_2, HIGH);

  digitalWrite(MOTOR_4_INPUT_1, LOW);
  digitalWrite(MOTOR_4_INPUT_2, HIGH);
}

void sharp_right(uint8_t speed) {
  analogWrite(ENABLE_1_PIN, speed - 20);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed - 20);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);       //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);       //Right Motor Speed

  digitalWrite(MOTOR_1_INPUT_1, HIGH);
  digitalWrite(MOTOR_1_INPUT_2, LOW);

  digitalWrite(MOTOR_2_INPUT_1, HIGH);
  digitalWrite(MOTOR_2_INPUT_2, LOW);

  digitalWrite(MOTOR_3_INPUT_1, LOW);
  digitalWrite(MOTOR_3_INPUT_2, HIGH);

  digitalWrite(MOTOR_4_INPUT_1, LOW);
  digitalWrite(MOTOR_4_INPUT_2, HIGH);
}

void sharp_left(uint8_t speed) {
  analogWrite(ENABLE_1_PIN, speed - 20);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed - 20);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);       //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);       //Right Motor Speed

  digitalWrite(MOTOR_1_INPUT_1, LOW);
  digitalWrite(MOTOR_1_INPUT_2, HIGH);

  digitalWrite(MOTOR_2_INPUT_1, LOW);
  digitalWrite(MOTOR_2_INPUT_2, HIGH);

  digitalWrite(MOTOR_3_INPUT_1, HIGH);
  digitalWrite(MOTOR_3_INPUT_2, LOW);

  digitalWrite(MOTOR_4_INPUT_1, HIGH);
  digitalWrite(MOTOR_4_INPUT_2, LOW);
}

void reverse(uint8_t speed) {
  analogWrite(ENABLE_1_PIN, speed - 20);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed - 20);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);       //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);       //Right Motor Speed

  digitalWrite(MOTOR_1_INPUT_2, LOW);
  digitalWrite(MOTOR_1_INPUT_1, HIGH);

  digitalWrite(MOTOR_2_INPUT_2, LOW);
  digitalWrite(MOTOR_2_INPUT_1, HIGH);

  digitalWrite(MOTOR_3_INPUT_2, LOW);
  digitalWrite(MOTOR_3_INPUT_1, HIGH);

  digitalWrite(MOTOR_4_INPUT_2, LOW);
  digitalWrite(MOTOR_4_INPUT_1, HIGH);
}

void lateral_right(uint8_t speed) {
  analogWrite(ENABLE_1_PIN, speed - 20);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed - 20);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);       //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);       //Right Motor Speed

  digitalWrite(MOTOR_1_INPUT_1, HIGH);
  digitalWrite(MOTOR_1_INPUT_2, LOW);

  digitalWrite(MOTOR_2_INPUT_1, LOW);
  digitalWrite(MOTOR_2_INPUT_2, HIGH);

  digitalWrite(MOTOR_3_INPUT_1, LOW);
  digitalWrite(MOTOR_3_INPUT_2, HIGH);

  digitalWrite(MOTOR_4_INPUT_1, HIGH);
  digitalWrite(MOTOR_4_INPUT_2, LOW);
}

void lateral_left(uint8_t speed) {
  analogWrite(ENABLE_1_PIN, speed - 20);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed - 20);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);       //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);       //Right Motor Speed

  digitalWrite(MOTOR_1_INPUT_1, LOW);
  digitalWrite(MOTOR_1_INPUT_2, HIGH);

  digitalWrite(MOTOR_2_INPUT_1, HIGH);
  digitalWrite(MOTOR_2_INPUT_2, LOW);

  digitalWrite(MOTOR_3_INPUT_1, HIGH);
  digitalWrite(MOTOR_3_INPUT_2, LOW);

  digitalWrite(MOTOR_4_INPUT_1, LOW);
  digitalWrite(MOTOR_4_INPUT_2, HIGH);
}


void slide_right(uint8_t speed) {
  analogWrite(ENABLE_1_PIN, speed - 20);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed - 20);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);       //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);       //Right Motor Speed

  digitalWrite(MOTOR_1_INPUT_1, HIGH);
  digitalWrite(MOTOR_1_INPUT_2, HIGH);

  digitalWrite(MOTOR_2_INPUT_1, LOW);
  digitalWrite(MOTOR_2_INPUT_2, HIGH);

  digitalWrite(MOTOR_3_INPUT_1, LOW);
  digitalWrite(MOTOR_3_INPUT_2, HIGH);

  digitalWrite(MOTOR_4_INPUT_1, HIGH);
  digitalWrite(MOTOR_4_INPUT_2, HIGH);
}

void slide_left(uint8_t speed) {
  analogWrite(ENABLE_1_PIN, speed - 20);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed - 20);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);       //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);       //Right Motor Speed

  digitalWrite(MOTOR_1_INPUT_1, LOW);
  digitalWrite(MOTOR_1_INPUT_2, HIGH);

  digitalWrite(MOTOR_2_INPUT_1, HIGH);
  digitalWrite(MOTOR_2_INPUT_2, HIGH);

  digitalWrite(MOTOR_3_INPUT_1, HIGH);
  digitalWrite(MOTOR_3_INPUT_2, HIGH);

  digitalWrite(MOTOR_4_INPUT_1, LOW);
  digitalWrite(MOTOR_4_INPUT_2, HIGH);
}



void stop() {

  digitalWrite(MOTOR_1_INPUT_1, HIGH);
  digitalWrite(MOTOR_1_INPUT_2, HIGH);

  digitalWrite(MOTOR_2_INPUT_1, HIGH);
  digitalWrite(MOTOR_2_INPUT_2, HIGH);

  digitalWrite(MOTOR_3_INPUT_1, HIGH);
  digitalWrite(MOTOR_3_INPUT_2, HIGH);

  digitalWrite(MOTOR_4_INPUT_1, HIGH);
  digitalWrite(MOTOR_4_INPUT_2, HIGH);
}
