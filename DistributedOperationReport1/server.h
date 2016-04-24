#pragma once
#include <afxsock.h>
int recv(int PID, int* data, int len, bool sync);
int send_result(void);
int message_handler(int);
bool register_command(void);