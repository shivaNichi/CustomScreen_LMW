#include "vxWorks.h"
#include <stdio.h>
#include "aplc.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "string.h"
#include <time.h>


struct Date 
{ 
    int d, m, y; 
}; 

extern void setUserBaseIni(unsigned long);
extern void setUserBaseMain(unsigned long);
extern void setUserPlcIni(unsigned long);
extern void setUserPlcPreMain(unsigned long);

extern void aplc_top();
extern void base_Init();
extern void base_Main();
extern void plcM_Init();
extern void plcM_Main();

extern long getNCData();
extern long setNCData();
extern long melplcWsetR();

 int countLeapYears(struct Date d);
 int getDifference(struct Date dt1,struct Date dt2); 
 void RestoreMtbData( );

#define	ADR_BASE_SYSTEM 0x1
#define	T_CHAR			0x1
#define	T_SHORT			0x2
#define	T_LONG			0x3
#define	T_DLONG			0x4
#define	T_DOUBLE		0x5
#define	PLC_WINDOW		0x1
#define CUSTOM_API		0x3

long	crnt;
long	last;


  
// To store number of days in all months from January to Dec. 
const int monthDays[12] = {31, 28, 31, 30, 31, 30, 
                           31, 31, 30, 31, 30, 31}; 
void aplc_top()
{
    setUserBaseIni(base_Init);
    setUserBaseMain(base_Main);
    setUserPlcIni(plcM_Init);
    setUserPlcPreMain(plcM_Main);

    return ;
}


void base_Init( void )
{
	/* set  Åg-1010Åh to open parameter1#29001 & #29896  	*/
	/* set  Åg-1.234Åh to open parametar2 #29901 & #29996 	*/
	/* set  ÅgBND-1003W400-A0BÅh to APLC version 	*/

	//long	a = -1010;
	//double	b = -1.234;

	///* setNCData(setNCData(Section, Sub-section, Part system number, Axis number,
	//						Base/Cross, Data type, Source ID, Read/Write data buffer address); */
	//setNCData(111, 1, 0, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &a);		/* set #29001 */
	//setNCData(112, 1, 0, 0, ADR_BASE_SYSTEM, T_DOUBLE, CUSTOM_API, &b);		/* set #29901 */
	//getNCData(111, 1, 0, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &a);		/* get #29001 */
	//getNCData(112, 1, 0, 0, ADR_BASE_SYSTEM, T_DOUBLE, CUSTOM_API, &b);		/* get #29901 */
	//setNCData(111, 896, 0, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &a);		/* set #29896 */
	//setNCData(112, 96, 0, 0, ADR_BASE_SYSTEM, T_DOUBLE, CUSTOM_API, &b);	/* set #29996 */
	///* set APLC version */
	//melplcWsetR(243, 0xFF42); /* '(empty colum)''B' */
	//melplcWsetR(242, 0x3041); /* '0''A' */
	//melplcWsetR(241, 0x0190); /* 0400 */
	//melplcWsetR(240, 0x03EB); /* 1003 */
}


