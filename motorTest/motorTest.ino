#include "GoBLE.h"


int joystickX, joystickY;
int buttonState[7];

//Standard PWM DC control
int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control

void stop(void)                    //Stop
{
  digitalWrite(E1,LOW);
  digitalWrite(E2,LOW);
}
void advance(char a,char b)          //Move forward
{
  analogWrite (E1,a);      //PWM Speed Control
  digitalWrite(M1,HIGH);
  analogWrite (E2,b);
  digitalWrite(M2,HIGH);
}
void back_off (char a,char b)          //Move backward
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);
  analogWrite (E2,b);
  digitalWrite(M2,LOW);
}
void turn_L (char a,char b)             //Turn Left
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);
  analogWrite (E2,b);
  digitalWrite(M2,HIGH);
}
void turn_R (char a,char b)             //Turn Right
{
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);
  analogWrite (E2,b);
  digitalWrite(M2,LOW);
}
void setup(void)
{
  int j;
  for(j=4;j<=7;j++)
    pinMode(j, OUTPUT);
  
  Goble.begin();
  Serial.begin(9600);      //Set Baud Rate
  Serial.println("Run keyboard control");
}

void loop(void)
{
   if(Goble.available()){
    joystickX = Goble.readJoystickX();
    joystickY = Goble.readJoystickY();
    
    buttonState[SWITCH_UP]     = Goble.readSwitchUp();
    buttonState[SWITCH_DOWN]   = Goble.readSwitchDown();
    buttonState[SWITCH_LEFT]   = Goble.readSwitchLeft();
    buttonState[SWITCH_RIGHT]  = Goble.readSwitchRight();
    buttonState[SWITCH_SELECT] = Goble.readSwitchSelect();
    buttonState[SWITCH_START]  = Goble.readSwitchStart();
    
    Serial.print("Joystick Value: ");
    Serial.print(joystickX);
    Serial.print("  ");
    Serial.println(joystickY);
    
    for (int i = 1; i < 7; i++) {
      Serial.print("Button ID: ");
      Serial.print(i);
      Serial.print("\t State: ");
      

      if(buttonState[i] == PRESSED && i == 1)
      {
        Serial.println("advance!");
         advance (255,255);
      }  
     
       if(buttonState[i] == PRESSED && i == 3)
      {
        Serial.println("backoff!");
         back_off (255,255);
      }  
      
       if(buttonState[i] == PRESSED && i == 4)
      {
        Serial.println("left!");
         turn_L (255,255);
      }  
     
        if(buttonState[i] == PRESSED && i == 2)
      {
        Serial.println("rights!");
         turn_R (255,255);
      }  
         if(buttonState[i] == PRESSED && i == 5)
      {
        Serial.println("stop!");
         stop(); 
      }  
      
    }
   }
    
  
  
}