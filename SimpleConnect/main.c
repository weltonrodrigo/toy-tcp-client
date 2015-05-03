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


int main(int argc, const char * argv[]) {
    
    int  port;
    char *server_response = "";
    struct tcp_connection conn;
    
    char *GET_ROOT = "GET / HTTP/1.1\r\n";
    
    //strcpy(*host, argv[0]);
    char *host = "www.prf.gov.br";
    
//    port = atoi(argv[1]);
    port = 80;
    
    conn = connect_to_host(&host, port);
    
    size_t status = send_message(conn, &GET_ROOT);
    
    if (status == sizeof(GET_ROOT)){
        get_server_response(&server_response);
        
        printf("%s", server_response);
    }
    
    return 0;
}
