#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reverse(char *s)
{
	int len = strlen(s)+1;//留給'\0' 
	char *s2 = malloc(len * sizeof(char));
	s2 = calloc(len,sizeof(char));//這裡也得calloc
	len--;//還原 
	for (int i = 0; i < len; i++)
	{

		s2[len - 1 - i] = s[i];
	}
	return s2;
}

char *concate(char *s, char c)
{
	int len = strlen(s);
	//int len2 = strlen(rev);
	int slen = 2*len+1;
	slen++;//留給'\0' 
	char *concat = malloc(slen * sizeof(char));
	concat = calloc(slen,sizeof(char));//真的需要使用,不然大於slen的部分會出現,還是亂碼
	for (int i = 0; i < len; i++)
	{
		concat[i] = s[i];
	}
	concat[len] = c;
	slen--;//還原 
	for (int j = 0; j < len; j++)
	{
		concat[slen - 1 - j] = s[j];
	}
	return concat;
}

void computeLPSArray(char *s, int lps[])
{
	int M = strlen(s);
	int len = 0;
	lps[0] = 0; // lps[0] is always 0

	int i = 1;
	while (i < M)
	{
		if (s[i] == s[len])
		{
			len++;
			lps[i] = len;
			i++;
		}
		else // (str[i] != str[len])
		{

			if (len != 0)
			{
				len = lps[len - 1];
			}
			else // if (len == 0)
			{
				lps[i] = 0;
				i++;
			}
		}
	}
	
}

int getMinToAdd(char *s)
{
	int len = strlen(s);
	//char *revStr = malloc(len * sizeof(char));
	//revStr = reverse(s);

	char c = 0x20;//原用'\t' 
	int slen = 2*len+1;
	slen++;//留給'\0' 
	char *concat = malloc(slen * sizeof(char));
	concat = calloc(slen,sizeof(char));
	concat = concate(s, c);
    //printf("concat = %s \n",concat);
	//int slen = strlen(concat);
	int lps[slen];
	computeLPSArray(concat, lps);
    
	//printf("slen = %d len = %d , lps last = %d \n",slen,len,lps[slen - 1]);
	//for(int i=0;i<slen;i++)printf("%d",lps[i]);
	//printf("\n");
    slen--;//還原 
	return (len - lps[slen - 1]);
}
void printpal(char *s, int add)
{
	int len = strlen(s);
	for (int i = len - 1; i >= len - add; i--)
	{
		//printf("%c", s[i]);
		//更快輸出 (unlock更快) 
		putchar(s[i]);
	}
	for (int j = 0; j < len; j++)
	{
		//printf("%c", s[j]);
		//更快輸出
		putchar(s[j]);
	}
}

int main()
{
	char *s = malloc(20000000 * sizeof(char));
	s = calloc(20000000,sizeof(char));
	//scanf("%s", s);
    //更快的輸入
	int ch,k=0;
	while ((ch = getchar()) != '\n' && ch != EOF) {
        s[k++] = (char)ch;
    }

	int add = getMinToAdd(s);
    
	int len = strlen(s)+1;//還要多留個放'\0'結束符號 
	char *s2 = malloc(len* sizeof(char));
	s2 = calloc(len,sizeof(char));
	s2 = reverse(s);
	int add2 = getMinToAdd(s2);
	//printf("%s",s2);
    //printf("add = %d, add2 = %d \n",add,add2);

	if (add < add2)
	{
		printf("%d\n", add);
		printpal(s, add);
	}
	else if (add2 < add)
	{
		printf("%d\n", add2);
		printpal(s2, add2);
	}
	else if(add == 0)//add == add2,但是 ==0
	{
       printf("%d\n", add);
	   printpal(s, add);
	}
	else
	{
		printf("%d\n", add);
		printpal(s, add);
		putchar('\n');
		printpal(s2, add2);
	}
	// printf("%d",getMinToAdd(s2));
	exit(0);//faster
	return 0;
}
