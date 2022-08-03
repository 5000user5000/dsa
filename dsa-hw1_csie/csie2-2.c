#include <stdio.h>
#include <math.h>
#define MaxSize 2000001

int priority(char op);
void transform(char postExp[],char* Exp);
int compare(char *Exp,char op,int first);
void compute(char* postExp);//這裡也採用指向記憶體 


int main()
{
    char *Exp;//malloc前要加pointer 
    Exp =malloc(MaxSize*sizeof(char));//抓記憶體出來 
    Exp = calloc(MaxSize,sizeof(char));//初始化 
    char *postExp;
    postExp =malloc(MaxSize*sizeof(char));
    postExp = calloc(MaxSize,sizeof(char));
    
	scanf("%s",Exp);
    transform(postExp,Exp);
    
    free(Exp);//記得釋放記憶體 
    compute(postExp);
    free(postExp);
    
    
    exit(0);//這樣比return快 
    
	return 0;
}

int priority(char op)
{
    switch(op)//根據之後的要求定義優先度,通常最優先數字會越大,只是括號和等號有點特別 
    {
      case '(':
        return -2;
        break;
     case ')':
        return -1;
        break;
     case 'w':
        return 0;
        break;
     /////
     case '+':
        return 1;
        break;
     case '-':
        return 1;
        break;
     /////
     case '*':
        return 2;
        break;
     case '/':
        return 2;
        break;
     case '%':
        return 2;
        break;
        
     case '=':
        return 3;
        break;
     case 'A':
        return 11;
        break;
     default:
        break;
    
    }
    
    
}

int compare(char* Exp,char op,int first)//把前後的運算服比較,產生各種結果,每個結果都專案處理 
{
    int priExp,priOp;
    priExp =priority(*Exp);
    priOp = priority(op);
    
    //先處理特殊case
    if(priExp ==-2)return 4;
    if(priExp ==-1)return 5;
    if(priExp == 3)return 6;
    if(*Exp=='-'&&(op=='w'||op=='('))//處理負數問題,如-3/2, (-2+4),先把A push到op stack 
	{                                  //偏暴力法解決->三重if ,就像補破洞,一個個補 
	  if(first==1)return 7;//只有這使用top,應付-((3/5)+3) 
	  Exp--; 
	  
	  if(!(*Exp >= '0' && *Exp <= '9'))//如果負號前面不是數字而後面是數字,就表示這是負數,應付 ((5+(7*6))-((3/(2-5))*4))=
	  {
	  	Exp+=2;
	  	if(*Exp >= '0' && *Exp <= '9'){
		  Exp--;//還原 
		  return 7;
		  }
		Exp-=2;//else 復原 
	   }
	   Exp++;//還原 
	  
	  //return 7;
	} 
    if(priOp==11)return 8; //之後直接push進去postExp 
    //之後是一般case
    if(priExp > priOp)return 1;
    else if(priExp == priOp)return 2;
    else return 3; //小於的情況
}

