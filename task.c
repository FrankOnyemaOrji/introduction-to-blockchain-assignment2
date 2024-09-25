#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>


#define MAX_TASKS 100
#define MAX_DESCRIPTION_LENGTH 256

typedef enum { PENDING, IN_PROGRESS, COMPLETED } TaskStatus;

typedef struct {
    int task_id;
    char description[MAX_DESCRIPTION_LENGTH];
    TaskStatus status;
    unsigned char hash[SHA256_DIGEST_LENGTH];
} Task;

//Global array to store tasks.
Task tasks[MAX_TASKS];
int task_count = 0;

//Function to calculate/compute the SHA-256 hash.
void calculate_hash(Task *task)
{
	unsigned char data[512];
    sprintf((char *)data, "%d%s%d", task->task_id, task->description, task->status);

    
    SHA256(data, strlen((char *)data), task->hash);

    
    printf("Computed hash for Task ID %d: ", task->task_id);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", task->hash[i]);
    }
    printf("\n");
}

//Function to verify if the task's current data matches stored hash.
int verify_task(Task *task)
{
	unsigned char recalculated_hash[SHA256_DIGEST_LENGTH];
    unsigned char data[512];
    sprintf((char *)data, "%d%s%d", task->task_id, task->description, task->status);
    SHA256(data, strlen((char *)data), recalculated_hash);

    // Print both the recalculated and stored hash for debugging
    printf("Recalculated hash for Task ID %d: ", task->task_id);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", recalculated_hash[i]);
    }
    printf("\n");

    printf("Stored hash for Task ID %d: ", task->task_id);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", task->hash[i]);
    }
    printf("\n");

    return memcmp(recalculated_hash, task->hash, SHA256_DIGEST_LENGTH) == 0;
}

// Function to add a new task
void add_task(char *description)
{
	if (task_count >= MAX_TASKS)
	{
		printf("Task list is full.\n");
		return;
	}

	Task new_task;
	new_task.task_id = task_count + 1;
	strcpy(new_task.description, description);
	new_task.status = PENDING;
	calculate_hash(&new_task);


	tasks[task_count++] = new_task;
	printf("Task added successfully.\n");
}

// Function to update a task's status
void update_task_status(int id, TaskStatus status)
{
	if (id <= 0 || id > task_count)
	{
		printf("Invalid task ID.\n");
		return;
	}

	tasks[id - 1].status = status;
	calculate_hash(&tasks[id - 1]);
	printf("Task status updated!.\n");
}

// Function to delete a task
void delete_task(int id)
{
	if (id <= 0 || id > task_count)
	{
		printf("Invalid task ID.\n");
		return;
	}

	for (int i = id - 1; i < task_count - 1; i++)
	{
		tasks[i] = tasks[i + 1];
		calculate_hash(&tasks[i]);
	}
	task_count--;
	printf("Task deleted successfully!. \n");
}


// Function to list all tasks
void list_tasks()
{
	if (task_count == 0) {
        printf("You have no task yet.\n");
        return;
    }

	for (int i = 0; i < task_count; i++)
	{
		printf("ID: %d, Description: %s, Status: %d\n", tasks[i].task_id, tasks[i].description, tasks[i].status);
	}
}

//Function to link task and calculate the hashs in a chain-like manner
void link_tasks()
{
	for (int i = 1; i < task_count; i++)
	{
		unsigned char data[1024];
		sprintf((char *)data, "%d%s%d", tasks[i].task_id, tasks[i].description, tasks[i].status);
		memcpy(data + strlen((char *)data), tasks[i - 1].hash, SHA256_DIGEST_LENGTH);

		SHA256(data, strlen((char *)data), tasks[i].hash);
	}
}

// Function to check the integrity of all tasks
void integrity_check() {
    int tampered = 0;
    for (int i = 0; i < task_count; i++) {
        if (!verify_task(&tasks[i])) {
            printf("Task ID %d has been tampered with!\n", tasks[i].task_id);
            tampered = 1;
        }
    }
    if (!tampered) {
        printf("All tasks are intact.\n");
    }
}

// Program Menu to interact with task system
void menu()
{
	int choice, id;
	char desc[256];

	while (1)
	{
		printf("\n1. Add Task\n2. Update Task\n3. Delete Task\n4. List Tasks\n5. Check Integrity\n6. Exit\nChoose: ");
		scanf("%d", &choice);

		switch (choice)
		{
			case 1:
				printf("Enter task description: ");
				scanf(" %[^\n]s", desc);
				add_task(desc);
				break;
			case 2:
				 printf("Enter task ID to update: ");
				 scanf("%d", &id);
				 printf("Choose Status (0: PENDING, 1: IN PROGRESS, 2: COMPLETED): ");
				 int status;
				 scanf("%d", &status);
				 update_task_status(id, (TaskStatus)status);
				 break;
			case 3:
				 printf("Enter task ID to delete: ");
				 scanf("%d", &id);
				 delete_task(id);
				 break;
			case 4:
				 list_tasks();
				 break;
			case 5:
				 integrity_check();
				 break;
			case 6:
				 return;
			default:
				 printf("Invalid choice.\n");
		}
	}
}


// Main function to start program
int main()
{
	menu();
	return 0;
}

