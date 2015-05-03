//
//  tcpclient.h
//  TCP-ClientServer
//
//  Created by Welton Torres Nascimento on 02/05/15.
//  Copyright (c) 2015 Welton Torres Nascimento. All rights reserved.
//

#ifndef __TCP_ClientServer__tcpclient__
#define __TCP_ClientServer__tcpclient__

#include <stdio.h>

struct tcp_connection {
    struct sockaddr_in *servaddr;
    int socketfd;
};

struct tcp_connection connect_to_host (char *host[], int port);

// Send message to server. Returns size of sent message.
size_t send_message (struct tcp_connection conn, char *message[]);

void get_server_response(char *buffer[]);

#endif /* defined(__TCP_ClientServer__tcpclient__) */
