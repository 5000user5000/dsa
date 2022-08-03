#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    /* data */
    unsigned long long int val;
    unsigned long long int origin;
    int key;
    int key2; // findSame用
    int same; // 1表示有相同,-1表示沒
    char *s;
} node;
// d q指定
unsigned long long int q = ULLONG_MAX / 95;
unsigned long long int d = 95;

unsigned long long int hash(char *s, int l)
{
    unsigned long long int hashed = 0, ddd = 1; // long long int 避免overflow
    for (int k = 0; k < l; k++)                 //還是後面的位數大,要配合changeFind的方式hash
    {
        // hashed = ((long long int)s[k] - 32 + (hashed * d)%q) % q; //不確定mod是否要自己刻的函數較好,減32是0x21是33,0x7E是126,為減少位數所用
        hashed = (hashed + (((int)s[k] - 32) * ddd) % q) % q;
        ddd = (ddd * d) % q;
    }

    return hashed; //注意要printf的話要%lld
}

int compare(const void *arg1, const void *arg2) // qsort(magic,k,sizeof(long long int),compare);
{
    //%q會把負值變正,不可用,這裡的差值也沒必要用 
    long long int ret = ((*(node *)(arg1)).val - (*(node *)(arg2)).val) ; //這樣排序只按照數值部分(把magic arrry順序改變),能夠還原key.
    if (ret > 0)
        return 1;
    if (ret < 0)
        return -1;
    return 0;
}

node *FindSame(node *magic, int k) //尋找同一值的,但只能找一組.找多組的另外做(flag=1),用node來存i j值
{
    unsigned long long int value = magic[0].val; //不用->真的好嗎,還是用(*magic[0]).val
    int inx1 = 0, inx2 = 0;
    for (int i = 1; i < k; i++)
    {
        if (value == magic[i].val)
        {
            inx2 = i;
            break;
        }
        else
        {
            inx1 = i;
            value = magic[i].val;
        }
    }
    node *ans = malloc(sizeof(node));
    ans = calloc(1, sizeof(node));
    if (inx2 == 0)
        ans->same = -1;
    else
    {
        ans->same = 1;              //表示有同值
        ans->key = magic[inx1].key; //原本的key
        ans->key2 = magic[inx2].key;
    }
    return ans;
}

unsigned long long int longPow(int ex) // math.pow是double
{
    unsigned long long int ans = 1;
    for (int i = 0; i < ex; i++)
    {
        ans = (ans * d) % q; //這裡也得避免overflow
    }

    return ans;
}

void changeFind(node *magic, int k, int l) //每次輪流讓一個位數char相同,來找相似的
{

    unsigned long long int ddd = 1;
    //int change;
    char *str = magic[0].s; //因為之後qsort會把順序打亂

    for (int i = 0; i < l; i++)
    {
        // change = (int)(str[i]) - 32;不一定要放,只要扣除不同去也可
        // ddd = longPow( i); //拿出來,別放loop內,會算好幾次,其實沒必要用long pow

        for (int j = 0; j < k; j++)
        {

            magic[j].val = magic[j].origin - (((int)(magic[j].s[i]) - 32) * (ddd)) % q; //把改變項補上,-change是因為前面-會抵消,負負得正
        }
        qsort(magic, k, sizeof(node), compare);
        node *ans = FindSame(magic, k);
        //如果有解
        if (ans->same == 1)
        {
            printf("Yes\n");
            printf("%d %d", ans->key, ans->key2);
            exit(0);
        }

        ddd = (ddd * d) % q;
        /*//沒解就復原
        for (int j = 0; j < k; j++)
        {
            magic[j].val = magic[j].origin;
        }*/
    }
    printf("No");
    exit(0); //都沒有
}

int main()
{
    int k, l, flag;  // k rows, l length
    scanf("%d", &k); //快速輸入之後再說
    scanf("%d", &l);
    scanf("%d", &flag);

    node *magic = malloc(k * sizeof(node));
    magic = calloc(k, sizeof(node));
    int leng = l + 1; //宣告長度多一格,'\0'

    for (int i = 0; i < k; i++)
    {
        magic[i].s = malloc(leng * sizeof(char));
        magic[i].s = calloc(leng, sizeof(char));
        scanf("%s", magic[i].s); // printf("%s \n",magic[i].s); //printf("%c \n",magic[i].s[3]);確認過不會RE
        magic[i].val = hash(magic[i].s, l);
        magic[i].origin = magic[i].val; //之後changeFind直接回復不用耗時太多
        magic[i].key = i;               // index
    }
    qsort(magic, k, sizeof(node), compare);
    node *ans = FindSame(magic, k);
    if (ans->same == 1)
    {
        printf("Yes\n");
        printf("%d %d", ans->key, ans->key2);
        exit(0);
    }
    else
    {
        changeFind(magic, k, l);
    }

    exit(0);
    return 0;
}
