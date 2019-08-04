#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void SiftDown(int start_index) {
    int le_children_index = start_index*2 + 1;
    int ri_children_index = start_index*2 + 2;

    while(le_children_index < data_.size()){ // has at least one children
      if (ri_children_index >= data_.size()){
        if(data_[start_index] < data_[le_children_index])
          break;
      }
      else{
        if(data_[start_index] < data_[le_children_index] && data_[start_index] < data_[ri_children_index]){
          break;
        }
      }
      if(ri_children_index < data_.size()){
        if (data_[le_children_index] < data_[ri_children_index]){
          swap(data_[le_children_index], data_[start_index]);
          swaps_.push_back(make_pair(start_index, le_children_index));
          start_index = le_children_index;
        }
        else{
          swap(data_[ri_children_index], data_[start_index]);
          swaps_.push_back(make_pair(start_index, ri_children_index));
          start_index = ri_children_index;
        }
      }
      else{
        swap(data_[le_children_index], data_[start_index]);
        swaps_.push_back(make_pair(start_index, le_children_index));
        start_index = le_children_index;
      }
      le_children_index = start_index*2 + 1;
      ri_children_index = start_index*2 + 2;
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap,
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
/*    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }*/

    // Own implementation
    for(int i = data_.size()/2-1; i >=0; --i){
      int le_children_index = i*2 + 1;
      int ri_children_index = i*2 + 2;
      if(data_[i] > data_[le_children_index] || (data_[i] > data_[ri_children_index] && ri_children_index<data_.size())){
        SiftDown(i);
      }
    }

  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
