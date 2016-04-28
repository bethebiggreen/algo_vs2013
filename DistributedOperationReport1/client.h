/*
get_broker_interface(int 
{
 {INT, 3}

*/
#pragma once
#include <afxsock.h>
int send(int PID, void* data, int len, bool sync);
int send_and_wait(void);
int broadcast(int PID, int* data, int len, int policy);
int multicast(int PID, int event, int* data, int len, int policy);
int run_event_handler(void);
