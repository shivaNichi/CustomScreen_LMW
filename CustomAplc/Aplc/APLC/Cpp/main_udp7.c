/************************************************************************/
/*                                                                      */
/* File Name: main.c                                                    */
/* Function : APLC�����ɣ�ʵ�ֺ�Java��ͨ��                              */
/*            1.APLC�汾�Ļ�ȡ                                          */
/*            2.������С���ֺ����ݵĻ�ȡ                                */
/*            3.NC�ļ��Ķ�ȡ                                            */
/*            4.�����С���ֺ����ݵĻ�ȡ                                */
/* Date     : 2014/01/10                                                */
/* Code By  : lisc	                                                    */
/* Copyright: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION			*/
/*                                                                      */
/************************************************************************/
/* ��������:   
2014.01.10 lisc : 
	���ڻ�е��������ٶȷǳ������ͻ������鲻�ã�ͬʱ����֧�ֶ�̨�ֻ�
	ͬʱ�鿴������Ϣ����˽��������ӵ�TCP/IPͨ�ŷ�ʽ�޸�Ϊ���������
	��broadcast��UDP/IPͨ�ŷ�ʽ��һ�������	����ͨѶ���ӵȴ���ʱ�䣬
	�ӿ��������ʾ�����ٶȣ�ͬʱ����֧�ֶ�	̨�ֻ��ͻ���ͬʱ��ʾ���
	��NC��Ϣ��
*/              

#include "vxWorks.h"
#include <stdio.h>
#include <stdlib.h>       /* exit() */
#include <string.h>       /* bzero() */
#include <sys/types.h>
#include <netinet/in.h>   /* htons() */
#include <unistd.h>
#include <time.h>

//[ �궨��]
#define BUFF_SIZE				1024			//[ ��������С							]
#define BC_SERVER_PORT			8820			//[ �㲥�˿ں�							]
#define BC_SERVER_ADDR			"192.168.1.255"	//[ �㲥��ַ							]
#define UDP_SERVER_PORT			8823			//[ UDP�˿ں�							]

//[ ϵͳ��]
#define SYS_NO_1				1				//[ ��1ϵͳ								]
#define SYS_NO_2				2				//[ ��2ϵͳ								]
#define SYS_NO_3				3				//[ ��3ϵͳ								]
#define SYS_NO_4				4				//[ ��4ϵͳ								]
#define SYS_NO_5				5				//[ ��5ϵͳ								]
#define SYS_NO_6				6				//[ ��6ϵͳ								]
#define SYS_NO_7				7				//[ ��7ϵͳ								]
#define SYS_NO_8				8				//[ ��8ϵͳ								]

//[ ���]
#define AXIS_NO_1				1				//[ ��1��								]
#define AXIS_NO_2				2				//[ ��2��								]
#define AXIS_NO_3				3				//[ ��3��								]
#define AXIS_NO_4				4				//[ ��4��								]
#define AXIS_NO_5				5				//[ ��5��								]
#define AXIS_NO_6				6				//[ ��6��								]
#define AXIS_NO_7				7				//[ ��7��								]
#define AXIS_NO_8				8				//[ ��8��								]

//[ APLC�汾��]
#define DEV_R_APLC_VER_0        240             //[ APLC�汾�Ĵ�����R240�Ķ���			]
#define DEV_R_APLC_VER_1        241             //[ APLC�汾�Ĵ�����R241�Ķ���			]
#define DEV_R_APLC_VER_2        242             //[ APLC�汾�Ĵ�����R242�Ķ���			]
#define DEV_R_APLC_VER_3        243             //[ APLC�汾�Ĵ�����R243�Ķ���			]

//[ �շ�����]
#define SD_RECEIVE				0x00
#define SD_SEND					0x01
#define SD_BOTH         		0x02

//[ ��������]
#define T_CHAR                  0x01
#define T_SHORT                 0x02
#define T_LONG                  0x03
#define T_DOUBLE                0x05
#define T_STR                   0x10

//[ ���ݾ���]
#define DOUBLE_PREC             0x03             //[ ����CustomAPI��ȡ���ݵ���������	]
#define ADR_BASE_SYSTEM         0x01             //[ ����CustomAPI��ȡ���ݵ�ϵͳ��		]

//[ ͨ��ָ��ĺ궨�� */
#define CMD_TYPE_NULL			0				//[ ��ָ��								]
#define CMD_TYPE_NAME_VER		1				//[ ��ȡAPLC�汾ָ��					]
#define CMD_TYPE_NC_DATA		2				//[ ��ȡ����NC����ָ��					]
#define CMD_TYPE_NC_FILE		3				//[ ��ȡNC�ļ�����ָ��					]

//[ ��������]
#define DT_INVALID				'0'				//[ ��Ч��������						]

#define DT_IPADDR				'I'				//[ IP��ַ								]
#define DT_UINT_NAME			'A'				//[ NC����								]
#define DT_WARNING				'W'				//[ ������Ϣ							]
#define DT_AXIS_NAME			'X'				//[ ������								]
#define DT_CUR_POS				'C'				//[ ��ǰλ��							]
#define DT_PRG_O				'O'				//[ �ӹ�����O							]
#define DT_PRG_F				'F'				//[ �ӹ�����F							]
#define DT_PRG_M				'M'				//[ �ӹ�����M							]
#define DT_PRG_S				'S'				//[ �ӹ�����S							]
#define DT_PRG_T				'T'				//[ �ӹ�����T							]
#define DT_MEM_MODE				'D'				//[ �ڴ�ģʽ							]
#define DT_WORK_NUM				'N'				//[ ������								]
#define DT_AUTO_RUN				'R'				//[ ѭ��������							]
#define DT_KEEP_PROGRESS		'P'				//[ ��������							]
#define DT_STEP_STOP			'E'				//[ ����ֹͣ							]
#define DT_NC_STATUS			'U'				//[ NC״̬-ȡ����						]

#define DT_WARNING_01			'1'
#define DT_WARNING_02			'2'
#define DT_WARNING_03			'3'
#define DT_WARNING_04			'4'
#define DT_WARNING_05			'5'
#define DT_WARNING_06			'6'
#define DT_WARNING_07			'7'
#define DT_WARNING_08			'8'
#define DT_WARNING_09			'9'
#define DT_WARNING_10			'a'
#define DT_WARNING_11			'b'
#define DT_WARNING_12			'c'
#define DT_WARNING_13			'd'
#define DT_WARNING_14			'e'
#define DT_WARNING_15			'f'
#define DT_WARNING_16			'g'
#define DT_WARNING_17			'h'
#define DT_WARNING_18			'i'
#define DT_WARNING_19			'j'
#define DT_WARNING_20			'k'
#define DT_WARNING_21			'l'
#define DT_WARNING_22			'm'
#define DT_WARNING_23			'n'
#define DT_WARNING_24			'o'
#define DT_WARNING_25			'p'

#define DT_AXIS_NO_01			'1'
#define DT_AXIS_NO_02			'2'
#define DT_AXIS_NO_03			'3'
#define DT_AXIS_NO_04			'4'
#define DT_AXIS_NO_05			'5'
#define DT_AXIS_NO_06			'6'
#define DT_AXIS_NO_07			'7'
#define DT_AXIS_NO_08			'8'

#define NO_SUB_NUMBER			'0'

