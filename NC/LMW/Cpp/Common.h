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

#define KEY_SHIFT					0x01
#define KEY_SEC						0x02
#define KEY_BITALL					0x03


static unsigned short usRCcount=1; // Row Col Count
/* Screen Numbers */
#define LOGO_SCREEN							0
#define CAUTION_SCREEN						1
#define EOS_SCREEN							2
#define PREV_SCREEN							3
#define CONFIRM_WINDOW						4
#define INOUTXY_SCREEN						5
#define INOUTL_SCREEN						6
#define ALARM_SCREEN						7
#define MCODE_SCREEN						8
#define GCODE_SCREEN						9
#define INIT_SCREEN							10
#define MTB_PASSWORD						11
#define MTB_SPSPEED							12
#define MTB_SPORIENT						13
#define MTB_AXIS							14
#define MTB_SYSINFO							15
#define SUBSYS_SCREEN						16
#define COOLANT_SCREEN						17
#define LUBRICATION_SCREEN					18
#define HYDROLIC_SCREEN						19
#define ATC_ARM_SCREEN						20
#define ATC_MAG_SCREEN						21
#define CHIPCONVEY_SCREEN					22
#define POWER_SCREEN						23
#define SPINDLE_SCREEN						24
#define MAINTAIN_HOME_SCREEN				25
#define POWER_SCREEN2						26



#define HMI_SCREEN					1000
#define SETUP_SCREEN				2000
#define HMI_EDIT_SCREEN				3000
#define DIAG_SCREEN					4000
#define MAINTENANCE_SCREEN			5000
#define MAIN_SCREEN					6000



#define TIME_STORE_REG				200

#define COUNT_START_STATUS			18326

#define PREVENTIVE_INPUT_SIZE		35
#define WARN_MSG_DATA_SIZE			60		//Message Size

#define WARN_MSG_SET_COLOR				0xFFFF00
#define WARN_MSG_CHAR_COLOR				0xFF0000
#define DEFAULT_WARN_MSG_COLOR			0x787878



#define CURSOR_COLOR				0x8080FF//0x6FB7FF
#define DEFAULT_COLOR				0xFFFFFF
#define RUNNING_COLOR				0x00FF40
//#define DEFAULT_COLOR				0xFDF2C8
#define GREEN_COLOR					0x00FF00
#define YELLOW_COLOR				0xFFFF00
#define RED_COLOR					0xFF0000
#define BACKGRNG_COLOR				0xC0C0C0


#define LOGOUT_TIME					499


struct Datarange{
	double minValue;
	double maxValue;
};

#define KEY_DATA_SIZE				60
#define SUCCESS						0
#define FAIL						1
#define FILE_OK						0
#define FILE_ERROR					1

#define WARNTEXT_SIZE				60
#define LIST_SIZE					13
#define MAX_PARAM					40
#define HELPTEXT_LEN				80



#endif	/* __COMMON_H__ */