# Process Scheduling Simulation

This project, developed for the Data Structures course, simulates process scheduling algorithms, specifically FCFS (First-Come, First-Served) and SJF (Shortest Job First). The program reads a list of processes from an input file, distributes them among multiple simulated computers, and calculates performance metrics such as execution time and waiting time.

## Data Structures Used

The scheduling policies were implemented using the following data structures:

  * **FCFS (First-Come, First-Served):** Implemented with a queue structure (FIFO - First-In, First-Out), where the first process to arrive is the first to be executed. The queue was built using a singly linked list.
  * **SJF (Shortest Job First):** Implemented with a linked list sorted in ascending order based on the CPU execution time (burst time) of each process.

## Features

  * **Multiple Computer Simulation:** The user can specify how many computers will be used in the simulation.
  * **Process Reading:** Processes are read from a `.txt` input file containing information about arrival time and execution times for CPU, disk, and network.
  * **Load Distribution:** Processes and their disk tasks are randomly distributed among the available computers and their disks.
  * **Performance Metrics Calculation:** At the end of the simulation, the program displays:
      * Total and Average Execution Time (Turnaround Time).
      * Total and Average Waiting Time.
      * Throughput.

## Project Structure

The project is organized into the following main files:

  * `main.cpp`: Contains the main simulation logic, file reading, and user interaction.
  * `FCFS.h` / `FCFS.cpp`: Implementation of the Queue (FIFO) data structure.
  * `SJF.h` / `SJF.cpp`: Implementation of the Linked List data structure, with a sorting function for the SJF policy.
  * `NeoLook.h` / `NeoLook.cpp`: Contains the classes that model the simulation components, such as `Process`, `CPU`, `Disk`, and `Computer`.
  * `Node.h`: Node structure used as the basis for the linked lists.

## How to Compile and Run

To compile and run the project, follow the steps below.

### Prerequisites

  * A C++ compiler (such as g++).

### Compilation

1.  Open a terminal in the project's root folder.

2.  Run the following command to compile all `.cpp` files and generate an executable named `main.exe`:

    ```bash
    g++ -std=c++11 *.cpp -o main.exe
    ```

### Execution

1.  After compiling, run the program using the following command:

    ```bash
    ./main.exe <structure> <input_file.txt>
    ```

    **Arguments:**

      * `<structure>`: The scheduling algorithm to be used. Can be `FCFS` or `SJF`.
      * `<input_file.txt>`: The name of the text file containing the list of processes.

    **Usage Example:**

    ```bash
    ./main.exe SJF input_file_1.txt
    ```

2.  The program will prompt you to enter the number of computers to be used in the simulation. Enter the desired number and press Enter.

## Authors

  * **Maria Alice Angelim Facundo**
  * **Yasmin Lima Costa**
