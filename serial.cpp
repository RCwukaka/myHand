
#include "serial.h"

/******************************************************************************
******************************************************************************/

void Class_Public::DebugMem(uchar *pMem, int len, const char *note)
{
    uchar *p = pMem;
    SERIAL_DEBUG("++++++++++%s+++++++\n", note);
    for(int n = 0; n < len; n++)
    {
        SERIAL_DEBUG("[%p]:0x%02X\n", p, *p);
        p++;
    }
    SERIAL_DEBUG("++++++++++++++++++++++++++\n");
}

Serial_raw::Serial_raw(char *path = SERIAL_PATH)
{
    serial_path = path;
    fd = open(serial_path,  O_RDWR | O_NOCTTY | O_NDELAY );
    if (-1 == fd)
    {
        printf("Can't Open %s\n", serial_path);
        return;
    }
    else
    {
        printf("open %s OK, fd %d\n", serial_path, fd);
    }
}
Serial_raw::~Serial_raw()
{
    if(-1 == fd)
    {
        printf("%s does not open\n", serial_path);
    }
    else
    {
        close(fd);
        printf("%s closed\n", serial_path);
    }
}
void Serial_raw::SetSpeed(int speed)
{
    int   status;
    struct termios   Opt;
    tcgetattr(fd, &Opt);
    for(uint i = 0; i < sizeof(speed_arr) / sizeof(int); i++)
    {
        if (speed == name_arr[i])
        {
            tcflush(fd, TCIOFLUSH);
            cfsetispeed(&Opt, speed_arr[i]);
            cfsetospeed(&Opt, speed_arr[i]);
            status = tcsetattr(fd, TCSANOW, &Opt);
            if (status != 0)
                perror("tcsetattr fd1");
            return;
        }
        tcflush(fd, TCIOFLUSH);
    }
}
int Serial_raw::SetParity(int databits, int stopbits, int parity)
{
    struct termios options;
    if ( tcgetattr( fd, &options) != 0)
    {
        perror("SetupSerial 1");
        return(FALSE);
    }

    //set Raw Mode
    options.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input*/
    options.c_oflag  &= ~OPOST;   /*Output*/
    options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

    options.c_cflag |= CREAD;
    options.c_cflag &= ~CSIZE;

    switch (databits) /*设置数据位数*/
    {
    case 7:
        options.c_cflag |= CS7;
        break;
    case 8:
        options.c_cflag |= CS8;
        break;
    default:
        fprintf(stderr, "Unsupported data size\n");
        return (FALSE);
    }
    switch (parity)
    {
    case 'n':
    case 'N':
        options.c_cflag &= ~PARENB;   /* Clear parity enable */
        options.c_iflag &= ~INPCK;     /* Enable parity checking */
        break;
    case 'o':
    case 'O':
        options.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/
        options.c_iflag |= INPCK;             /* Disnable parity checking */
        break;
    case 'e':
    case 'E':
        options.c_cflag |= PARENB;     /* Enable parity */
        options.c_cflag &= ~PARODD;   /* 转换为偶效验*/
        options.c_iflag |= INPCK;       /* Disnable parity checking */
        break;
    case 'S':
    case 's': /*as no parity*/
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;
        break;
    default:
        fprintf(stderr, "Unsupported parity\n");
        return (FALSE);
    }
    /* 设置停止位*/
    switch (stopbits)
    {
    case 1:
        options.c_cflag &= ~CSTOPB;
        break;
    case 2:
        options.c_cflag |= CSTOPB;
        break;
    default:
        fprintf(stderr, "Unsupported stop bits\n");
        return (FALSE);
    }
    /* Set input parity option */
    if (parity != 'n') options.c_iflag |= INPCK;
    options.c_cc[VTIME] = 150; // 15 seconds
    options.c_cc[VMIN] = 0;

    tcflush(fd, TCIFLUSH); /* Update the options and do it NOW */
    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
        perror("SetupSerial 3");
        return (FALSE);
    }
    return (TRUE);
}
int Serial_raw::ReadData(void *buf, int count)
{
    if(-1 == fd)
    {
        printf("%s does not open\n", serial_path);
        return -1;
    }
    else
    {
        return read(fd, buf, count);
    }
}
int Serial_raw::WriteData(void *buf, int count)
{
    if(-1 == fd)
    {
        printf("%s does not open\n", serial_path);
        return -1;
    }
    else
    {
       // DebugMem((uchar *)buf, count, "write_raw");
        return write(fd, buf, count);
    }
}

