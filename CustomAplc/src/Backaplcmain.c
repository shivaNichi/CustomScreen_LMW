#include "vxWorks.h"
#include "aplc.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "string.h"
#include <time.h>

#define SIZE_BUF	12
//#include "CNcCustomApi.h"
//#include "melncapi.h"
#define VALUE_INVALID			-1

#define DOUBLE_PREC			0x03
#define ADR_BASE_SYSTEM			0x01

#define SYS_NON				0
#define SYS_NUM1			1	

#define PART_SYSTEM			1

#define AXIS_NON				0
#define AXIS_NUM1				1
#define AXIS_NUM2				2
#define AXIS_NUM3				3
#define AXIS_NUM4				4
#define AXIS_NUM5				5
#define AXIS_NUM6				6
#define AXIS_NUM7				7

#define GAPS_TIMES				1

#define SECONDS_OF_1DAY			(24 * 60 * 60)

#define PROG_NAME_BUFF_SIZE		100

typedef struct {
	long	lBuffSize;										
	char	cDataBuff[PROG_NAME_BUFF_SIZE];					
} STRINGTYPE;
/* ################### Global Variables ####################*/


										
long g_lTotalPowerOnTimeStart = 0;									
long g_lTotalRapidTime = 0;									
long g_lTotalToolChangeTime = 0;										
long g_lTotalSpindleRunTime= 0;	
/* ################### Global Variables ####################*/
/* ################### Flags ####################*/
short sCutTimFlg = 0;
short sRapidTimFlg = 0;
short sSpindleTimeFlg = 0;
short sDownTimeResonOldState = 0;
short sDownTimStartFlg= 0;
short sDownTimeStopFlg = 0;

/* ################### Flags ####################*/
extern void setUserBaseIni(unsigned long);
extern void setUserBaseMain(unsigned long);
extern void setUserPlcIni(unsigned long);
extern void setUserPlcPreMain(unsigned long);
long convert (int base, long num);
extern void aplc_top();
extern void base_Init();
extern void base_Main();
extern void plcM_Init();
extern void plcM_Main();

extern long getNCData();
extern long setNCData();
extern long melplcWsetR();

void CycleTimeScreemData();
void DownTimeAnalysis();
unsigned long HourMinSecToSecConvertion(long lTime);
void ShiftAndClearDownTimeData();

#define	ADR_BASE_SYSTEM 0x1
#define	T_CHAR			0x1
#define	T_SHORT			0x2
#define	T_LONG			0x3
#define	T_DLONG			0x4
#define	T_DOUBLE		0x5
#define	PLC_WINDOW		0x1
#define CUSTOM_API		0x3
#define T_STR			0x10

long	crnt;
long	last;


void aplc_top()
{
	setUserBaseIni(base_Init);
    setUserBaseMain(base_Main);
   // setUserPlcIni(plcM_Init);
   // setUserPlcPreMain(plcM_Main);

    return ;
}


void base_Init( void )
{
	/* set  Åg-1010Åh to open parameter1#29001 & #29896  	*/
	/* set  Åg-1.234Åh to open parametar2 #29901 & #29996 	*/
	/* set  ÅgBND-1003W400-A0BÅh to APLC version 	*/

	long	a = -1010;
	double	b = -1.234;
	
	 melplcBrstM(5000);

	/* setNCData(setNCData(Section, Sub-section, Part system number, Axis number,
							Base/Cross, Data type, Source ID, Read/Write data buffer address); */
	setNCData(111, 1, 0, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &a);		/* set #29001 */
	setNCData(112, 1, 0, 0, ADR_BASE_SYSTEM, T_DOUBLE, CUSTOM_API, &b);		/* set #29901 */
	getNCData(111, 1, 0, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &a);		/* get #29001 */
	getNCData(112, 1, 0, 0, ADR_BASE_SYSTEM, T_DOUBLE, CUSTOM_API, &b);		/* get #29901 */
	setNCData(111, 896, 0, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &a);		/* set #29896 */
	setNCData(112, 96, 0, 0, ADR_BASE_SYSTEM, T_DOUBLE, CUSTOM_API, &b);	/* set #29996 */
	/* set APLC version */
	//melplcWsetR(243, 0xFF42); /* '(empty colum)''B' */
	//melplcWsetR(242, 0x3041); /* '0''A' */
	//melplcWsetR(241, 0x0190); /* 0400 */
	//melplcWsetR(240, 0x03EB); /* 1003 */

	 melplcWsetR(243, 0xFF44); /* '(empty colum)''B' */
	 melplcWsetR(242, 0x3041); /* '0''A' */
	 melplcWsetR(241, 0x0001); /* 0400 */
	 melplcWsetR(240, 0x2329); /* 1003 */

	 /* setNCData(setNCData(Section, Sub-section, Part system number, Axis number,
							Base/Cross, Data type, Source ID, Read/Write data buffer address); */	
}


