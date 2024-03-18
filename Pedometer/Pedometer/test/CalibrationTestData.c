#include <Board.h>
#include <stdio.h>
#include <stdlib.h>
#include <Accel.h>
#include <timers.h>
#include <Pedometer.h>
// #define CALIB_TEST
#ifdef CALIB_TEST
int main(void) {
    PedoInit();
    uint32_t lastTime = TIMERS_GetMilliSeconds();
    uint32_t sampleNum = 0;
    while(TRUE)
    {
        if (TIMERS_GetMilliSeconds() - lastTime > 20)
        {
            lastTime = TIMERS_GetMilliSeconds();
            double raw[3] = {0,0,0};
            GetAccel(raw);        
            printf("%f, %f, %f, %f\r\n", raw[0], raw[1], raw[2], GetMagnitude(raw));
            // printf("%f\r\n", GetMagnitude(raw));
            sampleNum++;
        }
        
    }
    
}
#endif
/*
* 
*
*
*
*
*
*
*/