#include<stdio.h>
#include <string.h>
#include<stdlib.h> 
#include <stdbool.h> //使用bool,c++是直接內建 
//using namespace std;

//先把要用的自訂義函數宣告,main才能用 
int findNext(int board[25][25],int rowClue[25][14],int colClue[25][14],int row,int col);
bool Recur(int board[25][25],int rowClue[25][14],int colClue[25][14],int row,int col,int total);
bool valid(int board[25][25],int rowClue[25][14],int colClue[25][14],int row,int col);
bool isFull(int board[25][25],int row,int col,int total);
void printbod(int board[25][25],int row,int col);//打印確認
void cleandown(int board[25][25],int row,int col,int cell);

int main()
{
	int row,col,a=0,b=0,clue=0,total=0; 
	int rowClue[25][14]={0},colClue[25][14]={0};//最多有12個,不過這樣會很麻煩,多一個備用在findNext不會跳出範圍,預設值0,也可省
	int board[25][25]={0};//因為1 * 25也算 ,預設0 
	bool justCall;//只是為呼叫recur 
	
	scanf("%d",&row);
	scanf("%d",&col);

	//row clue
	for(int i=0;i<row;i++)
	{
	 scanf("%d",&clue);
	 for(int j=0;j<clue;j++)
	 {
	  
	  scanf("%d",&rowClue[i][j]);//每次clue時才不會洗掉之前的 
	  total+=rowClue[i][j];//計算黑格數,方便之後確認是否有塗滿黑格 
	 }
	 
	}
	
	//col clue
	for(int i=0;i<col;i++)
	{
	 scanf("%d",&clue);
	 for(int j=0;j<clue;j++)
	 {
	  
	  scanf("%d",&colClue[i][j]);//每次clue時才不會洗掉之前的 
	 }
	
	}
	
	justCall=Recur(board,rowClue,colClue,row,col,total);
	
	
	return 0;
}

bool Recur(int board[25][25],int rowClue[25][14],int colClue[25][14],int row,int col,int total)
{
   int cell;
   bool succeed;
   if(isFull(board,row,col,total))//確認塗滿沒 
   {
   	if(valid(board,rowClue,colClue,row,col))//有效的話 
   	{
	   //打印 
	   printf("ans:  \n");
	   for(int i=0;i<row;i++)
	   {
	   	for(int j=0;j<col;j++)
	   	{
	   		if(board[i][j]==1)printf("o");//用"",''會出錯 
	   		else printf("_");
		   }
		printf("\n");//跳行 
	   }
	   
	   
	   //return true;
	   exit(0);//直接中止程式就不用繼續跑其他循環了 
	} 
   	else 
	   return false;
	   
   } 
   
   else{
   	cell=findNext(board,rowClue,colClue,row,col);//找下一個 
   	if(cell==-1)return false;
   	board[cell/col][cell% col]=1;//上色 
   	
   	printbod(board,row,col);//確認現在board
   	
   	succeed = Recur(board,rowClue,colClue,row,col,total);//遞迴 
   	
   	if(succeed)return true;//似乎沒用處,因為如果成功就直接exit 沒必要return 
   	
	cleandown(board,row,col,cell);//清理
	board[cell/col][cell% col]= -1;//塗白,讓next不會到這 
	
	
	printbod(board,row,col);//確認現在board
	
	succeed = Recur(board,rowClue,colClue,row,col,total);
   	
	if(succeed)return true;
   	//memset(board, 0, sizeof board);//清空,使用string.h 
   	//cell=-2;  make cell empty似乎不用 
   	
	return false;
   }


} 

