int potPin = A1;
int lightPin = 9;
int potVal;
float lightVal;

void setup() {
  // put your setup code here, to run once:
pinMode(potPin, OUTPUT);
pinMode(lightPin, OUTPUT);
Serial.begin(9600);



}

void loop() {
  // put your main code here, to run repeatedly:
potVal = analogRead(potPin);
lightVal = (255.0/1023.0)*potVal;
analogWrite(lightPin, lightVal);
Serial.println(potVal);
Serial.println(lightVal);

}
