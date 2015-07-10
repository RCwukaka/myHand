#ifndef __FUNC_H
#define __FUNC_H

#include <fcgi_stdio.h>      /*标准输入输出定义*/
#include <stdlib.h>     /*标准函数库定义*/
#include <unistd.h>     /*Unix标准函数定义*/
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
	int state;  //state=0/1  1 表示定时器开(able)	
	//char times[14][6];  //14个定时 ，"06:60"
};

struct transmiter
{
	int ID;
	char name[20]; //transmiter 's name
	char image[20];
	int scenstate; //scenstate=1 已添加到设备组，scenstate=0 未添加
	struct transvalues vv[16]; //每个遥控器，有16组channel值  vv[0] 表示channel 0
	struct transmiter *next;
};

struct room
{
	int ID;   //
	char name[20];
 	char image[20];
 	struct room *next;
	struct transmiter *transhead;   //二级链表头指针
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
	int exetime; //exetime :情景组延时执行时间 0~20 (0 表示立即执行 20 最多延长20min)
	struct devinscens *devhead;
	struct Scenarios *next;
};

/*struct transmiter
{
	int ID;
	char name[20]; //transmiter 's name
	char image[20];
	int scenstate; //scenstate=1 已添加到设备组，scenstate=0 未添加
	char channel[20];
	int hour;
	int minute;
	char workday[10];
	int state;  //state=0/1  1 表示定时器开(able)
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
