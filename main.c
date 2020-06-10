#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 101

typedef struct TERM {
    int degree;
    int coef;
} term;

void getPoly(term a[])
{
    char numc[10] = {0};
    term t[MAX] = {0};
    int j;

    #define get(item)\
    j = 0;\
    for (;;){\
        int i = 0;\
        while (' ' != (numc[i] = getchar()) && numc[i++] != '\n');\
        t[j++].item = atoi(numc);\
        if (numc[i - 1] == '\n') break;\
    }

    get(degree)
    get(coef)

    for (int i = t[0].degree, k = 0, h = 0; i >= 0; i--, k++){  //補缺項，i = 次方，k = 補0後的項編號，h = 補0前的項編號
        if (i == t[h].degree)
            a[k] = t[h++];
        else
            a[k].degree = i;
    }
}

int main()
{
    //freopen("list", "r", stdin);
    int n, s = sizeof(term);
    term polyA[MAX], polyB[MAX], polyAnsA[MAX];
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++){
        memset(polyA, 0, MAX * s);  //用0字元填滿poly陣列來洗白
        memset(polyB, 0, MAX * s);
        memset(polyAnsA, 0, MAX * s);

        getPoly(polyA);
        getPoly(polyB);

        int diff = polyA[0].degree - polyB[0].degree;  //次方差
        for (int j = 0; j <= diff; j++){
            polyAnsA[j].degree = diff - j;  //商
            polyAnsA[j].coef = polyA[j].coef / polyB[0].coef;  //商

            for (int k = 0; polyB[k].degree || polyB[k].coef; k++){
                polyA[k + j].coef -= polyB[k].coef * polyAnsA[j].coef;  //餘式
            }
        }

        int flag;
        #define show(tag, item)\
        flag = 1;\
        for (int j = 0; j < MAX; j++){\
            if (tag[j].coef){\
                flag = 0;\
                printf("%d ", tag[j].item);\
            }\
        }\
        if (flag)\
            putchar('0');\
        putchar('\n');

        show(polyAnsA, degree)
        show(polyAnsA, coef)

        show(polyA, degree)
        show(polyA, coef)
    }
    return 0;
}
