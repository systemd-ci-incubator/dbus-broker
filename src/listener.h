#pragma once

/*
 * Socket Listener
 */

#include <c-list.h>
#include <c-macro.h>
#include <stdlib.h>
#include "policy.h"
#include "util/dispatch.h"

typedef struct Bus Bus;
typedef struct DispatchContext DispatchContext;
typedef struct Listener Listener;

struct Listener {
        Bus *bus;
        char guid[16];
        int socket_fd;
        DispatchFile socket_file;
        PolicyRegistry policy;
        CList peer_list;
};

#define LISTENER_NULL(_x) {                                                     \
                .socket_fd = -1,                                                \
                .socket_file = DISPATCH_FILE_NULL((_x).socket_file),            \
                .policy = POLICY_REGISTRY_INIT((_x).policy),                    \
                .peer_list = C_LIST_INIT((_x).peer_list),                       \
        }

int listener_init_with_fd(Listener *listener,
                          Bus *bus,
                          DispatchContext *dispatcher,
                          int socket_fd,
                          const char *policpath);
Listener *listener_free(Listener *free);
void listener_deinit(Listener *listener);

C_DEFINE_CLEANUP(Listener *, listener_deinit);
