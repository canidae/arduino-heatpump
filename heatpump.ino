#include <dhtnew.h>

DHTNEW mySensor(2);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTNEW_LIB_VERSION);
  Serial.println();

  delay(2000);  // boot time

  mySensor.setWaitForReading(true);

  uint16_t rd = 2000;
  uint16_t step = 2000;

  while (step)
  {
    step /= 2;
    mySensor.setReadDelay(rd);
    int chk = mySensor.read();

    Serial.print("ReadDelay (ms): ");
    Serial.print(mySensor.getReadDelay());
    Serial.print("\t T: ");
    Serial.print(mySensor.getTemperature(), 1);
    Serial.print("\t H: ");
    Serial.print(mySensor.getHumidity(), 1);
    Serial.print("\t");
    printStatus(chk);

    if (chk == DHTLIB_OK) rd -= step;
    else rd += step;
  }

  // safety margin of 100 uSec
  rd += 100;
  mySensor.setReadDelay(rd);
  Serial.print("\nreadDelay set to (ms) : ");
  Serial.print(mySensor.getReadDelay());
  Serial.println("\n\nDuration test started");
}

void loop()
{
  // Note: the library prevents reads faster than readDelay...
  //       it will return previous values for T & H
  int chk = mySensor.read();
  Serial.print(millis());
  Serial.print("\t");
  Serial.print(mySensor.getReadDelay());
  Serial.print("\t T: ");
  Serial.print(mySensor.getTemperature(), 1);
  Serial.print("\t H: ");
  Serial.print(mySensor.getHumidity(), 1);
  Serial.print("\t");
  printStatus(chk);
}

void printStatus(int chk)
{
  switch (chk)
  {
    case DHTLIB_OK:
      Serial.print("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT_A:
      Serial.print("Time out A error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT_B:
      Serial.print("Time out B error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT_C:
      Serial.print("Time out C error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT_D:
      Serial.print("Time out D error,\t");
      break;
    case DHTLIB_ERROR_SENSOR_NOT_READY:
      Serial.print("Sensor not ready,\t");
      break;
    case DHTLIB_ERROR_BIT_SHIFT:
      Serial.print("Bit shift error,\t");
      break;
    default:
      Serial.print("Unknown: ");
      Serial.print(chk);
      Serial.print(",\t");
      break;
  }
  Serial.println();
}
