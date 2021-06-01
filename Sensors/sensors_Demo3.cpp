// Detpole
// Humidity and Temperature  Sensor - DHT11
// UV Sensor - GUVA-S12SD 

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library
// - Adafruit Unified Sensor
// - PubSubClient

#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <esp_task_wdt.h>

void connect_wifi();
void connect_mqtt();
void callback(char*, byte*, unsigned int);
void sensors_read_publish();
void compute_UV_Index();

#define DHTPIN 4		// Digital pin connected to the DHT sensor
#define DHTTYPE DHT11

#define UVPIN 36			// Analog pin connected to the UV sensor

DHT dht(DHTPIN, DHTTYPE);	// Initialize DHT sensor.

float temperature = 0, humidity = 0;
int UV_voltage = 0;
String UV_index;

// Wifi credentials 
const char* wifi_ssid = "Wifi";
const char* wifi_password = "12345";

// MQTT server IP and port
const char* mqtt_server_ip = "192.168.1.71";
const int mqtt_server_port = 1883;

// MQTT user and password
const char* mqtt_user = "iot";	
const char* mqtt_password = "iot";	



WiFiClient esp32;
PubSubClient client(esp32);

void setup()
{
	Serial.begin(115200);
	esp_task_wdt_init(2400, true);		// Set watchdog timeout (seconds) and panic handle
	
	connect_wifi();	// Connect wifi
	
	client.setServer(mqtt_server_ip, mqtt_server_port);
  	client.setCallback(callback);
	
	dht.begin();	// Start DHT sensor
	
	pinMode(UVPIN, INPUT);
}

void loop()
{
	if (!client.connected())
     	connect_mqtt();
  	
	client.loop();		// Keep MQTT connected
}

void connect_wifi()
{
	Serial.print("\nConnecting to wifi");
	
	// connecting to WiFi
	WiFi.begin(wifi_ssid, wifi_password);

	while (WiFi.status() != WL_CONNECTED)	// Wait until connected
	{
		delay(500);
		Serial.print(".");
	}

	Serial.println("WiFi connected");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
}

void connect_mqtt()
{
	// Connect to MQTT
	while (!client.connected())
	{
		Serial.print("Attempting MQTT connection...");
		
		if (client.connect("ESP32Client", mqtt_user, mqtt_password))	// Attempt to connect
		{
			Serial.println("connected");
			client.subscribe("sensores/request");	
		}
		else
		{
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			
			delay(5000);	// Wait 5 seconds before retrying
		}
	}
}

void callback(char* topic, byte* payload, unsigned int length)
{
	Serial.print("Message arrived on topic: ");
  	Serial.print(topic);
  	
  	
  	if (String(topic) == "sensores/request")
		sensors_read_publish();
}

void sensors_read_publish()
{
	humidity = dht.readHumidity();			// read humidity value
	temperature = dht.readTemperature();	// read temperature value as Celsius
	
	delay(300);
	UV_voltage = analogRead(UVPIN) * 3.3 * 1000 / 4095; // UV voltage mV
	compute_UV_Index();

	// checking for errors in DHT sensor values
	if (isnan(humidity) || isnan(temperature))	
	{
	 	Serial.print("\nFailed to read from DHT sensor!\n");
	 	return;
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

	// Convert values to a char array
	char temperature_char[6], humidity_char[6], uv_index_char[3];
    
	dtostrf(temperature, 1, 2, temperature_char);
	dtostrf(humidity, 1, 2, humidity_char);
	UV_index.toCharArray(uv_index_char, 3);

	
	// Send temperature and humidity values to raspberry - MQTT Publish
	client.publish("temperature", temperature_char);
	client.publish("humidity", humidity_char);
	client.publish("uv_index", uv_index_char);
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