void transform(char postExp[],char* Exp)//注意Exp用pointer指向記憶體,要考量到負數情況 
{
   
	int top,first=1;//first是用來應付-((3/5)+3),因為-號時不能Exp-- 
	char* op;//儲存operator 
	op = malloc(MaxSize*sizeof(char));
	
	
    top = 0;//原是用-1再++
    op[top] = 'w';   //top = 0,終止符或是起始符
    int i=0;//postExp的index   
    int order;//用於比較前後運算子優先度後,判斷是第幾種case,來做出相對應的處理
	 
    while(*Exp != NULL)
    {
        if(*Exp >= '0' && *Exp <= '9')//如果是數字
        {
            while (*Exp >= '0' && *Exp <= '9')
			{
				postExp[i++] = *Exp;
				Exp++;
				first=-1;//表示已經不是第一次        
			}
			postExp[i++] = '#';//數字和數字隔開
        }
        
        else //根據每種case做處理,可能比參考的code冗長,但較為直觀 
        {
            order = compare(Exp,op[top],first);
            
            
            if(order ==1 || order ==4)//如果遇到優先度更高的op或是(,先放入op stack 
            {
                top++;
                op[top] = *Exp;//push
                Exp++;//移動下一個記憶體(char)
                first=-1;//表示已經不是第一次 
            }
            else if(order ==3)//特別挑出來應付7-9/3+44= 
            {
			    postExp[i++] = op[top];//push
			    while(priority(op[--top])==1)
			    {
			    	postExp[i++] = op[top];
				}
				top++;
                op[top] = *Exp; //相當於先pop出去,再push新的
                
                Exp++; 
                first=-1;//表示已經不是第一次 
			} 
            else if(order ==2  || order ==8)//如果遇到優先度一樣或是較低的op,就可以pop出去,並把new op push進來 //元order3處 
            {
                postExp[i++] = op[top];//push
                op[top] = *Exp; //相當於先pop出去,再push新的
                Exp++;
                first=-1;//表示已經不是第一次 
            }
            else if(order ==5)//當遇到')',就把op stack直到遇到(的op全pop出去 
            {
                while(op[top]!= '(')
                {
                    postExp[i++] = op[top];//push
                    top--;
                }
                top--;//相當把 ( 給pop掉
                Exp++;
                first=-1;//表示已經不是第一次 
            }
            else if(order == 6)//遇到 =,就把op stack所有的op pop出去,w是中止符,表示開頭 
            {
                while(op[top]!= 'w')
                {
                    postExp[i++] = op[top];//push
                    top--;
                }
                postExp[i++]= *Exp;//把 = push進去
                Exp++;
                first=-1;//表示已經不是第一次 
            }
            else if(order==7)
            {
            	top++;
                op[top] = 'A';//表示負數,而不是一般減法 
                Exp++;
                first=-1;//表示已經不是第一次 
			}
            
            
        }
        
    }
    while(op[top]!= 'w')//到中止符前
    {
        postExp[i++]=op[top--];
       
    }
    free(op);//釋放記憶體 
    postExp[i] = '\0';//post的中止符
    
}
void compute(char * postExp)//這裡大致上不需修改,計算的函數怎麼想都和這樣沒差太多 
{
   
	printf("%s\n",postExp);
	int top;
	long long int* data;
	data = malloc(MaxSize*sizeof(long long int));

	long long int a, b, c, d;
	top = -1;
	while (*postExp != NULL)//因為calloc初始化是變成null(要用大寫) 
	{
		switch (*postExp)//針對每一個運算符號去處理 
		{
			case '+':
				a = data[top];
				top--;
				b = data[top];
				top--;
				c = a + b;
				top++;
				data[top] = c;
				break;
			case '-':
				a = data[top];
				top--;
				if(top ==-1)b= 0;//為應付首位為負數情況 
				else b = data[top];
	
				
				top--;
				c = b - a;
				top++;
				data[top] = c;
				break;
			case '*':
				a = data[top];
				top--;
				b = data[top];
				top--;
				c = b * a;
				top++;
				data[top] = c;
				break;
			case '/':
				a = data[top];
				top--;
				b = data[top];
				top--;
					
				c = floor((double)b / a);//無條件捨去法 
				top++;
				data[top] = c;	
				break;
			case '%':
				a = data[top];
				top--;
				b = data[top];
				top--;
					
				c = b % a;
				top++;
				data[top] = c;	
				break;
			case '=':
			    printf("Print: %lld \n",data[top]);//得解 lld->long long int
			    break;
			case 'A'://處理負數,也就是把前一個數字變負 
				data[top] =data[top]*(-1) ;
			    break;    
			    
			default: //遇到數字 
				d = 0;
				
            	while (*postExp >= '0' && *postExp <= '9')//原本一格1個位數,現在要轉換回原本位數大小 
				{
					  d = 10 * d + *postExp - '0';
					  postExp++;               //兩個postExp++恰好跳過了‘#’符號
				}	  
				top++;
				data[top] = d;
					
				
				
		}
		postExp++;
	}
	free(data);
	
}
