#include "scheduling_algorithms.h"


// assigns arrival time to each process in the processes list
void read_arrival_time(Process* processes) {

#if TESTING_MODE

  processes[0].arrival = 0; 
  processes[1].arrival = 1;
  processes[2].arrival = 2;
  processes[3].arrival = 5;
  processes[4].arrival = 7;

#else
  int arrival_time;

  for (int i = 0; i<num_processes; i++) {

    printf("Enter Arrival time for Process %d: ", i+1);
    scanf("%d", &arrival_time);

    processes[i].arrival = arrival_time;

  }

  printf("\n");

#endif

}

// assigns arrival time to each process in the processes list
void read_burst_time(Process* processes) {

#if TESTING_MODE

  processes[0].burst = 4; 
  processes[1].burst = 4;
  processes[2].burst = 2;
  processes[3].burst = 1;
  processes[4].burst = 3;

#else
  int burst_time;

  for (int i = 0; i<num_processes; i++) {

    printf("Enter Burst time for Process %d: ", i+1);
    scanf("%d", &burst_time);

    processes[i].burst = burst_time;

  }

  printf("\n");

#endif

}

#if (CURRENT_ALGORITHM == PRIORITY_SCHEDULING)
// assigns priority value to each process in the processes list
void read_priority_value(Process* processes) {

#if TESTING_MODE

  processes[0].priority = 0; 
  processes[1].priority = 1;
  processes[2].priority = 2;
  processes[3].priority = 5;
  processes[4].priority = 7;

#else
  int priority_value;

  for (int i = 0; i<num_processes; i++) {

    printf("Enter Priority value for Process %d: ", i+1);
    scanf("%d", &priority_value);

    processes[i].priority = priority_value;

  }

  printf("\n");

#endif

}
#endif

// calculates the completion time according to choose algorithm
void calc_completion_time(Process* processes) {

#if (CURRENT_ALGORITHM == FIRST_COME_FIRST_SERVE) 

solve_non_pre_emptive(processes, NULL, NULL);
 
#elif (CURRENT_ALGORITHM == SHORTEST_JOB_FIRST_PRE)

solve_pre_emptive(processes, BURST_VALUE, MINIMUM_VALUE_FIRST);

#elif (CURRENT_ALGORITHM == SHORTEST_JOB_FIRST_NON_PRE)

solve_non_pre_emptive(processes, BURST_VALUE, MINIMUM_VALUE_FIRST);

#elif (CURRENT_ALGORITHM == LONGEST_JOB_FIRST)

solve_non_pre_emptive(processes, BURST_VALUE, MAXIMUM_VALUE_FIRST);

#elif (CURRENT_ALGORITHM == PRIORITY_SCHEDULING)

solve_non_pre_emptive(processes, PRIORITY_VALUE, MINIMUM_VALUE_FIRST);

#elif (CURRENT_ALGORITHM == ROUND_ROBIN)

solve_pre_emptive(processes, NULL, NULL);

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

// prints one process
void print_process(Process process) {

printf("Process ID: %d\nArrival time: %d\nBurst time: %d\nCompletion time: %d\nTurn Around time: %d\nWaiting time: %d\n", process.id, process.arrival, process.burst, process.completion, process.turn_around, process.waiting);


}

// prints the list of process strucutures
void print_processes(Process* processes) {

  for(int i = 0; i<num_processes; i++) {

    print_process(processes[i]);

    printf("\n");

  } 
}

//frees the heap memory
void garbage_collection(Process* processes) {
  free(processes);
}


