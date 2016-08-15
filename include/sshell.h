/*-****************************************************************************/
/*-                                                                           */
/*-            Copyright (c) 2013 by SOCware Inc.                             */
/*-                                                                           */
/*-  This software is copyrighted by and is the sole property of SOCware, Inc.*/
/*-  All rights, title, ownership, or other interests in the software remain  */
/*-  the property of SOCware, Inc. The source code is for FREE short-term     */
/*-  evaluation, educational or non-commercial research only. Any commercial  */
/*-  application may only be used in accordance with the corresponding license*/
/*-  agreement. Any unauthorized use, duplication, transmission, distribution,*/
/*-  or disclosure of this software is expressly forbidden.                   */
/*-                                                                           */
/*-  Knowledge of the source code may NOT be used to develop a similar product*/
/*-                                                                           */
/*-  This Copyright notice may not be removed or modified without prior       */
/*-  written consent of SOCware, Inc.                                         */
/*-                                                                           */
/*-  SOCWare, Inc. reserves the right to modify this software                 */
/*-  without notice.                                                          */
/*-                                                                           */
/*-             socware.help@gmail.com                                        */
/*-             http://socware.net                                            */
/*-                                                                           */
/*-****************************************************************************/
#ifndef SSHELL0707
#define SSHELL0707

#include <string.h>

#ifndef SH_LINE
#define SH_LINE	128
#endif

#ifndef SH_HISTORY_N
#define SH_HISTORY_N	6
#endif

typedef struct {
	char l[SH_LINE];
} his_t;

typedef int (*sh_read_t) (void *priv);

typedef void (*sh_write_t) (void *priv, char *b, int n);

typedef struct {
	his_t his[SH_HISTORY_N];
	int his_next;
	char line[SH_LINE];
	int pos;
	sh_read_t r;
	sh_write_t w;
	ll_t cmd;
	void *priv;
} sshell_t;

static inline sshell_t *sh_init(sshell_t * o, sh_read_t r, sh_write_t w,
				void *priv)
{
	memset(o, 0, sizeof(sshell_t));
	o->r = r;
	o->w = w;
	ll_init(&o->cmd);
	o->priv = priv;
	return o;
}

int sh_uartr(void *priv);

void sh_uartw(void *priv, char *b, int n);

char *sh_gets(sshell_t * o);

int sh_exe(sshell_t * o, char *cmd);

typedef struct {
	char *cmd;
	int (*f) (char *cmd);
	char *desc;
	lle_t ll;
} cmd_t;

static inline void sh_cmd_add(sshell_t * sh, cmd_t * c)
{
	lle_init(&c->ll);
	ll_addh(&sh->cmd, &c->ll);
}

#endif
