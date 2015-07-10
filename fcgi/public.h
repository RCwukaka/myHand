 #ifndef __PUBLIC_H
#define __PUBLIC_H

#include <stdio.h>      /*标准输入输出定义*/
#include <stdlib.h>     /*标准函数库定义*/
#include <unistd.h>     /*Unix标准函数定义*/
#include <sys/types.h> /**/
#include <sys/stat.h>   /**/
#include <fcntl.h>      /*文件控制定义*/
#include <errno.h>      /*错误号定义*/
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <pthread.h>
#include <time.h>
  #include <sys/time.h>
  #include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <sys/stat.h>

#define SERIAL2CGIFIFO "/opt/smartHome/serial2cgififo"
#define CGI2SERIALFIFO "/opt/smartHome/cgi2serialfifo"

union semun
{
    int val;                    /* Value for SETVAL */
    struct semid_ds *buf;       /* Buffer for IPC_STAT, IPC_SET */
    unsigned short    *array;    /* Array for GETALL, SETALL */
    struct seminfo    *__buf;    /* Buffer for IPC_INFO*/
};

#define msleep(x) usleep(x*1000) //usleep 把进程挂起一段时间

#define strzero(a) memset((a), 0, (sizeof(a)))

#define PRODUCTID       "000-000-000"   //产品序列号
#define SOFTWAREVER     "V0.1Beta"      //软件版本号
#define HARDWAREVER     "V0.01"         //硬件版本号

//#define DB_FILE_NAME        "/root/mtdblock2/opt/zucn/db/data.db3"
//#define DB_BAK_FILE_NAME    "/root/mtdblock2/opt/zucn/data.db3"
#define DB_FILE_NAME        "/opt/zucn/db/data.db3"
#define DB_BAK_FILE_NAME    "/opt/zucn/data.db3"
#define TEMPERATURE_PATH    "/dev/18b20"

#ifndef NULL
#define NULL	0
#endif

#ifndef FALSE
#define FALSE	0
#endif

#ifndef TRUE
#define TRUE	1
#endif

#ifndef uint
#define uint    unsigned int
#endif

#ifndef uchar
#define uchar    unsigned char
#endif

#ifndef u8
#define u8    unsigned char
#endif

#ifndef u16
#define u16    unsigned short
#endif


#ifndef u32
#define u32    unsigned int
#endif

typedef struct
{
    u8 synHead;
    u8 addr;
    u8 rspLen;
} TXPacketOld;

typedef struct
{
    u8 head;  // start  1 bit
    u8 addr;  //addr 1 byte
    u8 data;
    u8 CRC;
    u8 rear; //rear  stop 2 bits
} TXPacket;  //TXPacket 发送包

typedef struct
{
    u8 synHead;
    u8 addr;
    u8 synRear;
    u8 dataLen;
    uchar data[4]; //最多四个
} RXPacket;  //RXPacket 接受包

typedef struct
{
    u8 synHead;
    u16 addr;
    uchar data1;
    uchar data2;
    u8 synRear;
} rxOldPacket;

//#pragma pack(2)

//每一块板卡的信息
//noUse 没有任何信息，因结构体第一项会出现莫名其妙的问题!!!
//问题找到，由于sscanf导致!!!下一步自己编写字符串转整形函数!
typedef struct
{
    //u8 noUse;
    char panelID[8];
    char panelType[16];
    char cardType[16];
    u8 videoChannel;//视频通道数量
    u8 cardAddress; //cardAddress即为cardSlot
    u8 cardDataLen;//cardData32有效数据字节数,从低到高
    u8 dataFlag;
    u32 cardData32;
    u32 cardDataMask;
    //u8 *pCardData;
} CardDataStruct;
//#pragma pack()

#define maxCardNum 16

#endif
