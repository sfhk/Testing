

// G Zone LORA


#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "44256a1d90ac41b1bcb06893418aa483";

#define W5100_CS  10
#define SDCARD_CS 4

// use Timer library
  #include <SimpleTimer.h>
  #include <TimeLib.h>

// use RTC library
  #include <WidgetRTC.h>

// Attach virtual serial terminal to Virtual Pin V2
  WidgetTerminal terminal(V2);
 

// Activate the Timer
  SimpleTimer timer;

// Define the "Water inflow" LED indicator on the Android control panel
  WidgetLED led1(V15);
  WidgetLED led2(V16);
  WidgetLED led3(V17);
  WidgetLED led4(V18);    
  WidgetRTC rtc;

// setup A0 as input port for sensing voltage
  #define VT_PIN A0  //connect with VT
  #define ARDUINO_WORK_VOLTAGE 5.0  //working volotage of arduino
  

// Digital clock display of the time
void clockDisplay()
{
// You can call hour(), minute(), ... at any time
// Please see Time library examples for details

  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + " " + month() + " " + year();
  char thm [128];
  char dat [128];
  sprintf(thm, "%02d:%02d", hour(), minute()); 
  sprintf(dat, "%02d/%02d/%04d", day(), month(), year()); 
  Serial.print("Current time: ");
  Serial.print(currentTime);
  Serial.print(" ");
  Serial.print(currentDate);
  Serial.println();

// Send time and Date to the App
  Blynk.virtualWrite(V8, thm);
  Blynk.virtualWrite(V1, dat);
  
}

void sendSensor()
{
/*
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

//  if (isnan(h) || isnan(t)) {
//    Serial.println("Failed to read from DHT sensor!");
//    return;
//  }
*/
   int vt_temp = analogRead(VT_PIN);
   double voltage = vt_temp * (ARDUINO_WORK_VOLTAGE / 1023.0) * 5;
   Serial.print ("Voltage (V): ");
   Serial.print(voltage); 
 
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
//  Blynk.virtualWrite(V32, h);
//  Blynk.virtualWrite(V31, t);
  Blynk.virtualWrite(V38, voltage);
}
 
#define M0      22
#define M1      24
#define AUX     26


String readString;
String command;


#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 20 chars and 4 line display
  LiquidCrystal_I2C lcd(0x27, 20, 4);

 
// BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  float voltage = Serial1.parseFloat();  

}

void setup() {

  
  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card

  Blynk.begin(auth);

// define D5,D6,D7,D8  as output pin to control relay module  
  pinMode(5, OUTPUT);   // NodeMCU need to specify "D"7, D1 mini only use number 
  pinMode(6, OUTPUT);   // NodeMCU need to specify "D"7, D1 mini only use number 
  pinMode(7, OUTPUT);   // NodeMCU need to specify "D"7, D1 mini only use number 
  pinMode(8, OUTPUT);   // NodeMCU need to specify "D"7, D1 mini only use number 

// reset all relays
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);


  rtc.begin(); // start synchronise Blynk real time clock
   
// initialize the digital pins
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT); 
  pinMode(AUX, INPUT_PULLUP);

// set the RF module to mode 0 - transparent transmission
  digitalWrite(M0, HIGH);
  digitalWrite(M1, LOW);

// initialize the H/W and S/W comm ports
  Serial.begin(9600); // Computer port
  Serial1.begin(9600); // RF port

  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LORA waiting....");
  delay(2000);




  timer.setInterval(60000L, clockDisplay);  
  timer.setInterval(10000L, sendSensor);  
}

  BLYNK_WRITE(V11)   // Define V11 as Switch 1 as "Manual Control" for Android control panel
{
  // You'll get HIGH/1 at startTime and LOW/0 at stopTime.
  // this method will be triggered every day
  // until you remove widget or stop project or
  // clean stop/start fields of widget
  Serial.print("Got a value: ");
  int v11 = param.asInt();
  Serial.println(param.asStr());
if 
(v11 == 1)
{
Serial1.print("BsFGG18=rl=on");
lcd.setCursor(0,3);
lcd.print("BsFGG18=rl=on ");
led1.on();
        String rtTime = String(hour()) + ":" + minute() + ":" + second();
        String rtDate = String(day()) + "-" + month() + "-" + year();
        terminal.print("一號制手動 打開  ");
        terminal.print(rtDate);
        terminal.print("  ");
        terminal.println(rtTime);
        terminal.flush();
        Blynk.email("A 區自動灌溉系統", "一號制 手動打開 ");
}
else
{
  Serial1.print("BsFGG18=rl=off");
lcd.setCursor(0,3);
lcd.print("BsFGG18=rl=off");  
led1.off();
        String rtTime = String(hour()) + ":" + minute() + ":" + second();
        String rtDate = String(day()) + "-" + month() + "-" + year();
        terminal.print("一號制手動 關閉  ");
        terminal.print(rtDate);
        terminal.print("  ");
        terminal.println(rtTime);
        terminal.flush();
        Blynk.email("A 區自動灌溉系統", "一號制 手動關閉 ");
}

}


  BLYNK_WRITE(V12)   // Define V12 as Switch to turn on deep sleep mode
{
  // You'll get HIGH/1 at startTime and LOW/0 at stopTime.
  // this method will be triggered every day
  // until you remove widget or stop project or
  // clean stop/start fields of widget
  Serial.print("Got a value: ");
  int v12 = param.asInt();
  Serial.println(param.asStr());
if 
(v12 == 1 )
{
Serial1.print("BsFGG18=sleep");
led2.on();
        String rtTime = String(hour()) + ":" + minute() + ":" + second();
        String rtDate = String(day()) + "-" + month() + "-" + year();
        terminal.print("GG18 go to deep sleep mode");
        terminal.print(rtDate);
        terminal.print("  ");
        terminal.println(rtTime);
        terminal.flush();
 //       Blynk.email("GG18 goes to deep sleep mode");
}

}

//Serial data transceiver
void loop() 
{

  Blynk.run();
  timer.run(); // Initiates SimpleTimer
    
   int vt_temp = analogRead(VT_PIN);
   double voltage = vt_temp * (ARDUINO_WORK_VOLTAGE / 1023.0) * 5;
   
  lcd.setCursor(0,0);
  lcd.print("Central Station running");
  lcd.setCursor(0,2);
  lcd.print("Voltage = ");
  lcd.print(voltage);

  readString = "";
  
 }

