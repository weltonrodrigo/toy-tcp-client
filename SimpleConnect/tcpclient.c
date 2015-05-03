//
//  tcpclient.c
//  TCP-ClientServer
//
//  Created by Welton Torres Nascimento on 02/05/15.
//  Copyright (c) 2015 Welton Torres Nascimento. All rights reserved.
//

#include "tcpclient.h"
#include "sys/socket.h"
#include "stdio.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "string.h"
#include <stdlib.h>

char *message_to_send[];
char *server_response[];

struct tcp_connection connect_to_host (char *host[], int port){
    int socketfd, result_code;
    
    struct sockaddr_in servaddr;
    struct tcp_connection established_connection;
    
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    bzero(&established_connection, sizeof(established_connection));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(*host);
    servaddr.sin_port = HTONS(port);
    
    result_code = connect(socketfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    
    if (result_code == -1){
        printf("Erro ao connectar. Saindo.\n");
        exit(1);
    }
    
    established_connection.servaddr = &servaddr;
    established_connection.socketfd = socketfd;
    
    return established_connection;
}

size_t send_message (struct tcp_connection conn, char *message[]){
    size_t bytes_sent;
    size_t n;
    
    
    bytes_sent =
    sendto(conn.socketfd, &message, sizeof(&message), 0, (struct sockaddr *) conn.servaddr, sizeof(conn.servaddr));
    
    if ( bytes_sent < sizeof(&message)) {
        // there was an error, I gess.
        return -1;
    }
    
    // We did good, now lets read the response, if any.
    n = recvfrom(conn.socketfd, server_response, 10000, 0, NULL, NULL);
    server_response[n] = 0;
    
    return bytes_sent;
    
}

void get_server_response(char *buffer[]){
    strcpy(*buffer, *server_response);
}

