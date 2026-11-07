#include <stdio.h>
#define ROWS 2
#define COLS 3

void mirror_matrix(int matrix[][COLS], int mirrored[][COLS], int rows);

int main(void)
{
  int matrix[ROWS][COLS];
  int mirrored[ROWS][COLS];
  // Read the matrix
  for (int row = 0; row < ROWS; row++)
  {
    for (int column = 0; column < COLS; column++)
    {
      scanf("%d", &matrix[row][column]);
    }
  }
  mirror_matrix(matrix, mirrored, ROWS);
  // Print the mirrored matrix
  for (int row = 0; row < ROWS; row++)
  {
    for (int column = 0; column < COLS; column++)
    {
      if (column == 0)
      {
        printf("%d", mirrored[row][column]);
      }
      else
      {
        printf(" %d", mirrored[row][column]);
      }
    }
    printf("\n");
  }

  return 0;
}

void mirror_matrix(int matrix[][COLS], int mirrored[][COLS], int rows)
{
  // Mirror the matrix
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      mirrored[i][j] = matrix[i][COLS - j - 1];
    }
  }
}
