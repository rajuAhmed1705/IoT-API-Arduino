/*
  Scrolling alphabet demo, displays characters one at a time into a scrolling box.
 */
#include <SoftwareSerial.h>
#include <SPI.h>
#include <DMD2.h>
#include <ArduinoJson.h>
#include <fonts/SystemFont5x7.h>
#include <fonts/Arial14.h>

SoftwareSerial ArduinoUno(3,2);
// Set Width to the number of displays wide you have
const int WIDTH = 1;

// You can change to a smaller font (two lines) by commenting this line,
// and uncommenting the line after it:
//const uint8_t *FONT = Arial14;
const uint8_t *FONT = SystemFont5x7;

SPIDMD dmd(WIDTH,1);  // DMD controls the entire display
DMD_TextBox box(dmd);  // "box" provides a text box to automatically write to/scroll the display

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  ArduinoUno.begin(4800);
  dmd.setBrightness(30);
  dmd.selectFont(FONT);
  dmd.begin();
}

// the loop routine runs over and over again forever:
void loop() {

    while(ArduinoUno.available()>0){
      const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 30;
      DynamicJsonBuffer jsonBuffer(capacity);
        
      const char* json = "[{\"counter\":5,\"queue\":565}]";
        
      JsonArray& root = jsonBuffer.parseArray(ArduinoUno);

      if(root == JsonObject::invalid()){
        return;
        }

      int counter = root[0]["counter"];
      int queue = root[0]["queue"];

      char *Co = "C-";
      char *Qu = "Q-";
      char next[10];

      sprintf(next, " %s%d %s%d", Co,counter, Qu,queue);

      char temp[10];

      if(temp != next){
         box.clear();
         dmd.clearScreen();
         for(int i = 0;i<10;i++) {
         Serial.print(next[i]);
         box.print(next[i]);
         temp[i] = next[i];
          }
        delay(10000);
       }
   }
   
}
