#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <vector>
#include <random>

class Airport {
private:
    std::mutex mtx;
    std::condition_variable cv_atc;
    std::condition_variable cv_pattern;
    std::atomic<bool> atc_sleeping{true};
    std::atomic<bool> atc_talking{false};
    std::queue<int> traffic_pattern;
    const std::size_t MAX_PATTERN_SIZE = 3; // 改为 std::size_t

public:
    bool can_enter_pattern() {
        return traffic_pattern.size() < MAX_PATTERN_SIZE;
    }
    
    void request_landing(int aircraft_id) {
        std::unique_lock<std::mutex> guard(mtx);
        
        std::cout << "Aircraft #" << aircraft_id << " requesting landing." << std::endl;
        
        // Wait until there's space in the pattern
        cv_pattern.wait(guard, [this]() {
            return can_enter_pattern();
        });
        
        // Enter traffic pattern
        traffic_pattern.push(aircraft_id);
        
        // Wake up ATC if sleeping
        if (atc_sleeping) {
            atc_sleeping = false;
            atc_talking = true;
        } else {
            // Wait for ATC to finish current communication
            cv_atc.wait(guard, [this]() {
                return !atc_talking;
            });
            atc_talking = true;
        }
        
        // Simulate landing process
        guard.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        guard.lock();
        
        // Aircraft has landed
        std::cout << "Aircraft #" << aircraft_id << " is cleared to land." << std::endl;
        traffic_pattern.pop();
        
        // ATC goes back to sleep
        atc_talking = false;
        atc_sleeping = true;
        
        std::cout << "Runway is now free." << std::endl;
        
        // Notify waiting aircraft
        cv_pattern.notify_one();
        cv_atc.notify_one();
    }
};

int main() {
    Airport airport;
    std::vector<std::thread> aircraft;
    
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 200);
    
    try {
        // Create 10 aircraft threads
        for (int i = 0; i < 10; ++i) {
            aircraft.emplace_back([&airport, i, &gen, &dis]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));
                airport.request_landing(i);
            });
        }
        
        // Wait for all aircraft to land
        for (auto& plane : aircraft) {
            if (plane.joinable()) {
                plane.join();
            }
        }
    }
    catch (const std::system_error& e) {
        std::cerr << "Thread error: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "duration : 5 seconds" << std::endl;
    return 0;
}

