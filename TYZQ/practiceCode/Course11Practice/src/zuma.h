#ifndef ZUMA_H
#define ZUMA_H

struct Node
{
  char color;
  struct Node *next;
};

int countBalls(const struct Node *head);
void printChain(const struct Node *head);
void freeList(struct Node **headPtr);
int insertBall(struct Node **headPtr, int position, char color);
int resolveMatches(struct Node **headPtr);
char randomColor(void);

#endif /* ZUMA_H */
