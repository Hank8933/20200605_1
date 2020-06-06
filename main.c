#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 101
//#define DEBUG
//  x + 1  x^2 + 3
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
        while (' ' != (numc[i] = getchar()) && numc[i++] != '\n'){\
        }\
        t[j++].item = atoi(numc);\
        if (numc[i - 1] == '\n') break;\
    }

    get(degree)
    get(coef)

    for (int i = t[0].degree, k = 0, h = 0; i >= 0; i--, k++){
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
        memset(polyA, 0, MAX * s);
        memset(polyB, 0, MAX * s);
        memset(polyAnsA, 0, MAX * s);

        getPoly(polyA);
        getPoly(polyB);

        #ifdef DEBUG
            printf("\n\n=========INPUT_DEBUG=========\n");
            for (int j = 0; j < 20; j++){
                printf("%3d ", polyA[j].degree);
            }
            printf("\n");
            for (int j = 0; j < 20; j++){
                printf("%3d ", polyA[j].coef);
            }
            printf("\n");
            for (int j = 0; j < 20; j++){
                printf("%3d ", polyB[j].degree);
            }
            printf("\n");
            for (int j = 0; j < 20; j++){
                printf("%3d ", polyB[j].coef);
            }
            printf("\n=========INPUT_DEBUG=========\n\n");
        #endif // DEBUG

        int diff = polyA[0].degree - polyB[0].degree;
        for (int j = 0; j <= diff; j++){
            polyAnsA[j].degree = diff - j;
            polyAnsA[j].coef = polyA[j].coef / polyB[0].coef;

            for (int k = 0; polyB[k].degree || polyB[k].coef; k++){
                polyA[k + j].coef -= polyB[k].coef * polyAnsA[j].coef;
            }

            #ifdef DEBUG
                printf("\n\n=========DEBUG=========\n");
                for (int p = 0; p < 20; p++){
                    printf("%3d ", polyA[p].coef);
                }
                printf("\n=========DEBUG=========\n\n");
            #endif // DEBUG
        }

        #ifdef DEBUG
            printf("\n\n=========OUTPUT_DEBUG=========\n");
            for (int j = 0; j < 20; j++){
                printf("%3d ", polyAnsA[j].degree);
            }
            printf("\n");
            for (int j = 0; j < 20; j++){
                printf("%3d ", polyAnsA[j].coef);
            }
            printf("\n\n");
            for (int j = 0; j < 20; j++){
                printf("%3d ", polyA[j].degree);
            }
            printf("\n");
            for (int j = 0; j < 20; j++){
                printf("%3d ", polyA[j].coef);
            }
            printf("\n=========OUTPUT_DEBUG=========\n\n");
        #endif // DEBUG

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
