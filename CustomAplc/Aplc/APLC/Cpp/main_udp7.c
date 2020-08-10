/************************************************************************/
/*                                                                      */
/* File Name: main.c                                                    */
/* Function : APLC端做成，实现和Java的通信                              */
/*            1.APLC版本的获取                                          */
/*            2.单个大小区分号数据的获取                                */
/*            3.NC文件的读取                                            */
/*            4.多个大小区分号数据的获取                                */
/* Date     : 2014/01/10                                                */
/* Code By  : lisc	                                                    */
/* Copyright: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION			*/
/*                                                                      */
/************************************************************************/
/* 更新履历:   
2014.01.10 lisc : 
	由于机械坐标更新速度非常慢，客户的体验不好，同时不能支持多台手机
	同时查看坐标信息，因此将面向连接的TCP/IP通信方式修改为面向非连接
	的broadcast及UDP/IP通信方式。一方面可以	减少通讯连接等处理时间，
	加快坐标的显示更新速度，同时可以支持多	台手机客户端同时显示相关
	的NC信息。
*/              

#include "vxWorks.h"
#include <stdio.h>
#include <stdlib.h>       /* exit() */
#include <string.h>       /* bzero() */
#include <sys/types.h>
#include <netinet/in.h>   /* htons() */
#include <unistd.h>
#include <time.h>

//[ 宏定义]
#define BUFF_SIZE				1024			//[ 缓冲区大小							]
#define BC_SERVER_PORT			8820			//[ 广播端口号							]
#define BC_SERVER_ADDR			"192.168.1.255"	//[ 广播地址							]
#define UDP_SERVER_PORT			8823			//[ UDP端口号							]

//[ 系统号]
#define SYS_NO_1				1				//[ 第1系统								]
#define SYS_NO_2				2				//[ 第2系统								]
#define SYS_NO_3				3				//[ 第3系统								]
#define SYS_NO_4				4				//[ 第4系统								]
#define SYS_NO_5				5				//[ 第5系统								]
#define SYS_NO_6				6				//[ 第6系统								]
#define SYS_NO_7				7				//[ 第7系统								]
#define SYS_NO_8				8				//[ 第8系统								]

//[ 轴号]
#define AXIS_NO_1				1				//[ 第1轴								]
#define AXIS_NO_2				2				//[ 第2轴								]
#define AXIS_NO_3				3				//[ 第3轴								]
#define AXIS_NO_4				4				//[ 第4轴								]
#define AXIS_NO_5				5				//[ 第5轴								]
#define AXIS_NO_6				6				//[ 第6轴								]
#define AXIS_NO_7				7				//[ 第7轴								]
#define AXIS_NO_8				8				//[ 第8轴								]

//[ APLC版本号]
#define DEV_R_APLC_VER_0        240             //[ APLC版本寄存器：R240的定义			]
#define DEV_R_APLC_VER_1        241             //[ APLC版本寄存器：R241的定义			]
#define DEV_R_APLC_VER_2        242             //[ APLC版本寄存器：R242的定义			]
#define DEV_R_APLC_VER_3        243             //[ APLC版本寄存器：R243的定义			]

//[ 收发类型]
#define SD_RECEIVE				0x00
#define SD_SEND					0x01
#define SD_BOTH         		0x02

//[ 数据类型]
#define T_CHAR                  0x01
#define T_SHORT                 0x02
#define T_LONG                  0x03
#define T_DOUBLE                0x05
#define T_STR                   0x10

//[ 数据精度]
#define DOUBLE_PREC             0x03             //[ 定义CustomAPI获取数据的数据类型	]
#define ADR_BASE_SYSTEM         0x01             //[ 定义CustomAPI获取数据的系统号		]

//[ 通信指令的宏定义 */
#define CMD_TYPE_NULL			0				//[ 空指令								]
#define CMD_TYPE_NAME_VER		1				//[ 获取APLC版本指令					]
#define CMD_TYPE_NC_DATA		2				//[ 获取单个NC数据指令					]
#define CMD_TYPE_NC_FILE		3				//[ 获取NC文件数据指令					]

//[ 数据类型]
#define DT_INVALID				'0'				//[ 无效数据类型						]

#define DT_IPADDR				'I'				//[ IP地址								]
#define DT_UINT_NAME			'A'				//[ NC名称								]
#define DT_WARNING				'W'				//[ 报警信息							]
#define DT_AXIS_NAME			'X'				//[ 轴名称								]
#define DT_CUR_POS				'C'				//[ 当前位置							]
#define DT_PRG_O				'O'				//[ 加工程序：O							]
#define DT_PRG_F				'F'				//[ 加工程序：F							]
#define DT_PRG_M				'M'				//[ 加工程序：M							]
#define DT_PRG_S				'S'				//[ 加工程序：S							]
#define DT_PRG_T				'T'				//[ 加工程序：T							]
#define DT_MEM_MODE				'D'				//[ 内存模式							]
#define DT_WORK_NUM				'N'				//[ 工件数								]
#define DT_AUTO_RUN				'R'				//[ 循环启动中							]
#define DT_KEEP_PROGRESS		'P'				//[ 进给保持							]
#define DT_STEP_STOP			'E'				//[ 单段停止							]
#define DT_NC_STATUS			'U'				//[ NC状态-取报警						]

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

//[ 获取指令的类型]
const char* pCmdType      = "CMD=%d;";
//[ 从大小区分号读取数据的格式]
const char* pNcDataFormat = "CMD=%d;SysNo=%d;Sect=%d;SubSect=%d;Axis=%d;";
//[ 读文件的格式]
const char* pPathFormat   = "CMD=%d;Path=%s;";
//[ 获取机械坐标相关数据]
const char* pSerialFormat = "CMD=%d;iType=%d;SysNo=%d;Sect=%d;SubSect=%d;Axis=%d;";
//[ 广播数据格式]
const char* pBCDataFmt = "%c%c%s;";
const char* pBCDataFmt0 = "%c%s;";
const char* pBCDataFmt1 = "%c%c;";
const char* pBCDataFmt2 = "%s|";

//[ 定义最大Log数量]
#define MAX_LOG_COUNT			100
//[ log文件全路径]
#define LOG_FILE_NAME			"M01:\\PRG\\USER\\APLCDEBUG"
//[ ASSEMBLY.INF]
#define SYS_INF_FILE			"M01:\\DGN\\ASSEMBLY.INF"

//[ 结构体定义]
typedef struct 
{
	long lBuffSize;				//[ 从NC端读取数据的大小				]
	char cDataBuf[BUFF_SIZE];	//[ 保存从NC端获取的数据				]
} STRINGTYPE;

