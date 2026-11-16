#include "zuma.h"
#include <assert.h>
#include <stdio.h>

static void assert_chain(const struct Node *head, const char *expected)
{
  const struct Node *temp = head;
  for (int i = 0; expected[i] != '\0'; i++)
  {
    assert(temp != NULL);
    assert(temp->color == expected[i]);
    temp = temp->next;
  }
  assert(temp == NULL);
}

static void test_resolve_case(const char *input, const char *expected,
                              int expectedRemoved)
{
  struct Node *head = NULL;

  for (int i = 0; input[i] != '\0'; i++)
  {
    int result = insertBall(&head, i, input[i]);
    if (result != 1)
    {
      freeList(&head);
      assert(result == 1);
      return;
    }
  }

  assert(expectedRemoved == resolveMatches(&head));
  assert_chain(head, expected);

  freeList(&head);
  assert(head == NULL);
  freeList(&head);
  assert(head == NULL);
}

static void test_chain_reaction(void)
{
  struct Node *head = NULL;
  const char *colors = "RRGGGR";

  for (int i = 0; i < 6; i++)
  {
    int result = insertBall(&head, i, colors[i]);
    if (result != 1)
    {
      freeList(&head);
      assert(result == 1);
      return;
    }
  }

  int deleteCount = resolveMatches(&head);
  assert(deleteCount == 6);
  assert(head == NULL);
}

static void test_insert_positions(void)
{
  struct Node *head = NULL;
  int result;
  result = insertBall(&head, 0, 'B');

  if (result != 1)
  {
    freeList(&head);
    assert(result == 1);
    return;
  }

  result = insertBall(&head, 0, 'R');

  if (result != 1)
  {
    freeList(&head);
    assert(result == 1);
    return;
  }

  result = insertBall(&head, 1, 'G');

  if (result != 1)
  {
    freeList(&head);
    assert(result == 1);
    return;
  }

  result = insertBall(&head, 3, 'R');

  if (result != 1)
  {
    freeList(&head);
    assert(result == 1);
    return;
  }

  assert_chain(head, "RGBR");
  assert(countBalls(head) == 4);

  freeList(&head);
  assert(head == NULL);
}

static void test_invalid_position(void)
{
  struct Node *head = NULL;
  int result;

  result = insertBall(&head, 0, 'R');

  if (result != 1)
  {
    freeList(&head);
    assert(result == 1);
    return;
  }

  result = insertBall(&head, 1, 'G');

  if (result != 1)
  {
    freeList(&head);
    assert(result == 1);
    return;
  }

  struct Node *originHead = head;

  result = insertBall(&head, -1, 'B');

  assert(result == 0);

  result = insertBall(&head, 3, 'B');

  assert(result == 0);
  assert(originHead == head);
  assert_chain(head, "RG");
  freeList(&head);
}

int main(void)
{
  char *input1 = "GGGGB";
  char *input2 = "BRRGGGRB";
  test_chain_reaction();
  test_insert_positions();
  test_invalid_position();
  test_resolve_case(input1, "B", 4);
  test_resolve_case(input2, "BB", 6);
  return 0;
}
