/************************************************************/
/* can_chinook2.h											*/
/* Generic difinitions for Chinook's CAN bus		 		*/
/*															*/
/*															*/
/* Author : David Khouya, Chinook 2							*/
/* Date	  :	02/05/2012										*/
/* Version: 0.1												*/
/************************************************************/

/************************************************************/
#ifndef CAN_CHINOOK2_MODULE
#define CAN_CHINOOK2_MODULE
/************************************************************/

/************************************************************/
/*						   INCLUDES			 				*/
/************************************************************/

/************************************************************/

/****BOARDS SID***/
#define CAN_MSG_VOLANT_SID				1
#define CAN_MSG_VOLANT_BUTTONS			0x01
#define CAN_MSG_VOLANT_GET_VOLTAGE		0x02
#define CAN_MSG_VOLANT_GET_WIND_DIR		0x03
#define CAN_MSG_VOLANT_GET_WHEEL_SPEED	0x04
#define CAN_MSG_VOLANT_GET_TURBINE_RPM	0x05
#define CAN_MSG_VOLANT_GET_GEAR			0x06

#define CAN_MSG_BATTERY_SID				2
#define CAN_MSG_BATTERY_VOLTAGE			0x01
#define CAN_MSG_BATTERY_CURRENT			0x02

#define CAN_MSG_AUT_SID					4
#define CAN_MSG_AUT_GEAR				0x01
#define CAN_MSG_AUT_TURBINE_RPM			0x02
#define CAN_MSG_AUT_WHEEL_RPM			0x03
#define CAN_MSG_AUT_TURBINE_DIR			0x04
#define CAN_MSG_AUT_WIND_DIR			0x05
#define CAN_MSG_AUT_WIND_SPEED			0x06					
/*****************/

/******TYPES******/
#define CAN_MSG_TYPE_INT				0x01
#define CAN_MSG_TYPE_INT_LENGHT			2

#define CAN_MSG_TYPE_CHAR				0x02
#define CAN_MSG_TYPE_CHAR_LENGHT		1

#define CAN_MSG_TYPE_FLOAT				0x03
#define CAN_MSG_TYPE_FLOAT_LENGHT		4
/*****************/

/************************************************************/
/*					 TYPES DEFINITIONS			 			*/
/************************************************************/
/*Float2bytes and Bytes2float Union*/
union bfconvert
{
    char bytes[4];
    float val;
};

union biconvert
{
    char bytes[2];
    int val;
};
/************************************************************/


/************************************************************/
#endif
/************************************************************/
