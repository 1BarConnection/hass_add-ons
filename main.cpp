#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

int relay = 0;

const char* mqtt_server = "192.168.1.254";
const char* mqtt_username = "hass";
const char* mqtt_password = "geshoMierie7aikoo5xaejoHeLahPhae4eipaemoh0yahzoj1diethaeYahghaer";
WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message: ");

  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];  // convert *byte to String
  }
   Serial.print(message);
  if(message == "0") {digitalWrite(relay,LOW);}
  if(message == "1") {digitalWrite(relay,HIGH);}

  Serial.println();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(relay,OUTPUT);

  Serial.begin(115200);
  Serial.println("Readings will apear here.");

  WiFi.begin("ssid","password"); // enter wifi ssid and password
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server,1883);
  client.setCallback(callback);

  if(client.connect("Light",mqtt_username,mqtt_password)){
    Serial.println("Light - MQTT - OK");
    client.subscribe("inLight");
  }else{
    Serial.println("Light - MQTT - ERROR");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  client.loop();
}