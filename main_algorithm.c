#include "scheduling_algorithms.h"

// solves for completion time or any pre-emptive algorithm according to
// what value to prioritize for (burst value, priority value) and whether
// the order is in ascending or descending order
void solve_pre_emptive(Process* processes, int priority_select, bool max_min_select) {



}

// solves for completion time or any pre-emptive algorithm according to
// what value to prioritize for (burst value, priority value) and whether
// the order is in ascending or descending order
void solve_non_pre_emptive(Process* processes, int priority_select, bool max_min_select) {

Node* SJFNP = newNode(&processes[0], processes[0].arrival);
for (int i = 1; i < num_processes; i++) {
  push(&SJFNP, &processes[i], processes[i].arrival, MINIMUM_VALUE_FIRST); //TODO: add a second priority thing when pushing in this. This causes a bug where when it searches for the first time after idle it doesn't consider the other priority
}

int prev_completion = 0;
bool inside_created = false;
#if DEBUG_MODE
  bool entered_internal_algorithm = false; 
#endif

/* bool entered_internal_algorithm = false; */ 
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
    printf("\nInputed according to Arrival time\n");
    print_process(*peek(&SJFNP));
    printf("\n\n");
#endif

    pop(&SJFNP);

    // dealing with other process that came within this current process's completion time
    
    // creating the inside priority queue for the first time
    for (int i = 0; i<num_processes; i++) {
      
      // if it's not already dealth with and is within comp time
      if ((!set_contains(done_processes, processes[i])) && processes[i].arrival <= prev_completion) {         

        if (inside_created) {

          push(&inside, &processes[i], processes[i].burst, max_min_select);
          
        } else {

          inside = newNode(&processes[i], processes[i].burst);
          inside_created = true;

        }

      }
    }

    // loop to finish inside queue. This contains processes that has arrival time before the completion of current process so now
    // we use the respective scheduling algorithm to choose which one to take
#if DEBUG_MODE
    entered_internal_algorithm = false; 
    if(!isEmpty(&inside)) {
      printf("##############Entering Inside Algorithm...\n\n");
      entered_internal_algorithm = true;
    }
#endif
    while(!isEmpty(&inside)) {
      
#if DEBUG_MODE
      printf("\nCurrent inside priority queue:\n\n");
      print_priority_queue(&inside);
      printf("\nCurrent inside priority queue END\n\n");
#endif
      
      peek(&inside)->completion = prev_completion + peek(&inside)->burst;
      prev_completion = peek(&inside)->completion;

      set_extend(done_processes, *peek(&inside));

#if DEBUG_MODE
      printf("\nInputed according to the wanted priority value\n");
      print_process(*peek(&inside));
      printf("\n\n");
#endif

      pop(&inside);

      // dealing with other process that came within this current process's completion time
      for (int i = 0; i<num_processes; i++) {
        
        // if it's not already dealth with and is within comp time
        if ((!set_contains(done_processes, processes[i])) && processes[i].arrival <= prev_completion && (!priority_queue_contains(&inside, processes[i]))) {  
          push(&inside, &processes[i], processes[i].burst, max_min_select);
    
        }
      }
    }
#if DEBUG_MODE
    if(entered_internal_algorithm) {
      printf("############## Exiting internal Algorithm...\n\n");
    }
#endif

  } else {
    // this process is dealt with inside another process
    pop(&SJFNP);
  }
}
 
free(SJFNP);
kill_set(done_processes);

#if DEBUG_MODE
printf("ALGORITHM FINISHED!!\n\n");
#endif

}


