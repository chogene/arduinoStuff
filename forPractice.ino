int bluePin = 10;
int redPin = 9;
int num = 5;
int waitT = 50;
int i;
int j;

void setup() {
  // put your setup code here, to run once:
pinMode(bluePin, OUTPUT);
pinMode(redPin, OUTPUT);


}


void loop() {
  // put your main code here, to run repeatedly:
for (i=1; i <= num; i++){
digitalWrite(bluePin,HIGH);
delay(waitT);
digitalWrite(bluePin, LOW);
delay(waitT);
}
for (j=1; j <= num; j++){
digitalWrite(redPin,HIGH);
delay(waitT);
digitalWrite(redPin, LOW);
delay(waitT);
}

}
