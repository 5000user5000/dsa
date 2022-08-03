#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 2000 //不能夠到太大,所以之後可能要自己修改2000001 

struct          //設定運算子優先級
{				//運算子
	char ch;    //優先級
	int pri;
}leftPri[] = { {'w',-1},{'=', 0}, {'(', 1}, {'*', 5}, {'/', 5}, {'+', 3}, {'-', 3}, {')', 6} },//w表示起始 
rightPri[] = { {'=', 0}, {'(', 6}, {'*', 4}, {'/', 4}, {'+', 2}, {'-', 2}, {')', 1} };

int LeftPri(char op);      //左運算子op的優先級
int RightPri(char op);     //右運算子op的優先級
bool InOp(char ch);        //判斷ch是否為運算子
int CompareCode(char op1, char op2);  //比較op1與op2的優先級
void Transform(char* exp, char postExp[]); //將exp（用戶輸入的運算式）轉變成堆疊中元素，
void Compute(char* postExp);           //進行后綴運算式運算，回傳結果


int main()
{
	char exp[1000001];//是不是不能用太大,10萬那種,會直接exit 
	//printf("計算器：\n\n");
	//printf("請輸入數學計算公式：");
	scanf("%s", exp);
	char postExp[MaxSize];
	Transform(exp, postExp);//先轉成後綴式較好處理 
	Compute(postExp);
	
	//printf("答案：%g\n\n", Compute(postExp));

	return 0;
}


int LeftPri(char op)      //左運算子op的優先級
{
	for(int i = 0; i < 8; i++)
	if (leftPri[i].ch == op)
		return leftPri[i].pri;

}

int RightPri(char op)     //右運算子op的優先級
{
	int i;
	for (int i = 0; i < 7; i++)
		if (rightPri[i].ch == op)
			return rightPri[i].pri;
}

bool InOp(char ch)        //判斷ch是否為運算子
{
	if (ch == '(' || ch == ')' || ch == '+' || ch == '-' || ch == '*' || ch == '/'|| ch == '=')
		return true;
	else
		return false;
}

int CompareCode(char op1, char op2)
{
	if(op1 == '=')//多補上去的,應付多個等於
	   return 1;
	
	if (LeftPri(op1) == RightPri(op2))
		return 0;
	else if (LeftPri(op1) < RightPri(op2))
		return -1;
	else
		return 1;
}

void Transform(char* exp, char postExp[])
{
	struct
	{
		char data[MaxSize];
		int top;
	} op;
	int i = 0;
	//int flag = 0;
	op.top = -1;
	op.top++;
	op.data[op.top] = 'w';   //top = 0
	while (*exp != '\0')
	{
		if (!InOp(*exp))
		{
			while (*exp >= '0' && *exp <= '9')
			{
				postExp[i++] = *exp;
				exp++;        
			}
			postExp[i++] = '#';//數字和數字隔開 
		}
		else
		{
			switch (CompareCode(op.data[op.top], *exp)) //top = 0即op.data[op.top] = '='
			{
			case -1:
				op.top++;     //top = 1
				op.data[op.top] = *exp;
				exp++;
				break;
			case 0:
				op.top--; //top = 0
				exp++;
				break;
			case 1:
				postExp[i++] = op.data[op.top]; 
				op.top--;  
				break;
			}
		}
		
	}
	while (op.data[op.top] != 'w') //減到0之后就退出，
	{

		postExp[i++] = op.data[op.top];
		op.top--;  //top的值越大，優先級就越高！
	}
	postExp[i] = '\0';
}

void Compute(char * postExp)
{
	struct
	{
		long long int data[MaxSize];
		int top;
	} ser;

	long long int a, b, c, d;
	ser.top = -1;
	while (*postExp != '\0')
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
				
				/*if (a!= 0)
				{
					c = b / a;
					ser.top++;
					ser.data[ser.top] = c;
				}
				else
				{
					printf("\n\t格式錯誤");
					exit(0);
				}*/
				
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

