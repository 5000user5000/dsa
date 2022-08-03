#include <stdio.h>
#include<stdlib.h>

void yieldseat(int* city,int index,int val);
void assignDistance(int* arr,int* city,int index,int r,int s);

typedef struct 
{
	int index;
	int distance;
	
	
	struct Tree *nxt;
	struct Tree *pre;
	
	struct Tree *top;//用於處理距離tree時,同距離是用linked list,要有辦法跳回最上面 
	
	
}Tree;

int main()
{
   int n,q,s,r;
   int index,val;
   
   scanf("%d",&n);//又忘加& 
   scanf("%d",&q);
   scanf("%d",&s);
   scanf("%d",&r);
   
   int* city;//index =city name, value= nxt city //注意不用city[n],且用指標 
   city = malloc((n+1)*sizeof(int));//n+1個(0~n) 
   city = calloc(n+1,sizeof(int));//初始化 
   
   //input n-1 road
   for(int i=1;i<n;i++) // run n-1 times
   {
   	 scanf("%d",&index);
   	 scanf("%d",&val);
   	 if(city[index] == 0) city[index] = val;//可以用陣列表示
   	 else yieldseat(city,index,val);//如果沒地方放就強制挪出 
   	 
   }
   //input q query
   int* query;
   query = malloc(q*sizeof(int));
   for(int i=0;i<q;i++)
   { 
       scanf("%d",query[i]); 
   	
   }
   
   //data process
   int* Rarr; //index->city 存取值為和s or r 的距離. 
   int* Sarr;
   Rarr = malloc((n+1)*sizeof(int));
   Rarr = calloc(n+1,sizeof(int));
   Sarr = malloc((n+1)*sizeof(int));
   Sarr = calloc(n+1,sizeof(int));
   
   Rarr[r]=0;//各自的起點 
   Sarr[s]=0; 
   //先連著起點的路徑給值 
   assignDistance(Sarr,city,s,r,s);
   assignDistance(Rarr,city,r,r,s);
   
   
   //賦予距離值 
   for(int i=1;i<=n;i++)
   {
   	  if(i!=s && Sarr[i]!=0)assignDistance(Sarr,city,i,r,s);
   	  if(i!=r && Rarr[i]!=0)assignDistance(Rarr,city,i,r,s);
   	  
   	
	} 
   //根據距離來做arr(index為距離),nxt為同輩 
   Tree* Stree = malloc(n*sizeof(int));//只要做r或s其中一個就好,為了記憶順序 
   int current;
   for(int i=0;i<n;i++)//距離只有0~n-1 
   {
   	 current = Sarr[i];
   	 Stree+=current;//地址位移 
   	 if(Stree->index!=0)//已經有相同距離了
	 {
	   Tree* old = Stree ;//不能使用 Stree->nxt->index,所以只好用old記住原本的node 
	   Stree->nxt = malloc(sizeof(Tree));
	   Stree = Stree->nxt;
	   Stree->index = i;
	   Stree->top = old->top;//方便之後只回原點 
	   Stree = old;
	 } 
	 else 
	 {
	   Stree->index = i;
	   Stree->top = Stree;
	 } 
	 Stree-=current;
	  
   	
   }
   
   //query
   int ans,ansidx;//解答的距離和其idx 
   for(int i=0;i<q;i++)
   {
   	ans = Rarr[ query[i] ];//預設為c鎮的距離值,只要看R距離最小者即為答案 
	ansidx =  query[i];
	for(int j=Sarr[ query[i] ]-1;j>=0;j--)//先往下走一步 
   	{
   		Stree += j;
		
		if(Rarr[Stree->index]<ans)
		{
			ans = Rarr[Stree->index];
			ansidx = Stree->index;
		 } 
		
			
		//如果還有nxt
		while(Stree->nxt !=NULL) 
		{
				
		  Stree = Stree->nxt;
		  if(Rarr[Stree->index]<ans)
		   {
			ans = Rarr[Stree->index];
			ansidx = Stree->index;
		    } 
		   	
			
	   }
	   Stree = Stree->top;//跳回最上面 
		
	
   	   Stree -=j;
	}
	printf("%d \n",ansidx);
   	
   	
  }
   
   
   
   
    free(city);
    free(Rarr);
    free(Sarr);
	exit(0);//這樣比return快 
	
	return 0;
}

void yieldseat(int* city,int index,int val)//val是上一個inx 
{
	int inx =index ,nxt=city[index],nxt2 =city[nxt];//值為下一個index,總共需要3個變數,存 now index, val=nxt.index , nxt.value =nxt.nxt.index 
	int value = val;
	 
	
	while(city[nxt2]!=0)//不斷nxt,直到有空位 
	{
		//下一個的nxt改成上一個index 
		city[inx]= value;
		city[nxt]= inx;
		city[nxt2] = nxt;
		
		//update
		value = nxt2;
		inx = city[nxt2];
		nxt = city[inx];
		nxt2 = city[nxt];
		
		
	}//注意city[0]=0一定要成立,如果不為0又會跳轉到其他city 
	city[inx]= value;
	if(nxt2!=0)
	{
	 city[nxt]= inx;
	 city[nxt2] = nxt;
	}
	else//remain city[0]=0
	{
		if(nxt!=0)city[nxt]= inx;
		
	}
	
}

void assignDistance(int* arr,int* city,int index,int r,int s)//賦予距離值 
{
	int inx = index,k;
	Tree* tree;//注意	
	 	
	while(city[inx]!=0)
	{
	  if(inx!=r && inx!=s&& arr[inx] ==0 )//因為有可能跳回s r
	  {
	  	Tree* treeOld = tree;
		tree->index = inx;
	  	tree->nxt = malloc(sizeof(Tree));
	  	//不能 tree->nxt->pre,因為tree->nxt只是空記憶體,沒有tree功能 
		//前後都存 
		tree = tree->nxt;
		tree->pre = treeOld;
	  	 
	   }
	  else
	  {
	  	 if(tree->pre != NULL)
	  	 {
	  	 	//往前走直到NULL,值遞減1 
	  	 	int dis = arr[inx];
	  	 	while(tree->pre != NULL)
	  	 	{
	  	 		tree = tree->pre;//因為當前tree必是空的 
				arr[tree->index]=--dis;
				if(dis<=0)break;//距離不會<=0(只有原點才會0) 
			}
	  	 	return;//結束函式 
		 }
		   
		 k = city[inx];
	     arr[k] = arr[inx]+1;//nxt dist = last +1
	   } 
	 
	  
	  inx = city[inx];//移到下一個 
	}
	
	free(tree);
	
	
}
