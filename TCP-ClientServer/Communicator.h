//
//  Communicator.h
//  TCP-ClientServer
//
//  Created by Welton Torres Nascimento on 30/04/15.
//  Copyright (c) 2015 Welton Torres Nascimento. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol CommunicatorDelegate;

typedef NS_ENUM(NSUInteger, CommunicatorStatus) {
    wantToRead = 0,
    WantToWrite = 1,
    None = 2
};

@interface Communicator : NSObject <NSStreamDelegate>

@property id <CommunicatorDelegate> delegate;

@property BOOL shouldExit;
@property NSInputStream *inputstream;
@property NSOutputStream *outputstream;
@property NSString *messageToSend;
@property CommunicatorStatus state;

-(void)connect:(NSString *) host;
-(void)sendMessage:(NSString *) message;

@end

@protocol CommunicatorDelegate <NSObject>

-(void) gotResponse:(NSString *)response;

@end
