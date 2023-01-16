
#ifndef IMPLEMENTATIONS_H
#define IMPLEMENTATIONS_H


// assigns arrival time to each process in the processes list
void read_arrival_time(Process* processes);

// assigns arrival time to each process in the processes list
void read_burst_time(Process* processes);

// assigns priority value to each process in the processes list
#if (CURRENT_ALGORITHM == PRIORITY_SCHEDULING)
void read_priority_value(Process* processes);
#endif

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
