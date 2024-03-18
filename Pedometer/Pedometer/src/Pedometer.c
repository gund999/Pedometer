#include "Pedometer.h"
#include "PedoSettings.h"

uint8_t PedoInit(void)
{
    uint8_t errorFlag = 0;
    BOARD_Init();
    OledInit();
    OledDrawString("\nStep Counter: \n\n|-------------------|");
    OledUpdate();
    if (TIMER_Init() == ERROR)
    {
        // printf("Timer Error \n");
        errorFlag++;
    }
    if (BNO055_Init() == ERROR)
    {
        // printf("IMU Error \n");
        errorFlag++;
    }
    if (errorFlag == 0)
    {
        OledDrawString("\nStep Counter: \nLoading:\n|*------------------|");
        HAL_Delay(INIT_DELAY);
        OledUpdate();
        OledDrawString("\nStep Counter: \nLoading:\n|***----------------|");
        HAL_Delay(INIT_DELAY);
        OledUpdate();
        OledDrawString("\nStep Counter: \nLoading:\n|*****--------------|");
        HAL_Delay(INIT_DELAY);
        OledUpdate();
        OledDrawString("\nStep Counter: \nLoading:\n|*******------------|");
        HAL_Delay(INIT_DELAY);
        OledUpdate();
        OledDrawString("\nStep Counter: \nLoading:\n|*********----------|");
        HAL_Delay(INIT_DELAY);
        OledUpdate();
        OledDrawString("\nStep Counter: \nLoading:\n|***********--------|");
        HAL_Delay(INIT_DELAY);
        OledUpdate();
        OledDrawString("\nStep Counter: \nLoading:\n|*************------|");
        HAL_Delay(INIT_DELAY);
        OledUpdate();
        OledDrawString("\nStep Counter: \nLoading:\n|***************----|");
        HAL_Delay(INIT_DELAY);
        OledUpdate();
        OledDrawString("\nStep Counter: \nLoading:\n|****************--|");
        HAL_Delay(INIT_DELAY);
        OledUpdate();
        OledDrawString("\nStep Counter: \nLoading:\n********************|");
        HAL_Delay(INIT_DELAY);
        OledUpdate();
        OledDrawString("\nStep Counter: Ready!\nComplete:\n********************|");
        OledUpdate();
        return SUCCESS;
    }
    OledDrawString("\nStep Counter: Fuck Up in Init!\n");
    OledUpdate();
    return ERROR;
}

WALKTYPE WhatWalk(double *walkArray)
{
    static WALKTYPE NUNA = FAST_WALK;
    static double LOW_THRESHOLD = TH_L_NORMAL;
    static double HIGH_THRESHOLD = TH_H_NORMAL;

    // Implement something here that takes moving window and can compare against old vals. 
    // double tot = TH_H_NORMAL-0.01; // use this line to hardset normal walk
    double tot = 0;
    uint8_t count = 0;
    for (int i = 30; i < WALK_SAMPLE_SIZE - 1; ++i) {
        if (walkArray[i] > 0.93)
        {
            tot += walkArray[i];
            count++;
        }
    }
    tot /= count;
    // printf("tot: %f\n", tot);
    switch(NUNA)
    {
        case FAST_WALK:
            if (tot < LOW_THRESHOLD) 
            {
                NUNA = FALSE_WALK;
                LOW_THRESHOLD = TH_L_FALSE;
                HIGH_THRESHOLD = TH_H_FALSE;
            }
            break;
        case NORMAL_WALK:
            if (tot < LOW_THRESHOLD) 
            {
                NUNA = SLOW_WALK;
                LOW_THRESHOLD = TH_L_SLOW;
                HIGH_THRESHOLD = TH_H_SLOW;
            } else if (tot > HIGH_THRESHOLD) 
            {
                NUNA = FAST_WALK;
                LOW_THRESHOLD = TH_L_FAST;
                HIGH_THRESHOLD = TH_H_FAST;
            }
            break;
        case SLOW_WALK:
            if (tot < LOW_THRESHOLD) 
            {
                NUNA = FALSE_WALK;
                LOW_THRESHOLD = TH_L_FALSE;
                HIGH_THRESHOLD = TH_H_FALSE;
            } else if (tot > HIGH_THRESHOLD) 
            {
                NUNA = NORMAL_WALK;
                LOW_THRESHOLD = TH_L_NORMAL;
                HIGH_THRESHOLD = TH_H_NORMAL;
            }
            break;
        case FALSE_WALK:
            if (tot > HIGH_THRESHOLD) 
            {
                NUNA = SLOW_WALK;
                LOW_THRESHOLD = TH_L_SLOW;
                HIGH_THRESHOLD = TH_H_SLOW;
            } 
            break;
        
            
    }
    return NUNA;
}

