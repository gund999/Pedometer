#ifndef ACCEL_H
#define ACCEL_H

/* 
 * File:   Accel.h
 * Author: Evan Draeger
 * 
 * Software module to get IMU data gyro data over I2C.
 * Provides access to each raw sensor axis along with raw temperature
 *
 * Created on March 7, 2024
 * Updated on March 11, 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <Board.h>
#include "BNO055.h"
#include "timers.h"
#include <MatrixMath.h>
#include "math.h"




/**
 * @Function GetRawAccel(double *acceleRray)
 * @param  acceleRray: Input parameter array of size 3 [x,y,z](modified)
 *                     In format: [g's,g's,g's]
 * @brief  Outputs accelerometer output into acceleRray(modified)
 * @note   Needs to be run inside a loop w/ timing. Timing is not
 *         built in to this function
 * @note   This is pure raw output, no bias, no scaling, no avg, no filtering, use for calibration
 * @return Void
 * @author Evan Draeger */
void GetRawAccel(double *acceleRray);

/**
 * @Function GetAccel(double *acceleRray)
 * @param  acceleRray: Input parameter array of size 3 [x,y,z](modified)
 *                     In format: [g's,g's,g's]
 * @brief  Outputs accelerometer output into acceleRray(modified)
 * @note   Needs to be run inside a loop w/ timing. Timing is not
 *         built in to this function
 * @return Void
 * @author Evan Draeger */
void GetAccel(double *acceleRray);


/**
 * @Function GetMagnitude(double *acceleRray)
 * @param  acceleRray: Input parameter array of size 3 [x,y,z](not modified)
 *                     In format: [g's,g's,g's]
 * @brief  Takes magnitude of acceleRray(not modified)
 * @return magnitude
 * @author Evan Draeger */
double GetMagnitude(double *acceleRray);



#endif /* ACCEL_H */