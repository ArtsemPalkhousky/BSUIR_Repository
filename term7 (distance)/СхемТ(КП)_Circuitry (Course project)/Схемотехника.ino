/*
    Полховский Артем Федорович, группа 990541
  Микропроцессорное устройство контроля параметров кабины комбайна "Гомсельмаш"
*/
#include <LiquidCrystal_I2C.h> 
#include <DallasTemperature.h>
#include <OneWire.h>
#include <Wire.h> 
#include <BH1750.h>
#include <MQ135.h>
#include <GyverBME280.h>

// Пины датчиков, пищалки и кнопки
#define ONE_WIRE_BUS 5 
#define analogPin A0 
const int flame_PIN = 2;
const int flameAlarm_PIN = 9;
const int Button1_PIN = 10;
const int led1 = 11;
const int led2 = 12;
const int led3 = 13;

// Необходимые глобальные объекты
LiquidCrystal_I2C LCD(0x27,16,2); 
MQ135 gasSensor = MQ135(analogPin); 
GyverBME280 bme;
BH1750 lightMeter;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); 

int knopka = 0;  // переменная отвечающая за состояние кнопки
int state = 0;   // переменная отвечающая за запуск ledOn и LedOff 

// Переменные хранящие измеренные значения
float celcius = 0;
float bmeTemperature = 0;
float bmeHumidity = 0;
float bmePressure = 0;
float lux = 0;
float ppm = 0;
float rzero = 0;


void setup() {
  Wire.begin();
  sensors.begin();
  lightMeter.begin();
  pinMode (flame_PIN, INPUT);
  pinMode (flameAlarm_PIN, OUTPUT);   
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (led3, OUTPUT);

  LCD.init(); 
  LCD.backlight();
  LCD.setCursor(1, 0); 
  LCD.print("Hello Gom");   
  LCD.setCursor(8, 1);    
  LCD.print("Selmash");  
  ledOn();
  ledOff();
  delay(1000);
  LCD.clear();
}


void loop() {
  // if(digitalRead(Button1_PIN) && !state && !knopka) // если кнопка нажата, state = 0, knopka = 0;
  // {
  //   ledOn();    // Запускаем вкючение
  //   delay(10);  // Небольшая защита от дребезга кнопки
  // }
  // if(digitalRead(Button1_PIN) && state && !knopka) //если кнопка нажата, state = 1, knopka = 0;
  // {
  //   ledOff();
  //   delay(10);
  // }
  // if(!digitalRead(Button1_PIN)) 
  // {
  //   knopka = 0;
  // }

  loopLedOn();
  loopLedOff();
  readAllSensors();
 
  // Light 
  LCD.print("Light?: ");
  LCD.setCursor(0, 1);
  LCD.print(lux);
  LCD.print(" lux");
  delay(1000);
  LCD.clear();
  
  readAndProcessFlameSensor();

  // Temperature 1
  LCD.print("Temperature DHT: ");
  LCD.setCursor(0, 1);
  LCD.print(celcius);
  LCD.print(" *C");
  delay(2000);
  LCD.clear();

  readAndProcessFlameSensor();

  // Temperature 2
  LCD.print("Temperature?: ");
  LCD.setCursor(0, 1);
  LCD.print(bmeTemperature);
  LCD.print(" *C");
  delay(1000);
  LCD.clear();

  readAndProcessFlameSensor();

  // Humidity2
  LCD.print("Humidity?: ");
  LCD.setCursor(0, 1);
  LCD.print(bmeHumidity);
  LCD.print(" g/m^3");
  delay(1000);
  LCD.clear();

  readAndProcessFlameSensor();

  // Pressure2
  LCD.print("Pressure?: ");
  LCD.setCursor(0, 1);
  LCD.print(bmePressure);
  LCD.print(" KGc/m^2");
  delay(1000);
  LCD.clear();

  readAndProcessFlameSensor();

  // CO2
  LCD.print("maintence CO2:");
  LCD.setCursor(0, 1);
  LCD.print(ppm);
  LCD.print(" ml/M^3");
  delay(2000);
  LCD.clear();

  readAndProcessFlameSensor();
}

void readAllSensors(){
  lux = lightMeter.readLightLevel(); // lightMeter GY-302 - BH1750
  ppm = gasSensor.getPPM(); // чтение данных концентрации CO2  // CO2 - MQ 135
  rzero = gasSensor.getRZero(); // чтение калибровочных данных // CO2 - MQ 135
  sensors.requestTemperatures();   // Temperature 1 - DS18B20
  celcius = sensors.getTempCByIndex(0);  // Temperature 1 - DS18B20
  bmeTemperature = bme.readTemperature();   // Temperature Humidity Pressure - BME280
  bmeHumidity = bme.readHumidity();
  bmePressure = bme.readPressure();
}

void readAndProcessFlameSensor(){
   // flame
  while(!digitalRead(flame_PIN)) {
    digitalWrite(flameAlarm_PIN, HIGH);
    LCD.clear();
    LCD.print("ALARM! FIRE!!");
    ledOn();
    ledOff();
    delay(1000);
  }
  LCD.clear();
  digitalWrite(flameAlarm_PIN, LOW);
}

void loopLedOn() {
  digitalWrite(led1, HIGH);
  delay(150);
}

void loopLedOff() {
  digitalWrite(led1, LOW);
  delay(150);
}

void ledOn() 
{
  digitalWrite(led1, HIGH);
  delay(150);
  digitalWrite(led2, HIGH);
  delay(150);
  digitalWrite(led3, HIGH);
  delay(200);
}

void ledOff() 
{
  digitalWrite(led1, LOW);
  delay(150);
  digitalWrite(led2, LOW);
  delay(150);
  digitalWrite(led3, LOW);
  delay(150);
}