#ifndef SERVO_H
#define SERVO_H

#define SERVO_STEPS 36
#define SERVO_RADIUS 100
#define SERVO_DISC_CENTER_X 120
#define SERVO_DISC_CENTER_Y 120
#define SERVO_BEARING_RADIUS 10
#define MAX_KEYWORD_STRING_LTH 10 // mksymalna dlugosc komendy
#define MAX_TOKEN_NR 4
#define MAX_KEYWORD_NR 4

#include "LCD_DISCO_F429ZI.h"



enum ServoState {CALLIB, IDLE, IN_PROGRESS};
enum DetectorState {ACTIVE, INACTIVE};


class Servo
{   
    public:
        void GoTo(unsigned int);
        void Step(unsigned int);
        void ServoCallib(void);
        Servo(void);
    private:
        Ticker ticker;
        LCD_DISCO_F429ZI ServoLcd;
        enum ServoState eState;
        int iCurrentAngle;
        int iPreviousAngle;
        int iCurrentPosition;
        int iDesiredPosition;
        bool bStepProtocol; 
        
        enum DetectorState eReadDetector(void);
        double calc_servoline_xcoord(double);
        double calc_servoline_ycoord(double);
        void DetectorInit(void);
        void calc_curr_angle(void);
        void displayArm(void);
        void Automat(void);
};



#endif
