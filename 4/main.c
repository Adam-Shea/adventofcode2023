#include "stdio.h"

#define CARDS 197
#define WINNINGNUMBERS 10
#define YOURNUMBERS 25

int main(void) {
  // Grab file
  FILE *file = fopen("inputfile", "r");
  // Line file
  char fileLine[1000000];
  // Totals
  int totalPoints = 0;
  int totalMatches = 0;

  int winningNumberCards[CARDS][WINNINGNUMBERS];
  int yourNumberCards[CARDS][YOURNUMBERS];
  int cardMultipliers[CARDS];

  for (int a = 0; a < CARDS; a++) {
    cardMultipliers[a] = 1;
  }

  // For every line
  int cardCount = 0;
  while (fgets(fileLine, 1000000, file)) {
    // Get game number from line
    char cardNumber[4];
    char *caretPos = &fileLine[5];
    char *startPos = &fileLine[0];

    // Loop through to the colon
    // We need to get the colon pos and
    // get the card number whilst we are at it
    while (*caretPos != ':') {
      cardNumber[(caretPos - startPos) - 5] = *caretPos;
      caretPos++;
    }
    // Move past colon
    caretPos += 2;

    // Parse the winning numbers into array
    int winningNumberPos = 0;
    while (*caretPos != '|') {
      if (*caretPos == ' ' && *(caretPos - 1) != ' ') {
        if (*(caretPos - 2) != ' ') {
          winningNumberCards[cardCount][winningNumberPos] =
              WINNINGNUMBERS * (*(caretPos - 2) - '0');
        } else {
          winningNumberCards[cardCount][winningNumberPos] = 0;
        }
        winningNumberCards[cardCount][winningNumberPos] +=
            *(caretPos - 1) - '0';
        winningNumberPos++;
      }
      caretPos++;
    }

    // Move past '|'
    caretPos += 2;

    // Parse your numbers into array
    int yourNumbersPosition = 0;
    while (*caretPos != '\0') {
      if ((*caretPos == ' ' && *(caretPos - 1) != ' ') ||
          *(caretPos + 1) == '\0') {
        if (*(caretPos - 2) != ' ') {
          yourNumberCards[cardCount][yourNumbersPosition] =
              WINNINGNUMBERS * (*(caretPos - 2) - '0');
        } else {
          yourNumberCards[cardCount][yourNumbersPosition] = 0;
        }
        yourNumberCards[cardCount][yourNumbersPosition] +=
            *(caretPos - 1) - '0';
        yourNumbersPosition++;
      }
      caretPos++;
    }
    cardCount++;
  }

  // Loop through 2d array of cards and
  // tally up card points
  for (int a = 0; a < CARDS; a++) {
    int cardPoints = 0;
    int cardMatches = 0;
    for (int i = 0; i < YOURNUMBERS; i++) {
      for (int g = 0; g < WINNINGNUMBERS; g++) {
        if (yourNumberCards[a][i] == winningNumberCards[a][g]) {
          cardMatches++;
          if (cardPoints == 0)
            cardPoints++;
          else {
            cardPoints *= 2;
          }
        }
      }
    }

    // Calculate all new cards using multiplier
    if (cardMatches > 0) {
      int multiplier = cardMultipliers[a];
      for (int i = 1; i <= cardMatches; i++) {
        if (a + i < CARDS) {
          cardMultipliers[i + a] += 1 * multiplier;
        } else {
          cardMultipliers[i + a] = 1;
        }
      }
    }
    totalPoints += cardPoints;
  }

  // Now do it again recursivly
  for (int a = 0; a < CARDS; a++) {
    totalMatches += cardMultipliers[a];
  }

  printf("%s", "Total Points  : ");
  printf("%i\n", totalPoints);

  printf("%s", "Total Matches : ");
  printf("%i\n", totalMatches);
  return 1;
}
