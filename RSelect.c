//RSelect
//input - массив 
//output - i от наименьшего элемент
//4 2 2 3 7 8
//i = 3 -> 4
//i = 4 -> 7
//
//output = (quicksort(array))[i]
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#define TIME cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; printf("%f\n",cpu_time_used);

int checker(const int *a, const int size){
	for(int i =0; i < size-1; ++i){
		if(a[i] > a[i+1])
        return 1;
	}
    return 0;
}

void view_arr(const int *a, const int size){
	for(int i =0; i < size; ++i){
		printf("%2d ",a[i]);	
	}
	printf("\n");
}

void random_array(int*a , const int MS){
    for(int i = 0; i < MS; ++i){
		srand(time(0) * i);
		a[i] = rand();
	}
}

void quick_sort_grog(int *a, const int MS){
    int tmp,opora;
    int l = 0;
    if(MS < 2)
        return;
    
    if(MS == 2){
        if(a[0] > a[1]){
            tmp = a[1];a[1] = a[0];a[0] = tmp;
            return;     
    }}

    opora = a[rand()%MS];
    for(int i=0; i<MS; ++i){
        if(a[i] < opora){
            tmp  = a[l];
            a[l] = a[i];
            a[i] = tmp;
            ++l;
        }
    }
    if(!l && !checker(a,MS)) 
            return;

    quick_sort_grog(a,l);
    quick_sort_grog(a+l,MS-l);
}
int RSelect(int *a, const int size, const int find){
    if(size == 1){
        return a[0];    
    }
    
    int opora = a[rand()%size];
    int tmp,i;
    int l = 0;
    
    for(i = 0; i<size; ++i){
        if(a[i] < opora){
            tmp  = a[l];
            a[l] = a[i];
            a[i] = tmp;
            ++l;
        }
    }

    if(find == l)    
        return opora;
    
    if(find > l)
        return RSelect (a+l,size-l,find-l);
    
    if(find < l)
        return RSelect (a,l,find);
    
    return -1; //never
}

int main(){
    clock_t start, end;
    double cpu_time_used;
    int i = 4;
    int size = 5000;
    printf("malloc %d byte\n",size*8);
    int *a = malloc(size*sizeof(int));
    int *b = malloc(size*sizeof(int));
    
    random_array(a,size);
    memcpy(b,a,size*sizeof(int));
    
    start = clock();
        int x = RSelect(b,size,i);
        end = clock();
        printf("RSelect   [%d] = %d\n",i,x);
        TIME

    start = clock();
        quick_sort_grog(a,size);
        end = clock();
        printf("quicksort [%d] = %d\n",i,a[i]);
        TIME
    free(a);
    free(b);
    return 0;
}



