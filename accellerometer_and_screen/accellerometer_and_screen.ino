#include <LCD_I2C.h>
#include <Wire.h> // This library allows you to communicate with I2C devices.
#include <math.h>
#include <Servo.h>
#include <IRremote.h>

//Define joystick stuff
#define joyX A0
#define joyY A1

int xVal, yVal;
//IR stuff
const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

//Servo stuff
Servo servo;


// Ultrasonic stuff
#define echo 12
#define trig 13

long duration;

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data

char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {

  // servo
  servo.attach(9);

//  IR
  irrecv.enableIRIn();


//  LCD startup
  lcd.begin();
  lcd.backlight();
  lcd.print("Hello");


//  Sonic stuff
pinMode(echo, INPUT);
pinMode(trig, OUTPUT);

  
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}
void loop() {
//  Wire.beginTransmission(MPU_ADDR);
//  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
//  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
//  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
//  
//  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
//  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
//  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
//  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
//  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
//  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
//  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
//  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
//  
  // print out data
//  Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
//  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
//  Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));
//  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
//  Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);
//  Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
//  Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
//  Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
//  Serial.println();

//  char accXStr[] = "Acc x: ";
//  char* accelerationX = convert_int16_to_str((accelerometer_x*9.8)/16384); // /16384 makes the measurement into the form of g's
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print(accXStr);
//  lcd.setCursor(10, 0);
//  lcd.print(accelerometer_x/16384);
//
//  
//  lcd.setCursor(0,1);
//  char tempStr[] = "Temp: ";
//  char* temp = convert_int16_to_str(temperature/340.00+36.53);
//  lcd.print(tempStr);
//  lcd.setCursor(10, 1);
//  lcd.print(temperature/340.00+36.53);


//  Joystick stuff
//  xVal = map(analogRead(joyX), 0, 1023, 0, 180);
//  yVal = map(analogRead(joyY), 0, 1023, 180, 0);
//  
//  lcd.setCursor(0, 0);
//  lcd.print(xVal);
//  lcd.setCursor(0, 1);
//  lcd.print(yVal);

//  servo.write(xVal);


//  Ultrasonic
// Clears the trigPin condition
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Distance in CM:");
  lcd.setCursor(0,1);
  lcd.print(calcDistanceCM(duration));


  
  if (irrecv.decode(&results)){
         //int result = results.value;// Results of decoding are stored in result.value     
         Serial.println(" ");     
         Serial.print("Code: ");     
         Serial.println(results.value); //prints the value a a button press     
         Serial.println(" ");     
         irrecv.resume(); // Restart the ISR state machine and Receive the next value  

         if(results.value == 16720605){
          servo.write(0);
         } else if (results.value == 16761405){
          servo.write(180);
         } else if (results.value == 16712445){
          servo.write(90);
         }  

         servo.attach(9);
  };
 
}


long calcDistanceCM(long sonicVal){

  long cm = sonicVal * 0.034/2;

  return cm;
}
