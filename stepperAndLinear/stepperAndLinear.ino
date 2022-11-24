
#include <Arduino.h>
#include "BasicStepperDriver.h"

// Define stepper motors properties
#define MOTOR_STEPS 200
#define RPM 30
#define RPM_L 300
#define SLEEP_L 15
#define SLEEP 2
#define MICROSTEPS_L 16
#define MICROSTEPS 1
#define DIR_L 13
#define STEP_L 14
#define DIR 0
#define STEP 1

//Defining the teensy pins for control using Bonsai
#define ALUM 21
#define ATT 20
#define NON 19
#define LFWD 17
#define LBCK 22
#define CATCH_FWD 18
#define CATCH_BCK 16

//Define the teensy pins to report back to Bonsai
#define L_WH 11
#define L_ST 10
#define L_CATCH 5
#define R_ALUM 8
#define R_MUT 7
#define R_NON 6
#define R_OBJ 9

// Create interrupt pin
const byte interruptPin = 23;

// intilaize motor objects
BasicStepperDriver linnear(MOTOR_STEPS, DIR_L, STEP_L,SLEEP_L);
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP,SLEEP);

// initilaize variables for computation of positions
int whiskPos; // create variable for the linear movement to whisker position
int stepperAngle = 0; // create variable for the object stepper angle
int catch_dis;
int myrand1; // first rand number generator for rotary stepper 
int myrand2; // second rand number generator for rotary stepper 
int myrandmove = myrand1+myrand2 ; // sum movement of myrand1+myrand2
int randangle; // rand option between 2 stimulus.
int randopt; // switch case for stimulus.
// define the position of the objects on the wheel
int al_1 = 1 * 32;
int al_2 = 3 * 32;
int at_1 = 2 * 32;
int at_2 = 5 * 32;  
int no_1 = 0 * 32;
int no_2 = 4 * 32;



void setup() {
    
    linnear.begin(RPM_L, MICROSTEPS_L);
    linnear.setEnableActiveState(LOW);
    stepper.begin(RPM, MICROSTEPS);
    stepper.setEnableActiveState(LOW);
    stepper.enable();
    Serial.begin(115200);
    pinMode(interruptPin, INPUT_PULLDOWN);
    pinMode(ALUM,INPUT_PULLDOWN);
    pinMode(ATT,INPUT_PULLDOWN);
    pinMode(NON,INPUT_PULLDOWN);
    
    pinMode(3,OUTPUT);
    randomSeed(analogRead(0));
    while (! Serial); // Wait until Serial is ready - Leonardo
   
   attachInterrupt(digitalPinToInterrupt(interruptPin), advancemotor, RISING);
   Serial.println("l - aluminum foil m - muted n - non");
//   
  linnear.enable();
   linnear.rotate(-36000);
   
   linnear.disable();

}

void loop() {
    // generate random numbers to rotate motor
 myrand1  = random(-250,250) ; 
 myrand2  = random(-250,250) ;
 myrandmove = myrand1+myrand2;
 // genrate random option from 2 identical stimulus.
      randangle = random(1,3);
      int tempAngle;  

// determine the position of the linear motor at ehiskers
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
        else if(jj == 'c') // determine catch trial distance
        {
          String catchD = Serial.readString();
          catchD.remove(0,1); 
          Serial.print("catch distance");
          Serial.println(catchD);
          catch_dis = catchD.toInt()*180;
        }
        else
        {
          ch = Serial.read(); 
          Serial.println("print ch");
          Serial.println(ch);
        }
      
      }
    

      
//    Send all teensy controlled pins to LOW so you make sure they are ready to give commands  
      digitalWrite(2,LOW);
      digitalWrite(ALUM,LOW);
      digitalWrite(ATT,LOW);
      digitalWrite(NON,LOW);
      digitalWrite(interruptPin,LOW);

    
      
       

           
        if (ch == 'l' || digitalRead(ALUM) == HIGH)
        {
           
          switch (randangle) {
          case 1:
          tempAngle = al_1;
          break;
          case 2:
          tempAngle = al_2;
          break;
          }
          linnear.enable();
          linnear.rotate(-whiskPos);
          stepper.move(-stepperAngle);
          delay(200);
          stepper.move(myrand1*MICROSTEPS);
          delay(200);
          stepper.move(myrand2*MICROSTEPS);
          delay(200);
          stepper.move((-myrandmove*MICROSTEPS)+(tempAngle*MICROSTEPS));       
          stepperAngle = tempAngle*MICROSTEPS;
          Serial.println("aluminum");
          delay(1000);
          linnear.rotate(whiskPos);
          linnear.disable();
          delay(500);
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          digitalWrite(ALUM,LOW);
        }
    
    
        if (ch == 'm'|| digitalRead(ATT) == HIGH)
        {
          
          switch (randangle) {
          case 2 :
          tempAngle = at_1;
          break;
          case 1 :
          tempAngle = at_2;
          break;
          }
          linnear.enable();
          linnear.rotate(-whiskPos);

          stepper.move(-stepperAngle);
          delay(200);
          stepper.move(myrand1*MICROSTEPS);
          delay(200);
          stepper.move(myrand2*MICROSTEPS);
          delay(200);
          stepper.move((-myrandmove*MICROSTEPS)+(tempAngle*MICROSTEPS));   
          stepperAngle = tempAngle*MICROSTEPS;
          Serial.println("aluminum silenced");
          delay(1000);
          linnear.rotate(whiskPos);
          linnear.disable();
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          delay(100);
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          digitalWrite(ATT,LOW);
         
          
        }
    
    
    
        if (ch == 'n' || digitalRead(NON) == HIGH)
        {
            
          switch (randangle) {
          case 1:
          tempAngle = no_1;
          break;
          case 2:
          tempAngle = no_2;
          break;
          }
          linnear.enable();
          linnear.rotate(-whiskPos);
          stepper.move(-stepperAngle);
          delay(200);
          stepper.move(myrand1*MICROSTEPS);
          delay(200);
          stepper.move(myrand2*MICROSTEPS);
          delay(200);
          stepper.move((-myrandmove*MICROSTEPS)+(tempAngle*MICROSTEPS));   
          stepperAngle = tempAngle;
          Serial.println("non");
          delay(1000);
          linnear.rotate(whiskPos);
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
          digitalWrite(NON,LOW);
        
         
          
          
        }
      
}
      




void advancemotor() {
  
  linnear.startBrake();
  linnear.rotate(180);
  Serial.println("stopped");
  
  
  
  
}
