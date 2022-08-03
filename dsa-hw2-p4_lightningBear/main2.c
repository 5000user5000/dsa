#include <stdio.h>
#include <stdlib.h>


typedef struct 
{
	int index;
	int dim;//n叉樹第幾層 
	 
	//int isRoot;//0 no,1 yes
	int hasNxt;//如果有nxt->1 
	struct Tree *child;
	struct Tree *nxt;//如果有多的child就用nxt存 
	struct Tree *parent;
	
	struct Tree *top;//用於處理距離tree時,同距離是用linked list,要有辦法跳回最上面 
	
	
}Tree;

void insertNear(Tree* city,int val);
void link(Tree* tree,Tree* node,Tree* old,int root);
void build(Tree* tree,Tree* Near,int root,int avoid,Tree* old);

int main()
{
   int n,q,s,r;
   int index,val;
   
   scanf("%d",&n);//又忘加& 
   scanf("%d",&q);
   scanf("%d",&s);
   scanf("%d",&r);
   
   Tree* city;//改存成下一個的index 
   city = malloc((n+1)*sizeof(Tree));//n+1個(0~n) 
   //city = calloc(n+1,sizeof(int));//初始化,似乎不用 
   
   //input n-1 road
   for(int i=1;i<n;i++) // run n-1 times
   {
   	 scanf("%d",&index);
   	 scanf("%d",&val);
   	 //index下,存附近的node 
	 city+=index;
   	 insertNear(city,val);
   	 city-=index;
   	 //雙向存 
   	 city+=val;
   	 insertNear(city,index);
   	 city-=val;
   }

   //input q query
   int* query;
   query = malloc(q*sizeof(int));
   for(int i=0;i<q;i++)
   { 
       scanf("%d",query);//pointer地址不能用陣列,query[3]是值(非址) ,scanf只能用地址 
	   query++; 
   	
   }
   query-=q;
   
   //data process
   Tree* Rarr; 
   Tree* Sarr;
   Rarr = malloc((n+1)*sizeof(Tree));    
   Sarr = malloc((n+1)*sizeof(Tree));
   
   Tree* oldR =Rarr;
   Tree* oldS =Sarr;
   Rarr+=r;
   Sarr+=s;
   
   build(Rarr,city,r,r,oldR);
   build(Sarr,city,s,s,oldS);
   
   Rarr = oldR;
   Sarr = oldS;
   
   //query
   int ans,ansidx,c;//解答的距離和其idx 
   
   for(int i=0;i<q;i++)//設s往回走,對應在r上深度越小者勝 
   {
   	c = query[i];
   	Rarr+=c;
   	
	ans = Rarr->dim;//r上深度
	ansidx =  c;
	Rarr-=c;//back
	
	
	Sarr+=c;
	
	
	while(Sarr->parent !=NULL)
	{
		Sarr = Sarr->parent;
		int m = Sarr->index;
		Rarr+=m;
		if(Rarr->dim < ans)
		{
			ans = Rarr->dim;
			ansidx = m;
		}
		Rarr-=m;
		
	}
	
	
	printf("%d \n",ansidx);
   	
   	Sarr = oldS;//back
  }
   
   
   
   
   /* free(city);
    free(Rarr);
    free(Sarr);
    free(Stree);*/ //直接exit應該就不用free 
	exit(0);//這樣比return快 
	
	return 0;
}



void insertNear(Tree* city,int val)//把每一個NODE鄰近點存起來 
{
	 Tree* old =city;
	 while(city->nxt!=NULL)
   	 {
		city = city->nxt;
		
		}
	 city->nxt = malloc(sizeof(Tree));
	 city = city->nxt;
	 city->index=val;
	 city = old;//還原 
	
 } 

void build(Tree* tree,Tree* Near,int root,int avoid,Tree* old)//建立樹,avoid是用來迴避dim=0的root (s or r)
{
	 
	Tree *oldNear =Near;
	
	//tree+=root;	tree應為當前節點(input記得要+r or s),old才是從0開始 
	Near+=root;
	
	Tree *thisold = tree;//此部分的最高父節點
	
	while(Near->nxt !=NULL)
	{
		Near = Near->nxt;
		root = Near->index;
		
		
		if(Near->dim ==0 && root!=avoid)//已經用過(包括最上面)就不要再跑了
		{
		 //link是用父節點,build是用當前節點 
		 
		 link(tree,Near,old,root);  
		
		
		 //tree = old;//tree應該要是當前位置 
		 build(tree,oldNear,root,avoid,old);//遞迴 
	   }
	   //else tree = old;//應該要是當前位置
	   tree = thisold;//恢復當前父節點 
	}
	
   
   Near =oldNear;
   


} 

void link(Tree* tree,Tree* node,Tree* old,int root)//協助build把node link到原樹 
{
    int dim;
    //new arr的元素用上去,之後query方便快速呼叫 
    Tree* thisOld = old;
    thisOld+=root;
    thisOld = node;
    
	if(tree->child ==NULL)//都不會動到tree位置 
	{
		
		tree->child = node;
		dim = tree->dim;
		node->dim = ++dim;//深度增加 
		node->parent = tree;
		tree = tree->child;//往下走 
	}
    
    else
    {
    	Tree* parent = tree;
		tree = tree->child;//當前已經是父節點,所以才用child到和node同層 
		dim = tree->dim; 
		while(tree->nxt!=NULL)
		{
		  tree = tree->nxt;
			
		}
		tree->nxt = malloc(sizeof(Tree));
		tree = tree->nxt;
		tree->parent = parent ;
		tree->dim =dim;
		  
		//tree = old;//回到父節點 
		
	}
	
	
}
 
