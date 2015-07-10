#include "main.h"

extern struct room *rmhead;
extern struct Scenarios *scenshead;

int main(int argc, char **argv)
{
   // FCGI_middle fcgi_middle = FCGI_middle();

    int action;
    int rmID, transID, cmd,get_time;
	int ret,nums; //nums 总数
	int rdroom,rdtransmiter,rdscens;     //readroom
	char rmname[20],transname[20],workday[20];
	char rmimage[20],transimage[20];
	char newname[20],newimage[20];
	char scensname[20];
	int state,rdchannel; //state 遥控器状态，rdchannel(0~15) 遥控器通道
	char hour[4],min[4]; //hour minute 遥控器设定时间
    char *pOutput = NULL; 
	char *timestr; //localtime 时间信息
	char *bufstr; //bufstr 情景组中特定房间遥控器信息
	char data[20];
	char transdata[100];
	int times;  //查询次数
	int count = 0;
	int exetime; //情景组延时执行时间

	/*room's linklist init*/
	if((rmhead = Initroom()) == NULL)
	{
		//printf("Init error\n");
		exit(1);
	}

	/*scenraios's linklist init*/
	if((scenshead = InitScenarios()) == NULL)
	{
		//printf("Init error\n");
		exit(1);
	}
	
	//demoHome();//init room
	
    while(FCGI_Accept() >= 0)
    {
		//cgi init
        cgi_init();
        cgi_process_form();
        if((cgi_param("action") == NULL) ||
                (sscanf(cgi_param("action"), "%d", &action) != 1))
        {
            puts("0");
            cgi_end();
            continue;
        }
		printf("Content_type:text/html\r\n"); //头一定要加
        printf("\r\n");		
		//printf("action=%d",action);	
		//printf("rmhead %x\n",rmhead);
		count++;
        //0-99调试
        switch(action)
        {
        case 0:
			printf("FastCGI hello!");
			printf("count=%d ",count);
			printf("rmhead:%x",rmhead);
            break;

        case 100:  //delete room
			if((cgi_param("roomname") != NULL) &&
				(sscanf(cgi_param("roomname"), "%s", rmname) == 1) )	
            {
            	//printf("action=%d,roomname=%s  ",action,rmname);
				//printf("rmhead:%x count=%d ",rmhead,count);
               ret = Delroom(rmname);
			  if(ret == -1)
			   {
					pOutput = "0";
			   }
			   else
			   {
					pOutput = "1";
			   }
            }		
			puts(pOutput);
            break;
			
        case 101://add room
			if((cgi_param("roomname") != NULL) &&
					(cgi_param("roomimage") != NULL) &&
					(sscanf(cgi_param("roomname"), "%s", rmname) == 1) &&
					(sscanf(cgi_param("roomimage"), "%s", rmimage) == 1) )
            {

               ret = Addroom(rmname,rmimage);		       			
				
			   if(ret == -1)  // fail to add room
			   {
					pOutput = "0";
			   }
			   else if(ret == 1) //the name room is already exist
			  	{
					pOutput = "2";
			   	}
			   else    //ret == 0  add room sucess
			   {
					pOutput = "1";
			   }
            }
			puts(pOutput);
            break;
			
		case 110:  //read all rooms num
			if((cgi_param("readroom") != NULL) &&
			   (sscanf(cgi_param("readroom"), "%d", &rdroom) == 1))
			{
				if(rdroom == 1)
				{
					nums = Searchroomnums();
					sprintf(data,"number=%d",nums);
					puts(data);	
					nums = 0;
				}
				else
				{
					puts("0");
				}
			}
			break;

		case 111:  //read all room's simple information
			if((cgi_param("readroom") != NULL) &&
				(cgi_param("time") != NULL) &&
			   (sscanf(cgi_param("readroom"), "%d", &rdroom) == 1) &&
			   (sscanf(cgi_param("time"), "%d", &times) == 1))
            {
               if(rdroom == 0)
               {
					struct room *temp;
					temp = Searchroom(NULL,times);
					if(temp != NULL)
					{
						sprintf(data,"roomname=%s&roomimage=%s",
										temp->name,temp->image);
						puts(data);
					}
					else
					{
						puts("0");
					}
			   }
			   else
			   {
			   		puts("0");
				 //printf("rdroom one room's information error");
			   }
            }			
			break;
			
        case 120://change room's information(newrmname and newrmimage)
			if((cgi_param("roomname") != NULL) &&
				(cgi_param("newroomname") != NULL) &&
					(cgi_param("newroomimage") != NULL) &&
					(sscanf(cgi_param("roomname"), "%s", rmname) == 1) &&
					(sscanf(cgi_param("newroomname"), "%s", newname) == 1) &&
					(sscanf(cgi_param("newroomimage"), "%s", newimage) == 1) )
            {
               ret = Changeroominfo(rmname, newname, newimage);		
				
			   if(ret == -1)
			   {
					pOutput = "0"; //fail to change room's information
			   }
			   else if(ret == 1)
			   {
					pOutput = "2"; //the newroomname is already exist
			   }
			   else  //ret == 0
			   {
					pOutput = "1"; //change room's info success
			   }
            }
			puts(pOutput);
			strzero(newname);
			strzero(newimage);
            break;	
			
		case 200:   //delete transmiter
			if((cgi_param("trasname") != NULL) &&
				(cgi_param("roomname") != NULL) &&
				(sscanf(cgi_param("trasname"), "%s", transname) == 1) &&
				(sscanf(cgi_param("roomname"), "%s", rmname) == 1) )
            {
               ret = Deltransmiter(rmname,transname);
	
			   if(ret == -1)
			   {
					pOutput = "0";
			   }
			   else
			   {
					pOutput = "1";
			   }
            }
			puts(pOutput);
            break;
			
		case 201: //add transmiter
			if((cgi_param("roomname") != NULL) &&
				(cgi_param("trasname") != NULL) &&
				(cgi_param("trasimage") != NULL) &&
				(sscanf(cgi_param("roomname"), "%s", rmname) == 1) &&
				(sscanf(cgi_param("trasname"), "%s", transname) == 1) &&
				(sscanf(cgi_param("trasimage"), "%s", transimage) == 1))
            {
              	ret = Addtransmiter(rmname,transname,transimage);
		       		
			   if(ret == -1)
			   {
					pOutput = "0"; //fail to add transmitter
			   }
			   else if(ret == 1)
			   {
					pOutput = "2"; //the name transmitter is already exist
			   }
			   else  //ret == 0
			   {
					pOutput = "1";//add sucess
			   }
            }
			puts(pOutput);	
			break;

		case 202: //save transmitter's channel value
			if((cgi_param("roomname") != NULL) &&
				(cgi_param("trasname") != NULL) &&
				(cgi_param("channel") != NULL) &&
				(cgi_param("hour") != NULL) &&
				(cgi_param("minute") != NULL) &&
				(cgi_param("workday") != NULL) &&
				(cgi_param("state") != NULL) &&
				(sscanf(cgi_param("roomname"), "%s", rmname) == 1) &&
				(sscanf(cgi_param("trasname"), "%s", transname) == 1) &&
				(sscanf(cgi_param("channel"), "%d", &rdchannel) == 1) &&
				(sscanf(cgi_param("hour"), "%s", hour) == 1) &&
				(sscanf(cgi_param("minute"), "%s", min) == 1) &&
				(sscanf(cgi_param("workday"), "%s", workday) == 1) &&
				(sscanf(cgi_param("state"), "%d", &state) == 1))
            {
				struct transvalues temp;
				strzero(&temp);
				
				//init temp;
				strncpy(temp.hour,hour,4);
				strncpy(temp.minute,min,4);
				strncpy(temp.workday,workday,20);
				temp.state = state;
				
              	ret = Savetransvalue(rmname,transname,rdchannel,&temp);
		       		
			   if(ret == -1)
			   {
					pOutput = "0"; //fail to save channel's value
			   }
			   else  //ret == 0
			   {
					pOutput = "1";//save success
			   }
            }
			puts(pOutput);	
			break;
			
		case 210:// 查询单个房间遥控器总数
			if((cgi_param("readtransmitter") != NULL) &&
				(cgi_param("roomname") != NULL) &&
			   (sscanf(cgi_param("readtransmitter"), "%d", &rdtransmiter) == 1) &&
			   (sscanf(cgi_param("roomname"), "%s", rmname) == 1))
			{
				//printf("readroom=%d",rdroom);
				if(rdtransmiter == 1)
				{
					nums = Searchtransnums(rmname);
					sprintf(data,"number=%d",nums);
					puts(data);	
					nums = 0;
				}
				else
				{
					//printf("rdroom all room's num error\n");
					puts("0");
				}
			}
			break;
			
		case 211: //read one room's transmiter's simple information
			if((cgi_param("readtransmitter") != NULL) &&
				(cgi_param("roomname") != NULL) &&
				(cgi_param("time") != NULL) &&
			   (sscanf(cgi_param("readtransmitter"), "%d", &rdtransmiter) == 1) &&
			   (sscanf(cgi_param("roomname"), "%s", rmname) == 1) &&
			   (sscanf(cgi_param("time"), "%d", &times) == 1))
			{
               if(rdtransmiter == 0)
               {
					struct transmiter *temp;	
				
					if((temp = Searchtransmiter(rmname, NULL,times)) != NULL)
					{
						sprintf(data,"trasname=%s&trasimage=%s",
									temp->name,temp->image);
						puts(data);
					}
					else
					{
						puts("0");
					}	
			   }
			   else
			   	{
					puts("0");
			   	}
			}
			break;
			
		case 212: //read one transmiter's all information
			if((cgi_param("readtransmitter") != NULL) &&
				(cgi_param("roomname") != NULL) &&
				(cgi_param("trasname") != NULL) &&
				(cgi_param("channel") != NULL) &&
			   (sscanf(cgi_param("readtransmitter"), "%d", &rdtransmiter) == 1) &&
			   (sscanf(cgi_param("roomname"), "%s", rmname) == 1) &&
			   (sscanf(cgi_param("trasname"), "%s", transname) == 1) &&
			   (sscanf(cgi_param("channel"), "%d", &rdchannel) == 1))
            {
            	//printf("roomname=%s transname=%s channel=%d",
						//rmname,transname,rdchannel);
               if(rdtransmiter == 2)
               {
					struct transvalues *temp;
					temp = Searchtransvalue(rmname,transname,rdchannel);
					if(temp != NULL)
					{
						strzero(transdata);
						sprintf(transdata,"hour=%s&minute=%s&workday=%s&state=%d",
								temp->hour,temp->minute,temp->workday,temp->state);
						puts(transdata);
					}
					else
					{
						puts("3");
					}	
			   }
			   else
			   {
			   		puts("0");
			   }
            }			
			break;
			
        case 220://change transmiter's information(newtransname and newtransimage)
			if((cgi_param("roomname") != NULL) &&
				(cgi_param("trasname") != NULL) &&
				(cgi_param("newtrasname") != NULL) &&
				(cgi_param("newtrasimage") != NULL) &&
				(sscanf(cgi_param("roomname"), "%s", rmname) == 1) &&
				(sscanf(cgi_param("trasname"), "%s", transname) == 1) &&
				(sscanf(cgi_param("newtrasname"), "%s", newname) == 1) &&
				(sscanf(cgi_param("newtrasimage"), "%s", newimage) == 1) )
            {

               ret = Changetransmiterinfo(rmname, transname,newname,newimage);
		       		
				//printf("transname=%s&transimage=%s",newtransname,newtransimage);		
				
			   if(ret == -1)
			   {
					pOutput = "0"; //fail to change information
			   }
			   else if(ret == 1) 
			   {
					pOutput = "2"; //the new name transmitter is already exist
			   }
			   else  //ret == 0
			   {
					pOutput = "1"; //sucess
			   }
            }
			
			puts(pOutput);
			strzero(newname);
			strzero(newimage);
            break;
 
         case 500:  //get system's time
			if((cgi_param("get_time") != NULL) &&
			   (sscanf(cgi_param("get_time"), "%d", &get_time) == 1))
			{
				if(get_time == 1)
				{
					timestr = getTime();
					puts(timestr);
				}
				else
				{
					puts("0");
				}
			}
			break; 
			
        case 600:  //delete scenraios
			if((cgi_param("groupname") != NULL) &&
				(sscanf(cgi_param("groupname"), "%s", scensname) == 1))	
            {
            	//printf("action=%d,roomname=%s  ",action,rmname);
				//printf("rmhead:%x count=%d ",rmhead,count);
              ret = DelScenarios(scensname);
				
			  if(ret == -1)
			   {
					pOutput = "0";
			   }
			   else
			   {
					pOutput = "1";
			   }
            }		
			puts(pOutput);
            break;	
			
        case 601://add scenraios
			if((cgi_param("groupname") != NULL) &&
				(sscanf(cgi_param("groupname"), "%s", scensname) == 1))	 
            {
               ret = AddScenarios(scensname);		       			
				
			   if(ret == -1)  // fail to add scenraios
			   {
					pOutput = "0";
			   }
			   else if(ret == 1) //the name scenraios is already exist
			  	{
					pOutput = "2";
			   	}
			   else    //ret == 0  add scenraios sucess
			   {
					pOutput = "1";
			   }
            }
			puts(pOutput);
            break;

		case 610:  //read all scenraios's num
			if((cgi_param("read_group") != NULL) &&
			   (sscanf(cgi_param("read_group"), "%d", &rdscens) == 1))
			{
				if(rdscens == 0)
				{
					nums = Searchscensnums();
					sprintf(data,"number=%d",nums);
					puts(data);	
					nums = 0;
				}
				else
				{
					puts("0");
				}
			}
			break;	

		case 611:  //read all scensraios's simple information
			if((cgi_param("read_group") != NULL) &&
				(cgi_param("time") != NULL) &&
			   (sscanf(cgi_param("read_group"), "%d", &rdscens) == 1) &&
			   (sscanf(cgi_param("time"), "%d", &times) == 1))
            {
               if(rdscens == 1)
               {
					struct Scenarios *temp;
					temp = Searchscens(NULL,times);
					if(temp != NULL)
					{
						sprintf(data,"groupname=%s",temp->name);
						puts(data);
					}
					else
					{
						puts("0");
					}
			   }
			   else
			   {
			   		puts("0");
				 //printf("rdscens one scenraios's information error");
			   }

            }			
			break;
			
        case 620://change scenraios's information(newscensname)
			if((cgi_param("groupname") != NULL) &&
				(cgi_param("newgroupname") != NULL) &&
					(sscanf(cgi_param("groupname"), "%s", scensname) == 1) &&
					(sscanf(cgi_param("newgroupname"), "%s", newname) == 1))	 
            {
               ret = Changescensinfo(scensname,newname);
		       		
				//printf("rooname=%s&roomimage=%s",newrmname,newrmimage);		
				
			   if(ret == -1)
			   {
					pOutput = "0"; //fail to change scenraios's information
			   }
			   else if(ret == 1)
			   {
					pOutput = "2"; //the newname is already exist
			   }
			   else  //ret == 0
			   {
					pOutput = "1"; //change scenraios's info success
			   }
            }
			puts(pOutput);
			strzero(newname);
            break;

		case 700:   //delete dev in the scenraios
			if((cgi_param("trasname") != NULL) &&
				(cgi_param("roomname") != NULL) &&
				(cgi_param("groupname") != NULL) &&
				(sscanf(cgi_param("trasname"), "%s", transname) == 1) &&
				(sscanf(cgi_param("roomname"), "%s", rmname) == 1) &&
				(sscanf(cgi_param("groupname"), "%s", scensname) == 1))
            {

               ret = Deldevinscens(scensname,rmname,transname);
			  // printf("rooname=%s&roomimage=%s",rmname,rmimage);		
			   if(ret == -1)
			   {
					pOutput = "0";
			   }
			   else
			   {
					pOutput = "1";
			   }
            }
			puts(pOutput);
            break;
			
		case 701: //add dev in the scenraios
			if((cgi_param("trasname") != NULL) &&
				(cgi_param("trasimage") != NULL) &&
				(cgi_param("roomname") != NULL) &&
				(cgi_param("groupname") != NULL) &&
				(sscanf(cgi_param("trasname"), "%s", transname) == 1) &&
				(sscanf(cgi_param("trasimage"), "%s", transimage) == 1) &&
				(sscanf(cgi_param("roomname"), "%s", rmname) == 1) &&
				(sscanf(cgi_param("groupname"), "%s", scensname) == 1))
            {
               // sprintf(sdata,"roomname=%s&trasname=%s",rmname,transname);
              	ret = ADDdevinscens(scensname,rmname,transname,transimage);
		       		
			   if(ret == -1)
			   {
					pOutput = "0"; //fail to add transmitter
			   }
			   else if(ret == 1)
			   {
					pOutput = "2"; //the name transmitter is already exist
			   }
			   else  //ret == 0
			   {
					pOutput = "1";//add sucess
			   }
            }
			puts(pOutput);	
			break;

		case 730:   //search room's devs that have been in the scenraios
			if((cgi_param("roomname") != NULL) &&
				(cgi_param("groupname") != NULL) &&
				(sscanf(cgi_param("roomname"), "%s", rmname) == 1) &&
				(sscanf(cgi_param("groupname"), "%s", scensname) == 1)) 	
            {
				bufstr = Searchdevinscens(scensname,rmname,1);
				puts(bufstr); //bufstr=NULL 表示空字符串
				//printf("rmname=%s groupname=%s",rmname,scensname);
			}
			
			//puts("1");
            break;

		case 731:   //search room's devs that are not in the scenraios
			if((cgi_param("roomname") != NULL) &&
				(cgi_param("groupname") != NULL) &&
				(sscanf(cgi_param("roomname"), "%s", rmname) == 1) &&
				(sscanf(cgi_param("groupname"), "%s", scensname) == 1)) 	
            {
				bufstr = Searchdevinscens(scensname,rmname,0);
				puts(bufstr); //bufstr=NULL 表示空字符串
			}
            break;
		
		case 740:   //search room's devs that are not in the scenraios
			if((cgi_param("groupname") != NULL) &&
				(cgi_param("time") != NULL) &&
				(sscanf(cgi_param("groupname"), "%s", scensname) == 1) &&
				(sscanf(cgi_param("time"), "%d", &exetime) == 1)) 	
            {
				struct Scenarios *temp;
				temp = Searchscens(scensname, 0);
			   if(temp == NULL)
			   {
					pOutput = "0";
			   }
			   else
			   {
			   		temp->exetime = exetime; //保存前端发送的情景组延时执行时间
					pOutput = "1";
			   }
			}
			puts(pOutput);
            break;

       /* case 800://单个设备发送命令
            if((cgi_param("roomname") != NULL) &&
				(cgi_param("trasname") != NULL) &&
                    (cgi_param("cmd") != NULL) &&
                    (sscanf(cgi_param("roomname"), "%s", rmname) == 1) &&
                    (sscanf(cgi_param("trasname"), "%s", transname) == 1) &&
                    (sscanf(cgi_param("cmd"), "%d", &cmd) == 1))
            {
            	struct room *rmtemp;
				struct transmiter * transtemp;
				//get rmID and transID
				rmtemp = Searchroom(rmname);
				transtemp = Searchtransmiter(rmname,transname);
				rmID = rmtemp->ID;
				transID = transtemp->ID;
				printf("rmid:%d,transId:%d\n",rmID,transID);
                pOutput = fcgi_middle.SendCmd(rmID,transID,cmd);
				puts(pOutput);
            }
            break;*/

        default:
            break;
        }

        cgi_end();
    }

	free(rmhead);
	free(scenshead);
    return 0;
}


