#ifndef __SERIAL_H
#define __SERIAL_H

#include <termios.h>    /*PPSIX÷’∂Àøÿ÷∆∂®“Â*/
#include "public.h"
#include "queue.h"


//#define Serial_raw_test
//#define Serial_middle_test
//#define Serial_app_test

//#define CONFIG_SERIAL_DEBUG

#ifdef CONFIG_SERIAL_DEBUG
#define SERIAL_DEBUG(fmt,args...) printf(fmt ,##args)
#else				/*  */
#define SERIAL_DEBUG(fmt, args...)
#endif

#define SERIAL_PATH "/dev/ttySAC0"


static int speed_arr[] =  {B115200, B57600, B38400, B19200, B9600, B4800, B2400, B1200, B300};
static int name_arr[] = {115200, 57600, 38400, 19200, 9600, 4800, 2400, 1200, 300};

class Serial_app;

class Class_Public
{
public:
    void DebugMem(uchar *pMem, int len, const char *note);
};

class Serial_raw : public Class_Public
{
public:
    Serial_raw(char *path);
    ~Serial_raw();
    void SetSpeed(int speed);
    int SetParity(int databits, int stopbits, int parity);
    int ReadData(void *buf, int count);
    int WriteData(void *buf, int count);
private:
    int fd;
    char *serial_path;
};

class Serial_middle : public Class_Public
{

public:
    Serial_middle(Serial_app *pSerial_app);
    ~Serial_middle();
    RXPacket *RecvPacket(void);
    u8 SendPacket(TXPacket *packet);
    void Start(void);
    void Stop(void);

private:
    static void *ReadRaw(void *pData);
    static void *WriteRaw(void *pData);
    u8 readThreadRunning;
    u8 writeThreadRunning;
    uchar rxBuff[16];
    Queue rxQueue;
    uchar txBuff[20];
    Queue txQueue;
    //uchar *ptxBuff;
    pthread_t readThread;
    pthread_t writeThread;
    Serial_raw serial_raw;
    Serial_app *pSerial_app;
};


#define ALLCARDDATA 1

class Serial_app
{

public:
    Serial_app();
    ~Serial_app();
    void Start();
    void Stop();
    //void DebugInfo(u8 flag);

    //AllCardDataStruct allCardData;

private:
    static void *Polling(void *pData);
    u8 pollingThreadRunning;
    pthread_t pollingThread;
    Serial_middle *pSerial_middle;
    int readFIFO_fd;
    int writeFIFO_fd;
    int led_fd;
};

#endif
