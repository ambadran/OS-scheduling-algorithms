#include "scheduling_algorithms.h"


// Reads how many processes needs to be created and creates them
// return heap pointer to a list of process structures
Process* create_processes(int *num_processes) {

  printf("Enter the number of Processes: ");
  scanf("%d", num_processes);
  printf("\n");

  // creating a custom sized array of Process in Heap
  Process* processes = (Process*)malloc(*num_processes*sizeof(Process));

  return processes;
 
}

// assigns arrival time to each process in the processes list
void read_arrival_time(Process* processes) {

  int arrival_time;

  for (int i = 0; i<num_processes; i++) {

    printf("Enter Arrival time for Process %d: ", i+1);
    scanf("%d", &arrival_time);

    processes[i].arrival = arrival_time;

  }

  printf("\n");

}

// assigns arrival time to each process in the processes list
void read_burst_time(Process* processes) {

  int burst_time;

  for (int i = 0; i<num_processes; i++) {

    printf("Enter Burst time for Process %d: ", i+1);
    scanf("%d", &burst_time);

    processes[i].burst = burst_time;

  }

  printf("\n");

}

// calculates the completion time according to choose algorithm
void calc_completion_time(Process* processes) {


#if (CURRENT_ALGORITHM == FIRST_COME_FIRST_SERVE) 

Node* FCFS = newNode(&processes[0], processes[0].arrival);
for (int i = 1; i < num_processes; i++) {
  push(&FCFS, &processes[i], processes[i].arrival);
}

int t1;
int prev_completion = 0;

while(!isEmpty(&FCFS)) {

  t1 = peek(&FCFS)->arrival;

  if (prev_completion > t1) {
    t1 = prev_completion;
  }

  peek(&FCFS)->completion = t1 + peek(&FCFS)->burst;

  prev_completion = peek(&FCFS)->completion;

  pop(&FCFS);
  
}
  
#elif (CURRENT_ALGORITHM == SHORTEST_JOB_FIRST_PRE)



#elif (CURRENT_ALGORITHM == SHORTEST_JOB_FIRST_NON_PRE)

Node* SJFNP = newNode(&processes[0], processes[0].arrival);
for (int i = 1; i < num_processes; i++) {
  push(&SJFNP, &processes[i], processes[i].arrival);
}

int t1;
int prev_completion = 0;

while(!isEmpty(&SJFNP)) {

  t1 = peek(&SJFNP)->arrival;

  peek(&SJFNP)->completion = t1 + peek(&SJFNP)->burst;

  prev_completion = peek(&SJFNP)->completion;

  pop(&SJFNP);


  
}
 

#elif (CURRENT_ALGORITHM == LONGEST_JOB_FIRST)



#elif (CURRENT_ALGORITHM == PRIORITY_SCHEDULING)



#elif (CURRENT_ALGORITHM == ROUND_ROBIN)



#endif

}

// assigns arrival time to each process in the processes list
void calc_turn_around_time(Process* processes) {

  for (int i = 0; i<num_processes; i++) {
    processes[i].turn_around = processes[i].completion - processes[i].arrival;
  }

}

// assigns arrival time to each process in the processes list
void calc_waiting_time(Process* processes) {

for (int i = 0; i<num_processes; i++) {
    processes[i].waiting = processes[i].turn_around - processes[i].burst;
  }

}

// return average turn around time
float calc_average_turn_around_time(Process* processes) {

  int sum = 0;

  for(int i = 0; i<num_processes; i++) {
    sum += processes[i].turn_around;
  }

  return (float)sum/num_processes;

}

// return average waiting time
float calc_average_waiting_time(Process* processes) {

  int sum = 0;

  for(int i = 0; i<num_processes; i++) {
    sum += processes[i].waiting;
  }

  return (float)sum/num_processes;

}

// prints the list of process strucutures
void print_processes(Process* processes) {

  for(int i = 0; i<num_processes; i++) {

    printf("Process ID: %d\nArrival time: %d\nBurst time: %d\nCompletion time: %d\nTurn Around time: %d\nWaiting time: %d\n", i+1, processes[i].arrival, processes[i].burst, processes[i].completion, processes[i].turn_around, processes[i].waiting);

    printf("\n");

  } 
}

void garbage_collection(Process* processes) {
  free(processes);
}
