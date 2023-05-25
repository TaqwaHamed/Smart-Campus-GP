/*********************
 *********************
   Smart Parking System
 *********************
 *********************/
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

WiFiClient client;


const char ssid[] = "ahmed22_2";
const char password[] = "ahmed_22_2 ";


long myChannelNumber = 1796003;
const char WriteAPIKey[] = "H87CW1V9KKM1UB9O";
const char ReadAPIKey[] = "SQEZK7PL2UYDFX42";

// Fields of Tingspeak
unsigned int USER_ID_Enter_Field = 1;
unsigned int USER_ID_Exit_Field = 2;

// Variables to store reading Values from Fields of Tingspeak
int USER_Status_Value;
int USER_ID_Value;
int USER_ID_Enter_Value;
int USER_ID_Exit_Value;
// Local Variables

const int PushButton = 16; //D0
const int LED = 5;   // D1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

   Serial1.begin(9600);
  // 
  WiFi.begin( ssid , password );
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  
  ThingSpeak.begin(client);
}

void loop() {
  // init to try only
  USER_ID_Enter_Value = 113;
 USER_ID_Exit_Value = 103;
  // receive id from ATmega32
  if( Serial.available()){
    USER_ID_Value = Serial1.read();
    }
    if( Serial.available()){
    USER_Status_Value = Serial1.read();
    }
    
    if(USER_Status_Value == 'e'){
      USER_ID_Enter_Value = USER_ID_Value;
      ThingSpeak.writeField(myChannelNumber, USER_ID_Enter_Field, USER_ID_Enter_Value , WriteAPIKey);
      delay(15000);
    }else{
        
      ThingSpeak.writeField(myChannelNumber, USER_ID_Exit_Field, USER_ID_Exit_Value , WriteAPIKey);
      delay(15000);
        
     }
 
  
 Serial.println("ID : "+ String(USER_ID_Value)+" Is Sent Correctly");
  delay(15000); // need to wait to next reading.
  delay(2000);
 
}
