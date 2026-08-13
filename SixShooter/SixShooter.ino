#define G1 2
#define G2 3
#define G3 4
#define G4 5
#define G5 6
#define R1 7
#define fire 13
#define resetPin 12

#define a 33
#define b 35
#define c 27
#define d 29
#define e 31
#define f 37
#define g 39




int i,j;
int myPins[] = {G1, G2, G3, G4, G5, R1};
int randomPins[] = {G1, G2, G3, G4, G5, R1};
int badPins[] = {0,0,0,0,0,0} ;
int state;

void setup() {
  // put your setup code here, to run once:
  digitalWrite(resetPin, HIGH);
  pinMode(resetPin, OUTPUT);

  Serial.begin(9600);

  pinMode(G1, OUTPUT);
  pinMode(G2, OUTPUT);
  pinMode(G3, OUTPUT);
  pinMode(G4, OUTPUT);
  pinMode(G5, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(fire, INPUT_PULLUP);
  digitalWrite(fire, LOW);
  //delay(5500);

  randomizeArray(randomPins);

  for(i = 0; i < 6; i++){
    Serial.println(randomPins[i]);
  }

  delay(500);
  
}

void loop() {
  //delay(3000);
  //Serial.println("State : " + state);
  //Serial.println(digitalRead(fire));
  // put your main code here, to run repeatedly:
  /*
  for(i=0; i <6; i++){
    Serial.println(myPins[i]);
    delay(500);
  }
  Serial.println("   ");
  
  //delay(5000);

  //lightPins(0, badPins, 6);

  //delay(5000);
 
  for(i=0; i < 6; i++){
    Serial.println(myPins[i]);
  }

  randomizeArray(myPins);

  delay(500);

  for(i=0; i < 6; i++){
    Serial.println(myPins[i]);
  }
  */
  /*
  randomizeArray(randomPins);
  Serial.println(" ");
  
  for(i = 0; i < 6; i++){
    Serial.println(randomPins[i]);
  }

  delay(2000);

 */



  switch (state) {
    case 0:

      state = 1;
      NumberChange(6);
      break;
    case 1:
      Serial.println("case 1");
      //delay(3000);

      if(digitalRead(fire) == LOW){
        lightPins(0, badPins, randomPins[0]);

        addBadPin(randomPins[0]);
        //need logic to add the bad pin into the badPins array, probably could make it into a fucntion

        if(randomPins[0] == 7){
          state = 7;
          //Serial.println(state);
        } else {
          state = 2;
          NumberChange(65);
          //Serial.println(state);
        }
      }
      break;
    
    case 2:
      Serial.println("case 2");
      //delay(3000);

      if(digitalRead(fire) == LOW){
        lightPins(1, badPins, randomPins[1]);

        addBadPin(randomPins[1]);

        if(randomPins[1] == 7){
          state = 7;
          //Serial.println(state);
        } else {
          state = 3;
          NumberChange(54);

          //Serial.println(state);
        }
      
      }
      break;

    case 3:
      Serial.println("case 3");
      //delay(3000);

      if(digitalRead(fire) == LOW){
        lightPins(2, badPins, randomPins[2]);

        addBadPin(randomPins[2]);

        if(randomPins[2] == 7){
          state = 7;
          
          //Serial.println(state);
        } else {
          state = 4;
          NumberChange(43);
          
          //Serial.println(state);
        }

      }
      break;

    case 4:
      Serial.println("case 4");
      //delay(3000);

      if(digitalRead(fire) == LOW){
        lightPins(3, badPins, randomPins[3]);

        addBadPin(randomPins[3]);

        if(randomPins[3] == 7){
          state = 7;
          
          //Serial.println(state);
        } else {
          state = 5;
          NumberChange(32);
          
          //Serial.println(state);
        }

      }
      break;

    case 5:
      Serial.println("case 5");
      //delay(3000);

      if(digitalRead(fire) == LOW){
        lightPins(4, badPins, randomPins[4]);

        addBadPin(randomPins[4]);

        if(randomPins[4] == 7){
          state = 7;
          //Serial.println(state);
        } else {
          state = 6;
          NumberChange(21);
          //Serial.println(state);
        }

      }
      break;

    case 6:
      Serial.println("case 6");
      //delay(3000);

      if(digitalRead(fire) == LOW){
        lightPins(5, badPins, randomPins[5]);

        addBadPin(randomPins[5]);
        state = 7;



      }
      break;

    case 7:
      //This is game over motherfucker
      NumberChange(0);

      if(digitalRead(fire) == LOW){
        digitalWrite(resetPin, LOW);
      }



  }


}

void addBadPin(int badPin){
  int hold;
  hold = badPin;
  badPin = badPin - 2;
  badPins[badPin] = hold;
}

void lightPins(int numBadPins, int offPins[6], int shot){

  //Serial.println("case entered");

  for(i = 0; i < 6; i++){

    for(j = 0; j < 6; j++){

        if( offPins[j] != myPins[j]){
              
          //Serial.println(myPins[j]);

          digitalWrite(myPins[j], HIGH);
          delay((400 - 75 * i ) * (7650 / (7650 - (1275 * numBadPins) ) ) );
          digitalWrite(myPins[j], LOW);

         }
    }

  }
  
  for(i = 0; i < shot - 1; i++){

    if(offPins[i] != myPins[i]){

      if( i != shot - 2){
        digitalWrite(myPins[i], HIGH);
        delay(600);
        digitalWrite(myPins[i], LOW);
      } else {
        digitalWrite(myPins[i], HIGH);
        delay(600);
        digitalWrite(myPins[i], LOW);
        for(j = 0; j < 3; j++){
          //Serial.println("We in the j loop hoe");
          delay(200);
          digitalWrite(myPins[i], HIGH);
          delay(200);
          digitalWrite(myPins[i], LOW);
        }
      }
    }

  }

}




void randomizeArray(int orderedPins[6]){
  for(i = 5; i > -1; i--){
    randomSeed(analogRead(A1));
    int hold;
    int j = random(0,5);
    hold = orderedPins[i];
    orderedPins[i] = orderedPins[j];
    orderedPins[j] = hold;
  }
}

void NumberChange(int change) {

  if( change == 0){
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, LOW);
  }
  else if( change == 1){
    //Serial.println("i understand it now");
    digitalWrite(f, LOW);
    digitalWrite(a, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
  }
  else if(change == 6){
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }
  else if(change == 12){
    //Serial.println("12 called");
    digitalWrite(c, LOW);
    digitalWrite(a, HIGH);
    digitalWrite(g, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(d, HIGH);
  }

  else if(change == 23){
    //Serial.println("23 called");
    digitalWrite(e, LOW);
    digitalWrite(c, HIGH);
  }

  else if(change == 34){
    //Serial.println("34 called");
    digitalWrite(a, LOW);
    digitalWrite(d, LOW);
    digitalWrite(f, HIGH);
  }

  else if(change == 45){
    //Serial.println("45 called");
    digitalWrite(b, LOW);
    digitalWrite(a, HIGH);
    digitalWrite(d, HIGH);
  }

  else if(change == 56) {
    //Serial.println("56 called");
    digitalWrite(e, HIGH);
  }

  else if(change == 67) {
    //Serial.println("67 called");
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    digitalWrite(e, LOW);
    digitalWrite(d, LOW);
    digitalWrite(b, HIGH);
  }

  else if(change == 78){
    //Serial.println("78 called");
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(d, HIGH);
  }

  else if(change == 89){
    //Serial.println("89 called");
    digitalWrite(e, LOW);
    digitalWrite(d, LOW);
  }

  else if(change == 98){
    //Serial.println("98 called");
    digitalWrite(e, HIGH);
    digitalWrite(d, HIGH);
  }

  else if(change == 87){
    //Serial.println("87 called");
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(g, LOW);
    digitalWrite(f, LOW);
  }

  else if(change == 76){
    //Serial.println("76 called");
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(b, LOW);
  }

  else if(change == 65){
    //Serial.println("65 called");
    digitalWrite(e, LOW);
  }

  else if(change == 54){
    //Serial.println("54 called");
    digitalWrite(b, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(d, LOW);
  }

  else if(change == 43){
    //Serial.println("43 called");
    digitalWrite(a, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(f, LOW);
  }

  else if(change == 32){
    //Serial.println("32 called");
    digitalWrite(e, HIGH);
    digitalWrite(c, LOW);
  }

  else if(change == 21){
    //Serial.println("21 called");
    digitalWrite(c, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(g, LOW);
  }

  else if(change == 10){
    //Serial.println("this 10 sghit got called son");
    digitalWrite(f, HIGH);
    digitalWrite(a, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
  }
}


