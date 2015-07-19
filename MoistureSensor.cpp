//Full wet 0
//Full Dry 5v (possibly)

#include <Arduino.h>
//#include <WProgram.h>

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
    bool turnOnErrorLED();
  
  public:
  MoistureSensor(const int probePin, const int sensorPin, const int ledPin = NULL, double wVoltage = .5, double dVoltage = 4.5, double mVoltage = 2.5);
  ~MoistureSensor();
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
  void setWetVoltage(int wetVoltage);
  void setDryVoltage(int dryVoltage);
  void setMoistVoltage(double moistVoltage);
};

  MoistureSensor::MoistureSensor(const int probePin, const int sensorPin, const int ledPin, double wVoltage, double dVoltage, double mVoltage) 
  : PROBE(probePin), SENSOR(sensorPin), ERROR_LED(ledPin), wetVoltage(wVoltage), dryVoltage(dVoltage), moistVoltage(mVoltage), isDryState(true), isWetState(false), isMoistState(false) 
  {
    //setMoistVoltage(readSensor());
  }

  //Destructor
  MoistureSensor::~MoistureSensor(){}
  
  /*
  Power on the Probe, delay to allow stabilisation and return true if successful
  @returns bool True if Probe is successfully turned on
  */
  bool MoistureSensor::turnOnProbe() {
    digitalWrite(PROBE, HIGH);
    delay(1000);
    return digitalRead(PROBE);
  }

  /*
  Power off the Probe and return true if successful
  @returns bool True if Probe is successfully turned off
  */
  bool MoistureSensor::turnOffProbe() {
    digitalWrite(PROBE, LOW);
    return !digitalRead(PROBE);
  }

  /**
  Reads the Value of the Water sensor on the PIN it's on and returns a voltage
  @returns double voltage read by Sensor
  */
  double MoistureSensor::readSensor() {
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
  @param double sVoltage The voltage read by the sensor
  */
  void MoistureSensor::moistureLevel(double sVoltage){
    if(sVoltage <= getWetVoltage()) {
      //Saturated
      setWettness(true, false, false);
    } else if(sVoltage <= getMoistVoltage() && sVoltage > getWetVoltage()) {
      //Moist
      setWettness(false, true, false);
    } else if(sVoltage >= getDryVoltage() and sVoltage > getMoistVoltage()) {
      //Dry
      setWettness(false, false, true);
    } else {
      //sensor failure as voltage below  0v (negative) or above 5v
      setWettness(false, false, false);
    }
}
  //Decide what are public and private
  /** Getters */
  int MoistureSensor::getProbe() { return PROBE; }
  int MoistureSensor::getSensor() { return SENSOR; }
  double MoistureSensor::getWetVoltage() { return wetVoltage; }
  double MoistureSensor::getDryVoltage() { return dryVoltage; }
  double MoistureSensor::getMoistVoltage() { return moistVoltage; }
  
  bool MoistureSensor::isDry() {return isDryState; }
  bool MoistureSensor::isMoist() {return isMoistState; }
  bool MoistureSensor::isWet() {return isWetState; }

  /** Setters */
  void MoistureSensor::setWetVoltage(int wetVoltage) {  wetVoltage = wetVoltage; }
  void MoistureSensor::setDryVoltage(int dryVoltage) { dryVoltage = dryVoltage; }
  void MoistureSensor::setMoistVoltage(double moistVoltage) { moistVoltage = moistVoltage; }
  
  /*
  Sets 3 moisture states
  @param bool isD Dry
  @param bool isM Moist
  @param bool isW Wet
  */
  void MoistureSensor::setWettness(bool isD, bool isM, bool isW) {
      isDryState = isD;
      isMoistState = isM;
      isWetState = isW;
  }
    