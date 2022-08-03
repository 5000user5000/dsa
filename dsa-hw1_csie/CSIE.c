#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 2000 //�������Ӥj,�ҥH����i��n�ۤv�ק�2000001 

struct          //�]�w�B��l�u����
{				//�B��l
	char ch;    //�u����
	int pri;
}leftPri[] = { {'w',-1},{'=', 0}, {'(', 1}, {'*', 5}, {'/', 5}, {'+', 3}, {'-', 3}, {')', 6} },//w��ܰ_�l 
rightPri[] = { {'=', 0}, {'(', 6}, {'*', 4}, {'/', 4}, {'+', 2}, {'-', 2}, {')', 1} };

int LeftPri(char op);      //���B��lop���u����
int RightPri(char op);     //�k�B��lop���u����
bool InOp(char ch);        //�P�_ch�O�_���B��l
int CompareCode(char op1, char op2);  //���op1�Pop2���u����
void Transform(char* exp, char postExp[]); //�Nexp�]�Τ��J���B�⦡�^���ܦ����|�������A
void Compute(char* postExp);           //�i��Z��B�⦡�B��A�^�ǵ��G


int main()
{
	char exp[1000001];//�O���O����ΤӤj,10�U����,�|����exit 
	//printf("�p�⾹�G\n\n");
	//printf("�п�J�ƾǭp�⤽���G");
	scanf("%s", exp);
	char postExp[MaxSize];
	Transform(exp, postExp);//���ন��󦡸��n�B�z 
	Compute(postExp);
	
	//printf("���סG%g\n\n", Compute(postExp));

	return 0;
}


int LeftPri(char op)      //���B��lop���u����
{
	for(int i = 0; i < 8; i++)
	if (leftPri[i].ch == op)
		return leftPri[i].pri;

}

int RightPri(char op)     //�k�B��lop���u����
{
	int i;
	for (int i = 0; i < 7; i++)
		if (rightPri[i].ch == op)
			return rightPri[i].pri;
}

bool InOp(char ch)        //�P�_ch�O�_���B��l
{
	if (ch == '(' || ch == ')' || ch == '+' || ch == '-' || ch == '*' || ch == '/'|| ch == '=')
		return true;
	else
		return false;
}

int CompareCode(char op1, char op2)
{
	if(op1 == '=')//�h�ɤW�h��,���I�h�ӵ���
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
			postExp[i++] = '#';//�Ʀr�M�Ʀr�j�} 
		}
		else
		{
			switch (CompareCode(op.data[op.top], *exp)) //top = 0�Yop.data[op.top] = '='
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
	while (op.data[op.top] != 'w') //���0���Z�N�h�X�A
	{

		postExp[i++] = op.data[op.top];
		op.top--;  //top���ȶV�j�A�u���ŴN�V���I
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
					printf("\n\t�榡���~");
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
					postExp++;               //���postExp++��n���L�F��#���Ÿ�
				}
				ser.top++;
				ser.data[ser.top] = d;
				
		}
		postExp++;
	}
	
}

