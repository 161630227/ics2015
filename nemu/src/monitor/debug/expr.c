#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
#include<string.h>
enum {
	NOTYPE = 256, EQ,W

	/* TODO: Add more token types */

};
int eval(int p,int q);
static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// spaces
	{"\\+", '+'},
        {"-", '-'},
        {"\\*", '*'},
        {"\\/", '/'},					// plus
	{"==", EQ},
        {"\\(",'('},
        {"\\)",')'},
        {"[0-9]+",W} 
						// equal
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret != 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;
int nr_token2;
static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;

	nr_token = 0;
	//printf("make_tken");
	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;
                              //  printf("fuck"); 
				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;
				//printf("true");
				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array ``tokens''. For certain 
				 * types of tokens, some extra actions should be performed.
				 */

				switch(rules[i].token_type) {
					case '+':
						tokens[nr_token++].type='+';
						break;
					case '-':
						tokens[nr_token++].type='-';
						break;
					case '*':
						tokens[nr_token++].type='*';
						break;
					case '/':
						tokens[nr_token++].type='/';
						break;
					case W:
						tokens[nr_token].type=W;
						int kk=0;
						for ( kk=0;kk<substr_len;++kk)
							tokens[nr_token].str[kk]=e[nr_token+kk];
						nr_token++;
						break;
					case '(':
						tokens[nr_token++].type='(';
						break;
					case ')':
						tokens[nr_token++].type=')';
						break;
					default: panic("please implement me");
				}
				printf("%d\n",tokens[nr_token-1].type);
				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

     { printf("%d",nr_token);
       nr_token2=nr_token;     
	     return true;} 
}
//nr_token--;

/*
static bool make_token(char *e)
{
	printf("hello");
return false;
}
*/

int find(int p,int q)
{

      int k=q;
      int op;
      bool index=false;//decide whether have found op
      while(k>p)
      {

          if((tokens[k].type=='+')||(tokens[k].type=='-'))
          {
            op=k;
            index=true;
            break;
          }
          else if((tokens[k].type==')')&&k>p)
                {
                    while((tokens[k].type!='('&&(k>p))) k--;
                }
          k--;
       }
      if(!index)
      {
          k=q;
          while(k>p)
          {
             if(((tokens[k].type=='*')||(tokens[k].type=='/'))&&index)
             {
               op=k;
               index=true;
               break;
             }
             else if((tokens[k].type==')')&&k>p)
                {
                    while((tokens[k].type!='('&&(k>p))) k--;
                }
            k--;
          }
     }
   if (index) return op;
   else return p;
} bool check_parentheses(int p,int q)
{
        if(tokens[p].type=='('&&tokens[q].type==')') return true;
        else return false;
}

uint32_t expr(char *e,bool *success) {
     
	if(!success)
	{
		bool temp=true;
		success=&temp;
		
	}

	if(!make_token(e)) {
		
		*success = false;
		return 0;	}
	else {  printf("%d",nr_token2);
		return eval(0,nr_token-1);
        }
}      
int eval(int p,int q)
        {
           if(p>q)
           {
            printf("error");
            return 0;
           }
           else if(p==q)
           {
             int k=0;
             int sum=0;
             for(k=0;k<=strlen(tokens[p].str)-1;++k)
             {
               sum*=10;
               sum+=tokens[p].str[k]-'0'; 
             }
             return sum;
           }
           else if(check_parentheses(p,q))
          
           return eval(p+1,q-1);
         
        else
          {
          int op=find(p,q);
          //if(op!=p)
        
          int  val1=eval(p,op-1);
          int  val2=eval(op+1,q);
          switch(tokens[op].type)
          {
            case'+': return val1+val2;
            case'-': return val1-val2;
            case'*': return val1*val2;
            case'/': return val1/val2;
            default:{
                    assert(0);
                    //return 0;
                    }
          }
          
       }       
        
//	TODO: Insert codes to evaluate the expression. */
      //	panic("please implement me");
     
}

