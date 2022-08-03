#include <stdio.h>
#define MaxSize 100

int priority(char op);
void transform(char postExp[],char* Exp);
int compare(char Exp,char top);
void compute(char* postExp);//這裡也採用指向記憶體 

int main()
{
    char Exp[100]={};
    char postExp[100]={};
    scanf("%s",Exp);
    transform(postExp,Exp);
    //printf("%s",postExp);
    compute(postExp);

    return 0;
}

int priority(char op)
{
    switch(op)
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
     
     default:
        break;
    
    }
    
    
}

int compare(char Exp,char top)
{
    int priExp,priTop;
    priExp =priority(Exp);
    priTop = priority(top);
    
    //先處理特殊case
    if(priExp ==-2)return 4;
    if(priExp ==-1)return 5;
    if(priExp == 3)return 6;
    //之後是一般case
    if(priExp > priTop)return 1;
    else if(priExp == priTop)return 2;
    else return 3; //小於的情況
}

void transform(char postExp[],char* Exp)//注意Exp用pointer指向記憶體
{
    struct
	{
		char data[MaxSize];
		int top;
	} op;
    op.top = 0;//原是用-1再++
    op.data[op.top] = 'w';   //top = 0
    int i=0;//postExp的index
    int order;//用於比較來輸出指令
    while(*Exp != '\0')
    {
        if(*Exp >= '0' && *Exp <= '9')//如果是數字
        {
            while (*Exp >= '0' && *Exp <= '9')
			{
				postExp[i++] = *Exp;
				Exp++;        
			}
			postExp[i++] = '#';//數字和數字隔開
        }
        
        else
        {
            order = compare(*Exp,op.data[op.top]);
            if(order ==1 || order ==4)
            {
                op.top++;
                op.data[op.top] = *Exp;//push
                Exp++;//移動下一個記憶體(char)
            }
            else if(order ==2 || order ==3)
            {
                postExp[i++] = op.data[op.top];//push
                op.data[op.top] = *Exp; //相當於先pop出去,再push新的
                Exp++;
            }
            else if(order ==5)//當遇到')'
            {
                while(op.data[op.top]!= '(')
                {
                    postExp[i++] = op.data[op.top];//push
                    op.top--;
                }
                op.top--;//相當把 ( 給pop掉
                Exp++;
            }
            else if(order == 6)//遇到 =
            {
                while(op.data[op.top]!= 'w')
                {
                    postExp[i++] = op.data[op.top];//push
                    op.top--;
                }
                postExp[i++]= *Exp;//把 = push進去
                Exp++;
            }
            
            
        }
        
    }
    while(op.data[op.top]!= 'w')//到中止符前
    {
        postExp[i++]=op.data[op.top--];
       
    }
    postExp[i] = '\0';//post的中止符
    
}
void compute(char * postExp)
{
	struct
	{
		long long int data[MaxSize];
		int top;
	} ser;

	long long int a, b, c, d;
	ser.top = -1;
	while (*postExp != '\0')//因為calloc初始化是變成null(要用大寫) 
	{
		switch (*postExp)
		{
			case '+':
				a = ser.data[ser.top];
				ser.top--;
				b = ser.data[ser.top];
				ser.top--;
				c = a + b;
				ser.top++;
				ser.data[ser.top] = c;
				break;
			case '-':
				a = ser.data[ser.top];
				ser.top--;
				b = ser.data[ser.top];
				ser.top--;
				c = b - a;
				ser.top++;
				ser.data[ser.top] = c;
				break;
			case '*':
				a = ser.data[ser.top];
				ser.top--;
				b = ser.data[ser.top];
				ser.top--;
				c = b * a;
				ser.top++;
				ser.data[ser.top] = c;
				break;
			case '/':
				a = ser.data[ser.top];
				ser.top--;
				b = ser.data[ser.top];
				ser.top--;
				
				
				c = b / a;
				ser.top++;
				ser.data[ser.top] = c;	
				break;
			case '=':
			    printf("Print: %d \n",ser.data[ser.top]);
			    break;
			default:
				d = 0;
				while (*postExp >= '0' && *postExp <= '9')
				{
					d = 10 * d + *postExp - '0';
					postExp++;               //兩個postExp++恰好跳過了‘#’符號
				}
				ser.top++;
				ser.data[ser.top] = d;
				
		}
		postExp++;
	}
	
}
