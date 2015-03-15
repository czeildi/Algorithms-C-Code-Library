#include <algorithm>
#include <vector>

using namespace std;

class interval{
  public:
    int left;
    int right;
    int cost;
    interval(int l, int r) : left(l), right(r) {}
    interval(int l, int r, int c): left(l), right(r), cost(c) {}
    bool operator< (const interval & i) const { //need to adjust this for every problem!
      return (right<i.right);
    }
};

//interval scheduling: max # of disjoint intervals: greedy method
int interval_scheduling(vector<interval> & jobs) {
  sort(jobs.begin(), jobs.end());
  int disjointIntervals = 1;
  auto job = jobs.begin();
  for(auto tempjob = jobs.begin(); tempjob!= jobs.end(); tempjob ++) {
    if (tempjob->left > job->right) {
      disjointIntervals++;
      job = tempjob;
    }
  }
  return disjointIntervals;
}

/*weighted interval scheduling: max weight of disjoint intervals
  sort in increasing order w.r.t. right endpoints */
int weightedIntervalScheduling(vector<interval> & jobs) {
  sort(jobs.begin(), jobs.end());
  int opt[jobs.size()]; //optimum for first i jobs
  opt[0] = jobs[0].cost;
  for(auto job = jobs.begin(); job != jobs.end(); job++) {
    interval upToThisPoint(job->left,job->left);
    auto it = lower_bound(jobs.begin(), jobs.end(), upToThisPoint);
    int previousIndex;
    if(it == jobs.begin()) { //there is no previous job with which this is compatible
      previousIndex = -1;
    }else { //this job actually ends earlier
      it--;
      previousIndex = it-jobs.begin();
    } 
    if(previousIndex >= 0) {
      opt[i] = max(opt[i-1], jobs[i].cost + opt[previousIndex]);
    }else {
      opt[i] = max(opt[i-1], jobs[i].cost);
    }
  }
  return opt[jobs.size()-1];
}
