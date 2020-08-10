/* Common.h */

#ifndef __COMMON_H__
#define __COMMON_H__

/* C Headers */
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

/* Custom API Headers */ 
#include "melsect.h"
#include "melssect.h"
#include "melncapi.h"
#include "meltype.h"
#include "ncmcapi.h"
#include "melfstyp.h"

//Initialization migrated PotManager Class
extern short sConfirmWindowNo;
static unsigned short usRCcount=1; // Row Col Count
extern short sParentScreen;

//End of Migration


#define KEY_SHIFT					0x01
#define KEY_SEC						0x02
#define KEY_BITALL					0x03

#define DISABLE_COLOR				0xFFFFFF
#define CURSOR_COLOR				0x0080C0
#define DEFAULT_COLOR				0xFFFFFF

#define WARN_MSG_DATA_SIZE			60		//Message Size
#define MAX_PARAM					40
#define PARAM_DATA_SIZE				12

//for Tool Management Table
#define COL_SIZE					5
#define TABLE_ARRAY_SIZE			36
#define PAGE_TOOLNUM				12
#define FIRST_PLC_DEVICE_END		11
#define SECOND_PLC_DEVICE_END		23
#define	INITTOOL_IDX				10700
#define	INITLD_IDX					28300
#define INITMINLD_IDX				28360
#define	INITDATA_IDX				10940
#define INITTYPE_IDX				28420

#define CLEAR						998
#define LOCK						999
#define THIRD_PLC_DEVICE_START		24
#define SPLIT_DATA_SIZE				16
#define INDEX_PLUS_ONE				1
#define PAGE_PLUS_ONE				1
#define OUTPUT_BUFFER_SIZE			10
#define TABLE_ROW_INDEX_END			11
#define TOOL_COL_NUM				1


#define HMI_SCREEN					1000
#define SETUP_SCREEN				2000
#define HMI_EDIT_SCREEN				3000
#define DIAG_SCREEN					4000
#define MAINTENANCE_SCREEN			5000


#define HOME_SCREEN							0
#define PRE_MACHINING_SCREEN				1
#define DURING_MACHINING_SCREEN				2
#define POST_MACHINING_SCREEN				3
#define DIAGNOSIS_SCREEN					4
#define MAINTENANCE1_SCREEN					5
#define GCODE_SCREEN						6
#define MCODE_SCREEN						7
#define CUTTING_PARAMETERS_SCREEN			8
#define DRILL_SELECTION_SCREEN				9
#define MAGAZINE_VIEW_SCREEN				10
#define MAGAZINE_LIST_SCREEN				11
#define TOOL_LOAD_TYPE_SCREEN				12
#define TREND_VIEW_SCREEN					13
#define MACHINE_COND_SETTINGS_SCREEN		14
#define MACHINE_COND_SELECTION_SCREEN		15
#define DAILY_MAINT_CHK_SCREEN				16
#define MONTHLY_MAINT_CHK_SCREEN			17
#define QUATERLY_MAINT_CHK_SCREEN			18
#define PREVENTIVE_MAINT_CHK_SCREEN			19
#define VERSION_1_SCREEN					20
#define VERSION_2_SCREEN					21
#define INPUT_1_SCREEN						22
#define INPUT_2_SCREEN						23
#define OUTPUT_1_SCREEN						24
#define OUTPUT_2_SCREEN						25
#define BITS_1_SCREEN						26
#define BITS_2_SCREEN						27
#define BITS_3_SCREEN						28
#define BITS_4_SCREEN						29
#define BITS_5_SCREEN						30
#define BITS_6_SCREEN						31
#define BITS_7_SCREEN						32
#define BITS_8_SCREEN						33
#define CYCLE_TIME_SCREEN					34
#define DOWNTIME_ANALYSIS_SCREEN			35
#define DOWNTIME_ANALYSIS_HIST_SCREEN		36
#define DAILY_UTILIZATION_SCREEN			37
#define DAILY_UTILIZATION_HIST_SCREEN		38
#define OEE_REPORT_SCREEN					39
#define OEE_HIST_SCREEN						40
#define OPERATOR_SETUP_SCREEN				41
#define ALARM_HELP_SCREEN					42
#define CUT_O_METER_SCREEN					43
#define EASY_BACKUP_SCREEN					44
#define CALCULATOR_WINDOW					45
#define DOWNTIME_DATA_WINDOW				46
#define LOCK_WINDOW							47
#define HELP_WINDOW							48
#define DOWNTIME_COUNTER_WINDOW				49


///Error Message Definitions
#define MAKE_LOWER_TOOL_ZERO_ERR	1
#define MAKE_UPPER_TOOL_ZERO_ERR	2
#define POT_TOOL_NUM_ZERO_ERR		3
#define JOG_MODE_ERR				4
#define LD_RANGE_ERR				5
#define DATA_OUT_OF_RANGE_ERR		6
#define ENTER_ZERO_OR_ONE_ERR		7
#define TOOL_NUM_EXISTS_ERR			8
#define POT_NOT_EXISTS_ERR			9
#define TOOL_NOT_EXISTS_ERR			10
#define SETTING_ERR					11
#define TOOL_CLR_ERR				12
#define PROPER_VALUE_ERR			13
#define POT_AND_TOOL_NOT_EQU_ERR	14
#define MAKE_LOWER_TOOL_BT_ZERO_ERR	15
#define MAKE_UPPER_TOOL_BT_ZERO_ERR	16
#define SPINDLE_TOOL_NUM_MATCH_ERR	17
#define JOG_MODE_CLEAR_ERR			18
#define MAG_CLEAR_COMPLETE			19
#define TOOL_LCK_ERR				20
#define TOOL_IS_ZERO_ERR			21
#define JOG_MODE_LOCK_ERR			22
#define EDIT_PERMIT_ERR				23
#define CAUTION_ERR					24
#define TEACH_MODE_ON_ERR			25
#define TEACH_MODE_OFF_ERR			26
#define UNDER_DEVELOPMENT_ERROR		100




#endif	/* __COMMON_H__ */