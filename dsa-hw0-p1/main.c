#include<stdio.h>
#include <string.h>

int getLength(char arr[257]);
void copy(char a[],char m[]);
void subtract(char m[],char n[]);
void arrange(char m[],int len);
void half(char a[]);
void multify(int times,char n[]);//先把要用的函數先宣告 

int main()
{
	char a[257]={0},b[257]={0},m[257]={0},n[257]={0};//一格只傳一個值 ,比int好用 ,最多只有256位數 ,先訂空位,不然會亂數 
	int ans =1,mLength,nLength;
	
	scanf("%s",a);//輸入也變麻煩 ,看情況決定要不要用& ,還有注意最大位數在第一個a[0]處 
	scanf("%s",b);
	
	
	//把大的給m,小的給n 
	if(getLength(a)>getLength(b))//先比位數大小 
	{
		copy(a,m);
		copy(b,n);
	}
	else if(getLength(a)<getLength(b))
	{
		copy(b,m);
		copy(a,n);
	}
	else//位數相同就只能老實比 
	{
		int i=0,k=0;
		while((int)a[i]>47)
		{
			if((int)a[i]>(int)b[i])
			{ copy(a,m);
		      copy(b,n);
		      k=1;
		      break;//即使跳出迴圈省時間 
				
			}
			if((int)a[i]<(int)b[i])
			{ copy(b,m);
		      copy(a,n);
		      k=1;
		      break;
				
			}
			if(i==getLength(a)-1&&k==0)//考慮兩數相同情況,用k是怕break後跑進來這if 
			{
			  copy(a,m);
		      copy(b,n);
		      break;
			}
			i++; 
		}
		
	}	  
	
	//開始找公因數 
	while((int)m[0]-48>0 && (int)n[0]-48>0) 
	{
		mLength = getLength(m);
		nLength = getLength(n);
		int mEnd,nEnd;
		mEnd = (int)m[mLength-1]-48;
		nEnd = (int)n[nLength-1]-48;
		
		if(mEnd% 2==0 && nEnd%2==0 )
		{
			ans*=2;
			half(n);
			half(m); 
		}
		else if(nEnd%2==0)half(n);
		else if(mEnd%2==0)half(m); 
		
		//如果n較大就交換
		mLength = getLength(m);
		nLength = getLength(n);
		if(nLength>mLength) 
		{
			char temp[257]={0};//忘記補0了 
			copy(m,temp);
			copy(n,m);
			memset(n, (char)(0), 257);//string.h,把n全歸零,不然copy的話,因為n位數多,無法用到n的尾巴 
			copy(temp,n);
		}
		else if(nLength==mLength)
		{
			for(int i=0;i<mLength;i++)
			{
				
				
				if((int)n[i]>(int)m[i])
				{
					char temp[257]={0};//忘記補0了
			        copy(m,temp);
			        copy(n,m);
			        memset(n, (char)(0), 257);//歸0不是'0' 
			        copy(temp,n);
			        break;
				
				  
				}
				
				else if((int)m[i]>(int)n[i])//放在下面,如果放成第一個if,會跳到下個if內,loop跳不出 
				    break;
								
				
			}
		}
		//m = m -n;
		subtract(m,n);
	
		
		
	}
	multify(ans,n);
	
	for(int i=0;i<getLength(n);i++)
     printf("%d",(int)n[i] - 48);
	
	return 0;
}


/////////////////  功能函數      ////////////////////////

int getLength(char arr[257])
{
	int i=0;
	while((int)arr[i]-48>=0)i++;//只要是0~9都會符合,如果是預設的0會變成-48 
	return i;//注意不用+1,因為假設到 
}
void arrange(char m[],int len)//排列,把整個列往前挪,也許用成queue較好 
{
	
	for(int i=0;i<len-1;i++ )
	    m[i]=m[i+1];
	
	m[len-1] = (char)(0);//不改變的話,尾數還會是48not0 
//	if(len<256)m[len-1]=m[len];
//	else m[255] = (char)(0);//注意char 0和'0'是不同的,char 0的ascill code =0,扣-48 =-48 ,直接256->257就不用這麼麻煩 
	
}
void copy(char a[],char m[])//array本身就是指標,所以會改動 
{	int i=0;
	while((int)a[i]>47){
	m[i]=a[i];
	i++;
	}
	
}
void subtract(char m[],char n[])//m = m-n
{
	int mLen = getLength(m);
	int	nLen = getLength(n);
	
	int i = mLen - 1;
	int j = nLen - 1;
	int down=0;
	int nVal =0;//用來應付m位數大過n兩位以上
	while(i >= 0)
	{
		if(j>=0)
		{
		    nVal=(int)n[j];
		}
		else nVal =48;
		  
		  
		if((int)m[i]-down>=nVal)
		 { 
			m[i] = (char)((int)m[i]-nVal-down + 48);
			down=0;
		 }
		 else
		 {
			m[i] = (char)((int)m[i] + 10 - nVal -down + 48);//加減法,從前面要10
			down =1;
			//m[i - 1] = (char)((int)m[i - 1] - 1 );if pre is 0 
		 }
		    
		
		i--;
		j--;
	}
	while((int)m[0] - 48==0)//如果出現0026->026,所以必須用while 
	{
		arrange(m,mLen);
		
	}
	
} 

void half(char a[])//除以2
{

   int len = getLength(a),down=0,value;//down 退一位要補的數字 
   for(int i=0;i<len;i++)
   {
    
	value = (int)a[i] - 48;//因為a[i]會改動,這樣算down的值會變 
	a[i] = (char)( (value)/2+48+down);
	//if( (value)%2 !=0 && i!= len-1 ) 把a[i]挪在前面就不用看if 
	down=(value*5)%10;// val*10/2後取尾數 
	
   	
   }
   
   if((int)a[0] - 48==0)
    	arrange(a,len);
		
	
}
void multify(int times,char n[])
{
	int len = getLength(n),length=0;
	int upNow=0,upPre=0;//進位 
	int times_len = 0,times2=times;//紀錄倍數的長度 
	
	while(times2>0)
	{
		times2/=10;
		times_len++;
	}
	
	 
	for(int i=len+times_len-1;i>times_len-1;i--)
	  {   n[i]=n[i-times_len];//先往後移,把首位空出來進位,error 不應只退一格,如132*245就要退兩格,保守應該退ans的長度 
	      n[i-times_len] = '0';//挪完就改成0 
	 } 
	//length =len;
	
	
	for(int i=len+times_len-1;i>=0;i--)
    {
       upNow =  ( ((int)n[i] - 48)*times +upPre);
	    
	    if( upNow >= 10  )
	    {
	  	  
		  n[i] = (char)( upNow%10+48);
		  upNow =  upNow/10;
		  upPre = upNow;
		  
		  
	   }
	   else
	   {
	   	 n[i] = (char)( upNow%10+48);
	   	 upPre =0;//因為沒進位
	   }
   	
   	
   	
    }
	 
	

   
   while((int)n[0] - 48==0)//避免首位0 
   {
		arrange(n,len+times_len);
		
	}
	
	
	
	
}
 
 
