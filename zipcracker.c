#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define MAX_THREAD_NUM 50
int count = 0;
time_t start, stop;
int diff;
int ret;

void * crack3();
void doThree();
int unzip(char * pass);
int main(int argc, char * argv[])
{
    
    int min_char = 1;
    int max_char = 3;
    char * start_pat = "a";
    char * end_pat = "zzz";
    if (argc == 5)
    {
        min_char = atoi(argv[1]);
        max_char = atoi(argv[2]);
        start_pat = argv[3];
        end_pat = argv[4];
    }
    doThree();
        //  char  test = 'a';
    //  printf("test1: %s\n", test);
    //  test++;
    //  printf("test2: %s\n", test);
    //   printf("Ret: %d\n", ret);
    //  printf("Cmd: %s\n", cmd);
    return 0;
}
void doThree()
{

    pthread_t thread[MAX_THREAD_NUM];
    pthread_t thread1;
    int id;
    int* ids_t = (int *) malloc(MAX_THREAD_NUM * sizeof(int));
    int i;
    for (i = 0; i < MAX_THREAD_NUM; i++)
        ids_t[i] = i;
    pthread_create(&thread1,NULL, crack3, (void *)&ids_t[0]);
    pthread_join(thread1, NULL);


}
void * crack3()
{
char alphanum[63] = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789";

int max = 3;
    int i, j, k, l, m, n, o, p, q, r;
    char string1[max + 1];
    start = time(NULL);
    for (i = 0; i < strlen(alphanum); i++) {
        string1[0] = alphanum[i];
        for (j = 0; j < strlen(alphanum); j++) {
            string1[1] = alphanum[j];
            for (k = 0; k < strlen(alphanum); k++) {
                string1[2] = alphanum[k];
                system("rm -rf ggg");
                ret = unzip(string1);
                count++;
                if (ret == 0)
                {
                    stop = time(NULL);
                    diff = difftime(stop, start);
                    printf("PASS: %s\n", string1);
                    printf("Time: %d\n", diff);
                    printf("count: %d\n", count);
                    printf("PPS: %d\n", count / diff);
                    break;
                }
            }
            if (ret == 0)
                break;
        }
        printf("String1: %s\n", string1);
        if (ret == 0)
            break;
    }
    return NULL;
}
int unzip(char * pass)
{
    char cmd[80];
    strcpy(cmd, "unzip -qu -P ");
    strcat(cmd, pass);
    strcat(cmd, " TestZip -d ./ggg > /dev/null 2>&1");
    int ret = system(cmd);
    return ret;
}
