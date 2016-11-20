#include <core.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "remoteTemp.h"
#include "read_temp.h"

using namespace core;

idType idTemp;

// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(TEMP_SENSOR_PIN);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

DeviceAddress addr;

void readTemp() {
  Serial.print(F("Requesting Temperature..."));
  /* if (!sensors.requestTemperaturesByAddress((uint8_t*)addr)) { */
  if (!sensors.requestTemperaturesByIndex(0)) {
    Serial.println(F("DS18B20 disconnected"));
    return;
  }

  Serial.println("DONE");

  /* float tempf = sensors.getTempC((uint8_t*)addr); */
  float tempf = sensors.getTempCByIndex(0);
  int16_t temp = int16_t(tempf * 10);
  store::setAnalog(idTemp, temp);

  Serial.print(F("Temp: "));
  Serial.print(tempf);
  Serial.print(" ");
  Serial.println(temp);
}

void setupReadTemp() {
  if (!sensors.getAddress(addr, 0)) {
    Serial.println(F("Get DS18B20 address failed"));
    return;
  }

  sensors.setResolution(12);

  idTemp = store::defineAnalog();
  
  clock::interval(5000, &readTemp);
}
