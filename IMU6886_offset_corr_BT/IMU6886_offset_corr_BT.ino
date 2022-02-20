#include <M5Core2.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

float accX = 0.0F;  // Define variables for storing inertial sensor data
float accY = 0.0F;  //定义存储惯性传感器相关数据的相关变量
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

float Sum_pitch = 0.0F; //オフセット計算用
float Sum_roll  = 0.0F; //オフセット計算用

float off_pitch = 0.0F; //オフセット
float off_roll  = 0.0F; //オフセット

float temp = 0.0F;
int i;

void setup(){
  M5.begin(); 
  SerialBT.begin("M5Core2");
  M5.IMU.Init();  
  M5.Lcd.fillScreen(BLACK); 
  M5.Lcd.setTextColor(GREEN , BLACK); 
  M5.Lcd.setTextSize(2); 
}

void loop() {
  M5.IMU.getGyroData(&gyroX,&gyroY,&gyroZ);
  M5.IMU.getAccelData(&accX,&accY,&accZ); 
  M5.IMU.getAhrsData(&pitch,&roll,&yaw); 
  M5.IMU.getTempData(&temp);

  M5.Lcd.setCursor(0, 20);  
  M5.Lcd.printf("gyroX,  gyroY, gyroZ"); 
  M5.Lcd.setCursor(0, 42);
  M5.Lcd.printf("%6.2f %6.2f%6.2f o/s", gyroX, gyroY, gyroZ);

  M5.Lcd.setCursor(0, 70);
  M5.Lcd.printf("accX,   accY,  accZ");
  M5.Lcd.setCursor(0, 92);
  M5.Lcd.printf("%5.2f  %5.2f  %5.2f G", accX, accY, accZ);

  M5.Lcd.setCursor(0, 120);
  M5.Lcd.printf("pitch,  roll,  yaw");
  M5.Lcd.setCursor(0, 142);
  M5.Lcd.printf("%5.2f  %5.2f  %5.2f deg", pitch-off_pitch, roll-off_roll, yaw);

  //M5.Lcd.setCursor(0, 175);
  //M5.Lcd.printf("Temperature : %.2f C", temp);

  SerialBT.print("x");
  SerialBT.print(pitch-off_pitch,4);
  SerialBT.print("y");
  SerialBT.print(roll-off_roll,4);
  SerialBT.print("z");
  SerialBT.println(yaw,4);
  
  delay(10);

  if (M5.BtnA.pressedFor(1000, 200)) {
    for(i=0;i<1000;i++){
      M5.Lcd.setCursor(0, 175);
      M5.Lcd.printf("Calibration!");
      M5.IMU.getAhrsData(&pitch,&roll,&yaw); 
      Sum_pitch = Sum_pitch + pitch;
      Sum_roll = Sum_roll + roll;
    }
    M5.Lcd.setCursor(0, 175);
    M5.Lcd.printf("");
    off_pitch = Sum_pitch * 0.001;
    off_roll = Sum_roll * 0.001;
    /*
    Serial.print("i:");
    Serial.print(i);
    Serial.print("Sum_pitch:");
    Serial.print(Sum_pitch);
    Serial.print(" Sum_roll:");
    Serial.print(Sum_roll);
    Serial.print(" off_pitch:");
    Serial.print(off_pitch);
    Serial.print(" off_roll:");
    Serial.println(off_roll);
    */
  }
  M5.update();
}
