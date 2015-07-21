#include "MoistureSensor.h"

MoistureSensor waterLevel(1,2,3);
MoistureSensor plantSoil(4,5,6);

const int EMPTY_LED_PIN = 7;
const int WATERING_LED_PIN = 8;
const int MOTOR_PIN = 10;


void setup() {
  waterLevel.readProbe();
  plantSoil.readProbe();
}

void loop() {
  //Check tank level
  waterLevel.readProbe();
  while (waterLevel.isDry())
  	{
      digitalWrite(EMPTY_LED_PIN, HIGH);
  		delay(100000);//if low send warning
  	}
  digitalWrite(EMPTY_LED_PIN, LOW);
  //check plant moisture
  plantSoil.readProbe();
  while (plantSoil.isDry())
  {
  		//Run Motor for x time
      digitalWrite(WATERING_LED_PIN, HIGH);
  		delay(60000); //wait for moisture to seep through
  		plantSoil.readProbe();

  }
  digitalWrite(WATERING_LED_PIN, LOW);
  
  //Delay x amount of time or powerdown for 1 day


}


