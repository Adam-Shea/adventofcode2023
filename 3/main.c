#include <stdio.h>
#include <stdlib.h>

// Find numbers in a row
// Return as int
int findNumber(char *schematicPoint) {
  int i = 0;
  while (*(schematicPoint - i) >= '0' && *(schematicPoint - i) <= '9') {
    i++;
  }
  schematicPoint -= i - 1;
  i = 0;
  char serial[4] = {};
  while (*(schematicPoint + i) >= '0' && *(schematicPoint + i) <= '9') {
    serial[i] = *(schematicPoint + i);
    i++;
  }
  return atoi(serial);
}

// Run gears calculation
void calculateGears(char *currentPos, int *partNumbers, char *checkPos,
                    int *gearValues) {
  if (*currentPos == '*') {
    (*partNumbers)++;
    *gearValues *= findNumber(checkPos);
  }
}

int main(void) {
#define MAX_WIDTH 142
#define MAX_HEIGHT 142

  // Grab file
  FILE *file = fopen("inputfile", "r");
  // Line file
  char fileLine[MAX_WIDTH];

  char schematicGrid[MAX_HEIGHT][MAX_WIDTH];

  int total = 0;
  int totalGearValue = 0;

  // Get the file into a 2d array
  int j = 0;
  while (fgets(fileLine, MAX_WIDTH, file)) {
    if (*fileLine) {
      // Loop through line chars
      for (int i = 0; fileLine[i] != '\0'; i++) {
        schematicGrid[j][i] = fileLine[i];
      }
      j++;
    }
  }

  // Loop through 2D array
  for (int y = 0; y < MAX_HEIGHT - 2; y++) {
    for (int x = 0; x < MAX_WIDTH - 2; x++) {
      if (schematicGrid[y][x]) {
        if (schematicGrid[y][x] != '.' &&
            !(schematicGrid[y][x] >= '0' && schematicGrid[y][x] <= '9')) {
          // Number of gear to part attachments
          int partNumbers = 0;
          // Total gear ratios. Set as 1 to allow
          // multiplication
          int gearValues = 1;

          // Define positions for easy access
          char *currentPos = &schematicGrid[y][x];
          char *leftPos = currentPos - 1;
          char *rightPos = currentPos + 1;

          char *upPos = &schematicGrid[y - 1][x];
          char *upLeftPos = upPos - 1;
          char *upRightPos = upPos + 1;

          char *downPos = &schematicGrid[y + 1][x];
          char *downLeftPos = downPos - 1;
          char *downRightPos = downPos + 1;

          // Check left
          if (*leftPos >= '0' && *leftPos <= '9') {
            total += findNumber(leftPos);
            calculateGears(currentPos, &partNumbers, leftPos, &gearValues);
          }

          // Check right
          if (*rightPos >= '0' && *rightPos <= '9') {
            total += findNumber(rightPos);
            calculateGears(currentPos, &partNumbers, rightPos, &gearValues);
          }

          // Check up
          if (*upPos >= '0' && *upPos <= '9') {
            total += findNumber(upPos);
            calculateGears(currentPos, &partNumbers, upPos, &gearValues);
          } else {
            // Check diagonal upleft
            if (*upLeftPos >= '0' && *upLeftPos <= '9') {
              total += findNumber(upLeftPos);
              calculateGears(currentPos, &partNumbers, upLeftPos, &gearValues);
            }
            // Check diagonal upright
            if (*upRightPos >= '0' && *upRightPos <= '9') {
              total += findNumber(upRightPos);
              calculateGears(currentPos, &partNumbers, upRightPos, &gearValues);
            }
          }

          // Check down
          if (*downPos >= '0' && *downPos <= '9') {
            total += findNumber(downPos);
            calculateGears(currentPos, &partNumbers, downPos, &gearValues);
          } else {
            // Check diagonal downleft
            if (*downLeftPos >= '0' && *downLeftPos <= '9') {
              total += findNumber(downLeftPos);
              calculateGears(currentPos, &partNumbers, downLeftPos,
                             &gearValues);
            }
            // Check diagonal downright
            if (*downRightPos >= '0' && *downRightPos <= '9') {
              total += findNumber(downRightPos);
              calculateGears(currentPos, &partNumbers, downRightPos,
                             &gearValues);
            }
          }

          // If there is a valid gear add to total
          if (partNumbers == 2) {
            totalGearValue += gearValues;
          }
        }
      }
    }
  }

  printf("%s", "Sum of part numbers : ");
  printf("%i\n", total);
  printf("%s", "Sum of gear ratios  : ");
  printf("%i\n", totalGearValue);

  return 1;
}
