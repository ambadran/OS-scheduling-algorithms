#include "scheduling_algorithms.h"

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


