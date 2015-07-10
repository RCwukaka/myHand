#include "func.h"

struct room *rmhead; 
struct Scenarios *scenshead;

int rmID[RMMAX] = {0};  //rmID数组中第i个值为1，说明i值已经分配为ID号，反之，则没有被分配
int transID[TRANSMAX] = {0};

struct room* Initroom(void)
{
	struct room *head;
	head = (struct room *)calloc(1,sizeof(struct room));
	head->transhead = (struct transmiter*)calloc(1,sizeof(struct transmiter));
	if(head == NULL || head->transhead == NULL)
	{
		printf("calloc error\n");
		return NULL;
	}
	head->ID = 0;
	strzero(head->image); 
	strzero(head->name);
	head->next = NULL;
	head->transhead->next = NULL;
	
	return head;
}

//每一个 新的room节点生成时，不要忘了给room节点中的transmiter 链表分配头节点
int Addroom(char *name,char *image)
{
	int i = 0  ;  //i 表示房间ID，房间ID 从0开始
	struct room *newrm;  
	struct room *current;

	current = rmhead;
	while(current->next != NULL)
	{
		current = current->next;//current is the frist one in the list
		
		if(strncmp(current->name,name,20) == 0)
		{
			//the name room is already exist
			return 1;  
		}
	}

	//creat new room listNode
	newrm = (struct room*)calloc(1,sizeof(struct room));
	newrm->transhead = (struct transmiter*)calloc(1,sizeof(struct transmiter)); 
	if(newrm == NULL || newrm->transhead == NULL)
	{
		//printf("calloc error\n");
		return -1;
	}

	/*find the new room's ID*/
	while((rmID[i] != 0) && (i < RMMAX))
	{
		i++;  
	}

	/*room full*/
	if(i == RMMAX)
	{
		return -1;  //?????
	}

	/*init newrm*/
	strncpy(newrm->image,image,20);
	strncpy(newrm->name,name,20);
	newrm->ID = i;  //房间ID从0 开始

	rmID[i] = 1;
	
	/*add new room*/
	current->next = newrm; //链表遍历完后，current 是list最后一个节点
	newrm->next = NULL;
	newrm->transhead->next = NULL;
	
	return 0;
}

int Delroom(char *name)
{
	struct room *current;
	struct room *precious;

	precious = rmhead;
	current = rmhead->next;
	
	while((current != NULL) &&(strncmp(name,current->name,20) != 0))
	{
		precious = current;
		current = current->next;
	}

	if(current == NULL)// the name room  is not exist  
	{
		return -1;
	}
	else
	{
		precious->next = current->next;  //delete the room
		
	}

	rmID[current->ID] = 0; //房间删除后，rmID中的第(current->ID)位 为 0
	free(current);
	
	return 0;
}

/**/
struct room* Searchroom(char *name,int times)
{
	int i;
	struct room *current;
	current = rmhead;
    
	if(times == 0)
	{
		current = current->next; //current is the frist Node
		while((current != NULL) &&(strncmp(name,current->name,20) != 0))
		{
			current = current->next;
		}

		if(current == NULL)  //the room is not exist
		{
			return NULL;
		}
	}
	else
	{
		for(i = 0;i < times;i++) //i值的大小决定取链表中第i个节点的值
		{	
			if(current->next != NULL)
			{
				current = current->next;
			}
			else
			{
				return NULL;
			}
		}
	}

	return current;
}

/*Searchallroom:查询房间总数*/
int Searchroomnums(void)  
{
	int num = 0;
	struct room * current;

	current = rmhead->next;
	while(current != NULL)
	{
		num++;
		current = current->next;
	}

	return num;
}

