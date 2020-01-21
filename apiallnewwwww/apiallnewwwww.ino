#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

const char* ssid = "DC";
const char* password = "CastaLia";

SoftwareSerial NodeMCU(D2,D3);

void setup() 
{
  Serial.begin(9600);
  NodeMCU.begin(4800);

  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting...");
  }
}

void loop() 
{
  if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http; //Object of class HTTPClient
    //http.begin("http://jsonplaceholder.typicode.com/users/1");
    http.begin("http://my-json-server.typicode.com/rajuAhmed1705/demo/update");
    int httpCode = http.GET();

    if (httpCode > 0) 
    {

        const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 30;
        DynamicJsonBuffer jsonBuffer(capacity);
        
        const char* json = "[{\"counter\":5,\"queue\":565}]";
        
        JsonArray& root = jsonBuffer.parseArray(http.getString());
        
        int root_0_counter = root[0]["counter"]; // 5
        int root_0_queue = root[0]["queue"]; // 565


        root.printTo(Serial);
        Serial.println(root_0_counter);
        Serial.println(root_0_queue);
        

        //char *msg = strcat(strcat("C-",root_0_counter),strcat("Q-",root_0_queue));
        //Serial.println(*msg);

        //NodeMCU.print("C-%d Q-%d",root_0_counter,root_0_queue);
        //NodeMCU.println("\n");
        //NodeMCU.print(root_0_queue);
        //NodeMCU.println("\n");

        root.printTo(NodeMCU);



    }
    http.end(); //Close connection
  }
  delay(1000);
}
