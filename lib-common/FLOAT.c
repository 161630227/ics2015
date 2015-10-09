#include "FLOAT.h"

FLOAT F_mul_F(FLOAT a, FLOAT b) {
        int index=0;
	if(a<0)
	{
		a=-a;
		index++;
	}
	if(b<0)
	{
	       b=-b;
	       index++;
	}
	unsigned int a1=(a>>16);
	unsigned int  b0=b&0xffff;
	unsigned int  a0=a&0xffff;
	unsigned int b1=(b>>16);
	unsigned int  c0=(a0*b0)/0xffff;
	unsigned int c1=a1*b0+a0*b1+c0;
	unsigned int c2=(a1*b1)<<16;
	c2+=c1;
	if(index%2==0) return c2;
	  else return -c2;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
  unsigned int i,ans,nb;
   nb=31; 
  unsigned int  a0=a&0xffff;
   unsigned int  a1=(a>>16);
   unsigned int  a11=(a0<<16);
   ans=0;
   for (i=1;i<=32;++i)
   {
	   if(a1>=b)							              {
									                 ans+=a1/b;								     a1=a1%b;
 	   }	
	   a1<<=1;							             a1+=(a11>>nb);							        if(a11>>nb) a11-=(1<<nb);ans=(ans<<1);					   nb--;
   }	
   return ans;
}

FLOAT f2F(float a) {
	int b=*(int *)&a;
	unsigned int  b1=b;
	int mid=b>>23;
	
	if(b<0)mid=mid&0xff;
	unsigned int back;
	if(b<0) back=b1-(mid<<23)-(1<<31);
	  else  back=b1-(mid<<23);
	back+=(1<<23);
	if(mid>=127)
	{
		mid-=127;
		mid+=16;
                if(mid>=23) back<<=(mid-23);
		else
		{	back=back>>(23-mid);
		}
	}
	else
	{
		int mid1=mid-127;
                mid1+=16;
		back>>=(23-mid1);
	}
        int back1=back;
	if(b<0) back1=-back1;
	return back1;
}

FLOAT Fabs(FLOAT a) {
	return a >=0 ? a : -a;
	return 0;
}

FLOAT sqrt(FLOAT x) {
	FLOAT dt, t = int2F(2);

	do {
		dt = F_div_int((F_div_F(x, t) - t), 2);
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

FLOAT pow(FLOAT x, FLOAT y) {
	/* we only compute x^0.333 */
	FLOAT t2, dt, t = int2F(2);

	do {
		t2 = F_mul_F(t, t);
		dt = (F_div_F(x, t2) - t) / 3;
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

