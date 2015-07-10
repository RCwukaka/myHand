#include "public.h"
int main()
{
    int write_fp = open(CGI2SERIALFIFO, O_WRONLY);
    int addr, data;
    u8 buff[8];
    u8 ret;
    while(1)
    {
        printf("input addr:");
        scanf("%d", &addr);
        printf("input data:");
        scanf("%d", &data);
        printf("========%d, %d\n", addr, data);
        buff[0] = addr;
        buff[1] = data;
        ret = write(write_fp, buff, 2);
        if(ret != 2)
            printf("write error!\n");
    }
    close(write_fp);
}

