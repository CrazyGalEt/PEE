// Detpole - André Brandão
// Humidity and Temperature  Sensor - DHT11
// UV Sensor - GUVA-S12SD 

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library
// - Adafruit Unified Sensor

#include <DHT.h>

void compute_UV_Index();

#define DHTPIN 4		// Digital pin connected to the DHT sensor
#define DHTTYPE DHT11

#define UVPIN 36			// Analog pin connected to the UV sensor

DHT dht(DHTPIN, DHTTYPE);	// Initialize DHT sensor.

float temperature = 0, humidity = 0;
int UV_voltage = 0;
String UV_index;

void setup()
{
	Serial.begin(115200);

	dht.begin();	// Start DHT sensor
	
	pinMode(UVPIN, INPUT);
}

void loop()
{
	humidity = dht.readHumidity();			// read humidity value
	temperature = dht.readTemperature();	// read temperature value as Celsius

	UV_voltage = analogRead(UVPIN) * 3.3 * 1000 / 4095; // UV voltage mV 	
	
	compute_UV_Index();
	
	// checking for errors in DHT sensor values
	if (isnan(humidity) || isnan(temperature))	
	{
		Serial.print("Failed to read from DHT sensor!\n");
		delay(5000);	// Wait 5 seconds between measurements
		return;		// go back to loop
	}

	Serial.print("\nTemperature: ");
	Serial.print(temperature);
  	Serial.print("\nHumidity: ");
  	Serial.print(humidity);
	Serial.print("\nUV voltage: ");
  	Serial.print(UV_voltage);
  	Serial.print(" (mV)");
	Serial.print("\nUV Index: ");
  	Serial.print(UV_index);
  	Serial.print("\n");

	delay(5000);	// Wait 5 seconds between measurements
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
