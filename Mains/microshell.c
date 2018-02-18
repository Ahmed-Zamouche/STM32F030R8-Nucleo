#include <stdio.h>
#include <string.h>

#include "msuart.h"
#include "microshell.h"
#include "mscmd.h"
#include "msconf.h"

#include "ntlibc.h"
#include "timer.h"
#include "led.h"


typedef struct {
    int (*puts)(const char *str);
} USER_OBJECT;

static MSCMD_USER_RESULT usrcmd_timer(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_led(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_help(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_quit(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);

static MSCMD_COMMAND_TABLE table[] = {
    {   "timer",     usrcmd_timer   },
    {   "led",      usrcmd_led      },
    {   "help",     usrcmd_help     },
    {   "quit",     usrcmd_quit     },
};

static void utx(char c)
{
    msuart_putc(c);
}

static char urx(void)
{
    return msuart_getc();
}

static void action_hook(MSCORE_ACTION action)
{
}

static MSCMD_USER_RESULT usrcmd_timer(MSOPT *msopt, MSCMD_USER_OBJECT usrobj)
{
	char buf[MSCONF_MAX_INPUT_LENGTH];
    int argc;

    USER_OBJECT *uo = (USER_OBJECT *)usrobj;

    uo->puts("Timer: ");
    msopt_get_argc(msopt, &argc);
    if(argc != 2){
    	uo->puts("argc error!\r\n");
    	return -1;
    }

    msopt_get_argv(msopt, 1, buf, sizeof(buf));

    if(!strcmp(buf, "start"))
    {
    	timer_start(TIMER_1);
    }else
    if(!strcmp(buf, "stop")){
    	timer_stop(TIMER_1);
    }else
    if(!strcmp(buf, "value")){
    	uint32_t value = timer_counterValue(TIMER_1);
    	uo->puts(buf);
    	uo->puts(" = ");
    	ntlibc_itoa(value, buf, 10);
    }else{
    	uo->puts("argv[1] error!\r\n");
    	return -2;
    }
    uo->puts(buf);
    uo->puts("\r\n");
    return 0;
}

static MSCMD_USER_RESULT usrcmd_led(MSOPT *msopt, MSCMD_USER_OBJECT usrobj)
{
	char buf[MSCONF_MAX_INPUT_LENGTH];
    int argc;

    USER_OBJECT *uo = (USER_OBJECT *)usrobj;

    uo->puts("LED: ");
    msopt_get_argc(msopt, &argc);
    if(argc != 2){
    	uo->puts("argc error!\r\n");
    	return -1;
    }

    msopt_get_argv(msopt, 1, buf, sizeof(buf));

    if(!strcmp(buf, "on"))
    {
    	Led_Set(LED_1, true);
    }else
    if(!strcmp(buf, "off")){
    	Led_Set(LED_1, false);
    }else
    if(!strcmp(buf, "toggle")){
    	Led_Toggle(LED_1);
    }else{
    	uo->puts("argv[1] error!\r\n");
    	return -2;
    }
    uo->puts(buf);
    uo->puts("\r\n");
    return 0;
}

static MSCMD_USER_RESULT usrcmd_quit(MSOPT *msopt, MSCMD_USER_OBJECT usrobj)
{
    USER_OBJECT *uo = (USER_OBJECT *)usrobj;
    uo->puts("bye\r\n");

    return 0;
}

static MSCMD_USER_RESULT usrcmd_help(MSOPT *msopt, MSCMD_USER_OBJECT usrobj)
{
    USER_OBJECT *uo = (USER_OBJECT *)usrobj;
    uo->puts(
    		"timer  : (start|stop|value)\r\n"
    		"led    : (on|off)\r\n"
            "help   : help command\r\n"
            );
    return 0;
}

int main(void)
{
    char buf[MSCONF_MAX_INPUT_LENGTH];

    MICROSHELL ms;
    MSCMD mscmd;
    USER_OBJECT usrobj = {
            .puts = msuart_puts,
    };

    msuart_init();
    msuart_puts(
            "\r\n\r\n"
            "======================================\r\n"
            " MicroShell for  STM32F030R8 Nucleo   \r\n"
            "======================================\r\n"
            );
    msuart_puts(" Type 'help' for a list of commands.\r\n");

    microshell_init(&ms, utx, urx, action_hook);
    mscmd_init(&mscmd, table, sizeof(table) / sizeof(table[0]), &usrobj);

    while (1) {
    	MSCMD_USER_RESULT r;
        msuart_puts("MicroShell>");
        microshell_getline(&ms, buf, sizeof(buf));
        mscmd_execute(&mscmd, buf, &r);
    }

    return 0;
}
