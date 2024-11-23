
# Answer for question5

Assigning a new task immediately after finishing could lead to resource contention, similar to the Dining Philosophers Problem. Multiple robots may need access to shared tools, and if a robot doesn't release them in time, it can cause deadlock or starvation, preventing progress. In Question 02, robots sharing tools in a circular setup may hold onto tools, blocking others. Immediate task assignment also risks insufficient time for recharging or maintenance, causing performance issues.

Potential Solution: To prevent these issues, a short delay between tasks allows robots to release resources and reset. A priority-based allocation strategy and mutexes can manage shared tools to prevent conflicts. Monitoring systems can ensure robots are charged and in good condition, while threads and condition variables help coordinate actions smoothly.
