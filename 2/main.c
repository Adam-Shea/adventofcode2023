#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

int main(void) {
  // Grab file
  FILE *file = fopen("inputfile", "r");
  // Line file
  char fileLine[1000000];
  // Totals
  int totalGameNumbers = 0;
  int totalSum = 0;

  // For every line
  while (fgets(fileLine, 1000000, file)) {
    // Get game number from line
    char gameNumber[4];
    int i = 5;

    // Loop through to the colon
    // We need to get the colon pos and
    // get the game number whilst we are at it
    while (fileLine[i] != ':') {
      gameNumber[i - 5] = fileLine[i];
      i++;
    }

    // Skip the colon and the following space
    i += 2;
    // Get all of the colours
    bool invalid = false;
    int smallestRed = 1;
    int smallestGreen = 1;
    int smallestBlue = 1;
    int red = 0;
    int green = 0;
    int blue = 0;
    int currentNumber;

    // Loop through every character
    for (int j = i; fileLine[j] != '\0'; j++) {
      if (fileLine[j] == ';') {
        // If semi
        // Update smallest possible
        if (red > smallestRed) {
          smallestRed = red;
        }
        if (green > smallestGreen) {
          smallestGreen = green;
        }
        if (blue > smallestBlue) {
          smallestBlue = blue;
        }
        // If too large, invalid and break (less looping)
        if (red > 12 || green > 13 || blue > 14) {
          invalid = true;
          // Removed for p2
          /* break; */
        }
        // Reset
        red = 0;
        green = 0;
        blue = 0;
      } else if (fileLine[j] >= '0' && fileLine[j] <= '9') {
        // If the character is number
        // Check to see if double digits
        if (fileLine[j + 1] >= '0' && fileLine[j + 1] <= '9') {
          currentNumber = ((fileLine[j] - '0') * 10) + fileLine[j + 1] - '0';
          j++;
        } else {
          currentNumber = fileLine[j] - '0';
        }
      } else if (fileLine[j] == 'r') {
        // If red
        red += currentNumber;
        j += 2;
      } else if (fileLine[j] == 'g') {
        // If green
        green += currentNumber;
        j += 4;
      } else if (fileLine[j] == 'b') {
        // If blue
        blue += currentNumber;
        j += 3;
      } else {
      }
    }

    // Update smallest possible
    if (red > smallestRed) {
      smallestRed = red;
    }
    if (green > smallestGreen) {
      smallestGreen = green;
    }
    if (blue > smallestBlue) {
      smallestBlue = blue;
    }

    // If too large, invalid
    if (red > 12 || green > 13 || blue > 14) {
      invalid = true;
    }

    // Add total game numbers
    if (invalid != true) {
      totalGameNumbers += atoi(gameNumber);
    }

    // Add sum
    totalSum += smallestRed * smallestBlue * smallestGreen;
  }
  printf("%i\n", totalGameNumbers);
  printf("%i\n", totalSum);
  return 1;
}
