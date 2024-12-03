#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

uint16_t counter(uint32_t* list, uint32_t number,  uint32_t count) {
  if (!list) return 0;

  uint16_t amount = 0;
  for (uint32_t i = 0; i < count; ++i) {
    if (list[i] == number) amount++;
  }

  return amount;
}

int main(int argc, char** argv) {
  
  if (argc < 2) { printf("No input file!\n"); return 1; }
  
  uint64_t final = 0;

  uint32_t list1[1024];
  uint32_t list2[1024];

  // ^^^ ewwww
  
  char* line = NULL;
  ssize_t readsize = 0;
  FILE* infile = fopen(argv[1], "r");

  uint32_t num1, num2;

  uint32_t lines = 0;

  // initialize lists
  while (getline(&line, &readsize, infile) != -1) {
    num1 = strtoul(line, &line, 10);
    num2 = strtoul(line, &line, 10);
    //printf("%u | %u\n", num1, num2);
    list1[lines] = num1;
    list2[lines++] = num2;
    line = NULL;
    readsize = 0;
  }

  printf("lines: %u\n", lines);

  uint32_t count = lines;
  while (lines > 0) {    
    final += (list1[lines] * counter(list2, list1[lines], count));

    --lines;
  }

  printf("final answer: %llu\n", final);

  return 0;
}
