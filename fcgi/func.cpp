#include "func.h"

struct room *rmhead; 
struct Scenarios *scenshead;

int rmID[RMMAX] = {0};  //rmID�����е�i��ֵΪ1��˵��iֵ�Ѿ�����ΪID�ţ���֮����û�б�����
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

//ÿһ�� �µ�room�ڵ�����ʱ����Ҫ���˸�room�ڵ��е�transmiter �������ͷ�ڵ�
int Addroom(char *name,char *image)
{
	int i = 0  ;  //i ��ʾ����ID������ID ��0��ʼ
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
	newrm->ID = i;  //����ID��0 ��ʼ

	rmID[i] = 1;
	
	/*add new room*/
	current->next = newrm; //����������current ��list���һ���ڵ�
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

	rmID[current->ID] = 0; //����ɾ����rmID�еĵ�(current->ID)λ Ϊ 0
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
		for(i = 0;i < times;i++) //iֵ�Ĵ�С����ȡ�����е�i���ڵ��ֵ
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

/*Searchallroom:��ѯ��������*/
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
	int i = 0 ;  //i ��ʾң����ID��  ��0��ʼ
	struct room *rmtemp;
	struct transmiter *transnew, *current;
	int j;
	
	//ȷ���˷���ң��������ͷ
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
	transnew->scenstate = 0; //scenstate Ĭ��ֵΪ 0 
	//����channelĬ��ֵ
	
	for(j=0; j<16; j++)
	{
		strcpy(transnew->vv[j].hour,"--:");
		strcpy(transnew->vv[j].minute,"--");
		strcpy(transnew->vv[j].workday,"/--");
		transnew->vv[j].state = 0;
	}
	
	transID[i] = 1;  //���� ID=i ����

	current->next = transnew; //current is the last ,add in the end
	transnew->next = NULL;
	
	return 0;	
}

int Savetransvalue(char *rmname,char *transname,int channel,struct transvalues *temp)
{
	int i = 0 ;  //i ��ʾң����ID��  ��0��ʼ
	struct transmiter *transtemp;

	//ȷ���˷���ң��������ͷ
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

/*��ѯ��������ң��������*/
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

	current = temp->transhead;  //current ң��������ͷ
	while(current->next != NULL)
	{
		num++;
		current = current->next;
	}

	return num;
}

/*��ѯ����ң����*/
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
		for(i = 0;i < times;i++) //times��ʾ����������ڼ����ڵ�
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

//Searchtransvalue:��ѯң�����ض�channel���趨��ֵ
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

//Changeroominfo:�޸ķ�����Ϣ
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

/*demoHome:��������ʼ��ʱ��������������:���� ���� ����*/
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
	return (n - '0' + 48); // 0 �� ASCII �� 48
}