//[ 数据结构]
typedef struct 
{
	char	cDataType;			//[ 数据类型							]
	char	cSubType;			//[ 数据子类型							]
	int		iSecNo;				//[ 大区分号							]
	int		iSecSubNo;			//[ 小区分号							]
	int		iSysNo;				//[ 系统号								]
	int		iAxisNo;			//[ 轴号								]
	BOOL	bCheckAxisNum;		//[ 是否检查轴的合法性					]
}STSECINFO;

//[ 全局变量定义]
int iTime = 0;					//[ 控制主函数只执行一次，内部无限循环	]
int iCount = 0;					//[ 控制Log信息的数量					]
int	bcSocket = 0;				//[ 广播socket							]
int udpSocket = 0;				//[ 接收socket							]
fd_set	ReadFds = {0};			//[ udp通讯socket管理结构体				]
char cNcBasicInfo[BUFF_SIZE];	//[ 存储NC的基本信息					]
struct timespec g_tpCycTime;	//[ 存储广播周期开始时间				]

//[ 待取数据列表]
STSECINFO g_stSecData[] = 
{
	// 数据类型			数据子类型			大区分	小区分			系统号	轴号		是否检查轴的合法性
	// cDataType		cSubType			iSecNo	iSecSubNo		iSysNo	iAxisNo		bCheckAxisNum
	//-----------------------------------------------------------------------------------------------------------------------
	{DT_IPADDR,			NO_SUB_NUMBER,		124,	2,				0,		0,			FALSE	},		//[ IP地址			]

	//[ 报警信息]
	{DT_WARNING,		DT_WARNING_01,		53,		1 + 0x0C98,		0,		0,			FALSE	},		//[ 系统报警($1)	]
	{DT_WARNING,		DT_WARNING_02,		53,		1 + 0x0DD8,		0,		0,			FALSE	},		//[ 系统报警($2)	]
	{DT_WARNING,		DT_WARNING_03,		53,		1 + 0x0F18,		0,		0,			FALSE	},		//[ 系统报警($3)	]
	{DT_WARNING,		DT_WARNING_04,		53,		1 + 0x1058,		0,		0,			FALSE	},		//[ 系统报警($4)	]
	{DT_WARNING,		DT_WARNING_05,		53,		1 + 0x0C99,		0,		0,			FALSE	},		//[ 伺服报警($1)	]
	{DT_WARNING,		DT_WARNING_06,		53,		1 + 0x0DD9,		0,		0,			FALSE	},		//[ 伺服报警($2)	]
	{DT_WARNING,		DT_WARNING_07,		53,		1 + 0x0F19,		0,		0,			FALSE	},		//[ 伺服报警($3)	]
	{DT_WARNING,		DT_WARNING_08,		53,		1 + 0x1059,		0,		0,			FALSE	},		//[ 伺服报警($4)	]
	{DT_WARNING,		DT_WARNING_09,		53,		1 + 0x0C9A,		0,		0,			FALSE	},		//[ 程序报警($1)	]
	{DT_WARNING,		DT_WARNING_10,		53,		1 + 0x0DDA,		0,		0,			FALSE	},		//[ 程序报警($2)	]
	{DT_WARNING,		DT_WARNING_11,		53,		1 + 0x0F1A,		0,		0,			FALSE	},		//[ 程序报警($3)	]
	{DT_WARNING,		DT_WARNING_12,		53,		1 + 0x105A,		0,		0,			FALSE	},		//[ 程序报警($4)	]
	{DT_WARNING,		DT_WARNING_13,		53,		1 + 0x0C9B,		0,		0,			FALSE	},		//[ 操作报警($1)	]
	{DT_WARNING,		DT_WARNING_14,		53,		1 + 0x0DDB,		0,		0,			FALSE	},		//[ 操作报警($2)	]
	{DT_WARNING,		DT_WARNING_15,		53,		1 + 0x0F1B,		0,		0,			FALSE	},		//[ 操作报警($3)	]
	{DT_WARNING,		DT_WARNING_16,		53,		1 + 0x105B,		0,		0,			FALSE	},		//[ 操作报警($4)	]
	{DT_WARNING,		DT_WARNING_17,		53,		1 + 0x0CB1,		0,		0,			FALSE	},		//[ 操作报警($1)	]
	{DT_WARNING,		DT_WARNING_18,		53,		1 + 0x0DF1,		0,		0,			FALSE	},		//[ 操作报警($2)	]
	{DT_WARNING,		DT_WARNING_19,		53,		1 + 0x0F31,		0,		0,			FALSE	},		//[ 操作报警($3)	]
	{DT_WARNING,		DT_WARNING_20,		53,		1 + 0x1071,		0,		0,			FALSE	},		//[ 操作报警($4)	]
	{DT_WARNING,		DT_WARNING_21,		53,		1 + 0x0C9C,		0,		0,			FALSE	},		//[ 伺服警告($1)	]
	{DT_WARNING,		DT_WARNING_22,		53,		1 + 0x0DDC,		0,		0,			FALSE	},		//[ 伺服警告($2)	]
	{DT_WARNING,		DT_WARNING_23,		53,		1 + 0x0F1C,		0,		0,			FALSE	},		//[ 伺服警告($3)	]
	{DT_WARNING,		DT_WARNING_24,		53,		1 + 0x105C,		0,		0,			FALSE	},		//[ 伺服警告($4)	]
	{DT_WARNING,		DT_WARNING_25,		55,		100069,			0,		0,			FALSE	},		//[ 紧急停止		]

	//[ 轴名称信息]
	{DT_AXIS_NAME,		DT_AXIS_NO_01,		127,	2,				1,		1,			TRUE	},		//[ 第1轴表示名称	]
	{DT_AXIS_NAME,		DT_AXIS_NO_02,		127,	2,				1,		2,			TRUE	},		//[ 第2轴表示名称	]
	{DT_AXIS_NAME,		DT_AXIS_NO_03,		127,	2,				1,		3,			TRUE	},		//[ 第3轴表示名称	]
	{DT_AXIS_NAME,		DT_AXIS_NO_04,		127,	2,				1,		4,			TRUE	},		//[ 第4轴表示名称	]
	{DT_AXIS_NAME,		DT_AXIS_NO_05,		127,	2,				1,		5,			TRUE	},		//[ 第5轴表示名称	]
	{DT_AXIS_NAME,		DT_AXIS_NO_06,		127,	2,				1,		6,			TRUE	},		//[ 第6轴表示名称	]
	{DT_AXIS_NAME,		DT_AXIS_NO_07,		127,	2,				1,		7,			TRUE	},		//[ 第7轴表示名称	]
	{DT_AXIS_NAME,		DT_AXIS_NO_08,		127,	2,				1,		8,			TRUE	},		//[ 第8轴表示名称	]

	//[ 当前位置信息]
	{DT_CUR_POS,		DT_AXIS_NO_01,		37,		3,				1,		1,			TRUE	},		//[ 第1轴当前位置	]
	{DT_CUR_POS,		DT_AXIS_NO_02,		37,		3,				1,		2,			TRUE	},		//[ 第2轴当前位置	]
	{DT_CUR_POS,		DT_AXIS_NO_03,		37,		3,				1,		3,			TRUE	},		//[ 第3轴当前位置	]
	{DT_CUR_POS,		DT_AXIS_NO_04,		37,		3,				1,		4,			TRUE	},		//[ 第4轴当前位置	]
	{DT_CUR_POS,		DT_AXIS_NO_05,		37,		3,				1,		5,			TRUE	},		//[ 第5轴当前位置	]
	{DT_CUR_POS,		DT_AXIS_NO_06,		37,		3,				1,		6,			TRUE	},		//[ 第6轴当前位置	]
	{DT_CUR_POS,		DT_AXIS_NO_07,		37,		3,				1,		7,			TRUE	},		//[ 第7轴当前位置	]
	{DT_CUR_POS,		DT_AXIS_NO_08,		37,		3,				1,		8,			TRUE	},		//[ 第8轴当前位置	]

	//[ 其他信息]
	{DT_PRG_O,			NO_SUB_NUMBER,		46,		2,				1,		0,			FALSE	},		//[加工程序：O		]
	{DT_PRG_F,			NO_SUB_NUMBER,		33,		1,				1,		0,			FALSE	},		//[加工程序：F		]
	{DT_PRG_M,			NO_SUB_NUMBER,		38,		1,				1,		0,			FALSE	},		//[加工程序：M		]
	{DT_PRG_S,			NO_SUB_NUMBER,		38,		101,			0,		1,			FALSE	},		//[加工程序：S		]
	{DT_PRG_T,			NO_SUB_NUMBER,		38,		201,			1,		0,			FALSE	},		//[加工程序：T		]
	{DT_MEM_MODE,		NO_SUB_NUMBER,		35,		11,				1,		0,			FALSE	},		//[NC内存模式		]
	{DT_WORK_NUM,		NO_SUB_NUMBER,		126,	8002,			1,		0,			FALSE	},		//[工件数量			]
	{DT_AUTO_RUN,		NO_SUB_NUMBER,		35,		20,				1,		0,			FALSE	},		//[循环启动中		]
	{DT_KEEP_PROGRESS,	NO_SUB_NUMBER,		35,		22,				1,		0,			FALSE	},		//[进给保持			]
	{DT_STEP_STOP,		NO_SUB_NUMBER,		53,		13090,			0,		0,			FALSE	},		//[单段停止			]
	{DT_NC_STATUS,		NO_SUB_NUMBER,		35,		10,				1,		0,			FALSE	},		//[NC状态-取报警	]
	{DT_UINT_NAME,		NO_SUB_NUMBER,		126,	135,			0,		0,			FALSE	},		//[NC名称(#1135)	]

	//[ 结束标识信息]
	{DT_INVALID,		NO_SUB_NUMBER,		0,		0,				0,		0,			FALSE	},		//[结束				]
};