//these codes for test
#ifdef Serial_raw_test
int main(int argc, char **argv)
{
    /*char buff[512];
    char *pbuff = buff, buffLen = 0;
    int nread, n;

    Serial_raw serial_raw_test;
    serial_raw_test.SetSpeed(115200);
    if (serial_raw_test.SetParity(8, 1, 'N') == FALSE)
    {
        printf("Set Parity Error\n");
        exit(1);
    }
    while(1)
    {
        nread = serial_raw_test.ReadData(pbuff, 1);
        if(nread > 0)
        {
            pbuff++;
            buffLen ++;// nread;
            if(40 == buffLen)
            {
                printf("++++++++++++++++++++++\n");
                pbuff = (char *)&buff;
                for(n = 0; n < 40; n++)
                {
                    printf("[%p]:0x%02X\n", pbuff, *pbuff);
                    pbuff++;
                }
                printf("++++++++++++++++++++++\n");
                memset(buff, 0, sizeof(buff));
                buffLen = 0;
                pbuff = buff;
                msleep(500);

            }
        }
        usleep(5);
    } */
	
    char buff[512] = "hello";
    char *pbuff = buff, buffLen = 0;
    int nwrite, n;

    Serial_raw serial_raw_test;
    serial_raw_test.SetSpeed(9600);
    if (serial_raw_test.SetParity(8, 1, 'N') == FALSE)
    {
        printf("Set Parity Error\n");
        exit(1);
    }
	printf("serial init sucess\n");
    while(1)
    {
        nwrite= serial_raw_test.WriteData(pbuff, 1);
        if(nwrite> 0)
        {
            pbuff++;
            buffLen ++;// nread;
            
        }
		else
		{
			printf("send success\n");
			break;
		}
        usleep(5);
    }    
    return 0;
}
#endif

/******************************************************************************
******************************************************************************/

Serial_middle::Serial_middle(Serial_app *pSerial_app) 
{
    //serial_raw = Serial_raw();
    this->pSerial_app = pSerial_app;
    serial_raw.SetSpeed(9600);
    if (serial_raw.SetParity(8, 1, 'N') == FALSE)
    {
        printf("Set Parity Error\n");
        //exit(1);
    }
    //    pthread_mutex_init(&rxMutex, NULL);
    //Start();
}

Serial_middle::~Serial_middle()
{
    Stop();
}

void Serial_middle::Start(void)
{
    int error;
    readThreadRunning = 1;
    writeThreadRunning = 1;
    error = pthread_create(&writeThread, NULL, WriteRaw, this);
    if(error != 0)
    {
        printf("readThread not created\n");
        //exit(1);
    }
    error = pthread_create(&readThread, NULL, ReadRaw, this);
    if(error != 0)
    {
        printf("readThread not created\n");
        //exit(1);
    }
    //pthread_join(writeThread, NULL);
    //pthread_join(readThread, NULL);
} 

void Serial_middle::Stop(void)
{
    int error;
    readThreadRunning = 0;
    writeThreadRunning = 0;
    error = pthread_join(writeThread, NULL);
    if(0 != error)
    {
        printf("writeThread exit error\n");
    }
    else
    {
        printf("writeThread exit ok\n");
    }
    error = pthread_join(readThread, NULL);
    if(0 != error)
    {
        printf("readThread exit error\n");
    }
    else
    {
        printf("readThread exit ok\n");
    }
}

void *Serial_middle::ReadRaw(void *pData)
{
    int len = 0, nread = 0;
    RXPacket *pPacket;
    Serial_middle *pObj = (Serial_middle *)pData;
    uchar *pBuff = pObj->rxBuff;

    printf("ReadRaw start\n");
    while(pObj->readThreadRunning)
    {
        nread = pObj->serial_raw.ReadData(pBuff, 1);
        if(nread > 0)
        {
            pBuff++;
            len++;
            if(*(pBuff - 1) == 0xCA) //a packet ok
            {
                if(pObj->rxBuff[0] != 0xC3)
                {
                    pObj->DebugMem(pObj->rxBuff, len, "Head ERR!");
                    goto error;
                }

                pObj->DebugMem(pObj->rxBuff, len, "ReadRaw");

                pPacket = (RXPacket *)malloc(sizeof(RXPacket));
                if(pPacket == NULL)
                {
                    printf("malloc RXPacket error!\n");
                    break;
                }

                //fill the data
                pPacket->synHead = pObj->rxBuff[0];
                pPacket->addr = pObj->rxBuff[1];
                pPacket->dataLen = len - 3; //减去同步头、地址、同步尾，3个字节
                memcpy(pPacket->data, pObj->rxBuff + 2, pPacket->dataLen);
                pPacket->synRear = pObj->rxBuff[len-1];

                //fill data finished, insert data to queue
                pObj->rxQueue.QInsertRear(pPacket);

error:
                memset(pObj->rxBuff, 0, sizeof(pObj->rxBuff));//clear the rxBuff
                len = 0;
                pBuff = pObj->rxBuff;
            }

            if(len == sizeof(pObj->rxBuff))
            {
                pObj->DebugMem(pObj->rxBuff, len, "Data ERR!");
                memset(pObj->rxBuff, 0, sizeof(pObj->rxBuff));//clear the rxBuff
                len = 0;
                pBuff = pObj->rxBuff;
            }
        }
        usleep(500);
    }
    printf("ReadRaw end\n");
    return NULL;
}

