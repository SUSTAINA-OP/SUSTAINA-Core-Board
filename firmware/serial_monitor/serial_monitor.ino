#include "./src/INA226.h"
#include "Wire.h"

// number of sensors to be mounted
const int numSensors = 4;

// array of sensor objects
INA226 sensors[numSensors] = {
  INA226(0x40),
  INA226(0x41),
  INA226(0x42),
  INA226(0x43)
};

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  for (int i = 0; i < numSensors; i++)
  {
    if (!sensors[i].begin())
    {
      Serial.println("Could not connect to sensor. Fix and Reboot");
      while (1);
    }
    sensors[i].setMaxCurrentShunt(20, 0.002);
  }
}

void loop()
{
  for (int i = 0; i < numSensors; i++)
    printSensorData(sensors[i]);

  Serial.print("\n \n");
  delay(10);
}

void printSensorData(INA226 & sensor)
{
  Serial.print("ADDRESS: 0x");
  Serial.print(sensor.getAddress(), HEX);
  Serial.print(" \t");

  Serial.print("BUS: ");
  Serial.print(sensor.getBusVoltage(), 5);
  Serial.print(" V\t");

  Serial.print("CURRENT: ");
  Serial.print(sensor.getCurrent_mA(), 5);
  Serial.println(" mA\t");
}
