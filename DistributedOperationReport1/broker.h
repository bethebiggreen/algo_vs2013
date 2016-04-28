#pragma once
int main_loop(void);
int register_multicast_server(void);
int find_server(const char*);
int get_server_location(void);
void subscribe_event(int);
int get_multicast_server(int event);