#include "scheduling_algorithms.h"

int main() {

  // Inputs:
  // 1- Num of Processes
  // 2- Arrival Time of each
  // 3- Burst Time of each
  Process* processes = create_processes(&num_processes);
  read_arrival_time(processes);
  read_burst_time(processes);
#if (CURRENT_ALGORITHM == PRIORITY_SCHEDULING)
  read_priority_value(processes);
#endif

  // This is calculate the completion time according to choosen algorithm
  calc_completion_time(processes);

  // Outputs:
  // 1- Turn Arround time for each
  // 2- Waiting time for each
  // 3- Average Turn Around
  // 4- Average Waiting time
  calc_turn_around_time(processes);
  calc_waiting_time(processes);
  
  float average_turn_around_time = calc_average_turn_around_time(processes);
  float average_waiting_time = calc_average_waiting_time(processes);

  // Viewing the outputs
  printf("Result Processes Values:\n\n");
  print_processes(processes);
  printf("Average Turn Around Time: %.3f\nAverage Waiting Time: %.3f\n", average_turn_around_time, average_waiting_time);

  // deleting the list created in Heap memory
  garbage_collection(processes);

  return 0;

}
