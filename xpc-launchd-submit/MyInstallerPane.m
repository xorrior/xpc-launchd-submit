//
//  MyInstallerPane.m
//  xpc
//
//  Created by afrosamurai on 7/13/21.
//  Copyright © 2021 example organization. All rights reserved.
//

#import "MyInstallerPane.h"
#include "xpc_helper.h"

__attribute__((constructor)) static void exec()
{
    xpc_object_t resp = XpcLaunchdSubmitJob("PAYLOAD", "LABEL", 1);
    
    char *strResp = xpc_copy_description(resp);
    NSString *objcResp = [NSString stringWithCString:strResp encoding:NSUTF8StringEncoding];
    
    [objcResp writeToFile:@"/private/tmp/xpc_plugin_log.txt" atomically:YES encoding:NSUTF8StringEncoding error:NULL];
}

@implementation MyInstallerPane

- (NSString *)title
{
    return [[NSBundle bundleForClass:[self class]] localizedStringForKey:@"PaneTitle" value:nil table:nil];
}

- (void)willEnterPane:(InstallerSectionDirection)dir {
    // This winodw
}

- (void) willExitPane:(InstallerSectionDirection)dir {
    return;
}

- (BOOL)shouldExitPane:(InstallerSectionDirection)dir
{
    return YES;
}

@end

