#include "scheduling_algorithms.h"

//TODO: put this functions in its own array.c file
bool not_in_there(Process* array, Process process) {

  bool not_in_there = true;
  for(int i = 0; i<num_processes; i++) {
    if (array[i].id == process.id) {
      not_in_there = false; 
    }
  }

  return not_in_there;

}


Process getMin_burst(Process* processes) {

  Process min = processes[0];

  for (int i = 1; i < num_processes; i++) {
    if (processes[i].burst < min.burst) {
      min = processes[i];
    }
  }

  return min;

}


// Reads how many processes needs to be created and creates them
// return heap pointer to a list of process structures
Process* create_processes(int *num_processes) {

#if TESTING_MODE

  *num_processes = 5;

#else
  printf("Enter the number of Processes: ");
  scanf("%d", num_processes);
  printf("\n");
#endif

  // creating a custom sized array of Process in Heap
  Process* processes = (Process*)malloc(*num_processes*sizeof(Process));

  // assigning ID's
  for (int i = 0; i < *num_processes; i++) {
    processes[i].id = i;
  }

  return processes;
 
}

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

free(FCFS);
  
#elif (CURRENT_ALGORITHM == SHORTEST_JOB_FIRST_PRE)


//********************************//
Node* SJFNP = newNode(&processes[0], processes[0].arrival);
for (int i = 1; i < num_processes; i++) {
  push(&SJFNP, &processes[i], processes[i].arrival); //TODO: add a second priority thing when pushing in this. This causes a bug where when it searches for the first time after idle it doesn't consider the other priority
}

int prev_completion = 0;
int done_array_counter = 0;

Process* done_array = (Process*)malloc(num_processes*sizeof(Process)); // array of done_array
for (int i = 0; i<num_processes; i++) {
  done_array[i].id = -1; // initial value is -1
}

while(!isEmpty(&SJFNP)) {


  // next not in done_array: take arrival + burst then pop else pop
  if(not_in_there(done_array, *peek(&SJFNP))) {
    
#if DEBUG_MODE
    printf("\nArrivalTime input\n");
    print_process(*peek(&SJFNP));
    printf("lkjkjfherherhehrerer\n\n");
#endif

    peek(&SJFNP)->completion = peek(&SJFNP)->arrival + peek(&SJFNP)->burst;

    prev_completion = peek(&SJFNP)->completion;

    done_array[done_array_counter] = *peek(&SJFNP); // POSSIBLE PROBLEM could be * here before peek
    done_array_counter++;                                              

    pop(&SJFNP);

    // dealing with other process that came within this current process's completion time
    for (int i = 0; i<num_processes; i++) {
      
      // if it's not already dealth with and is within comp time
      if (not_in_there(done_array, processes[i]) && processes[i].id == getMin_burst(processes).id) {         

        processes[i].completion = prev_completion + processes[i].burst;
        prev_completion = processes[i].completion;

        done_array[done_array_counter] = processes[i];
        done_array_counter++;

      }
    }


  } else {
    // this process is dealt with inside another process
    pop(&SJFNP);
  }
}
 
free(SJFNP);
free(done_array);
//********************************//

#elif (CURRENT_ALGORITHM == SHORTEST_JOB_FIRST_NON_PRE)

Node* SJFNP = newNode(&processes[0], processes[0].arrival);
for (int i = 1; i < num_processes; i++) {
  push(&SJFNP, &processes[i], processes[i].arrival); //TODO: add a second priority thing when pushing in this. This causes a bug where when it searches for the first time after idle it doesn't consider the other priority
}

int prev_completion = 0;
int done_array_counter = 0;

Process* done_array = (Process*)malloc(num_processes*sizeof(Process)); // array of done_array
for (int i = 0; i<num_processes; i++) {
  done_array[i].id = -1; // initial value is -1
}

