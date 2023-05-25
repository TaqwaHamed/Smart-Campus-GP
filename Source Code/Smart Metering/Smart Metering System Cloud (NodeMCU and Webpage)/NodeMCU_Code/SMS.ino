/*********************
 *********************
 Smart Metering System
 *********************
 *********************/


#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

WiFiClient client;


const char ssid[] = "ahmed22_2";
const char password[] = "ahmed_22_2 ";


long myChannelNumber = 1778102;
const char WriteAPIKey[] = "5MHPOB3W756JOK1V";
const char ReadAPIKey[] = "7H03YP3U8S8RBXUR";

unsigned int Voltage_Field = 1;
unsigned int Current_Field = 2;
unsigned int PF_Field = 3;
unsigned int Power_Field = 4;
unsigned int Load_Status_Field = 5;

// Variables to store reading Values from Fields of Tingspeak
 float Voltage_Value;
 float Current_Value ;
 float PF_Value ;
 float Power_Value =0 ;
unsigned int Load_Status = 1 ;

// check status of server
int statusCode = 0;

// Local Variables

const int PushButton = 16; //D0
const int LED = 5;   // D1



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial1.begin(9600);
  
  WiFi.begin( ssid , password );
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  // begain server
  ThingSpeak.begin(client);
}

void loop() {
  // take values from ATmega32
    Voltage_Value = 220;
    Current_Value = 0.322 ;
    PF_Value = 1;
    Power_Value = 0.4568 ;

    if(Serial1.available()){
    Voltage_Value = Serial1.read();
    Serial.print("Voltage is received" Voltage_Value);
    }
    if(Serial1.available()){
    Current_Value = Serial1.read();
    Serial.print("Current is received" Current_Value);
    }
    if(Serial1.available()){
    PF_Value = Serial1.read() / 100.0;
    Serial.print("PF is received" PF_Value);
    }
    if(Serial1.available()){
    Power_Value = Serial1.read() / 100.0;
    Serial.print("Power is received" Power_Value);
    }

    Serial1.write(Load_Status);
    delay(500);
    
  // Write and Read From Server
    // Write Voltage , Current , PF and Power
  ThingSpeak.writeField(myChannelNumber, Voltage_Field, Voltage_Value , WriteAPIKey);
   delay(15500); // need 15sec to Write Again in channel.
  ThingSpeak.writeField(myChannelNumber, Current_Field, Current_Value , WriteAPIKey);
  delay(15500); // need 15sec to Write Again in channel.
  ThingSpeak.writeField(myChannelNumber, PF_Field     , PF_Value      , WriteAPIKey);
  delay(15500); // need 15sec to Write Again in channel.
  ThingSpeak.writeField(myChannelNumber, Power_Field  , Power_Value   , WriteAPIKey);
  delay(15500); // need 15sec to Write Again in channel.
  
   // Read Load_Status
  Load_Status = ThingSpeak.readLongField(myChannelNumber, Load_Status_Field, ReadAPIKey);  
  // Check the status of the read operation to see if it was successful
  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    Serial.println("Load Status: " + String(Load_Status));
    
  }
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }
  
  delay(15000); // No need to read the temperature too often.
  delay(2000);
}
