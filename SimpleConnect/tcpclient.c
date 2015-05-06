//
//  tcpclient.c
//  TCP-ClientServer
//
//  Created by Welton Torres Nascimento on 02/05/15.
//  Copyright (c) 2015 Welton Torres Nascimento. All rights reserved.
//

#include "tcpclient.h"
#include <sys/socket.h>
#include <stdio.h>
#include "stdlib.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "string.h"
#include <stdlib.h>
#include "err.h"
#include <unistd.h>


int connect_to_host (struct tcp_connection *conn, char host[], char port[]){
//    int socketfd;

//    int err = getaddrinfo(host, port, 0, &conn->addrinfo);
    
    ////////
    struct addrinfo *res, *res0;
    int error;
    int s;
    const char *cause = NULL;
    
    conn->addrinfo.ai_family = PF_INET;
    conn->addrinfo.ai_socktype = SOCK_STREAM;
    
    error = getaddrinfo(host, port, &conn->addrinfo, &res0);
    if (error) {
        errx(1, "%s", gai_strerror(error));
        /*NOTREACHED*/
    }
    s = -1;
    for (res = res0; res; res = res->ai_next) {
        s = socket(res->ai_family, res->ai_socktype,
                   res->ai_protocol);
        if (s < 0) {
            cause = "socket";
            continue;
        }
        
        if (connect(s, res->ai_addr, res->ai_addrlen) < 0) {
            cause = "connect";
            close(s);
            s = -1;
            continue;
        }
        
        break;  /* okay we got one */
    }
    if (s < 0) {
        err(1, "%s", cause);
        /*NOTREACHED*/
    }
    
    conn->addrinfo = *res;
    conn->socketfd = s;
    return 0;
}

size_t send_message (struct tcp_connection *conn, char message[], char *buffer, size_t bufsize){
    size_t bytes_sent = 0;
    size_t n = 0;
    
    bytes_sent =
    sendto(conn->socketfd, message, strlen(message), 0, conn->addrinfo.ai_addr, conn->addrinfo.ai_addrlen);
    
    if ( bytes_sent < sizeof(&message)) {
        // there was an error, I gess.
        return -1;
    }
    
    size_t total_read = 0;
    
    while (total_read <= bufsize) {
        n = recvfrom(conn->socketfd, buffer + total_read, bufsize, 0, NULL, NULL);
        if (n == 0) {
            //No data left on socket.
            break;
        }
        total_read += n;
    }
    buffer[total_read] = 0;
    
    return 0;
}
