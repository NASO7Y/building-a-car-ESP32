#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

#define in1 25
#define in2 26
#define in3 27
#define in4 14

#define ena 32
#define enb 33

#define speed 255   /*max speed*/

int pwm = 1000; /* 1 KHz */
int pwm_resolution = 8;
int ena_pwm_channel = 4;
int enb_pwm_channel = 5;

void Move(int right_wheels_speed, int left_wheels_speed)
{
  if (right_wheels_speed > 0)
  {
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
  }
  else if (right_wheels_speed < 0)
  {
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);    
  }
  
  if (left_wheels_speed > 0)
  {
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);      
  }
  else if (left_wheels_speed < 0)
  {
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);    
  }

  else
  {
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW); 
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);      
  }
  
  ledcWrite(ena_pwm_channel, speed);
  ledcWrite(enb_pwm_channel, speed);  
}

void setUpPinModes()
{
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);

  //Set up PWM for speed
  ledcSetup(ena_pwm_channel, pwm, pwm_resolution);
  ledcSetup(enb_pwm_channel, pwm, pwm_resolution);  
  ledcAttachPin(ena, ena_pwm_channel);
  ledcAttachPin(enb, enb_pwm_channel);
}

void setup()
{
  setUpPinModes();
  Dabble.begin("MyBluetoothCar"); 
}

void loop()
{
  int right_wheels_speed=0;
  int left_wheels_speed=0;
  Dabble.processInput();
  if (GamePad.isUpPressed())
  {
    right_wheels_speed = speed;
    left_wheels_speed = speed;
  }

  if (GamePad.isDownPressed())
  {
    right_wheels_speed = -speed;
    left_wheels_speed = -speed;
  }

  if (GamePad.isLeftPressed())
  {
    right_wheels_speed = speed;
    left_wheels_speed = -speed;
  }

  if (GamePad.isRightPressed())
  {
    right_wheels_speed = -speed;
    left_wheels_speed = speed;
  }

  Move(right_wheels_speed, left_wheels_speed);
}
