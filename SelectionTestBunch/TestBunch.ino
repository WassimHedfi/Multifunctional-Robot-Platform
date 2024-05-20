
#include <Wire.h>
#include <MPU9250_WE.h>
#define MPU9250_ADDR 0x68

/* There are several ways to create your MPU9250 object:
 * MPU9250_WE myMPU9250 = MPU9250_WE()              -> uses Wire / I2C Address = 0x68
 * MPU9250_WE myMPU9250 = MPU9250_WE(MPU9250_ADDR)  -> uses Wire / MPU9250_ADDR
 * MPU9250_WE myMPU9250 = MPU9250_WE(&wire2)        -> uses the TwoWire object wire2 / MPU9250_ADDR
 * MPU9250_WE myMPU9250 = MPU9250_WE(&wire2, MPU9250_ADDR) -> all together
 * Successfully tested with two I2C busses on an ESP32
 */
MPU9250_WE myMPU9250 = MPU9250_WE(MPU9250_ADDR);
#include <SoftwareSerial.h>

#define BT_NAME "BT_Slave"

SoftwareSerial mySerial(3, 4);  // RX, TX



char received;

int speed = 220;


#include <Servo.h>
#include "DHT.h"

// DHT
#define DHT22_PIN 11
DHT dht22(DHT22_PIN, DHT22);

// LCD

unsigned long StepsRight = 0, StepsLeft = 0, TurnsRight = 0, TurnsLeft = 0;
int previous_right = 0, previous_left = 0;

unsigned long previous_millis = 0;
int numMeter;
int Rdistance;
int Ldistance;


int mode = 0;
int modeBegin = 0;

int switchButton = 8;
int stopButton = 7;
int switch_val = 1;
int stop_val = 1;


// Radar
const int startingAngle = 90;

const int minimumAngle = 15;

const int maximumAngle = 165;

const int rotationSpeed = 1;

// Autonomous
Servo servo;  // create servo object to control a servo


#define ENABLE_1_PIN 6  // This should be a pwm (~) pin
#define MOTOR_1_INPUT_2 PB14
#define MOTOR_1_INPUT_1 PB15
#define MOTOR_2_INPUT_2 PB1
#define MOTOR_2_INPUT_1 PB2
#define ENABLE_2_PIN 5

int TriggerPin = PA4;  // TRIG pin
int EchoPin = PB0;     // ECHO pin

int red_led = PA15;
int yellow_led = PA14;

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

//--------------------------------------------------------------------------------  SetUP  -------------------------------------------------------
//-------------------------------------------------------------------------------- Functions ----------------------------------------------------



void setup() {
  // put your setup code here, to run once:
  pinMode(PC1, INPUT);
  pinMode(2, INPUT);
  Wire.begin();


  pinMode(switchButton, INPUT_PULLUP);
  pinMode(stopButton, INPUT_PULLUP);

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
  mySerial.begin(38400);


  // Ultrason
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  // LED
  pinMode(red_led, OUTPUT);
  digitalWrite(red_led, LOW);

  pinMode(yellow_led, OUTPUT);
  digitalWrite(yellow_led, LOW);

  // Servo
  servo.attach(PA0);  // attaches the servo on pin 9 to the servo objectư
  servo.write(90);
  stop();
  //
  // DHT
  dht22.begin();  // initialize the DHT22 sensor

  // Radar


   myMPU9250.autoOffsets();
  
  myMPU9250.setSampleRateDivider(5);

  myMPU9250.setAccRange(MPU9250_ACC_RANGE_2G);


  myMPU9250.enableAccDLPF(true);

  myMPU9250.setAccDLPF(MPU9250_DLPF_6);

}

//--------------------------------------------------------------------------------  MAIN  -------------------------------------------------------
//-------------------------------------------------------------------------------- LOOP ----------------------------------------------------


void loop() {
  // put your main code here, to run repeatedly:
  switch (mode) {

    case 0:
      digitalWrite(yellow_led, HIGH);
      switch_val = digitalRead(switchButton);
      if (switch_val == 0) {
        modeBegin += 1;
        if (modeBegin > 6) modeBegin = 1;
        ledR(modeBegin);
      }

      stop_val = digitalRead(stopButton);
      if (stop_val == 0) {
        mode = modeBegin;
        digitalWrite(yellow_led, LOW);
        delay(500);
        ledY(mode);
      }
      break;

    // Radar
    case 1:
      Radar();
      if (digitalRead(stopButton) == 0) {
        mode = 0;
        init_bot();
      }

      break;

    // Autonomous
    case 2:
      maze();
      if (digitalRead(stopButton) == LOW) {
        mode = 0;
        init_bot();
      }

      break;

      // Encoder

    case 3:
      encoderSet();
      break;


    case 7:
      Encoders();

      if (digitalRead(stopButton) == LOW) {
        mode = 0;
        init_bot();
      }

      break;

    // Movement Loop
    case 4:
      loopMove();

      if (digitalRead(stopButton) == LOW) {
        mode = 0;
        init_bot();
      }

      break;

    // DHT
    case 5:
      DHT22_fun();
      if (digitalRead(stopButton) == LOW) {
        mode = 0;
        init_bot();
      }

      break;

    case 6:
      IMU();
      if (digitalRead(stopButton) == LOW) {
        mode = 0;
        init_bot();
      }
      break;
  }
}



//--------------------------------------------------------------------------------  BOT  -------------------------------------------------------
//-------------------------------------------------------------------------------- Functions ----------------------------------------------------