//[[ 函数声明]]
//[ APLC初始化函数]
extern void aplc_top();	
//[ APLC主函数]
extern void base_Main();

//[[ 数据处理函数]]
//[ 设置APLC版本号]
void SetAplcVer();
//[ 取得机械位置坐标]
int GetXYData(int iSys, char* cBuffer);
//[ 取得监视界面的信息]
int GetMonitorData(int iSys, char* cBuffer);
//[ 取得NC基本信息]
int GetNcBasicInfo();

//[ UDP/IP模式]
//[ 取得命令]
int GetCmdID(char* cCmd);
//[ 发送APLC sokcet版本号]
void SendAplcVer(struct sockaddr * pAddr);
//[ 获取单个大小区分号数据]
void SendNCData(struct sockaddr * pAddr, char* cBuf);
//[ 发送客户端请求文件]
void SendNCFile(struct sockaddr * pAddr, char* cBuf);

//[[ 通讯函数]]
//[ 关闭广播socket]
void CloseBcSocket();
//[ 创建广播socket]
int CreateBcSocket();
//[ 广播数据]
int BroadcastData();
//[ 关闭udp socket]
void CloseUdpSocket();
//[ 创建udp socket]
int CreateUdpSocket();
//[ udp通信]
int DoUdpCommunicate();

//[[ Log函数]]
//[ 记录Log信息]
void WriteLogInfo(char* pLogInfo);
//[ 记录Log信息]
void WriteLastErrInfo(char* pInfoName);
//[ 记录Log信息]
void WriteLogInfoBin(char* pLogInfo, int iLen);

/************************************************************************/
/* Function Name: GetCmdID                                              */
/* Function		: 取得客户端的命令			                            */
/* Parameter	: char* cCmd <I> : 客户端的命令字符串                   */
/* Return Value	: void　                                                */
/* Date			: 2014/01/03                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
int GetCmdID(char* cCmd)
{
	//[[[ 取得客户端请求的命令]]]

	//[ 命令变量定义]
	int iCmd = CMD_TYPE_NULL;

	//[ 检查输入是否合法]
	if(NULL == cCmd)
	{
		//[ 非法]
		//[ 返回非法指令]
		return iCmd;
	}

	//[ 取得客户端发来的指令]
	sscanf(cCmd, pCmdType, &iCmd);

	//[ 返回取得的命令]
	return iCmd;
}

/************************************************************************/
/* Function Name: SendAplcVer											*/
/* Function		:  取得aplc socket的版本                                */
/* Parameter	: struct sockaddr * pAddr <I> : 客户端地址              */
/* Return Value	: void　                                                */
/* Date			: 2014/01/07                                            */
/* Code By		: lisc                                                  */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void SendAplcVer(struct sockaddr * pAddr)
{
	//[[[ 向请求客户端发送APLC的版本号]]]

	//[[ 初始化接收APLC版本信息的临时变量]]
	short sR240 = 0;			//[ 初始化R240的数据	]
	short sR241 = 0;			//[ 初始化R241的数据	]
	short sR242 = 0;			//[ 初始化R242的数据	]
	short sR243 = 0;			//[ 初始化R243的数据	]
	char cBuff[BUFF_SIZE];		//[ APLC版本的定义		]
	int iRet = 0;

	//[ 初始化临时缓存]
	memset(cBuff, 0, sizeof(cBuff));/* APLC版本的初始化 */
	//[ 获取R240数据]
	melplcWtstR(DEV_R_APLC_VER_0, &sR240);
	//[ 获取R241数据]
	melplcWtstR(DEV_R_APLC_VER_1, &sR241);
	//[ 获取R242数据]
	melplcWtstR(DEV_R_APLC_VER_2, &sR242);
	//[ 获取R243数据]
	melplcWtstR(DEV_R_APLC_VER_3, &sR243);

	//[ 组合发送内容 APLC版本]
	sprintf(cBuff,"%s%04d%s%03d%s%c%c%c","BND-",sR240,"W",sR241,"-",
		sR242 & 0x00FF, (sR242 >> 8) & 0x00FF, sR243 & 0x00FF);

	//[ 发送APLC版本]
	iRet = sendto(bcSocket, cBuff, strlen(cBuff), 0, pAddr, sizeof(struct sockaddr));
	if(iRet <= 0)
	{
		//[ 发送失败]
		WriteLastErrInfo("SendAplcVer::sendto");
	}
	else
	{
		//[ 发送成功]
		WriteLogInfo("aplc ver:");
		WriteLogInfo(cBuff);
		WriteLogInfo("\n");
	}
}

