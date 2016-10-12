#if _EXE_
#include <hcos/task.h>
#include <stdio.h>
#include "sshell.h"
#include "_soc.h"
#include "uart.h"
#include "plt.h"

PRINTF_FLOAT;

static unsigned busy_cnt;

static int test(char *cmd)
{
	printf("hello %s\n", cmd);
	return 0;
}

static cmd_t cmd_test = { "test", test, "" };

static int ut(char *cmd)
{
	unsigned idle = load_ut.idle;
	unsigned all = load_ut.all;
	printf("sys-idle %d %d %.2f%%\n", idle, all, ((double)idle*100)/all);
	return 0;
}

static cmd_t cmd_ut = { "ut", ut, "" };

static int busy(char *cmd)
{
	busy_cnt = atoi(cmd+4);
	printf("busy=%d\n", busy_cnt);
	return 0;
}

static cmd_t cmd_busy = { "busy", busy, "" };

static char buf[128];

static void shell(void *priv)
{
	sshell_t s;
	uart_int_in(&u0, buf, 128);
	sh_init(&s, sh_uartr, sh_uartw, &u0);
	sh_cmd_add(&s, &cmd_test);
	sh_cmd_add(&s, &cmd_ut);
	sh_cmd_add(&s, &cmd_busy);
	load_ut_init(tmr_hz);
	while (1) {
		char *cmd;
		cmd = sh_gets(&s);
		if (sh_exe(&s, cmd))
			printf("no such: %s\n", cmd);
	}
}

static void calulate(void* priv)
{
	unsigned volatile sum;
	int i, j;
	while(1){
		for( i = 0 ; i < busy_cnt; i ++) {
			sum = 0;
			for( j = 0 ; j < 100; j ++)
				sum += j;
		}
		task_sleep(tmr_hz/5);
	}
}

int main(void)
{
	core_init();
	task_new("shell", shell, 6, 2048, -1, 0);
	task_new("busy", calulate, 8, 2048, -1, 0);
	core_start();
	return 0;
}
#endif
