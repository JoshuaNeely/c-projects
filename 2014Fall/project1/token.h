#ifndef __TOKEN_H_
#define __TOKEN_H_

struct token {
  char content[50];
};

typedef struct token token;

static const token defaultToken = {""};

#endif // __TOKEN_H_
