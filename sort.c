#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>
#include <string.h>

#define TIME double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; printf("%f\n",cpu_time_used);
#define CHECK char res = checker(a,MS);if(!res) printf("sort good\n");else printf("sort bad\n");


int cmpfunc (const void * a, const void * b) {
   return (*(int*)a - *(int*)b);
}

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

void shaiker(int *a, const int size){
	printf("shaiker  ");
    if(checker(a,size) == 0){
        return;
    }
    int temp;
	int start = 0;
	int end = size;
	for(int j =0;j<size/2;j++){
		if(start == end)
		break;
		
		for(int i = start; i < end-1; i ++){
			if(a[i] > a[i+1]){
				temp = a[i];
				a[i] = a[i+1];
				a[i+1] = temp;
			}	
		}
		end --;	
		for(int i = end; i > start; i --){
			if(a[i] < a[i-1]){
				temp = a[i];
				a[i] = a[i-1];
				a[i-1] = temp;
			}
		}
		start++;
	}
}

void bubble_sort(int *a, const int size){
    printf("bubble   ");
    if(checker(a,size) == 0){
        return;
    }
	int temp;
	for(int j = 0; j<size; ++j){
		for(int i = 0; i < size-j-1; ++i){
			if(a[i] > a[i+1]){
				temp = a[i];
				a[i] = a[i+1];
				a[i+1] = temp;
			}
		}
	}
}

void select_sort(int *a, const int size){
    printf("select   ");
    if(checker(a,size) == 0){
        return;
    }
    
    int min = INT_MAX;
    int temp = 0;
    int index = 0;
    
    for(int j = 0; j<size; ++j){
        for (int i = index; i<size; ++i){
            if(a[i] < min){
                min = a[i];
                temp = i;
            }
        }
        min = a[index];
        a[index] = a[temp];
        a[temp] = min;
        min = INT_MAX;
        ++index;
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
    //if(!checker(a,MS)) return;
    //opora = a[MS>>1]; // maybe infinity recurcive
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
    //  if infinity cycle and 
    //  sorted this asea

    quick_sort_grog(a,l);
    quick_sort_grog(a+l,MS-l);
}

void merging(int*a, int*b, const int size,int *buf){
    int asize = size/2;
    int bsize = size - size/2;
    int temp = 0;
    int acurr = 0;
    int bcurr = 0;
    while((acurr - asize) && (bcurr - bsize)){
    //    acur of bcurr iss full
        if(a[acurr] > b[bcurr]){
            buf[temp] = b[bcurr];
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

void merge_sort(int *a, const int size, int *buf){
    int temp;
    if(size == 2){
        if(a[0] > a[1]){
            temp = a[1];
            a[1] = a[0];
            a[0] = temp;
        }
        return;   
    }
    if(size!=3)
        merge_sort(a,size/2,buf);
    merge_sort(a+size/2,size-size/2,buf);
    
    merging(a,a+size/2,size,buf);
}

void merge_call(int *a, const int size){
    if(size < 2) return;
    int *buf = malloc(size*sizeof(int));
    printf("mymerge  ");
    merge_sort(a,size,buf);
    free(buf);
}

void funny_char_sort(unsigned char* a, const int size, int*helper){
    int i,h;    
    for(i = 0; i<size; ++i){
        ++helper[a[i]];    
    }
    h = 0;
    for(i =0; i<size; ++i){
        while(!helper[h]){
            ++h;
        }
        a[i] = h;
        --helper[h];
    }
}

void funny_char_call(void (*f)(unsigned char*,const int, int*),const int MS){
    clock_t start, end;
    const int hsize = 256;

    unsigned char *a = malloc(MS);
    int *helper = malloc(hsize*sizeof(int));
    for(int i = 0; i < MS; ++i){
		srand(time(0) + i);
		a[i] += rand();
	}
    for(int i =0; i<hsize;++i)
        helper[i] = 0;
    
    start = clock();
    
    f(a,MS,helper);

    end = clock();
    TIME
    //Good or bad sort print
    char check;
    for(int i =0; i < MS-1; ++i){
		if(a[i] > a[i+1])
        check = 1; //CHECK
	}
    check = 0;
    if(!check) {
        //printf("sort good\n");
    }
    else {
        printf("sort bad\n");
        exit(0);
    }
    free(a);
    free(helper);
}

void random_array(int*a , const int MS){
    for(int i = 0; i < MS; ++i){
		srand(time(0) + i);
		a[i] = rand();
	}
}

void timeopen(void (*f)(int*,const int),int*a,const int MS){
    clock_t start, end;
    start = clock();
    f(a,MS);
    end = clock();
    TIME
    //CHECK
}



#define DEBUG 0
int main(){
    clock_t start, end;
    #if DEBUG == 1
        int MS = 100;
	    int a[MS];
        
        for(int i = 0; i < MS; ++i){
		    srand(time(0) + i);
		    a[i] = rand()%200;
	    }
        view_arr(a,MS);
        start = clock();
            
        //merge_call(a,MS);
        quick_sort_grog(a,MS);
        //shaiker(a,MS);	
        //bubble_sort(a,MS);
        //select_sort(a,MS);



        end = clock();
        //printf("\n");
        view_arr(a,MS);
            
        TIME //define
        CHECK
        
    #else
        const int MS = 100000;
	    int a[MS];
        printf("count %d, %ldkb\n",MS,sizeof(a)/1024);
//      C std qsort
        random_array(a,MS);
        printf("qsortstd ");
        start = clock();
        qsort(a,MS,sizeof(int),cmpfunc);
        end = clock();
        TIME
        //CHECK
        
//      other sort
        printf("counting ");
        funny_char_call(&funny_char_sort,MS);
        
        printf("myqsort  ");
        random_array(a,MS);
        timeopen(&quick_sort_grog,a,MS); 

        random_array(a,MS);
        timeopen(&merge_call,a,MS);

        random_array(a,MS);
        timeopen(&select_sort,a,MS);

        random_array(a,MS);
        timeopen(&shaiker,a,MS);

        random_array(a,MS);
        timeopen(&bubble_sort,a,MS);
        
    #endif  
    
	return 0;
}



















































































