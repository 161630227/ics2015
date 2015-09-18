#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_list[NR_WP];
static WP *head, *free_,*index1;

void init_wp_list() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_list[i].NO = i;
		wp_list[i].next = &wp_list[i + 1];
	}
	wp_list[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_list;
}

/* TODO: Implement the functionality of watchpoint */
WP* new_wp()
{
      index1=free_;	
      free_=free_->next;
      if(free_==NULL) 
      {
	   printf("no more free");
	   return NULL;
      }
      return (index1);
}
void free_wp(WP *wp)
{
    index1=free_;
    if(index1!=NULL)
    {
	    free_=wp;
	    free_->NO=wp->NO;
            free_->next=index1;	    
    }
   else
    {
	    free_=wp;
	    free_->next=NULL;
    }	    
}

