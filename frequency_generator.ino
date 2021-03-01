#include <Encoder.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Encoder myEnc(6, 5);
#define btnPin 7
bool btnState = HIGH;
bool lastbtnState = HIGH;
int bntCount = 0;
int increment = 0;
#define ledPin 13

#define genPin 4
long freq = 0;
long oldPosition  = 0;
long oldfreq = 20;
int mult;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


#define OLED_RESET     4 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  pinMode(genPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
}

void loop() {
  btnState = digitalRead(btnPin);
  long newPosition = (myEnc.read())/4;
  Serial.println(oldPosition);

  if(btnState == LOW){
    increment ++;
    oldPosition = newPosition;
    oldfreq = freq;
    delay(300);
  }

  freq = oldfreq + (newPosition - oldPosition)*pow(10, increment);

  mult = pow(10, increment);
    
  if(increment > 4){
    increment = 0;
  }

  if(freq < 20){
    freq = 20;
  }

  analogWriteFrequency(genPin, freq);
  analogWrite(genPin, 128);
  
  display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(freq);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(100, 10);
  display.print("Hz");

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 50);
  display.print(mult);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 50);
  display.print("x");

  display.display();
}
