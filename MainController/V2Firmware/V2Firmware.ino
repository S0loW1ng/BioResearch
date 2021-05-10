#include "DHT.h"
#include <PID_v2.h>
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
double Kp = 2, Ki = 5, Kd = 1;
PID_v2 myPID(Kp, Ki, Kd, PID::Direct);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin(); // initialize the sensor

  pinMode(pinHum,OUTPUT);
  pinMode(pinFan,OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(13,OUTPUT);
  while(!Serial){
    
  }
    if(Serial.available() > 0){
    coms = Serial.readString();
    Serial.println("Command Recieved" + coms);
      parseReadings(coms);
      getReadings();
      getParameters();
      startup = false;
      delay(500);

  }
   myPID.Start(dht.readHumidity(),  // input
              0,                      // current output
              relativeHGoal);        // setpoint
   myPID.SetOutputLimits(0,200);
  
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
  float in = dh
 
   
    
  

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
