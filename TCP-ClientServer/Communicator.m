//
//  Communicator.m
//  TCP-ClientServer
//
//  Created by Welton Torres Nascimento on 30/04/15.
//  Copyright (c) 2015 Welton Torres Nascimento. All rights reserved.
//

#import "Communicator.h"

@implementation Communicator

@synthesize shouldExit, inputstream, outputstream, headersSent;

- (void)stream:(NSStream *)theStream handleEvent:(NSStreamEvent)streamEvent{
    //NSLog(@"stream event %i", streamEvent);
    
    switch (streamEvent) {
        case NSStreamEventOpenCompleted:
            NSLog(@"CONNECTED!");
            break;
        case NSStreamEventHasSpaceAvailable:
            if(theStream == outputstream && !headersSent){
                NSData *data = [[NSData alloc] initWithData:[@"GET / HTTP/1.1\r\nHost: www.prf.gov.br\r\n\r\n" dataUsingEncoding:NSASCIIStringEncoding]];
                
                [outputstream write:[data bytes] maxLength:[data length]];
                headersSent = true;
            }
            break;
        case NSStreamEventHasBytesAvailable:
            if(theStream == inputstream){
                NSInteger len;
                uint8_t buffer[1024];
                
                while([inputstream hasBytesAvailable]){
                    len = [inputstream read:buffer maxLength:sizeof(buffer)];
                    
                    if(len > 0 ){
                        NSString *output = [[NSString alloc] initWithBytes:buffer length:len encoding:NSASCIIStringEncoding];
                        
                        if (nil != output){
                            NSLog(@"SERVER SAID:");
                            NSLog(@"%@", output);
                            
                        }
                        
                    }
                }
                
                    [self setShouldExit:true];
            }
            
        default:
            break;
    }
    
}

- (void)connect{
    // insert code here...
    NSLog(@"DA BITCH COMMUNICATOR!\n");
    
    CFReadStreamRef readstream;
    CFWriteStreamRef writestream;
    
    CFStreamCreatePairWithSocketToHost(NULL, (CFStringRef)@"www.prf.gov.br", 80, &readstream, &writestream);
    
    NSLog(@"Opening connection...");
    
    inputstream = (__bridge  NSInputStream *)readstream;
    outputstream = (__bridge NSOutputStream *)writestream;
    
    [inputstream setDelegate:self];
    [outputstream setDelegate:self];
    
    [inputstream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [outputstream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    
    [inputstream open];
    [outputstream open];
}
@end
