
#ifndef IMPLEMENTATIONS_H
#define IMPLEMENTATIONS_H

int num_processes;

typedef struct {

  int id; // initial value so that it is known this one is only initialized not set
  int arrival;
  int burst;
  int completion;
  int turn_around;
  int waiting;

} Process;

// Reads how many processes needs to be created and creates them
// return heap pointer to a list of process structures
Process* create_processes(int *num_processes);

// assigns arrival time to each process in the processes list
void read_arrival_time(Process* processes);

// assigns arrival time to each process in the processes list
void read_burst_time(Process* processes);

// calculate the completion time using the wanted algorithm
void calc_completion_time(Process* processes);

// assigns arrival time to each process in the processes list
void calc_turn_around_time(Process* processes);

// assigns arrival time to each process in the processes list
void calc_waiting_time(Process* processes);

// return average turn around time
float calc_average_turn_around_time(Process* processes);

// return average waiting time
float calc_average_waiting_time(Process* processes);

// prints one process
void print_process(Process process);

// prints the list of Processes structures
void print_processes(Process* processes);

//frees the heap memory
void garbage_collection(Process* processes);

#endif
