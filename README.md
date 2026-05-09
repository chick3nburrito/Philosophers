I have learned the basics of threading a process.
And as well how to create threads and explore the use of mutexes

# Philosophers

`philosophers` is a concurrency and synchronization project from the 42 curriculum that simulates the classical Dining Philosophers problem.

The project focuses on designing a correct and efficient multithreaded program where shared resources must be carefully managed to avoid race conditions, deadlocks, and starvation.

## Result

✅ Final Grade: **100/100**

---

# Core Objective

Simulate a group of philosophers who alternate between:
- eating
- thinking
- sleeping

Each philosopher must acquire shared resources (forks) using strict synchronization rules while ensuring no data races or deadlocks occur.

---

# Key Engineering Challenges

This project focuses on real-world systems programming concepts:

- Concurrent execution with threads
- Shared resource management
- Deadlock prevention strategies
- Race condition elimination
- Time-sensitive execution control
- Deterministic behavior under concurrency

---

# Concurrency Model

## Threads

Each philosopher is implemented as an independent thread executing a lifecycle loop.

## Shared Resources

Forks are shared between adjacent philosophers and protected using mutexes.

## Synchronization Strategy

- Mutex locks protect critical sections
- Resource acquisition is carefully ordered
- Timing logic ensures fairness and liveness

---

# Failure Conditions

A philosopher dies if:
- they do not eat within `time_to_die`

The simulation stops when:
- a philosopher dies, or
- all philosophers complete required meals (if specified)

---

# Compilation

```bash
make
```

make clean
```

make fclean
```

Rebuild:

```bash
make re
```

---

# Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```

Example:

```bash
./philo 5 800 200 200
```

With meal limit:

```bash
./philo 5 800 200 200 7
```

---

# Output Behavior

The program logs state transitions in real time:

```text
timestamp 1 is thinking
timestamp 2 has taken a fork
timestamp 3 is eating
timestamp 4 is sleeping
```

---

# Technical Skills Demonstrated

- Multithreading in C (pthread)
- Mutex-based synchronization
- Deadlock avoidance strategies
- Race condition debugging
- High-resolution timing control
- System-level programming
- Concurrent system design

---

# Tech Stack

- C
- pthread (POSIX threads)
- Unix/Linux environment
- GCC
- Makefile

---

# Why This Project Matters

This project reflects core backend and systems engineering concepts used in:
- operating systems
- database engines
- distributed systems
- high-performance servers

---

# Author

Philosophers project completed as part of the 42 Network curriculum.  
Validated with a final score of **100/100**.
