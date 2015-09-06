#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include"cpu/reg.h"
void cpu_exec(uint32_t);

/* We use the ``readline'' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}
static int cmd_p(char *args)
{
       // bool *k;
        //*k=true
        bool k=true;
        return (expr(args,&k));
}
static int cmd_info(char * args){
      if(!strcmp(args,"r"))
      {
            int i;
           for (i=R_EAX;i<=R_EDI;i++)
          {
           printf("%s    %x\n",regsl[i],cpu.gpr[i]._32);
           //printf("%s\n",*(regsl+i-1));
	 }
      }
      return 1;
}
static int  cmd_si(char *str)
{
        if(str)
        {
         int length=strlen(str);
         int index=0;
         int i;
         for (i=0;i<length;++i)
          {
              index*=10;
              index+=str[i]-'0';
              
          }
         
         cpu_exec(index);
       //  printf("%d",index);
      }
      else cpu_exec(1);
    // printf("%d",index);
       return 1;
}
static int cmd_q(char *args) {
	return -1;
}
static int cmd_x(char *args){

         char * index=strtok(args," ");
         int digit=0;
         int i;
         for( i=0;i<strlen(index);++i)
        {
            digit*=10;
            digit+=index[i]-'0';
        }
        int sum=0;
        char *arv=args+1+strlen(index);
        for (i=2;i<strlen(arv);++i)
        {
           sum*=16;
           if (arv[i]>='a') sum+=10+arv[i]-'a';
           else sum+=arv[i]-'0';
        }
       for (i=0;i<digit;++i)
       printf("%02x  ",swaddr_read(sum+i,1));
       printf("\n");         
return 1;
}
static int cmd_help(char *args);

static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit NEMU", cmd_q },
        {"si"," the times",cmd_si},
        {"info","print the state",cmd_info},
	{"x","visit the memory",cmd_x},
        {"p","expr",cmd_p}

        /* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}

void ui_mainloop() {
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }
		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
		if(strcmp(cmd, cmd_table[i].name) == 0) {
//                                 if(strcmp(cmd,"si"))
  //                               {
//
  //                                if( cmd_si(str)) return;
                                               
    //                             }	

//                     	else 
			if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}

		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
