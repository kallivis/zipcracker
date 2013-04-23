#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int unzip(char * pass);
int main(int argc, char * argv[])
{
    int min_char = 1;
    int max_char = 3;
    int ret;
    char * start_pat = "a";
    int i, j, k, l, m, n, o, p, q, r;
    char * end_pat = "zzz";
    char alphanum[63] = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789";

    if (argc == 5)
    {
        min_char = atoi(argv[1]);
        max_char = atoi(argv[2]);
        start_pat = argv[3];
        end_pat = argv[4];
    }
    char string1[max_char + 1];
    for (i = 0; i < strlen(alphanum); i++) {
        string1[0] = alphanum[i];
        for (j = 0; j < strlen(alphanum); j++) {
            string1[1] = alphanum[j];
            for (k = 0; k < strlen(alphanum); k++) {
                string1[2] = alphanum[k];
                system("rm -rf ggg");
                ret = unzip(string1);
                if (ret == 0)
                {

                    printf("PASS: %s", string1);
                    break;
                }
            }
            if (ret == 0)
                break;

        }

        if (ret == 0)
            break;
    }
    unzip(start_pat);
    //  char  test = 'a';
    //  printf("test1: %s\n", test);
    //  test++;
    //  printf("test2: %s\n", test);
    //   printf("Ret: %d\n", ret);
    //  printf("Cmd: %s\n", cmd);
    return 0;
}
int unzip(char * pass)
{
    char cmd[80];
    strcpy(cmd, "unzip -qu -P ");
    strcat(cmd, pass);
    strcat(cmd, " TestZip -d ./ggg");
    int ret = system(cmd);

    return ret;
}
