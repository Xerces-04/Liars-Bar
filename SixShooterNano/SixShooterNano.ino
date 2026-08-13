#include <TM1637Display.h>
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>


#define G1 2
#define G2 3
#define G3 4
#define G4 5
#define G5 6
#define R1 7
#define fire 9
#define CLK 8
#define DIO 10
#define Rx 11
#define Tx 12
#define BUSY_PIN A1


//import random
int lives = 6;
int i,j;
int myPins[] = {G1, G2, G3, G4, G5, R1};
int randomPins[] = {G1, G2, G3, G4, G5, R1};
int badPins[] = {0,0,0,0,0,0} ;
int state = 0;
bool displayRunning;
unsigned long startTime;


TM1637Display display(CLK, DIO);
const uint8_t SEG_DEAD[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          // d
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,          // E
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,  // A
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G           // d
};

SoftwareSerial mySoftwareSerial(11, 12); // RX (11), TX (12)
DFRobotDFPlayerMini myDFPlayer;


void setup() {
  delay(5000);
  pinMode(R1, OUTPUT);
  digitalWrite(R1, HIGH);
  delay(2000);
  

  pinMode(G1, OUTPUT);
  pinMode(G2, OUTPUT);
  pinMode(G3, OUTPUT);
  pinMode(G4, OUTPUT);
  pinMode(G5, OUTPUT);
  //pinMode(R1, OUTPUT);
  pinMode(fire, INPUT_PULLUP);
  pinMode(BUSY_PIN, INPUT);

  randomSeed(analogRead(A0));
  randomizeArray(randomPins);

  state = 7;
  display.setBrightness(0x03); // Set brightness (0x00 to 0x0f)
  display.showNumberDec(lives); //start by diplaying the number of lives, 6
  displayRunning = true;

  Serial.begin(9600);
  mySoftwareSerial.begin(9600);

  //digitalWrite(R1, HIGH);

  //delay(1000); // Give the DFPlayer 2 seconds to power up before initializing




  
  while (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("DFPlayer error - check wiring/SD card.");
    delay(1000);
  }
  myDFPlayer.volume(24); // Volume 0 to 30

  //digitalWrite(R1, LOW);
  digitalWrite(R1, LOW);

  lightPinsSpin(); //activate inital spin with reload sound

}

void loop() {

   switch (state) {

    case 7:

      if(digitalRead(fire) == LOW && state == 7){

        addBadPin(randomPins[0]);
        
        if(randomPins[0] == 7){
          wetFire();
          state = 13;
        } else {
          dryFire();
          state = 8;
        }
        lightPins(0);
      }
      break;
    
    case 8:


      if(digitalRead(fire) == LOW && state == 8){
        addBadPin(randomPins[1]);
        if(randomPins[1] == 7){
          wetFire();
          state = 13;

        } else {
          dryFire();
          state = 9;

        }
        lightPins(1);
      }
      break;

    case 9:


      if(digitalRead(fire) == LOW && state == 9){
        addBadPin(randomPins[2]);
        if(randomPins[2] == 7){
          wetFire();
          state = 13;
        } else {
          dryFire();
          state = 10;
        }
        lightPins(2);
      }
      break;

    case 10:


      if(digitalRead(fire) == LOW && state == 10){
        addBadPin(randomPins[3]);
        if(randomPins[3] == 7){
          wetFire();
          state = 13;
        } else {
          dryFire();
          state = 11;
        }
        lightPins(3);
      }
      break;

    case 11:


      if(digitalRead(fire) == LOW && state == 11){
        addBadPin(randomPins[4]);
        if(randomPins[4] == 7){
          wetFire();
          state = 13;
        } else {
          dryFire();
          state = 12;
        }
        lightPins(4);
      }
      break;

    case 12:

      if(digitalRead(fire) == LOW && state == 12){
        addBadPin(randomPins[5]);
        wetFire();
        state = 13;
        lightPins(5);
      }
      break;

    case 13:

      

      if (displayRunning && (millis() - startTime >= 15000))
      {
        display.clear();
        displayRunning = false;
      }
      // Game over sequence
      if(digitalRead(fire) == LOW) {
        resetGame(); 
      }
      break;
  }
}

void addBadPin(int badPin){
  int hold;
  hold = badPin;
  badPin = badPin - 2;
  badPins[badPin] = hold;
}

void lightPins(int j)
{
  digitalWrite(randomPins[j], HIGH);
  delay(1000);
  digitalWrite(randomPins[j], LOW);

}
void lightPinsSpin() {
  triggerSound(4);
  delay(2900);
  int spinDelay = 7; 
  unsigned long startTime = millis(); // Record the start time
  unsigned long duration = 600;      // 3 seconds in milliseconds

  // Keep spinning as long as 3 seconds haven't passed
  while (millis() - startTime < duration) {
    for (int j = 0; j < 6; j++) {
      // Check again inside the loop to ensure we don't start a 
      // new pin cycle if the time has just run out
      if (millis() - startTime >= duration) break;

      digitalWrite(myPins[j], HIGH);
      delay(spinDelay);
      digitalWrite(myPins[j], LOW);

      // Increase delay to simulate slowing down
      // Adjust the '+ 2' to a smaller number if it stops too fast
      spinDelay += 4; 
    }
}

}

void randomizeArray(int orderedPins[6]) {
  // 1. Seed the random generator ONCE at the start of the shuffle
  // We use an unconnected analog pin for floating voltage "noise"
  randomSeed(micros() + analogRead(A0)); 

  // 2. Fisher-Yates Shuffle
  // We start from the end of the array and swap each element with 
  // a random element that comes before it.
  for (int i = 5; i > 0; i--) {
    // Pick a random index from 0 to i
    int j = random(0, i + 1);
    
    // Swap orderedPins[i] with orderedPins[j]
    int temp = orderedPins[i];
    orderedPins[i] = orderedPins[j];
    orderedPins[j] = temp;
  }

  // Optional: Visual feedback that the "gun is loaded"

}



void resetGame() {

  lives = 6;
  for (int k = 0; k < 6; k++) {
    badPins[k] = 0;
  }
  
  // Re-shuffle for the new game
  randomizeArray(randomPins); 

  display.clear();
  display.showNumberDec(6);
  
  // Jump straight to the first trigger pull state
  state = 7; 
  while(digitalRead(fire) == LOW)
  {
    delay(100);

  }
  Serial.println("Gun Reloaded. Ready for Round 1.");

  lightPinsSpin();

  displayRunning = true;
  
}

// In your loop logic, replace playBang() with:
void triggerSound(int fileNumber) {
  myDFPlayer.playFolder(1, fileNumber);
}

void waitForSound() {
  delay(100); // Give the DFPlayer a moment to actually start the file
  while (digitalRead(BUSY_PIN) == LOW) {
    // Do nothing! Just wait for the sound to finish.
  }
  Serial.println("Sound Over");
}

void dryFire()
{
  lives = lives - 1;
  triggerSound(2);
  delay(2500);
  triggerSound(3);
  display.clear();
  display.showNumberDec(lives);
  //waitForSound();
}

void wetFire()
{
  triggerSound(2);
  delay(2500);
  triggerSound(5);
  display.clear();
  display.setSegments(SEG_DEAD);
  startTime = millis();
  //waitForSound();
}
