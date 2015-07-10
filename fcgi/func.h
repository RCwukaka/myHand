#ifndef __FUNC_H
#define __FUNC_H

#include <fcgi_stdio.h>      /*��׼�����������*/
#include <stdlib.h>     /*��׼�����ⶨ��*/
#include <unistd.h>     /*Unix��׼��������*/
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

#define RMMAX 8
#define TRANSMAX 16
#define strzero(a) memset((a), 0, (sizeof(a)))
 
struct transvalues
{
	char hour[4];
	char minute[4];
	char workday[20];
	int state;  //state=0/1  1 ��ʾ��ʱ����(able)	
	//char times[14][6];  //14����ʱ ��"06:60"
};

struct transmiter
{
	int ID;
	char name[20]; //transmiter 's name
	char image[20];
	int scenstate; //scenstate=1 ����ӵ��豸�飬scenstate=0 δ���
	struct transvalues vv[16]; //ÿ��ң��������16��channelֵ  vv[0] ��ʾchannel 0
	struct transmiter *next;
};

struct room
{
	int ID;   //
	char name[20];
 	char image[20];
 	struct room *next;
	struct transmiter *transhead;   //��������ͷָ��
};

//Scenarios mode

struct devinscens
{
	char rmname[20];
	char transname[20];
	char transimage[20];
	int cmd;
	struct devinscens *next;
};

struct Scenarios
{
	char name[20];
	int exetime; //exetime :�龰����ʱִ��ʱ�� 0~20 (0 ��ʾ����ִ�� 20 ����ӳ�20min)
	struct devinscens *devhead;
	struct Scenarios *next;
};

/*struct transmiter
{
	int ID;
	char name[20]; //transmiter 's name
	char image[20];
	int scenstate; //scenstate=1 ����ӵ��豸�飬scenstate=0 δ���
	char channel[20];
	int hour;
	int minute;
	char workday[10];
	int state;  //state=0/1  1 ��ʾ��ʱ����(able)
	struct transmiter *next;
};*/

struct room* Initroom(void);
int Addroom(char *name,char *image);
int Delroom(char *name);
struct room* Searchroom(char *name,int times);
int Searchroomnums(void);
int Changeroominfo(char *roomname,char *newrmname,char *newrmimage);
int Addtransmiter(char *rmname,char *transname,char *transimage);
int Deltransmiter(char *rmname,char *transname);
struct transmiter* Searchtransmiter(char *rmname,char *transname,int times);
int Searchtransnums(char *rmname);
int Savetransvalue(char *rmname,char *transname,int channel,struct transvalues *temp);
struct transvalues* Searchtransvalue(char *rmname,char *transname,int channel);
int Changetransmiterinfo(char *roomname,char *transname,char *newtransname,char *newtransimage);
int itoasc(int n);
int ctoasc(char *c);
char *getTime(void);

struct Scenarios* InitScenarios(void);
int AddScenarios(char *name);
int DelScenarios(char *name);
int Searchscensnums(void);
struct Scenarios* Searchscens(char *name,int times);
int Changescensinfo(char *name,char *newname);
int ADDdevinscens(char *scensname,char *rmname,char *transname,char *transimage);
int Deldevinscens(char *scensname,char *rmname,char *transname);
char *Searchdevinscens(char *scensname,char *rmname,int key);

#endif
