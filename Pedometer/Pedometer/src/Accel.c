#include <Accel.h>
#include <AccelSettings.h>

void GetRawAccel(double *acceleRray) // Pointer to array [x,y,z]
{
    acceleRray[0] = BNO055_ReadAccelX();
    acceleRray[1] = BNO055_ReadAccelY();
    acceleRray[2] = BNO055_ReadAccelZ();
}

void GetAccel(double *acceleRray) // Pointer to array [x,y,z]
{
    // Store moving Avg vals/Keep btwn calls
    static double movingAverageX = 0;
    static double movingAverageY = 0;
    static double movingAverageZ = 0;

    // Get new readings
    double newX = BNO055_ReadAccelX();
    double newY = BNO055_ReadAccelY();
    double newZ = BNO055_ReadAccelZ();

    // Do we want to scale/bias before avg?
    // Calculate exponential moving average for X axis avg = alpha * newMeas + (1-alpha)*lastAvg
    movingAverageX = ALPHA * newX + (1 - ALPHA) * movingAverageX;
    acceleRray[0] = (movingAverageX * ACCEL_SCALE_X) + ACCE_X_BIAS;

    // Calculate exponential moving average for Y axis
    movingAverageY = ALPHA * newY + (1 - ALPHA) * movingAverageY;
    acceleRray[1] = (movingAverageY * ACCEL_SCALE_Y) + ACCE_Y_BIAS;

    // Calculate exponential moving average for Z axis
    movingAverageZ = ALPHA * newZ + (1 - ALPHA) * movingAverageZ;
    acceleRray[2] = (movingAverageZ * ACCEL_SCALE_Z) + ACCE_Z_BIAS;
}

double GetMagnitude(double *acceleRray)
{
    double tot = (acceleRray[0] * acceleRray[0]) + (acceleRray[1] * acceleRray[1]) + (acceleRray[2] * acceleRray[2]);
    return sqrt(tot);
}