void RC() {
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
      sharp_Right(speed);
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

void commit_bot() {
  switch (mode) {
    case 1:
      break;

    case 2:
      break;


    case 6:
      break;

    case 4:
      break;

    case 5:
      break;
  }
  delay(3000);
}


void init_bot() {
  stop();
  servo.write(90);
  delay(1000);
}



//--------------------------------------------------------------------------------  Motors  -------------------------------------------------------
//-------------------------------------------------------------------------------- Functions ----------------------------------------------------

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

//__________________________________________________________________________________________________________________________________________________________________



//--------------------------------------------------------------------------------  Encoder  -------------------------------------------------------
//-------------------------------------------------------------------------------- Functions ----------------------------------------------------

void Encoders() {
  int right = digitalRead(2);
  int left = digitalRead(PC1);
  forward(180);
  if (right != previous_right) {
    StepsRight += 1;
    previous_right = right;
  }
  if (left != previous_left) {
    StepsLeft += 1;
    previous_left = left;
  }

  TurnsRight = StepsRight / 40;
  TurnsLeft = StepsLeft / 40;

  Rdistance = TurnsRight * 3.14 * 0.08;
  Ldistance = TurnsLeft * 3.14 * 0.08;

  if ((Rdistance >= numMeter) || (Ldistance >= numMeter)) {
    stop();
  }
}


//--------------------------------------------------------------------------------  Maze  -------------------------------------------------------
//-------------------------------------------------------------------------------- Functions ----------------------------------------------------


void maze() {

  switch (travel) {
    case 1:
      get_distance();
      forward(NORMAL_MOTOR_SPEED);
      if (distance_cm < 40) {
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
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(EchoPin, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;

  // print the value to Serial Monitor
}


void encoderSet() {
  StepsRight = 0;
  StepsLeft = 0;
  analogWrite(PA1, 120);
  while (digitalRead(stopButton)) {}

  delay(500);
  analogWrite(PA1, 30);


  numMeter = 0;

  while (digitalRead(stopButton)) {

    switch_val = digitalRead(switchButton);

    if (switch_val == 0) {
      numMeter += 1;


      if (numMeter > 9) numMeter = 0;

      if (numMeter >= 1)
        ledR(numMeter);
    }
  }

  ledY(numMeter);
  analogWrite(PA1, 0);

  mode = 7;
}


// -------------------------------------------------------------------------- Loop Movement   ------------------------------------------------
//------------------------------------------------------------------------------ Functions  -------------------------------------------------


void loopMove() {
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

  slide_left(NORMAL_MOTOR_SPEED);
  delay(2000);

  stop();
  delay(10000);
}

// -------------------------------------------------------------------------- DHT22   ------------------------------------------------
//------------------------------------------------------------------------- Functions  -------------------------------------------------


void DHT22_fun() {
  // wait a few seconds between measurements.
  delay(1000);

  // read humidity
  float humi = dht22.readHumidity();
  // read temperature as Celsius
  float tempC = dht22.readTemperature();
  // read temperature as Fahrenheit
  float tempF = dht22.readTemperature(true);

  // check if any reads failed
  if (isnan(humi) || isnan(tempC) || isnan(tempF)) {
    // Serial.println("Failed to read from DHT22 sensor!");
  } else {
    //Serial.print("DHT22# Humidity: ");
    //Serial.print(humi);
    //Serial.print("%");

    //Serial.print("  |  ");

    //Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print(",");

    Serial.print(humi);
    Serial.print("\n");


    //Serial.print("°C ~ ");
    //Serial.print(tempF);
    //Serial.println("°F");
  }
}

// -------------------------------------------------------------------------- IMU   ------------------------------------------------
//------------------------------------------------------------------------- Functions  -------------------------------------------------


void IMU() {
  xyzFloat accRaw = myMPU9250.getAccRawValues();
  xyzFloat accCorrRaw = myMPU9250.getCorrectedAccRawValues();
  xyzFloat gValue = myMPU9250.getGValues();
  float resultantG = myMPU9250.getResultantG(gValue);

 // Serial.print("axex,");
  Serial.print(gValue.x);
  Serial.print(",");
  Serial.print(gValue.y);
  Serial.print(",");
  Serial.print(gValue.z);
  Serial.print("\n");
  
  delay(10);
}


// -------------------------------------------------------------------------- Radar   ------------------------------------------------
//------------------------------------------------------------------------- Functions  -------------------------------------------------
void Radar() {
  static int motorAngle = startingAngle;

  static int motorRotateAmount = rotationSpeed;

  servo.write(motorAngle);

  delay(10);

  SerialOutput(motorAngle, CalculateDistance());

  motorAngle += motorRotateAmount;


  if (motorAngle <= minimumAngle || motorAngle >= maximumAngle) {
    motorRotateAmount = -motorRotateAmount;
  }
}


int CalculateDistance(void)

{
  digitalWrite(TriggerPin, HIGH);

  delayMicroseconds(10);

  digitalWrite(TriggerPin, LOW);

  long duration = pulseIn(EchoPin, HIGH);

  float distance = duration * 0.017F;

  return int(distance);
}

void SerialOutput(const int angle, const int distance)

{

  String angleString = String(angle);

  String distanceString = String(distance);

  Serial.println(angleString + "," + distanceString);
}


void ledR(int num) {
  for (int i = 0; i < num; i++) {
    digitalWrite(red_led, HIGH);
    delay(500);
    digitalWrite(red_led, LOW);
    delay(300);
  }
}

void ledY(int num) {
  for (int i = 0; i < num; i++) {
    digitalWrite(yellow_led, HIGH);
    delay(500);
    digitalWrite(yellow_led, LOW);
    delay(300);
  }
}
