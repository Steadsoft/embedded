#pragma once
// Simply runs a loop while or until some condition is true
#define SPIN_WHILE(X) while((X))
#define SPIN_UNTIL(X) while(!(X))
#define DAWDLE(Y) for (unsigned int X = 0; X < Y; X++){}

// Runs a loop while or until some condition is true and increments 
// a counter which is useful when debugging to see the number of actual iterations.
#define COUNT_WHILE(X,Y) (*Y)=0;while((X))(*Y)++;
#define COUNT_UNTIL(X,Y) (*Y)=0;while(!(X))(*Y)++;

#define WAIT_FOR(T) {while (T.SR.UIF == 0); T.SR.UIF = 0;}

