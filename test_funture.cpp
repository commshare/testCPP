//http://deathbytape.com/articles/2015/02/03/cpp-threading.html
/*
More specifically, futures are created through an asynchronous result provider.
 In C++, std::promise, std::packaged_task, and std::async are the interfaces for such providers which all implement a get_future() method that returns the corresponding future. A short summary of the differences between these providers is below:

std::promise. The most flexible way to provide a value for a future. Computation is performed independently from the promise object and the result is simply passed through the object to the future using the set_value() method.
std::packaged_task. The second most flexible way to provide a value for a future. The constructor takes a function and uses the return value of that function to set the value for the future. Since packaged_tasks must be explicitly invoked, they can be created and then assigned to be run on particular threads.
std::async. A high-level utility method to provide a value for a future providing the least flexibility, but also the simplest way to execute an asynchronous computation. The method (note: std::async is not an object like the others, it is a function) takes a function and uses the return value of that function to set the value for the future. The primary distinction between std::async and std::packaged_task is that std::async automatically begins execution upon calling it. Additionally, the caller has no control over where the task is scheduled to run (including on the current thread). 
Finally, there has been some discussion about uncertainty as to when std::async will release its resources.
*/
/**
 * ParallelCompute.cpp
 *
 * Compute a function result in parallel.
 *
 * Author: Dennis J. McWherter, Jr.
 */

#include <chrono>
#include <iostream>
#include <future>
#include <thread>

using namespace std;

int myComputation(int x) {
  for (unsigned i = 0 ; i < 999999999 ; ++i) {
    x++;
  }
  return x;
}

int main() {
  // Create promises
  packaged_task<int(int)> task1(myComputation);
  packaged_task<int(int)> task2(myComputation);

  // Get futures
  future<int> val1 = task1.get_future();
  future<int> val2 = task2.get_future();

  // Schedule promises
  thread t1(move(task1), 0);
  thread t2(move(task2), 5);

  // Print status while we wait
  bool s1 = false, s2 = false;
  do {
    s1 = val1.wait_for(chrono::milliseconds(50)) == future_status::ready;
    s2 = val2.wait_for(chrono::milliseconds(50)) == future_status::ready;
    cout<< "Value 1 is " << (s1 ? "" : "not ") << "ready" << endl;
    cout<< "Value 2 is " << (s2 ? "" : "not ") << "ready" << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
  } while (!s1 || !s2);

  // Cleanup threads-- we could obviously block and wait for our threads to finish if we don't want to print status.
  t1.join();
  t2.join();

  // Final result
  cout<< "Value 1: " << val1.get() << endl;
  cout<< "Value 2: " << val2.get() << endl;
  return 0;
}
