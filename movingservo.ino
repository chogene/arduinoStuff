#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int potPin = A1;
int potVal;
float theta;
Servo myServo;

int lastPotVal = 0;       // To store the last potentiometer value
unsigned long lastMoveTime = 0; // To track the last time the servo was moved
bool isAutoMode = true;   // Flag to check if in auto mode
int autoAngle = 0;        // Angle for auto rotation

void setup() {
  Serial.begin(115200);
  pinMode(potPin, INPUT);
  myServo.attach(13);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
}

void loop() {
  potVal = analogRead(potPin);
  theta = (180.0 / 1023.0) * (1023 - potVal);
  theta = (int)theta;

  // Check if potentiometer has moved significantly
  if (abs(potVal - lastPotVal) > 5) {
    isAutoMode = false;
    lastMoveTime = millis();  // Reset the timer
  } else if (millis() - lastMoveTime > 3000) { // 3 seconds of inactivity
    isAutoMode = true;
  }

  if (isAutoMode) {
    // Automatic rotation mode
    autoAngle = (autoAngle + 1) % 181; // Increment angle from 0 to 180
    myServo.write(autoAngle);
    theta = autoAngle; // Update theta to match auto angle
  } else {
    // Manual control mode
    myServo.write(theta);
  }

  // Update display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Twist the knob!");
  display.print("       Angle: ");
  display.print(theta);
  display.println(" deg");

  // Calculate end point of the line based on theta
  int x = 64 + 70 * cos(radians(theta));
  int y = 64 - 70 * sin(radians(theta));

  // Draw line from origin to calculated endpoint (x, y)
  display.drawLine(64, 64, x, y, WHITE);
  display.display();

  lastPotVal = potVal;
  delay(20);
}
