

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool helper(const AvailabilityMatrix&, const size_t, const size_t, DailySchedule&, int, int, int, vector<int>);
// Add your implementation of schedule() and other helper functions here

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
    vector<int> shiftsByWorker;
    for(int i = 0;i<(int)avail[0].size();i++) shiftsByWorker.push_back(0);
    for(int i = 0;i<(int)avail.size();i++) sched.push_back(vector<unsigned int>());

    return helper(avail, dailyNeed, maxShifts, sched, 0, 0, 0, shiftsByWorker);
}









bool helper(const AvailabilityMatrix& avail,const size_t dailyNeed,const size_t maxShifts,DailySchedule& sched, int day, int shiftNum, int worker, vector<int> shiftsByWorker)
{
    if(day == (int)avail.size()){
        return true;
    }
    else if(shiftNum == (int)dailyNeed){
        cout << "next day" << endl;
        return helper(avail,dailyNeed,maxShifts,sched,day+1,0,0,shiftsByWorker);
    }
    else{
        for(int i = worker;i<(int)avail[day].size();i++){
            cout << i << endl;
            if(avail[day][i] && (shiftsByWorker[i] < (int)maxShifts)){
                cout << "viable option" << endl;
                sched[day].push_back(i);
                shiftsByWorker[i]++;
                cout << "recursive call" << endl;
                if(helper(avail,dailyNeed,maxShifts,sched,day,shiftNum+1,i+1,shiftsByWorker)){
                    return true;
                }
                //remove most recent addition
                sched[day].pop_back();
                shiftsByWorker[i]--;
            }
        }
        return false;
    }
}
