//==============================================================================
#include "io430.h"
//==============================================================================
#define FWD     (1)
#define BWD     (0)
#define DELAY  {for(unsigned int i = 0; i < 0x7fff; i++);}
#define DELAYS {for(unsigned int i = 0; i < 800; i++);}
//==============================================================================
void winding(unsigned int aMotor, unsigned int aNumb, unsigned int aDir)
{
  switch(aMotor)
  {
  case 1: 
    if(aNumb == 1)
    {
      if(aDir) {P2OUT |= BIT1; P2OUT &= ~BIT0;}
      else     {P2OUT |= BIT0; P2OUT &= ~BIT1;}
      DELAYS;
      P2OUT &= ~(BIT0 | BIT1);
    }
    else if (aNumb == 2)
    {
      if(aDir) {P2OUT |= BIT2; P2OUT &= ~BIT3;}
      else     {P2OUT |= BIT3; P2OUT &= ~BIT2;}
      DELAYS;
      P2OUT &= ~(BIT2 | BIT3);
    }
    break;
  
  case 2: 
    if(aNumb == 1)
    {
      if(aDir) {P1OUT |= BIT3; P1OUT &= ~BIT0;}
      else     {P1OUT |= BIT0; P1OUT &= ~BIT3;}
      DELAYS;
      P1OUT &= ~BIT0; P1OUT &= ~BIT3;
    }
    else if (aNumb == 2)
    {
      if(aDir) {P1OUT |= BIT4; P1OUT &= ~BIT5;}
      else     {P1OUT |= BIT5; P1OUT &= ~BIT4;}
      DELAYS;
      P1OUT &= ~BIT4; P1OUT &= ~BIT5;
    }
    break;
  }
  
  
//  if(aNumb == 1)
//  {
//    if(aDir) {P1OUT |= BIT1; P1OUT &= ~BIT2;}
//    else     {P1OUT |= BIT2; P1OUT &= ~BIT1;}
//    DELAYS;
//    P1OUT &= ~BIT2; P1OUT &= ~BIT1;
//  }
//  else if (aNumb == 2)
//  {
//    if(aDir) {P1OUT |= BIT3; P1OUT &= ~BIT5;}
//    else     {P1OUT |= BIT5; P1OUT &= ~BIT3;}
//    DELAYS;
//    P1OUT &= ~BIT3; P1OUT &= ~BIT5;
//  }
  
}
//==============================================================================
void steps(unsigned int aMotor, unsigned int aDir, unsigned int aCnt)
{
//  for(unsigned int i = 0; i < aCnt; i++)  
//    if(aDir)
//      {
//        
//        P1OUT |= BIT1; P1OUT &= ~BIT2; DELAYS;
//        P1OUT &= ~BIT3; P1OUT |= BIT5; DELAYS;
//        P1OUT |= BIT5; P1OUT &= ~BIT3; DELAYS;
//        P1OUT &= ~BIT1; P1OUT |= BIT2; DELAYS;
//        P1OUT |= BIT2; P1OUT &= ~BIT1; DELAYS;
//        P1OUT &= ~BIT5; P1OUT |= BIT3; DELAYS;
//        P1OUT |= BIT3; P1OUT &= ~BIT5; DELAYS;
//        P1OUT &= ~BIT2; P1OUT |= BIT1; DELAYS;
//        
//        P1OUT &= ~(BIT1 | BIT2 | BIT3 | BIT5);
//      }
//      else
//      {
//         
//        P1OUT &= ~BIT2; P1OUT |= BIT1; DELAYS;
//        P1OUT |= BIT3; P1OUT &= ~BIT5; DELAYS;
//        P1OUT &= ~BIT5; P1OUT |= BIT3; DELAYS;
//        P1OUT |= BIT2; P1OUT &= ~BIT1; DELAYS;
//        P1OUT &= ~BIT1; P1OUT |= BIT2; DELAYS;
//        P1OUT |= BIT5; P1OUT &= ~BIT3; DELAYS;
//        P1OUT &= ~BIT3; P1OUT |= BIT5; DELAYS;
//        P1OUT |= BIT1; P1OUT &= ~BIT2; DELAYS; 
//        
//        P1OUT &= ~(BIT1 | BIT2 | BIT3 | BIT5);
//      }
    
  if(aDir)
      {
    for(unsigned int i = 0; i < aCnt; i++) 
    {
      winding(aMotor, 1, FWD); //DELAY;
      winding(aMotor, 2, BWD); //DELAY;   
      winding(aMotor, 1, BWD); //DELAY;
      winding(aMotor, 2, FWD); //DELAY;           
    }
  }
  else
  {
    for(unsigned int i = 0; i < aCnt; i++) 
    {     
      winding(aMotor, 2, FWD); //DELAY;
      winding(aMotor, 1, BWD); //DELAY;
      winding(aMotor, 2, BWD); //DELAY; 
      winding(aMotor, 1, FWD); //DELAY;     
    }
  }  
}
//==============================================================================
void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  P1OUT &= ~(BIT0 | BIT3 | BIT4 | BIT5);
  P1DIR |=  (BIT0 | BIT3 | BIT4 | BIT5);
  
  P2OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3);
  P2DIR |=  (BIT0 | BIT1 | BIT2 | BIT3);
  
//  P1OUT &= ~(BIT1 | BIT2 | BIT3 | BIT5);
//  P1DIR |=  (BIT1 | BIT2 | BIT3 | BIT5);
  
  while(1)
  {
   
      for(unsigned int i = 0; i < 6; i++) 
      {
        steps(1, FWD, 2); DELAY; DELAY;
        steps(2, FWD, 2); DELAY;  DELAY;
      }
      
      for(unsigned int i = 0; i < 6; i++) 
      {
        steps(1, BWD, 2); DELAY; DELAY;
        steps(2, FWD, 3); DELAY; DELAY;
      }
      
      for(unsigned int i = 0; i < 6; i++) 
      {
        steps(1, BWD, 2); DELAY;  DELAY;
        steps(2, BWD, 3); DELAY;  DELAY;
      }
      
      for(unsigned int i = 0; i < 6; i++) 
      {
        steps(1, FWD, 2); DELAY;  DELAY;
        steps(2, BWD, 3); DELAY; DELAY; 
      }
     
  }
}