int Addtransmiter(char *rmname,char *transname,char *transimage)
{
	int i = 0 ;  //i 表示遥控器ID号  从0开始
	struct room *rmtemp;
	struct transmiter *transnew, *current;
	int j;
	
	//确定此房间遥控器链表头
	if((rmtemp = Searchroom(rmname,0)) == NULL)  //find the room
	{
		return -1; //the room is not exist 
	}
	
	current = rmtemp->transhead;  //the transmiter's head in this room

	while(current->next != NULL) 
	{
		current = current->next;//current is the frist one in the list

		if(strncmp(current->name,transname,20) == 0)
		{
			//the new name transmiter is already exist
			return 1;
		}

	}
	
	transnew = (struct transmiter*)calloc(1,sizeof(struct transmiter));

	if(transnew == NULL)
	{
		return -1;
	}

	/*find the new transmitter's ID*/
	while((transID[i] != 0) && (i < TRANSMAX))
	{
		i++;  
	}

	/*transmitter full*/
	if(i == TRANSMAX)
	{
		return -1;  //?????
	}

	//init new transmitter list Node
	transnew->ID = i;
	strncpy(transnew->name,transname,20);
	strncpy(transnew->image,transimage,20);
	transnew->scenstate = 0; //scenstate 默认值为 0 
	//设置channel默认值
	
	for(j=0; j<16; j++)
	{
		strcpy(transnew->vv[j].hour,"--:");
		strcpy(transnew->vv[j].minute,"--");
		strcpy(transnew->vv[j].workday,"/--");
		transnew->vv[j].state = 0;
	}
	
	transID[i] = 1;  //表明 ID=i 已用

	current->next = transnew; //current is the last ,add in the end
	transnew->next = NULL;
	
	return 0;	
}

int Savetransvalue(char *rmname,char *transname,int channel,struct transvalues *temp)
{
	int i = 0 ;  //i 表示遥控器ID号  从0开始
	struct transmiter *transtemp;

	//确定此房间遥控器链表头
	if((transtemp = Searchtransmiter(rmname,transname,0)) == NULL)  //find the dev
	{
		return -1; //the dev is not exist 
	}
	
	//init new transmitter list Node
	strzero(&(transtemp->vv[channel]));
	transtemp->vv[channel] = *temp;
	
	return 0;	
}

int Deltransmiter(char *rmname,char *transname)
{
	struct room *rmtemp;
	struct transmiter *precious,*current;

	if((rmtemp = Searchroom(rmname,0)) == NULL)  //find the room
	{
		//printf("the %d room is not exixt\n",rmname);
		return -1;
	}

	precious = rmtemp->transhead; //the transmiter's head
	current = precious->next;  //the first one in the list

	while((current != NULL) && (strncmp(current->name,transname,20) != 0))
	{
		precious = current;
		current = current->next;
	}

	if(current == NULL)
	{
		//printf("the %d transmiter is not exitst\n",transname);
		return -1;
	}
	else
	{
		precious->next = current->next;
	}

	transID[current->ID] = 0;
	free(current);
}

/*查询单个房间遥控器总数*/
int Searchtransnums(char *rmname)  
{
	int num = 0;
	struct room *temp;
	struct transmiter *current;
	if((temp = Searchroom(rmname,0)) == NULL)
	{
		//printf("searchroom error\n");
		return -1;
	}

	current = temp->transhead;  //current 遥控器链表头
	while(current->next != NULL)
	{
		num++;
		current = current->next;
	}

	return num;
}

/*查询单个遥控器*/
struct transmiter* Searchtransmiter(char *rmname,char *transname,int times)
{
	struct room *rmtemp;
	struct transmiter *current;
	int i;

	if((rmtemp = Searchroom(rmname,0)) == NULL)  //find the room
	{
		//printf("the %d room is not exixt\n",rmname);
		return NULL;
	}

	current = rmtemp->transhead;

	if(times == 0) //search list by transmitter's name
	{
		current = current->next;
		while((current != NULL) && (strncmp(current->name,transname,20) != 0))
		{
			current = current->next;
		}

		if(current == NULL)
		{
			//printf("the %d transmiter is not exitst\n",transname);
			return NULL;
		}
	}
	else
	{
		for(i = 0;i < times;i++) //times表示链表遍历到第几个节点
		{	
			if(current->next != NULL)
			{
				current = current->next;
			}
			else
			{
				return NULL;
			}
		}
	}

	return current;
}

//Searchtransvalue:查询遥控器特定channel所设定的值
struct transvalues* Searchtransvalue(char *rmname,char *transname,int channel)
{
	struct transmiter *temp;
	struct transvalues *vtp;
	int i;

	if((temp = Searchtransmiter(rmname,transname,0)) == NULL)
	{
		//the dev is not exist
		return NULL;
	}

	vtp = &(temp->vv[channel]);
	return vtp;
}

