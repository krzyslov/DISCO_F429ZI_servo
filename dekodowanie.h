#ifndef DEKODOWANIE_H
#define DEKODOWANIE_H

enum KeywordCode { ID, GOTO, CALIB, STEP};

union TokenValue
{
enum KeywordCode eKeyword; // jezeli KEYWORD
unsigned int uiNumber; // jezeli NUMBER
char * pcString; // jezeli STRING
};


enum TokenType {KEYWORD, NUMBER, STRING };

struct Token
{
enum TokenType eType; // KEYWORD, NUMBER, STRING
union TokenValue uValue; // enum, unsigned int, char*
};

void DecodeMsg(char *);

#endif