#define M_SEC_UPRM_HOST_LINK	123
#define M_SSEC_UPHLNK_LPOLLTM	22

//[ ��ȡָ�������]
const char* pCmdType      = "CMD=%d;";
//[ �Ӵ�С���ֺŶ�ȡ���ݵĸ�ʽ]
const char* pNcDataFormat = "CMD=%d;SysNo=%d;Sect=%d;SubSect=%d;Axis=%d;";
//[ ���ļ��ĸ�ʽ]
const char* pPathFormat   = "CMD=%d;Path=%s;";
//[ ��ȡ��е�����������]
const char* pSerialFormat = "CMD=%d;iType=%d;SysNo=%d;Sect=%d;SubSect=%d;Axis=%d;";
//[ �㲥���ݸ�ʽ]
const char* pBCDataFmt = "%c%c%s;";
const char* pBCDataFmt0 = "%c%s;";
const char* pBCDataFmt1 = "%c%c;";
const char* pBCDataFmt2 = "%s|";

//[ �������Log����]
#define MAX_LOG_COUNT			100
//[ log�ļ�ȫ·��]
#define LOG_FILE_NAME			"M01:\\PRG\\USER\\APLCDEBUG"
//[ ASSEMBLY.INF]
#define SYS_INF_FILE			"M01:\\DGN\\ASSEMBLY.INF"

//[ �ṹ�嶨��]
typedef struct 
{
	long lBuffSize;				//[ ��NC�˶�ȡ���ݵĴ�С				]
	char cDataBuf[BUFF_SIZE];	//[ �����NC�˻�ȡ������				]
} STRINGTYPE;

//[ ���ݽṹ]
typedef struct 
{
	char	cDataType;			//[ ��������							]
	char	cSubType;			//[ ����������							]
	int		iSecNo;				//[ �����ֺ�							]
	int		iSecSubNo;			//[ С���ֺ�							]
	int		iSysNo;				//[ ϵͳ��								]
	int		iAxisNo;			//[ ���								]
	BOOL	bCheckAxisNum;		//[ �Ƿ�����ĺϷ���					]
}STSECINFO;

//[ ȫ�ֱ�������]
int iTime = 0;					//[ ����������ִֻ��һ�Σ��ڲ�����ѭ��	]
int iCount = 0;					//[ ����Log��Ϣ������					]
int	bcSocket = 0;				//[ �㲥socket							]
int udpSocket = 0;				//[ ����socket							]
fd_set	ReadFds = {0};			//[ udpͨѶsocket����ṹ��				]
char cNcBasicInfo[BUFF_SIZE];	//[ �洢NC�Ļ�����Ϣ					]
struct timespec g_tpCycTime;	//[ �洢�㲥���ڿ�ʼʱ��				]

//[ ��ȡ�����б�]
STSECINFO g_stSecData[] = 
{
	// ��������			����������			������	С����			ϵͳ��	���		�Ƿ�����ĺϷ���
	// cDataType		cSubType			iSecNo	iSecSubNo		iSysNo	iAxisNo		bCheckAxisNum
	//-----------------------------------------------------------------------------------------------------------------------
	{DT_IPADDR,			NO_SUB_NUMBER,		124,	2,				0,		0,			FALSE	},		//[ IP��ַ			]

	//[ ������Ϣ]
	{DT_WARNING,		DT_WARNING_01,		53,		1 + 0x0C98,		0,		0,			FALSE	},		//[ ϵͳ����($1)	]
	{DT_WARNING,		DT_WARNING_02,		53,		1 + 0x0DD8,		0,		0,			FALSE	},		//[ ϵͳ����($2)	]
	{DT_WARNING,		DT_WARNING_03,		53,		1 + 0x0F18,		0,		0,			FALSE	},		//[ ϵͳ����($3)	]
	{DT_WARNING,		DT_WARNING_04,		53,		1 + 0x1058,		0,		0,			FALSE	},		//[ ϵͳ����($4)	]
	{DT_WARNING,		DT_WARNING_05,		53,		1 + 0x0C99,		0,		0,			FALSE	},		//[ �ŷ�����($1)	]
	{DT_WARNING,		DT_WARNING_06,		53,		1 + 0x0DD9,		0,		0,			FALSE	},		//[ �ŷ�����($2)	]
	{DT_WARNING,		DT_WARNING_07,		53,		1 + 0x0F19,		0,		0,			FALSE	},		//[ �ŷ�����($3)	]
	{DT_WARNING,		DT_WARNING_08,		53,		1 + 0x1059,		0,		0,			FALSE	},		//[ �ŷ�����($4)	]
	{DT_WARNING,		DT_WARNING_09,		53,		1 + 0x0C9A,		0,		0,			FALSE	},		//[ ���򱨾�($1)	]
	{DT_WARNING,		DT_WARNING_10,		53,		1 + 0x0DDA,		0,		0,			FALSE	},		//[ ���򱨾�($2)	]
	{DT_WARNING,		DT_WARNING_11,		53,		1 + 0x0F1A,		0,		0,			FALSE	},		//[ ���򱨾�($3)	]
	{DT_WARNING,		DT_WARNING_12,		53,		1 + 0x105A,		0,		0,			FALSE	},		//[ ���򱨾�($4)	]
	{DT_WARNING,		DT_WARNING_13,		53,		1 + 0x0C9B,		0,		0,			FALSE	},		//[ ��������($1)	]
	{DT_WARNING,		DT_WARNING_14,		53,		1 + 0x0DDB,		0,		0,			FALSE	},		//[ ��������($2)	]
	{DT_WARNING,		DT_WARNING_15,		53,		1 + 0x0F1B,		0,		0,			FALSE	},		//[ ��������($3)	]
	{DT_WARNING,		DT_WARNING_16,		53,		1 + 0x105B,		0,		0,			FALSE	},		//[ ��������($4)	]
	{DT_WARNING,		DT_WARNING_17,		53,		1 + 0x0CB1,		0,		0,			FALSE	},		//[ ��������($1)	]
	{DT_WARNING,		DT_WARNING_18,		53,		1 + 0x0DF1,		0,		0,			FALSE	},		//[ ��������($2)	]
	{DT_WARNING,		DT_WARNING_19,		53,		1 + 0x0F31,		0,		0,			FALSE	},		//[ ��������($3)	]
	{DT_WARNING,		DT_WARNING_20,		53,		1 + 0x1071,		0,		0,			FALSE	},		//[ ��������($4)	]
	{DT_WARNING,		DT_WARNING_21,		53,		1 + 0x0C9C,		0,		0,			FALSE	},		//[ �ŷ�����($1)	]
	{DT_WARNING,		DT_WARNING_22,		53,		1 + 0x0DDC,		0,		0,			FALSE	},		//[ �ŷ�����($2)	]
	{DT_WARNING,		DT_WARNING_23,		53,		1 + 0x0F1C,		0,		0,			FALSE	},		//[ �ŷ�����($3)	]
	{DT_WARNING,		DT_WARNING_24,		53,		1 + 0x105C,		0,		0,			FALSE	},		//[ �ŷ�����($4)	]
	{DT_WARNING,		DT_WARNING_25,		55,		100069,			0,		0,			FALSE	},		//[ ����ֹͣ		]

	//[ ��������Ϣ]
	{DT_AXIS_NAME,		DT_AXIS_NO_01,		127,	2,				1,		1,			TRUE	},		//[ ��1���ʾ����	]
	{DT_AXIS_NAME,		DT_AXIS_NO_02,		127,	2,				1,		2,			TRUE	},		//[ ��2���ʾ����	]
	{DT_AXIS_NAME,		DT_AXIS_NO_03,		127,	2,				1,		3,			TRUE	},		//[ ��3���ʾ����	]
	{DT_AXIS_NAME,		DT_AXIS_NO_04,		127,	2,				1,		4,			TRUE	},		//[ ��4���ʾ����	]
	{DT_AXIS_NAME,		DT_AXIS_NO_05,		127,	2,				1,		5,			TRUE	},		//[ ��5���ʾ����	]
	{DT_AXIS_NAME,		DT_AXIS_NO_06,		127,	2,				1,		6,			TRUE	},		//[ ��6���ʾ����	]
	{DT_AXIS_NAME,		DT_AXIS_NO_07,		127,	2,				1,		7,			TRUE	},		//[ ��7���ʾ����	]
	{DT_AXIS_NAME,		DT_AXIS_NO_08,		127,	2,				1,		8,			TRUE	},		//[ ��8���ʾ����	]

	//[ ��ǰλ����Ϣ]
	{DT_CUR_POS,		DT_AXIS_NO_01,		37,		3,				1,		1,			TRUE	},		//[ ��1�ᵱǰλ��	]
	{DT_CUR_POS,		DT_AXIS_NO_02,		37,		3,				1,		2,			TRUE	},		//[ ��2�ᵱǰλ��	]
	{DT_CUR_POS,		DT_AXIS_NO_03,		37,		3,				1,		3,			TRUE	},		//[ ��3�ᵱǰλ��	]
	{DT_CUR_POS,		DT_AXIS_NO_04,		37,		3,				1,		4,			TRUE	},		//[ ��4�ᵱǰλ��	]
	{DT_CUR_POS,		DT_AXIS_NO_05,		37,		3,				1,		5,			TRUE	},		//[ ��5�ᵱǰλ��	]
	{DT_CUR_POS,		DT_AXIS_NO_06,		37,		3,				1,		6,			TRUE	},		//[ ��6�ᵱǰλ��	]
	{DT_CUR_POS,		DT_AXIS_NO_07,		37,		3,				1,		7,			TRUE	},		//[ ��7�ᵱǰλ��	]
	{DT_CUR_POS,		DT_AXIS_NO_08,		37,		3,				1,		8,			TRUE	},		//[ ��8�ᵱǰλ��	]

	//[ ������Ϣ]
	{DT_PRG_O,			NO_SUB_NUMBER,		46,		2,				1,		0,			FALSE	},		//[�ӹ�����O		]
	{DT_PRG_F,			NO_SUB_NUMBER,		33,		1,				1,		0,			FALSE	},		//[�ӹ�����F		]
	{DT_PRG_M,			NO_SUB_NUMBER,		38,		1,				1,		0,			FALSE	},		//[�ӹ�����M		]
	{DT_PRG_S,			NO_SUB_NUMBER,		38,		101,			0,		1,			FALSE	},		//[�ӹ�����S		]
	{DT_PRG_T,			NO_SUB_NUMBER,		38,		201,			1,		0,			FALSE	},		//[�ӹ�����T		]
	{DT_MEM_MODE,		NO_SUB_NUMBER,		35,		11,				1,		0,			FALSE	},		//[NC�ڴ�ģʽ		]
	{DT_WORK_NUM,		NO_SUB_NUMBER,		126,	8002,			1,		0,			FALSE	},		//[��������			]
	{DT_AUTO_RUN,		NO_SUB_NUMBER,		35,		20,				1,		0,			FALSE	},		//[ѭ��������		]
	{DT_KEEP_PROGRESS,	NO_SUB_NUMBER,		35,		22,				1,		0,			FALSE	},		//[��������			]
	{DT_STEP_STOP,		NO_SUB_NUMBER,		53,		13090,			0,		0,			FALSE	},		//[����ֹͣ			]
	{DT_NC_STATUS,		NO_SUB_NUMBER,		35,		10,				1,		0,			FALSE	},		//[NC״̬-ȡ����	]
	{DT_UINT_NAME,		NO_SUB_NUMBER,		126,	135,			0,		0,			FALSE	},		//[NC����(#1135)	]

	//[ ������ʶ��Ϣ]
	{DT_INVALID,		NO_SUB_NUMBER,		0,		0,				0,		0,			FALSE	},		//[����				]
};

