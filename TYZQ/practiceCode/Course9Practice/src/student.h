#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 20
#define NAME_SIZE 24
#define SUBJECT_COUNT 3

/* ===== Data Model ===== */

struct Student {
  int id;
  char name[NAME_SIZE];
  int scores[SUBJECT_COUNT];
};

/* Display */

void printStudent(const struct Student *student);
void printAll(const struct Student students[], int count);

/* Search */
int findById(const struct Student students[], int count, int id);

int findByName(const struct Student students[], int count, const char name[]);

/* Statistics */

void calculateStats(const struct Student *student, int *total, double *average,
                    int *maximum, int *minimum);

/* Student Management */

int addStudent(struct Student students[], int *count,
               const struct Student *newStudent);

#endif /* STUDENT_H */