while(!isEmpty(&SJFNP)) {


  // next not in done_array: take arrival + burst then pop else pop
  if(not_in_there(done_array, *peek(&SJFNP))) {
    

    peek(&SJFNP)->completion = peek(&SJFNP)->arrival + peek(&SJFNP)->burst;

    prev_completion = peek(&SJFNP)->completion;

    done_array[done_array_counter] = *peek(&SJFNP); // POSSIBLE PROBLEM could be * here before peek
    done_array_counter++;                                              

#if DEBUG_MODE
    printf("\nArrivalTime input\n");
    print_process(*peek(&SJFNP));
    printf("lkjkjfherherhehrerer\n\n");
#endif

    pop(&SJFNP);

    // dealing with other process that came within this current process's completion time
    for (int i = 0; i<num_processes; i++) {

      // if it's not already dealth with and is within comp time
      if (not_in_there(done_array, processes[i]) && processes[i].arrival < prev_completion) {         

        /* min = processes[i] */
/* processes[i].id == getMin_burst(processes).id */ 
#if DEBUG_MODE
        printf("process1\n");
        print_process(processes[i]);
        printf("prev compl: %d\n", prev_completion);
        printf("\n\n");
#endif

        processes[i].completion = prev_completion + processes[i].burst;
        prev_completion = processes[i].completion;

        done_array[done_array_counter] = processes[i];
        done_array_counter++;

#if DEBUG_MODE
        printf("process2\n");
        print_process(processes[i]);
        printf("\n\n");
#endif

      }
    }


  } else {
    // this process is dealt with inside another process
    pop(&SJFNP);
  }
}
 
free(SJFNP);
free(done_array);

#elif (CURRENT_ALGORITHM == LONGEST_JOB_FIRST)

//********************************//
Node* SJFNP = newNode(&processes[0], processes[0].arrival);
for (int i = 1; i < num_processes; i++) {
  push(&SJFNP, &processes[i], processes[i].arrival); //TODO: add a second priority thing when pushing in this. This causes a bug where when it searches for the first time after idle it doesn't consider the other priority
}

int prev_completion = 0;
int done_array_counter = 0;

Process* done_array = (Process*)malloc(num_processes*sizeof(Process)); // array of done_array
for (int i = 0; i<num_processes; i++) {
  done_array[i].id = -1; // initial value is -1
}

while(!isEmpty(&SJFNP)) {


  // next not in done_array: take arrival + burst then pop else pop
  if(not_in_there(done_array, *peek(&SJFNP))) {
    
#if DEBUG_MODE
    printf("\nArrivalTime input\n");
    print_process(*peek(&SJFNP));
    printf("lkjkjfherherhehrerer\n\n");
#endif

    peek(&SJFNP)->completion = peek(&SJFNP)->arrival + peek(&SJFNP)->burst;

    prev_completion = peek(&SJFNP)->completion;

    done_array[done_array_counter] = *peek(&SJFNP); // POSSIBLE PROBLEM could be * here before peek
    done_array_counter++;                                              

    pop(&SJFNP);

    // dealing with other process that came within this current process's completion time
    for (int i = 0; i<num_processes; i++) {
      
      // if it's not already dealth with and is within comp time
      if (not_in_there(done_array, processes[i]) && processes[i].id == getMin_burst(processes).id) {         

        processes[i].completion = prev_completion + processes[i].burst;
        prev_completion = processes[i].completion;

        done_array[done_array_counter] = processes[i];
        done_array_counter++;

      }
    }


  } else {
    // this process is dealt with inside another process
    pop(&SJFNP);
  }
}
 
free(SJFNP);
free(done_array);
//********************************//

#elif (CURRENT_ALGORITHM == PRIORITY_SCHEDULING)


//********************************//
Node* SJFNP = newNode(&processes[0], processes[0].arrival);
for (int i = 1; i < num_processes; i++) {
  push(&SJFNP, &processes[i], processes[i].arrival); //TODO: add a second priority thing when pushing in this. This causes a bug where when it searches for the first time after idle it doesn't consider the other priority
}

int prev_completion = 0;
int done_array_counter = 0;

Process* done_array = (Process*)malloc(num_processes*sizeof(Process)); // array of done_array
for (int i = 0; i<num_processes; i++) {
  done_array[i].id = -1; // initial value is -1
}