//[[ ��������]]
//[ APLC��ʼ������]
extern void aplc_top();	
//[ APLC������]
extern void base_Main();

//[[ ���ݴ�����]]
//[ ����APLC�汾��]
void SetAplcVer();
//[ ȡ�û�еλ������]
int GetXYData(int iSys, char* cBuffer);
//[ ȡ�ü��ӽ������Ϣ]
int GetMonitorData(int iSys, char* cBuffer);
//[ ȡ��NC������Ϣ]
int GetNcBasicInfo();

//[ UDP/IPģʽ]
//[ ȡ������]
int GetCmdID(char* cCmd);
//[ ����APLC sokcet�汾��]
void SendAplcVer(struct sockaddr * pAddr);
//[ ��ȡ������С���ֺ�����]
void SendNCData(struct sockaddr * pAddr, char* cBuf);
//[ ���Ϳͻ��������ļ�]
void SendNCFile(struct sockaddr * pAddr, char* cBuf);

//[[ ͨѶ����]]
//[ �رչ㲥socket]
void CloseBcSocket();
//[ �����㲥socket]
int CreateBcSocket();
//[ �㲥����]
int BroadcastData();
//[ �ر�udp socket]
void CloseUdpSocket();
//[ ����udp socket]
int CreateUdpSocket();
//[ udpͨ��]
int DoUdpCommunicate();

//[[ Log����]]
//[ ��¼Log��Ϣ]
void WriteLogInfo(char* pLogInfo);
//[ ��¼Log��Ϣ]
void WriteLastErrInfo(char* pInfoName);
//[ ��¼Log��Ϣ]
void WriteLogInfoBin(char* pLogInfo, int iLen);

