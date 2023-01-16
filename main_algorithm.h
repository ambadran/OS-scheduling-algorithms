#ifndef MAIN_ALGORITHM_H
#define MAIN_ALGORITHM_H

#define BURST_VALUE 0
#if (CURRENT_ALGORITHM == PRIORITY_VALUE)
#define PRIORITY_VALUE 1
#endif

#define MINIMUM_VALUE_FIRST 0
#define MAXIMUM_VALUE_FIRST 1

// solves for completion time or any pre-emptive algorithm according to// what value to prioritize for (burst value, priority value) and whether
// the order is in ascending or descending order
void solve_pre_emptive(Process* processes, int priority_select, bool max_min_select);

// solves for completion time or any non-pre-emptive algorithm according to// what value to prioritize for (burst value, priority value) and whether
// the order is in ascending or descending order
void solve_non_pre_emptive(Process* processes, int priority_select, bool max_min_select);

#endif
