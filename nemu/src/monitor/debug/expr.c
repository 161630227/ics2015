#include "nemu.h"

/* We use the POSIX regex functions to iprocess regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
#include<string.h>
//#include<ui.h>
#include<memory.h>
enum {
	NOTYPE = 256, EQ,N,W,YU,HUO,REG,NOT,RETEF

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
	{"\\=\\=", EQ},
	{"\\!\\=",NOT},
        {"\\(",'('},
        {"\\)",')'},
	
	{"\\|\\|",HUO},
	{"\\&\\&",YU},
	{"\\$[[:alpha:]]+",REG},
        {"0x[0-9a-f]+",N},	
        {"[0-9]+",W} 
//	{"0x[0-9a-f]+",N},//nei cun					// equal
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
static int make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;

	nr_token = 0;
	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;
                               
				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;
				
				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array ``tokens''. For certain 
				 * types of tokens, some extra actions should be performed.
				 */

				switch(rules[i].token_type) {
					case '+':
						tokens[nr_token].type='+';
	          				nr_token++;	break;
	
					case '-':
						tokens[nr_token++].type='-';
						break;
					case '*':
						tokens[nr_token++].type='*';
						break;
					case '/':
						tokens[nr_token++].type='/';
						break;
					case EQ:
						tokens[nr_token++].type=EQ;
						break;
					  case N:
						tokens[nr_token].type=N;
					        int kk=0;
						for ( kk=0;kk<substr_len;++kk)
			                        tokens[nr_token].str[kk]=e[position-substr_len+kk];
						nr_token++;
					        break;

					case W:
						tokens[nr_token].type=W;
						int ku=0;
						for ( ku=0;ku<substr_len;++ku)
 							tokens[nr_token].str[ku]=e[position-substr_len+ku];
						nr_token++;
            
	                                        break;
					case REG:
						tokens[nr_token].type=REG;
                                                int k1=0;
						for ( k1=0;k1<substr_len;++k1)
		                                tokens[nr_token].str[k1]=e[position-substr_len+k1];
						nr_token++;
						break;
					case YU:tokens[nr_token++].type=YU;
						break;
					case HUO:tokens[nr_token++].type=HUO;
						break;

					case '(':
						tokens[nr_token++].type='(';
						break;
					case ')':
						tokens[nr_token++].type=')';
						break;
					case NOT:
						tokens[nr_token++].type=NOT;
						break;
					default: panic("please implement me");
				}
			//	pintf("%d\n",tokens[nr_token-1].type);
				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
            			return -1;
		}
	}

     {  
	     return nr_token;} 
}
//nr_token--; nr_token2=nr_token; 
/*
static bool make_token(char *e)
{
	rintf("hello");
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
          if((tokens[k].type==YU||tokens[k].type==HUO))
	  {
		  op=k;
		  index=true;
		  break;
          }
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
             if(((tokens[k].type=='*')||(tokens[k].type=='/'))&&(!index))
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
     if(!index)
     {
	     k=q;
	    while(k>p)
	    {
		    if(((tokens[k].type==NOT)||(tokens[k].type==EQ))&&(!index))
		    {
		      op=k;
		    //  printf("here\n");
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
            
 /*   if(!index)
    {
	     k=q;
          while(k>p)
            {       
		    if(((tokens[k].type==RETEF)&&(!index))
                    {
                       op=k;
                     //  printf("here\n");
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
*/
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
        int index=make_token(e);
	//index=make_token(e);
	int i1;
	for(i1=0;i1<nr_token;++i1)
		if((tokens[i1].type=='*')&&(i1==0||((tokens[i1-1].type!=N)&&(tokens[i1-1].type!=W)&&(tokens[i1-1].type!=REG))))
					tokens[i1].type=RETEF;
	if(index==-1) {
		
		*success = false;
		return 0;	}
	else { 
		return eval(0,nr_token-1);
        }
}      
int eval(int p,int q)
        {
	//	rintf("q:%d\n",q);
           if(p>q)
           {
           printf("error");
            return 0;
           }
           else if(p==q)
           {
 
       		   int k=0;
		   int sum=0;
          	   if(tokens[p].type==W)
                   { 
                  
			   for(k=0;k<=strlen(tokens[p].str)-1;++k)
                           {
              
				   sum*=10;
                                   sum+=tokens[p].str[k]-'0'; 
                            }
            // return sum;
                   }
	           else if(tokens[p].type==N)
	                {
	       
				int sum1,i;
	                        sum1=0;
	      
                                for (i=2;i<strlen(tokens[p].str);++i)
                                {      
                
					sum1*=16;
                                        if (tokens[p].str[i]>='a') sum1+=10+tokens[p].str[i]-'a';
                                        else sum1+=tokens[p].str[i]-'0';
                                }
	                        //  printf("sum1=  %d\n",sum1);
	                       printf("sum= %x\n",sum1);
	                        sum=swaddr_read(sum1,1);
               
	                }
	          else if(tokens[p].type==REG)
	          {	
       		     
		
			  for (k=R_EAX;k<=R_EDI;k++)
	      	          {
		  
				  if(!strcmp(tokens[p].str,regsl[k]))
		                  {
                                         printf("%s  %d\n",tokens[p].str,k);
			                  sum=reg_l(k);
					  //sum=cpu.gpr[k]._32;
					  printf("sum=  %d\n",sum);
			                  break;
	                           }		  
                           } 
	          }
            return sum;
	   }
	   
           else if(check_parentheses(p,q))
          
           return eval(p+1,q-1);
           else if(tokens[p].type==RETEF)
           {
          
		   int sum7=0;
	           /*int k2;
	           for (k2=2;k2<strlen(tokens[q].str);++k2)
	           {
		   
			   sum7*=16;
		           if (tokens[q].str[k2]>='a') sum7+=10+tokens[q].str[k2]-'a';
		           else sum7+=tokens[q].str[k2]-'0';
		      //      return swaddr_read(sum7,1);
                    }
		   return swaddr_read(sum7,1);
	           */
		  sum7=eval(p+1,q);
	          printf("*  %x\n",sum7);
		  return (swaddr_read(sum7,4));

	 } 

          
          else
          {
      
          
		  int op=find(p,q);
                  //if(op!=p)
	          if(op==p) 
	          {
		 
			  assert(0);
			  return 0;
                  }
          //rintf("op=%d\n",op);      
                  int  val1=eval(p,op-1);
        //rintf("val1%d\n",val1);
                  int  val2=eval(op+1,q);
	 // printf("val2=%d\n",val2);
                 switch(tokens[op].type)
                {
            
			case'+': return val1+val2;
                        case'-': return val1-val2;
                        case'*': return val1*val2;
                        case'/': return val1/val2;
                        case HUO:
		        if(val1) return 1;
		         else if(val2) return 1;
		          else return 0;//return val1||val2;
		     
		    // return 10;
	    case YU:
		     if(val1&&val2)return 1;
                     else return 0;		     
            case NOT:
		      if(val1!=val2) return 1;
		      else return 0;
	    case EQ:
		      printf("te\n");
		      if(val1==val2) return 1;
		      else return 0;
	    default:{
                    assert(0);
                   return 0;
                    }
                }
          
        }       
        
//	TODO: Insert codes to evaluate the expression. */
      //	panic("please implement me");
    return 0; 
}

