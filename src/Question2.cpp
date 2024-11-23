#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

// Constants for timing (in milliseconds)
const int TIME_GRABBING_TOOL = 500;
const int TIME_LANDING_PROCESS = 500;
const int TIME_USING_TOOL = 3000;

const int NUM_ROBOTS = 5; // Number of robots and tools
std::vector<std::mutex> tools(NUM_ROBOTS); // Mutexes for tools

void robotTask(int id) {
    // Calculate tool indices
    int leftTool = id;
    int rightTool = (id + 1) % NUM_ROBOTS;

    // Reaching and grabbing the tools
    std::cout << "Robot " << id << " is reaching and grabbing the tools." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(TIME_GRABBING_TOOL));

    // Lock tools in a consistent order
    if (id % 2 == 0) {
        std::lock(tools[leftTool], tools[rightTool]);
        std::lock_guard<std::mutex> lockLeft(tools[leftTool], std::adopt_lock);
        std::lock_guard<std::mutex> lockRight(tools[rightTool], std::adopt_lock);
    } else {
        std::lock(tools[rightTool], tools[leftTool]);
        std::lock_guard<std::mutex> lockRight(tools[rightTool], std::adopt_lock);
        std::lock_guard<std::mutex> lockLeft(tools[leftTool], std::adopt_lock);
    }

    // Acquired tools and performing task
    std::cout << "Robot " << id << " acquired tools and starts performing a task." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(TIME_USING_TOOL));

    // Returning tools
    std::this_thread::sleep_for(std::chrono::milliseconds(TIME_LANDING_PROCESS));
    std::cout << "Robot " << id << " finished the task and returning the tools." << std::endl;
}

int main() {
    // Output timing constants
    std::cout << "TIME_GRABBING_TOOL    " << TIME_GRABBING_TOOL << ";" << std::endl;
    std::cout << "TIME_LANDING_PROCESS  " << TIME_LANDING_PROCESS << ";" << std::endl;
    std::cout << "TIME_USING_TOOL       " << TIME_USING_TOOL << ";" << std::endl;

    std::cout << "################ Question 02 ################" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    // Launch robot threads
    std::vector<std::thread> robots;
    for (int i = 0; i < NUM_ROBOTS; ++i) {
        robots.emplace_back(robotTask, i);
    }

    // Wait for all robots to finish
    for (auto& robot : robots) {
        robot.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Output total duration
    std::cout << "Duration : " << duration.count() << " seconds" << std::endl;
    std::cout << "################ End Question 02 ################" << std::endl;

    return 0;
}

