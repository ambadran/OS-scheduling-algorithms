#ifndef process_H
#define process_H

int num_processes;

typedef struct {

  int id; // initial value so that it is known this one is only initialized not set
  int arrival;
  int burst;
  int completion;
  int turn_around;
  int waiting;
#if (CURRENT_ALGORITHM == PRIORITY_SCHEDULING)
  int priority;
#endif

} Process;

// extracts Process attribute using an integer refrence. e.g- instead of process.burst, get_attr_int_refrence(process, 2)
int get_attr_int_refrence(Process process, int int_ref);

// Reads how many processes needs to be created and creates them
// return heap pointer to a list of process structures
Process* create_processes(int *num_processes);



#endif
