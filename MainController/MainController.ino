#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);


int pinSensor = 2;
int pinHum = 5;
int in1 = 10;
int in2 = 11;
int pinFan = 6; 

float temperatureGoal = 0;
float relativeHGoal = 0; 
boolean startup = true;

const String comtemplate ="000/00.00/000" ;// hum/temp/pwm 
const int sizeOfCom = comtemplate.length();
String coms = "";

float currentTemp = 0;
float currentH = 0;
int pwm = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin(); // initialize the sensor

  pinMode(pinHum,OUTPUT);
  pinMode(pinFan,OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(13,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    coms = Serial.readString();
    Serial.println("Command Recieved" + coms);
      parseReadings(coms);
      getReadings();
      getParameters();
      startup = false;
      delay(500);

  }
  if(startup == false){
   if(currentH !=  relativeHGoal){
    if(currentH < relativeHGoal){
      analogWrite(pinHum,255);
      delay(500);
      
    }else if(currentH > relativeHGoal +2){
      analogWrite(pinHum,000);
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      analogWrite(pinFan,pwm);
      delay(500);
    }
   }
    
  }

delay(1000);

}
void parseReadings(String str){
 if(str.charAt(3)=='/' && str.charAt(6) == '.' && str.charAt(9) == '/'){
   relativeHGoal =  str.substring(0,3).toFloat();
   //Serial.println(relativeHGoal);
   
   temperatureGoal = str.substring(4,9).toFloat();
  // Serial.println(temperatureGoal);
   pwm = str.substring(10).toInt();
   //Serial.println(pwm);

 }
}
void getParameters(){
Serial.print(currentH);
Serial.print("/" );
Serial.print(currentTemp);
Serial.print("/");
Serial.println(pwm);


  
}

 void getReadings(){
    // read humidity
  currentH  = dht.readHumidity();
  // read temperature as Celsius
  currentTemp = dht.readTemperature();
   Serial.print("Humidity: ");
    Serial.print(currentH);
    Serial.print("%");

    Serial.print("  |  "); 

    Serial.print("Temperature: ");
    Serial.print(currentTemp);
    Serial.println("°C ~ ");
 
}
