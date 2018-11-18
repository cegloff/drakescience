#include <SPI.h> // Use Servo library, included with IDE
#include <Adafruit_GFX.h> //Installed from Arduino Library Manager
#include <Adafruit_PCD8544.h>  //Installed from Arduino Library Manager
#include <Servo.h>    // Use Servo library, included with IDE

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (CLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (DC)
// pin 4 - LCD chip select (CE)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
float stopSensor = 0;
int IRpin = 0; // Plug IR sensor yellow wire into Arduino A0
int servoPin = 8; // Plug the servo orange wire in Arduino pin 8
int buttonPin = 10; // Plug the button wire into Arduino pin 9
bool buttonStatus = 0;
// float topTime = 00.00;
float runTime = 00.00;
float accel = 0;
float velocity = 0;
float StartTime = 0;
float topTime = 99999;
float CurrentTime = 0;
float ElapsedTime = 0;
bool buttonPushed = 0;
float distance = 18;

Servo myServo;
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

void setup()   {
  Serial.begin(9600);
  pinMode(IRpin, INPUT);
  pinMode(buttonPin, INPUT);
  // pinMode(servoPin, OUTPUT);
  myServo.attach(servoPin);  // Servo is connected to digital pin 9 
  myServo.write(110);   // Rotate servo counter clockwise
  delay(1000);
  myServo.detach();
  
  display.begin();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(50);
 
  display.clearDisplay();   // clears the screen and buffer


}


void loop() {

  // buttonStatus = digitalRead(buttonPin);
  // if (buttonStatus){
  //   myServo.attach(servoPin);
  //   myServo.write(20);
  //   StartTime = millis();
  //   buttonPushed = 1;
  // }

  // getstopSensor();
  // if (stopSensor > 900 && buttonPushed){
  //   CurrentTime = millis();
  //   ElapsedTime = CurrentTime - StartTime;
  //   if (ElapsedTime < topTime){
  //     topTime = ElapsedTime;
  //   }
  //   delay(1000);
  //   myServo.write(110);
  //   delay(1000);
  //   myServo.detach();
  //   buttonPushed = 0;
  //   velocity = distance / (ElapsedTime / 1000);
  //   accel = velocity / (ElapsedTime / 1000);
  // }

  // delay(200);
  display.clearDisplay(); 
  display.println("Hello, world!");
  // updateDisplay();
  display.display();

}

void updateDisplay(){
  // display.clearDisplay();   // clears the screen and buffer
  // text display tests
  // display.setTextSize(1);
  // display.setTextColor(BLACK);
  // display.setCursor(0,0);
  Serial.print("Top Time:");
  Serial.print(topTime, 0);
  Serial.print(", Stop Sensor:");
  Serial.print((int)floor(stopSensor/100));
  Serial.print(", Distance:");
  Serial.print(distance);
  Serial.print(", Time:");
  Serial.print(ElapsedTime);
  // Serial.println(buttonStatus);
  Serial.print(", Accel:");
  Serial.print(accel);
  Serial.print(", Velocity:");
  Serial.println(velocity);
  // display.display();
}

void getstopSensor (){
  float volts = analogRead(IRpin); // * 5/1024;   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
  // stopSensor = 65*pow(volts, -1.10);   // worked out from graph 65 = theretical stopSensor / (1/Volts)S - luckylarry.co.uk  
  stopSensor = volts;
}