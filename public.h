#ifndef __PUBLIC_H
#define __PUBLIC_H
#include <stdio.h>      /*��׼�����������*/
#include <stdlib.h>     /*��׼�����ⶨ��*/
#include <unistd.h>     /*Unix��׼��������*/
#include <sys/types.h> /**/
#include <sys/stat.h>   /**/
#include <fcntl.h>      /*�ļ����ƶ���*/
#include <errno.h>      /*����Ŷ���*/
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
#include <ctype.h>

//#define SERIAL2CGIFIFO "/opt/smartHome/serial2cgififo"
#define CGI2SERIALFIFO "/opt/smartHome/cgi2serialfifo"

#define msleep(x) usleep(x*1000)

#define strzero(a) memset((a), 0, (sizeof(a)))
#define itoasc(n) (n - '0' + 48)
#define ctoasc(c) (isdigit(c)) ? itoasc(c) : (c - 'a' + 97)

#define PRODUCTID       "000-000-000"   //��Ʒ���к�
#define SOFTWAREVER     "V0.1Beta"      //����汾��
#define HARDWAREVER     "V0.01"         //Ӳ���汾��

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
    u8 head;
    u8 addr;
    u8 data;
    u8 CRC;
    u8 rear;
} TXPacketold;

typedef struct
{
    u8 head;  //start  >
   // uint datalen;
	uchar data[20];
	u8 rear[2]; //stop  0x0D(�س�) 0x0A(����)
} TXPacket;

typedef struct
{
    u8 synHead;
    u8 addr;
    u8 synRear;
    u8 dataLen;
    uchar data[4]; //����ĸ�
} RXPacket;



//#pragma pack(2)

//ÿһ��忨����Ϣ
//noUse û���κ���Ϣ����ṹ���һ������Ī�����������!!!
//�����ҵ�������sscanf����!!!��һ���Լ���д�ַ���ת���κ���!
typedef struct
{
    //u8 noUse;
    char panelID[8];
    char panelType[16];
    char cardType[16];
    u8 videoChannel;//��Ƶͨ������
    u8 cardAddress; //cardAddress��ΪcardSlot
    u8 cardDataLen;//cardData32��Ч�����ֽ���,�ӵ͵���
    u8 dataFlag;
    u32 cardData32;
    u32 cardDataMask;
    //u8 *pCardData;
} CardDataStruct;
//#pragma pack()

#define maxCardNum 16

#endif
