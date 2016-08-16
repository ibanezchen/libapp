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
#include <hcos/core.h>
#include <hcos/task.h>
#include <hcos/soc.h>
#include <hcos/sem.h>
#include <hcos/mq.h>
#include <string.h>
#include <stdio.h>
#include "plt.h"

#if _EXE_

PRINTF_FLOAT;

#define CNTB	(10000<<3)

static sem_t sem;

static mut_t mut;

static mq_t mq;

static int cnt;

static double inter, semp, semg, cs, lockunlock, mqsend, mqget;

static irq_handler(addcnt)
{
	cnt++;
	return IRQ_DONE;
}

static double strip(double off)
{
	return off - (off * inter) / CNTB;
}

<<<<<<< HEAD
=======
int bench_mm(void);

int bench_mm2(void);

>>>>>>> 36ec004... Add API benchmark
static void t1(void *priv)
{
	int i;
	unsigned t, t1;

	// interrupt
	cnt = 0;
	t = tmr_ticks;
	while (cnt < CNTB)
		irq_sgi(12);
	t1 = tmr_ticks;
	inter = t1 - t;
	printf("%8dx%12s = %f\n", CNTB, "interrupt", inter / tmr_hz);

	// Semaphore post
	t = tmr_ticks;
	for (i = 0; i < CNTB; i++)
		sem_post(&sem);
	t1 = tmr_ticks;
	semp = strip(t1 - t);
	printf("%8dx%12s = %f\n", CNTB, "sem post", semp / tmr_hz);

	// Semaphore get
	t = tmr_ticks;
	for (i = 0; i < CNTB; i++)
		sem_get(&sem, WAIT);
	t1 = tmr_ticks;
	semg = strip(t1 - t);
	printf("%8dx%12s = %f\n", CNTB, "sem get", semg / tmr_hz);

	// context-switch
	t = tmr_ticks;
	for (cnt = 0; cnt < CNTB; cnt++)
		sem_get(&sem, WAIT);
	t1 = tmr_ticks;
	cs = strip(t1 - t) - semg - semp;
	printf("%8dx%12s = %f\n", CNTB, "c-switch", cs / tmr_hz);

	// mutex lock & unlock
	t = tmr_ticks;
	for (cnt = 0; cnt < CNTB; cnt++) {
		sem_get(&sem, WAIT);
		mut_lock(&mut, WAIT);
		mut_unlock(&mut);
	}
	t1 = tmr_ticks;
	lockunlock = (strip(t1 - t) - cs - semg - semp) / 2;
	printf("%8dx%12s = %f\n", CNTB, "lock-unlock", lockunlock / tmr_hz);

	// message queue
	mqsend = 0;
	mqget = 0;
	for (cnt = 0; cnt < CNTB; cnt += mq.sz) {
		unsigned d = 0xbeefbeef;
		t = tmr_ticks;
		for (i = 0; i < mq.sz; i++)
			mq_put(&mq, &d, WAIT);
		t1 = tmr_ticks;
		mqsend += t1 - t;

		t = tmr_ticks;
		for (i = 0; i < mq.sz; i++)
			mq_get(&mq, &d, WAIT);
		t1 = tmr_ticks;
		mqget += t1 - t;
	}
	mqsend = strip(mqsend);
	mqget = strip(mqget);
	printf("%8dx%12s = %f\n", CNTB, "mqsend", mqsend / tmr_hz);
	printf("%8dx%12s = %f\n", CNTB, "mqget", mqget / tmr_hz);

	t = tmr_ticks;
	i = bench_mm();
	t1 = tmr_ticks;
	printf("%8dx%12s = %f\n", i, "malloc,free", strip(t1 - t) / tmr_hz);

#ifdef CFG_BUDDY
	t = tmr_ticks;
	i = bench_mm2();
	t1 = tmr_ticks;
	printf("%8dx%12s = %f\n", i, "malloc,free2", strip(t1 - t) / tmr_hz);
#endif
	printf("ok\n");
}

static void t2(void *priv)
{
	while (cnt < CNTB)
		sem_post(&sem);
	while (cnt < CNTB) {
		mut_lock(&mut, WAIT);
		sem_post(&sem);
		mut_unlock(&mut);
	}
}

static void bench_api(void *priv)
{
	unsigned *buf;
	plt_init();
	irq_init(12, addcnt);
	sem_init(&sem, 0);
	mut_init(&mut);
	buf = core_alloc(4096, 2);
	mq_init(&mq, 1, buf, 4096);
	task_new("t1", t1, 10, 1024, -1, 0);
	task_new("t2", t2, 11, 1024, -1, 0);
}

int main(void)
{
	core_init();
	task_new("benchmark", bench_api, 2, 1024, -1, 0);
	core_start();
	return 0;
}
#endif
