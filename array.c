#include "scheduling_algorithms.h"


bool not_in_there(Process* array, Process process) {

  bool not_in_there = true;
  for(int i = 0; i<num_processes; i++) {
    if (array[i].id == process.id) {
      not_in_there = false; 
    }
  }

  return not_in_there;

}


