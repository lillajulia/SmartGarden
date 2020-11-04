int tempSensor; // raw data from TMP36

int tempSensorPin = 0; // the pin where TMP36 is plugged in

int potentioPin = 1; // pin of the potentiometer

int pingPin = 7; //ping pin if the UDS 

float duration; //  ping duration of UDS

float distance; // distance of UDS

int waterPumpPin = 2; //pin of the DC motor

int heatLampPin = 4; // pin of the heat lamp

int minHumidity = 800; // minimum humidity value
 
float minTemp = 24; //minimum required temperature

int ledPin = 13; // pin of the led light

int minWaterLevel = 30; // minimum water level in cm 



void setup()
{
  pinMode(waterPumpPin, OUTPUT);

  pinMode(heatLampPin, OUTPUT);

  pinMode (ledPin, OUTPUT);
  
  Serial.begin(9600);
}



void loop()
{
  SoilHumidityControl();

  TemperatureControl();

  WatertankLevel();
      Serial.println(distance);


}

void TemperatureControl () {

  tempSensor = analogRead(tempSensorPin); //read the sensor from the given pin

  float voltRead = tempSensor * 5.0 ; //convert raw data from sensor to voltage

  voltRead /= 1024.0;

  float temperatureCelsius = (voltRead - 0.5 ) * 100;

  //Serial.println(temperatureCelsius); // returns celsius -40-125

  if (temperatureCelsius < minTemp) {

    digitalWrite(heatLampPin, HIGH);
  }
  else if (temperatureCelsius >= minTemp) {

    digitalWrite(heatLampPin, LOW);

  }
}

void WatertankLevel() {
  
  pinMode (pingPin, OUTPUT);

  digitalWrite(pingPin, LOW);

  delayMicroseconds(2);

  digitalWrite( pingPin, HIGH);

  delayMicroseconds(10);

  digitalWrite(pingPin, LOW);

  pinMode (pingPin, INPUT);

  duration = pulseIn(pingPin, HIGH);

  distance = (duration / 2) * 0.0343;//speed of sound

  if (distance > minWaterLevel) {

    digitalWrite(ledPin, HIGH);
  }
  else if (distance < minWaterLevel) {

    digitalWrite(ledPin, LOW);

  }
}

void SoilHumidityControl() {
  
 int potentiometer = analogRead(potentioPin); // read potentiometer data from pin

  //Serial.println(potentiometer); // returns data from 0-1023

  if (potentiometer > minHumidity) {

    digitalWrite(waterPumpPin, LOW);
  }
  else if (potentiometer < minHumidity) {

    digitalWrite(waterPumpPin, HIGH);

  }
}
