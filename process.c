#include "scheduling_algorithms.h"

static int get_id(Process process) {
  return process.id;
}
static int get_arrival(Process process) {
  return process.arrival;
} 
static int get_burst(Process process) {
  return process.burst;
}
static int get_completion(Process process) {
  return process.completion;
}
static int get_turn_around(Process process) {
  return process.turn_around;
}
static int get_waiting(Process process) {
  return process.waiting;
}
#if (CURRENT_ALGORITHM == PRIORITY_SCHEDULING)
static int get_priority(Process process) {
  return process.priority;
}


// extracts Process attribute using an integer refrence. e.g- instead of process.burst, get_attr_int_refrence(process, 2)
int (*get_attr_int_refrence[7])() = {
  get_id, get_arrival, get_burst, get_completion, get_turn_around,
  get_waiting, get_priority
};
#else
// extracts Process attribute using an integer refrence. e.g- instead of process.burst, get_attr_int_refrence(process, 2)
int (*get_attr_int_refrence[6])() = {
  get_id, get_arrival, get_burst, get_completion, get_turn_around,
  get_waiting 
};
#endif


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


