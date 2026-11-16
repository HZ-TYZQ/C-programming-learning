#include "zuma.h"
#include <stdio.h>
#include <stdlib.h>

static struct Node *createNode(char color)
{
  struct Node *newNode = malloc(sizeof(struct Node));

  if (newNode == NULL)
  {
    return NULL;
  }
  else
  {
    newNode->color = color;
    newNode->next = NULL;
    return newNode;
  }
}

int countBalls(const struct Node *head)
{
  const struct Node *p = head;
  int count = 0;

  while (p != NULL)
  {
    count++;
    p = p->next;
  }

  return count;
}

void printChain(const struct Node *head)
{
  const struct Node *p = head;
  while (p != NULL)
  {
    printf("%c ", p->color);
    printf("-> ");
    p = p->next;
  }

  printf("NULL\n");
  return;
}

void freeList(struct Node **headPtr)
{
  while (*headPtr != NULL)
  {
    struct Node *temp = *headPtr;
    *headPtr = (*headPtr)->next;
    free(temp);
  }

  return;
}

int insertBall(struct Node **headPtr, int position, char color)
{
  struct Node **link = headPtr;
  int count = countBalls(*headPtr);
  if (position < 0 || position > count)
  {
    return 0;
  }

  struct Node *newNode = createNode(color);

  if (newNode == NULL)
  {
    return -1;
  }

  for (int i = 0; i < position; i++)
  {
    link = &((*link)->next);
  }

  newNode->next = *link;
  (*link) = newNode;

  return 1;
}

static int eliminateOnce(struct Node **headPtr)
{
  struct Node *start = *headPtr;
  struct Node *after = *headPtr;
  struct Node **link = headPtr;
  int length = 0;

  while (after != NULL)
  {
    start = after;
    length = 0;

    while (after != NULL && start->color == after->color)
    {
      after = after->next;
      length++;
    }

    if (length < 3)
    {
      for (int i = 0; i < length; i++)
      {
        link = &((*link)->next);
      }
    }
    else
    {
      for (int i = 0; i < length; i++)
      {
        struct Node *temp = *link;
        *link = (*link)->next;
        free(temp);
      }
      return length;
    }
  }
  return 0;
}

int resolveMatches(struct Node **headPtr)
{
  int total = 0;
  while (1)
  {
    int removedBalls = eliminateOnce(headPtr);

    if (removedBalls == 0)
    {
      return total;
    }
    else
    {
      total += removedBalls;
    }
  }
}

char randomColor(void)
{
  char colors[3] = {'R', 'G', 'B'};
  int choice = rand() % 3;
  return colors[choice];
}
