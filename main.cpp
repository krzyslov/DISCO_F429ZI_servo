#include "mbed.h"
#include "servo.h"
#include "dekodowanie.h"

Serial pc(USBTX, USBRX);
extern struct Token asToken[MAX_TOKEN_NR]; // wypelniana przez DecodeMsg na podstawie cUartRxBuffer i 

char getst(char * cStrPtr, unsigned char ucStrSize)
{   

    for(unsigned char ucStrCtr = 0; ucStrCtr < ucStrSize; ucStrCtr++)
    {
        cStrPtr[ucStrCtr] = pc.getc();
        if (cStrPtr[ucStrCtr] == '\r')
        {
            cStrPtr[ucStrCtr] = NULL;
            return 0;
        }
    }
    return 1;
}

int main()
{      
    Servo sServo;
    
    while(1)
    {   
        char cStrBuffor[20];
        unsigned char ucStrSize = sizeof(cStrBuffor)/sizeof(cStrBuffor[0]);
        
        if ( getst(&cStrBuffor[0],ucStrSize) == 0 )
        {
            //puts("Otrzymano wiadomosc \r");
            DecodeMsg(cStrBuffor);
            
            if (asToken[0].eType == KEYWORD)
            {
                switch(asToken[0].uValue.eKeyword)
                    {
                        case ID:
                            puts("DISCO_F429ZI \r");
                            break;
                        case GOTO:
                            if (asToken[1].eType == NUMBER) { sServo.GoTo(asToken[1].uValue.uiNumber); }
                            break;
                        case CALIB:
                            sServo.ServoCallib();
                            break;
                        case STEP:
                            if (asToken[1].eType == NUMBER) { sServo.Step(asToken[1].uValue.uiNumber); }
                            break;
                    }
            } else { puts("unknown command \r"); }
        }
        
        
    }
}

