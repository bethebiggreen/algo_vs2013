#pragma once
#include <afxsock.h>
int send(int PID, int* data, int len, bool sync);
int send_and_wait(void);
int register_event(int event);
int broadcast(int PID, int* data, int len, int policy);
int multicast(int PID, int event, int* data, int len, int policy);
int run_event_handler(void);
