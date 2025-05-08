#include <DHT.h> // source: https://github.com/adafruit/DHT-sensor-library

#define PIN_DHT_SENSOR_READ 2  // pin for reading the temperature and humidity sensor
#define PIN_DHT_SENSOR_POWER 3 // pin for powering the temperature and humidity sensor
#define PIN_RELAY_FOR_FAN 13   // pin for the relay control that powers the 12v fan

DHT dht(PIN_DHT_SENSOR_READ, DHT11);
float humidity = 0.0;
float temperature = 0.0;

void setup() {
  pinMode(PIN_DHT_SENSOR_POWER, OUTPUT);
  pinMode(PIN_RELAY_FOR_FAN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(PIN_RELAY_FOR_FAN, LOW); 
  digitalWrite(PIN_DHT_SENSOR_POWER, LOW);
}

void loop() {  
  readSensor();  
  if (ventilationIsNecessary()) {
    turnFanOn();
  } else {
    turnFanOff();
  }
  operateOrWaitFor10Minutes();
}

void readSensor() {
  digitalWrite(PIN_DHT_SENSOR_POWER, HIGH);
  delay(1000);
  dht.begin();
  delay(1000);
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  digitalWrite(PIN_DHT_SENSOR_POWER, LOW);
}

bool ventilationIsNecessary() {
  return humidity > 55.0 || temperature > 35.0;
}

void turnFanOn() {
  digitalWrite(LED_BUILTIN, HIGH); 
  digitalWrite(PIN_RELAY_FOR_FAN, HIGH);
}

void turnFanOff() {
  digitalWrite(LED_BUILTIN, LOW); 
  digitalWrite(PIN_RELAY_FOR_FAN, LOW);
}

void operateOrWaitFor10Minutes() {
  delay(600000);
}
