
#include <Arduino.h>
#include "BasicStepperDriver.h"
//#include <ezButton.h> 
#define MOTOR_STEPS 200
#define RPM 30
#define RPM_L 300
#define SLEEP_L 15
#define SLEEP 2


const byte interruptPin = 23;


#define MICROSTEPS_L 16
int whiskPos;
int stepperAngle = 0;

//int resetPin = 12; 

#define DIR_L 13
#define STEP_L 14
BasicStepperDriver linnear(MOTOR_STEPS, DIR_L, STEP_L,SLEEP_L);

#define MICROSTEPS 1

#define DIR 0
#define STEP 1
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP,SLEEP);
int randAr[6] = {1,2,3,1,2,3};
int countAll = 0;
int myrand1; // first rand number generator for motor
int myrand2; // second rand number generator for motor
int myrandmove = myrand1+myrand2 ; // sum movement of myrand1+myrand2
//Uncomment line to use enable/disable functionality
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);


void setup() {
    
    linnear.begin(RPM_L, MICROSTEPS_L);
    linnear.setEnableActiveState(LOW);
    stepper.begin(RPM, MICROSTEPS);
    stepper.setEnableActiveState(LOW);
    // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
    // stepper.setEnableActiveState(LOW);
    stepper.enable();
    Serial.begin(115200);
    pinMode(interruptPin, INPUT_PULLDOWN);
    pinMode(11,INPUT_PULLDOWN);
    pinMode(21,INPUT_PULLDOWN);
    pinMode(20,INPUT_PULLDOWN);
    pinMode(19,INPUT_PULLDOWN);
    
    pinMode(3,OUTPUT);
    randomSeed(analogRead(0));
    while (! Serial); // Wait until Serial is ready - Leonardo
   
   attachInterrupt(digitalPinToInterrupt(interruptPin), advancemotor, RISING);
   Serial.println("l - aluminum foil m - muted n - non");
//   
  linnear.enable();
   linnear.rotate(-36000);
   
   linnear.disable();
//   stepper.rotate(1.8);
}

void loop() {
 myrand1  = random(-250,250) ; 
 myrand2  = random(-250,250) ;
 myrandmove = myrand1+myrand2;        
//Serial.println(digitalRead(21));

  int mm = 0;
  char jj;
  int rot;
 char ch;
  int bt;
     if (Serial.available())
      {   
        jj = Serial.peek();
        if(isDigit(jj) || jj == '-'){
      
          linnear.enable();
          mm = Serial.parseInt();
          Serial.println(mm);
          
          bt = mm * 180;
          linnear.rotate(bt);
          whiskPos += bt;
          Serial.println(whiskPos);
          linnear.disable();
        }
        else if(jj=='r')
        {
          String rr = Serial.readString();
          rr.remove(0,1);
          Serial.print("Rotating stepper  ");
          Serial.println(rr);
          rot = rr.toInt();
          stepper.move(rot);
          stepperAngle = 0;
        }
        else
        {
          ch = Serial.read(); 
          Serial.println("print ch");
          Serial.println(ch);
        }
      
      }

      
      
      digitalWrite(2,LOW);
      digitalWrite(11,LOW);
      digitalWrite(21,LOW);
      digitalWrite(20,LOW);
      digitalWrite(19,LOW);
      digitalWrite(23,LOW);

    
      
       

           
        if (ch == 'l' || digitalRead(21) == HIGH)
        {
          
          linnear.enable();
          linnear.rotate(-whiskPos);
          stepper.move(-stepperAngle);
          delay(200);
          stepper.move(myrand1*MICROSTEPS);
          delay(200);
          stepper.move(myrand2*MICROSTEPS);
          delay(200);
          stepper.move((-myrandmove*MICROSTEPS)+(32*MICROSTEPS));       
          stepperAngle = 32*MICROSTEPS;
//          stepper.rotate(-stepperAngle);
//          delay(100);
//          stepper.rotate(60);
//          stepperAngle = 60;
          Serial.println("aluminum");
          delay(1000);
          linnear.rotate(whiskPos);
          linnear.disable();
//          stepper.disable();
          delay(500);
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          digitalWrite(21,LOW);
         
          
          
          
        }
        if (ch == 'm'|| digitalRead(20) == HIGH)
        {
          
          linnear.enable();
          linnear.rotate(-whiskPos);

          stepper.move(-stepperAngle);
          delay(200);
          stepper.move(myrand1*MICROSTEPS);
          delay(200);
          stepper.move(myrand2*MICROSTEPS);
          delay(200);
          stepper.move((-myrandmove*MICROSTEPS)+(64*MICROSTEPS));   
          stepperAngle = 64*MICROSTEPS;
//          stepper.rotate(-stepperAngle);
//          delay(100);
//          stepper.rotate(120);
//          stepperAngle = 120;
          Serial.println("aluminum silenced");
          delay(1000);
          linnear.rotate(whiskPos);
//          stepper.disable();
          linnear.disable();
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          delay(100);
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          digitalWrite(20,LOW);
         
          
        }
        if (ch == 'n' || digitalRead(19) == HIGH)
        {
          
          linnear.enable();
          linnear.rotate(-whiskPos);
          stepper.move(-stepperAngle);
          delay(200);
          stepper.move(myrand1*MICROSTEPS);
          delay(200);
          stepper.move(myrand2*MICROSTEPS);
          delay(200);
          stepper.move((-myrandmove*MICROSTEPS)+(0*MICROSTEPS));   
          stepperAngle = 0;
          Serial.println("non");
          delay(1000);
          linnear.rotate(whiskPos);
//          stepper.disable();
          linnear.disable();
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          delay(100);
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          delay(100);
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          digitalWrite(19,LOW);
        
         
          
          
        }
      
}
      




void advancemotor() {
  
  linnear.startBrake();
  linnear.rotate(180);
  Serial.println("stopped");
  
  
  
  
}