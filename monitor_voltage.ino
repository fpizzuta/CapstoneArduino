#include <Ethernet.h>

float R1=30000;
float R2=7500;
int led = 13;

byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char serverName[] = {192,168,1,48};
int serverPort = 8080;
EthernetClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);

// https://playground.arduino.cc/Code/WebClient/
  Serial.print(F("Starting ethernet..."));
  if(!Ethernet.begin(mac)) Serial.println(F("failed"));
  else Serial.println(Ethernet.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);
  //5 is max voltage, R is ohms resistance on arduino and 1024 is units
  float voltage = (5*sensorValue*(R1+R2))/(1024*R2);
//  Serial.println(voltage);
   if (voltage > 12) {
      Serial.println(voltage);
      digitalWrite(led,HIGH);
      if (client.connect("192.168.1.48", 8080)) {
        Serial.println("connected");
        client.println("POST /drwho HTTP/1.1");
        client.println("Host: 192.168.1.48");
        client.println("Content-Type: application/x-www-form-urlencoded");
       
        client.println("Connection: close");
        client.println("User-Agent: Arduino/1.0");
        client.println();
       
      } else {
        Serial.println("connection failed");
      }
    } 
 
delay(200);
 
}