void DervMag(double *walkArray, double *dervArray)
{
    // walkArray[70];
    // return (walkArray[WALK_SAMPLE_SIZE-1] - walkArray[WALK_SAMPLE_SIZE-2]);
    for (int i = 0; i < WALK_SAMPLE_SIZE-2;i++)
    {
        dervArray[i] = walkArray[i+1] - walkArray[i];
    }  
}


uint32_t DetectZeroCrossing(double *dervArray, WALKTYPE walkState)
{
    uint8_t crossFlag = TRUE;
    uint32_t localCount = 0;
    uint8_t posIndex = 0;
    double lowThresh = -2;
    double highThresh = 2;
    switch(walkState)
    {
        case FALSE_WALK:
            highThresh = 3; // values it would never reach bc no steps in false walk
            lowThresh = -3;
            break;
        case SLOW_WALK:
            highThresh = ZCROSS_H_THRESH_SLOW;
            lowThresh = ZCROSS_L_THRESH_SLOW;
            break;
        case NORMAL_WALK:
            highThresh = ZCROSS_H_THRESH;
            lowThresh = ZCROSS_L_THRESH;
            break;
        case FAST_WALK:
            highThresh = ZCROSS_H_THRESH;
            lowThresh = ZCROSS_L_THRESH;
            break;
        
    }
    for (int i = 0; i < WALK_SAMPLE_SIZE-2;i++)
    {
        // We are looking for + slope above some threshold, only look at 1 kind at a time
        if ((dervArray[i] > highThresh) && crossFlag)
        {
            posIndex = i;
            crossFlag = FALSE;
        // We have seen + slope, now looking for -
        } else if ((dervArray[i] < lowThresh) && !crossFlag)
        {
            if ((i - posIndex) > MIN_CROSS_TIME)
            {
                crossFlag = TRUE;
                localCount++;
            }
        }
    }
    return localCount;
}


uint8_t FindPeaks(double mag, WALKTYPE walk)
{
    static uint8_t peakFlag = TRUE;
    double UpperThresh, LowerThresh;
    static double peakMag = 0;
    static uint32_t peakNum = 0;
    uint32_t returnPeak = 0;


    // Pick Hysteresis bounds based on walk type
    switch (walk)
    {
        case FALSE_WALK:
            UpperThresh = TH_H_FALSE;
            LowerThresh = TH_L_FALSE;
            break;
        case SLOW_WALK:
            UpperThresh = TH_H_SLOW;
            LowerThresh = TH_L_SLOW;
            break;
        case NORMAL_WALK:
            UpperThresh = TH_H_NORMAL;
            LowerThresh = TH_L_NORMAL;
            break;
        case FAST_WALK:
            UpperThresh = TH_H_FAST;
            LowerThresh = TH_L_FAST;
            break;
        default:
            UpperThresh = TH_H_NORMAL;
            LowerThresh = TH_L_NORMAL;
            break;
        
    } 
    // Find actual max value of a peak
    if (mag > peakMag) {
        peakMag = mag;
        peakNum = WALK_SAMPLE_SIZE - 1;
    } else {
        peakNum--;
    }
    // If we find a val above this threshold, that means we are approaching a peak
    if ((mag > UpperThresh) && (peakFlag)) 
    {
        // set flag low, says we are waiting to see when value drops high enough to avoid noise          
        peakFlag = FALSE;
    }
    // Current Cursor has confirmed an actual peak after cursor passes threshold
    else if ((!peakFlag) && (mag < LowerThresh))
    {
        // Set flag high, saying we are looking for a new peak
        peakFlag = TRUE;
        // Set Peak Return
        returnPeak = peakNum;
        // Reset Max Peak [x,y]
        peakMag = 0; // y
        peakNum = 0; // x
        // printf("hitting low  thresh, Mag: %f\n", mag);
        return returnPeak;
    }
    return FALSE; // return 0 if no peak detected
}


uint8_t DispCount(uint16_t stepCount, WALKTYPE walkSpeed)
{
    char stepCountLine[256]; // Num of Chars per line max 128/6 = 21.33 . . .
    // Reset Screen before Updating
    OledClear(OLED_COLOR_BLACK);
    // Format and fill string with info "*********************" <- max line size
    if (walkSpeed == SLOW_WALK)
    {
        sprintf(stepCountLine, "---------------------\nSteps #: %u\nSpeed: Slow\n---------------------", stepCount);
    } else if (walkSpeed == NORMAL_WALK)
    {
        sprintf(stepCountLine, "---------------------\nSteps #: %u\nSpeed: Normal\n---------------------", stepCount);
    } else if (walkSpeed == FAST_WALK)
    {
        sprintf(stepCountLine, "---------------------\nSteps #: %u\nSpeed: Fast\n---------------------", stepCount);
    } else {
        sprintf(stepCountLine, "---------------------\nSteps #: %u\nSpeed: Slug\n---------------------", stepCount);
    }
    
    // Put string into what is to be displayed
    OledDrawString(stepCountLine);
    // Update Screen
    OledUpdate();
    return SUCCESS;
}