int ctoasc(char c) //char to ascii
{
	if(isdigit(c) == 0) //��������
	{
		c = tolower(c); //���ַ�ת��ΪСд
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

/*InitScenarios:��ʼ���龰��������������ͷ*/
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

/* AddScenarios:����龰�� */
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
	newscens->exetime = -1; //Ĭ��ֵΪ-1����ʾδ�����龰����ʱʱ��
	
	/* add new Scenarios listNode */
	current->next = newscens; //����������current ��list���һ���ڵ�
	newscens->next = NULL;
	newscens->devhead->next = NULL;
	
	return 0;
}

//DelScenarios:ɾ���龰��
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

//Searchallscens:��ѯ�龰������
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

//Searchscens: ��ѯ�龰��
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
		for(i = 0;i < times;i++) //iֵ�Ĵ�С����ȡ�����е�i���ڵ��ֵ
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

//Changescensinfo:�޸��龰��(name)
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

/*ADDdevinscens: ����龰���豸  attention cmd */
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

/*Deldevinscens:ɾ���龰���е��豸*/
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

//Searchdevinscens:��ѯ�龰�����ض������ң����(�˷������δ���뵽�龰����)
//key=1 ��ʾ��������ӵ��豸��key=0 ��ʾ����δ��ӵ��豸
char *Searchdevinscens(char *scensname,char *rmname,int key)
{
	struct Scenarios *scenstemp; 
	struct devinscens *devtemp;
	struct room *rmtemp;
	struct transmiter *transtemp,*current;
	char data[80]; //{'trasname':%s,'trasimage':%s}
	static char bufin[512] ;
	static char bufnotin[512];
	int temp = 0; //temp  ��־rmname�����Ƿ����龰����

	strzero(bufin);
	strzero(bufnotin);

	scenstemp = Searchscens(scensname,0); //scenstemp is the scenslist's head
	devtemp = scenstemp->devhead;   //devtemp is the devinscenslist's head

	//1) ���龰����û����κ��豸ʱ��rmname�����е�ң������Ϊδ��ӵ�
	//��rmname����û����κ��豸ʱ�����ؿ�
	//��rmname�������豸ʱ����Ϊδ��ӵ�
	if(devtemp->next == NULL)
	{
		rmtemp = Searchroom(rmname,0); //rmname ����϶����ڷ���������
		transtemp = rmtemp->transhead; //transtemp ��rnmane����ң��������ͷ
	
		if(transtemp->next == NULL)
		{
			//��rmname ������û����κ��豸ʱ�����ؿ�
			return NULL;
		}
		else
		{
			//rmname �����е�ң��������δ��ӵ��龰���
			transtemp = transtemp->next; //transtemp ��ң��������ĵ�һ���ڵ�
			while(transtemp != NULL)
			{
				strzero(data);
				sprintf(data,"{'trasname':'%s','trasimage':'%s'},",transtemp->name,transtemp->image);
				strcat(bufnotin,data);
				transtemp = transtemp->next;//��Ȼ������һ�У����簡!!!!
			}
		}
	}
	else //2)���龰��������豸ʱ
	{
		//���ж�rmname�����Ƿ��ڴ��龰����
		while(devtemp->next != NULL) //�����龰���е��豸
		{
			devtemp = devtemp->next;
			//��rmname�������龰����ʱ��˵���˷�����ң������ӵ��龰����
			//Ȼ����Ҵ˷����ң��������ȷ������ӵ��龰���е�ң����
			//������ô�ң������scenstate=1����������ӵ��龰�飬����������
			if(strncmp(devtemp->rmname,rmname,20) == 0) 
			{
				temp = 1; 
				// ��ң���������в����龰��������ӵ��豸
				transtemp = Searchtransmiter(rmname, devtemp->transname, 0);
			
				//��scenstate=1���������豸����ӵ��龰��
				transtemp->scenstate = 1;
			}
		}
		//temp = 0 rmname���� �����ڴ��龰����
		//1)��rmname��û����κ�ң����ʱ������Ϊ��
		//2)��rmname�������ң����ʱ��ң������Ϊδ��ӵ��龰���
		if(temp == 0) 
		{
			rmtemp = Searchroom(rmname,0); //rmname����һ�����ڷ�������
			transtemp = rmtemp->transhead; //transtemp ��rnmane����ң��������ͷ
	
			if(transtemp->next == NULL)
			{
				//��rmname ������û����κ��豸ʱ�����ؿ�
				return NULL;
			}
			else
			{
				//rmname �����е�ң��������δ��ӵ��龰���
				transtemp = transtemp->next; //transtemp ��ң��������ĵ�һ���ڵ�
				while(transtemp != NULL)
				{
					strzero(data);
					sprintf(data,"{'trasname':'%s','trasimage':'%s'},",transtemp->name,transtemp->image);
					strcat(bufnotin,data);
					transtemp = transtemp->next;
				}
			}
		}
		else //temp = 1 rmname ������ڴ��龰����
		{
			//���� rmname �ķ���ڵ�
			rmtemp = Searchroom(rmname,0);
			
			//�����˷�����豸����currentΪ����ͷ ,
			//����scenstate����������ӵ���δ��ӵ��龰����豸
			//�����scenstate��ֵ�ָ���Ĭ��ֵ 0
			current = rmtemp->transhead; //current Ϊ����ͷ 
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

	if(key == 1)  //��ѯ�龰��������ӵ��豸
	{
		return bufin;
	}
	else  //key == 0 ��ѯ�龰����δ��ӵ��豸
	{
		return bufnotin;
	}
}


