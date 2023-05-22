#include "dekodowanie.h"
#include "mbed.h"
#define MAX_KEYWORD_NR 4
#define MAX_KEYWORD_STRING_LTH 20 // mksymalna dlugosc komendy
#define MAX_TOKEN_NR 4

struct Keyword
{
enum KeywordCode eCode;
char cString[MAX_KEYWORD_STRING_LTH + 1];
};

struct Keyword asKeywordList[MAX_KEYWORD_NR]=
{
{ID,"id"},
{GOTO, "goto" },
{CALIB, "calib"},
{STEP, "step"}
};


struct Token asToken[MAX_TOKEN_NR]; // wypelniana przez DecodeMsg na podstawie cUartRxBuffer i 

void ReplaceCharactersInString(char pcString[])
{
    char korektor[] = " ";
    pcString = strtok(pcString,korektor);
    
    while (pcString != NULL)
    {
        pcString = strtok(NULL,korektor);
    }
    
    return;
}


enum StringToKeyword { OK, ERROR_ };

enum StringToKeyword eIntStringToUInt(char pcStr[],unsigned int *puiValue)
{
    if ( 1 == sscanf(pcStr, "%d", puiValue)) { return OK; } else { return ERROR_; };
}

unsigned char ucTokenNr = 0; // liczba odebranych tokenĂłw

unsigned char ucFindTokensInString (char *pcString)
{
    char korektor[] = " ";
    char * pcTokenAddress = strtok( pcString, korektor );
    asToken[0].uValue.pcString = pcTokenAddress;
    ucTokenNr = 1;
    while ( pcTokenAddress != NULL || MAX_TOKEN_NR == ucTokenNr )
    {        
        pcTokenAddress = strtok( NULL, korektor );
        asToken[ucTokenNr].uValue.pcString = pcTokenAddress;
        ucTokenNr++;
    }
    return ucTokenNr;
}

enum StringToKeyword eStringToKeyword (char pcStr[],enum KeywordCode *peKeywordCode)
{
    unsigned char ucStrCounter;
    for(ucStrCounter=0;ucStrCounter<MAX_KEYWORD_NR;ucStrCounter++)
    {
        //if( EQUAL == eCompareString(asKeywordList[ucStrCounter].cString, pcStr ) ) <---- tutaj zamieniłem
        if( strcmp(asKeywordList[ucStrCounter].cString,pcStr) == 0 )
        {
            *peKeywordCode=asKeywordList[ucStrCounter].eCode;
            return OK;
        }
    }
    return ERROR_;
}

void DecodeTokens(void)
{
    unsigned char ucTokenCounter = 0;
    char *pcStrPointer;
    enum KeywordCode peKeywordCode;
    unsigned int uiValue;
    struct Token asCurrentToken;

    for (ucTokenCounter = 0; ucTokenCounter < ucTokenNr; ucTokenCounter++  )
    {
        pcStrPointer = asToken[ucTokenCounter].uValue.pcString;
        if ( OK == eStringToKeyword(pcStrPointer,&peKeywordCode))
        {
            asCurrentToken.uValue.eKeyword = peKeywordCode;
            asCurrentToken.eType = KEYWORD;
        }else if ( OK == eIntStringToUInt(pcStrPointer,&uiValue))
        {
            asCurrentToken.uValue.uiNumber = uiValue;
            asCurrentToken.eType = NUMBER;
        }else
        {
            asCurrentToken.eType = STRING;
            asCurrentToken.uValue.pcString = pcStrPointer;
        }
        
        asToken[ucTokenCounter] = asCurrentToken;
    }
    return;
}

void DecodeMsg(char * pcString)
{
    ucTokenNr = ucFindTokensInString(pcString);
    //puts(asToken[0].uValue.pcString);
    ReplaceCharactersInString(pcString);
    //puts(pcString);
    DecodeTokens();
    return;
}