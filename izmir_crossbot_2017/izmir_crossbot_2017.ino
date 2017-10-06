/*
 * Author: B. Onder Karamelek
 * Date: 23.09.2017
 * Iztech Roboleague Cross Bot
 */

#define debug_mode
//#define debug_mode2

 uint8_t motor_en1 = 9, motor_en2 = 10, motor_A1 = 2, motor_B1 = 3, motor_A2 = 4, motor_B2 = 5;
 uint8_t k = 20;
 signed long int yon, sag_hiz, sol_hiz, hiz_okunan;

//=================================================================  

 //Motor Config
 
 void dur(){
  digitalWrite(motor_A1,0);
  digitalWrite(motor_B1,0);
  digitalWrite(motor_A2,0);
  digitalWrite(motor_B2,0);
  }

 void sag_ileri(){
  digitalWrite(motor_A1,1);
  digitalWrite(motor_A2,0);
  }

 void sol_ileri(){
   digitalWrite(motor_A1,0);
   digitalWrite(motor_A2,1);
   }

  void sag_geri(){
  digitalWrite(motor_B1,1);
  digitalWrite(motor_B2,0);
  }

 void sol_geri(){
   digitalWrite(motor_B1,0);
   digitalWrite(motor_B2,1);
   }

//=================================================================  
   
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(11,INPUT);
  pinMode(12,INPUT);
  pinMode(motor_A1,OUTPUT);
  pinMode(motor_A2,OUTPUT);
  pinMode(motor_B1,OUTPUT);
  pinMode(motor_B2,OUTPUT);
  pinMode(motor_en1,OUTPUT);
  pinMode(motor_en2,OUTPUT);
  
}

//=================================================================  

void loop() {
  // put your main code here, to run repeatedly:

  //Gurultuden kurtul
  hiz_okunan=map(pulseIn(11,HIGH),1000,1900,-5,5);
  yon=map(pulseIn(12,HIGH),1000,1900,-5,5) +  1;

//Update
  if(hiz_okunan == 0 && yon == 0){
      dur();
      #ifdef debug_mode
        Serial.println("stoped");
      #endif
    }
  else{
       sag_hiz = 50 * hiz_okunan - yon * k;
       sol_hiz = 50 * hiz_okunan + yon * k;

      if(sol_hiz < 0){
        if(sol_hiz < -255)
          sol_hiz = -255;
        sol_hiz = -sol_hiz;
        sol_geri();
      }
      else{
        if(sol_hiz > 255)
         sol_hiz = 255;
        sol_ileri;
        }

      if(sag_hiz < 0){
        if(sag_hiz < -255)
          sag_hiz = -255;
        sag_hiz = -sag_hiz;
        sag_geri;
        }
      else{
        if(sag_hiz > 255)
          sag_hiz = 255;
        sag_ileri();
      }

      
    //start debug session
   #ifdef debug_mode
    Serial.print("sag_hiz:    "); 
    Serial.print(sag_hiz);
    Serial.print("\n");
    Serial.print("sol_hiz:    ");
    Serial.print(sol_hiz);
    Serial.print("\n");
    delay(10);
   #endif


   #ifdef debug_mode2
     Serial.print("sag_hiz:    ");
     Serial.print(sag_hiz);
    Serial.print("\n");
    Serial.print("sol_hiz:    ");
     Serial.print(sol_hiz);
    Serial.print("\n");
    delay(100);
   #endif

      analogWrite(motor_en1,sag_hiz);
      analogWrite(motor_en2,sol_hiz);
      
     }

  }
//=================================================================  

