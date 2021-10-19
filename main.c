// Include directives

#include <stdio.h>    // For printing
#include <unistd.h>   // For sleep() function
#include <pthread.h>  // For threads and mutexes
#include <string.h>   // For strcmp()
#include <stdlib.h>   // For rand()


// Definitions
#define FALSE 0
#define TRUE  1


pthread_mutex_t lock;                                            
pthread_cond_t cond[5];           // Decleare condition variables of the philosophers

enum philosopher_state { THINKING, HUNGRY, EATING };  // Philosophers alternate between Thinking and Eating.Also adding Hungry as a middle state is useful for condition checks                                                      
enum philosopher_state state[5];
int Philosophers[5] = {0,1,2,3,4};   // Philosopher's identification numbers
int passed_argc;                    // Integer variable to store the number of arguments passed to main thread
char **passed_argv;                 // String variable to store the arguments passed to main thread


// Function declerations
void *chow_line     (void *nphilosopher);
void pickup_forks   (int ph_num);
void putdown_forks  (int ph_num);
void control        (int ph_num);


// Starting point of the main thread and also the program itself
int main(int argc, char **argv)
{
  passed_argc = argc;     // Assign private arguments to the public ones
  passed_argv = argv;
  
  pthread_t philosopher_life[5];                // Declare philosopher threads
  pthread_mutex_init(&lock, NULL);              // Initialize the mutex lock

  for (int i = 0; i < 5; i++) {                 // Initialize the  condition variables
    pthread_cond_init(&cond[i], NULL); }

  for (int i = 0; i < 5; i++)                   // Create the philosopher threads
    pthread_create(&philosopher_life[i], NULL, chow_line, &Philosophers[i]);
    
  for (int i = 0; i < 5; i++)                   // Wait for threads finishing their tasks
    pthread_join(philosopher_life[i], NULL);

  pthread_mutex_destroy(&lock);                 // Remove mutex lock from memory
  for (int i = 0; i < 5; i++)                   // Remove conditions from memory
    pthread_cond_destroy(&cond[i]);


  return(0); }

/*
 Starting point of the child threads
 Every philosopher alternate between Thinking and Eating, infinetely
 --> nphilosopher : The identity number of philosopher which is executing the lifecyle function currently
*/
void *chow_line(void *nphilosopher)
{
  while(TRUE) {       
    int *no_philosopher = nphilosopher;
    sleep( 1 + (rand() % 2));   
                                
    printf("Philosopher %d is THINKING.\n", *no_philosopher + 1);
    if(passed_argc > 1){                                    
        if(strcmp(passed_argv[1], "--with-time") == 0)      
          sleep(1+(rand()%2));                              
    }
    state[*no_philosopher] = HUNGRY;
    printf("Philosopher %d is HUNGRY.\n", *no_philosopher + 1);
    pickup_forks(*no_philosopher);    
    putdown_forks(*no_philosopher);   
  }
}


	
void pickup_forks(int no_philosopher) {
  pthread_mutex_lock(&lock);      

  control(no_philosopher);      
  while (state[no_philosopher] != EATING) 
    pthread_cond_wait(&cond[no_philosopher], &lock);   
                                                      
  pthread_mutex_unlock(&lock);    
}


 //When the eating task is finished, the philosophers must release the forks  and looks if their neighbors are hungry

void putdown_forks(int no_philosopher) {
  pthread_mutex_lock(&lock);          // Lock the putdown_forks function in order to pretend mutual exclusion

  state[no_philosopher] = THINKING;   // Philosopher finished eating and started thinking again
  control((no_philosopher + 4) % 5);     // Make left neighbor eating if she is hungry
  control((no_philosopher + 1) % 5);     // Make right neighbor eating if she is hungry

  pthread_mutex_unlock(&lock);        // Release the putdown_forks function
}


 //If the current philosopher is hungry,Check her left and right neighbors if they are hungry and if they are not, start eating

void control(int no_philosopher) {
  if (state[no_philosopher] == HUNGRY                 // Check if current philosopher wants eating
    && state[(no_philosopher + 4) % 5] != EATING      // Check if left neighbor is not eating
    && state[(no_philosopher + 1) % 5] != EATING) {   // Check if right neighbor is not eating
      
      state[no_philosopher] = EATING;
      printf("Philosopher %d is EATING.\n", no_philosopher + 1);
      if(passed_argc > 1){                                 // If the main thread is called with --with-time argument,
        if(strcmp(passed_argv[1], "--with-time") == 0)     // make philosopher thinking for a random number of time
          sleep(1+(rand()%2));                             // between 1 and 3
      }
      pthread_cond_signal(&cond[no_philosopher]);     // Signal if philosopher starts eating
  }
}
