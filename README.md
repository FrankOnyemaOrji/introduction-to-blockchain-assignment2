# To-Do List with Blockchain-like Features

This C program simulates a to-do list application that mimics how data is managed in a blockchain system. The tasks are stored with cryptographic hashes, ensuring data integrity and immutability, similar to how tasks would be handled if stored on the Ethereum blockchain.

## Features
- **Add Task**: Add a new task with a description and a default status of "Pending." Each task is assigned a unique ID and is hashed using SHA-256 to ensure data integrity.
- **Update Task Status**: Update the status of a task (e.g., from "Pending" to "In Progress" or "Completed"). When a task is updated, its hash is recalculated to reflect the changes, ensuring that any tampering can be detected.
- **Delete Task**: Delete a task by its ID. All subsequent tasks are rehashed to maintain the integrity of the blockchain-like structure.
- **List Tasks**: View all tasks, including their description, status, and hash values.
- **Integrity Check**: Verify the integrity of the task list. If any task's hash does not match its recalculated hash, it is flagged as potentially tampered with.
- **Blockchain-like Structure**: The hash of each task is influenced by the hash of the previous task, creating a linked chain of tasks that simulates blockchain immutability.

## Blockchain-like Features
This program simulates a blockchain by:
- **Cryptographic Hashing**: Each task has a unique hash generated using the SHA-256 algorithm. This hash is stored along with the task data to ensure its integrity.

- **Hash Chain**: The hash of each task is linked to the hash of the previous task, similar to how blocks in a blockchain are linked together. This ensures that altering a task would break the chain, helping detect tampering.

- **Data Immutability**: Once a task is added, its integrity is maintained using the stored hash. Any unauthorized modifications to the task will be detected when the hash is recalculated and compared to the stored hash.

## Prerequisites
- **OpenSSL**: This program uses the OpenSSL library for cryptographic hashing (SHA-256). Make sure OpenSSL is installed on your system.
  - On Linux:
    ```bash
    sudo apt-get install libssl-dev
    ```

## How to Compile and Run

### 1. Clone or Download the Project

If you're cloning the repository or have downloaded the project files, navigate to the project directory.

### 2. Compile the Program

Use the following command to compile the program. Ensure that you link OpenSSL to handle the cryptographic functions:

```bash
gcc -o todo_list todo_list.c -lssl -lcrypto
```

### 3. Run the Program

After compiling, you can run the program by typing:

```bash
./todo_list
```

### 4. Interaction

Once the program is running, you will be presented with a menu-driven interface with the following options:

1. **Add Task**: Enter a description to add a new task. The task will be stored with a unique ID and hashed to ensure integrity.

2. **Update Task**: Select a task by its ID and update its status (e.g., "Pending," "In Progress," "Completed"). The task’s hash will be recalculated, and the blockchain chain will be updated.

3. **Delete Task**: Remove a task by its ID. All subsequent tasks will be rehashed to maintain blockchain consistency.

4. **List Tasks**: Display all tasks with their details (ID, description, status, and hash).

5. **Check Integrity**: Verify the integrity of the task list by recalculating hashes and checking for mismatches. If tampering is detected, the task will be flagged.

6. **Exit**: Exit the program.

### 5. Example Interaction

```text
1. Add Task
2. Update Task
3. Delete Task
4. List Tasks
5. Check Integrity
6. Exit
Choose: 1

Enter task description: "Complete assignment"
Task added successfully.

1. Add Task
2. Update Task
3. Delete Task
4. List Tasks
5. Check Integrity
6. Exit
Choose: 4

ID: 1, Description: Complete assignment, Status: Pending, Hash: [task_hash_here]
```

### 6. Error Handling
The program handles the following errors:

- **Task List Full**: If the task list reaches its maximum size, an error message will appear.

- **Invalid Task ID**: If an invalid task ID is entered for updating or deleting, an error message will be shown.

- **Memory or Hashing Errors**: If there are any issues with memory allocation or hash calculation, appropriate error messages will be displayed.

## Additional Notes
- The maximum number of tasks is currently set to 100, but this can be adjusted in the code.

- The integrity check is an important feature that detects any tampering with the task data. If any task’s data is altered outside of the program, its hash will no longer match, and the program will flag this during the integrity check.

- The linking of tasks through their hashes simulates a simplified version of how blockchains work in real-world systems like Ethereum.