void base_Main( void )
{
	/* set  Ågmovement amount of X-axis of 7.1msecÅh to open parameter1 #29002 	*/

	long    lPowerTime=0,lSetTime=0,i=0,lRuntime=0,lRemainTime=0,
		lData=0,mnslRuntime=0,mnslPowerTime=0,lPowerOnDate=0,lRunDate=0;
	struct Date dates[2];
	long TotalSetTime=0,TotalRemainTime=0,lPercentValue=0,tempUnit=0;
	int nUnit[10],j=0,temp=0,nNoofDays=0;
	long bFlagbit[4]={0,0,0,0};
	long lCheckstatus=0;

	for(j=0;j<10;j++)
		nUnit[j]=30;
	nUnit[0]=5,nUnit[1]=5,nUnit[8]=60;

	/* setNCData(setNCData(Section, Sub-section, Part system number, Axis number,
							Base/Cross, Data type, Source ID, Read/Write data buffer address); */
	/* get machine position counter of X-axis  ,  set  movement amount of X-axis  */
	//getNCData(37, 2, 1, 1, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &crnt);		/* get machine pos. counter */

	//data = crnt - last;

	getNCData(40, 7, 0, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lRuntime);
	lRuntime=lRuntime/100;
	mnslRuntime=(lRuntime/100)*60+lRuntime%100;

	getNCData(40, 6, 0, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lRunDate);
for(i=0;i<9;i++)
{
	getNCData(111, i+40, 1, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lPowerOnDate);


		if(lPowerOnDate>0)
		{
		dates[1].y=lPowerOnDate/10000;
		dates[1].m=(lPowerOnDate%10000)/100;
		dates[1].d=lPowerOnDate%100;
		
		dates[0].y=lRunDate/10000;
		dates[0].m=(lRunDate%10000)/100;
		dates[0].d=lRunDate%100;



		 nNoofDays=getDifference(dates[0],dates[1]);
		nNoofDays=nNoofDays*(24*60);
		}
		else
		nNoofDays=0;



	getNCData(111, i+1, 1, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lPowerTime);
	mnslPowerTime=((lPowerTime/100)*60)+lPowerTime%100;

	lRemainTime=mnslPowerTime+nNoofDays-mnslRuntime;
	if(lRemainTime<0)
		lRemainTime=0;
	getNCData(111, i+10, 1, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lSetTime);
	lSetTime=lSetTime*60;

	if(lSetTime==0)
	{
	lData=0;
	lPercentValue=0;
	lCheckstatus=0;
	}
	else
	{
		if(lSetTime!=0&&lRemainTime!=0)
		{
		TotalSetTime=TotalSetTime+lSetTime;
		TotalRemainTime=TotalRemainTime+lRemainTime;
		lData=1;
		lCheckstatus=1;
		}
	
	/* if((((lRemainTime/lSetTime)*100)>90)||lRemainTime==0)*/
		if(lRemainTime==0)
		{
		lCheckstatus=3;
		lData=3;
		lPercentValue=600;
		}
		else if(((lSetTime-lRemainTime)*100/lSetTime)>75)
		{
		lCheckstatus=2;
		lData=2;
		lPercentValue=(lSetTime-lRemainTime);
		temp=lSetTime/nUnit[i];
		 tempUnit=temp-1-(lRemainTime/nUnit[i]);

		lPercentValue= tempUnit*(600.0/temp);
		}
		else if(((lSetTime-lRemainTime)*100/lSetTime)<75)
		{
		
		lPercentValue=(lSetTime-lRemainTime);
		temp=lSetTime/nUnit[i];
		 tempUnit=temp-1-(lRemainTime/nUnit[i]);

		lPercentValue= tempUnit*(600.0/temp);
		if(((lSetTime-lRemainTime)*100/lSetTime)>=50)
			lCheckstatus=1;
		else
			lCheckstatus=0;


		}
	}
	
		
	setNCData(111, 20+i, 1, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lData);	/* set #20 */
	setNCData(55, 528600+i, 0, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lPercentValue);	/* set #R28600 */
	
	bFlagbit[0]=0;bFlagbit[1]=0;bFlagbit[2]=0;bFlagbit[3]=0;
	bFlagbit[lCheckstatus]=1;
	setNCData(53, 25010+i*3, 0, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &bFlagbit[1]);	/* set MBITS */
	setNCData(53, 25011+i*3, 0, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &bFlagbit[2]);
	setNCData(53, 25012+i*3, 0, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &bFlagbit[3]);
	


}
	if(TotalSetTime!=0)
	{
	lData=(TotalSetTime-TotalRemainTime)*100/TotalSetTime;
	setNCData(111, 30, 1, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lData);
	}

	RestoreMtbData( );
}

void plcM_Init( void )
{
	;
}

void plcM_Main( void )
{
	;
}
int countLeapYears(struct Date d) 
{ 
    int years = d.y; 
  
    // Check if the current year needs to be considered 
    // for the count of leap years or not 
    if (d.m <= 2) 
        years--; 
  
    // An year is a leap year if it is a multiple of 4, 
    // multiple of 400 and not a multiple of 100. 
    return years / 4 - years / 100 + years / 400; 
} 
  
// This function returns number of days between two given 
// dates 
int getDifference(struct Date dt1,struct Date dt2) 
{ 
    // COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt1' 
  
    // initialize count using years and day 
	 long int n2=0;
    long int n1 = dt1.y*365 + dt1.d; 
	int i=0;
  
    // Add days for months in given date 
    for ( i=0; i<dt1.m - 1; i++) 
        n1 += monthDays[i]; 
  
    // Since every leap year is of 366 days, 
    // Add a day for every leap year 
    n1 += countLeapYears(dt1); 
  
    // SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'dt2' 
  
     n2 = dt2.y*365 + dt2.d; 
    for ( i=0; i<dt2.m - 1; i++) 
        n2 += monthDays[i]; 
    n2 += countLeapYears(dt2); 
  
    // return difference between two counts 
    return (n2 - n1); 
} 
void RestoreMtbData( )
{
	int i=0;
	long lData=0, lData1=1,bitdata=0;
	long Adress[13][3]={{97,1,1},{97,5,1},{98,1057,1},{98,1061,1},
						{97,108,1},{97,106,1},{98,1227,1},
						{127,2014,1},{127,2013,1},{127,2014,2},{127,2013,2},{127,2014,3},{127,2013,3}};

	for( i=0;i<13;i++)
	{
		getNCData(55, 528620+i, 0, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lData);

		getNCData(Adress[i][0],Adress[i][1], 0, Adress[i][2], ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lData1);
		if(i==5||i==6)
		{
			if(i==5)
			{
				bitdata=(lData1>>15);
				if(bitdata!=lData)
				{
					if(lData==1)
					{
					lData=lData1|0x8000;
				
					}
					else
					lData=lData1&0x7FFF;
					setNCData(Adress[i][0],Adress[i][1], 0, Adress[i][2], ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lData);

				}
			}

			else
			{
				bitdata=(lData1>>14);
				if(bitdata!=lData)
				{
					if(lData==1)
					{
					lData=lData1|0x4000;
				
					}
					else
					lData=lData1&0xBFFF;
					setNCData(Adress[i][0],Adress[i][1], 0, Adress[i][2], ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lData);

				}
			}

		}
		else
		{
		if(lData!=lData1)
		setNCData(Adress[i][0],Adress[i][1], 0, Adress[i][2], ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lData);
		}
	}




}