while(!isEmpty(&SJFNP)) {


  // next not in done_array: take arrival + burst then pop else pop
  if(not_in_there(done_array, *peek(&SJFNP))) {
    
#if DEBUG_MODE
    printf("\nArrivalTime input\n");
    print_process(*peek(&SJFNP));
    printf("lkjkjfherherhehrerer\n\n");
#endif

    peek(&SJFNP)->completion = peek(&SJFNP)->arrival + peek(&SJFNP)->burst;

    prev_completion = peek(&SJFNP)->completion;

    done_array[done_array_counter] = *peek(&SJFNP); // POSSIBLE PROBLEM could be * here before peek
    done_array_counter++;                                              

    pop(&SJFNP);

    // dealing with other process that came within this current process's completion time
    for (int i = 0; i<num_processes; i++) {
      
      // if it's not already dealth with and is within comp time
      if (not_in_there(done_array, processes[i]) && processes[i].id == getMin_burst(processes).id) {         

        processes[i].completion = prev_completion + processes[i].burst;
        prev_completion = processes[i].completion;

        done_array[done_array_counter] = processes[i];
        done_array_counter++;

      }
    }


  } else {
    // this process is dealt with inside another process
    pop(&SJFNP);
  }
}
 
free(SJFNP);
free(done_array);
//********************************//

#elif (CURRENT_ALGORITHM == ROUND_ROBIN)


//********************************//
Node* SJFNP = newNode(&processes[0], processes[0].arrival);
for (int i = 1; i < num_processes; i++) {
  push(&SJFNP, &processes[i], processes[i].arrival); //TODO: add a second priority thing when pushing in this. This causes a bug where when it searches for the first time after idle it doesn't consider the other priority
}

int prev_completion = 0;
int done_array_counter = 0;

Process* done_array = (Process*)malloc(num_processes*sizeof(Process)); // array of done_array
for (int i = 0; i<num_processes; i++) {
  done_array[i].id = -1; // initial value is -1
}

while(!isEmpty(&SJFNP)) {


  // next not in done_array: take arrival + burst then pop else pop
  if(not_in_there(done_array, *peek(&SJFNP))) {
    
#if DEBUG_MODE
    printf("\nArrivalTime input\n");
    print_process(*peek(&SJFNP));
    printf("lkjkjfherherhehrerer\n\n");
#endif

    peek(&SJFNP)->completion = peek(&SJFNP)->arrival + peek(&SJFNP)->burst;

    prev_completion = peek(&SJFNP)->completion;

    done_array[done_array_counter] = *peek(&SJFNP); // POSSIBLE PROBLEM could be * here before peek
    done_array_counter++;                                              

    pop(&SJFNP);

    // dealing with other process that came within this current process's completion time
    for (int i = 0; i<num_processes; i++) {
      
      // if it's not already dealth with and is within comp time
      if (not_in_there(done_array, processes[i]) && processes[i].id == getMin_burst(processes).id) {         

        processes[i].completion = prev_completion + processes[i].burst;
        prev_completion = processes[i].completion;

        done_array[done_array_counter] = processes[i];
        done_array_counter++;

      }
    }


  } else {
    // this process is dealt with inside another process
    pop(&SJFNP);
  }
}
 
free(SJFNP);
free(done_array);
//********************************//

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

void print_process(Process process) {

printf("Process ID: %d\nArrival time: %d\nBurst time: %d\nCompletion time: %d\nTurn Around time: %d\nWaiting time: %d\n", process.id, process.arrival, process.burst, process.completion, process.turn_around, process.waiting);


}

// prints the list of process strucutures
void print_processes(Process* processes) {

  for(int i = 0; i<num_processes; i++) {

    printf("Process ID: %d\nArrival time: %d\nBurst time: %d\nCompletion time: %d\nTurn Around time: %d\nWaiting time: %d\n", processes[i].id, processes[i].arrival, processes[i].burst, processes[i].completion, processes[i].turn_around, processes[i].waiting);

    printf("\n");

  } 
}

void garbage_collection(Process* processes) {
  free(processes);
}
