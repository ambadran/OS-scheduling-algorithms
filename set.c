#include "scheduling_algorithms.h"


Set* set_create() {

  // creating a pointer to a newly created set which we can return
  Set* new_set = (Set*)malloc(sizeof(Set)); 

  // initial set is empty with size 0
  new_set->length = 0; 

  // members is just an array of Process datatype
  new_set->members = (Process*)malloc(sizeof(Process));

  return new_set;

}


void set_extend(Set* set, Process process) {

  // This process is indeed not already in set
  if(!set_contains(set, process)) {

    // increasing the length of our set
    set->length++; 
    //re allocating new memory to engulf the new process :)
    set->members = realloc(set->members, (set->length)*sizeof(Process));
    // adding the new member
    set->members[set->length-1] = process;

  }

}


void set_remove(Set*set, Process process) {



}


bool set_contains(Set* set, Process process) {

  bool in_set = false;

  for (int i = 0; i< set->length; i++) {
    if (set->members[i].id == process.id) {
      in_set = true;
    }
  }

  return in_set;

}


bool set_is_empty(Set* set) {

  return (set->length == 0);

}


void print_set(Set* set) {

  for(int i = 0; i < set->length ; i++) {

    print_process(set->members[i]);
    printf("\n");

  }

}


void kill_set(Set* set) {

  free(set);

}
