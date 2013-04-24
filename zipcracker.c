#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <math.h>

#define MAX_THREAD_NUM 80


struct arg_struct {
    int min_i;
    int max_i;
    int min_j;
    int max_j;
    int min_k;
    int max_k;
    int min_l;
    int max_l;

};

int count;
time_t start, stop;
int diff;
int ret;

void * crack3();
void * crack4();
void doThree();
void doFour();
int unzip(char * pass);

int main(int argc, char * argv[])
{

    int min_char = 1;
    int max_char = 4;
    char * start_pat = "a";
    char * end_pat = "zzz";
    if (argc == 5)
    {
        min_char = atoi(argv[1]);
        max_char = atoi(argv[2]);
        start_pat = argv[3];
        end_pat = argv[4];
    }
    doFour();
    return 0;
}   

void doFour()
{
    int block_size = pow(62, 4) / MAX_THREAD_NUM;
    printf("Block Size: %d\n", block_size);
    pthread_t thread[MAX_THREAD_NUM];
    struct arg_struct args[MAX_THREAD_NUM];
    int i; 
    for (i = 0; i < MAX_THREAD_NUM; i++)
    {
        int a1 = (i * block_size) / pow(62, 3);
        int b1 = (i * block_size) % (int)pow(62, 3) / pow(62, 2);
        int c1 = ((i * block_size) % (int)pow(62, 3) % (int)pow(62, 2)) / 62;
        int d1 = ((i * block_size) % (int)pow(62, 3) % (int)pow(62, 2)) % 62;
        int a2 = ((i + 1) * block_size) / pow(62, 3);
        int b2 = ((i + 1) * block_size) % (int)pow(62, 3) / pow(62, 2);
        int c2 = ((((i + 1) * block_size) % (int)pow(62, 3)) % (int)pow(62, 2)) / 62;
        int d2 = ((((i + 1) * block_size) % (int)pow(62, 3)) % (int)pow(62, 2)) % 62;

               if (i == MAX_THREAD_NUM - 1)
        {
            /*printf("MOD: %d\n", a2 % (int)pow(62, 2)); 
              printf("a2: %d\n", a2);
              printf("b2: %d\n", b2);
              printf("c2: %d\n", c2);
              */
            a2 = 62;
            b2 = 62;
            c2 = 62;
            d2 = 62;
        }
         printf("Thread: %d", i);
        printf("a1: %d\n", a1);
        printf("b1: %d\n", b1);
        printf("c1: %d\n", c1);
        printf("d1: %d\n", d1);

        printf("a2: %d\n", a2);
        printf("b2: %d\n", b2);
        printf("c2: %d\n", c2);
        printf("d2: %d\n", d2);



        args[i].min_i = a1;
        args[i].max_i = a2;
        args[i].min_j = b1;
        args[i].max_j = b2;
        args[i].min_k = c1;
        args[i].max_k = c2;
        args[i].min_l = d1;
        args[i].max_l = d2;
    }
    int id;
    int* ids_t = (int *) malloc(MAX_THREAD_NUM * sizeof(int));

    start = time(NULL);
    for (i = 0; i < MAX_THREAD_NUM; i++)
        ids_t[i] = i;
    for (i = 0; i < MAX_THREAD_NUM; i++)
        pthread_create(&thread[i],NULL, crack4, (void *)&args[i]);
    for (i = 0; i < MAX_THREAD_NUM; i++)
        pthread_join(thread[i], NULL);

    stop = time(NULL);
    diff = difftime(stop, start);
    printf("Time: %d\n", diff);
    printf("Passwords: %d\n", (int)pow(62,4));
    printf("PPS: %d\n", ((int)pow(62, 4)) / diff);

}
void doThree()
{
    int block_size = pow(62, 3) / MAX_THREAD_NUM;
    printf("Block Size: %d\n", block_size);
    pthread_t thread[MAX_THREAD_NUM];
    struct arg_struct args[MAX_THREAD_NUM];
    int i; 
    for (i = 0; i < MAX_THREAD_NUM; i++)
    {
        int a1 = (i * block_size) / pow(62, 2);
        int b1 = (((i * block_size) % (int)pow(62, 2)) / 62); 
        int c1 = (((i * block_size) % (int)pow(62, 2)) % 62);
        int a2 = ((i +1) * block_size) / pow(62, 2);
        int b2 = (((i +1) * block_size) % (int)pow(62, 2)) / 62; 
        int c2 = (((i +1) * block_size) % (int)pow(62, 2)) % 62; 
        if (i == MAX_THREAD_NUM - 1)
        {
            /*printf("MOD: %d\n", a2 % (int)pow(62, 2)); 
              printf("a2: %d\n", a2);
              printf("b2: %d\n", b2);
              printf("c2: %d\n", c2);
              */
            a2 = 62;
            b2 = 62;
            c2 = 62;
        }

        args[i].min_i = a1;
        args[i].max_i = a2;
        args[i].min_j = b1;
        args[i].max_j = b2;
        args[i].min_k = c1;
        args[i].max_k = c2;
    }
    int id;
    int* ids_t = (int *) malloc(MAX_THREAD_NUM * sizeof(int));

    start = time(NULL);
    for (i = 0; i < MAX_THREAD_NUM; i++)
        ids_t[i] = i;
    for (i = 0; i < MAX_THREAD_NUM; i++)
        pthread_create(&thread[i],NULL, crack3, (void *)&args[i]);
    for (i = 0; i < MAX_THREAD_NUM; i++)
        pthread_join(thread[i], NULL);

    stop = time(NULL);
    diff = difftime(stop, start);
    printf("Time: %d\n", diff);
    printf("Passwords: %d\n", (int)pow(62,3));
    printf("PPS: %d\n", ((int)pow(62, 3)) / diff);

}
void * crack3(void *arguments)
{

    char alphanum[63] = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789";
    struct arg_struct *args = arguments;
    int max = 3;
    int i, j, k, l, m, n, o, p, q, r;
    char string1[max + 1];
    count = 0;
    for (i = args->min_i; i <= args->max_i; i++) {
        string1[0] = alphanum[i];
        for (j = args->min_j; j <= args->max_j; j++) {
            string1[1] = alphanum[j];
            for (k = args->min_k; k <= args->max_k; k++) {
                string1[2] = alphanum[k];
                system("rm -rf ggg > /dev/null 2>&1");
                ret = unzip(string1);
                count++;
                if (ret == 0)
                {
                    printf("PASS: %s\n", string1);
                    if (diff == 0)
                        diff = 1;
                    break;
                }
            }
            if (ret == 0)
                break;
        }
        if (ret == 0)
            break;
    }
    //printf("End Count: %d\n", count);
    //  printf("String1: %s\n", string1);
    return NULL;
}
void * crack4(void *arguments)
{
    char alphanum[63] = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789";
    struct arg_struct *args = arguments;
    int max = 4;
    int i, j, k, l, m, n, o, p, q, r;
    char string1[max + 1];
    count = 0;
    for (i = args->min_i; i <= args->max_i; i++) {
        string1[0] = alphanum[i];
        for (j = args->min_j; j <= args->max_j; j++) {
            string1[1] = alphanum[j];
            for (k = args->min_k; k <= args->max_k; k++) {
                string1[2] = alphanum[k];
                for(l = args->min_l; l <= args->max_l; l++){
                    string1[3] = alphanum[l];
                    system("rm -rf ggg > /dev/null 2>&1");
                    ret = unzip(string1);
                    count++;
                    if (ret == 0)
                    {
                        printf("PASS: %s\n", string1);
                        break;
                    }
                }
                if (ret == 0)
                    break;
            }
            if (ret == 0)
                break;
        }
        if (ret == 0)
            break;
    }
    //printf("End Count: %d\n", count);
    //printf("String1: %s\n", string1);
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
