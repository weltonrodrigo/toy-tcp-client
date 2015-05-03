//
//  main.m
//  TCP-ClientServer
//
//  Created by Welton Torres Nascimento on 30/04/15.
//  Copyright (c) 2015 Welton Torres Nascimento. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Communicator.h"

int main(int argc, const char * argv[])
{
    NSRunLoop   * runLoop;
    Communicator        * main; // replace with desired class
    
    @autoreleasepool
    {
        // create run loop
        runLoop = [NSRunLoop currentRunLoop];
        main    = [[Communicator alloc] init]; // replace with init method
        
        [main connect:@"localhost"];
        NSString *response = [main sendMessage:@"GET / HTTP/1.1\r\n"];
        
        NSLog(response);
        
        // enter run loop
        while((!([main shouldExit])) && (([runLoop runMode:NSDefaultRunLoopMode beforeDate:[NSDate dateWithTimeIntervalSinceNow:2]])));
        
    };
    return(0);
}