void *Serial_middle::WriteRaw(void *pData)
{
    Serial_middle *pObj = (Serial_middle *)pData;
    TXPacket *pPacket;
	int i;
    //memset(pObj->txBuff, 0, sizeof(pObj->txBuff));

    printf("WriteRaw start\n");
    while(pObj->writeThreadRunning)
    {
        //printf("writeThreadRunning...\n");
        pPacket = (TXPacket *)pObj->txQueue.QGetFront();
		
		//for debug 
		//printf("i am wt,addr:%d cmd:%d\n",pObj->txBuff[1],pObj->txBuff[2]);
		
        if(pPacket != NULL)
        {
            pObj->txBuff[0] = pPacket->head;
			for(i = 1;i < 15;i++)
			{
				pObj->txBuff[i] = pPacket->data[i];
			}
			
            pObj->txBuff[15] = pPacket->rear[0];
			pObj->txBuff[16] = pPacket->rear[1];
            pObj->serial_raw.WriteData(pObj->txBuff, 17);
        }
        msleep(1);//serial rate:9600pbs~1K/S
    }
    printf("WriteRaw end\n");
    return NULL;
}

RXPacket *Serial_middle::RecvPacket(void)
{
    RXPacket *pPacket;
    pPacket = (RXPacket *)rxQueue.QGetFront();
    return pPacket;
}

u8 Serial_middle::SendPacket(TXPacket *packet)
{
    if(packet == NULL)
        return FALSE;
    return txQueue.QInsertRear(packet);
}

//these code for test
#ifdef Serial_middle_test
int main(int argc, char **argv)
{
    Serial_middle serial_middle_test;
    RXPacket *pPacket;
    int ret = 0;
    while(1)
    {
        pPacket = serial_middle_test.RecvPacket();
        if(pPacket != NULL)
        {
            printf("ReadPacket a packet\t");
            printf("synHead:0x%02X, addr:0x%02X, pData:0x%02X, synRear:0x%02X\n", pPacket->synHead,
                   pPacket->addr, *(pPacket->pData), pPacket->synRear);
        }
        msleep(200);
    }
    return 0;
}
#endif

/******************************************************************************
******************************************************************************/

Serial_app::Serial_app() //make fifo
{
    //printf("SmartHome\n");
    this->pSerial_middle = new Serial_middle(this);
    if((mkfifo(CGI2SERIALFIFO, 0666) < 0) && (errno != EEXIST))
        printf("cannot create %s\n", CGI2SERIALFIFO);
    
    readFIFO_fd = open(CGI2SERIALFIFO, O_RDONLY);//只读 默认阻塞
    if (-1 == readFIFO_fd)
    {
        printf("Can't Open %s\n", CGI2SERIALFIFO);
    }
	//printf("open succes\n");
}

Serial_app::~Serial_app()
{
    Stop();
}

void Serial_app::Start()  //create pollingthread
{
    this->pSerial_middle->Start();

    pollingThreadRunning = 1;
    int error = pthread_create(&pollingThread, NULL, Polling, this);
    if(error != 0)
    {
        printf("pollingThread not created\n");
    }
}

void Serial_app::Stop()  //  stop pollingthread
{
    int error;
    pollingThreadRunning = 0;
    error = pthread_join(pollingThread, NULL);
    if(0 != error)
    {
        printf("pollingThread exit error\n");
    }
    else
    {
        printf("pollingThread exit ok\n");
    }
}

void *Serial_app::Polling(void *pData)
{
	printf("polling start\n");
    Serial_app *pObj = (Serial_app *)pData;
    int i,count = 0;
 
   // u8 led_state = 0;
    char readBuff[20];
    //RXPacket *pPacket;
    TXPacket txPacket;
    txPacket.head = 0x3E; // >
    txPacket.rear[0] = 0x0D; //回车  head rear
	txPacket.rear[1] = 0x0A; //换行
	
    SERIAL_DEBUG("Polling start\n");
    while(pObj->pollingThreadRunning)
    {

        strzero(readBuff);
        count = read(pObj->readFIFO_fd, readBuff, 7);
        if(count > 0)
        {
            printf("get:%s\n", readBuff);
            
            //led_state = 1 - led_state;
           // ioctl(pObj->led_fd, led_state, 2);

			//将readbuf中的字符串转为ASCII码
          sprintf(readBuff,"%d%d%d%d%d%d%d",
           			ctoasc(readBuff[0]),
           			ctoasc(readBuff[1]),
           			ctoasc(readBuff[2]),
           			ctoasc(readBuff[3]),
           			ctoasc(readBuff[4]),
           			ctoasc(readBuff[5]),
           			ctoasc(readBuff[6]));

			//txPacket.datalen = strlen(readBuff);
			// attention: data u8 只能一位一位的赋值 
			for(i = 0;i < 14;i++)
			{
				txPacket.data[i] = (u8)readBuff[i];
			}
			
            pObj->pSerial_middle->SendPacket(&txPacket);//发送

            //pPacket = pObj->pSerial_middle->RecvPacket();//接收 */
        }
        msleep(10);

    }
    printf("Polling end\n");
    return NULL;
}

#ifdef Serial_app_test
int main(int argc, char **argv)
{
    
    Serial_app serial_app_test = Serial_app();
    serial_app_test.Start();
    while(1)
        sleep(1);
    return 0;
}
#endif 


