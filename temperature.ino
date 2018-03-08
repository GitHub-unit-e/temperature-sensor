//code implemented from https://create.arduino.cc/projecthub/everth-villamil-ruiz/temperature-sensor-ds18b20-3decfc
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>

#define ONE_WIRE_BUS 2
#define servoPin 9

//initialization
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Servo servo;

//variables
int temp = 0;
int servoAngle = 0;

void setup(void)
{
  //begin serial
  Serial.begin(9600);

  //begin sensor bus and attach sensor
  sensors.begin();
  servo.attach(servoPin);

  //servo range test
  delay(500);
  servo.write(0);
  delay(500);
  servo.write(180);
  delay(500);

  //set servo to show 0C
  servo.write(40);
}

void loop(void)
{
  //request temperature from sensor
  sensors.requestTemperatures();

  //set variable temp to current temperature
  temp = sensors.getTempCByIndex(0);

  //calculate servo angle (40 degrees is 0C)
  servoAngle = 40 + (temp * 2);

  //if the temperature is off the display, show end of display
  if (servoAngle < 0) {

    servoAngle = 0;
  } else if (servoAngle > 180) {

    servoAngle = 180;
  }

  //write angle to servo
  servo.write(servoAngle);

  //delay 500 miliseconds
  delay(500);
}

