#include "input.h"
#include "zuma.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INITIAL_BALL_COUNT 6
#define MAX_BALL_COUNT 15

static int readPosition(int count, int *position)
{
  while (1)
  {
    printf("Range: %d ~ %d\nExit: %d\n", 0, count, -1);
    if (readInt("Position: ", position) == 0)
    {
      return 0;
    }
    else if (*position == -1)
    {
      return 0;
    }
    else if (*position >= 0 && *position <= count)
    {
      return 1;
    }
    else
    {
      printf("Invalid position..\n");
    }
  }
}

int main(void)
{
  struct Node *head = NULL;
  char last1 = '\0';
  char last2 = '\0';
  srand((unsigned int)time(NULL));

  for (int i = 0; i < INITIAL_BALL_COUNT; i++)
  {
    char color = randomColor();
    while (i >= 2 && color == last1 && color == last2)
    {
      color = randomColor();
    }

    if (insertBall(&head, i, color) != 1)
    {
      printf("Failed to initialize.\n");
      freeList(&head);
      return 1;
    };

    last2 = last1;
    last1 = color;
  }

  int turn = 1;
  int count = countBalls(head);

  while (1)
  {
    int deleteCount = 0;
    int position = 0;
    char nextColor = randomColor();

    printChain(head);
    printf("Round: %d\n", turn);
    printf("Balls: %d\n", count);
    printf("Maximum: %d\n", MAX_BALL_COUNT);
    printf("Color: %c\n", nextColor);

    if (readPosition(count, &position) == 0)
    {
      printf("Goodbye\n");
      break;
      ;
    }

    if (insertBall(&head, position, nextColor) != 1)
    {
      printf("An error occurs.\n");
      freeList(&head);
      return 1;
    }

    deleteCount = resolveMatches(&head);
    count = countBalls(head);

    printf("Count: %d\n", count);
    printf("Removed: %d\n", deleteCount);

    if (count == 0)
    {
      printf("YOU WIN!\n");
      printChain(head);
      break;
    }
    else if (count > MAX_BALL_COUNT)
    {
      printf("YOU LOSE!\n");
      printChain(head);
      break;
    }

    turn++;
  }

  freeList(&head);
  return 0;
}
