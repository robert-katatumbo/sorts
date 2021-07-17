//  Инверсия массива—это пара элементов, которые расположены 
//  «вне своего естественного порядка». 
//  Это означает, что элемент, который в массиве
//  встречается ранее, больше, чем тот, который встречается позже.
//
//  a           b
//  1   3   5   2   4   6
//  2   4   6 - right merge
//  3:2 5:2 5:4 = 3 inv 
//  
//  Применяется для ранжирования 
//  Совместная фильтрация
//  левая инверсия
//  правая инверсия
//  разделелнная инверсия  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

void view_arr(const int *a, const int size){
	for(int i =0; i < size; ++i){
		printf("%2d ",a[i]);	
	}
	printf("\n");
}
void merging(int*a, int*b, const int size,int *buf, int *count){
    int asize = size/2;
    int bsize = size - size/2;
    int temp = 0;
    int acurr = 0;
    int bcurr = 0;
    while((acurr - asize) && (bcurr - bsize)){//left of right arrays done
        if(a[acurr] > b[bcurr]){
            buf[temp] = b[bcurr];
            //  if b[i] < a[i] ist inv
            *count = *count + asize-acurr;
            ++bcurr;
        } else {
            buf[temp] = a[acurr];
            ++acurr;        
        }   
        ++temp;
    }
    if(acurr!=asize){
        memcpy(buf+temp,a+acurr,(asize-acurr)*sizeof(int));
    }else{
        memcpy(buf+temp,b+bcurr,(bsize-bcurr)*sizeof(int));
    }
    memcpy(a,buf,size*sizeof(int));
  //memcpy(куда,откуда,сколько байт) 
}

void merge_sort(int *a, const int size, int *buf,int *count){
    int temp;
    if(size == 2){
        if(a[0] > a[1]){
            temp = a[1];
            a[1] = a[0];
            a[0] = temp;
            *count+=1;        
        }
        return;   
    }
    if(size!=3)
        merge_sort(a,size/2,buf,count);
    merge_sort(a+size/2,size-size/2,buf,count);
    
    merging(a,a+size/2,size,buf,count);
}

int merge_call(int *a, const int size){
    if(size < 2) return 0;
    int *buf = malloc(size*sizeof(int));
    int count = 0;
    merge_sort(a,size,buf,&count);
    free(buf);
    return count;
}

int brute_force(int *a, int size){
    int sum = 0;
    int i,j;
    for(i = 0; i<size-1; ++i){
        for(j = i+1; j<size; ++j){
            if(a[i] > a[j])
                ++sum;        
        }
    }
    return sum;
}


int main(){
    clock_t start, end;
    int inv = 0;
    double cpu_time_used;
    const int size = 50000;
    int a[size];
    a[0] = 1;
    a[1] = 3;
    a[2] = 5;
    a[3] = 2;
    a[4] = 4;
    a[5] = 6;
    for(int i = 0; i < size; ++i){
		srand(time(0) + i);
		a[i] = rand()%size;
	}
    start = clock();
        inv = brute_force(a,size);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("brute inv %d %f\n",inv,cpu_time_used);
    
    start = clock();
        inv = merge_call(a,size);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("merge inv %d %f\n",inv,cpu_time_used);    

    return 0;
}

























