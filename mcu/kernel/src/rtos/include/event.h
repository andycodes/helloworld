#ifndef EVENT_H
#define EVENT_H

#include <stdint.h>
#include "os.h"
#include "lib.h"
#include "task.h"

#if 0
typedef enum event_type_tag {
    EVENT_TYPE_UNKNOWN  = (0 << 16),
    EVENT_TYPE_SEM      = (1 << 16),
    EVENT_TYPE_MAILBOX  = (2 << 16),
    EVENT_TYPE_MEM_BLOCK = (3 << 16),
    EVENT_TYPE_MUTEX = (4 << 16),
}event_type_e;
#endif

typedef uint32_t event_type_e;
#define EVENT_TYPE_UNKNOWN      (0 << 16)
#define EVENT_TYPE_SEM          (1 << 16)
#define EVENT_TYPE_MAILBOX      (2 << 16)
#define EVENT_TYPE_MEM_BLOCK    (3 << 16)
#define EVENT_TYPE_MUTEX        (4 << 16)
#define EVENT_TYPE_FLAG_GROUP   (5 << 16)

typedef struct event_tag {
    event_type_e type;
    list_t wait_list;
}event_t;

extern void event_init(event_t *event, event_type_e type);
extern void event_wait(event_t *event, task_t *task, void *msg, uint32_t state, uint32_t timeout);
extern task_t *event_wakeup(event_t *event, void *msg, uint32_t result);
extern void event_remove_task(task_t *task, void *msg, uint32_t result);
extern uint32_t event_remove_all(event_t *event, void *msg, uint32_t result);
extern uint32_t event_wait_count(event_t *event);
extern task_t *event_wakeup_task(event_t *event, task_t *task, void *msg, uint32_t result);

#endif /*EVENT_H*/
