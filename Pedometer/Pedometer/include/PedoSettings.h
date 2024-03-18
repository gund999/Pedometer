#ifndef PEDO_SETTINGS_H
#define PEDO_SETTINGS_H

/* 
 * File:   PedoSettings.h
 * Author: Evan Draeger
 * 
 * Macro file to store relevent parameters that may or may need to be modified in
 * 1 place easily. Keeps Macros separate so there's no conflicts in multiple redefs
 * Created on March 7, 2024
 * Updated on March 11, 2024
 */


/* 
 * Define macros for pedometer settings
 * 
 */ 

// Settable Macros
// #define GYRO_INIT_DELAY 1000 // How long to delay gyro before execution of later code
// #define MOVING_AVG_SIZE 5 // size of accelerometer moving average for each axis
// #define READING_PERIOD 20 // in ms 
// #define READING_PERIOD_SEC 0.021 // in seconds
// #define ALPHA 0.007 // Exponential Moving Average alpha value (0 < ALPHA < 1), chosen for 3.2[Hz]
#define INIT_DELAY 60

// Not so Settable Macros

// TBD Thresholds for min peak distance
#define SLOW_PEAK_DISTANCE 0
#define NORMAL_PEAK_DISTANCE 0
#define FAST_PEAK_DISTANCE 0

// Walking Speed Thresholds from Magnitude
#define TH_L_FALSE 0.93
#define TH_H_FALSE 0.96
#define TH_L_SLOW 0.97
#define TH_H_SLOW 0.985
#define TH_L_NORMAL 0.991
#define TH_H_NORMAL 1.056
#define TH_L_FAST 1.059
#define TH_H_FAST 1.063
// TBD Thresholds for walking speeds?
// #define WALK_SAMPLE_SIZE 70 // in Pedometer.h

// Zero Crossing Slope(of Mag) Thresholds for Derivative of Mag
#define ZCROSS_H_THRESH 0.022
#define ZCROSS_L_THRESH -0.0028

#define ZCROSS_H_THRESH_SLOW 0.017
#define ZCROSS_L_THRESH_SLOW -0.0028

#define ZCROSS_H_THRESH_FAST 0.0721
#define ZCROSS_L_THRESH_FAST -0.016


#define MIN_CROSS_TIME 5 // Not actually in time, its in sample #, but you know what I mean 

// Do NOT set Macros
#define RAD_2_DEG_SCALE 180.0/3.14 // scale factor from radians to degrees
#define DEG_2_RAD_SCALE 3.14/180.0 // scale factor from degrees to radians


#endif // ACCEL_SETTINGS_H