/************************************************************************/
/* Function Name: GetCmdID                                              */
/* Function		: ȡ�ÿͻ��˵�����			                            */
/* Parameter	: char* cCmd <I> : �ͻ��˵������ַ���                   */
/* Return Value	: void��                                                */
/* Date			: 2014/01/03                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
int GetCmdID(char* cCmd)
{
	//[[[ ȡ�ÿͻ������������]]]

	//[ �����������]
	int iCmd = CMD_TYPE_NULL;

	//[ ��������Ƿ�Ϸ�]
	if(NULL == cCmd)
	{
		//[ �Ƿ�]
		//[ ���طǷ�ָ��]
		return iCmd;
	}

	//[ ȡ�ÿͻ��˷�����ָ��]
	sscanf(cCmd, pCmdType, &iCmd);

	//[ ����ȡ�õ�����]
	return iCmd;
}

/************************************************************************/
/* Function Name: SendAplcVer											*/
/* Function		:  ȡ��aplc socket�İ汾                                */
/* Parameter	: struct sockaddr * pAddr <I> : �ͻ��˵�ַ              */
/* Return Value	: void��                                                */
/* Date			: 2014/01/07                                            */
/* Code By		: lisc                                                  */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void SendAplcVer(struct sockaddr * pAddr)
{
	//[[[ ������ͻ��˷���APLC�İ汾��]]]

	//[[ ��ʼ������APLC�汾��Ϣ����ʱ����]]
	short sR240 = 0;			//[ ��ʼ��R240������	]
	short sR241 = 0;			//[ ��ʼ��R241������	]
	short sR242 = 0;			//[ ��ʼ��R242������	]
	short sR243 = 0;			//[ ��ʼ��R243������	]
	char cBuff[BUFF_SIZE];		//[ APLC�汾�Ķ���		]
	int iRet = 0;

	//[ ��ʼ����ʱ����]
	memset(cBuff, 0, sizeof(cBuff));/* APLC�汾�ĳ�ʼ�� */
	//[ ��ȡR240����]
	melplcWtstR(DEV_R_APLC_VER_0, &sR240);
	//[ ��ȡR241����]
	melplcWtstR(DEV_R_APLC_VER_1, &sR241);
	//[ ��ȡR242����]
	melplcWtstR(DEV_R_APLC_VER_2, &sR242);
	//[ ��ȡR243����]
	melplcWtstR(DEV_R_APLC_VER_3, &sR243);

	//[ ��Ϸ������� APLC�汾]
	sprintf(cBuff,"%s%04d%s%03d%s%c%c%c","BND-",sR240,"W",sR241,"-",
		sR242 & 0x00FF, (sR242 >> 8) & 0x00FF, sR243 & 0x00FF);

	//[ ����APLC�汾]
	iRet = sendto(bcSocket, cBuff, strlen(cBuff), 0, pAddr, sizeof(struct sockaddr));
	if(iRet <= 0)
	{
		//[ ����ʧ��]
		WriteLastErrInfo("SendAplcVer::sendto");
	}
	else
	{
		//[ ���ͳɹ�]
		WriteLogInfo("aplc ver:");
		WriteLogInfo(cBuff);
		WriteLogInfo("\n");
	}
}

/************************************************************************/
/* Function Name: SendNCData		                                    */
/* Function		: ��ȡ������С���ֺ�����                                */
/* Parameter	: struct sockaddr * pAddr <I> : �ͻ��˵�ַ              */
/*				  char* buf <I> :  ���յ�����							*/
/* Return Value	: void��                                                */
/* Date			: 2014/01/07                                            */
/* Code By		: lisc                                                  */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void SendNCData(struct sockaddr * pAddr, char* cBuf)
{
	//[[[ ��ͻ��˷���ָ�����󣨴�С���ֺš�ϵͳ�š���ţ�������]]]
	int iCmd = CMD_TYPE_NULL;  //[ ָ�����͵Ķ���		]
	int iSysNo = 0;            //[ ϵͳ��				]
	int iSect = 0;             //[ ������				]
	int iSubSect = 0;          //[ С����				]
	int iAxis = 0;             //[ ���					]
	STRINGTYPE GetStrType;     //[ ��ȡ������			]
	long iRet = 0;             //[ getNCData�����ķ���ֵ]
	char cBuff[BUFF_SIZE];

	//[ ���ݵĻ�������С]
	GetStrType.lBuffSize = sizeof (GetStrType.cDataBuf);
	//[ �б��ʼ��]
	memset(GetStrType.cDataBuf, 0, sizeof(GetStrType.cDataBuf));
	//[ ָ�����͡���ʽ���ݷ���]
	sscanf(cBuf, pNcDataFormat, &iCmd, &iSysNo, &iSect, &iSubSect, &iAxis);

	//[ ��ȡ����]
	iRet = getNCData(iSect, iSubSect, iSysNo, iAxis, ADR_BASE_SYSTEM, T_STR, DOUBLE_PREC, &GetStrType);
	if(0 == iRet)
	{
		//[ ����ȡ�óɹ�]

		//[ ����� getNCData �����Ϣ������]
		//[ ���ͻ�ȡ���ݵķ���ֵ]
		iRet = sendto(bcSocket, (char*)&iRet, sizeof(iRet), 0, pAddr, sizeof(struct sockaddr));
		if(iRet <= 0)
		{
			//[ ����ʧ��]
			WriteLastErrInfo("SendNCData::getNCData:NG\n");
		}
		else
		{
			//[ ���ͳɹ�]
			WriteLogInfo("SendNCData::getNCData:OK\n");
		}

		//[ ��������]
		iRet = sendto(bcSocket, GetStrType.cDataBuf, GetStrType.lBuffSize, 0, pAddr, sizeof(struct sockaddr));
		if(iRet <= 0)
		{
			//[ ����ʧ��]
			WriteLastErrInfo("SendNCData::sendto:NG\n");
		}
		else
		{
			//[ ���sendto��Ϣ]
			WriteLogInfo("<reply:");
			WriteLogInfoBin(GetStrType.cDataBuf, GetStrType.lBuffSize);
			WriteLogInfo(">\n");
		}
	}
	else
	{
		//[ ȡ������ʧ��]
		WriteLogInfo("SendNCData::getNCData:NG\n");
	}
}

/************************************************************************/
/* Function Name: SendNCFile		                                    */
/* Function		: ���ļ��Ĵ�����		                                */
/* Parameter	: struct sockaddr * pAddr <I> : �ͻ��˵�ַ              */
/*				  char* buf <I> :  ���յ�����							*/
/* Return Value	: void��                                                */
/* Date			: 2014/01/07                                            */
/* Code By		: lisc                                                  */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void SendNCFile(struct sockaddr * pAddr, char* cBuf)
{
	//[[[ ��ͻ��˷���������ļ���Ϣ]]]

	//[[ ��ʱ��������]]
	int iCmd = CMD_TYPE_NULL;        //[ ָ�����͵Ķ���			]
	char path[BUFF_SIZE];              //[ �ļ���·��				]
	char senddata[BUFF_SIZE];          //[ ���͵Ļ���������		]
	FILE * fFile = 0;                //[ �ļ�					]
	long  nLen = 0;                  //[ һ�η������ݵĳ���		]
	int iRet = 0;                    //[ SendNCFile�����ķ���ֵ ]

	//[ ��ʼ��path ]
	bzero(path, BUFF_SIZE);
	//[ ��ȡ�ļ�·����ָ�� ]
	sscanf(cBuf, pPathFormat, &iCmd, path);
	//[ ���ļ� ]
	fFile  = fopen(path, "r");
	//[ �ļ���ʧ�ܣ��´��ٴ����� ]
	//[ ����ֵ���趨 ]
	iRet = 1;
	if (!fFile)
	{
		iRet = 0;
	}
	//[ �����ļ��򿪽�� ]
	iRet = sendto(bcSocket, (char*)&iRet, sizeof(iRet), 0, pAddr, sizeof(struct sockaddr));
	if(iRet <= 0)
	{
		//[ ����ʧ��]
		WriteLastErrInfo("SendNCFile::sendto::iRet");
	}
	//[ �ļ���ʧ��]
	if (!fFile)
	{
		//[ ֱ�ӷ���]
		return;
	}

	//] ѭ�������ļ����� ]
	do
	{
		//[ һ��������byte������ ]
		nLen = fread(senddata, sizeof(char), BUFF_SIZE, fFile);

		//[ �������� ]
		iRet = sendto(bcSocket, senddata, nLen, 0, pAddr, sizeof(struct sockaddr));
		if(iRet <= 0)
		{
			//[ ����ʧ��]
			WriteLastErrInfo("SendNCFile::sendto::File");
		}
	} while (nLen == BUFF_SIZE);

	//[ �ر��ļ� ]
	fclose(fFile);
}

