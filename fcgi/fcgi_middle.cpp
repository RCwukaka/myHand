#include "fcgi_middle.h"

FCGI_middle::FCGI_middle()
{
    
   writeFIFO_fp = open(CGI2SERIALFIFO, O_WRONLY);  //where to create fifo???
	
    //get ip addr and hardware addr
    memset(ipAddrStr, '\0', sizeof(ipAddrStr));
    memset(hwAddrStr, '\0', sizeof(hwAddrStr));

    struct ifreq getinfo_ifreq;  //ifreq ��������ip
    struct sockaddr_in *ip_addr;
    int sock;

    strcpy(getinfo_ifreq.ifr_name, "eth0");
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        goto end;

    if(ioctl(sock, SIOCGIFADDR, &getinfo_ifreq) < 0)//get ip addr
        goto end;

	//ȡ��ַ��Ȼ��ǿ��ת��Ϊ struct sockaddr_in * ���͵�ָ��
    ip_addr = (struct sockaddr_in *) & (getinfo_ifreq.ifr_addr);
    sprintf(ipAddrStr, "%s", inet_ntoa(ip_addr->sin_addr));

    if(ioctl(sock, SIOCGIFHWADDR, &getinfo_ifreq) < 0)//get hardware addr
        goto end;
	//sockaddr �ṹ���� char sa_data[14]
    /*sprintf(hwAddrStr, "%02x%02x%02x%02x%02x%02x",
            (unsigned char)getinfo_ifreq.ifr_hwaddr.sa_data[0],
            (unsigned char)getinfo_ifreq.ifr_hwaddr.sa_data[1],
            (unsigned char)getinfo_ifreq.ifr_hwaddr.sa_data[2],
            (unsigned char)getinfo_ifreq.ifr_hwaddr.sa_data[3],
            (unsigned char)getinfo_ifreq.ifr_hwaddr.sa_data[4],
            (unsigned char)getinfo_ifreq.ifr_hwaddr.sa_data[5]);*/
            
    //��ȡMAC��ַ�ĺ���λ
	sprintf(hwAddrStr, "%02x%02x",
            (unsigned char)getinfo_ifreq.ifr_hwaddr.sa_data[4],
            (unsigned char)getinfo_ifreq.ifr_hwaddr.sa_data[5]);
	//printf("hw:%s",hwAddrStr);
end:
    close(sock);
}

FCGI_middle::~FCGI_middle()
{
    //Stop();
    //delete this->pDataBase_middle;
}
char *FCGI_middle::SendCmd(int rmID,int transID, int cmd)
{
    u8 ret;
    if((cmd < 0) || (cmd > 255))
        return "0";
    //strzero(outputString);
   // strzero(readBuf);
    strzero(writeBuf);
	/*writebuf MAC��ַ����λ+roomID+transID+cmd
		> :��ʾ��ʼλ
		0x0D0x0A:��ַ
		*/
    sprintf(writeBuf,"%4s%d%d%d",hwAddrStr,rmID,transID,cmd);
	//printf("%s\n",writeBuf);
	//��MAC��ַ�ĺ���λ��ֵ��writebuf
    		
    ret = write(writeFIFO_fp,writeBuf,7);
	
	//printf("ret = %d\n",ret);
    if(7 == ret)
        return "1";
    else
        return "0";
}

