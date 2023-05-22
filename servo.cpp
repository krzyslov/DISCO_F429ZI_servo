#include "servo.h"
#include "led.h"
#include "LCD_DISCO_F429ZI.h"


Servo sServo;

Servo::Servo()
{

    iCurrentPosition = 0;
    iDesiredPosition = 0;
    iPreviousAngle = 0;
    iCurrentAngle = 0;
    eState = CALLIB;

    ServoLcd.Clear(LCD_COLOR_WHITE);
    ServoLcd.SetTextColor(LCD_COLOR_BLACK);
    ServoLcd.FillCircle(SERVO_DISC_CENTER_X, SERVO_DISC_CENTER_Y, SERVO_RADIUS);
    LedDisplayInit();

    LedOn(0);
    displayArm();
    
    ticker.attach(callback(this, &Servo::Automat), 0.1);
    
}

enum DetectorState Servo::eReadDetector()
{
    
    if ( (iCurrentPosition % SERVO_STEPS) == 0 )
    {
        return ACTIVE;
    }else
    {
        return INACTIVE;
    }
    
}

void Servo::ServoCallib()
{
    bStepProtocol = false;
    eState = CALLIB;
    return;
}

void Servo::calc_curr_angle()
{
    iCurrentAngle = iCurrentPosition * (360 / SERVO_STEPS);
    return;
}


double Servo::calc_servoline_xcoord(double dAngle = 0)
{
    dAngle = dAngle * 3.14 / 180;
    return (SERVO_DISC_CENTER_X + SERVO_RADIUS*cos(dAngle));
}

double Servo::calc_servoline_ycoord(double dAngle = 0)
{
    dAngle = dAngle * 3.14 / 180;
    return (SERVO_DISC_CENTER_Y + SERVO_RADIUS*sin(dAngle));
}

void Servo::displayArm()
{
        calc_curr_angle();
        // zakrycie poprzedniej czarnej kresi
        ServoLcd.SetTextColor(LCD_COLOR_BLACK);
        ServoLcd.DrawLine(SERVO_DISC_CENTER_X,SERVO_DISC_CENTER_Y,calc_servoline_xcoord(iPreviousAngle),calc_servoline_ycoord(iPreviousAngle));
        iPreviousAngle = iCurrentAngle;
        // biala kreska i biale lozysko
        ServoLcd.SetTextColor(LCD_COLOR_WHITE);
        ServoLcd.DrawLine(SERVO_DISC_CENTER_X,SERVO_DISC_CENTER_Y,calc_servoline_xcoord(iCurrentAngle),calc_servoline_ycoord(iCurrentAngle));
        ServoLcd.FillCircle(SERVO_DISC_CENTER_X, SERVO_DISC_CENTER_Y, SERVO_BEARING_RADIUS);
}

void Servo::GoTo(unsigned int uiGoToPosition)
{
    eState = IN_PROGRESS;
    iCurrentPosition = iCurrentPosition % SERVO_STEPS;
    iDesiredPosition = uiGoToPosition % SERVO_STEPS; 
    bStepProtocol = false;
    
}

void Servo::Step(unsigned int uiStepAbout)
{
    eState = IN_PROGRESS;
    iDesiredPosition = iCurrentPosition + uiStepAbout; 
    bStepProtocol = true;
}

void Servo::Automat()
{
    
    switch(eState)
        {
            case CALLIB:
            {
                displayArm();
                if ( ACTIVE == eReadDetector() )
                {
                    iCurrentPosition = 0;
                    iDesiredPosition = 0;
                    eState = IDLE;
                }else
                {
                    LedStepRight();
                    iCurrentPosition += 1;
                    eState = CALLIB;
                }
                break;
            }
            case IDLE:
            { 
                break;
            }
            case IN_PROGRESS:
            {
                displayArm();
                if ( (eReadDetector() == ACTIVE) && !bStepProtocol )
                {
                    iCurrentPosition = 0;
                }   
                    
                if ( iCurrentPosition == iDesiredPosition )
                {
                    eState = IDLE;
                } else {
                    unsigned int uiLdir_steps_needed = 0;
                    unsigned int uiRdir_steps_needed = 0;
                    
                    if ( iDesiredPosition > iCurrentPosition ) 
                    {
                        uiRdir_steps_needed = iDesiredPosition - iCurrentPosition;
                        uiLdir_steps_needed = SERVO_STEPS - (iDesiredPosition - iCurrentPosition);
                        
                    }else
                    {
                        uiRdir_steps_needed = SERVO_STEPS - (iCurrentPosition - iDesiredPosition);
                        uiLdir_steps_needed = iCurrentPosition - iDesiredPosition;
                    }
                    
                    
                    if ( (uiLdir_steps_needed < uiRdir_steps_needed) && !bStepProtocol )
                    {
                        LedStepLeft();
                        iCurrentPosition -= 1;
                        if ( iCurrentPosition == -1 ) 
                        {
                            iCurrentPosition = SERVO_STEPS - 1;
                        }
                    }else
                    {
                        LedStepRight();
                        iCurrentPosition += 1;
                    }
                    
                }
                break;
             }   
        }
}