/*
 * Soft:        Keepalived is a failover program for the LVS project
 *              <www.linuxvirtualserver.org>. It monitor & manipulate
 *              a loadbalanced server pool using multi-layer checks.
 *
 * Part:        vrrp_track.c include file.
 *
 * Version:     $Id: vrrp_track.h,v 1.1.15 2007/09/15 04:07:41 acassen Exp $
 *
 * Author:      Alexandre Cassen, <acassen@linux-vs.org>
 *
 *              This program is distributed in the hope that it will be useful,
 *              but WITHOUT ANY WARRANTY; without even the implied warranty of
 *              MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *              See the GNU General Public License for more details.
 *              
 *              This program is free software; you can redistribute it and/or
 *              modify it under the terms of the GNU General Public License
 *              as published by the Free Software Foundation; either version
 *              2 of the License, or (at your option) any later version.
 *
 * Copyright (C) 2001-2007 Alexandre Cassen, <acassen@freebox.fr>
 */

#ifndef _VRRP_TRACK_H
#define _VRRP_TRACK_H

/* global includes */
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <syslog.h>

/* local includes */
#include "vector.h"
#include "list.h"

/* Macro definition */
#define TRACK_ISUP(L)	(vrrp_tracked_up((L)))

/* VRRP script tracking defaults */
#define VRRP_SCRIPT_DI 1       /* external script track interval (in sec) */
#define VRRP_SCRIPT_DW 2       /* external script default weight */

/* VRRP script tracking results */
#define VRRP_SCRIPT_STATUS_DISABLED  0
#define VRRP_SCRIPT_STATUS_INIT      1
#define VRRP_SCRIPT_STATUS_NONE      2
#define VRRP_SCRIPT_STATUS_GOOD      3

/* external script we call to track local processes */
typedef struct _vrrp_script {
	char *sname;		/* instance name */
	char *script;		/* the command to be called */
	int interval;		/* interval between script calls */
	int weight;		/* weight associated to this script */
	int result;		/* result of last call to this script */
	int inuse;		/* how many users have weight>0 ? */
} vrrp_script;

/* Tracked script structure definition */
typedef struct _tracked_sc {
	int weight;		/* tracking weight when non-zero */
	vrrp_script *scr;	/* script pointer, cannot be NULL */
} tracked_sc;

/* prototypes */
extern void dump_track(void *track_data_obj);
extern void alloc_track(list track_list, vector strvec);
extern void dump_track_script(void *track_data_obj);
extern void alloc_track_script(list track_list, vector strvec);
extern int vrrp_tracked_up(list l);
extern void vrrp_log_tracked_down(list l);
extern int vrrp_tracked_weight(list l);
extern int vrrp_script_weight(list l);

#endif
