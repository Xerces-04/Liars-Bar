#define G1 2
#define G2 3
#define G3 4
#define G4 5
#define G5 6
#define R1 7
#define fire 9
#define resetPin 12

int i,j;
int myPins[] = {G1, G2, G3, G4, G5, R1};
int randomPins[] = {G1, G2, G3, G4, G5, R1};
int badPins[] = {0,0,0,0,0,0} ;
int state;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(fire, INPUT_PULLUP);
}

void loop() {
  /*// put your main code here, to run repeatedly:
  randomSeed(millis());
  int j = random(0,6);
  Serial.println(j);
  //delay(1000);
  //currentTime = millis();
  Serial.print("Milliseconds since start and seed value: ");
  Serial.println(millis());
  delay(1000); // Wait for 1 second
*/

  if(digitalRead(fire) == LOW){
    /*randomSeed(millis());
    int j = random(0,6);
    Serial.println(j);
    Serial.println(millis());
    Serial.println(" ");
    delay(500);
    */
  randomizeArray(randomPins);

    for(i = 0; i < 6; i++){
      Serial.print(randomPins[i]);
     }
    Serial.println(" ");
    state = 1;
    delay(500);
  }

}


void randomizeArray(int orderedPins[6]){
  for(j = 0; j < 8; j++){
    for(i = 0; i < 6; i++){
      randomSeed(millis());
      int hold;
      int j = random(0,5);
      hold = orderedPins[i];
      orderedPins[i] = orderedPins[j];
      orderedPins[j] = hold;
      delay(30);
    }
  }
}
