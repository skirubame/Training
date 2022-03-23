#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
char auth[] = "EqF6GGkVt_kFgBJHIX0v32TrFcc_Wxy5"; // blynk token
char ssid[] = "";   //ssid
char pass[] = "";    //password
int readD1;
int readD2;
int moisture_sensor1;
int moisture_sensor2;
int Pin_D1 = 5;
int Pin_D2 = 4;
int Pin_D4 = 2;
#define DHTPIN 0 
#define DHTTYPE DHT11 
const int dry = 600; // value for dry sensor
const int wet = 200; // value for wet sensor
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
const int dry = 600; // value for dry sensor
const int wet = 200; // value for wet sensor
void setup() 
{ 
  Serial.begin(9600);
  pinMode(Pin_D1,OUTPUT);
  pinMode(Pin_D2,OUTPUT);
  pinMode(Pin_D4,OUTPUT);
  pinMode(A0,INPUT);
  
  dht.begin();
  timer.setInterval(1000L, sendSensor);
  Blynk.begin(auth, ssid, pass);
}
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  Blynk.virtualWrite(V7, t);
  Blynk.virtualWrite(V8 , h);
}
void loop() 
{
   Blynk.run();
  //for first sensor
  digitalWrite(Pin_D1, HIGH);     //Turn D1 On
  delay(100);                     
  readD1 = analogRead(0);       //Read Analog value of first sensor
  digitalWrite(Pin_D1, LOW);      //Turn D1 Off
  delay(100);   
 //for second sensor
  digitalWrite(Pin_D2, HIGH);     //Turn D2 On
  delay(100);                     
  readD2 = analogRead(0);       //Read Analog value of second sensor
  digitalWrite(Pin_D2, LOW);      //Turn D2 Off
  delay(100); 
  moisture_sensor1=map(readD1, wet, dry, 100, 0);
  moisture_sensor2=map(readD2, wet, dry, 100, 0);
  //to the serial monitor
  Serial.print("sensor 1 = ");   
  Serial.print(readD1);
  Serial.print(" / sensor 2 = ");   
  Serial.println(readD2);
  if (moisture_sensor2<=50)
   {
    digitalWrite(Pin_D4,HIGH);
    delay(10);
    }
if (moisture_sensor2>50)
   {
    digitalWrite(Pin_D4,LOW);
    delay(10);
    }
  Blynk.virtualWrite(V5, moisture_sensor1);  // to Blynk server
  Blynk.virtualWrite(V6, moisture_sensor2);  // to Blynk server
  timer.run();  
}
 
