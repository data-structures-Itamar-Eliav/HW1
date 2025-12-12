// C++
#pragma once
#include <chrono>
#include <iostream>
#include <iomanip>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

struct ProfileRecord {
    long long total_ns = 0;
    long long calls = 0;
};

inline std::unordered_map<std::string, ProfileRecord> g_prof_map;
inline std::mutex g_prof_mutex;

class ScopedProfile {
public:
    explicit ScopedProfile(const char* name) : name_(name),
        start_(std::chrono::steady_clock::now()) {}
    ~ScopedProfile() {
        auto end = std::chrono::steady_clock::now();
        long long ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start_).count();
        std::lock_guard<std::mutex> lock(g_prof_mutex);
        auto &r = g_prof_map[name_];
        r.total_ns += ns;
        r.calls += 1;
    }
private:
    std::string name_;
    std::chrono::steady_clock::time_point start_;
};

#define PROFILE_SCOPE(name) ScopedProfile _scoped_profile_##__LINE__ (name)
#define PROFILE_FUNC() PROFILE_SCOPE(__FUNCTION__)

inline void print_profile_report() {
    std::lock_guard<std::mutex> lock(g_prof_mutex);
    std::vector<std::pair<std::string, ProfileRecord>> vec;
    vec.reserve(g_prof_map.size());
    for (auto &p : g_prof_map) vec.emplace_back(p.first, p.second);
    std::sort(vec.begin(), vec.end(),
              [](auto &a, auto &b){ return a.second.total_ns > b.second.total_ns; });
    std::cout << "\n=== PROFILE REPORT ===\n";
    std::cout << std::left << std::setw(40) << "function"
              << std::right << std::setw(12) << "total ms"
              << std::setw(12) << "calls"
              << std::setw(12) << "avg ms\n";
    for (auto &p : vec) {
        double total_ms = p.second.total_ns / 1e6;
        double avg_ms = (p.second.calls ? total_ms / p.second.calls : 0.0);
        std::cout << std::left << std::setw(40) << p.first
                  << std::right << std::setw(12) << std::fixed << std::setprecision(3) << total_ms
                  << std::setw(12) << p.second.calls
                  << std::setw(12) << std::fixed << std::setprecision(3) << avg_ms
                  << "\n";
    }
    std::cout << "======================\n";
}

inline struct AutoPrint {
    ~AutoPrint(){ print_profile_report(); }
} _auto_print_profile;
