
# Answer for question6

Developing the program for Question 03 may encounter issues like race conditions, deadlocks, and resource contention. When actions such as waking up the ATC or checking the traffic pattern take time to complete, delays can lead to bottlenecks, causing other aircraft to wait indefinitely. This could result in starvation, where some aircraft are never granted permission to land, or deadlock, where no aircraft can proceed due to circular waiting.

Potential Solution: To address these issues, the program can use condition variables to efficiently manage waiting pilots and ATC personnel, ensuring actions proceed in an orderly manner. Mutexes should be used to protect shared resources, such as the traffic pattern state. A timeout mechanism can also be implemented for actions like waiting for the ATC to wake up, allowing aircraft to divert if the wait exceeds a certain threshold, thereby avoiding indefinite delays.
