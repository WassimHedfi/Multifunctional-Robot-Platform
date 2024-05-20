
#include <LiquidCrystal_I2C.h>

unsigned long StepsRight = 0, StepsLeft = 0, TurnsRight = 0, TurnsLeft = 0;
int previous_right = 0, previous_left = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 column and 2 rows
unsigned long previous_millis = 0;

int Rdistance;
int Ldistance;

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
#define NORMAL_MOTOR_SPEED 200


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PC1, INPUT);
  pinMode(2, INPUT);

  lcd.init();  // initialize the lcd
  lcd.backlight();


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
  stop();
  display();
  previous_millis = millis();
  delay(5000);
  forward(150);
}



void forward(uint8_t speed) {
  analogWrite(ENABLE_1_PIN, speed - 15);  //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed - 15);  //Right Motor Speed
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
  // put your main code here, to run repeatedly:
  int right = digitalRead(2);
  int left = digitalRead(PC1);

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

  if ((Rdistance >= 3) || (Ldistance >= 3)) {
    stop();
  }
  //
  // if (millis() - previous_millis > 700) display();
}

void display() {
  lcd.clear();  // clear display
  lcd.setCursor(0, 0);
  lcd.print(" Encoders Test");
  lcd.setCursor(0, 1);  // move cursor to   (2, 1)
  lcd.print("  STOP at 3m");
}
