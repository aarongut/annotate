#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define PRINT_BUF_SIZE 1280

void print_now() {
  time_t now;
  time(&now);

  struct tm *time_parts = localtime(&now);

  printf("[%d-%02d-%02d %02d:%02d:%02d] ",
      time_parts->tm_year + 1900,
      time_parts->tm_mon + 1,
      time_parts->tm_mday,
      time_parts->tm_hour,
      time_parts->tm_min,
      time_parts->tm_sec);
}

/**
 * Program that reads from STDIN and writes to STDOUT with each line annotated
 * with the current date and time
 */
int main() {
  char buffer[BUF_SIZE];


  // when true, print the time on the next iteration
  // allows us to avoid printing after the last newline
  bool output_time = true;

  ssize_t count_read;
  while ((count_read = read(STDIN_FILENO, buffer, BUF_SIZE))) {
    for (ssize_t i=0; i < count_read; i++) {
      if (output_time && !feof(stdin)) {
        print_now();
        output_time = false;
      }

      if (buffer[i] == '\n') {
        printf("\n");
        fflush(stdout);
        output_time = true;
      } else {
        fputc(buffer[i], stdout);
      }
    }
  }

  if (count_read < 0) {
    perror("Error reading from stdin");
    return 1;
  }

  fflush(stdout);

  return 0;
}
