// Detpole
// Code to test the UV Sensor - GUVA-S12SD

#include <Arduino.h>

#define UVPIN 36			// Analog pin connected to the UV sensor

void compute_UV_Index();

float UV_voltage = 0;
String UV_index;

void setup() 
{
	Serial.begin(115200);
	pinMode(UVPIN, INPUT);

}

void loop() 
{
  	float sensorValue;
 
  	sensorValue = analogRead(UVPIN);
  	UV_voltage = sensorValue * 3.3 / 4095.0 * 1000;
  	Serial.print("sensor reading = ");
  	Serial.print(sensorValue);
  	Serial.println("");
  	Serial.print("sensor voltage = ");
  	Serial.print(UV_voltage);
  	Serial.println(" mV");
  	delay(1000);
}

void compute_UV_Index()
{
	if (UV_voltage >= 0 && UV_voltage < 227)
		UV_index = "0";
	
	else if (UV_voltage >= 227 && UV_voltage < 318)
		UV_index = "1";
	
	else if (UV_voltage >= 318 && UV_voltage < 408)
		UV_index = "2";
	
	else if (UV_voltage >= 408 && UV_voltage < 503)
		UV_index = "3";
	
	else if (UV_voltage >= 503 && UV_voltage < 606)
		UV_index = "4";
	
	else if (UV_voltage >= 606 && UV_voltage < 696)
		UV_index = "5";
	
	else if (UV_voltage >= 696 && UV_voltage < 795)
		UV_index = "6";
	
	else if (UV_voltage >= 795 && UV_voltage < 881)
		UV_index = "7";
	
	else if (UV_voltage >= 881 && UV_voltage < 976)
		UV_index = "8";
	
	else if (UV_voltage >= 976 && UV_voltage < 1079)
		UV_index = "9";
	
	else if (UV_voltage >= 1079 && UV_voltage < 1170)
		UV_index = "10";
	
	else
		UV_index = "11";
}
