#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#include "token.h"

token readToken(FILE* openFileStream) {
  token t = defaultToken;

  char nextCharacter;
  int index = 0;
  bool inQuotes = false;
  bool continueToken = true;

  void stopReading() {
    continueToken = false;
    t.content[index] = '\0';
  }

  while (continueToken) {
    nextCharacter = fgetc(openFileStream);

    switch (nextCharacter) {

      case EOF:
        assert(inQuotes == false);
        stopReading();
        break;

      case '\n':
        assert(inQuotes == false);
        stopReading();
        break;

      case '"':
        inQuotes = !inQuotes;
        break;

      case ' ':
        if (inQuotes) {
          t.content[index] = nextCharacter;
          index++;
        }
        else {
          stopReading();
        }
        break;

      default:
        t.content[index] = nextCharacter;
        index++;
        break;
    }
  }

  return t;
}
