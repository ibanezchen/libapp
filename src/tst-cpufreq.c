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

extern uart_t u0;

void cpufreq(void *priv)
{
	unsigned ts = (unsigned)priv;
	clk_t *clk = clk_cpu_init(0);
	int i;

	sshell_t s;
	sh_init(&s, sh_uartr, sh_uartw, &u0);
	irq_lock();
	while (1) {
		for (i = 0; i < 9; i++) {
			clk_setf(clk, i);
			printf("%d clk = %d\n", i, clk_getf(clk));
			task_sleep(ts);
			printf("%s\n", sh_gets(&s));
		}
		printf("wfi\n");
		__asm__ volatile ("wfi");
	}

}

#if _EXE_
int main(int argc, char **argv)
{
	int i;
	core_init();
	for (i = 0; i < argc; i++)
		printf("argv[%d] = %s\r\n", i, argv[i]);
	irq_init(12, isr_use_float);
	task_new("cpufreq", cpufreq, 56, 4024, -1, (void *)(tmr_hz * 1));
	core_start();
	return 0;
}

#endif
