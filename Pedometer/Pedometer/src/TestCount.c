#include <Board.h>
#include <stdio.h>
#include <stdlib.h>
#include <Accel.h>
#include <timers.h>
#include <Pedometer.h>

/*
 *--------- TO-DO:----------------
 * - finish peaks function, add counting
 * - find thresholds for what walk, add better parameters for int8_t
 * -
 *
 *
 *
 *
 */

int main(void)
{
    PedoInit();
    uint32_t lastTime = TIMERS_GetMilliSeconds();
    uint32_t lastPrintTime = TIMERS_GetMilliSeconds();
    // uint8_t stepCountFlag = TRUE;
    uint32_t sampleNum = 0;                               // Vestigial
    uint16_t stepCount = 0;                               // Self-Explanatory
    uint8_t measCount = 0;                                // Count of how many values have been measured since beginning,
    uint8_t measureIndex = 0;                             // Datapoint #
    static double walkArray[WALK_SAMPLE_SIZE] = {1.0};    // moving window of measured magnitudes of acceleration vector, 70 vals
    static double dervMagArray[WALK_SAMPLE_SIZE] = {0.0}; // derivative of mag window
    static WALKTYPE currWalkSpeed = NORMAL_WALK;
    // float GyroX;
    // float GyroY;
    // float GyroZ;

    while (TRUE)
    {
        if (TIMERS_GetMilliSeconds() - lastTime > 20)
        {
            lastTime = TIMERS_GetMilliSeconds();

            // Find Magnitude/Get Datapoints
            double raw[3] = {0, 0, 0};
            GetAccel(raw);
            // double mag = GetMagnitude(raw);

            // Update Moving Window
            for (int i = 0; i < WALK_SAMPLE_SIZE - 1; ++i)
            {
                walkArray[i] = walkArray[i + 1];
            }
            // Assign the new reading to the most recent position
            walkArray[WALK_SAMPLE_SIZE - 1] = GetMagnitude(raw);
            // Update Measurement Count
            measCount++;
            // When we have measured a full new arrays worth of mags,
            if (measCount >= WALK_SAMPLE_SIZE)
            {
                // Count steps
                DervMag(walkArray, dervMagArray);
                for (int i = 0; i < WALK_SAMPLE_SIZE - 2; ++i)
                {
                    measureIndex++;
                    printf("%f\n", dervMagArray[i]);
                }
                stepCount += DetectZeroCrossing(dervMagArray, currWalkSpeed);
                measCount = 0; // reset counter
            }
            // GyroX = (float)BNO055_ReadGyroX()/131.0;
            // GyroY = (float)BNO055_ReadGyroY()/131.0;
            // GyroZ = (float)BNO055_ReadGyroZ()/131.0;

            // Print x,y,z, magnitude[x,y,z] for MATLAB to plot
            // printf("%f, %f, %f, %f\r\n", raw[0], raw[1], raw[2], walkArray[WALK_SAMPLE_SIZE - 1]);
            

            currWalkSpeed = WhatWalk(walkArray);

            // uint8_t peakPosition = FindPeaks(walkArray[WALK_SAMPLE_SIZE - 1], currWalkSpeed);
            // if (peakPosition)
            // {
            //     stepCount++;
            //     DispCount(stepCount, currWalkSpeed);
            // }

            // Save, used to find Peaks function, then add counting, but new func test
            // if ((walkArray[WALK_SAMPLE_SIZE - 1] > 1.07) && stepCountFlag)
            // {
            //     stepCount++;
            //     stepCountFlag = FALSE;
            //     DispCount(stepCount, NORMAL_WALK);
            // } else if ((walkArray[WALK_SAMPLE_SIZE - 1] < 1.00) && !stepCountFlag)
            // {
            //     stepCountFlag = TRUE;
            // }
            sampleNum++;
        }
        // Display at a different rate, otherwise its laggy and we miss some steps and dont print recorded data properly. 
        if (TIMERS_GetMilliSeconds() - lastPrintTime > 300)
        {
            lastPrintTime = TIMERS_GetMilliSeconds();
            DispCount(stepCount, currWalkSpeed);
            // printf("%f, %f, %f\r\n", GyroX, GyroY, GyroZ);
        }
    }
}
/*
 *
 *
 *
 *
 *
 *
 *
 */