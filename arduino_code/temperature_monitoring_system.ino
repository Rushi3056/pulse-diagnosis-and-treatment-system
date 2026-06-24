/*
===========================================================
PROJECT : Pulse Diagnosis and Treatment System
MODULE  : Temperature Monitoring & Protection System
PLATFORM: Arduino UNO
DISPLAY : 20x4 LCD
SENSORS : LM35 Temperature Sensors

DESCRIPTION:
This module continuously monitors temperatures from:

T1 - Rectifier Heatsink
T2 - IGBT Heatsink
T3 - Transformer Primary
T4 - Coil

Temperature values are displayed on a 20x4 LCD and
sent to the Serial Monitor.

PROTECTION LOGIC:
If any temperature exceeds 60°C:
- Relay is activated
- Warning LED is turned ON

TECHNOLOGIES:
- Arduino UNO
- LM35 Temperature Sensors
- 20x4 LCD
- Relay Module
- Embedded C

===========================================================
*/

#include <LiquidCrystal.h>

// Temperature Sensor Pins
const int rect_heatsink = A1;
const int igbt_heatsink = A2;
const int primary = A3;
const int coil = A4;

// Output Pins
const int Relay = 4;
const int LED = 5;

// LCD Pins (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(2, 3, 8, 9, 10, 11);

void setup()
{
    Serial.begin(9600);

    pinMode(Relay, OUTPUT);
    pinMode(LED, OUTPUT);

    lcd.begin(20, 4);
    lcd.clear();

    Serial.println("Temperature Monitoring System Started");
}

void loop()
{
    // Read ADC Values
    int adc_val1 = analogRead(rect_heatsink);
    int adc_val2 = analogRead(igbt_heatsink);
    int adc_val3 = analogRead(primary);
    int adc_val4 = analogRead(coil);

    // Convert ADC Values to Temperature
    float rect_temp = (((adc_val1 * 4.88) - 0.0027) / 10.0);
    float igbt_temp = (((adc_val2 * 4.88) - 0.0027) / 10.0);
    float primary_temp = (((adc_val3 * 4.88) - 0.0027) / 10.0);
    float coil_temp = (((adc_val4 * 4.88) - 0.0027) / 10.0);

    // Serial Monitor Output
    Serial.println("--------------------------------");
    Serial.print("Rectifier Heatsink : ");
    Serial.print(rect_temp);
    Serial.println(" C");

    Serial.print("IGBT Heatsink      : ");
    Serial.print(igbt_temp);
    Serial.println(" C");

    Serial.print("Primary Temp       : ");
    Serial.print(primary_temp);
    Serial.println(" C");

    Serial.print("Coil Temp          : ");
    Serial.print(coil_temp);
    Serial.println(" C");

    // LCD Display
    lcd.setCursor(0, 0);
    lcd.print("T1=");
    lcd.print(rect_temp);
    lcd.print(" C   ");

    lcd.setCursor(0, 1);
    lcd.print("T2=");
    lcd.print(igbt_temp);
    lcd.print(" C   ");

    lcd.setCursor(0, 2);
    lcd.print("T3=");
    lcd.print(primary_temp);
    lcd.print(" C   ");

    lcd.setCursor(0, 3);
    lcd.print("T4=");
    lcd.print(coil_temp);
    lcd.print(" C   ");

    // Protection Logic
    if (rect_temp > 60 ||
        igbt_temp > 60 ||
        primary_temp > 60 ||
        coil_temp > 60)
    {
        digitalWrite(Relay, HIGH);
        digitalWrite(LED, HIGH);

        Serial.println("WARNING: Over Temperature Detected!");
    }
    else
    {
        digitalWrite(Relay, LOW);
        digitalWrite(LED, LOW);
    }

    delay(1000);
}
