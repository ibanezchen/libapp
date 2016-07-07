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
#include <hcos/ll.h>

#include <stdarg.h>
#include <string.h>
#include "sshell.h"
#include "uart.h"

#define W(_o, _c)

static void del(sshell_t * o, int n)
{
	while (n-- > 0) {
		o->w(o->priv, "\b", 1);
		o->w(o->priv, " ", 1);
		o->w(o->priv, "\b", 1);
	}
}

char *sh_gets(sshell_t * o)
{
	int c0, c1, c2;
	o->pos = 0;
	do {
		c0 = o->r(o->priv);
		if (c0 < 0)
			continue;
		if (c0 == '\b') {
			if (o->pos > 0) {
				(o->pos)--;
				del(o, 1);
			}
		} else if (c0 == (int)'\r') {
			o->w(o->priv, "\n", 1);
			o->w(o->priv, (void *)&c0, 1);
		} else if (c0 == 27) {
			while ((c1 = o->r(o->priv)) < 0) ;
			while ((c2 = o->r(o->priv)) < 0) ;
			del(o, o->pos);
			o->pos = 0;
			o->his_next = (o->his_next - 1) % SH_HISTORY_N;
			strcpy(o->line, o->his[o->his_next].l);
			o->pos = strlen(o->line);
			o->w(o->priv, o->line, o->pos);
		} else if (o->pos < sizeof(o->line)) {
			o->line[(o->pos)++] = c0;
			o->w(o->priv, (void *)&c0, 1);
		}
	} while (c0 != (int)'\r');
	o->line[o->pos] = 0;
	strcpy(o->his[o->his_next].l, o->line);
	o->his_next = (o->his_next + 1) % SH_HISTORY_N;
	return o->line;
}

int sh_exe(sshell_t * o, char *cmd)
{
	lle_t *p;
	int len;
	ll_for_each(&o->cmd, p) {
		cmd_t *c = lle_get(p, cmd_t, ll);
		len = strlen(c->cmd);
		if (!memcmp(cmd, c->cmd, len)) {
			return c->f(cmd);
		}
	}
	return -1;
}

int sh_uartr(void *priv)
{
	uart_t *o = (uart_t *) priv;
	return uart_get(o);
}

void sh_uartw(void *priv, char *b, int n)
{
	uart_t *o = (uart_t *) priv;
	uart_w(o, b, n);
}

#if _EXE_

#include <hcos/task.h>
#include <stdio.h>
#include "_soc.h"

static int test(char *cmd)
{
	printf("test_cmd:%s\n", cmd);
	return 0;
}

static cmd_t cmd_test = { "test", test, "" };

static void shell(void *priv)
{
	sshell_t s;
	sh_init(&s, sh_uartr, sh_uartw, &u0);
	sh_cmd_add(&s, &cmd_test);
	while (1) {
		char *cmd = sh_gets(&s);
		if (sh_exe(&s, cmd))
			printf("no such: %s\n", cmd);
	}
}

int main(void)
{
	core_init();
	task_new("shell", shell, 6, 2048, -1, 0);
	core_start();
	return 0;
}
#endif
