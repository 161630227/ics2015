#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
	int NO;
	char * watch_expr;
	int v;
	struct watchpoint *next;

	/* TODO: Add more members if necessary */


} WP;
extern WP* new_wp();
extern bool check_watchpoint();
extern void free_wp(WP*);
extern void pri();
extern void delete(int);
#endif
