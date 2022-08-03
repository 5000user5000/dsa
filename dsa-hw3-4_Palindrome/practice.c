#include <stdio.h>
#include <stdlib.h>



int findEndSymFromMid(char *s, int end, int head);

int main()
{
    char *s = malloc(10000001 * sizeof(char));
    scanf("%s", s);
    // printf("%c",(char)s[1]);
    int slast = strlen(s) - 1; // s last index
    int lastInx, lastInx2;

    //先從固定前端檢驗
    for (int i = slast; i > 0; i--)
    {
        lastInx = findEndSymFromMid(s, i, 0);
        if (lastInx != -1)
            break;
    }

    //先從固定前端檢驗
    for (int i = 0; i < slast; i++)
    {
        lastInx2 = findEndSymFromMid(s, i, slast);
        if (lastInx2 != -1)
            break;
    }
    //輸出
    //都沒對稱,則有前後兩種對稱
    if (lastInx == -1 && lastInx2 == -1) 
    {
        printf("%d \n", slast); // s len-1
        for (int i = slast; i > 0; i--)
        {
            printf("%c", s[i]);
        }
        for (int j = 0; j <= slast; j++)
        {
            printf("%c", s[j]);
        }
        printf("\n");
        for (int j = 0; j <= slast; j++)
        {
            printf("%c", s[j]);
        }
        for (int i = slast - 1; i >= 0; i--)
        {
            printf("%c", s[i]);
        }
    }

    else if (lastInx2==-1||(slast - lastInx) < lastInx2) //如果前面增加較少字
    {
        printf("%d \n", slast - lastInx);
        for (int i = slast; i > lastInx; i--)
        {
            printf("%c", s[i]);
        }
        for (int j = 0; j <= slast; j++)
        {
            printf("%c", s[j]);
        }
    }
    else
    {
        printf("%d \n", lastInx2);
        for (int j = 0; j <= slast; j++)
        {
            printf("%c", s[j]);
        }
        for (int i = lastInx2 - 1; i >= 0; i--)
        {
            printf("%c", s[i]);
        }
    }

    // exit(0);
    return 0;
}

int findEndSymFromMid(char *s, int end, int head) // head指的是固定端,end是移動端,return 重複的端inx
{

    int lastInx = strlen(s) - 1; //字串最後的inx
    int mid, mid2 = 0;
    //如果是固定前端
    if (head == 0)
    {
        //先指定中點
        if ((end + 1) % 2 == 0) //偶數個
        {
            //如果子字串是偶數個,中點就會有2個
            mid = end / 2;
            mid2 = mid + 1; //+1是因為inx是從0開始

            while (mid >= 0 && mid2 <= lastInx)
            {
                if (s[mid] == s[mid2])
                {
                    mid--;
                    mid2++;
                }
                else
                    return -1;
            }
            return mid2 - 1;
        }
        else //奇數個
        {
            mid = end / 2;
            int r = 0;
            while (mid - r >= 0 && mid + r <= lastInx) //不超過左右兩界
            {
                if (s[mid - r] == s[mid + r])
                    r++;

                else
                    return -1;
            }
            return mid + r - 1; //因為最後會多加一次,需剪掉
        }
    }
    //如果是固定尾端
    else
    {
        if ((head - end + 1) % 2 == 0) // even
        {
            mid = (head + end) / 2;
            mid2 = mid + 1;

            while (mid >= 0 && mid2 <= lastInx)
            {
                if (s[mid] == s[mid2])
                {
                    mid--;
                    mid2++;
                }
                else
                    return -1;
            }
            return mid + 1; //因為是固定尾端,所以回傳前面的中點
        }
        else // odd
        {
            mid = (head + end) / 2;
            int r = 0;
            while (mid - r >= 0 && mid + r <= lastInx) //不超過左右兩界
            {
                if (s[mid - r] == s[mid + r])
                    r++;

                else
                    return -1;
            }
            return mid - r + 1; //因為最後會多加一次,需剪掉
        }
    }
}
