//
//  HTTPClient.h
//  TCP-ClientServer
//
//  Created by Welton Torres Nascimento on 01/05/15.
//  Copyright (c) 2015 Welton Torres Nascimento. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Communicator.h"

@interface HTTPClient : NSObject <CommunicatorDelegate>

-(void)get:(NSString *)url;

@end