/************************************************************************/
/* Function Name: SendNCData		                                    */
/* Function		: 获取单个大小区分号数据                                */
/* Parameter	: struct sockaddr * pAddr <I> : 客户端地址              */
/*				  char* buf <I> :  接收的数据							*/
/* Return Value	: void　                                                */
/* Date			: 2014/01/07                                            */
/* Code By		: lisc                                                  */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void SendNCData(struct sockaddr * pAddr, char* cBuf)
{
	//[[[ 向客户端发送指定请求（大小区分号、系统号、轴号）的数据]]]
	int iCmd = CMD_TYPE_NULL;  //[ 指令类型的定义		]
	int iSysNo = 0;            //[ 系统号				]
	int iSect = 0;             //[ 大区分				]
	int iSubSect = 0;          //[ 小区分				]
	int iAxis = 0;             //[ 轴号					]
	STRINGTYPE GetStrType;     //[ 获取的数据			]
	long iRet = 0;             //[ getNCData函数的返回值]
	char cBuff[BUFF_SIZE];

	//[ 数据的缓冲区大小]
	GetStrType.lBuffSize = sizeof (GetStrType.cDataBuf);
	//[ 列表初始化]
	memset(GetStrType.cDataBuf, 0, sizeof(GetStrType.cDataBuf));
	//[ 指令类型、格式数据分析]
	sscanf(cBuf, pNcDataFormat, &iCmd, &iSysNo, &iSect, &iSubSect, &iAxis);

	//[ 获取数据]
	iRet = getNCData(iSect, iSubSect, iSysNo, iAxis, ADR_BASE_SYSTEM, T_STR, DOUBLE_PREC, &GetStrType);
	if(0 == iRet)
	{
		//[ 数据取得成功]

		//[ 下面的 getNCData 结果信息不发送]
		//[ 发送获取数据的返回值]
		iRet = sendto(bcSocket, (char*)&iRet, sizeof(iRet), 0, pAddr, sizeof(struct sockaddr));
		if(iRet <= 0)
		{
			//[ 发送失败]
			WriteLastErrInfo("SendNCData::getNCData:NG\n");
		}
		else
		{
			//[ 发送成功]
			WriteLogInfo("SendNCData::getNCData:OK\n");
		}

		//[ 发送数据]
		iRet = sendto(bcSocket, GetStrType.cDataBuf, GetStrType.lBuffSize, 0, pAddr, sizeof(struct sockaddr));
		if(iRet <= 0)
		{
			//[ 发送失败]
			WriteLastErrInfo("SendNCData::sendto:NG\n");
		}
		else
		{
			//[ 输出sendto信息]
			WriteLogInfo("<reply:");
			WriteLogInfoBin(GetStrType.cDataBuf, GetStrType.lBuffSize);
			WriteLogInfo(">\n");
		}
	}
	else
	{
		//[ 取得数据失败]
		WriteLogInfo("SendNCData::getNCData:NG\n");
	}
}

/************************************************************************/
/* Function Name: SendNCFile		                                    */
/* Function		: 读文件的处理函数		                                */
/* Parameter	: struct sockaddr * pAddr <I> : 客户端地址              */
/*				  char* buf <I> :  接收的数据							*/
/* Return Value	: void　                                                */
/* Date			: 2014/01/07                                            */
/* Code By		: lisc                                                  */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void SendNCFile(struct sockaddr * pAddr, char* cBuf)
{
	//[[[ 向客户端发送请求的文件信息]]]

	//[[ 临时变量定义]]
	int iCmd = CMD_TYPE_NULL;        //[ 指令类型的定义			]
	char path[BUFF_SIZE];              //[ 文件的路径				]
	char senddata[BUFF_SIZE];          //[ 发送的缓冲区数据		]
	FILE * fFile = 0;                //[ 文件					]
	long  nLen = 0;                  //[ 一次发送数据的长度		]
	int iRet = 0;                    //[ SendNCFile函数的返回值 ]

	//[ 初始化path ]
	bzero(path, BUFF_SIZE);
	//[ 获取文件路径和指令 ]
	sscanf(cBuf, pPathFormat, &iCmd, path);
	//[ 打开文件 ]
	fFile  = fopen(path, "r");
	//[ 文件打开失败，下次再次连接 ]
	//[ 返回值的设定 ]
	iRet = 1;
	if (!fFile)
	{
		iRet = 0;
	}
	//[ 发送文件打开结果 ]
	iRet = sendto(bcSocket, (char*)&iRet, sizeof(iRet), 0, pAddr, sizeof(struct sockaddr));
	if(iRet <= 0)
	{
		//[ 发送失败]
		WriteLastErrInfo("SendNCFile::sendto::iRet");
	}
	//[ 文件打开失败]
	if (!fFile)
	{
		//[ 直接返回]
		return;
	}

	//] 循环发送文件数据 ]
	do
	{
		//[ 一次以最大的byte数发送 ]
		nLen = fread(senddata, sizeof(char), BUFF_SIZE, fFile);

		//[ 发送数据 ]
		iRet = sendto(bcSocket, senddata, nLen, 0, pAddr, sizeof(struct sockaddr));
		if(iRet <= 0)
		{
			//[ 发送失败]
			WriteLastErrInfo("SendNCFile::sendto::File");
		}
	} while (nLen == BUFF_SIZE);

	//[ 关闭文件 ]
	fclose(fFile);
}

