#include <Servo.h>

Servo servo;  // create servo object to control a servo

#define buzzer PA1
#define ENABLE_1_PIN 6  // This should be a pwm (~) pin
#define MOTOR_1_INPUT_2 PB14
#define MOTOR_1_INPUT_1 PB15
#define MOTOR_2_INPUT_2 PB1
#define MOTOR_2_INPUT_1 PB2
#define ENABLE_2_PIN 5

int trigPin = PA4;  // TRIG pin
int echoPin = PB0;  // ECHO pin

int red_led = PA14;
int yellow_led = PA15;

float duration_us, distance_cm, left_distance, right_distance;

int turn_90deg_time = 700;

unsigned long current_time;
unsigned long previous_time;

int travel = 1;


#define ENABLE_4_PIN 9  // This should be a pwm (~) pin
#define MOTOR_4_INPUT_2 PC2
#define MOTOR_4_INPUT_1 PC3
#define MOTOR_3_INPUT_2 PB7
#define MOTOR_3_INPUT_1 PH1
#define ENABLE_3_PIN 10  // This should be a pwm (~) pin



#define MAX_MOTOR_SPEED 200
#define SLOW_MOTOR_SPEED 80
#define NORMAL_MOTOR_SPEED 200



void setup() {
  // Motors
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


  Serial.begin(9600);

  // Ultrason
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // LED
  pinMode(red_led, OUTPUT);
  digitalWrite(red_led, LOW);

  pinMode(yellow_led, OUTPUT);
  digitalWrite(yellow_led, LOW);

  // Servo
  servo.attach(PA0);  // attaches the servo on pin 9 to the servo objectư
  servo.write(90);
  stop();
  delay(10000);
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

void sharp_Right(uint8_t speed) {
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








/*
 * Created by ArduinoGetStarted, https://arduinogetstarted.com
 *
 * Arduino - Ultrasonic Sensor HC-SR04
 *
 * Wiring: Ultrasonic Sensor -> Arduino:
 * - VCC  -> 5VDC
 * - TRIG -> Pin 9
 * - ECHO -> Pin 8
 * - GND  -> GND
 *
 * Tutorial is available here: https://arduinogetstarted.com/tutorials/arduino-ultrasonic-sensor
 */



void loop() {
  // begin serial port

  switch (travel) {
    case 1:
      get_distance();
      forward(NORMAL_MOTOR_SPEED);
      if (distance_cm < 40) {
        analogWrite(buzzer, 170);
        delay(500);
        analogWrite(buzzer,0);
        travel = 2;
        reverse(150);
        delay(600);
        stop();
        delay(2000);
        previous_time = millis();
        digitalWrite(red_led, HIGH);
      }
      break;


    case 2:
      get_distance();
      current_time = millis();
      lateral_right(NORMAL_MOTOR_SPEED);

      if (current_time - previous_time > 2000) {
        analogWrite(buzzer, 170);
        delay(300);
        analogWrite(buzzer, 0);

        travel = 3;
        stop();
        delay(1000);
        previous_time = millis();
      }
      if (distance_cm > 100) {
        travel = 1;
        stop();
        delay(1000);
        lateral_right(NORMAL_MOTOR_SPEED);
        delay(500);
        digitalWrite(red_led, LOW);
      }
      break;

    case 3:
      get_distance();
      current_time = millis();
      lateral_left(NORMAL_MOTOR_SPEED);
      if (current_time - previous_time > 4000) {
        analogWrite(buzzer, 170);
        delay(300);
        analogWrite(buzzer, 0);

        travel = 4;
        stop();
        delay(1000);
      }
      if (distance_cm > 100) {
        travel = 1;
        stop();
        delay(1000);
        lateral_left(NORMAL_MOTOR_SPEED);
        delay(500);
        digitalWrite(red_led, LOW);
      }
      break;

    case 4:

      servo.write(0);
      delay(500);
      get_distance();
      right_distance = distance_cm;
      delay(200);

      servo.write(180);
      delay(500);
      get_distance();
      left_distance = distance_cm;
      delay(200);

      if (right_distance >= left_distance)
        travel = 5;
      else travel = 6;
      analogWrite(buzzer, 170);
      delay(300);
      analogWrite(buzzer, 0);
      delay(200);
      analogWrite(buzzer, 170);
      delay(300);
      analogWrite(buzzer, 0);


      break;

    case 5:
      sharp_Right(NORMAL_MOTOR_SPEED);
      delay(turn_90deg_time);
      travel = 1;
      stop();
      delay(1000);
      servo.write(90);
      delay(300);
      digitalWrite(red_led, LOW);

      break;

    case 6:
      sharp_left(NORMAL_MOTOR_SPEED);
      delay(turn_90deg_time);
      travel = 1;
      stop();
      delay(1000);
      servo.write(90);
      delay(300);
      digitalWrite(red_led, LOW);
      break;
  }
}

void get_distance() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
}
