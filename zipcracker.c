#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <math.h>

#define MAX_THREAD_NUM 50
struct arg_struct {
    int min_i;
    int max_i;
    int min_j;
    int max_j;
    int min_k;
    int max_k;
};
int count;
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
    return 0;
}
void doThree()
{
    int block_size = pow(62, 3) / MAX_THREAD_NUM;
    printf("Block Size: %d\n", block_size);
    pthread_t thread[MAX_THREAD_NUM];
    struct arg_struct args[MAX_THREAD_NUM];
    args[0].min_i = 0;
    args[0].max_i = 1;
    args[0].min_j = 0;
    args[0].max_j = 14;
    args[0].min_k = 0;
    args[0].max_k = 26;
    int id;
    int* ids_t = (int *) malloc(MAX_THREAD_NUM * sizeof(int));
    int i;
    for (i = 0; i < MAX_THREAD_NUM; i++)
        ids_t[i] = i;
    pthread_create(&thread[0],NULL, crack3, (void *)&args[0]);
    pthread_join(thread[0], NULL);


}
void * crack3(void *arguments)
{

    char alphanum[63] = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789";
    struct arg_struct *args = arguments;
    printf("Max K: %d", args->max_k);
    int max = 3;
    int i, j, k, l, m, n, o, p, q, r;
    char string1[max + 1];
    start = time(NULL);
    count = 0;
    //strlen(alphanum)
    for (i = args->min_i; i <= args->max_i; i++) {
        string1[0] = alphanum[i];
        for (j = args->min_j; j <= args->max_j; j++) {
            string1[1] = alphanum[j];
            for (k = args->min_k; k <= args->max_k; k++) {
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
                    if (diff == 0)
                        diff = 1;
                    printf("PPS: %d\n", count / diff);
                    break;
                }
            }
            if (ret == 0)
                break;
        }
        //printf("String1: %s\n", string1);
        if (ret == 0)
            break;
    }
    printf("End Count: %d\n", count);
    printf("String1: %s\n", string1);
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