/************************************************************************/
/* Function Name: aplc_top                                              */
/* Function		: APLC初始化函数		                                */
/* Parameter	: null                                                  */
/* Return Value	: void                                                  */
/* Date			: 2014/01/03                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void aplc_top(void)
{
	//[ 设置APLC的版本 ]
    SetAplcVer();

    //[ APLC非同期处理的登录 ]
    setUserBaseMain(base_Main);
}

/************************************************************************/
/* Function Name: CloseBcSocket			                                */
/* Function		: 关闭广播socket		                                */
/* Parameter	: void							                        */
/* Return Value	: void　                                                */
/* Date			: 2014/01/07                                            */
/* Code By		: lisc                                                  */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void CloseBcSocket()
{
	//[ 检查socket是否存在]
	int iRet = 0;
	if (bcSocket <= 0) 
	{
		//[ 不存在]
		//[ 不用关闭，直接返回]
		return;
	}

	//[ 关闭socket]
	shutdown(bcSocket, SD_BOTH);
	bcSocket = 0;

	WriteLogInfo("CloseBcSocket\n");
}

/************************************************************************/
/* Function Name: CreateBcSocket			                            */
/* Function		: 创建广播socket		                                */
/* Parameter	: void							                        */
/* Return Value	: void　                                                */
/* Date			: 2014/01/07                                            */
/* Code By		: lisc                                                  */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
int CreateBcSocket()
{
	//[ 函数返回值及广播标识符初始变量定义]
	int iRet = 0;
	BOOL yes = TRUE;

	//[ 关闭旧的socket]
	CloseBcSocket();

	//[ 创建新的socket]
	bcSocket = socket(AF_INET, SOCK_DGRAM, 0);
	//[ 检查是否创建成功]
	if (bcSocket < 0) 
	{
		//[ 创建失败]
		WriteLastErrInfo("CreateBcSocket::socket");
		return -1;
	}

	//[ 创建成功]
	//[ 设置socket为广播socket]
	iRet = setsockopt(bcSocket, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));
	if (iRet != 0 ) 
	{
		//[ 设置失败]
		WriteLastErrInfo("CreateBcSocket::setsockopt");
		return -1;
	}

	//[ 返回创建成功]
	return 0;
}

/************************************************************************/
/* Function Name: BroadcastData                                         */
/* Function		: 广播数据(机械位置坐标)	                            */
/* Parameter	: null                                                  */
/* Return Value	: void　                                                */
/* Date			: 2014/01/03                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
int BroadcastData()
{
	char cBuff[BUFF_SIZE];				//[ 临时缓存		]
	struct sockaddr_in addrto;			//[ 广播地址		]
	int nlen = sizeof(addrto);			//[ 广播地址长度	]
	int iRet = 0;
	int iDataLen = 0;

	//[ 设置广播地址]
	addrto.sin_family = AF_INET;
	addrto.sin_addr.s_addr = inet_addr(BC_SERVER_ADDR);
	addrto.sin_port = htons(BC_SERVER_PORT);

	//[ 取得坐标]
	bzero(cBuff, BUFF_SIZE);
	//if(0 == GetXYData(SYS_NO_1, cBuff))
	if(0 == GetMonitorData(SYS_NO_1, cBuff))
	{
		//[ 发送坐标]
		iDataLen = strlen(cBuff);
		iRet = sendto(bcSocket, cBuff, iDataLen, 0, (struct sockaddr*)&addrto, nlen);
		if(iRet <= 0)
		{
			//[ 发送失败]
			WriteLastErrInfo("BroadcastData::sendto");
		}
		else
		{
			//[ 发送成功]
			//bzero(cBuff, BUFF_SIZE);
			//sprintf(cBuff, "%dB of %dB sent\n", iRet, iDataLen);
			WriteLogInfo(cBuff);
			WriteLogInfo("\n");
		}
	}
	else
	{
		//[ 取得坐标失败]
		WriteLogInfo("Failed to get xyz\n");
	}
}

/************************************************************************/
/* Function Name: CloseUdpSocket			                            */
/* Function		: 关闭udp socket		                                */
/* Parameter	: void							                        */
/* Return Value	: void　                                                */
/* Date			: 2014/01/07                                            */
/* Code By		: lisc                                                  */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void CloseUdpSocket()
{
	//[ 检查socket是否存在]
	int iRet = 0;
	if (udpSocket <= 0) 
	{
		//[ 不存在]
		//[ 直接返回]
		return;
	}

	//[ 清楚socket 与 通讯标识符结构体的关系]
	FD_CLR(udpSocket, &ReadFds);

	//[ 关闭socket]
	shutdown(udpSocket, SD_BOTH);
	udpSocket = 0;

	WriteLogInfo("CloseUdpSocket\n");
}

/************************************************************************/
/* Function Name: CloseUdpSocket			                            */
/* Function		: 创建udp socket		                                */
/* Parameter	: void							                        */
/* Return Value	: void　                                                */
/* Date			: 2014/01/07                                            */
/* Code By		: lisc                                                  */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
int CreateUdpSocket()
{
	//[ 定义函数返回值、udp地址及临时缓存]
	int iRet = 0;
	struct sockaddr_in addr;
	char cBuff[BUFF_SIZE];

	//[ 关闭旧的udp socket]
	CloseUdpSocket();

	//[ 创建udp socket]
	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (udpSocket < 0) 
	{
		//[ 创建失败]
		//[ 返回失败]
		WriteLastErrInfo("CreateUdpSocket::socket");
		return -1;
	}

	//[ 设置udp地址信息]
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(UDP_SERVER_PORT);

	//[ 绑定udp socket和udp地址]
	iRet = bind(udpSocket, (struct sockaddr *)&addr, sizeof(addr));
	if (iRet < 0) 
	{
		//[ 绑定失败]
		WriteLastErrInfo("CreateUdpSocket::bind");
		//[ 返回失败]
		return -1;
	}

	//[ 返回创建成功]
	return 0;
}

