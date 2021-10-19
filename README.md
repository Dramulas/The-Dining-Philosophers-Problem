# CEN354 Operating Systems - Assignment #3:

# The Dining Philosophers Problem
---
**Assigned: May 12, 2020**

**Due date: June 04, 2020, 23:00**

*Submit through GitHub Classroom. Make sure you start submitting before the deadline. Late submissions will not be accepted.*

In Section 7.1.3, we provide an outline of a solution to the dining-philosophers problem. This project involves implementing a solution to this problem using POSIX mutex locks and condition variables. Solution will be based on the algorithm illustrated in Figure 7.7.

Implementation will require creating five philosophers, each identified by a number 0 . . 4. Each philosopher will run as a separate thread. Philosophers alternate between thinking and eating. To simulate both activities, have each thread sleep for a random period between one and three seconds.

Thread creation using Pthreads is covered in Section 4.4.1. When a philosopher wishes to eat, she invokes the function:

`pickup_forks(int philosopher_number)`

Your implementation will require the use of POSIX condition variables, which are covered in Section 7.3.

Submit your C source code, your `Makefile` and a `.pdf` file as your report. Make sure you add your name and student id at the end of your report.

When you accepted this assignment, you have created a repository as assignment3-your_GitHub_username. Cloning this repository gives you a local copy of your project. After adding your files you can commit the changes.

Reference: Operating System Concepts Tenth Edition, A. Silberschatz, P. B. Galvin, G. Gagne,
Wiley, 2018.
