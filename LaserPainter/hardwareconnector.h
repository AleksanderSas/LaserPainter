#ifndef HARDWARECONNECTOR_H
#define HARDWARECONNECTOR_H

#include "stdio.h"
#include "Collection/project.h".h"

#define RESET_PIN 3
#define LASER_PIN 0
#define TEST_PIN 6
#define LDAC_PIN 2
#define TEST_FAILURE 1

class HardwareConnector
{
public:
    HardwareConnector();
    ~HardwareConnector();
    const char* draw(Project &sc, unsigned int resolution, unsigned int repeats, int scale, bool enableWaitCircuid);
    bool run = false;

private:
    int SpiOpenPort (int spi_device);
    int SpiClosePort (int spi_device);
    int SpiWriteAndRead (int SpiDevice, unsigned char *TxData, unsigned char *RxData, int Length, int LeaveCsLow);

    void sent(unsigned int x, unsigned int y);

    int spi_cs0_fd;				//file descriptor for the SPI device
    int spi_cs1_fd;				//file descriptor for the SPI device
    unsigned char spi_mode;
    unsigned char spi_bitsPerWord;
    unsigned int spi_speed;
    const char* waitExceededErrorMessage = "Number of wait iteration exceeded";

};

#endif // HARDWARECONNECTOR_H
