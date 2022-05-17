#include <atomic>
#include <mutex>
#include <benchmark/benchmark.h>


class spinlock_mutex{
public:
    spinlock_mutex():flag(ATOMIC_FLAG_INIT){};
    ~spinlock_mutex() = default;
    void lock(){
        while(flag.test_and_set(std::memory_order_acquire)){};
    }

    void unlock(){
        flag.clear(std::memory_order_release);
    }
private:
    std::atomic_flag flag;
};

static void mutex_add(benchmark::State& state) {
  long sum = 0;
  std::mutex mu;
  for (auto _ : state) {
      std::lock_guard<std::mutex> lg(mu);
      sum++;
  }
}

static void atomic_add(benchmark::State& state) {
  std::atomic<long> sum = {0};
  for (auto _ : state) {
      sum++;
  }
}


BENCHMARK(mutex_add);
BENCHMARK(atomic_add);

BENCHMARK_MAIN();