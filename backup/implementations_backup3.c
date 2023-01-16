
// calculates the completion time according to choose algorithm
void calc_completion_time(Process* processes) {


#if (CURRENT_ALGORITHM == FIRST_COME_FIRST_SERVE) 

Node* FCFS = newNode(&processes[0], processes[0].arrival);
for (int i = 1; i < num_processes; i++) {
  push(&FCFS, &processes[i], processes[i].arrival, MINIMUM_HIGHEST_PRIORITY);
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

Node* SJFP = newNode(&processes[0], processes[0].arrival);
for (int i = 1; i < num_processes; i++) {
  push(&SJFP, &processes[i], processes[i].arrival, MINIMUM_HIGHEST_PRIORITY); //TODO: add a second priority thing when pushing in this. This causes a bug where when it searches for the first time after idle it doesn't consider the other priority
}

int prev_completion = 0;

bool inside_created = false;
Node* inside;

Set* done_processes = set_create();

while(!isEmpty(&SJFP)) {

  inside_created = false;

  // next not in done_processes: take arrival + burst then pop else pop
  if(!set_contains(done_processes, *peek(&SJFP))) {
    
    peek(&SJFP)->completion = peek(&SJFP)->arrival + peek(&SJFP)->burst;

    prev_completion = peek(&SJFP)->completion;

    set_extend(done_processes, *peek(&SJFP));

#if DEBUG_MODE
    printf("\nArrivalTime input\n");
    print_process(*peek(&SJFP));
    printf("lkjkjfherherhehrerer\n\n");
#endif

    pop(&SJFP);

    // dealing with other process that came within this current process's completion time
    
    // creating the inside priority queue for the first time
    for (int i = 0; i<num_processes; i++) {
      
      // if it's not already dealth with and is within comp time
      if ((!set_contains(done_processes, processes[i])) && processes[i].arrival <= prev_completion) {         

        if (inside_created) {

          push(&inside, &processes[i], processes[i].priority, MINIMUM_HIGHEST_PRIORITY);
          
        } else {

          inside = newNode(&processes[i], processes[i].priority);
          inside_created = true;

        }

      }
    }

    // loop to finish inside queue. This contains processes that has arrival time before the completion of current process so now
    // we use the respective scheduling algorithm to choose which one to take
    while(!isEmpty(&inside)) {
      
      printf("\ncurrent inside priority queue:\n");
      print_priority_queue(&inside);
      printf("Finish\n\n");
      
      peek(&inside)->completion = prev_completion + peek(&inside)->burst;
      prev_completion = peek(&inside)->completion;

      set_extend(done_processes, *peek(&inside));

#if DEBUG_MODE
      printf("\nBurstTimeherere\n");
      print_process(*peek(&inside));
      printf("lskdjflj\n\n");
#endif

      pop(&inside);

      // dealing with other process that came within this current process's completion time
      for (int i = 0; i<num_processes; i++) {
        
        // if it's not already dealth with and is within comp time
        if ((!set_contains(done_processes, processes[i])) && processes[i].arrival <= prev_completion && (!priority_queue_contains(&inside, processes[i]))) {  
          push(&inside, &processes[i], processes[i].priority, MINIMUM_HIGHEST_PRIORITY);
    
        }
      }
    }

  } else {
    // this process is dealt with inside another process
    pop(&SJFP);
  }
}
 
free(SJFP);
kill_set(done_processes);

#elif (CURRENT_ALGORITHM == SHORTEST_JOB_FIRST_NON_PRE)

Node* SJFNP = newNode(&processes[0], processes[0].arrival);
for (int i = 1; i < num_processes; i++) {
  push(&SJFNP, &processes[i], processes[i].arrival, MINIMUM_HIGHEST_PRIORITY); //TODO: add a second priority thing when pushing in this. This causes a bug where when it searches for the first time after idle it doesn't consider the other priority
}

int prev_completion = 0;

bool inside_created = false;
Node* inside;

Set* done_processes = set_create();

while(!isEmpty(&SJFNP)) {

  inside_created = false;

  // next not in done_processes: take arrival + burst then pop else pop
  if(!set_contains(done_processes, *peek(&SJFNP))) {
    
    peek(&SJFNP)->completion = peek(&SJFNP)->arrival + peek(&SJFNP)->burst;

    prev_completion = peek(&SJFNP)->completion;

    set_extend(done_processes, *peek(&SJFNP));

#if DEBUG_MODE
    printf("\nArrivalTime input\n");
    print_process(*peek(&SJFNP));
    printf("lkjkjfherherhehrerer\n\n");
#endif

    pop(&SJFNP);

    // dealing with other process that came within this current process's completion time
    
    // creating the inside priority queue for the first time
    for (int i = 0; i<num_processes; i++) {
      
      // if it's not already dealth with and is within comp time
      if ((!set_contains(done_processes, processes[i])) && processes[i].arrival <= prev_completion) {         

        if (inside_created) {

          push(&inside, &processes[i], processes[i].burst, MINIMUM_HIGHEST_PRIORITY);
          
        } else {

          inside = newNode(&processes[i], processes[i].burst);
          inside_created = true;

        }

      }
    }

    // loop to finish inside queue. This contains processes that has arrival time before the completion of current process so now
    // we use the respective scheduling algorithm to choose which one to take
    while(!isEmpty(&inside)) {
      
      printf("\ncurrent inside priority queue:\n");
      print_priority_queue(&inside);
      printf("Finish\n\n");
      
      peek(&inside)->completion = prev_completion + peek(&inside)->burst;
      prev_completion = peek(&inside)->completion;

      set_extend(done_processes, *peek(&inside));

#if DEBUG_MODE
      printf("\nBurstTimeherere\n");
      print_process(*peek(&inside));
      printf("lskdjflj\n\n");
#endif

      pop(&inside);

      // dealing with other process that came within this current process's completion time
      for (int i = 0; i<num_processes; i++) {
        
        // if it's not already dealth with and is within comp time
        if ((!set_contains(done_processes, processes[i])) && processes[i].arrival <= prev_completion && (!priority_queue_contains(&inside, processes[i]))) {  
          push(&inside, &processes[i], processes[i].burst, MINIMUM_HIGHEST_PRIORITY);
    
        }
      }
    }

  } else {
    // this process is dealt with inside another process
    pop(&SJFNP);
  }
}
 
free(SJFNP);
kill_set(done_processes);

#elif (CURRENT_ALGORITHM == LONGEST_JOB_FIRST)

Node* LJFNP = newNode(&processes[0], processes[0].arrival);
for (int i = 1; i < num_processes; i++) {
  push(&LJFNP, &processes[i], processes[i].arrival, MINIMUM_HIGHEST_PRIORITY); //TODO: add a second priority thing when pushing in this. This causes a bug where when it searches for the first time after idle it doesn't consider the other priority
}

int prev_completion = 0;

bool inside_created = false;
Node* inside;

Set* done_processes = set_create();

while(!isEmpty(&LJFNP)) {

  inside_created = false;

  // next not in done_processes: take arrival + burst then pop else pop
  if(!set_contains(done_processes, *peek(&LJFNP))) {
    
    peek(&LJFNP)->completion = peek(&LJFNP)->arrival + peek(&LJFNP)->burst;

    prev_completion = peek(&LJFNP)->completion;

    set_extend(done_processes, *peek(&LJFNP));

#if DEBUG_MODE
    printf("\nArrivalTime input\n");
    print_process(*peek(&LJFNP));
    printf("lkjkjfherherhehrerer\n\n");
#endif

    pop(&LJFNP);

    // dealing with other process that came within this current process's completion time
    
    // creating the inside priority queue for the first time
    for (int i = 0; i<num_processes; i++) {
      
      // if it's not already dealth with and is within comp time
      if ((!set_contains(done_processes, processes[i])) && processes[i].arrival <= prev_completion) {         

        if (inside_created) {

          push(&inside, &processes[i], processes[i].burst, MAXIMUM_HIGHEST_PRIORITY);
          
        } else {

          inside = newNode(&processes[i], processes[i].burst);
          inside_created = true;

        }

      }
    }

    // loop to finish inside queue. This contains processes that has arrival time before the completion of current process so now
    // we use the respective scheduling algorithm to choose which one to take
    while(!isEmpty(&inside)) {
      
      printf("\ncurrent inside priority queue:\n");
      print_priority_queue(&inside);
      printf("Finish\n\n");
      
      peek(&inside)->completion = prev_completion + peek(&inside)->burst;
      prev_completion = peek(&inside)->completion;

      set_extend(done_processes, *peek(&inside));

#if DEBUG_MODE
      printf("\nBurstTimeherere\n");
      print_process(*peek(&inside));
      printf("lskdjflj\n\n");
#endif

      pop(&inside);

      // dealing with other process that came within this current process's completion time
      for (int i = 0; i<num_processes; i++) {
        
        // if it's not already dealth with and is within comp time
        if ((!set_contains(done_processes, processes[i])) && processes[i].arrival <= prev_completion && (!priority_queue_contains(&inside, processes[i]))) {  
          push(&inside, &processes[i], processes[i].burst, MAXIMUM_HIGHEST_PRIORITY);
    
        }
      }
    }

  } else {
    // this process is dealt with inside another process
    pop(&LJFNP);
  }
}
 
free(LJFNP);
kill_set(done_processes);

#elif (CURRENT_ALGORITHM == PRIORITY_SCHEDULING)

Node* PS = newNode(&processes[0], processes[0].arrival);
for (int i = 1; i < num_processes; i++) {
  push(&PS, &processes[i], processes[i].arrival, MINIMUM_HIGHEST_PRIORITY); //TODO: add a second priority thing when pushing in this. This causes a bug where when it searches for the first time after idle it doesn't consider the other priority
}

int prev_completion = 0;

bool inside_created = false;
Node* inside;

Set* done_processes = set_create();

while(!isEmpty(&PS)) {

  inside_created = false;

  // next not in done_processes: take arrival + burst then pop else pop
  if(!set_contains(done_processes, *peek(&PS))) {
    
    peek(&PS)->completion = peek(&PS)->arrival + peek(&PS)->burst;

    prev_completion = peek(&PS)->completion;

    set_extend(done_processes, *peek(&PS));

#if DEBUG_MODE
    printf("\nArrivalTime input\n");
    print_process(*peek(&PS));
    printf("lkjkjfherherhehrerer\n\n");
#endif

    pop(&PS);

    // dealing with other process that came within this current process's completion time
    
    // creating the inside priority queue for the first time
    for (int i = 0; i<num_processes; i++) {
      
      // if it's not already dealth with and is within comp time
      if ((!set_contains(done_processes, processes[i])) && processes[i].arrival <= prev_completion) {         

        if (inside_created) {

          push(&inside, &processes[i], processes[i].priority, MINIMUM_HIGHEST_PRIORITY);
          
        } else {

          inside = newNode(&processes[i], processes[i].priority);
          inside_created = true;

        }

      }
    }

    // loop to finish inside queue. This contains processes that has arrival time before the completion of current process so now
    // we use the respective scheduling algorithm to choose which one to take
    while(!isEmpty(&inside)) {
      
      printf("\ncurrent inside priority queue:\n");
      print_priority_queue(&inside);
      printf("Finish\n\n");
      
      peek(&inside)->completion = prev_completion + peek(&inside)->burst;
      prev_completion = peek(&inside)->completion;

      set_extend(done_processes, *peek(&inside));

#if DEBUG_MODE
      printf("\nBurstTimeherere\n");
      print_process(*peek(&inside));
      printf("lskdjflj\n\n");
#endif

      pop(&inside);

      // dealing with other process that came within this current process's completion time
      for (int i = 0; i<num_processes; i++) {
        
        // if it's not already dealth with and is within comp time
        if ((!set_contains(done_processes, processes[i])) && processes[i].arrival <= prev_completion && (!priority_queue_contains(&inside, processes[i]))) {  
          push(&inside, &processes[i], processes[i].priority, MINIMUM_HIGHEST_PRIORITY);
    
        }
      }
    }

  } else {
    // this process is dealt with inside another process
    pop(&PS);
  }
}
 
free(PS);
kill_set(done_processes);

#elif (CURRENT_ALGORITHM == ROUND_ROBIN)

Node* RR = newNode(&processes[0], processes[0].arrival);
for (int i = 1; i < num_processes; i++) {
  push(&RR, &processes[i], processes[i].arrival, MINIMUM_HIGHEST_PRIORITY); //TODO: add a second priority thing when pushing in this. This causes a bug where when it searches for the first time after idle it doesn't consider the other priority
}

int prev_completion = 0;

bool inside_created = false;
Node* inside;

Set* done_processes = set_create();

while(!isEmpty(&RR)) {

  inside_created = false;

  // next not in done_processes: take arrival + burst then pop else pop
  if(!set_contains(done_processes, *peek(&RR))) {
    
    peek(&RR)->completion = peek(&RR)->arrival + peek(&RR)->burst;

    prev_completion = peek(&RR)->completion;

    set_extend(done_processes, *peek(&RR));

#if DEBUG_MODE
    printf("\nArrivalTime input\n");
    print_process(*peek(&RR));
    printf("lkjkjfherherhehrerer\n\n");
#endif

    pop(&RR);

    // dealing with other process that came within this current process's completion time
    
    // creating the inside priority queue for the first time
    for (int i = 0; i<num_processes; i++) {
      
      // if it's not already dealth with and is within comp time
      if ((!set_contains(done_processes, processes[i])) && processes[i].arrival <= prev_completion) {         

        if (inside_created) {

          push(&inside, &processes[i], processes[i].priority, MINIMUM_HIGHEST_PRIORITY);
          
        } else {

          inside = newNode(&processes[i], processes[i].priority);
          inside_created = true;

        }

      }
    }

    // loop to finish inside queue. This contains processes that has arrival time before the completion of current process so now
    // we use the respective scheduling algorithm to choose which one to take
    while(!isEmpty(&inside)) {
      
      printf("\ncurrent inside priority queue:\n");
      print_priority_queue(&inside);
      printf("Finish\n\n");
      
      peek(&inside)->completion = prev_completion + peek(&inside)->burst;
      prev_completion = peek(&inside)->completion;

      set_extend(done_processes, *peek(&inside));

#if DEBUG_MODE
      printf("\nBurstTimeherere\n");
      print_process(*peek(&inside));
      printf("lskdjflj\n\n");
#endif

      pop(&inside);

      // dealing with other process that came within this current process's completion time
      for (int i = 0; i<num_processes; i++) {
        
        // if it's not already dealth with and is within comp time
        if ((!set_contains(done_processes, processes[i])) && processes[i].arrival <= prev_completion && (!priority_queue_contains(&inside, processes[i]))) {  
          push(&inside, &processes[i], processes[i].priority, MINIMUM_HIGHEST_PRIORITY);
    
        }
      }
    }

  } else {
    // this process is dealt with inside another process
    pop(&RR);
  }
}
 
free(RR);
kill_set(done_processes);

#endif

}


