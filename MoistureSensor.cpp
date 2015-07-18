//Full wet 0
//Full Dry 5v (possibly)
#include "MoistureSensor.h"

class MoistureSensor{
  private:

    const int PROBE;
    const int SENSOR;

    int wetVoltage;
    int dryVoltage;
    double moistVoltage;
    bool isDryState;
    bool isWetState;
    bool isMoistState;

    int sensorValue;
    double sensorVoltage;
  
  public:
  
  MoistureSensor(const int probePin, const int sensorPin, int wVoltage = 0, int dVoltage = 5, double mVoltage = 2.5) 
  : PROBE(probePin), SENSOR(sensorPin), wetVoltage(wVoltage), dryVoltage(dVoltage), moistVoltage(mVoltage), isDryState(true), isWetState(false), isMoistState(false) 
  {
    //setMoistVoltage(readSensor());
  }

  ~MoistureSensor(){}
  
  /*
  Power on the Probe, delay to allow stabilisation and return true if successful
  */
  bool turnOnProbe() {
    digitalWrite(PROBE, HIGH);
    delay(1000);
    return digitalRead(PROBE);
  }

  /*
  Power off the Probe and return true if successful
  */
  bool turnOffProbe() {
    digitalWrite(PROBE, LOW);
    return !digitalRead(PROBE);
  }

  /**
  Reads the Value of the Water sensor on the PIN it's on and returns a voltage
  */
  double readSensor() {
    if (!digitalRead(PROBE)){
      turnOnProbe();
    }
    //Do I need Setters???
    sensorValue = analogRead(PROBE);
    sensorVoltage = map(sensorValue, 0, 1024, 0, 5);
    turnOffProbe();

    return sensorVoltage;
  }


  /*
  Sets the the flag as to whether the sensor is reading wet, dry or moist.
  */
  void moistureLevel(double sVoltage){
    //TODO Fix this Logic...it wrong
    if(sVoltage >= getWetVoltage()) {
      setWettness(true, false, false);
    } else if(sVoltage <= getMoistVoltage() && sVoltage > getWetVoltage()) {
      setWettness(false, true, false);
    } else if(sVoltage <= getDryVoltage() and sVoltage > getMoistVoltage()) {
      setWettness(false, false, true);
    } else {
      //sensor failure as voltage below  0v (negative) or above 5v
      setWettness(false, false, false);
    }
}
  //Decide what are public and private
  /** Getters */
  int getWetVoltage() { return wetVoltage; }
  int getDryVoltage() { return dryVoltage; }
  double getMoistVoltage() { return moistVoltage; }
  bool isDry() {return isDryState; }
  bool isMoist() {return isMoistState; }
  bool isWet() {return isWetState; }

  /** Setters */
  void setWetVoltage(int wetVoltage) {  wetVoltage = wetVoltage; }
  void setDryVoltage(int dryVoltage) { dryVoltage = dryVoltage; }
  void setMoistVoltage(double moistVoltage) { moistVoltage = moistVoltage; }
  void setWettness(bool isD, bool isM, bool isW) {
      isDryState = isD;
      isMoistState = isM;
      isWetState = isW;
  }
    
};
