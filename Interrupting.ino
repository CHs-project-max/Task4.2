

#include <BH1750FVI.h>
#define RED 7
#define BLUE 8
#define ORG 9
uint8_t ORG_state = LOW;
uint8_t BLUE_state = LOW;
uint8_t RED_state = LOW;
// Create the Lightsensor instance
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

void setup() 
{
  Serial.begin(115200);
  LightSensor.begin();  
  pinMode(10, INPUT_PULLDOWN);
  pinMode(11, INPUT_PULLDOWN);
  pinMode(13, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(10), toggle_led1 , RISING);
  attachInterrupt(digitalPinToInterrupt(11), toggle_led2 , RISING);
  attachInterrupt(digitalPinToInterrupt(13), toggle_led3, FALLING);
  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(ORG, OUTPUT);
  
}

void loop()
{
  uint16_t lux = LightSensor.GetLightIntensity();
  if(lux <1000)
  {
  Serial.println("it's night time");
  Serial.print("Light: ");
  Serial.println(lux);
  lux = LightSensor.GetLightIntensity();
  digitalWrite(3,HIGH);
  delay(100);
  digitalWrite(3,LOW);
  }
  else{
      Serial.println("it's day time");
      Serial.print("Light: ");
      Serial.println(lux);
      lux = LightSensor.GetLightIntensity();
      digitalWrite(2,HIGH);
      delay(100);
      digitalWrite(2, LOW);
  }
  delay(1000);
}

void toggle_led1()
{
  Serial.println("Toggle red");
  digitalWrite(BLUE, LOW);
  RED_state = !RED_state ;
  digitalWrite(RED, RED_state);
}

void toggle_led2()
{
  Serial.println("Toggle Blue");
  digitalWrite(RED, LOW);
  BLUE_state = !BLUE_state;
  digitalWrite(BLUE,BLUE_state);
}

void toggle_led3()
{
  ORG_state = !ORG_state;
  digitalWrite(ORG, ORG_state);
}