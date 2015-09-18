#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_list[NR_WP];
static WP *head, *free_,*index1,*index2;

void init_wp_list() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_list[i].NO = i;
		wp_list[i].v=0;
		wp_list[i].watch_expr=NULL;
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
      index2=head;      
      free_=free_->next;
      if(head)
      {
	      head->next=index1;
	      index1->next=index2->next;
	      return index1;
	      
      }
      else
      {
	      head=index1;
	      index1->next=NULL;
	      head->next=NULL;
	      return index1;
      }
      if(free_==NULL) 
      {
	   printf("no more free");
	  // return NULL;
      }
     // return (index1);

}
void pri()
{
	 WP* index5=head;
	 while(index5!=NULL)
	 {
		 printf("NO%d  expr%s  v%d  \n",index5->NO,index5->watch_expr,index5->v);
		 index5=index5->next;
			   
       	 }
   return;
}
void free_wp(WP *wp)
{
    index1=free_;
    index2=head;
    if(wp!=head)
   {	 
	   while(index2->next!=wp)
           index2=index2->next;
	   index2->next=wp->next; 
   }
    else
	    head=head->next;
  
    if(index1!=NULL)
    {
	    free_=wp;
            free_->next=index1;
            free_->watch_expr=NULL;
            free_->v=0;	    
    }
   else
    {
	    free_=wp;
	    free_->v=0;
	    free_->watch_expr=NULL;
	    free_->next=NULL;
    }	    
}
bool check_watchpoint()
{
   index1=head;
   bool x2=false;
   if(index1)
	   while(index1!=NULL)
	   {
		   bool k=true;
		   uint32_t rst=expr(index1->watch_expr,&k);
		   if((rst!=index1->v))
		   {
		 	   printf("nemu: HIT watchpoint %d:%s\n\nOld value = %d\nNew value = %d\n",index1->NO, index1->watch_expr, index1->v, rst);
                           x2=true;
	           }
		   index1=index1->next;
           }
   return x2;
}
