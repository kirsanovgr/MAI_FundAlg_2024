#include "main.h"

int main() {
    int res, res0, res1, res2;
    char temp[100];

//    unroman("MMMCMXCIX", &res);

//    zecken(&res, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1);
//    printf("%d", res);

    FILE* a = fopen("a", "r");
//

//    scanf("  %d%d w%d", &res0, &res, &res1, temp);
//    overfscanf(a, "asd%Cv %Zr\n%s %Ro", &res0, 2, &res, temp, &res1);
//    oversscanf("   asdXIXasdfa", "asd%Ro", &res0, 2, &res, temp, &res1);
//    int mnn;
//    scanf("%*d", &mnn);
    int err = oversscanf("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz", "%CV", &res0, 36);
    if (err)
        return err;
//    fscanf(stdin, "   %d   %d %s", &res, &res1, temp);
//    unzeckendorf(&res, a);
//    printf("%d\n", fgetc(a));
    printf("%d %d %s %d %d", res, res0, temp, res2, res1);
//    printf("%d", mnn);

    return 0;
}