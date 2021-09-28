//
//  xpc_helper.c
//  xpc
//
//  Created by afrosamurai on 7/17/21.
//  Copyright © 2021 example organization. All rights reserved.
//

#include "xpc_helper.h"

xpc_object_t XpcLaunchdSubmitJob(char *program, char *label, int keepalive) {
    xpc_object_t dict = xpc_dictionary_create(NULL, NULL, 0);
    xpc_object_t request = xpc_dictionary_create(NULL, NULL, 0);
    xpc_object_t job = xpc_dictionary_create(NULL, NULL, 0);
    
    // Set KeepAlive to TRUE
    xpc_dictionary_set_bool(job, "KeepAlive", 1);
    // Set the label
    xpc_dictionary_set_string(job, "Label", label);
    // Create the empty ProgramArguments array
    xpc_object_t pArgs = xpc_array_create(NULL, 0);
    xpc_dictionary_set_value(job, "ProgramArguments", pArgs);
    // Set the program value
    xpc_dictionary_set_string(job, "Program", program);
    // Create the XPC request object
    xpc_dictionary_set_value(request, "SubmitJob", job);
    xpc_dictionary_set_value(dict, "request", request);
    xpc_dictionary_set_uint64(dict, "subsystem", 7);
    xpc_dictionary_set_uint64(dict, "type", 7);
    xpc_dictionary_set_uint64(dict, "handle", 0);
    xpc_dictionary_set_uint64(dict, "routine", ROUTINE_SUBMIT);
    xpc_object_t *outDict = NULL;
    struct xpc_global_data *xpc_gd = (struct xpc_global_data *) _os_alloc_once_table[1].ptr;
    // Submit the job to launchd
    int rc = xpc_pipe_routine(xpc_gd->xpc_bootstrap_pipe, dict, &outDict);
    
    if (rc == 0) {
        return outDict;
    }
    if (outDict != NULL) {
        int err = xpc_dictionary_get_int64(outDict, "error");
        return outDict;
    }
    
    xpc_object_t errDict = xpc_dictionary_create(NULL, NULL, 0);
    xpc_dictionary_set_string(errDict, "error", "xpc_bootstripe_pipe returned a null dictionary");
    
    return errDict;
}

