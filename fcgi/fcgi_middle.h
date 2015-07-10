#ifndef __GETDATA_H
#define __GETDATA_H

//#include "../dataBase.h"
//#include "deviceInfo.h"
#include   <sys/types.h>
#include   <sys/socket.h>
#include   <sys/ioctl.h>
#include   <netinet/in.h>
#include   <net/if.h>
#include   <net/if_arp.h>
#include   <arpa/inet.h>
#include   <errno.h>
#include   <ctype.h>
#include   "public.h"

//#define FCGI_middle_test
//#define ParseStr_test
//#define GetData_rand_data_test

#define STRINTLEN  1024

class FCGI_middle
{
public:
    FCGI_middle();
    ~FCGI_middle();

    char *SendCmd(int rmID,int transID, int cmd);//�����豸��Ⱥ���豸�ݶ���ʹ�ñ�����
    char *GetDeviceNormalInfo();
    char *GetDeviceRunningInfo();

    u8 RebootDevice();
    u8 ResetDevice();
    char *ModifyIP(const char *ip);
    char *ModifyUser(const char *name, const char *pwd);

    //char outputString[STRINTLEN];
    int temperature;
   // system_info deviceInfo;

private:
    char ipAddrStr[16];
    char hwAddrStr[5]; //MAC��ַ����λ(16����)
    int writeFIFO_fp;
    int readFIFO_fp;
    char writeBuf[10];
    //u8 readBuf[8];
};

#endif
