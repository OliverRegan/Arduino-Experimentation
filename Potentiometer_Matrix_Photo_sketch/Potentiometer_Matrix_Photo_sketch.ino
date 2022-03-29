#include <MPU6050.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


MPU6050 mpu;
LiquidCrystal_I2C lcd(0x27, 16, 2);


// ======================== Main setup ========================

void setup() {

  // Serial init
  Serial.begin(115200);

  // Start LCD  
  lcd.init();
  lcd.backlight();
  lcd.print("hello");
  
  lcd.println("MPU6050 Found!");

  mpu.begin();
  
  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(1000);
}


// ======================== Main Loop ========================

void loop() {

  process();
  
}


// ======================== Main function ========================
void process(){


  
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  lcd.setCursor(0, 0);
  lcd.println("Acceleration x:");
  lcd.setCursor(0, 1);
  lcd.println(a.acceleration.x);


  delay(500);
  
  lcd.clear();
  
  

}


// ======================== Other functions ========================

// Write scrolling text
void writeScrollText(String text){

  lcd.clear();

  //  Print input text
  lcd.print(text);

  delay(2000);

  int txtLength = text.length();

  
  
  
  for(int i = 0; i < (txtLength - 16); i++){
    
    lcd.scrollDisplayLeft();
    delay(500);
    
  }

  delay(2000);
  
  lcd.clear();
    
}