//Changeroominfo:修改房间信息
int Changeroominfo(char *roomname,char *newrmname,char *newrmimage)
{
	struct room *temp;
	if((temp = Searchroom(newrmname,0)) != NULL)	
	{
		return 1; //the newroomname is already exist
	}
	else
	{
		if((temp = Searchroom(roomname,0)) == NULL)  //find the room
		{
			//printf("the %d room is not exixt\n",roomname);
			return -1;
		}

		/*change room's information*/
		strzero(temp->name);
		strzero(temp->image);
		strncpy(temp->name,newrmname,20);
		strncpy(temp->image,newrmimage,20);

		return 0;		
	}
}

int Changetransmiterinfo(char *roomname,char *transname,char *newtransname,char *newtransimage)
{
	struct transmiter *temp;
	if((temp = Searchtransmiter(roomname, newtransname,0)) != NULL)
	{
		//the new name trasmiter is already exist
		return 1;
	}
	
	if((temp = Searchtransmiter(roomname, transname,0)) == NULL)  //find the room
	{
		//the old name transmitter is not exist
		return -1;
	}

	/*change room's information*/
	strzero(temp->name);
	strzero(temp->image);
	strncpy(temp->name,newtransname,20);
	strncpy(temp->image,newtransimage,20);

	return 0;	
}

/*demoHome:服务器初始化时，就有三个房间:卧室 客厅 厨房*/
int demoHome(void)
{
	int ret;

	ret = Addroom("bedroom", "kk");

	if(ret != 0)
	{
		return -1;
	}

	//ret =Addtransmiter("bedroom", struct transmiter * temp);
	ret = Addroom("drawing room", "kk");

	if(ret != 0)
	{
		return -1;
	}

	ret = Addroom("kitchen", "kk");

	if(ret != 0)
	{
		return -1;
	}

	return 0;
}

int itoasc(int n)  //int to ascii
{
	return (n - '0' + 48); // 0 的 ASCII 是 48
}

int ctoasc(char c) //char to ascii
{
	if(isdigit(c) == 0) //不是数字
	{
		c = tolower(c); //将字符转换为小写
		return (c - 'a' + 97);
	}
	else
	{
		itoasc(c);
	}
}

char *getTime(void)
{
	static char timebuf[10];   //attention static
	struct tm *t;
	time_t tt;
	time(&tt);
	t = localtime(&tt);
	strzero(timebuf);
	sprintf(timebuf,"%d:%d:%d:%d",t->tm_hour,t->tm_min,t->tm_sec,t->tm_wday);
	//printf("%d %d %d %d:%d:%d\n",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
	return timebuf;
	
}

