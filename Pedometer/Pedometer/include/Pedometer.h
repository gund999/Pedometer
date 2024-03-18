#ifndef PEDOMETER_H
#define PEDOMETER_H

#include <stdio.h>
#include <stdint.h> // for uint8_t? Do i need for portability lol
#include <stdlib.h>
#include <Board.h>
#include "BNO055.h"
#include "timers.h"
#include "Oled.h"


// Macros for Main Loop use
#define WALK_SAMPLE_SIZE 70


// Walking Speed Types
typedef enum 
{
    // Add running? false stepping?
    FALSE_WALK,
    SLOW_WALK,
    NORMAL_WALK,
    FAST_WALK
}WALKTYPE;

/**
 * @Function GetAccel(void)
 * @param acceleRray: input parameter array of size 3 [x,y,z]
 * @brief Runs all init functions needed and returns any errors
 * @return SUCCESS or ERROR
 * @note Comment in print statements to see which error
 * @author Evan Draeger */
uint8_t PedoInit(void);


/**
 * @Function WhatWalk(double *walkArray)
 * @param walkArray: input magnitude of acc vector array of size 70
 * @brief Determines what kind walking speed based on amplitude of waveform
 * @return WALKTYPE, FAST_WALK, SLOW_WALK, etc
 * @note Seems to work, maybe could use refining on thresholds or use dif method altogether
 * @author Evan Draeger */
WALKTYPE WhatWalk(double *walkArray);


/**
 * @Function DervMag(double *walkArray, double *dervArray)
 * @param walkArray: input magnitude of acc vector array of size 70
 * @param dervArray: output array to be used later to count steps
 * @brief Modifies dervArray to be derivative to find zero crossings.
 * @note NEED2TEST, has 1 less item in array than sample size 
 * @author Evan Draeger */
void DervMag(double *walkArray, double *dervArray);


/**
 * @Function DetectZeroCrossing(double *dervArray)
 * @param dervArray: derivative of magnitude of acceleration vector array 
 * @brief Counts zero crossings of dataset w/ hysteresis bounds
 * @return Returns # of steps counted in dataset
 * @note NEED2TEST, has 1 less item in array than sample size 
 * @author Evan Draeger */
uint32_t DetectZeroCrossing(double *dervArray, WALKTYPE walkState);


/**
 * @Function FindPeaks(double mag, WALKTYPE walk)
 * @param mag: magnitude point
 * @param walk: walk speed type, from WhatWalk()
 * @brief Finds peaks of an array
 * @return position in og array of peak
 * @note Comment in print statements to see which error
 * @author Evan Draeger */
uint8_t FindPeaks(double mag, WALKTYPE walk);

/**
 * @Function DispCount(uint16_t stepCount)
 * @param stepCount: Current Counted # of Steps
 * @brief Displays step count to screen
 * @return SUCCESS or ERROR
 * @author Evan Draeger */
uint8_t DispCount(uint16_t stepCount, WALKTYPE walkSpeed);


#endif /* PEDOMETER_H */
