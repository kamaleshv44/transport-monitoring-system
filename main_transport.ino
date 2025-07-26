
// Smart Crop Field Protection & Automated Irrigation - Arduino Sketch

#include <SimpleDHT.h>
#include <Wire.h>  // library for I2C protocol 
#include <LiquidCrystal_I2C.h> // library for I2C LCD  
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display 
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9,10);
char msg;
char call;

#define led 13 //Buzzer
#define led1 7 //Water Pump
#define led2 8 //fan
#define led3 11 //Relay For teg Module

#define sensorpin A0 //Gas Sensor
#define sensorpin1 A1 // Flame Sensor
#define sensorpin2 A2 // Water Leakage sensor



// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 16
int pinDHT11 = 12; // Humidity
SimpleDHT11 dht11(pinDHT11);


void setup() 
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);// Setting the baud rate of Serial Monitor (Arduino)
  lcd.init();
  lcd.backlight(); // backlight ON 
  lcd.setCursor(0,0); 
  lcd.print("Smart");  
  lcd.setCursor(2,1);  
  lcd.print("Monitoring"); 
  // put your setup code here, to run once:
 
  delay(1000);
  lcd.clear();
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(sensorpin, INPUT);
  pinMode(sensorpin1, INPUT);
  pinMode(sensorpin2, INPUT);

  digitalWrite(led, LOW); //Buzzer
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);


 

}

void loop() 
{

// start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Tempature  "); lcd.print((int)temperature);
  lcd.setCursor(0, 1);
  lcd.print("Humidity  ");
  lcd.print((int)humidity);
  delay(1000);

if (temperature > 28)//Change the Temperature value
{
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("HIGH Temp");
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW); //Teg Module
SendMessage();
}

if (temperature < 28)//Change the Temperature value
{
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH); //Teg module
}


if (digitalRead(sensorpin)==LOW) // Gas Sensor
{
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("GAS LEAKAGE");
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  digitalWrite(led2, HIGH);
  delay(3000);
  digitalWrite(led2, LOW);
  lcd.clear();

  SendMessage1();
}

/*
if (digitalRead(sensorpin)==HIGH) // Gas Sensor
{
  digitalWrite(led2, LOW);
}
*/

if (digitalRead(sensorpin1)==LOW) // Flame Sensor
{
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("FIRE ALERT");
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  digitalWrite(led1, HIGH);
  delay(3000);
  digitalWrite(led1, LOW);
  lcd.clear();

  SendMessage2();
}

/*
if (digitalRead(sensorpin1)==HIGH) // Flame Sensor
{
  digitalWrite(led1, LOW);
}
*/

if (digitalRead(sensorpin2)==LOW)// Water Sensor
{
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("WATER LEAKAGE");
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(3000);

  lcd.clear();
  SendMessage3();
}

/*
if (digitalRead(sensorpin2)==HIGH) // Water Sensor
{

}
*/

}

void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);

  mySerial.println("HIGH TEMPERATURE, Location: https://maps.app.goo.gl/yH3UmfdAGpFHh8bN6");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void SendMessage1()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);

  mySerial.println("GAS LEAKAGE, Location: https://maps.app.goo.gl/yH3UmfdAGpFHh8bN6");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void SendMessage2()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);

  mySerial.println("FIRE ALERT, Location: https://maps.app.goo.gl/yH3UmfdAGpFHh8bN6");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void SendMessage3()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);

  mySerial.println("WATER LEAKAGE, Location: https://maps.app.goo.gl/yH3UmfdAGpFHh8bN6");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}