
#include "serial.h"
//#include "backupDB.h"
/*
void signal_handler(int sigNum)
{
    printf("sigNum:%d\n", sigNum);
    BackupDB::BackupFile();
}
*/
int main(int argc, char **argv)
{
    /*if((signal(SIGINT, signal_handler) == SIG_ERR) ||
        (signal(SIGTERM, signal_handler) == SIG_ERR))
    {
        printf("setup SIGINT error!\n");
    }
    BackupDB backupDB = BackupDB();
    DataBase_middle *pDataBase_middle = new DataBase_middle(DB_FILE_NAME);*/
    Serial_app serial_app = Serial_app();
    serial_app.Start();
    while(1)
    {
        fflush(stdout);
        sleep(1);
    }
    return 0;
}