void base_Main( void )
{
	long   data = 0;
	
	/* setNCData(setNCData(Section, Sub-section, Part system number, Axis number,
							Base/Cross, Data type, Source ID, Read/Write data buffer address); */
	/* get machine position counter of X-axis  ,  set  movement amount of X-axis  */
	data = getNCData(37, 2, 1, 1, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &crnt);		/* get machine pos. counter */
	data = crnt - last;
	data = setNCData(111, 2, 0, 0, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &data);	/* set #29002 */
	last = crnt;
	CycleTimeScreemData();
	DownTimeAnalysis();
	
}


void plcM_Init( void )
{
	;
}

void plcM_Main( void )
{
	;
	/* setNCData(setNCData(Section, Sub-section, Part system number, Axis number,
							Base/Cross, Data type, Source ID, Read/Write data buffer address); */
	/* get machine position counter of X-axis  ,  set  movement amount of X-axis  */

//extern long getNCData(long, long, long, long, long, long, long, void *);
//extern long setNCData(long, long, long, long, long, long, long, void *);
}

void CycleTimeScreemData(){
short sXC12 = 0, sXC21=0, sXC20=0, sM3502=0, sM3503=0, sY1898=0, sY1899=0;	
short i;
unsigned long ulTotCycleTimeSec =0;
long lCycleDate = 0, lOldCycleDate=0;
long lCycleTime = 0;									
long lTimeStart=0;
long lTimeStop=0;
long lTotalTime=0;


if(0 == getNCData(40, 6, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lCycleDate))
	lCycleDate = lCycleDate%100;
if(getNCData(111, 11, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lOldCycleDate)==0)
	lOldCycleDate = lOldCycleDate%100;

if(lOldCycleDate != lCycleDate){
	// reset all cycle time related data
	
	setNCData(111, 11, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lCycleDate); // current date
	for(i = 12; i < 21; i++){
	ulTotCycleTimeSec = 0;
	setNCData(111, i, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &ulTotCycleTimeSec);
	}
	

}

	if(getNCData(53, 3091, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sXC12)==0){
		if(sXC12 == 1){
			if(getNCData(40, 8, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lCycleTime)==0){
				ulTotCycleTimeSec = HourMinSecToSecConvertion(lCycleTime);
				//getNCData(111, 12, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lCycleTime); 
				//ulTotCycleTimeSec += lCycleTime;
				setNCData(111, 12, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &ulTotCycleTimeSec); // open param1  29011 total Cycle time
			}
			if(getNCData(53, 3106, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sXC21)==0){
				
				if(sXC21 == 1 && sCutTimFlg == 0){
					sCutTimFlg = 1;
					if(getNCData(40, 8, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lCycleTime)==0){
						lTimeStart =  HourMinSecToSecConvertion(lCycleTime);
						setNCData(111, 13, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTimeStart);
					}
				}else if(sXC21 == 0 && sCutTimFlg == 1){
					if(getNCData(40, 8, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lCycleTime)==0)
						lTimeStop =  HourMinSecToSecConvertion(lCycleTime);
					sCutTimFlg = 0;
					getNCData(111, 13, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTimeStart);
					getNCData(111, 14, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalTime); //  get total Cutting time
					lTotalTime += (lTimeStop - lTimeStart);
					setNCData(111, 14, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalTime); // Set total Cutting time
				}
			}
			if(getNCData(53, 3105, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sXC20)==0){
				if(sXC20 == 1 && sRapidTimFlg == 0){
					sRapidTimFlg = 1;
					if(getNCData(40, 8, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lCycleTime)==0){
						lTimeStart =  HourMinSecToSecConvertion(lCycleTime);
						setNCData(111, 15, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTimeStart);
					}
				}else if(sXC20 == 0 && sRapidTimFlg == 1){
					if(getNCData(40, 8, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lCycleTime)==0)
						lTimeStop =  HourMinSecToSecConvertion(lCycleTime);
					sRapidTimFlg = 0;
					getNCData(111, 15, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTimeStart);
					getNCData(111, 16, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalTime); //  get total Cutting time
					lTotalTime += (lTimeStop - lTimeStart);
					setNCData(111, 16, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalTime); // Set total Cutting time
				}
			}
			
		}
	}
	if(getNCData(53, 23502, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sM3502)==0){
		if(sM3502 == 1 ){
				if(getNCData(40, 8, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lCycleTime)==0){
					lTimeStart =  HourMinSecToSecConvertion(lCycleTime);
					setNCData(111, 17, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTimeStart);
				}
		}
	}
	if(getNCData(53, 23503, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sM3503)==0){
		if(sM3503 == 1 ){
			if(getNCData(40, 8, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lCycleTime)==0)
				lTimeStop =  HourMinSecToSecConvertion(lCycleTime);
				getNCData(111, 17, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTimeStart);
				getNCData(111, 18, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalTime); //  get total Cutting time
				lTotalTime += (lTimeStop - lTimeStart);
				setNCData(111, 18, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalTime); // Set total Cutting time
		}
	}
	if((getNCData(53, 11898, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sY1898)==0) ||
		(getNCData(53, 11899, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sY1899)==0)){
			if((sY1898 ==1 || sY1899 ==1) && sSpindleTimeFlg == 0){
				sSpindleTimeFlg = 1;
				if(getNCData(40, 8, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lCycleTime)==0){
					lTimeStart =  HourMinSecToSecConvertion(lCycleTime);
					setNCData(111, 19, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTimeStart);
				}
			}else if(sY1898 ==0 && sY1899 ==0 && sSpindleTimeFlg == 1){
				sSpindleTimeFlg = 0;
				if(getNCData(40, 8, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lCycleTime)==0)
				lTimeStop =  HourMinSecToSecConvertion(lCycleTime);
				getNCData(111, 19, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTimeStart);
				getNCData(111, 20, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalTime); //  get total Cutting time
				lTotalTime += (lTimeStop - lTimeStart);
				setNCData(111, 20, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalTime); // Set total Cutting time
			}	
	}

}


