#include <Arduino.h>
#include "Wire.h"
#include "Adafruit_MPU6050.h"
#include "Adafruit_Sensor.h"

Adafruit_MPU6050 mpu;

float bax = 0,bay = 0,baz = 0,bgx = 0,bgy = 0,bgz = 0;
sensors_event_t a;
sensors_event_t g;
sensors_event_t t;

uint16_t i;

void setup(){
    Serial.begin(115200);
    Wire.begin(21,22);
    if (mpu.begin(0x68,&Wire)){
        Serial.println("MPU 6050 is connected");
        Serial.println("Calibration under progress");

        for (i=0;i<1000;i++){
            mpu.getEvent(&a,&g,&t);
            bax += a.acceleration.x;
            bay += a.acceleration.y;
            baz += a.acceleration.z;
            bgx += g.gyro.x;
            bgy += g.gyro.y;
            bgz += g.gyro.z;
            delay(5);
        }

        //bias calculation - Averaging the 1000 quantities
        bax /= 1000;
        bay /= 1000;
        baz /= 1000;
        bgx /= 1000;
        bgy /= 1000;
        bgz /= 1000;
        Serial.println("Calibration is done");
    }

    else {
        Serial.println("Not connected");
        while(1);
    }

}

void loop(){
    mpu.getEvent(&a,&g,&t);
    Serial.print("Acc : ");
    Serial.print(a.acceleration.x - bax);
    Serial.print(" ");
    Serial.print(a.acceleration.y - bay);
    Serial.print(" ");
    Serial.println(a.acceleration.z - baz);
    Serial.print("Gyro - ");
    Serial.print(g.gyro.x - bgx);
    Serial.print(" ");
    Serial.print(g.gyro.y - bgy);
    Serial.print(" ");
    Serial.println(g.gyro.z - bgz);
    delay (1000);
}
