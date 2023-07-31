#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

bool isDeadlock(int processes, int resources, int allocated[MAX_PROCESSES][MAX_RESOURCES],
                int max_claim[MAX_PROCESSES][MAX_RESOURCES], int available[MAX_RESOURCES])
{
  bool finished[MAX_PROCESSES] = {false};
  bool visited[MAX_PROCESSES] = {false};
  int work[MAX_RESOURCES];
  int i, j, k;
  for (i = 0; i < resources; i++)
    work[i] = available[i];

  int count = 0;

  while (count < processes)
  {
    bool can_execute = false;

    for (i = 0; i < processes; i++)
    {
      if (!finished[i])
      {
        bool can_execute = true;

        for (j = 0; j < resources; j++)
        {
          if (max_claim[i][j] - allocated[i][j] > work[j])
          {
            can_execute = false;
            break;
          }
        }

        if (can_execute)
        {
          for (k = 0; k < resources; k++)
            work[k] += allocated[i][k];
          visited[i] = true;
          finished[i] = true;
          count++;
          break;
        }
      }
    }

    if (!can_execute)
      return true;
  }

  return false;
}

int main()
{
  int processes, resources, i, j;

  printf("Enter the number of processes: ");
  scanf("%d", &processes);

  printf("Enter the number of resources: ");
  scanf("%d", &resources);

  int allocated[MAX_PROCESSES][MAX_RESOURCES];
  int max_claim[MAX_PROCESSES][MAX_RESOURCES];
  int available[MAX_RESOURCES];

  printf("Enter the allocation matrix (size %d x %d):\n", processes, resources);
  for (i = 0; i < processes; i++)
  {
    for (j = 0; j < resources; j++)
    {
      scanf("%d", &allocated[i][j]);
    }
  }

  printf("Enter the maximum claim matrix (size %d x %d):\n", processes, resources);
  for (i = 0; i < processes; i++)
  {
    for (j = 0; j < resources; j++)
    {
      scanf("%d", &max_claim[i][j]);
    }
  }

  printf("Enter the available resources vector (size %d):\n", resources);
  for (i = 0; i < resources; i++)
  {
    scanf("%d", &available[i]);
  }

  bool result = isDeadlock(processes, resources, allocated, max_claim, available);

  if (result)
  {
    printf("Deadlock detected!\n");
  }
  else
  {
    printf("No deadlock detected.\n");
  }

  return 0;
}