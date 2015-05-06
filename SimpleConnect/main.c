//
//  main.c
//  SimpleConnect
//
//  Created by Welton Torres Nascimento on 02/05/15.
//  Copyright (c) 2015 Welton Torres Nascimento. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "tcpclient.h"
#include "strings.h"


#define SOCK_BUF_SIZE 15000
#define CRLF "\r\n"
#define GET_ROOT "GET / HTTP/1.1" CRLF "Host: www.prf.gov.br" CRLF CRLF

int main(int argc, const char * argv[]) {
    
    char message[] = GET_ROOT;
    
    char server_response[SOCK_BUF_SIZE];
    struct tcp_connection conn;
    
    bzero(&conn, sizeof(conn));
    
    // Connect to host
    int err = connect_to_host(&conn, (char *)argv[1], (char *)argv[2]);
    
    if (err) {
        printf("Erro ao conectar:%s\n", strerror(err));
        exit(1);
    }
    
    size_t status = send_message(&conn, message, server_response, sizeof(server_response));
    
    if (status == 0){
        printf("%s", server_response);
    }
    
    return 0;
}