/*char *FCGI_middle::GetDeviceNormalInfo()
{
    memset(outputString, '\0', STRINTLEN);
    strcat(outputString, PRODUCTID);
    strcat(outputString, ",");
    strcat(outputString, ipAddrStr);
    strcat(outputString, ",");
    strcat(outputString, hwAddrStr);
    strcat(outputString, ",");
    strcat(outputString, SOFTWAREVER);
    strcat(outputString, ",");
    strcat(outputString, HARDWAREVER);
    return outputString;
}

char *FCGI_middle::GetDeviceRunningInfo()
{
    char temp[32] = {0};
    float cpuLoad = 0.0;
    if(get_system_info(&deviceInfo) == FALSE)
        return NULL;
    strzero(outputString);
    cpuLoad = deviceInfo.cpustates[0] / 3;
    if(cpuLoad > 100)
        cpuLoad = 100;
    sprintf(temp, "%.1f,", cpuLoad); //cpu����
    strcat(outputString, temp);

    sprintf(temp, "%.1f,", (float)100 * (deviceInfo.memory[0] - deviceInfo.memory[1]) / deviceInfo.memory[0]); //�ڴ�ʹ��
    strcat(outputString, temp);

    sprintf(temp, "%ld,", (long)deviceInfo.now); //ϵͳʱ��
    strcat(outputString, temp);

    //����������ݽ��в���
    srand((unsigned) time(NULL));
    temperature = rand() % 600;
    sprintf(temp, "%.1f,", (float)temperature / 10); //�¶�
    strcat(outputString, temp);

    sprintf(temp, "%ld,", (long)deviceInfo.uptime[0]); //����ʱ��
    strcat(outputString, temp);

    sprintf(temp, "%.1f,", (deviceInfo.uptime[0] - deviceInfo.uptime[1]) / deviceInfo.uptime[0]); //CPU��ʹ����
    strcat(outputString, temp);

    return outputString;
}

u8 FCGI_middle::RebootDevice()
{
    if(fork() == 0)
    {
        execl("/sbin/reboot", "reboot", (char *)NULL);
    }
    return TRUE;
}

u8 FCGI_middle::ResetDevice()
{
    return TRUE;
}

char *FCGI_middle::ModifyIP(const char *ip)
{
    FILE *fp;
    int fileSize;
    int readSize;
    char *pStart;
    char *fileConten = NULL;
    fp = fopen("/etc/init.d/rcS", "r");
    if (fp == NULL)
        return NULL;

    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp); // �����ļ�����
    
    fileConten = (char *)malloc(fileSize);
    if(fileConten == NULL)
        return NULL;
    rewind(fp);  //ʹ�ļ��ڲ���λ��ָ������ָ���ļ��Ŀ�ͷ
	
    readSize = fread(fileConten, 1, fileSize, fp);  //���ļ��������ݶ���fileconten��
    if(fileSize != readSize)
    {
        fclose(fp);
        return NULL;
    }
    fclose(fp);  //close fp
	
    pStart = strstr(fileConten, ipAddrStr); //��fileconten �в��� ipAddrStr��������ָ���λ�õ�ָ��
    if(pStart == NULL)
        return NULL;

    //open again and clear it
    fp = fopen("/etc/init.d/rcS", "w");
    if (fp == NULL)
        return NULL;

	//1fwrite ��ipǰ����ַ�д�뵽 fp(ע��д���ļ��ڲ���λ��ָ������?)
	//2fwrite �ٽ�ip����  д�뵽 fp
	//3fwrite
    fwrite(fileConten, 1, pStart - fileConten, fp);
    fwrite(ip, 1, strlen(ip), fp);
    fwrite(pStart + strlen(ipAddrStr), 1, fileSize - strlen(ipAddrStr) - (pStart - fileConten), fp);
    fclose(fp);

    free(fileConten);

    return "1";
}

char *FCGI_middle::ModifyUser(const char *name, const char *pwd)
{
    FILE *fp;
    char fileContent[32] = {'\0'};
    fp = fopen("/etc/lighttpd/lighttpd.user", "w");
    if (fp == NULL)
        return NULL;
    sprintf(fileContent, "%s:%s\n", name, pwd);
    fputs(fileContent, fp);
    fclose(fp);
    return "1";
}

/*
float FCGI_middle::GetTemperData()
{
	float temperData;
	#ifdef GetData_rand_data_test
	//����������ݽ��в���
	srand((unsigned) time(NULL));
	temperature = rand() % 600;
	#else
	pDataBase_middle->GetTemperature(&temperature);
	#endif
	temperData = (float)temperature/10;
	return temperData;
}
*/

#ifdef FCGI_middle_test

int main(int argc, char **argv)
{
    int i;
	char *c;
    FCGI_middle fcgi_middle = FCGI_middle();

	//c = fcgi_middle.SendCmd(1,1,1);
	//puts(c);
    return 0;
}

#endif

