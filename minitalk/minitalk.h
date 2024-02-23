#ifndef MINITALK_H
#define MINITALK_H

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handle_signal(int signal);
void send_signal(int pid, char c);

#endif
