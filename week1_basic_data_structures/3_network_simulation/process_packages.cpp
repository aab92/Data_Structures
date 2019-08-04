#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>

#define DEBUG ;

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {}

    void clear( std::queue<int> &q )
    {
     std::queue<int> empty;
     std::swap( q, empty );
    }

    Response Process(const Request &request) {
        // write your code here
        Response response(false,0);
        if(!finish_time_.empty() && finish_time_.back()<=request.arrival_time){
          clear(finish_time_);
        }

        if(finish_time_.empty()){
          finish_time_.push(request.arrival_time+request.process_time);
          response.start_time = request.arrival_time;
          return response;
        }

        for(int i=0; i< finish_time_.size(); ++i){
          if(finish_time_.front()<=request.arrival_time){
            finish_time_.pop();
          }
        }

        if(finish_time_.size()>=size_){
          response.dropped = true;
          return response;
        }
        int starting_time;
        if(!finish_time_.empty())
          starting_time = finish_time_.back();
        else
          starting_time = request.arrival_time;
        finish_time_.push(starting_time+request.process_time);
        response.start_time = starting_time;
        return response;
    }
private:
    int size_;
    std::queue <int> finish_time_;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

void PrintResponsesToFile(const std::vector <Response> &responses) {
    std::ofstream myfile;
    myfile.open ("result.txt");
    for (int i = 0; i < responses.size(); ++i)
        myfile << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
    myfile.close();
}

std::vector <Request> ReadRequestsFromFile(std::ifstream& testfile, const int count) {
    std::vector <Request> requests;
    std::string line;
    if (testfile.is_open()){
      while( std::getline(testfile, line) ) {
        std::istringstream iss(line);
        std::vector<std::string> v(std::istream_iterator<std::string>{iss},
                                   std::istream_iterator<std::string>());

        int arrival_time = std::stoi(v[0],nullptr);
        int process_time = std::stoi(v[1],nullptr);
        requests.push_back(Request(arrival_time, process_time));
      }
      return requests;
    }
    else
      exit(EXIT_FAILURE);
}

void test_solution(){
  int size;
  int count;
  std::ifstream testfile("tests/22");
  std::string line;
  if (testfile.is_open()){
    std::getline(testfile,line);
  }
  std::istringstream iss(line);
  std::vector<std::string> v(std::istream_iterator<std::string>{iss},
                             std::istream_iterator<std::string>());
  if (v.size()==2){
    size = std::stoi(v[0],nullptr);
    count = std::stoi(v[1],nullptr);
  }
  else{
    testfile.close();
    exit(EXIT_FAILURE);
  }
  std::vector <Request> requests = ReadRequestsFromFile(testfile, count);
  testfile.close();

  Buffer buffer(size);
  std::vector <Response> responses = ProcessRequests(requests, &buffer);

  PrintResponsesToFile(responses);
  return;

}

int main() {
#ifdef DEBUG
    test_solution();
#else
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
#endif
}
