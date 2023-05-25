
// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Servo.h>

// Set these to run example.  
#define FIREBASE_HOST "mask-f003e-default-rtdb.firebaseio.com"  
#define FIREBASE_AUTH "cF5D9qvfWdIf0KBWOTL8Q2KXCGbWi6ZD9TeCcRiT"  
#define WIFI_SSID "ibrahim_2571999"  
#define WIFI_PASSWORD "ibrahim@S_25@1999$" 

bool Access_To_System = false ;
#define GreenLed D1
#define RedLed   D0
#define servo   D2

Servo myservo;  // create servo object to control a servo

void DoorOpen(void)
{
  int pos = 0;
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void CloseDoor(void)
{
  int pos = 0;
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  myservo.attach(servo);  // attaches the servo on GIO2 to the servo object
  pinMode(GreenLed , OUTPUT);
  pinMode(RedLed , OUTPUT); 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
}
void loop() {
  
    // get the Access variable
  Access_To_System = Firebase.getFloat("Access to system/Access");
  Serial.print("Access value = ");
  Serial.println(Access_To_System);

  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  else if (Access_To_System == true){
    digitalWrite(GreenLed , HIGH);
    digitalWrite(RedLed , LOW);
    DoorOpen(); // Open the door
  }
  else if(Access_To_System == false){

     digitalWrite(GreenLed , LOW);
     digitalWrite(RedLed , HIGH);
     CloseDoor(); // Close the Door 
  }
}