/************************************************************************/
/* Function Name: aplc_top                                              */
/* Function		: APLC��ʼ������		                                */
/* Parameter	: null                                                  */
/* Return Value	: void                                                  */
/* Date			: 2014/01/03                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void aplc_top(void)
{
	//[ ����APLC�İ汾 ]
    SetAplcVer();

    //[ APLC��ͬ�ڴ���ĵ�¼ ]
    setUserBaseMain(base_Main);
}

/************************************************************************/
/* Function Name: CloseBcSocket			                                */
/* Function		: �رչ㲥socket		                                */
/* Parameter	: void							                        */
/* Return Value	: void��                                                */
/* Date			: 2014/01/07                                            */
/* Code By		: lisc                                                  */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void CloseBcSocket()
{
	//[ ���socket�Ƿ����]
	int iRet = 0;
	if (bcSocket <= 0) 
	{
		//[ ������]
		//[ ���ùرգ�ֱ�ӷ���]
		return;
	}

	//[ �ر�socket]
	shutdown(bcSocket, SD_BOTH);
	bcSocket = 0;

	WriteLogInfo("CloseBcSocket\n");
}

/************************************************************************/
/* Function Name: CreateBcSocket			                            */
/* Function		: �����㲥socket		                                */
/* Parameter	: void							                        */
/* Return Value	: void��                                                */
/* Date			: 2014/01/07                                            */
/* Code By		: lisc                                                  */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
int CreateBcSocket()
{
	//[ ��������ֵ���㲥��ʶ����ʼ��������]
	int iRet = 0;
	BOOL yes = TRUE;

	//[ �رվɵ�socket]
	CloseBcSocket();

	//[ �����µ�socket]
	bcSocket = socket(AF_INET, SOCK_DGRAM, 0);
	//[ ����Ƿ񴴽��ɹ�]
	if (bcSocket < 0) 
	{
		//[ ����ʧ��]
		WriteLastErrInfo("CreateBcSocket::socket");
		return -1;
	}

	//[ �����ɹ�]
	//[ ����socketΪ�㲥socket]
	iRet = setsockopt(bcSocket, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));
	if (iRet != 0 ) 
	{
		//[ ����ʧ��]
		WriteLastErrInfo("CreateBcSocket::setsockopt");
		return -1;
	}

	//[ ���ش����ɹ�]
	return 0;
}

/************************************************************************/
/* Function Name: BroadcastData                                         */
/* Function		: �㲥����(��еλ������)	                            */
/* Parameter	: null                                                  */
/* Return Value	: void��                                                */
/* Date			: 2014/01/03                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
int BroadcastData()
{
	char cBuff[BUFF_SIZE];				//[ ��ʱ����		]
	struct sockaddr_in addrto;			//[ �㲥��ַ		]
	int nlen = sizeof(addrto);			//[ �㲥��ַ����	]
	int iRet = 0;
	int iDataLen = 0;

	//[ ���ù㲥��ַ]
	addrto.sin_family = AF_INET;
	addrto.sin_addr.s_addr = inet_addr(BC_SERVER_ADDR);
	addrto.sin_port = htons(BC_SERVER_PORT);

	//[ ȡ������]
	bzero(cBuff, BUFF_SIZE);
	//if(0 == GetXYData(SYS_NO_1, cBuff))
	if(0 == GetMonitorData(SYS_NO_1, cBuff))
	{
		//[ ��������]
		iDataLen = strlen(cBuff);
		iRet = sendto(bcSocket, cBuff, iDataLen, 0, (struct sockaddr*)&addrto, nlen);
		if(iRet <= 0)
		{
			//[ ����ʧ��]
			WriteLastErrInfo("BroadcastData::sendto");
		}
		else
		{
			//[ ���ͳɹ�]
			//bzero(cBuff, BUFF_SIZE);
			//sprintf(cBuff, "%dB of %dB sent\n", iRet, iDataLen);
			WriteLogInfo(cBuff);
			WriteLogInfo("\n");
		}
	}
	else
	{
		//[ ȡ������ʧ��]
		WriteLogInfo("Failed to get xyz\n");
	}
}

/************************************************************************/
/* Function Name: CloseUdpSocket			                            */
/* Function		: �ر�udp socket		                                */
/* Parameter	: void							                        */
/* Return Value	: void��                                                */
/* Date			: 2014/01/07                                            */
/* Code By		: lisc                                                  */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void CloseUdpSocket()
{
	//[ ���socket�Ƿ����]
	int iRet = 0;
	if (udpSocket <= 0) 
	{
		//[ ������]
		//[ ֱ�ӷ���]
		return;
	}

	//[ ���socket �� ͨѶ��ʶ���ṹ��Ĺ�ϵ]
	FD_CLR(udpSocket, &ReadFds);

	//[ �ر�socket]
	shutdown(udpSocket, SD_BOTH);
	udpSocket = 0;

	WriteLogInfo("CloseUdpSocket\n");
}

/************************************************************************/
/* Function Name: CloseUdpSocket			                            */
/* Function		: ����udp socket		                                */
/* Parameter	: void							                        */
/* Return Value	: void��                                                */
/* Date			: 2014/01/07                                            */
/* Code By		: lisc                                                  */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
int CreateUdpSocket()
{
	//[ ���庯������ֵ��udp��ַ����ʱ����]
	int iRet = 0;
	struct sockaddr_in addr;
	char cBuff[BUFF_SIZE];

	//[ �رվɵ�udp socket]
	CloseUdpSocket();

	//[ ����udp socket]
	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (udpSocket < 0) 
	{
		//[ ����ʧ��]
		//[ ����ʧ��]
		WriteLastErrInfo("CreateUdpSocket::socket");
		return -1;
	}

	//[ ����udp��ַ��Ϣ]
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(UDP_SERVER_PORT);

	//[ ��udp socket��udp��ַ]
	iRet = bind(udpSocket, (struct sockaddr *)&addr, sizeof(addr));
	if (iRet < 0) 
	{
		//[ ��ʧ��]
		WriteLastErrInfo("CreateUdpSocket::bind");
		//[ ����ʧ��]
		return -1;
	}

	//[ ���ش����ɹ�]
	return 0;
}

