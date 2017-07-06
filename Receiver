#include "Timer.h"
Timer t;

// LORA
#include <string.h>

#define MAX_STRING_LEN  52  //56
#define MAX_INPUT 13
char buflist[MAX_STRING_LEN];

int aux=4;
int m0=3;
int m1=2;
int i,j,k;
// LORA

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN            6         // Pin which is connected to the DHT sensor.
// Uncomment the type of sensor in use:
#define DHTTYPE           DHT22     // DHT 22 (AM2302)
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;


#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);


#include <DS3231_Simple.h>
DS3231_Simple Clock;


const int buttonPin = 7;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status


void setup()
{
// LORA
  pinMode(aux,INPUT);
  pinMode(m0,OUTPUT);
  pinMode(m1,OUTPUT);

  Serial.begin(9600);
  digitalWrite(m0,0);
  digitalWrite(m1,1);
  
  int tickEvent = t.every(2000, printTemHum);
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
    
  Serial.begin(9600);
  Clock.begin();

  dht.begin();  
//  Serial.println("DHTxx Unified Sensor Example");
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);

  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);

  // Set delay between sensor readings based on sensor details.
//  delayMS = sensor.min_delay / 1000;
  	
	// initialize the LCD
	lcd.begin();

}

void loop()
{
  t.update();
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn backLight on:
   lcd.backlight();
  } else {
    // turn backLight off:
   lcd.noBacklight();
  }  
  // Create a variable to hold the data 
  DateTime MyDateAndTime;
  
  // Ask the clock for the data.
  MyDateAndTime = Clock.read();
  
//  Serial.print("Hour: ");   Serial.println(MyDateAndTime.Hour);
//  Serial.print("Minute: "); Serial.println(MyDateAndTime.Minute);
//  Serial.print("Second: "); Serial.println(MyDateAndTime.Second);
//  Serial.print("Year: ");   Serial.println(MyDateAndTime.Year);
 // Serial.print("Month: ");  Serial.println(MyDateAndTime.Month);
//  Serial.print("Day: ");    Serial.println(MyDateAndTime.Day);

lcd.setCursor(0,0);
char dateBuf [32];
sprintf(dateBuf, "20%02d-%02d-%02d", MyDateAndTime.Year,MyDateAndTime.Month, MyDateAndTime.Day);
lcd.print(dateBuf);

lcd.setCursor(12,0);
char timeBuf [32];
sprintf(timeBuf, "%02d:%02d:%02d", MyDateAndTime.Hour,MyDateAndTime.Minute, MyDateAndTime.Second);
lcd.print(timeBuf);

// LORA READ
  digitalWrite(m0,0);
  digitalWrite(m1,1);
while (Serial.available () > 0)   {
processIncomingByte (Serial.read ());
// LORA READ
}

}

// OTHER ROUNTINE FOR LORA

void process_data (const char * data)   {
  // for now just display it
  // (but you could compare it to some value, convert to an integer, etc.)
  lcd.println (data);
  }  // end of process_data
  


void processIncomingByte (const byte inByte)  {
  static char input_line [MAX_INPUT];
  static unsigned int input_pos = 0;

  switch (inByte)  {

    case 'x':   // end of text
      input_line [input_pos] = 0;  // terminating null byte
      
      // terminator reached! process input_line here ...
      process_data (input_line);
      
      // reset buffer for next time
      input_pos = 0;  
      break;

    case '\r':   // discard carriage return
      break;

    default:
      // keep adding if not full ... allow for terminating null byte
      if (input_pos < (MAX_INPUT - 1))
        input_line [input_pos++] = inByte;
      break;

    }  // end of switch

    lcd.setCursor(0,2);
    for(i=0;i<=19;i++){
    lcd.print(input_line[i]); 
    }
 
    lcd.setCursor(0,3);
    for(i=20;i<=39;i++){
    lcd.print(input_line[i]); 
    }

  } // end of processIncomingByte  




// Function to return a substring defined by a delimiter at an index
char* subStr (char* str, char delim, int index) {
  char *act, *sub, *ptr;
  char copy[MAX_STRING_LEN];
  int i;

  // Since strtok consumes the first arg, make a copy
  strcpy(copy, str);

  for (i = 1, act = copy; i <= index; i++, act = NULL) {
     //Serial.print(".");
     sub = strtok_r(act, &delim, &ptr);
     if (sub == NULL) break;
  }
  return sub;

}
// OTHER ROUNTINE FOR LORA

void printTemHum()
{
// Print Temperature and Humidity
char temBuf[32];
char humBuf[32];

  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
//    Serial.println("Error reading temperature!");
  }
  else {
//    Serial.print("Temperature: ");
//    Serial.print(event.temperature);
//    Serial.println(" *C");
    sprintf(temBuf, "%02d.%1dC", int(event.temperature), int((event.temperature-int(event.temperature))*10));
    lcd.setCursor(0, 1);
    lcd.print(temBuf);
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
//    Serial.println("Error reading humidity!");
  }
  else {
//    Serial.print("Humidity: ");
//    Serial.print(event.relative_humidity);
//    Serial.println("%");
    lcd.setCursor(7, 1);
    lcd.print(int(event.relative_humidity));
    lcd.print("%");
  }




}
