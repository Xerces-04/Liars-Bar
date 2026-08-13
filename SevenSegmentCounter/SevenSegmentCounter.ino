#define a 33
#define b 35
#define c 27
#define d 29
#define e 31
#define f 37
#define g 39

int delayTime = 300;
int i;

void setup() {
  // put your setup code here, to run once:c

  Serial.begin(9600);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  //digitalWrite(g, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  

  for(i = 1; i < 90; i = i + 11){
    delay(delayTime);
    NumberChange(i);
  }

  for(i = 98; i > 9; i = i -11){
    delay(delayTime);
    NumberChange(i);
  }
}

void NumberChange(int change) {


  if( change == 1){
    //Serial.println("i understand it now");
    digitalWrite(f, LOW);
    digitalWrite(a, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
  }

  else if(change == 12){
    Serial.println("12 called");
    digitalWrite(c, LOW);
    digitalWrite(a, HIGH);
    digitalWrite(g, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(d, HIGH);
  }

  else if(change == 23){
    Serial.println("23 called");
    digitalWrite(e, LOW);
    digitalWrite(c, HIGH);
  }

  else if(change == 34){
    Serial.println("34 called");
    digitalWrite(a, LOW);
    digitalWrite(d, LOW);
    digitalWrite(f, HIGH);
  }

  else if(change == 45){
    Serial.println("45 called");
    digitalWrite(b, LOW);
    digitalWrite(a, HIGH);
    digitalWrite(d, HIGH);
  }

  else if(change == 56) {
    Serial.println("56 called");
    digitalWrite(e, HIGH);
  }

  else if(change == 67) {
    Serial.println("67 called");
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    digitalWrite(e, LOW);
    digitalWrite(d, LOW);
    digitalWrite(b, HIGH);
  }

  else if(change == 78){
    Serial.println("78 called");
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(d, HIGH);
  }

  else if(change == 89){
    Serial.println("89 called");
    digitalWrite(e, LOW);
    digitalWrite(d, LOW);
  }

  else if(change == 98){
    Serial.println("98 called");
    digitalWrite(e, HIGH);
    digitalWrite(d, HIGH);
  }

  else if(change == 87){
    Serial.println("87 called");
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(g, LOW);
    digitalWrite(f, LOW);
  }

  else if(change == 76){
    Serial.println("76 called");
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(b, LOW);
  }

  else if(change == 65){
    Serial.println("65 called");
    digitalWrite(e, LOW);
  }

  else if(change == 54){
    Serial.println("54 called");
    digitalWrite(b, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(d, LOW);
  }

  else if(change == 43){
    Serial.println("43 called");
    digitalWrite(a, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(f, LOW);
  }

  else if(change == 32){
    Serial.println("32 called");
    digitalWrite(e, HIGH);
    digitalWrite(c, LOW);
  }

  else if(change == 21){
    Serial.println("21 called");
    digitalWrite(c, HIGH);
    digitalWrite(a, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(g, LOW);
  }

  else if(change == 10){
    Serial.println("this 10 sghit got called son");
    digitalWrite(f, HIGH);
    digitalWrite(a, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
  }
}