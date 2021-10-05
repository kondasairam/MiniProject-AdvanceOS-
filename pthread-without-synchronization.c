#include<stdio.h>
#include<stdlib.h>

// pthread.h library is used for pthread create and join methods
#include<pthread.h> 
// ctype.h library is used for isdigit method
#include<ctype.h>
// unistd.h library is used for usleep method 
#include<unistd.h>

int SharedVariable = 0;

//Function is used to check whether it is an integer or not
int isNumber(char number[]){
  int i=0;
  //checking for negative numbers
  if(number[0]=='-'){
    i=1;
  }
  
  for(;number[i]!=0;i++){
     //if(number[i]>'9' || number[i]<'0') checking the ascii for 0 to 9
     if(!isdigit(number[i])){
        return 0;
     }
  }
  return 1;
}

void SimpleThread(int which) {
   int num, val;
   
   for(num=0; num < 20; num++) {
     if(random() > RAND_MAX/2) {
       usleep(500);
     }
     
     val=SharedVariable;
     printf("***thread %d sees value %d\n",which, val);
     SharedVariable = val+1;
   }
   
   val = SharedVariable;
   printf("***thread %d sees final value %d\n",which, val);
}

// This function converts argument void* type to integer 
void *simpleThread(void * i) {
   int * k=(int *)i;
   int which= *k;
   
   //Calling SimpleThread function
   SimpleThread(which);
}

int main(int argc, char *argv[]){
   int i; 
   int check_num = isNumber(argv[1]); 
   
   // This handles if the given argument is not integer
   if(check_num == 0) {
     printf("It is an arbitary string");
     return 0;
   } 
   
   // Converting cmd line argument to interger  
   int Num_threads = atoi(argv[1]);
   // Declaring Pthread id's 
   pthread_t tid[Num_threads];
   
   //Create / fork threads
   for(i=0; i< Num_threads; i++) {
     int *arg=malloc(sizeof(*arg));
     *arg=i;
     pthread_create(&tid[i], NULL,simpleThread, arg);
     printf("%d",i);
   }
   
   //wait / join threads
   for(i=0; i < Num_threads; i++) { 
     pthread_join(tid[i], NULL);
   }
   
   return 0;
}
