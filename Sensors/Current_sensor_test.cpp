// Detpole
// Code to test the Current Sensor - ACS712

#include <Arduino.h>

#define CURRENT_PIN 33

const int Nread = 500;	// number of reads of the input value of the sensor before averages it

long int sensorValue = 0;

float Scale_factor = 185.0;	// Sensor scale factor - 185 mV/A 
float Vref = 2159;		// Voltage (mV) with no current flowing

void setup() 
{
	Serial.begin(115200);
	pinMode(CURRENT_PIN, INPUT);
}

void loop() 
{
	// Read the value Nread times:
  	for (int i = 0; i < Nread; i++)
	{
    	sensorValue += analogRead(CURRENT_PIN);
		delay(5);
	}

	sensorValue = sensorValue / Nread;	// Average Value

	float voltage = sensorValue * 3.3 / 4095.0 * 1000; // Voltage (mV)
	float current = ((voltage - Vref) / Scale_factor) * 1000;	// current (mA)

	Serial.print("\nVoltage (current): ");
	Serial.print(voltage);
	Serial.print(" mV\n");
	Serial.print("Current: "); 
	Serial.print(current);
	Serial.print(" mA\n");

	sensorValue = 0;	// Reset the sensorValue for the next reading
}
