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
#include "tcpclient.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "stdio.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "string.h"
#include <stdlib.h>
#include <netdb.h>
#include "errno.h"

struct tcp_connection {
    struct addrinfo addrinfo;
    int socketfd;
};

int connect_to_host (struct tcp_connection *conn, char host[], char port[]);

// Send message to server. Returns size of sent message.
size_t send_message (struct tcp_connection *conn, char message[], char *buffer, size_t bufsize);

#endif /* defined(__TCP_ClientServer__tcpclient__) */
