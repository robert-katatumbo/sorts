#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define CHECK char res = checker(a,size);if(!res) printf("sort good\n");else printf("sort bad\n");
#define TIME double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; printf("%f\n",cpu_time_used);

int checker(const unsigned char *a, const unsigned long size){
	for(unsigned long i =0; i < size-1; ++i){
		if(a[i] > a[i+1])
        return 1; // sort fail
	}
    return 0; // sort ok
}

void funny_char_sort(unsigned char* a, const unsigned long size, unsigned int*helper){
    // a[a b a c a a b]
    // h[4 2 1]
    // [a a a a b b c]
    // 4(a)    2(b) 1(c)
    unsigned long i,h;
    for(i = 0; i<size; ++i){
        helper[a[i]]++;
    }
    
    h = 0;
    for(i =0; i<size; ++i){
        while(helper[h]==0){
            ++h;
        }
        a[i] = h;
        --helper[h];
    }
}

int main(const int argc, const char**argv){
    unsigned long size = 5000;
    clock_t start, end;
    const int hsize = 256;
    //  input size from console 
    if(argc > 1)
        size = atoll(argv[1]);

    printf("%ld elms %ldmb\n",size,size/1024/1024);
    unsigned char * a = malloc(size);
    if(!a){
        perror("");
        return 1;    
    }
    
    /*to randomisation array
      job slow of size > 10`000`000      
    printf("randomisation ...");
    fflush(stdout);
    
    for(unsigned long i = 0; i < size; ++i){
	    srand(time(0) + i);
	    a[i] = rand();
    }
    printf(" done\n");
    */

    unsigned int helper[hsize];
    for(int i =0; i<hsize; ++i)
        helper[i] = 0;
    
    start = clock();
    funny_char_sort(a,size,helper);
    end = clock();
        
    TIME
    CHECK
    
    free(a);
    return 0;
}

