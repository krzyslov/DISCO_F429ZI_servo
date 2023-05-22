#include "led.h"
#include "LCD_DISCO_F429ZI.h"
LCD_DISCO_F429ZI lcd;

void LedDisplayInit(void)
{
    lcd.SetTextColor(LCD_COLOR_BLACK);
    lcd.DrawCircle(45,280,LED_CIRCLE_RADIUS);
    lcd.DrawCircle(95,280,LED_CIRCLE_RADIUS);
    lcd.DrawCircle(145,280,LED_CIRCLE_RADIUS);
    lcd.DrawCircle(195,280,LED_CIRCLE_RADIUS);
}

void LedOn(unsigned char ucLedIndeks)
{
    
    lcd.SetTextColor(LCD_COLOR_WHITE);
    lcd.FillCircle(45,280,LED_CIRCLE_RADIUS -1 );
    lcd.FillCircle(95,280,LED_CIRCLE_RADIUS - 1);
    lcd.FillCircle(145,280,LED_CIRCLE_RADIUS - 1);
    lcd.FillCircle(195,280,LED_CIRCLE_RADIUS - 1);
    
    lcd.SetTextColor(LCD_COLOR_RED);
    switch(ucLedIndeks)
    {
        case 0:
            lcd.FillCircle(45,280,LED_CIRCLE_RADIUS -1 );
            break;
        case 1:
            lcd.FillCircle(95,280,LED_CIRCLE_RADIUS - 1);
            break;
        case 2:
            lcd.FillCircle(145,280,LED_CIRCLE_RADIUS - 1);
            break;
        case 3:
            lcd.FillCircle(195,280,LED_CIRCLE_RADIUS - 1);
            break;
        default:
            break;
    }
    return;
}

void LedStep( enum StepDirection eDirection )
{
    
    static unsigned int uiLedState = 0;
    if (eDirection == RIGHT )
    {
        uiLedState = (uiLedState + 1) % 4;
        LedOn(uiLedState);
    }else
    {
        uiLedState = (uiLedState - 1) % 4;
        LedOn(uiLedState);
    }
    return;
}

void LedStepRight()
{
    LedStep(RIGHT);
    return;
}

void LedStepLeft()
{
    LedStep(LEFT);
    return;
}

