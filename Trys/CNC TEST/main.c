
#include "io430.h"

void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P1DIR |= BIT4;

  while(1)
  {
    for(unsigned int i = 1; i < 0xffff; i++);
    P1OUT ^= BIT4;
  }
}
