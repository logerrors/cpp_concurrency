#include <map>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <chrono>
#include <benchmark/benchmark.h>

using namespace std::chrono_literals;

class dns_entry
{};

class dns_cache1
{
    std::map<std::string,dns_entry> entries;
    std::shared_mutex entry_mutex;
public:
    dns_entry find_entry(std::string const& domain)
    {
        std::shared_lock<std::shared_mutex> lk(entry_mutex);
        std::map<std::string,dns_entry>::const_iterator const it=
            entries.find(domain);
        return (it==entries.end())?dns_entry():it->second;
    }
    void update_or_add_entry(std::string const& domain,
                             dns_entry const& dns_details)
    {
        std::unique_lock<std::shared_mutex> lk(entry_mutex);
        entries[domain]=dns_details;
    }
};

class dns_cache2
{
    std::map<std::string,dns_entry> entries;
    std::mutex entry_mutex;
public:
    dns_entry find_entry(std::string const& domain)
    {
        std::lock_guard<std::mutex> lk(entry_mutex);
        std::map<std::string,dns_entry>::const_iterator const it=
            entries.find(domain);
        return (it==entries.end())?dns_entry():it->second;
    }
    void update_or_add_entry(std::string const& domain,
                             dns_entry const& dns_details)
    {
        std::lock_guard<std::mutex> lk(entry_mutex);
        entries[domain]=dns_details;
    }
};

static void mutex_bench(benchmark::State& state) {
  // Perform setup here
  dns_cache1 dc;
  long i = 0;
  for (auto _ : state) {
    if(i % 10 == 0){
        dns_entry de;
        dc.update_or_add_entry(std::to_string(i), de);
    }else{
        dc.find_entry(std::to_string(i));
    }
  }
}

static void share_mutex_bench(benchmark::State& state) {
  // Perform setup here
  dns_cache2 dc;
  long i = 0;
  for (auto _ : state) {
    if(i % 10 == 0){
        dns_entry de;
        dc.update_or_add_entry(std::to_string(i), de);
    }else{
        dc.find_entry(std::to_string(i));
    }
  }
}

BENCHMARK(mutex_bench);
BENCHMARK(share_mutex_bench);

BENCHMARK_MAIN();





