#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {

  uint16_t final = 0;

  if (argc < 2) { printf("No input file!\n"); return 1; }

  char* line = NULL;
  ssize_t readsize = 0;
  FILE* infile = fopen(argv[1], "r");

  uint8_t bad = 0;

  uint8_t inc = 0, dec = 0;

  while (getline(&line, &readsize, infile) != -1) {

    //printf("%s", line);
    int32_t temp = strtol(line, &line, 10);
    while (*line != '\n') {
      int32_t new = strtol(line, &line, 10);
      int32_t diff = temp - new;
      if (!(inc && dec)) {
        if (diff < 0) inc = 1; else dec = 1;
      }
      if ((diff == 0) || (inc && (diff < -3 || diff > 0)) || (dec && (diff > 3 || diff < 0))) {
        bad = 1;
        break;
      }
      else temp = new;
    }
    
    //printf("bad: %hhu\n\n", bad);

    if (!bad) ++final;
    bad = 0;

    inc = 0;
    dec = 0;
    
    line = NULL;
    readsize = 0;

  }

  printf("final: %hu\n", final);

  return 0;

}