/************************************************************************/
/* Function Name: DoUdpCommunicate	                                    */
/* Function		: udp通信				                                */
/* Parameter	: void							                        */
/* Return Value	: void　                                                */
/* Date			: 2014/01/07                                            */
/* Code By		: lisc                                                  */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
int DoUdpCommunicate()
{
	//[[[ 执行UDP通讯]]]

	//[ 定义通讯中用到的临时变量]
	int iCmd = CMD_TYPE_NULL;				//[ 命令类型			]
	int iRet = 0;							//[ 函数返回值			]
	struct sockaddr_in addrFrom;			//[ 客户端地址			]
	int addrLen = sizeof(addrFrom);			//[ 客户端地址长度		]
	char cBuff[BUFF_SIZE];					//[ 临时缓存			]
	struct timeval timeout = {0, 1000};		//[ 超时时间			]

	//[ 设置socket的超时时间]
	memset(&addrFrom, 0, sizeof(addrFrom));
	bzero(cBuff, BUFF_SIZE);
	//[ fd和socket关联]
	FD_SET(udpSocket, &ReadFds);
	//[ timeout的socket信号等待连接]
	iRet = select(FD_SETSIZE, &ReadFds, (fd_set *)0, (fd_set *)0, &timeout);
	//[ timeout的error时的的处理]
	if (iRet < 0)
	{
		//[ 设置超时时间失败]
		return -1;
	}

	//[ 检查select是否time expired]
	if(0 == iRet)
	{
		//[ 返回处理完成]
		return 0;
	}
	
	//[ 检查udpSocket是否有有效的信号]
	if(FD_ISSET(udpSocket, &ReadFds))
	{
		//[ 有有效信号]
		//[ 从客户端收取请求命令]
		iRet = recvfrom(udpSocket, (char *)&cBuff, sizeof(cBuff), 0, (struct sockaddr *)&addrFrom, &addrLen);
		//[ 检查接收的结果是否有效]
		if (iRet <= 0) 
		{
			//[ 无效]
			WriteLastErrInfo("DoUdpCommunicate::recvfrom");
			//[ 返回错误]
			return -1;
		}
		else
		{
			//[ 输出收到的请求指令]
			WriteLogInfo("<from:");
			WriteLogInfo(cBuff);
			WriteLogInfo(">\n");

			//[ 取得客户端的请求指令]
			iCmd = GetCmdID(cBuff);

			//[ 根据命令进行相应的动作]
			switch(iCmd)
			{
			//[ 客户端申请APLC socket版本号]
			case CMD_TYPE_NAME_VER:
				//[ 向客户端发送APLC socket版本号]
				SendAplcVer((struct sockaddr *)&addrFrom);
				break;

			//[ 客户端申请单个大小区分号数据]
			case CMD_TYPE_NC_DATA:
				//[ 向客户端发送单个大小区分号数据]
				SendNCData((struct sockaddr *)&addrFrom, cBuff);
				break;

			//[ 客户端申请发送文件]
			case CMD_TYPE_NC_FILE:
				//[ 向客户端发送请求的文件数据]
				SendNCFile((struct sockaddr *)&addrFrom, cBuff);
				break;

			//[ 其他请求不做处理]
			default:
				break;
			}
		}
	}
	
	//[ 返回udp通讯处理成功]
	return 0;
}

/************************************************************************/
/* Function Name: SetAplcVer                                            */
/* Function		: aplc 版本的设置                                       */
/* Parameter	: null                                                  */
/* Return Value	: void                                                  */
/* Date			: 2014/01/08                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void SetAplcVer()
{
	//[[ APLC版本号：BND-9001W001-A0B						]]
	//[[ 说明：												]]
	//[[	sR240用以设置9001（=0x2329）					]]
	//[[	sR241用以设置001 （0x0001）						]]
	//[[	sR242 bit7-0设置A0B的A （0x41:'A'的ASCII码）	]]
	//[[	sR242 bitF-8设置A0D的0 （0x41:'0'的ASCII码）	]]
	//[[	sR243 bit7-0设置A0D的D （0x44:'D'的ASCII码）	]]
	//[[	sR243 bitF-8固定设为FF，否则不能显示			]]

	//[[ 初始化APLC版本号信息]]
	short sR240 = 0x2329;    /* APLC版本：R240的设定值的定义 */
	short sR241 = 0x0001;    /* APLC版本：R241的设定值的定义 */
	short sR242 = 0x3041;    /* APLC版本：R242的设定值的定义 */
	short sR243 = 0xFF44;    /* APLC版本：R243的设定值的定义 */
	/*设置R240数据*/
	melplcWsetR(DEV_R_APLC_VER_0, sR240);
	/*设置R241数据*/
	melplcWsetR(DEV_R_APLC_VER_1, sR241);
	/*设置R242数据*/
	melplcWsetR(DEV_R_APLC_VER_2, sR242);
	/*设置R243数据*/
	melplcWsetR(DEV_R_APLC_VER_3, sR243);
}

