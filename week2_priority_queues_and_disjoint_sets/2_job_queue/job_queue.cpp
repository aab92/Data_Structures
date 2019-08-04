#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;

class Worker{
  private:
    int worker_id;
    long long working_time;

  public:
    Worker(int id){
      worker_id = id;
      working_time = 0;
    }

    void add_time(int time){
      working_time += (long long)time;
    }

    long long get_working_time(){
      long long result = working_time;
      return result;
    }

    int get_worker_id(){
      int result = worker_id;
      return result;
    }

};

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  // Sifts down the root of the heap
  void SiftDown(vector<Worker>& thread) {
    int start_index = 0;
    int le_children_index = start_index*2 + 1;
    int ri_children_index = start_index*2 + 2;

    while(le_children_index < thread.size()){ // has at least one children
      if(thread[start_index].get_working_time() >= thread[le_children_index].get_working_time() || (thread[start_index].get_working_time() >= thread[ri_children_index].get_working_time() && ri_children_index < thread.size()) ){
        if(ri_children_index < thread.size()){
          if (thread[le_children_index].get_working_time() == thread[ri_children_index].get_working_time()){
            if(thread[le_children_index].get_worker_id() < thread[ri_children_index].get_worker_id()){
              swap(thread[le_children_index], thread[start_index]);
              start_index = le_children_index;
            }
            else{
              swap(thread[ri_children_index], thread[start_index]);
              start_index = ri_children_index;
            }
          }
          else if (thread[le_children_index].get_working_time() < thread[ri_children_index].get_working_time()){
            swap(thread[le_children_index], thread[start_index]);
            start_index = le_children_index;
          }
          else{
            if (thread[start_index].get_working_time() == thread[ri_children_index].get_working_time()){
              if(thread[ri_children_index].get_worker_id() < thread[start_index].get_worker_id()){
                swap(thread[ri_children_index], thread[start_index]);
                start_index = ri_children_index;
              }
              else{
                break;
              }
            }
            else{
              swap(thread[ri_children_index], thread[start_index]);
              start_index = ri_children_index;
            }
          }
        }
        else{
          if (thread[start_index].get_working_time() == thread[le_children_index].get_working_time()){
              if(thread[le_children_index].get_worker_id() < thread[start_index].get_worker_id()){
                swap(thread[le_children_index], thread[start_index]);
                start_index = le_children_index;
              }
              else{
                break;
              }
          }
          else{
            swap(thread[le_children_index], thread[start_index]);
            start_index = le_children_index;
          }
        }
        le_children_index = start_index*2 + 1;
        ri_children_index = start_index*2 + 2;
      }
      else
        break;
    }
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
/*    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }*/

    //Own implementation
    vector<Worker> thread;
    for(int i=0; i<num_workers_; ++i){
      Worker worker(i);
      thread.push_back(worker);
    }

    for(int i=0; i<jobs_.size(); ++i){
      assigned_workers_[i] = thread[0].get_worker_id();
      start_times_[i] = thread[0].get_working_time();
      thread[0].add_time(jobs_[i]);
      SiftDown(thread);
    }

  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
