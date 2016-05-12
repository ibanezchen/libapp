#include <hcos/core.h>
#include <hcos/task.h>
#include <hcos/soc.h>
#include <hcos/mod.h>
#include <string.h>
#include <stdio.h>

#if _EXE_

static void hellof(void *priv)
{
	unsigned ts = (unsigned)priv;
	unsigned i = 0;
	while (1) {
		printf("Hello %6d\r\n", i++);
		task_sleep(ts);
	}
}

int main(void)
{
	core_init();
	task_new("hello-1", hellof, 56, 1024, -1, (void *)50);
	task_new("hello-2", hellof, 10, 1024, -1, (void *)100);
	core_start();
	return 0;
}
#endif