/************************************************************************/
/* Function Name: DoUdpCommunicate	                                    */
/* Function		: udpͨ��				                                */
/* Parameter	: void							                        */
/* Return Value	: void��                                                */
/* Date			: 2014/01/07                                            */
/* Code By		: lisc                                                  */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
int DoUdpCommunicate()
{
	//[[[ ִ��UDPͨѶ]]]

	//[ ����ͨѶ���õ�����ʱ����]
	int iCmd = CMD_TYPE_NULL;				//[ ��������			]
	int iRet = 0;							//[ ��������ֵ			]
	struct sockaddr_in addrFrom;			//[ �ͻ��˵�ַ			]
	int addrLen = sizeof(addrFrom);			//[ �ͻ��˵�ַ����		]
	char cBuff[BUFF_SIZE];					//[ ��ʱ����			]
	struct timeval timeout = {0, 1000};		//[ ��ʱʱ��			]

	//[ ����socket�ĳ�ʱʱ��]
	memset(&addrFrom, 0, sizeof(addrFrom));
	bzero(cBuff, BUFF_SIZE);
	//[ fd��socket����]
	FD_SET(udpSocket, &ReadFds);
	//[ timeout��socket�źŵȴ�����]
	iRet = select(FD_SETSIZE, &ReadFds, (fd_set *)0, (fd_set *)0, &timeout);
	//[ timeout��errorʱ�ĵĴ���]
	if (iRet < 0)
	{
		//[ ���ó�ʱʱ��ʧ��]
		return -1;
	}

	//[ ���select�Ƿ�time expired]
	if(0 == iRet)
	{
		//[ ���ش������]
		return 0;
	}
	
	//[ ���udpSocket�Ƿ�����Ч���ź�]
	if(FD_ISSET(udpSocket, &ReadFds))
	{
		//[ ����Ч�ź�]
		//[ �ӿͻ�����ȡ��������]
		iRet = recvfrom(udpSocket, (char *)&cBuff, sizeof(cBuff), 0, (struct sockaddr *)&addrFrom, &addrLen);
		//[ �����յĽ���Ƿ���Ч]
		if (iRet <= 0) 
		{
			//[ ��Ч]
			WriteLastErrInfo("DoUdpCommunicate::recvfrom");
			//[ ���ش���]
			return -1;
		}
		else
		{
			//[ ����յ�������ָ��]
			WriteLogInfo("<from:");
			WriteLogInfo(cBuff);
			WriteLogInfo(">\n");

			//[ ȡ�ÿͻ��˵�����ָ��]
			iCmd = GetCmdID(cBuff);

			//[ �������������Ӧ�Ķ���]
			switch(iCmd)
			{
			//[ �ͻ�������APLC socket�汾��]
			case CMD_TYPE_NAME_VER:
				//[ ��ͻ��˷���APLC socket�汾��]
				SendAplcVer((struct sockaddr *)&addrFrom);
				break;

			//[ �ͻ������뵥����С���ֺ�����]
			case CMD_TYPE_NC_DATA:
				//[ ��ͻ��˷��͵�����С���ֺ�����]
				SendNCData((struct sockaddr *)&addrFrom, cBuff);
				break;

			//[ �ͻ������뷢���ļ�]
			case CMD_TYPE_NC_FILE:
				//[ ��ͻ��˷���������ļ�����]
				SendNCFile((struct sockaddr *)&addrFrom, cBuff);
				break;

			//[ ��������������]
			default:
				break;
			}
		}
	}
	
	//[ ����udpͨѶ����ɹ�]
	return 0;
}

/************************************************************************/
/* Function Name: SetAplcVer                                            */
/* Function		: aplc �汾������                                       */
/* Parameter	: null                                                  */
/* Return Value	: void                                                  */
/* Date			: 2014/01/08                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void SetAplcVer()
{
	//[[ APLC�汾�ţ�BND-9001W001-A0B						]]
	//[[ ˵����												]]
	//[[	sR240��������9001��=0x2329��					]]
	//[[	sR241��������001 ��0x0001��						]]
	//[[	sR242 bit7-0����A0B��A ��0x41:'A'��ASCII�룩	]]
	//[[	sR242 bitF-8����A0D��0 ��0x41:'0'��ASCII�룩	]]
	//[[	sR243 bit7-0����A0D��D ��0x44:'D'��ASCII�룩	]]
	//[[	sR243 bitF-8�̶���ΪFF����������ʾ			]]

	//[[ ��ʼ��APLC�汾����Ϣ]]
	short sR240 = 0x2329;    /* APLC�汾��R240���趨ֵ�Ķ��� */
	short sR241 = 0x0001;    /* APLC�汾��R241���趨ֵ�Ķ��� */
	short sR242 = 0x3041;    /* APLC�汾��R242���趨ֵ�Ķ��� */
	short sR243 = 0xFF44;    /* APLC�汾��R243���趨ֵ�Ķ��� */
	/*����R240����*/
	melplcWsetR(DEV_R_APLC_VER_0, sR240);
	/*����R241����*/
	melplcWsetR(DEV_R_APLC_VER_1, sR241);
	/*����R242����*/
	melplcWsetR(DEV_R_APLC_VER_2, sR242);
	/*����R243����*/
	melplcWsetR(DEV_R_APLC_VER_3, sR243);
}

