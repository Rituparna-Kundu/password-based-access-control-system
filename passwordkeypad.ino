#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

char keys[4][4] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
byte rowPins[4] = {9, 8, 7, 6}, colPins[4] = {5, 4, 3, 2};
Keypad key(makeKeymap(keys), rowPins, colPins, 4, 4);

#define RELAY 10
#define ON  LOW    
#define OFF HIGH

const String PASS = "123A";   
String input = "";           
int wrong = 0;              


void show(String title, String text) {
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setTextSize(1); oled.setCursor(0, 0);  oled.print(title);
  oled.setTextSize(2); oled.setCursor(0, 25); oled.print(text);
  oled.display();
}

void prompt() {
  String star = "";
  for (int i = 0; i < input.length(); i++) star += '*';
  show("Enter password (#=OK)", star);
}

void setup() {
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, OFF);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  prompt();
}

void loop() {
  char k = key.getKey();
  if (!k)
   return;

  if (k == '*')
   input = "";                         
  else if (k == '#') {                              
    if (input == PASS) {                            
      wrong = 0;
      show("ACCESS", "GRANTED");
      digitalWrite(RELAY, ON);  delay(5000);        
      digitalWrite(RELAY, OFF);
    } else if (++wrong >= 3) {                      
      for (int s = 30; s > 0; s--) {
        show("LOCKED", "Wait " + String(s) + "s");
        delay(1000);
      }
      wrong = 0;
    } else {                                        
      show("WRONG PASSWORD", "Left: " + String(3 - wrong));
      delay(2000);
    }
    input = "";
  }
  else if (input.length() < 4) input += k;          
  prompt();
}