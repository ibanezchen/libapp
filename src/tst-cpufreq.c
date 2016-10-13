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
#include <hcos/task.h>
#include <hcos/soc.h>
#include <hcos/io.h>
#include <hcos/cpu/nvic.h>
#include <hcos/clk-cpu.h>

#include <string.h>
#include <stdio.h>

#include "term.h"
#include "sshell.h"
#include "uart.h"
#include "plt.h"

#define MEASURE		0

extern uart_t u0;

void cpufreq(void *priv)
{
	int i;
	unsigned ts = (unsigned)priv;
	clk_t *clk;
	sshell_t s;

	plt_init();	
	clk = clk_cpu_init(0);
	sh_init(&s, sh_uartr, sh_uartw, &u0);
#if MEASURE
	irq_lock();
#endif
	while (1) {
		for (i = 0; i < 9; i++) {
			clk_setf(clk, i);
			printf("%d clk = %d\n", i, clk_getf(clk));
			task_sleep(ts);
#if MEASURE
			printf("press\n");
			sh_gets(&s)
#endif
		}
#if MEASURE
		printf("wfi\n");
		__asm__ volatile ("wfi");
#endif
	}
}

#if _EXE_

int main(void)
{
	core_init();
	task_new("cpufreq", cpufreq, 56, 4024, -1, (void *)(tmr_hz * 1));
	core_start();
	return 0;
}

#endif