//[ ȡ��NC������Ϣ]
/************************************************************************/
/* Function Name: GetNcBasicInfo                                        */
/* Function		: ȡ��NC������Ϣ                                        */
/* Parameter	: null                                                  */
/* Return Value	: -1 : ȡ��ʧ�ܣ���Ϊ-1��ȡ�óɹ�                       */
/* Date			: 2014/01/08                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
int GetNcBasicInfo()
{
	//[ ������ʱ����]
	FILE * fFile = 0;               //[ �ļ�					]
	int iDataLen = 0;				//[ ��ʱ�����С			]
	int iTempLen = 0;				//[ һ�ζ�ȡ�����ݳ���		]
	char cBuffer[3 * BUFF_SIZE];	//[ ��ʱ�����С			]

	//[ ���ļ� ]
	fFile  = fopen(SYS_INF_FILE, "r");
	//[ �ļ���ʧ��]
	if (!fFile)
	{
		return -1;
	}

	//[ ѭ�������ļ����� ]
	bzero(cBuffer, 3 * BUFF_SIZE);
	do
	{
		//[ һ��������byte������ ]
		iTempLen = fread(&cBuffer[iDataLen], sizeof(char), BUFF_SIZE, fFile);
		iDataLen = iDataLen + iTempLen;
	} while (iTempLen == BUFF_SIZE);

	//[ �����ļ�ȡ�û��֡�M/L���汾�š����кŵ���Ϣ]
	//[��������������������������������������������]

	//[ �ر��ļ� ]
	fclose(fFile);

	//[ ����ȡ�óɹ�]
	return 0;
}

/************************************************************************/
/* Function Name: GetXYData                                             */
/* Function		: ȡ�û�еλ������                                      */
/* Parameter	: int iSys <I> : ϵͳ��                                 */
/*				  char* cBuffer <O> : ������Ϣ(��ʽ��x����;y����;z����;)*/
/* Return Value	: int: С��0-ʧ�� 0-�ɹ�                                */
/* Date			: 2014/01/03                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
int GetXYData(int iSys, char* cBuffer)
{
	//[[[ ȡ��ָ��ϵͳ�Ļ�еλ������]]]

	//[ ��������]
	STRINGTYPE stStrTypex;
	char cAxisNum = 0;
	int iIdx = 0;
	int iDataLen = 0;
	int iTempLen = 0;
	stStrTypex.lBuffSize = BUFF_SIZE;

	//[ ȡ��ָ��ϵͳ������]
	if( 0 != getNCData(126, 3, iSys, 0, ADR_BASE_SYSTEM, T_CHAR, DOUBLE_PREC, &cAxisNum) )
	{
		WriteLogInfo("Failed to get Axis Num\n");
		return -1;
	}

	//[ ѭ��ȡ��ÿ���������]
	bzero(cBuffer, BUFF_SIZE);
	for(iIdx = 0; iIdx < (int)cAxisNum; iIdx = iIdx + 1 )
	{
		//[ ȡ�õ����������]
		bzero(stStrTypex.cDataBuf, BUFF_SIZE);
		if( 0 == getNCData(37, 2, iSys, iIdx + 1, ADR_BASE_SYSTEM, T_STR, DOUBLE_PREC, &stStrTypex) )
		{
			//[ ȡ�óɹ�]
			//[ ��ȡ�õ�������ֵ���Ƶ����������]
			iTempLen = strlen(stStrTypex.cDataBuf);
			memmove(&cBuffer[iDataLen], stStrTypex.cDataBuf, iTempLen);
			iDataLen = iDataLen + iTempLen;
			cBuffer[iDataLen] = ';';
			iDataLen = iDataLen + 1;
		}
		else
		{
			//[ ȡ��ʧ��]
			WriteLogInfo("Failed to get XY\n");
			return -1;
		}
	}

	//[ ����ȡ�óɹ�]
	return 0;
}

/************************************************************************/
/* Function Name: GetMonitorData                                        */
/* Function		: ȡ�ü��ӽ������Ϣ		                            */
/* Parameter	: int iSys <I> : ϵͳ��                                 */
/*				  char* cBuffer <O> : ������Ϣ(��ʽ��x����;y����;z����;)*/
/* Return Value	: int: С��0-ʧ�� 0-�ɹ�                                */
/* Date			: 2014/01/13                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
int GetMonitorData(int iSys, char* cBuffer)
{
	//[ ��������]
	int iIndex = 0;
	char cAxisNum = 0;
	int iSecSubNo = 0;
	int iTempLen = 0;
	int iDataLen = 0;
	STRINGTYPE stStrTypex;
	char cTempBuffer[128] = {0};

	//[ ��ʼ���㲥���ݻ���]
	stStrTypex.lBuffSize = BUFF_SIZE;
	bzero(cBuffer, BUFF_SIZE);

	//[ ȡ��ָ��ϵͳ������]
	if( 0 != getNCData(126, 3, iSys, 0, ADR_BASE_SYSTEM, T_CHAR, DOUBLE_PREC, &cAxisNum) )
	{
		WriteLogInfo("Failed to get Axis Num\n");
		return -1;
	}

	//[ ѭ��ȡ����������]
	while(DT_INVALID != g_stSecData[iIndex].cDataType)
	{
		//[ ȡ������ǰ��Ԥ����]
		////[ ȡ��С���ֺ�]
		//iSecSubNo = g_stSecData[iIndex].iSecSubNo;

		//[ ����Ƿ��ǵ�ǰλ����Ϣ]
		if( TRUE == g_stSecData[iIndex].bCheckAxisNum )
		{
			//[ �ǵ�ǰλ����Ϣ]
			//[ ������Ƿ����]
			if(g_stSecData[iIndex].iAxisNo > ((int)cAxisNum))
			{
				//[ ������]
				//[ ������һ�����ݴ���]
				iIndex = iIndex + 1;
				continue;
			}
		}

		//[ ȡ������]
		//[ ȡ�õ����������]
		bzero(stStrTypex.cDataBuf, BUFF_SIZE);
		if( 0 == getNCData(	g_stSecData[iIndex].iSecNo, 
							g_stSecData[iIndex].iSecSubNo, 
							iSys, 
							g_stSecData[iIndex].iAxisNo, 
							ADR_BASE_SYSTEM, 
							T_STR, 
							DOUBLE_PREC, 
							&stStrTypex) )
		{
			//[ ȡ�óɹ�]

			//[ ����Ƿ��Ǳ�����Ϣ]
			//[ û�б�������Ϣ����Ҫ����]
			if( DT_WARNING == g_stSecData[iIndex].cDataType)
			{
				if(DT_WARNING_25 == g_stSecData[iIndex].cSubType)
				{
					if(0 == strcmp(stStrTypex.cDataBuf, "FFFF"))
					{
						//[ û�б���]
						//[ ���÷��ͣ�ֱ�ӽ�����һ�����ݴ���]
						iIndex = iIndex + 1;
						continue;
					}
				}
				else
				{
					if('0' == stStrTypex.cDataBuf[0])
					{
						//[ û�б���]
						//[ ���÷��ͣ�ֱ�ӽ�����һ�����ݴ���]
						iIndex = iIndex + 1;
						continue;
					}
				}
			}

			//[ ��ȡ�õ�������ֵ���Ƶ����������]
			bzero(cTempBuffer, 128);
			if(NO_SUB_NUMBER != g_stSecData[iIndex].cSubType)
			{
				if(DT_WARNING == g_stSecData[iIndex].cDataType)
				{
					// SAMPLE: ������Ϣ "W1"
					sprintf(cTempBuffer, pBCDataFmt1, g_stSecData[iIndex].cDataType, g_stSecData[iIndex].cSubType);
				}
				else
				{
					// SAMPLE: ������ "X1X"
					sprintf(cTempBuffer, pBCDataFmt, g_stSecData[iIndex].cDataType, g_stSecData[iIndex].cSubType, stStrTypex.cDataBuf);
				}
			}
			else
			{
				if(DT_IPADDR == g_stSecData[iIndex].cDataType)
				{
					// SAMPLE: IP��ַ "192.168.1.61|"
					sprintf(cTempBuffer, pBCDataFmt2, stStrTypex.cDataBuf);
				}
				else
				{
					// SAMPLE: NC���� "ANME"
					sprintf(cTempBuffer, pBCDataFmt0, g_stSecData[iIndex].cDataType, stStrTypex.cDataBuf);
				}
			}
			iTempLen = strlen(cTempBuffer);
			memmove(&cBuffer[iDataLen], cTempBuffer, iTempLen);
			iDataLen = iDataLen + iTempLen;

			////[ ���Log]
			//WriteLogInfo(cBuffer);
			//WriteLogInfo("\n");
		}
		else
		{
			//[ ȡ��ʧ��]
			WriteLogInfo("Failed to get data\n");
			return -1;
		}

		//[ ��ָ��ָ����һ������]
		iIndex = iIndex + 1;
	}
	
	//[ ��������ȡ�óɹ�]
	return 0;
}

/************************************************************************/
/* Function Name: base_Main                                             */
/* Function		: �첽ģʽ�µ�APLC������	                            */
/* Parameter	: null                                                  */
/* Return Value	: void��                                                */
/* Date			: 2014/01/03                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void base_Main()
{
	//[[[ �첽ģʽ�µ�APLC������						]]]
	//[[[ ��Ҫʵ��ȡ�û�еλ�����겢����㲥��������	]]]]

	int iRet = 0;
	short sDelay = 0;
	struct timespec tpCurCycTime;

	memset(&tpCurCycTime,0,sizeof(struct timespec));
	clock_gettime(CLOCK_REALTIME,&tpCurCycTime);

	//[ ����Ƿ��ǵ�һ��ִ�иú���]
	iTime = iTime + 1;
	if(1 == iTime)
	{
		//[ ��һ��ִ��	]
		//[ socket����ṹ��ʼ��]
		FD_ZERO(&ReadFds);

		//[ ����broadcast��socket]
		iRet = CreateBcSocket();
		if(iRet < 0)
		{
			iTime = 0;
			return;
		}

		//[ ����udp��socket]
		iRet = CreateUdpSocket();
		if(iRet < 0)
		{
			iTime = 0;
			return;
		}

		//[ ����aplc��ͣʱ������]
		//[ #9622 bit4-7����0���������Log]
		//[       bit4-7����0���������Log]
		//[       bit0-3Ϊaplc�㲥ʱ������]
		sDelay = 0x10/*�������Log*/ + 0x4/*aplc�㲥ʱ������Ϊ4*/;
		iRet = setNCData(M_SEC_UPRM_HOST_LINK, M_SSEC_UPHLNK_LPOLLTM, SYS_NO_1, 0, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sDelay);
		if( 0 != iRet )
		{
			//[ ȡ��ʧ��]
			sDelay = 5;
		} 
		iTime = 1;
	}
	//[ ȡ�ù㲥ʱ��������]
	//[ ����#9622�� bit0-3 ��������ѭ��������]
	//[ ����#9622�Ĵ����ֺţ�123��С���ֺţ�22]
	iRet = getNCData(M_SEC_UPRM_HOST_LINK, M_SSEC_UPHLNK_LPOLLTM, SYS_NO_1, 0, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sDelay);
	if(0 != iRet)
	{
		//[ ȡ��ʧ�ܣ���������]
		sDelay = 4;
	}
	else
	{
		//[ ȡ�ù㲥ʱ��������]
		sDelay = (sDelay & 0x0F);
		if(sDelay < 1)
		{
			sDelay = 1;
		}
	}

	//[ ѭ���㲥��һϵͳ����������]
	//[ �����ֻ��˵����󣬲�������������Ӧ������]
	//[ sDelay��ʾѭ������������10����һ��ѭ�����ڵ�ʱ��Ϊ10ms]
	if((((tpCurCycTime.tv_sec- g_tpCycTime.tv_sec)*1000) + (tpCurCycTime.tv_nsec - g_tpCycTime.tv_nsec)/1000000) > sDelay*10)
	{
		g_tpCycTime.tv_nsec = tpCurCycTime.tv_nsec;
		g_tpCycTime.tv_sec = tpCurCycTime.tv_sec;
		//[ �㲥����]
		iRet = BroadcastData();
		if(iRet < 0)
		{
			//[ �رչ㲥socket��udp socket]
			CloseBcSocket();
			CloseUdpSocket();
			//[ ���´����׽��� ]
			iTime = 0;
			return;
		}

		//[ ���տͻ�������]
		iRet = DoUdpCommunicate();
		if(iRet < 0)
		{
			//[ �رչ㲥socket��udp socket]
			CloseBcSocket();
			CloseUdpSocket();
			//[ ���´����׽��� ]
			iTime = 0;
			return;
		}
		iTime = 1;
	}
}

