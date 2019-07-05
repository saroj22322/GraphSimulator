/*Prorammed by HTC for the help during projects*/
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

//Global Variable:
COORD coordinate={0,0};

//Making a full screen console:
void fullscreen()
{
keybd_event(VK_MENU,0x38,0,0);
keybd_event(VK_RETURN,0x1c,0,0);
keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

//Making a gotoxy function:
void gotoxy(int x,int y)
{
    coordinate.X=x;
    coordinate.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinate);
}

//This one is for getting string with whitespace accepted and ignore tab
void get(char ch[])
{
	char c;
	int i=0;
	do
	{
		c=getch();
		if(c==9) continue;
		if (c==8)
		{
			if(i!=0)
			{
				i--;
				printf("\b \b");
			}
			continue;			
		}
		printf("%c",c);
		ch[i]=c;
		i++;
	}while (c!=13);
	ch[i-1]='\0';
	printf("\n");	
}

int is_leap_year(int y)
{
	if (y%4==0) return 1;
	return 0;
}


//This is a menu_maker:
int htc_menumaker(char* list[],int num,int x,int y)// Want 2 arguments : list of heading and menu options,number of elements in list
{
	int x_fix=x,y_initial=y,i,place=1;
    char ch='0';
	for (i=0;i<strlen(list[0]);++i)
		{
			gotoxy(x_fix+i+3,y_initial);printf("\xba");
		}
	gotoxy(x_fix+3,y_initial+1);
	printf("%s",list[0]);
	for (i=0;i<strlen(list[0]);++i)
		{
			gotoxy(x_fix+i+3,y_initial+2);printf("\xba");
		}
	gotoxy(x_fix,y_initial+5);
 	while(1)
	 {
 	 	switch(ch)
		{
	   		case 80: //Code for DOWN arrow equivalent to P
	    	place++;
	    	if (place==num) place=1;
	   		 break;
	   		case 72: //Code for UP arrow quivalent to H
	    	place--;
	   		 if(place<1) place=num-1;
	    	break;
	    	case 27://ASCII code for ESC
	    	place=-1;
	    	ch='\r';
	    	goto forward;
	    	break;
		}
		for (i=1;i<=num-1;++i)
		{
			gotoxy(x_fix-1,y_initial+4+i);printf("  %s",list[i]);
		}
		for (i=1;i<=num-1;++i)
			if (place==i)
			{
				gotoxy(x_fix-1,y_initial+4+i);printf("->%s",list[i]);
				break;
			}
			ch=getch();
			forward:
		if(ch=='\r')
		{
	 		return (place);
		}
	}
}





/*This will make password input secret*/
void htc_password_maker(char inputpass[])
{
	char ch;
    int position = 0;
    do
    {
    	ch=getch();
    	if (ch==13) //ASCII for ENTER
    	{
    		inputpass[position]='\0';
			break;	
		}
		else if(ch==8) //ASCII for BACKSPACE
		{
			if (position>0)
			{
				position--;
				printf("\b \b");
			}
		}
		else if (ch==9||ch==32) //ASCII for TAB and SPACE
		{
			continue;
		}
		else
		{
			inputpass[position]=ch;
			position++;
			printf("*");
		}
	}while(1);
}





/*Note it only check validity for year range 1000-9999 AD*/
int htc_datecheck(char inputdate[]) //ASCII code for 0 is 48
{
	int error=0,day,mnth,year,i;	
	day=(inputdate[0]-48)*10+(inputdate[1]-48);
	mnth=(inputdate[3]-48)*10+(inputdate[4]-48);
	year=(inputdate[6]-48)*1000+(inputdate[7]-48)*100+(inputdate[8]-48)*10+(inputdate[9]-48);
	if(inputdate[2]!='.'||inputdate[5]!='.') error++;
	if (mnth>12) error++;
	if (strlen(inputdate)!=10) error++;
    for(i=0;i<=9;++i)
	{
		if (i==2||i==5)
			continue;
		else if(inputdate[i]<48 || inputdate[i]>57)
			{
				error++;
				break;
			}
	}
	switch(mnth)
	{
		case 1: if(day>31) error++;break;
		case 2: if(day>28) error++;
				if(year%4==0&&day==29) error--;
				break;
		case 3: if(day>31) error++;break;
		case 4: if(day>30) error++;break;
		case 5: if(day>31) error++;break;
		case 6: if(day>30) error++;break;
		case 7: if(day>31) error++;break;
		case 8: if(day>31) error++;break;
		case 9: if(day>30) error++;break;
		case 10: if(day>31) error++;break;
		case 11: if(day>30) error++;break;
		case 12: if(day>31) error++;break;
	}
	return(error); //error is if error>0
}



/* It clears the region in between x1-x2 and y1-y2 */
void htc_fieldclr(int x1,int x2,int y1,int y2)
{
	int i,j;
	for (i=x1;i<=x2;i++)
	for (j=y1;j<=y2;j++)
	{
		gotoxy(i,j);
		printf("%c",32);
	}
}


