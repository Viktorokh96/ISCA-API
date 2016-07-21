#ifndef TYPES_H
#define TYPES_H

typedef unsigned int opt_t;
typedef void (*drawhandler_t)(void *ths);
typedef void (*eventhandler_t)(void *ths, ISCA_Event *event);
typedef void (*deletehandler_t)(void *ths);

#endif
