#ifndef HARDWARECONNECTOR_H
#define HARDWARECONNECTOR_H

#include "stdio.h"
#include "Collection/project.h"
#include "configuration.h"

#define RESET_PIN 3
#define LASER_PIN 0
#define TEST_PIN 6
#define LDAC_PIN 2
#define TEST_FAILURE 1
#define LDAC_BUFFER true
#define LDAC_FLUSH false

struct HardwareStatictics
{
public:
    HardwareStatictics(int iosPerSec, int loopsPerSec, int waitsPerSec);
    int iosPerSecond;
    int loopsPerSecond;
    int waitsPerSecond;
};

class HardwareConnector
{
public:
    HardwareConnector();
    ~HardwareConnector();
    const char* draw(Project &sc,  Configuration *config, bool enableWaitCircuid, bool enableMoving);
    void centerLaser(bool isLaserEnabled);
    bool run = false;
    HardwareStatictics getOperationPerSecons();

private:
    int SpiOpenPort (int spi_device);
    int SpiClosePort (int spi_device);
    int SpiWriteAndRead (int SpiDevice, unsigned char *TxData, unsigned char *RxData, int Length, int LeaveCsLow);
    void ResetAndConfigure(bool enableLaser);
    void sent(unsigned int x, unsigned int y);
    bool handleLaserSwitch(bool enableWaitCircuid, const PointWithMetadata* p);
    bool waitUntillReachPosition();

    int spi_cs0_fd;				//file descriptor for the SPI device
    int spi_cs1_fd;				//file descriptor for the SPI device
    unsigned char spi_mode;
    unsigned char spi_bitsPerWord;
    unsigned int spi_speed;
    const char* waitExceededErrorMessage = "Number of wait iteration exceeded";

    unsigned int waits;
    unsigned long long int ioOperation;
    unsigned long long int loops;
    volatile long long int startTime;
};

#endif // HARDWARECONNECTOR_H
