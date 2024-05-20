/*
ROBOTHON ELECTRONIX ENSTAB
Workshop 3 : Motors and drivers
Copy and Paste this code on your Arduino IDE


This code is delicately typed by the ELECTRONIX Club for whom this may be of concern
HEDFI Wassim.
*/



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




#define MAX_MOTOR_SPEED 200
#define SLOW_MOTOR_SPEED 80
#define NORMAL_MOTOR_SPEED 220



void setup() {
  pinMode(MOTOR_1_INPUT_1, OUTPUT);  // DEFINE
  pinMode(MOTOR_1_INPUT_2, OUTPUT);  // MOTOR

  pinMode(MOTOR_2_INPUT_1, OUTPUT);  // DRIVER
  pinMode(MOTOR_2_INPUT_2, OUTPUT);  // PINS

  pinMode(ENABLE_1_PIN, OUTPUT);     // AS
  pinMode(ENABLE_2_PIN, OUTPUT);

  pinMode(MOTOR_3_INPUT_1, OUTPUT);  // DEFINE
  pinMode(MOTOR_3_INPUT_2, OUTPUT);  // MOTOR

  pinMode(MOTOR_4_INPUT_1, OUTPUT);  // DRIVER
  pinMode(MOTOR_4_INPUT_2, OUTPUT);  // PINS

  pinMode(ENABLE_3_PIN, OUTPUT);     // AS

  pinMode(ENABLE_4_PIN, OUTPUT);     // OUTPUT
}

void forward(uint8_t speed) {
  analogWrite(ENABLE_1_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);  //Right Motor Speed

  digitalWrite(MOTOR_1_INPUT_1, LOW);
  digitalWrite(MOTOR_1_INPUT_2, HIGH);

  digitalWrite(MOTOR_2_INPUT_1, LOW);
  digitalWrite(MOTOR_2_INPUT_2, HIGH);

  digitalWrite(MOTOR_3_INPUT_1, LOW);
  digitalWrite(MOTOR_3_INPUT_2, HIGH);

  digitalWrite(MOTOR_4_INPUT_1, LOW);
  digitalWrite(MOTOR_4_INPUT_2, HIGH);
}

void sharp_Right(uint8_t speed) {
  analogWrite(ENABLE_1_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);  //Right Motor Speed

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
  analogWrite(ENABLE_1_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);  //Right Motor Speed

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
  analogWrite(ENABLE_1_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);  //Right Motor Speed

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
  analogWrite(ENABLE_1_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);  //Right Motor Speed

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
  analogWrite(ENABLE_1_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);  //Right Motor Speed

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
  analogWrite(ENABLE_1_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);  //Right Motor Speed

  digitalWrite(MOTOR_1_INPUT_1, HIGH);
  digitalWrite(MOTOR_1_INPUT_2, HIGH);

  digitalWrite(MOTOR_2_INPUT_1, LOW);
  digitalWrite(MOTOR_2_INPUT_2, HIGH);

  digitalWrite(MOTOR_3_INPUT_1, LOW);
  digitalWrite(MOTOR_3_INPUT_2, HIGH);

  digitalWrite(MOTOR_4_INPUT_1, HIGH);
  digitalWrite(MOTOR_4_INPUT_2, HIGH);
}

void slide_right_back(uint8_t speed) {
  analogWrite(ENABLE_1_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);  //Right Motor Speed

  digitalWrite(MOTOR_1_INPUT_1, HIGH);
  digitalWrite(MOTOR_1_INPUT_2, HIGH);

  digitalWrite(MOTOR_2_INPUT_1, HIGH);
  digitalWrite(MOTOR_2_INPUT_2, LOW);

  digitalWrite(MOTOR_3_INPUT_1, HIGH);
  digitalWrite(MOTOR_3_INPUT_2, LOW);

  digitalWrite(MOTOR_4_INPUT_1, HIGH);
  digitalWrite(MOTOR_4_INPUT_2, HIGH);
}

void slide_left(uint8_t speed) {
  analogWrite(ENABLE_1_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);  //Right Motor Speed

  digitalWrite(MOTOR_1_INPUT_1, LOW);
  digitalWrite(MOTOR_1_INPUT_2, HIGH);

  digitalWrite(MOTOR_2_INPUT_1, HIGH);
  digitalWrite(MOTOR_2_INPUT_2, HIGH);

  digitalWrite(MOTOR_3_INPUT_1, HIGH);
  digitalWrite(MOTOR_3_INPUT_2, HIGH);

  digitalWrite(MOTOR_4_INPUT_1, LOW);
  digitalWrite(MOTOR_4_INPUT_2, HIGH);
}

void slide_left_back(uint8_t speed) {
  analogWrite(ENABLE_1_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed);  //Right Motor Speed
  analogWrite(ENABLE_3_PIN, speed);  //Left Motor Speed
  analogWrite(ENABLE_4_PIN, speed);  //Right Motor Speed

  digitalWrite(MOTOR_1_INPUT_1, HIGH);
  digitalWrite(MOTOR_1_INPUT_2, LOW);

  digitalWrite(MOTOR_2_INPUT_1, HIGH);
  digitalWrite(MOTOR_2_INPUT_2, HIGH);

  digitalWrite(MOTOR_3_INPUT_1, HIGH);
  digitalWrite(MOTOR_3_INPUT_2, HIGH);

  digitalWrite(MOTOR_4_INPUT_1, HIGH);
  digitalWrite(MOTOR_4_INPUT_2, LOW);
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






void loop() {
  stop();
  delay(2000);
  forward(NORMAL_MOTOR_SPEED);
  delay(2000);
  reverse(NORMAL_MOTOR_SPEED);
  delay(2000);
  sharp_Right(NORMAL_MOTOR_SPEED);
  delay(2000);
  sharp_left(NORMAL_MOTOR_SPEED);
  delay(2000);
  lateral_right(NORMAL_MOTOR_SPEED);
  delay(2000);
  lateral_left(NORMAL_MOTOR_SPEED);
  delay(2000);
  slide_right(NORMAL_MOTOR_SPEED);
  delay(2000);
  slide_right_back(NORMAL_MOTOR_SPEED);
  delay(2000);
  slide_left(NORMAL_MOTOR_SPEED);
  delay(2000);
  slide_left_back(NORMAL_MOTOR_SPEED);
  delay(2000);
  stop();
  delay(10000);
}