int settime(int hour,int min,int sec,int wday)
{
	time_t t;
	struct tm *tm;
	int ret;

	tm->tm_hour = hour;
	tm->tm_min = min;
	tm->tm_sec = sec;
	tm->tm_wday = wday;

	t = mktime(tm);

	if((ret = stime(&t)) == 0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

/*InitScenarios:初始化情景组链表，产生链表头*/
struct Scenarios* InitScenarios(void)
{
	struct Scenarios *head;
	head = (struct Scenarios *)calloc(1,sizeof(struct Scenarios));
	head->devhead= (struct devinscens*)calloc(1,sizeof(struct devinscens));
	if(head == NULL || head->devhead == NULL)
	{
		printf("calloc error\n");
		return NULL;
	}

	head->next = NULL;
	head->devhead->next = NULL;
	
	return head;
}

/* AddScenarios:添加情景组 */
int AddScenarios(char *name)
{
	struct Scenarios *newscens;  
	struct Scenarios *current;

	current = scenshead;
	while(current->next != NULL)
	{
		current = current->next;//current is the frist one in the list
		
		if(strncmp(current->name,name,20) == 0)
		{
			//the name Scenarios is already exist
			return 1;  
		}
	}

	//creat new Scenarios listNode
	newscens = (struct Scenarios*)calloc(1,sizeof(struct Scenarios ));
	newscens->devhead = (struct devinscens*)calloc(1,sizeof(struct devinscens)); 
	if(newscens == NULL || newscens->devhead == NULL)
	{
		//printf("calloc error\n");
		return -1;
	}

	/* init newscens */
	strncpy(newscens->name,name,20);
	newscens->exetime = -1; //默认值为-1，表示未设置情景组延时时间
	
	/* add new Scenarios listNode */
	current->next = newscens; //链表遍历完后，current 是list最后一个节点
	newscens->next = NULL;
	newscens->devhead->next = NULL;
	
	return 0;
}

//DelScenarios:删除情景组
int DelScenarios(char *name)
{
	struct Scenarios *current;
	struct Scenarios *precious;

	precious = scenshead;
	current = scenshead->next;
	
	while((current != NULL) &&(strncmp(name,current->name,20) != 0))
	{
		precious = current;
		current = current->next;
	}

	if(current == NULL)// the name scenraios is not exist  
	{
		return -1;
	}
	else
	{
		precious->next = current->next;  //delete the room
	}
	
	free(current);
	return 0;
}

//Searchallscens:查询情景组总数
int Searchscensnums(void)
{
	int num = 0;
	struct Scenarios *current;

	current = scenshead->next;
	while(current != NULL)
	{
		num++;
		current = current->next;
	}

	return num;
}

//Searchscens: 查询情景组
struct Scenarios* Searchscens(char *name,int times)
{
	struct Scenarios *current;
	int i; 
	/*find the scensname scenraios */
	current = scenshead; //current is the head

	if(times == 0)
	{
		current = current->next; //current is the frist Node
		while((current != NULL) &&(strncmp(name,current->name,20) != 0))
		{
			current = current->next;
		}

		if(current == NULL)  //the room is not exist
		{
			return NULL;
		}
	}
	else
	{
		for(i = 0;i < times;i++) //i值的大小决定取链表中第i个节点的值
		{	
			if(current->next != NULL)
			{
				current = current->next;
			}
			else
			{
				return NULL;
			}
		}
	}
	
	return current;
}

//Changescensinfo:修改情景组(name)
int Changescensinfo(char *name,char *newname)
{
	struct Scenarios *temp;
	if((temp = Searchscens(newname,0)) != NULL)	
	{
		return 1; //the newname scenraios is already exist
	}
	else
	{
		if((temp = Searchscens(name,0)) == NULL)  //find the scenraios
		{
			//printf("the scenraios is not exixt\n",roomname);
			return -1;
		}

		/*change scenraios's information*/
		strzero(temp->name);
		strncpy(temp->name,newname,20);

		return 0;		
	}
}

/*ADDdevinscens: 添加情景组设备  attention cmd */
int ADDdevinscens(char *scensname,char *rmname,char *transname,char *transimage)
{
	struct Scenarios *scenstemp;
	struct devinscens *current,*newdev;

	if ((scenstemp = Searchscens(scensname,0)) == NULL)
	{
		return -1;  //the scensname is not exist
	}
	else
	{
		//add dev in the scenraios at the last
		current = scenstemp->devhead;
		while(current->next != NULL)
		{
			current = current->next;//current is the frist one in the list
			
			if((strncmp(current->rmname,rmname,20) == 0) && (strncmp(current->transname,transname,20) == 0))
			{
				//the dev is already exist
				return 1;  
			}
		}

		//creat new devinscens listNode
		
		newdev = (struct devinscens*)calloc(1,sizeof(struct devinscens));
		
		strncpy(newdev->rmname,rmname,20);
		strncpy(newdev->transname,transname,20);
		strncpy(newdev->transimage,transimage,20);
		//newdev->cmd = cmd;

		//add new dev in scenraios
		current->next = newdev;  //current is the last Node
		newdev->next = NULL;

		return 0;
	}
}

/*Deldevinscens:删除情景组中的设备*/
int Deldevinscens(char *scensname,char *rmname,char *transname)
{
	struct Scenarios *scenstemp;
	struct devinscens *precious,*current;

	if ((scenstemp = Searchscens(scensname,0)) == NULL)
	{
		return -1;  //the scensname is not exist
	}
	else
	{
		precious = scenstemp->devhead;
		current = precious->next;  //current is the frist Node
		while(current != NULL)
		{
			if((strncmp(current->rmname,rmname,20) == 0) && (strncmp(current->transname,transname,20) == 0))
			{
				//find the dev
				break; 
			}

			precious = current;
			current = current->next;//current is the frist one in the list
		}
		if(current == NULL)
		{
			//the dev is not exist
			return -1;
		}

		//del the dev
		precious->next = current->next;
		free(current);
		return 0;
	}
}

//Searchdevinscens:查询情景组中特定房间的遥控器(此房间可能未加入到情景组中)
//key=1 表示查找已添加的设备，key=0 表示查找未添加的设备
char *Searchdevinscens(char *scensname,char *rmname,int key)
{
	struct Scenarios *scenstemp; 
	struct devinscens *devtemp;
	struct room *rmtemp;
	struct transmiter *transtemp,*current;
	char data[80]; //{'trasname':%s,'trasimage':%s}
	static char bufin[512] ;
	static char bufnotin[512];
	int temp = 0; //temp  标志rmname房间是否在情景组中

	strzero(bufin);
	strzero(bufnotin);

	scenstemp = Searchscens(scensname,0); //scenstemp is the scenslist's head
	devtemp = scenstemp->devhead;   //devtemp is the devinscenslist's head

	//1) 当情景组中没添加任何设备时，rmname房间中的遥控器均为未添加的
	//当rmname房间没添加任何设备时，返回空
	//但rmname房间有设备时，均为未添加的
	if(devtemp->next == NULL)
	{
		rmtemp = Searchroom(rmname,0); //rmname 房间肯定存在房间链表中
		transtemp = rmtemp->transhead; //transtemp 是rnmane房间遥控器链表头
	
		if(transtemp->next == NULL)
		{
			//当rmname 房间中没添加任何设备时，返回空
			return NULL;
		}
		else
		{
			//rmname 房间中的遥控器都是未添加到情景组的
			transtemp = transtemp->next; //transtemp 是遥控器链表的第一个节点
			while(transtemp != NULL)
			{
				strzero(data);
				sprintf(data,"{'trasname':'%s','trasimage':'%s'},",transtemp->name,transtemp->image);
				strcat(bufnotin,data);
				transtemp = transtemp->next;//居然忘了这一行，悲剧啊!!!!
			}
		}
	}
	else //2)当情景组已添加设备时
	{
		//先判断rmname房间是否在此情景组中
		while(devtemp->next != NULL) //遍历情景组中的设备
		{
			devtemp = devtemp->next;
			//当rmname房间在情景组中时，说明此房间有遥控器添加到情景组中
			//然后查找此房间的遥控器链表，确定已添加到情景组中的遥控器
			//最后设置此遥控器的scenstate=1，表明已添加到情景组，方便后面操作
			if(strncmp(devtemp->rmname,rmname,20) == 0) 
			{
				temp = 1; 
				// 在遥控器链表中查找情景组中已添加的设备
				transtemp = Searchtransmiter(rmname, devtemp->transname, 0);
			
				//设scenstate=1，表明此设备已添加到情景组
				transtemp->scenstate = 1;
			}
		}
		//temp = 0 rmname房间 不存在此情景组中
		//1)当rmname中没添加任何遥控器时，返回为空
		//2)当rmname中添加了遥控器时，遥控器均为未添加到情景组的
		if(temp == 0) 
		{
			rmtemp = Searchroom(rmname,0); //rmname房间一定存在房间链表
			transtemp = rmtemp->transhead; //transtemp 是rnmane房间遥控器链表头
	
			if(transtemp->next == NULL)
			{
				//当rmname 房间中没添加任何设备时，返回空
				return NULL;
			}
			else
			{
				//rmname 房间中的遥控器都是未添加到情景组的
				transtemp = transtemp->next; //transtemp 是遥控器链表的第一个节点
				while(transtemp != NULL)
				{
					strzero(data);
					sprintf(data,"{'trasname':'%s','trasimage':'%s'},",transtemp->name,transtemp->image);
					strcat(bufnotin,data);
					transtemp = transtemp->next;
				}
			}
		}
		else //temp = 1 rmname 房间存在此情景组中
		{
			//查找 rmname 的房间节点
			rmtemp = Searchroom(rmname,0);
			
			//遍历此房间的设备链表，current为链表头 ,
			//根据scenstate，分离已添加到和未添加到情景组的设备
			//分离后，scenstate的值恢复到默认值 0
			current = rmtemp->transhead; //current 为链表头 
			while(current->next != NULL)
			{
				current = current->next;
				strzero(data);
				sprintf(data,"{'trasname':'%s','trasimage':'%s'},",current->name,current->image);

				if(current->scenstate == 1)
				{
					strcat(bufin,data);
					current->scenstate = 0;
				}	
				else
				{
					strcat(bufnotin,data);
				}
			}			
		}
	}

	if(key == 1)  //查询情景组中已添加的设备
	{
		return bufin;
	}
	else  //key == 0 查询情景组中未添加的设备
	{
		return bufnotin;
	}
}