unsigned long HourMinSecToSecConvertion(long lTime){

	unsigned short sSecond = 0 ;
	unsigned short sMinute = 0 ;
	unsigned short sHour = 0 ;
	unsigned long lTotalSec=0;

	if(lTime > 0){
		sSecond = lTime %100;
		lTime = lTime/100;	
		if(lTime > 0){
			sMinute = lTime %100;
			lTime = lTime/100;
			if(lTime > 0)
				sHour = lTime%1000;
			}
		}		
		lTotalSec = (sHour * 3600)+(sMinute*60)+sSecond;
		return lTotalSec;

}
void DownTimeAnalysis(){
	short sXC12 = 0, sXC13 = 0, sXC10 = 0;
	short sDownTimeReson = 0, i , j;
	short sGetBaseAddr, sSetBaseAddr;
	long lCycleDate = 0, lOldCycleDate=0;
	long lCycleTime = 0, lPowerOnTime = 0;
	long lTotalPowerOnTime = 0;
	long lDownTimeStart = 0;
	long lDownTimeEnd = 0;
	long lTotalDownTime = 0;


	if(0 == getNCData(40, 6, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lCycleDate))
		//lCycleDate = lCycleDate%100;
	if(getNCData(111, 21, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lOldCycleDate)==0)
		//lOldCycleDate = lOldCycleDate%100;

	if(lOldCycleDate != lCycleDate){
		ShiftAndClearDownTimeData();
		setNCData(111, 21, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lCycleDate); // current date
		if(getNCData(40, 1, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, DOUBLE_PREC, &g_lTotalPowerOnTimeStart)==0);
		g_lTotalPowerOnTimeStart = HourMinSecToSecConvertion(g_lTotalPowerOnTimeStart);
		
	}
	
	if(getNCData(53, 3089, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_SHORT, CUSTOM_API, &sXC10)==0)
	if(sXC10 == 1)
	{
		if(getNCData(40, 1, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, DOUBLE_PREC, &lPowerOnTime)==0);
		lTotalPowerOnTime = HourMinSecToSecConvertion(lPowerOnTime);
		lTotalPowerOnTime -= g_lTotalPowerOnTimeStart;
		setNCData(111, 22, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalPowerOnTime);
		
		if(getNCData(53, 3091, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sXC12)==0);
		if(getNCData(53, 3092, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sXC13)==0);
		getNCData(5, 1430, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sDownTimeReson);
		if(sDownTimeResonOldState != sDownTimeReson)
			sDownTimeStopFlg =1;
		
		if(sXC12 == 1 && sXC13 == 0)
		{
			if(sDownTimStartFlg == 1  || sDownTimStartFlg == 0){	
				sDownTimeResonOldState = sDownTimeReson = 1;
				sDownTimeStopFlg= 1;
				sDownTimStartFlg = 2;
				if(getNCData(111, 22, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, DOUBLE_PREC, &lDownTimeStart)==0);
				setNCData(111, (21 + (2*sDownTimeReson)), SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lDownTimeStart);
			}
		
		}
		else if((sXC12 == 0 && sXC13 == 0) &&(sDownTimeReson < 1 && sDownTimeReson > 12) )
		{
			if(sDownTimStartFlg == 1 || sDownTimStartFlg == 0){	
				sDownTimeResonOldState = sDownTimeReson = 3;
				sDownTimeStopFlg= 1;
				sDownTimStartFlg = 2;
				if(getNCData(111, 22, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, DOUBLE_PREC, &lDownTimeStart)==0);
				setNCData(111, (21 + (2*sDownTimeReson)), SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lDownTimeStart);
			}
		
		
		}
		else if(sXC12 == 0)
		{
			getNCData(5, 1430, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sDownTimeReson);
			if(sDownTimeReson >= 2 && sDownTimeReson <= 12 )
			{
				if(sDownTimStartFlg == 1 || sDownTimStartFlg == 0)
				{
					sDownTimeResonOldState = sDownTimeReson;
					
					sDownTimeStopFlg= 1;
					sDownTimStartFlg = 2;
	//				if(getNCData(53, 3088, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &lDownTimeStart)==0)
					if(getNCData(111, 22, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, DOUBLE_PREC, &lDownTimeStart)==0);
					//lDownTimeStart = HourMinSecToSecConvertion(lDownTimeStart);
					setNCData(111, (21 + (2*sDownTimeReson)), SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lDownTimeStart);
					
				}
			}
		
		}
		
		if(sDownTimeStopFlg == 1 && sDownTimStartFlg == 2 ){
			getNCData(111, (22 + (2*sDownTimeResonOldState)), SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalDownTime);
		//	if(getNCData(53, 3088, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &lDownTimeEnd)==0)
			if(getNCData(111, 22, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, DOUBLE_PREC, &lDownTimeEnd)==0);
			//lDownTimeEnd = HourMinSecToSecConvertion(lDownTimeEnd);
			getNCData(111, (21 + (2*sDownTimeResonOldState)), SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lDownTimeStart);
			lDownTimeEnd =  (lDownTimeEnd - lDownTimeStart);
			lTotalDownTime += lDownTimeEnd;
			setNCData(111, (22 + (2*sDownTimeResonOldState)), SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalDownTime);
			//lDownTimeEnd = lTotalDownTime;
			if(getNCData(111, 22, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, DOUBLE_PREC, &lDownTimeStart)==0);
					//lDownTimeStart = HourMinSecToSecConvertion(lDownTimeStart);
					setNCData(111, (21 + (2*sDownTimeReson)), SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lDownTimeStart);
			getNCData(111, 47 , SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalDownTime);
			lTotalDownTime += lDownTimeEnd;
			setNCData(111, 47 , SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalDownTime);
			sDownTimStartFlg = 1;
		}
		
	
	}

}
void ShiftAndClearDownTimeData()
{	
	short  i , j;
	short sGetBaseAddr, sSetBaseAddr;
	long lCycleDate = 0, lCycleTime=0;
	

	long lTotalDownTime = 0;
	// shift day data to another day
	for(j = 0; j < 3; j++)
	{
		if(j == 0)
		{
			sGetBaseAddr = 76;
			sSetBaseAddr  = 90;			
		}
		else if(j == 1)
		{
			sGetBaseAddr = 62;
			sSetBaseAddr  = 76;			
		}
		else if(j == 2)
		{
			sGetBaseAddr = 48;
			sSetBaseAddr  = 62;			
		}
		for(i = 0; i < 14; i++)
		{
			getNCData(111, (sGetBaseAddr + i) , SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalDownTime);
			setNCData(111, (sSetBaseAddr + i) , SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalDownTime);
		}
	
	}
	for(i = 0; i < 14; i++)
		{
			if( i < 12)
				getNCData(111, (24 + i*2) , SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalDownTime);
			else if(i == 12)
				getNCData(111, 47 , SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalDownTime);
			else
				getNCData(111, 21, SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalDownTime);

			setNCData(111, (48 + i) , SYS_NON, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lTotalDownTime);
		}
	// reset all cycle time related data	
	
	for(i = 21; i < 48; i++)
	{
		lCycleTime = 0;
		setNCData(111, i, PART_SYSTEM, AXIS_NON, ADR_BASE_SYSTEM, T_LONG, CUSTOM_API, &lCycleTime);
	}
}