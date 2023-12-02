#include <stdbool.h>
#include <stdio.h>

// Check if the suppied char* is actually a number
int checkIfNumber(char *fileLine) {
  char *numberDefs[] = {"one", "two",   "three", "four", "five",
                        "six", "seven", "eight", "nine"};
  int numberDefsLength = sizeof(numberDefs) / sizeof(numberDefs[0]);

  // Loops through all of our number definitions
  for (int i = 0; i < numberDefsLength; i++) {
    // Have we found a number
    bool isNumber = true;
    // Loop through all future characters to check to see if
    // they are equal to those in *numberDefs[]
    for (int j = 0; numberDefs[i][j] != 0; j++) {
      if (fileLine[j] != numberDefs[i][j]) {
        isNumber = false;
        break;
      }
    }
    // If it's a number return
    if (isNumber) {
      return i + 1;
    }
  }
  return 10;
}

int main(void) {
  // Grab file
  FILE *file = fopen("inputfile", "r");
  // Line file
  char fileLine[100];
  // Total numbers
  int total = 0;

  // For every line
  while (fgets(fileLine, 100, file)) {
    if (*fileLine) {
      // Define first and last number of file
      int i = 0;
      int firstNumber = 10;
      int lastNumber = 10;

      // Loop through line chars
      while (fileLine[i] != '\0') {
        // If char is a number
        if (fileLine[i] >= '0' && fileLine[i] <= '9') {
          lastNumber = fileLine[i];
          if (firstNumber == 10) {
            firstNumber = fileLine[i];
          }
        } else {
          // Else check for number string
          int numberInString = checkIfNumber(&fileLine[i]);
          if (numberInString != 10) {
            lastNumber = numberInString + '0';
            if (firstNumber == 10) {
              firstNumber = numberInString + '0';
            }
          }
        }
        i++;
      }

      // Convert string values to number and add to total
      total += (((firstNumber - '0') * 10) + (lastNumber - '0'));
    }
  }
  printf("%i\n", total);
  return 1;
}
