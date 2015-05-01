//
//  Communicator.h
//  TCP-ClientServer
//
//  Created by Welton Torres Nascimento on 30/04/15.
//  Copyright (c) 2015 Welton Torres Nascimento. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Communicator : NSObject <NSStreamDelegate>

-(void)connect;
//-(NSString*)sendMessage: (NSString*)message;

@property BOOL shouldExit;

@property BOOL headersSent;
@property NSInputStream *inputstream;
@property NSOutputStream *outputstream;

@end
