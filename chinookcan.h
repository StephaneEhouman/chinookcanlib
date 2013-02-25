#ifndef __CHINOOK_CAN_H__
#define __CHINOOK_CAN_H__


#include "chinookpack.h"

// Devices IDs

// Exemple : 
//
// #define CHINOOK_CAN_ID_WIND_SPEED 0x01



// Actions
#define CHINOOK_CAN_ACTIONS_GET
#define CHINOOK_CAN_ACTIONS_SET



typedef struct {
  int id;
  int action;
  int data_type;
  void* data;
} chinookcan_msg;


// chinookcan_send
//
// this function create a real can packet out of the chinook format
// int device: the device we want to send to
// int action: get/set/etc...
int chinookcan_send(int device, int action, void* data);


// chinookcan_decode
//
// decodes the message received from can and put it into the msg struct
//
// int id: the received id
// void* data: the content of the message
// chinookcan_msg msg: the output of the function, contains the parsed message
int chinookcan_decode(int id,void* data,chinookcan_msg* msg);

// chinookcan_send_raw
// send raw can msgs (used by chinookcan_send)
// id: the canid of the chinook device we target
// data: the chinookpack_pack data (or any other format if it is custom
int chinookcan_send_raw(int id, void* data);


