//
//  xpc_helper.h
//  xpc
//
//  Thanks to J. Levin for the launchjtl source http://newosxbook.com/articles/jlaunchctl.html
//  Copyright © 2021 example organization. All rights reserved.
//

#include <stdio.h>
#include <xpc/xpc.h>
#include <xpc/connection.h>
#include <dispatch/dispatch.h>
#include <Block.h>
#include <objc/objc.h>
#include <mach/task.h>
#include <sys/utsname.h>

#ifndef xpc_helper_h
#define xpc_helper_h

#define ROUTINE_SUBMIT        100

extern xpc_type_t TYPE_ERROR;

extern xpc_type_t TYPE_ARRAY;
extern xpc_type_t TYPE_DATA;
extern xpc_type_t TYPE_DICT;
extern xpc_type_t TYPE_INT64;
extern xpc_type_t TYPE_STRING;
extern xpc_type_t TYPE_UUID;
extern xpc_type_t TYPE_BOOL;
extern xpc_type_t TYPE_DATE;
extern xpc_type_t TYPE_FD;
extern xpc_type_t TYPE_CONNECTION;
extern xpc_type_t TYPE_NULL;
extern xpc_type_t TYPE_SHMEM;

extern xpc_object_t ERROR_CONNECTION_INVALID;
extern xpc_object_t ERROR_CONNECTION_INTERRUPTED;
extern xpc_object_t ERROR_CONNECTION_TERMINATED;


extern void *objc_retain (void *);
extern int xpc_pipe_routine (xpc_object_t *xpc_pipe, xpc_object_t *inDict, xpc_object_t *out);
extern char *xpc_strerror (int);
extern int csr_check (int what);


typedef unsigned char * ptr_to_uuid_t;
extern const ptr_to_uuid_t ptr_to_uuid(void *p);

extern xpc_object_t XpcLaunchdSubmitJob(char *program, char *label, int keepalive);

// os_alloc_once_table:
//
// Ripped this from XNU's libsystem
#define OS_ALLOC_ONCE_KEY_MAX    100

struct _os_alloc_once_s {
    long once;
    void *ptr;
};
extern struct _os_alloc_once_s _os_alloc_once_table[];

struct xpc_global_data {
    uint64_t    a;
    uint64_t    xpc_flags;
    mach_port_t    task_bootstrap_port;  /* 0x10 */
#ifndef _64
    uint32_t    padding;
#endif
    xpc_object_t    xpc_bootstrap_pipe;   /* 0x18 */
    // and there's more, but you'll have to wait for MOXiI 2 for those...
    // ...
};

#endif /* xpc_helper_h */

