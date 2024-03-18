#ifndef ACCEL_SETTINGS_H
#define ACCEL_SETTINGS_H

/* 
 * File:   AccelSettings.h
 * Author: Evan Draeger
 * 
 * Macro file to store relevent parameters that may or may need to be modified in
 * 1 place easily.
 * Created on March 7, 2024
 * Updated on March 11, 2024
 */


/* 
 * Define macros for accelerometer settings
 * 
 */ 

// Settable Macros
#define GYRO_INIT_DELAY 1000 // How long to delay gyro before execution of later code
#define ALPHA 0.1007 // Exponential Moving Average alpha value (0 < ALPHA < 1), chosen for 3.2[Hz]

// Not so Settable Macros
// #define ACCEL_SCALE_X 0.0008510850379491662
// #define ACCEL_SCALE_Y 0.0008406597754340823
// #define ACCEL_SCALE_Z 0.0009310350993489291
// #define ACCE_X_BIAS 0.0187 // prev -17
// #define ACCE_Y_BIAS 0.0186 // prev -9
// #define ACCE_Z_BIAS 0.1029 // prev 2
#define ACCEL_SCALE_X 0.0009475382367784052
#define ACCEL_SCALE_Y 0.0009412863445762291
#define ACCEL_SCALE_Z 0.0009661136321250275
#define ACCE_X_BIAS 0.0213153663764763 // prev -17
#define ACCE_Y_BIAS 0.0153933410616407 // prev -9
#define ACCE_Z_BIAS 0.0412569336487562 // prev 2



// Do NOT set Macros
#define RAD_2_DEG_SCALE 180.0/3.14 // scale factor from radians to degrees
#define DEG_2_RAD_SCALE 3.14/180.0 // scale factor from degrees to radians


#endif // ACCEL_SETTINGS_H
