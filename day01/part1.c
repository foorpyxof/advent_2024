#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

uint32_t smallest(uint32_t* list, uint32_t count) {
  if (!list) return 0;

  uint32_t index = 0;
  for (uint32_t i = 1; i < count; ++i) {
    if (list[i] < list[index]) index = i;
  }

  uint32_t toReturn = list[index];
  list[index] = UINT_MAX;
  return toReturn;
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
    uint32_t smallest1, smallest2;
    
    smallest1 = smallest(list1, count);
    smallest2 = smallest(list2, count);

    final += ((smallest1 > smallest2) ? (smallest1 - smallest2) : (smallest2 - smallest1));

    --lines;
  }

  printf("final answer: %llu\n", final);

  return 0;
}
