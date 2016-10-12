#include <hcos/task.h>
#include <jerryscript/jerry.h>
#include "sshell.h"
#include <string.h>
#include "uart.h"

extern uart_t u0;

jerry_completion_code_t code;

void jshell(void *priv)
{
	char *script = "print ('hello java script');";
	sshell_t s;
	sh_init(&s, sh_uartr, sh_uartw, &u0);
	do {
		if ((code = jerry_run_simple((void *)script,
					     strlen(script), JERRY_FLAG_EMPTY)))
			printf("err code %d\n", code);
		script = sh_gets(&s);
	} while (1);
}

#if _EXE_
int main(void)
{
	core_init();
	task_new("jshell", jshell, 56, 4096, -1, 0);
	core_start();
	return 0;
}

#endif
