/*********************
 *********************
   Smart Light System
 *********************
 *********************/

#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

WiFiClient client;


const char ssid[] = "ahmed22_2";
const char password[] = "ahmed_22_2 ";


long myChannelNumber = 1779547;
const char WriteAPIKey[] = "G1K3I3AMBDPZY27Y";
const char ReadAPIKey[] = "GB4QAFESQ82J9GI3";

// Fields of Tingspeak
unsigned int Sunrise_Field = 1;
unsigned int Control_Field = 2;
unsigned int Sunset_Field  = 3;

// Variables to store reading Values from Fields of Tingspeak
unsigned int Sunrise_Value;
unsigned int Sunset_Value ;
unsigned int Control_Value ;

// check status of server
int statusCode = 0;


//// Local Variables

unsigned char SUNSET_HOURS=6;
unsigned char SUNSET_MIN=15;
unsigned char SUNRISE_HOURS = 17;
unsigned char SUNRISE_MIN = 20;


unsigned char RTC_HOURS = 0;
unsigned char RTC_MIN = 0;
unsigned char RTC_SEC = 0;

String Time;
//
const int PushButton = 16; //D0
const int LED = 5;   // D1


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // begin Serial1 
  Serial1.begin(9600);
  // Pins Mode
  pinMode(PushButton,INPUT);
  pinMode(LED,OUTPUT);
  
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

   // Start Reading Data from Server
        // Read Sunrise Value
  Sunrise_Value = ThingSpeak.readLongField(myChannelNumber, Sunrise_Field, ReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    Serial.println("Sunrise: " + String(Sunrise_Value));
  }
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }
  
 Sunset_Value = ThingSpeak.readLongField(myChannelNumber, Sunset_Field, ReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    Serial.println("Sunset: " + String(Sunset_Value));
  }
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }

   Control_Value = ThingSpeak.readLongField(myChannelNumber, Control_Field, ReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    Serial.println("Load_Status: " + String(Control_Value));
  }
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }

  Time = ThingSpeak.readCreatedAt(myChannelNumber, ReadAPIKey);
  Serial.println(Time);

  RTC_HOURS = ((Time[11] - '0') * 10) + (Time[12] - '0') + 2;
  if (RTC_HOURS > 24){RTC_HOURS = (((Time[11] - '0') * 10) + (Time[12] - '0') + 2) - 24;}
  RTC_MIN = ((Time[14] - '0' )* 10) + (Time[15] - '0');
  RTC_SEC = ((Time[17] - '0')* 10) + (Time[18] - '0');
  
  SUNSET_HOURS = (Sunset_Value / 100);
  SUNSET_MIN = Sunset_Value - (SUNSET_HOURS*100);
  SUNRISE_HOURS = (Sunrise_Value / 100);
  SUNRISE_MIN = Sunrise_Value - (SUNRISE_HOURS*100);
  
Serial.println(SUNSET_HOURS);
Serial.println(SUNSET_MIN);
Serial.println(SUNRISE_HOURS);
Serial.println(SUNRISE_MIN);
Serial.println(RTC_HOURS);
Serial.println(RTC_MIN);
Serial.println(RTC_SEC);

   digitalWrite(LED,LOW);
  if(digitalRead(PushButton) == HIGH){
    
    digitalWrite(LED,HIGH);
    
     Serial1.write(RTC_HOURS);
     delay(500);

     Serial1.write(RTC_MIN);
     delay(500);

     Serial1.write(RTC_SEC);
     delay(500);
     
     Serial1.write(SUNRISE_HOURS);
     delay(500);

     Serial1.write(SUNRISE_MIN);
     delay(500);
     
     Serial1.write(SUNSET_HOURS);
     delay(500);

     Serial1.write(SUNSET_MIN);
     delay(500);
     
     Serial.println("Control Value Should be Transfered" );
    }




  
 // delay(15000); // need to wait to next reading.
  delay(2000);
 
}
