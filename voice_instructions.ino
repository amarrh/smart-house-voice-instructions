// Glasovne naredbe : 1. "GARAŽA" 2. "GARAŽA SVJETLO" 3. "ULAZ" 4. "PROZOR" 5. "SOBA SVJETLO"

#include <Servo.h>

Servo myServo1; // motor garaža
Servo myServo2; // motor ulaz
Servo myServo3; // motor prozor

//pinovi za diode
#define sobaLED 2
#define garazaLED 3

//boolean zastavice za određivanje trenutnog stanja
boolean garazaOtvorena = false;
boolean garazaSvjetlo = false;
boolean ulazOtvoren = false;
boolean prozorOtvoren = false;
boolean sobaSvjetlo = false; 

int poz = 0; //pozicija motora

byte com = 0; // varijabla za spremanje pristigle naredbe

void setup() {

pinMode(garazaLED, OUTPUT);
pinMode(sobaLED, OUTPUT);

Serial.begin(9600);

//pinovi za motore
myServo1.attach(8);   
myServo2.attach(9);
myServo3.attach(10);    

//početni uglovi svakog motora u ovisnosti od položaja i funkcije
myServo1.write(0);
myServo2.write(0);
myServo3.write(180);  

Serial.write(0xAA);

Serial.write(0x37); //kompaktni način

delay(1000);

Serial.write(0xAA);

Serial.write(0x22); //grupa 1
}

void loop() {

  //serijska komunikacija i čitanje naredbe
  while(Serial.available()) {

  com = Serial.read();

  //switch case u ovisnosti od primljene naredbe - 0x11 naredba 1, 0x12 naredba 2, itd.
  switch(com) {

      case 0x11:   
      
      // ugao motora mijenja se for petljom, iz razloga da se kontroliše i brzina rada motora 
      if (garazaOtvorena == false){ //uz pomoć zastavice određuje se koji if else blok naredbi se koristi, tj. da li se vrata otvaraju ili zatvaraju
        for (poz = 0; poz <= 80; poz += 1){
          myServo1.write(poz);
          delay(15);
        }
        garazaOtvorena = true;
      }
      else{
        for (poz = 80; poz >= 0; poz -= 1) { 
          myServo1.write(poz);  
          delay(15);
        }            
        garazaOtvorena = false;
       }

      break;

      case 0x12:  

      if (garazaSvjetlo == false){
            digitalWrite(garazaLED, HIGH);
            garazaSvjetlo = true;
            }
          else{
            digitalWrite(garazaLED, LOW);
            garazaSvjetlo = false;
            }

      break;

      case 0x13: 

      if (ulazOtvoren == false){
        for (poz = 0; poz <= 90; poz += 1){
          myServo2.write(poz);
          delay(15);
        }
        ulazOtvoren = true;
        }
        
      else{
         for (poz = 90; poz >= 0; poz -= 1) { 
          myServo2.write(poz);  
          delay(15);
        }            
        ulazOtvoren = false;
        }
  

      break;

      case 0x14:  
      
      if (prozorOtvoren == false){
        for (poz = 180; poz >= 100; poz -= 1){
          myServo3.write(poz);
          delay(15);
        }
        prozorOtvoren = true;
        }
      else{
         for (poz = 100; poz <= 180; poz += 1) { 
          myServo3.write(poz);  
          delay(15);
        }  
        prozorOtvoren = false;
        }
  

      break;

      case 0x15:  
      
        if (sobaSvjetlo == false){
        digitalWrite(sobaLED, HIGH);
        sobaSvjetlo = true;
        }
      else{
        digitalWrite(sobaLED, LOW);
        sobaSvjetlo = false;
        }
  

      break;

            }
      }
}
