#ifndef HARDWARECONNECTOR_H
#define HARDWARECONNECTOR_H

#include "stdio.h"
#include "shapecollection.h"

#define RESET_PIN 4
#define LASER_PIN 5

class HardwareConnector
{
public:
    HardwareConnector();
    ~HardwareConnector();
    void draw(ShapeCollection &sc, unsigned int resolution, unsigned int repeats);
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

};

#endif // HARDWARECONNECTOR_H
