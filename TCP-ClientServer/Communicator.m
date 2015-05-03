//
//  Communicator.m
//  TCP-ClientServer
//
//  Created by Welton Torres Nascimento on 30/04/15.
//  Copyright (c) 2015 Welton Torres Nascimento. All rights reserved.
//

#import "Communicator.h"

@implementation Communicator

@synthesize shouldExit, inputstream, outputstream, messageToSend, state, delegate;

NSString *serverResponse;

- (void)stream:(NSStream *)theStream handleEvent:(NSStreamEvent)streamEvent{
    //NSLog(@"stream event %i", streamEvent);
    
    switch (streamEvent) {
        case NSStreamEventOpenCompleted:
            NSLog(@"CONNECTED!");
            break;
        case NSStreamEventHasSpaceAvailable:
            if(theStream == outputstream && state == WantToWrite){
                NSData *data = [[NSData alloc] initWithData:[messageToSend dataUsingEncoding:NSUTF8StringEncoding]];
                
                // Should we care if we can't send the whole message at once?
                [outputstream write:[data bytes] maxLength:[data length]];
                
                state = wantToRead;
            }
            break;
        case NSStreamEventHasBytesAvailable:
            if(theStream == inputstream && state == wantToRead){
                NSInteger len;
                uint8_t buffer[1024];
                
                while([inputstream hasBytesAvailable]){
                    len = [inputstream read:buffer maxLength:sizeof(buffer)];
                    
                    if(len > 0 ){
                        NSString *output = [[NSString alloc] initWithBytes:buffer length:len encoding:NSUTF8StringEncoding];
                        
                        if (nil != output){
                            serverResponse = output;
                            state = Idle;
                        }
                    }
                }
            }
            
        default:
            NSLog(@"Error. Exiting.");
            [self setShouldExit:true];
            break;
    }
    
}

- (NSString *) sendMessage:(NSString *) message{
    [self setMessageToSend:message];
    state = WantToWrite;
    
    return serverResponse;
}

- (void)connect:(NSString *)host{
    // insert code here...
    NSLog(@"DA BITCH COMMUNICATOR!\n");
    
    CFReadStreamRef readstream;
    CFWriteStreamRef writestream;
    
    CFStreamCreatePairWithSocketToHost(NULL, (__bridge CFStringRef)host, 8000, &readstream, &writestream);
    
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
