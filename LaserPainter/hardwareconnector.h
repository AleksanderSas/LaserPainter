#ifndef HARDWARECONNECTOR_H
#define HARDWARECONNECTOR_H

#include "stdio.h"
#include "bezier.h"

#define RAW_IO_WRITE 1

class HardwareConnector
{
public:
    HardwareConnector();
    ~HardwareConnector();
    void drawBezier(Bezier &b, unsigned int resolution, unsigned int repeats);
    bool run = false;

private:
    int SpiOpenPort (int spi_device);
    int SpiClosePort (int spi_device);
    int SpiWriteAndRead (int SpiDevice, unsigned char *TxData, unsigned char *RxData, int Length, int LeaveCsLow);

    void myopen();
    void MyClose();
    void spi_write(int SpiDevice, unsigned char *TxData, int len);
    void sent(unsigned int x, unsigned int y);

    FILE* fp1;
    FILE* fp2;

    int spi_cs0_fd;				//file descriptor for the SPI device
    int spi_cs1_fd;				//file descriptor for the SPI device
    unsigned char spi_mode;
    unsigned char spi_bitsPerWord;
    unsigned int spi_speed;

};

#endif // HARDWARECONNECTOR_H
