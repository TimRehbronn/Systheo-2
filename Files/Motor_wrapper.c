
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#ifndef MATLAB_MEX_FILE
#include <Arduino.h>

void rising(void);
void falling(void);

volatile int prev_time = 0;
volatile int16_t currentPos = 0;
volatile int16_t lastPos = 0;
volatile uint8_t clampState = 0;
volatile int16_t curDeriv = 0;
volatile double outputDeriv = 0;
volatile int8_t inIrq = 0;
volatile int8_t inOutput = 0;

volatile int16_t posMem[32] = {0};
volatile int32_t sumPos = 0;
volatile uint16_t posMemPos = 0;

volatile int16_t derivMem[32] = {0};
volatile int32_t sumDeriv = 0;
volatile uint16_t derivMemPos = 0;

void rising() {
  attachInterrupt(1, falling, FALLING);
  prev_time = micros();
}
 
void falling() {
  attachInterrupt(1, rising, RISING);
  // 0 deg -> 30
  // 360 deg -> 1070
  // factor for to deg convertion 0.35

  currentPos = (micros()-prev_time-30);
}


#endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define y_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
#ifndef MATLAB_MEX_FILE
extern void rising(void);
extern void falling(void);
extern volatile int16_t currentPos;
extern volatile int16_t currentPos;
extern volatile uint8_t clampState;
extern volatile int16_t curDeriv;
extern volatile double outputDeriv;
extern volatile int8_t inIrq;
extern volatile int8_t inOutput;

extern volatile int16_t derivMem[32];
extern volatile int32_t sumDeriv;
extern volatile uint16_t derivMemPos;

extern volatile int16_t posMem[32];
extern volatile int32_t sumPos;
extern volatile uint16_t posMemPos;

#endif
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Start function
 *
 */
void Motor_Start_wrapper(real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Start_Changes_BEGIN --- EDIT HERE TO _END */
/*
 * Custom Start code goes here.
 */
#ifndef MATLAB_MEX_FILE
	attachInterrupt(1, rising, RISING);
#endif
/* %%%-SFUNWIZ_wrapper_Start_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Output function
 *
 */
void Motor_Outputs_wrapper(real_T *posRad,
			real_T *deriv,
			const real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/* This sample sets the output equal to the input
      y0[0] = u0[0]; 
 For complex signals use: y0[0].re = u0[0].re; 
      y0[0].im = u0[0].im;
      y1[0].re = u1[0].re;
      y1[0].im = u1[0].im;
 */
#ifndef MATLAB_MEX_FILE
    
    sumPos += currentPos - posMem[posMemPos%32];
	posMem[posMemPos%32] = currentPos;
	posMemPos ++;
    posRad[0] = ((double)(sumPos))*0.00018879763;

    
    curDeriv = (currentPos - lastPos);
    if(currentPos < 1020 && currentPos > 10 && clampState == 0){
        sumDeriv += curDeriv - derivMem[derivMemPos%32];
        derivMem[derivMemPos%32] = curDeriv;
        derivMemPos ++;
        outputDeriv = (double)(sumDeriv) * 0.09439881772;//0.04719940886;
    }else if((currentPos > 1020 || currentPos < 10) && clampState == 0){
        clampState = 1;
	}else{
        if(curDeriv >= 0 && outputDeriv >= 0 && currentPos < 1020){
            clampState = 0;
        }else if(curDeriv <= 0 && outputDeriv <= 0 && currentPos > 10){
            clampState = 0;
        }
	}

    deriv[0] = outputDeriv;
    lastPos = currentPos;
#endif
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Updates function
 *
 */
void Motor_Update_wrapper(real_T *posRad,
			real_T *deriv,
			real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
/*
 * Code example
 *   xD[0] = u0[0];
 */
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}