/*This function input 4 arguments viz. Array of options,
number of options,initial x and y coordinate to start
to print. It makes options and give out index of selected
option in the array.*/
int htc_option(char* options[],int num,int x,int y)
{
	int i=0,maxlen=0,len,half;char ch;
	for(i=0;i<=num-1;i++)
	{
		if(strlen(options[i])>maxlen)
		maxlen=strlen(options[i]);
	}
	i=0;	
	gotoxy(x,y);printf("< ");
	len=maxlen-strlen(options[i]);
	if(len%2==0) 
		half=len/2;
	else
		half=(len+1)/2;
	gotoxy(x+2+half,y);printf("%s",options[i]);gotoxy(x+maxlen+2,y);printf(" >");
	do
	{
		ch=getch();
		if((i==0&&ch==75)||(i==(num-1)&&ch==77))
		continue;
		if(ch==77)
		{
			Beep(400,50);
			i++;
			htc_fieldclr(x,x+maxlen+4,y,y);
			gotoxy(x,y);printf("< ");
			len=maxlen-strlen(options[i]);
			if(len%2==0) 
				half=len/2;
			else
				half=(len+1)/2;
		gotoxy(x+2+half,y);printf("%s",options[i]);gotoxy(x+maxlen+2,y);printf(" >");
		}
		if(ch==75)
		{
			Beep(400,50);
			i--;
			htc_fieldclr(x,x+maxlen+4,y,y);
			gotoxy(x,y);printf("< ");
			len=maxlen-strlen(options[i]);
			if(len%2==0) 
				half=len/2;
			else
				half=(len+1)/2;
			gotoxy(x+2+half,y);printf("%s",options[i]);gotoxy(x+maxlen+2,y);printf(" >");
	 	}
	 	if(ch==13)break;
	}while(1);
	return(i);
}

//This function is used for email address validation
//valid characters: -.@_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789
// structure : xxxx@xxx.xxxx

int htc_emailvalidator(char id[])
{
	int len=strlen(id),i,error=0,count=0,place,place1,count1=0;
	if(id[0]==46) error++;
	for (i=0;i<len;i++)
	{
		if(id[i]==64)
		{
			count1++;
			place1=i;
		}
		if(i!=len-1)
		{
			if((id[i]==46&&id[i+1]==46)||(id[i]==95&&id[i+1]==95)||(id[i]==45&&id[i+1]==45)) error++;
		}
		if(!(id[i]==45||id[i]==46||id[i]==95||id[i]==64))
		{
			if((id[i]<48||id[i]>57)&&(id[i]<65||id[i]>90)&&(id[i]<97||id[i]>122))
			error++;	
		}
	}
	for(i=place1;i<len;i++)
	if(id[i]==46)
		{
			count++;
			place=i;
		}
	if(count1!=1||count!=1) error++;
	if(place1>place) error++;
	return (error);
}


void htc_dayadder(int* cdays,int* cmonths,int* cyears,int days)
{
	int i,check,cday,cmonth,cyear;
	cday=*cdays;
	cmonth=*cmonths;
	cyear=*cyears;
	int monthday[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
					for (i=1;i<=days;i++)
					{
						check=is_leap_year(cyear);
						cday++;
						if(check==1&&cmonth==2)
						{
							if (cday>monthday[cmonth]+1)
							{
								cmonth++;
								cday=1;
							}			
						}
						else
						{
							if (cday>monthday[cmonth])
							{
								cmonth++;
								cday=1;
							}
						}
						if (cmonth>12)
						{
							cyear++;
							cmonth=1;
						}
					}
			*cdays=cday;
			*cmonths=cmonth;
			*cyears=cyear;
}

int htc_daycalculator(int pday,int pmonth,int pyear,int cday,int cmonth,int cyear)
{
int i,check;
int dpyear=0,dpyear1,dcyear=0,dinyears=0,total_days;
int monthday[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
check=is_leap_year(pyear);
for(i=1;i<pmonth;i++)
{
	if(check==1&&i==2)
	{
	dpyear+=29;
	}
	else
	{
		dpyear+=monthday[i];
	}
}
dpyear=dpyear+pday;
dpyear1=(check==1)?366-dpyear:365-dpyear;
//-------------------------------------
check=is_leap_year(cyear);
for(i=1;i<cmonth;i++)
{
	if(check==1&&i==2)
	{
	dcyear+=29;
	}
	else
	{
		dcyear+=monthday[i];
	}
}
dcyear=dcyear+cday;
//----------------------------------------
if(cyear-pyear>1)
{
	for (i=pyear+1;i<cyear;i++)
	{
		check=is_leap_year(i);
		dinyears+=(check==1)?366:365;
	}
}
total_days=dpyear1+dcyear+dinyears;
if (cyear==pyear) total_days=dcyear-dpyear;
return(total_days);
}

