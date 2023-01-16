
#ifndef SET_H
#define SET_H


typedef struct {

  Process* members; // the underlying data structure of set is just an array

  int length;

} Set;


// initializes the set data structure
Set* set_create();

// add a new process into this set
void set_extend(Set* set, Process process);

// removes a certain process form this set
void set_remove(Set*set, Process process);

// compaires process.id with every process id inside the set
bool set_contains(Set* set, Process process);

// return whether set is empty or not
bool set_is_empty(Set* set);

// shows the insides of the set
void print_set(Set* set);

// deinit set altogether
void kill_set(Set* set);

#endif