/************************************************************************/
/* Function Name: WriteLogInfo                                          */
/* Function		: д��Log��Ϣ				                            */
/* Parameter	: char* pLogInfo <I> : ��д���Log��Ϣ                  */
/* Return Value	: void��                                                */
/* Date			: 2014/01/03                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void WriteLogInfo(char* pLogInfo)
{
	//[[[ ˵����������ֻ�������ã��������á�]]]

	//[ ��Log�ļ�]
	int iRet = 0;
	short sCanWriteLog = 0;
	FILE* pFile = NULL;

	//[ ����д�����Ϣ�Ƿ�Ϸ�]
	if(NULL == pLogInfo)
	{
		//[ ��Ϣ���Ϸ�]
		//[ ��������]
		return;
	}

	//[ ����Ƿ�����ЩLog��Ϣ]
	//[ ����#9622�� bit4-7��Ϊ0������bit4-7Ϊ0��������]
	//[ ����#9622�Ĵ����ֺţ�123��С���ֺţ�22]
	iRet = getNCData(M_SEC_UPRM_HOST_LINK, M_SSEC_UPHLNK_LPOLLTM, SYS_NO_1, 0, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sCanWriteLog);
	if( (0 != iRet) || (0 == (sCanWriteLog & 0xF0)) )
	{
		//[ ȡ��ʧ�ܣ���������]
		return;
	} 

	//[ ���Log�ļ��Ƿ����]
	//[ ����������򴴽�]
	pFile = fopen(LOG_FILE_NAME, "r");
	//[ ����Ƿ񴴽��ɹ�]
	if(NULL == pFile)
	{
		//[ ����ʧ��]
		iCount = 0;
	}
	else
	{
		//[ �ر��ļ�]
		fclose(pFile);
		pFile = NULL;
	}

	//[ ���Log��Ϣ������]
	iCount = iCount + 1;
	if(iCount > MAX_LOG_COUNT)
	{
		//[ ���������������200]
		//[ ��������]
		return;
	}

	//[ ����־�ļ�]
	//[ ����������򴴽�]
	pFile = fopen(LOG_FILE_NAME, "r+");
	//[ ����Ƿ񴴽��ɹ�]
	if(NULL == pFile)
	{
		//[ ����ʧ��]
		return;
	}

	//[ д����־��Ϣ]
	fseek(pFile, 0, SEEK_END);
	fputs(pLogInfo, pFile);

	//[ �ر�]
	fclose(pFile);
}

/************************************************************************/
/* Function Name: WriteLastErrInfo                                      */
/* Function		: д�����������Ϣ			                            */
/* Parameter	: void									                */
/* Return Value	: void��                                                */
/* Date			: 2014/01/03                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void WriteLastErrInfo(char* pInfoName)
{
	//[[[ ˵����������ֻ�������ã��������á�]]]

	//[ ��������]
	int iRet = 0;
	char cBuff[BUFF_SIZE];

	//[ �����������Ϸ���]
	if(NULL == pInfoName)
	{
		//[ �����Ƿ�]
		return;
	}

	//[ ȡ�����������Ϣ]
	bzero(cBuff, BUFF_SIZE);
	iRet = errnoGet();
	sprintf(cBuff, "%s err=%d\n", pInfoName, iRet);

	//[ �������Log��Ϣ]
	WriteLogInfo(cBuff);
}

/************************************************************************/
/* Function Name: WriteLogInfoBin                                       */
/* Function		: д������Ƶ�Log��Ϣ		                            */
/* Parameter	: char* pLogInfo <I> : ��д���Log��Ϣ                  */
/*				  int iLen <I> : Log��Ϣ�ĳ���		                    */
/* Return Value	: void��                                                */
/* Date			: 2014/01/03                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void WriteLogInfoBin(char* pLogInfo, int iLen)
{
	//[[[ ��ASCII��ת���ɿɼ��ַ�			]]]
	//[[[ ˵����������ֻ�������ã��������á�]]]

	//[ ����ѭ������ʱ����]
	int iIdx = 0;

	//[ �����������Ϸ���]
	if(NULL == pLogInfo)
	{
		//[ �����Ƿ�]
		return;
	}

	//[ ѭ��ת��]
	for(iIdx = 0; (iIdx < iLen) && (0 != pLogInfo[iIdx]); iIdx = iIdx + 1)
	{
		pLogInfo[iIdx] = pLogInfo[iIdx] + 48;
	}

	//[ ���Log��Ϣ]
	WriteLogInfo(pLogInfo);
}