//[ 取得NC基本信息]
/************************************************************************/
/* Function Name: GetNcBasicInfo                                        */
/* Function		: 取得NC基本信息                                        */
/* Parameter	: null                                                  */
/* Return Value	: -1 : 取得失败；不为-1：取得成功                       */
/* Date			: 2014/01/08                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
int GetNcBasicInfo()
{
	//[ 定义临时变量]
	FILE * fFile = 0;               //[ 文件					]
	int iDataLen = 0;				//[ 临时缓存大小			]
	int iTempLen = 0;				//[ 一次读取的数据长度		]
	char cBuffer[3 * BUFF_SIZE];	//[ 临时缓存大小			]

	//[ 打开文件 ]
	fFile  = fopen(SYS_INF_FILE, "r");
	//[ 文件打开失败]
	if (!fFile)
	{
		return -1;
	}

	//[ 循环发送文件数据 ]
	bzero(cBuffer, 3 * BUFF_SIZE);
	do
	{
		//[ 一次以最大的byte数发送 ]
		iTempLen = fread(&cBuffer[iDataLen], sizeof(char), BUFF_SIZE, fFile);
		iDataLen = iDataLen + iTempLen;
	} while (iTempLen == BUFF_SIZE);

	//[ 解析文件取得机种、M/L、版本号、序列号等信息]
	//[。。。。。。。。。。。。。。。。。。。。。。]

	//[ 关闭文件 ]
	fclose(fFile);

	//[ 返回取得成功]
	return 0;
}

/************************************************************************/
/* Function Name: GetXYData                                             */
/* Function		: 取得机械位置坐标                                      */
/* Parameter	: int iSys <I> : 系统号                                 */
/*				  char* cBuffer <O> : 坐标信息(格式：x坐标;y坐标;z坐标;)*/
/* Return Value	: int: 小于0-失败 0-成功                                */
/* Date			: 2014/01/03                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
int GetXYData(int iSys, char* cBuffer)
{
	//[[[ 取得指定系统的机械位置坐标]]]

	//[ 变量定义]
	STRINGTYPE stStrTypex;
	char cAxisNum = 0;
	int iIdx = 0;
	int iDataLen = 0;
	int iTempLen = 0;
	stStrTypex.lBuffSize = BUFF_SIZE;

	//[ 取得指定系统的轴数]
	if( 0 != getNCData(126, 3, iSys, 0, ADR_BASE_SYSTEM, T_CHAR, DOUBLE_PREC, &cAxisNum) )
	{
		WriteLogInfo("Failed to get Axis Num\n");
		return -1;
	}

	//[ 循环取得每根轴的坐标]
	bzero(cBuffer, BUFF_SIZE);
	for(iIdx = 0; iIdx < (int)cAxisNum; iIdx = iIdx + 1 )
	{
		//[ 取得单根轴的坐标]
		bzero(stStrTypex.cDataBuf, BUFF_SIZE);
		if( 0 == getNCData(37, 2, iSys, iIdx + 1, ADR_BASE_SYSTEM, T_STR, DOUBLE_PREC, &stStrTypex) )
		{
			//[ 取得成功]
			//[ 将取得的坐标数值复制到输出缓存中]
			iTempLen = strlen(stStrTypex.cDataBuf);
			memmove(&cBuffer[iDataLen], stStrTypex.cDataBuf, iTempLen);
			iDataLen = iDataLen + iTempLen;
			cBuffer[iDataLen] = ';';
			iDataLen = iDataLen + 1;
		}
		else
		{
			//[ 取得失败]
			WriteLogInfo("Failed to get XY\n");
			return -1;
		}
	}

	//[ 返回取得成功]
	return 0;
}

/************************************************************************/
/* Function Name: GetMonitorData                                        */
/* Function		: 取得监视界面的信息		                            */
/* Parameter	: int iSys <I> : 系统号                                 */
/*				  char* cBuffer <O> : 坐标信息(格式：x坐标;y坐标;z坐标;)*/
/* Return Value	: int: 小于0-失败 0-成功                                */
/* Date			: 2014/01/13                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
int GetMonitorData(int iSys, char* cBuffer)
{
	//[ 变量定义]
	int iIndex = 0;
	char cAxisNum = 0;
	int iSecSubNo = 0;
	int iTempLen = 0;
	int iDataLen = 0;
	STRINGTYPE stStrTypex;
	char cTempBuffer[128] = {0};

	//[ 初始化广播数据缓存]
	stStrTypex.lBuffSize = BUFF_SIZE;
	bzero(cBuffer, BUFF_SIZE);

	//[ 取得指定系统的轴数]
	if( 0 != getNCData(126, 3, iSys, 0, ADR_BASE_SYSTEM, T_CHAR, DOUBLE_PREC, &cAxisNum) )
	{
		WriteLogInfo("Failed to get Axis Num\n");
		return -1;
	}

	//[ 循环取得所有数据]
	while(DT_INVALID != g_stSecData[iIndex].cDataType)
	{
		//[ 取得数据前的预处理]
		////[ 取得小区分号]
		//iSecSubNo = g_stSecData[iIndex].iSecSubNo;

		//[ 检查是否是当前位置信息]
		if( TRUE == g_stSecData[iIndex].bCheckAxisNum )
		{
			//[ 是当前位置信息]
			//[ 检查轴是否存在]
			if(g_stSecData[iIndex].iAxisNo > ((int)cAxisNum))
			{
				//[ 不存在]
				//[ 继续下一个数据处理]
				iIndex = iIndex + 1;
				continue;
			}
		}

		//[ 取得数据]
		//[ 取得单根轴的坐标]
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
			//[ 取得成功]

			//[ 检查是否是报警信息]
			//[ 没有报警的信息不需要发送]
			if( DT_WARNING == g_stSecData[iIndex].cDataType)
			{
				if(DT_WARNING_25 == g_stSecData[iIndex].cSubType)
				{
					if(0 == strcmp(stStrTypex.cDataBuf, "FFFF"))
					{
						//[ 没有报警]
						//[ 不用发送，直接进入下一个数据处理]
						iIndex = iIndex + 1;
						continue;
					}
				}
				else
				{
					if('0' == stStrTypex.cDataBuf[0])
					{
						//[ 没有报警]
						//[ 不用发送，直接进入下一个数据处理]
						iIndex = iIndex + 1;
						continue;
					}
				}
			}

			//[ 将取得的坐标数值复制到输出缓存中]
			bzero(cTempBuffer, 128);
			if(NO_SUB_NUMBER != g_stSecData[iIndex].cSubType)
			{
				if(DT_WARNING == g_stSecData[iIndex].cDataType)
				{
					// SAMPLE: 报警信息 "W1"
					sprintf(cTempBuffer, pBCDataFmt1, g_stSecData[iIndex].cDataType, g_stSecData[iIndex].cSubType);
				}
				else
				{
					// SAMPLE: 轴名称 "X1X"
					sprintf(cTempBuffer, pBCDataFmt, g_stSecData[iIndex].cDataType, g_stSecData[iIndex].cSubType, stStrTypex.cDataBuf);
				}
			}
			else
			{
				if(DT_IPADDR == g_stSecData[iIndex].cDataType)
				{
					// SAMPLE: IP地址 "192.168.1.61|"
					sprintf(cTempBuffer, pBCDataFmt2, stStrTypex.cDataBuf);
				}
				else
				{
					// SAMPLE: NC名称 "ANME"
					sprintf(cTempBuffer, pBCDataFmt0, g_stSecData[iIndex].cDataType, stStrTypex.cDataBuf);
				}
			}
			iTempLen = strlen(cTempBuffer);
			memmove(&cBuffer[iDataLen], cTempBuffer, iTempLen);
			iDataLen = iDataLen + iTempLen;

			////[ 输出Log]
			//WriteLogInfo(cBuffer);
			//WriteLogInfo("\n");
		}
		else
		{
			//[ 取得失败]
			WriteLogInfo("Failed to get data\n");
			return -1;
		}

		//[ 将指针指向下一个数据]
		iIndex = iIndex + 1;
	}
	
	//[ 返回数据取得成功]
	return 0;
}

/************************************************************************/
/* Function Name: base_Main                                             */
/* Function		: 异步模式下的APLC主函数	                            */
/* Parameter	: null                                                  */
/* Return Value	: void　                                                */
/* Date			: 2014/01/03                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void base_Main()
{
	//[[[ 异步模式下的APLC主函数						]]]
	//[[[ 主要实现取得机械位置坐标并将其广播到网络中	]]]]

	int iRet = 0;
	short sDelay = 0;
	struct timespec tpCurCycTime;

	memset(&tpCurCycTime,0,sizeof(struct timespec));
	clock_gettime(CLOCK_REALTIME,&tpCurCycTime);

	//[ 检查是否是第一次执行该函数]
	iTime = iTime + 1;
	if(1 == iTime)
	{
		//[ 第一次执行	]
		//[ socket管理结构初始化]
		FD_ZERO(&ReadFds);

		//[ 创建broadcast的socket]
		iRet = CreateBcSocket();
		if(iRet < 0)
		{
			iTime = 0;
			return;
		}

		//[ 创建udp的socket]
		iRet = CreateUdpSocket();
		if(iRet < 0)
		{
			iTime = 0;
			return;
		}

		//[ 设置aplc暂停时钟周期]
		//[ #9622 bit4-7大于0：允许输出Log]
		//[       bit4-7等于0：不许输出Log]
		//[       bit0-3为aplc广播时钟周期]
		sDelay = 0x10/*允许输出Log*/ + 0x4/*aplc广播时钟周期为4*/;
		iRet = setNCData(M_SEC_UPRM_HOST_LINK, M_SSEC_UPHLNK_LPOLLTM, SYS_NO_1, 0, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sDelay);
		if( 0 != iRet )
		{
			//[ 取得失败]
			sDelay = 5;
		} 
		iTime = 1;
	}
	//[ 取得广播时钟周期数]
	//[ 参数#9622的 bit0-3 用于设置循环周期数]
	//[ 参数#9622的大区分号：123；小区分号：22]
	iRet = getNCData(M_SEC_UPRM_HOST_LINK, M_SSEC_UPHLNK_LPOLLTM, SYS_NO_1, 0, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sDelay);
	if(0 != iRet)
	{
		//[ 取得失败，立即返回]
		sDelay = 4;
	}
	else
	{
		//[ 取得广播时钟周期数]
		sDelay = (sDelay & 0x0F);
		if(sDelay < 1)
		{
			sDelay = 1;
		}
	}

	//[ 循环广播第一系统的三轴坐标]
	//[ 接收手机端的请求，并根据请求发送相应的数据]
	//[ sDelay表示循环周期数，‘10’是一个循环周期的时间为10ms]
	if((((tpCurCycTime.tv_sec- g_tpCycTime.tv_sec)*1000) + (tpCurCycTime.tv_nsec - g_tpCycTime.tv_nsec)/1000000) > sDelay*10)
	{
		g_tpCycTime.tv_nsec = tpCurCycTime.tv_nsec;
		g_tpCycTime.tv_sec = tpCurCycTime.tv_sec;
		//[ 广播解析]
		iRet = BroadcastData();
		if(iRet < 0)
		{
			//[ 关闭广播socket和udp socket]
			CloseBcSocket();
			CloseUdpSocket();
			//[ 重新创建套接字 ]
			iTime = 0;
			return;
		}

		//[ 接收客户端请求]
		iRet = DoUdpCommunicate();
		if(iRet < 0)
		{
			//[ 关闭广播socket和udp socket]
			CloseBcSocket();
			CloseUdpSocket();
			//[ 重新创建套接字 ]
			iTime = 0;
			return;
		}
		iTime = 1;
	}
}

