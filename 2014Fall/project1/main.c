#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#include "token.h"
#include "readToken.h"

void validateCommandLineArguments(int, char**);
void translateMessage(char*, char*);
int countTokens(char*);
char peak(FILE*);
void readTokens(char*, token*);
void translateTokens(int, token*, int, token*, token*);


int main(int argc, char **argv) {
  validateCommandLineArguments(argc, argv);
  char* dictionaryFilePath = argv[1];
  char* messageFilePath = argv[2];
  translateMessage(dictionaryFilePath, messageFilePath);
  printf("\n");
  return 0;
}

void validateCommandLineArguments(int argc, char **argv) {
  const char *correctFormat = "main ./path-to-dictionary ./path-to-message";
  if (argc != 3) {
    printf("\nProvide dictionary and message files. For example:\n%s\n", correctFormat);
    exit(-1);
  }
}

void translateMessage(char *dictionaryFilePath, char *messageFilePath) {
  const int dictionaryTokenCount = countTokens(dictionaryFilePath);
  const int messageTokenCount = countTokens(messageFilePath);

  token *dictionaryTokens = malloc(dictionaryTokenCount * sizeof(token));
  token *messageTokens = malloc(messageTokenCount * sizeof(token));
  token *translatedMessageTokens = malloc(messageTokenCount * sizeof(token));

  readTokens(dictionaryFilePath, dictionaryTokens);
  readTokens(messageFilePath, messageTokens);
  translateTokens(dictionaryTokenCount, dictionaryTokens, messageTokenCount, messageTokens, translatedMessageTokens);

  printf("\n\ndictionary:\n");
  for (int i=0; i<dictionaryTokenCount; i++) {
    printf("%s ", dictionaryTokens[i].content);
  }

  printf("\n\noriginal message:\n");
  for (int i=0; i<messageTokenCount; i++) {
    printf("%s ", messageTokens[i].content);
  }

  printf("\n\ntranslated message:\n");
  for (int i=0; i<messageTokenCount; i++) {
    printf("%s ", translatedMessageTokens[i].content);
  }

  free(dictionaryTokens);
  free(messageTokens);
  free(translatedMessageTokens);
}


char peak(FILE* stream) {
  char peaked;
  peaked = fgetc(stream);
  ungetc(peaked, stream);
  return peaked;
}

int countTokens(char *filePath) {
  int count = 0;
  char peakedNextCharacter;
  FILE* filePointer;

  filePointer = fopen(filePath, "r");

  do {
    readToken(filePointer);
    count++;
    peakedNextCharacter = peak(filePointer);
  }
  while (peakedNextCharacter != EOF);

  fclose(filePointer);

  return count;
}

void readTokens(char *filePath, token *tokens) {
  int index = 0;
  char peakedNextCharacter;
  FILE* filePointer;

  filePointer = fopen(filePath, "r");

  do {
    tokens[index] = readToken(filePointer);
    index++;
    peakedNextCharacter = peak(filePointer);
  }
  while (peakedNextCharacter != EOF);

  fclose(filePointer);
}

int findMatchIndexInDictionary(int dictionarySize, token *dictionary, token tokenToMatch) {
  for (int i=0; i<dictionarySize/2; i++) {
    if (strcmp(dictionary[i*2].content, tokenToMatch.content) == 0) {
      return (i*2)+1;
    }
  }
  return -1;
}

void translateTokens(int dictionarySize,
                     token *dictionary,
                     int messageSize,
                     token *message,
                     token *translatedMessage) {

  for (int i=0; i<messageSize; i++) {
    const token tokenToTranslate = message[i];
    const int matchIndex = findMatchIndexInDictionary(dictionarySize, dictionary, tokenToTranslate);

    if (matchIndex == -1) {
      translatedMessage[i] = message[i];
    }
    else {
      translatedMessage[i] = dictionary[matchIndex];
    }
  }
}
