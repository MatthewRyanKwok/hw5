#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool helper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& shiftCounts,
    size_t day,
    size_t slot);

// Add your implementation of schedule() and other helper functions here

bool helper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& shiftCounts,
    size_t day,
    size_t slot)
{
    size_t n = avail.size();
    size_t k = avail[0].size();

    if (day == n) { //base case is if all days are filled
        return true;
    }

    if (slot == dailyNeed) { //if current day is scheduled, move on
        return helper(avail, dailyNeed, maxShifts, sched, shiftCounts, day + 1, 0);
    }

    for (size_t worker = 0; worker < k; worker++) { //try each worker
        if (avail[day][worker] && shiftCounts[worker] < static_cast<int>(maxShifts) && find(sched[day].begin(), sched[day].end(), worker) == sched[day].end()) { //conditions are if worker is available/worker has not gone past maxShifts/worker is not already scheduled
            sched[day].push_back(worker); //assign worker
            shiftCounts[worker]++;

            if (helper(avail, dailyNeed, maxShifts, sched, shiftCounts, day, slot + 1)) { //recursion to next slot
                return true;
            }
            sched[day].pop_back(); //backtrack
            shiftCounts[worker]--;
        }
    }
    return false;
}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t n = avail.size(); //num days
    size_t k = avail[0].size(); //num workers

    sched.resize(n); //scheudle has n days
    vector<int> shiftCounts(k,0); //shift for each worker

    return helper(avail, dailyNeed, maxShifts, sched, shiftCounts, 0, 0); //recursive backtrack from day 0/slot 0

}

