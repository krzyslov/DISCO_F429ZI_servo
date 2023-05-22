#ifndef LED_H
#define LED_H

#define LED_CIRCLE_RADIUS 20

enum StepDirection {LEFT,RIGHT};

void LedOn(unsigned char);
void LedStep(enum StepDirection);
void LedStepRight(void);
void LedStepLeft(void);
void LedDisplayInit(void);

#endif