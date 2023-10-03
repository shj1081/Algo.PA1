# Algo.PA1
23-2 Algorithm Project_1


## 1. Objective

Your task is to implement a Min-Max-Median Priority Queue in C. Design a robust data structure that can efficiently find the minimum, maximum, and median integer elements.
When the number of elements is even, the median is defined as the smaller of the two middle elements.

## 2. Required Functions

Implement the following functions:

• void insert(int element): Inserts an integer element into the priority queue.
• int delete min(): Deletes and returns the minimum element.
• int delete max): Deletes and returns the maximum element.
• int delete median(): Deletes and returns the median element.
• int find min(): Fetches but does not remove the minimum element.
• int find max(): Fetches but does not remove the maximum element.

• int find median(): Fetches but does not remove the median element.

## 3. Input Format and Examples

The input consists of a series of operations. The first integer denotes the number of operations to perform (ranging from 1 up to 500,000). Each subsequent line describes an operation, starting with a character indicating the operation type (I for insert, D for
delete, F for find) followed by a character specifying the target (M for min, X for max, E for median), and if inserting, the integer to insert.
