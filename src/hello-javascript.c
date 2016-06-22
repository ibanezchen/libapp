#include <hcos/task.h>
#include <jerryscript/jerry.h>

#include <string.h>

jerry_completion_code_t code;

void js(void *priv)
{
	char script[] = "print ('hello java script');";
	code =
	    jerry_run_simple((void *)script, strlen(script), JERRY_FLAG_EMPTY);
}

#if _EXE_
int main(void)
{
	core_init();
	task_new("js", js, 56, 4096, -1, 0);
	core_start();
	return 0;
}

#endif
