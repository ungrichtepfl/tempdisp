#include <LiquidCrystal.h>
#include <avr/dtostrf.h>

#define PERIOD_MS (500)
#define TEMPERATURE_PIN (A1)
#define TEMP_SCALE_FACTOR (10.0f) // 10mV per degree C
#define CALIB_TEMP_VOLTAGE_MV_OFFSET (870.0f) // at value below
#define CALIB_TEMP_C_OFFSET (23.3f) // at value above

// Setup the LiquidCrystal library with the pin numbers we have
// physically connected the module to.
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

void setup() {
  // Setup the number of columns and rows that are available on the LCD.
  lcd.begin(16, 2);
}

void loop() {
    const int start_time = millis();
    const int sensor_value = analogRead(TEMPERATURE_PIN);
    const int voltage_mv = sensor_value * 3300 / 1023;
    char voltage_disp_str[16];
    snprintf(voltage_disp_str, sizeof(voltage_disp_str), "Voltage: %dmV", voltage_mv);
    
    const float temperature_c = (voltage_mv - CALIB_TEMP_VOLTAGE_MV_OFFSET) / TEMP_SCALE_FACTOR + CALIB_TEMP_C_OFFSET;

    char temp_c_str[16];
    dtostrf(temperature_c, 4, 1, temp_c_str);

    char temp_disp_str[16];
    snprintf(temp_disp_str, sizeof(temp_disp_str), "Temp: %s degC", temp_c_str);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(temp_disp_str);
    lcd.setCursor(0, 1);
    lcd.print(voltage_disp_str);
    

    const int end_time = millis();
    const int elapsed_time = end_time - start_time;
    if (elapsed_time < PERIOD_MS) {
        delay(PERIOD_MS - elapsed_time);
    }

}
