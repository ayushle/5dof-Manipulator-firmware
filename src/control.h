#include <Arduino.h>



// Defining the pins for the motors
#define DIR1 PA3
#define PWM1 PA1
#define encA1 PA2
#define encB1 PA0
#define PIN2_1 PB5
#define PIN2_2 PB4
#define encA2 0
#define encB2 0
#define PIN3_1 PB10
#define PIN3_2 PB2
#define encA3 0
#define encB3 0
#define DIR4 PA8
#define PWM4 PB15
#define encA4 PA14
#define encB4 PA13
#define DIR5 PB9
#define PWM5 PB8
#define encA5 0
#define encB5 PB6
#define DIR6 PA6
#define PWM6 PA7
#define encA6 PB0
#define encB6 PB1
// #define limit 0

class motor
{

  private:

  uint8_t direction, pwm; // The direction and PWM pins of the driver respectively

  public:

  // This is the constructor for the actuator_enable class
  motor(int direction, int pwm)
  {
    this->direction = direction;
    this->pwm = pwm;
  }
  void stop()
  {
    analogWrite(pwm, 0);
  }
  // This function is used to rotate the actuator clockwise
  void rotateClockwise(int speedPercentage)
  {
    digitalWrite(direction, HIGH);
    analogWrite(pwm, 255 * speedPercentage / 100);
  }

  // This function is used to rotate the actuator anti-clockwise
  void rotateAntiClockwise(int speedPercentage)
  {
    digitalWrite(direction, LOW);
    analogWrite(pwm, 255 * speedPercentage / 100);
  }
};

class linear_actuator
{

  private:

  int pin1, pin2; // The pins of the linear actuator

  public:

  // This is the constructor for the linear_actuator class
  linear_actuator(int pin1, int pin2)
  {
    this->pin1 = pin1;
    this->pin2 = pin2;
  }

  // This function is used to stop the actuator
  void stop()
  {
    analogWrite(this->pin1, 0);
    analogWrite(this->pin2, 0);
  }

  // This function is used to increase the length of the actuator
  void increaseLength()
  {
    analogWrite(this->pin1, 0);
    analogWrite(this->pin2, 204);
  }

  // This function is used to decrease the length of the actuator
  void decreaseLength()
  {
    analogWrite(this->pin2, 0);
    analogWrite(this->pin1, 204);
  }

};

class encoder
{
  private:

  volatile int lastEncoded = 0;
  long lastencoderValue = 0;
  int lastMSB = 0;
  int lastLSB = 0;
  uint8_t encA, encB; 

  public:
    volatile long encoderValue;

  encoder(int encA, int encB)
  {
    this->encA = encA;
    this->encB = encB;
    encoderValue = 0;
  }

  void updateEncoder()
  {
    int MSB = digitalRead(encA);
    int LSB = digitalRead(encB); 
    int encoded = (MSB << 1) |LSB; 
    int sum = (lastEncoded << 2) | encoded; 
    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
      encoderValue ++;
    if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
      encoderValue --;
    lastEncoded = encoded; 
  }
};

motor Link1(DIR1, PWM1);
linear_actuator Link2(PIN2_1, PIN2_2);
linear_actuator Link3(PIN3_1, PIN3_2);
motor Link4(DIR4, PWM4);
motor Link5(DIR5, PWM5);
motor Link6(DIR6, PWM6);

encoder encLink1(encA1, encB1);
encoder encLink2(encA2, encB2);
encoder encLink3(encA3, encB3);
encoder encLink4(encA4, encB4);
encoder encLink5(encA5, encB5);
encoder encLink6(encA6, encB6);



void intial_setup()
{ 
  pinMode(DIR1, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(encA1,INPUT);
  pinMode(encB1,INPUT);
  digitalWrite(encA1, HIGH); 
  digitalWrite(encB1, HIGH);
  pinMode(PIN2_1, OUTPUT);
  pinMode(PIN2_2, OUTPUT);
  pinMode(encA2,INPUT);
  pinMode(encB2,INPUT);
  digitalWrite(encA2, HIGH); 
  digitalWrite(encB2, HIGH);
  pinMode(PIN3_1, OUTPUT);
  pinMode(PIN3_2, OUTPUT);
  pinMode(encA3,INPUT);
  pinMode(encB3,INPUT);
  digitalWrite(encA3, HIGH); 
  digitalWrite(encB3, HIGH);
  pinMode(DIR4, OUTPUT);
  pinMode(PWM4, OUTPUT);
  pinMode(encA4,INPUT);
  pinMode(encB4,INPUT);
  digitalWrite(encA4, HIGH); 
  digitalWrite(encB4, HIGH);
  pinMode(DIR5, OUTPUT);
  pinMode(PWM5, OUTPUT);
  pinMode(encA5,INPUT);
  pinMode(encB5,INPUT);
  digitalWrite(encA5, HIGH); 
  digitalWrite(encB5, HIGH);
  pinMode(DIR6, OUTPUT);
  pinMode(PWM6, OUTPUT);
  pinMode(encA6,INPUT);
  pinMode(encB6,INPUT);
  digitalWrite(encA6, HIGH); 
  digitalWrite(encB6, HIGH);
  // pinMode(limit,INPUT_PULLUP);
}