//第一row看到下一個row ,return next要塗的格子index 
int findNext(int board[25][25],int rowClue[25][14],int colClue[25][14],int row,int col)
{
	    int rowclueNum,breakout=0,k=0,clue;
		for(int i=0;i<row;i++)//三重迴圈 
		{
			clue=0;//歸零(忘) 
			k=0; 
			breakout =0;
			while(rowClue[i][clue]>0)
			{
				
				rowclueNum = rowClue[i][clue]; 
				for(int j=k;j<col;j++)
			    {
				  if(board[i][j]==0&&rowclueNum>0)return i*col+j;//格數0~24 
							
				  if(board[i][j]==1)
				  {
					rowclueNum--;
					breakout=j;//第j個結束
				                   }
				  if(rowclueNum>0&& j<24 && board[i][j]==1 &&board[i][j+1]==-1)return -1;//如果連續三個,避免出現1 1 -1 1 0 這類中斷,浪費時間 
				  //忘了考慮-1 -1 0 0 0 -> -1 -1 1 1 0 這樣的情況 ,增加  board[i][j]==1先確認是否開始連載             
			      if(rowclueNum==0)break;
	            
				}
				if(rowclueNum>0)return -1;//如果全跑過,但還是沒銷完,如有3個但 -1 -1 -1 1 1 
				
				k =breakout+2;
				clue++;
			}
					
		}
		return -1;//都沒有,可能是填滿(理論上填滿會被檢查full,所以不會有填滿的情況)或是無法填 
}

bool valid(int board[25][25],int rowClue[25][14],int colClue[25][14],int row,int col) 
{
    int breakout =0,k=0,colclueNum,clue=1;
	for(int i=0;i<col;i++)
	{
		clue=0;//重新歸0 (忘) 
		k=0;
		if(colClue[i][0]==0)//如果這裡沒有黑格
		{
			for(int j=0;j<row;j++)
			{
				if(board[j][i]==1)return false;//如果這有黑格就 
			}
		}
		
		 
		while(colClue[i][clue]>0)//塗格子是按照row規則,所以只要檢查col有無符合就好 
		{
		  
		  
		  colclueNum = colClue[i][clue]; 
		  for(int j=k;j<row;j++)
		  {
			
							
		    if(board[j][i]==1)//board[row][col]
		    {
				colclueNum--;
				breakout=j;//第j個結束
				if(j<24&& colclueNum>0 && board[j+1][i]!=1) return false;//如果是連續塗黑,而後面沒有黑就錯了,<24是怕out of range          
			    if(colclueNum==0)
				{
					if(j<24&& board[j+1][i]>0) return false;//如果連續黑格後間隔是黑not白就是錯誤 
					clue++;
					colclueNum = colClue[i][clue];
				}
			  
			  }
			
			if(colclueNum>0&&j==row-1)return false;//如果結束這行時,還未消掉,就是錯誤 
			
			if(colclueNum<=0) 
			{ 
			  if(j<24&&board[j+1][i]>0)return false;//如果下一格該空格卻有數字就算錯誤 ,and ensure no out of range
			  if(colclueNum<0) return false;//可能這行沒黑,但有黑就會<0 
			  //break;不應離開,因為如果這行理應要2,但是2 1就檢查不出 
	          }
	          
	        
		  }
		  //k =breakout+2;//加2,因空白處已檢查 ,跳下一格可能黑的部分 
		  
		  clue++;
			
		}
		
			
		
		
	}
	return true;
	
	
	
}

bool isFull(int board[25][25],int row,int col,int total)//藉由計算黑格總數確認是否有塗滿,只是每次都要跑一輪 ,耗資源 
{
	int sum=0;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
		   if(board[i][j]>0)sum++;	
		}
	}
	if(sum==total)return  true;
	else return false;
	
}

void printbod(int board[25][25],int row,int col)//打印確認
{
 for(int i=0;i<row;i++)
	   {
	   	for(int j=0;j<col;j++)
	   	{
	   		printf("%d ",board[i][j]);
	   		
		   }
		printf("\n");//跳行 
	   }
	   printf("---------- \n");
    
}
void cleandown(int board[25][25],int row,int col,int cell)
{
    
    int i = cell/col;//row
    int j = cell%col;//col
    for(i;i<row;i++)
    {
        for(j;j<col;j++)//j不應該用 j = cell%col,不然洗到下一行的時候,也是從 cell%col開始,無法從col 0開始 
        {
            board[i][j]=0;
        }
        j = 0;//使其 從0開始 
    } 
    
}