/************************************************************************/
/* Function Name: WriteLogInfo                                          */
/* Function		: 写入Log信息				                            */
/* Parameter	: char* pLogInfo <I> : 待写入的Log信息                  */
/* Return Value	: void　                                                */
/* Date			: 2014/01/03                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void WriteLogInfo(char* pLogInfo)
{
	//[[[ 说明：本函数只作调试用，不做他用。]]]

	//[ 打开Log文件]
	int iRet = 0;
	short sCanWriteLog = 0;
	FILE* pFile = NULL;

	//[ 检查待写入的信息是否合法]
	if(NULL == pLogInfo)
	{
		//[ 信息不合法]
		//[ 立即返回]
		return;
	}

	//[ 检查是否允许些Log信息]
	//[ 参数#9622的 bit4-7不为0：允许；bit4-7为0：不允许]
	//[ 参数#9622的大区分号：123；小区分号：22]
	iRet = getNCData(M_SEC_UPRM_HOST_LINK, M_SSEC_UPHLNK_LPOLLTM, SYS_NO_1, 0, ADR_BASE_SYSTEM, T_SHORT, DOUBLE_PREC, &sCanWriteLog);
	if( (0 != iRet) || (0 == (sCanWriteLog & 0xF0)) )
	{
		//[ 取得失败，立即返回]
		return;
	} 

	//[ 检查Log文件是否存在]
	//[ 如果不存在则创建]
	pFile = fopen(LOG_FILE_NAME, "r");
	//[ 检查是否创建成功]
	if(NULL == pFile)
	{
		//[ 创建失败]
		iCount = 0;
	}
	else
	{
		//[ 关闭文件]
		fclose(pFile);
		pFile = NULL;
	}

	//[ 检查Log信息的数量]
	iCount = iCount + 1;
	if(iCount > MAX_LOG_COUNT)
	{
		//[ 超过最大允许数量200]
		//[ 立即返回]
		return;
	}

	//[ 打开日志文件]
	//[ 如果不存在则创建]
	pFile = fopen(LOG_FILE_NAME, "r+");
	//[ 检查是否创建成功]
	if(NULL == pFile)
	{
		//[ 创建失败]
		return;
	}

	//[ 写入日志信息]
	fseek(pFile, 0, SEEK_END);
	fputs(pLogInfo, pFile);

	//[ 关闭]
	fclose(pFile);
}

/************************************************************************/
/* Function Name: WriteLastErrInfo                                      */
/* Function		: 写入最近错误信息			                            */
/* Parameter	: void									                */
/* Return Value	: void　                                                */
/* Date			: 2014/01/03                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void WriteLastErrInfo(char* pInfoName)
{
	//[[[ 说明：本函数只作调试用，不做他用。]]]

	//[ 变量定义]
	int iRet = 0;
	char cBuff[BUFF_SIZE];

	//[ 检查输入参数合法性]
	if(NULL == pInfoName)
	{
		//[ 参数非法]
		return;
	}

	//[ 取得最近错误信息]
	bzero(cBuff, BUFF_SIZE);
	iRet = errnoGet();
	sprintf(cBuff, "%s err=%d\n", pInfoName, iRet);

	//[ 输出错误Log信息]
	WriteLogInfo(cBuff);
}

/************************************************************************/
/* Function Name: WriteLogInfoBin                                       */
/* Function		: 写入二进制的Log信息		                            */
/* Parameter	: char* pLogInfo <I> : 待写入的Log信息                  */
/*				  int iLen <I> : Log信息的长度		                    */
/* Return Value	: void　                                                */
/* Date			: 2014/01/03                                            */
/* Code By		: lisc	                                                */
/* Copyright	: COPYRIGHT(C) 2014 MITSUBISHI ELECTRIC CORPORATION     */
/************************************************************************/
void WriteLogInfoBin(char* pLogInfo, int iLen)
{
	//[[[ 将ASCII码转换成可见字符			]]]
	//[[[ 说明：本函数只作调试用，不做他用。]]]

	//[ 定义循环的临时变量]
	int iIdx = 0;

	//[ 检查输入参数合法性]
	if(NULL == pLogInfo)
	{
		//[ 参数非法]
		return;
	}

	//[ 循环转换]
	for(iIdx = 0; (iIdx < iLen) && (0 != pLogInfo[iIdx]); iIdx = iIdx + 1)
	{
		pLogInfo[iIdx] = pLogInfo[iIdx] + 48;
	}

	//[ 输出Log信息]
	WriteLogInfo(pLogInfo);
}
