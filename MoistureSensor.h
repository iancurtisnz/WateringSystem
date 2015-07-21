#ifndef MOISTURESENSOR_H
#define MOISTURESENSOR_H

#include <Arduino.h>
//#include <WProgram.h>
/* Class to use a moisture sensor commonly used for the Arduino
Constructor requires 2 pins one digital for the power one analog for the readings.
An additional pin can be specified for an LED for if things go wrong. 
By Ian Curtis
19 July 2015
*/
class MoistureSensor{
  private:

    const int PROBE;
    const int SENSOR;
    const int ERROR_LED;

    double wetVoltage;
    double dryVoltage;
    double moistVoltage;
    bool isDryState;
    bool isWetState;
    bool isMoistState;

    int sensorValue;
    double sensorVoltage;

    void setWettness(bool isD, bool isM, bool isW);
    double readSensor();
    void moistureLevel(double sVoltage);
    void turnOnErrorLED();
  
  public:
  MoistureSensor(const int probePin, const int sensorPin, const int ledPin = NULL, double wVoltage = .5, double dVoltage = 4.5, double mVoltage = 2.5);
  ~MoistureSensor();

  void readProbe();

  bool turnOnProbe();
  bool turnOffProbe();
  
  int getProbe();
  int getSensor();
  int getErrorLED();

  double getWetVoltage();
  double getDryVoltage();
  double getMoistVoltage();
  
  bool isDry();
  bool isMoist();
  bool isWet();

  /** Setters */
  void setWetVoltage(double wetVoltage);
  void setDryVoltage(double dryVoltage);
  void setMoistVoltage(double moistVoltage);
};
#endif
