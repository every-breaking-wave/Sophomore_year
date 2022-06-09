#include "common.h"
using namespace Minisat;

bool lab1(int states[], int n, int button[][2], int m, bool answer[])
{  //states:primary state  n: stone  m: switch  button: stone No.

    Solver solver;
    Var variables[1000];
    int i, j;
    for(i = 0; i<m; ++i)
        variables[i] = solver.newVar();
    //TODO : your solution here.
   // solver.addClause(  )

    int switchNum1 , switchNum2;
    for(int i = 0; i < n; i++){    // n :stone id
       switchNum1 = -1, switchNum2 = -1;
       for(int j = 0; j < m; j++){
           if (button[j][0] == i + 1 ||  (button[j][1] == i + 1))
           {
              
               if (switchNum1 == -1)
                   switchNum1 = j;
               else
                   switchNum2 = j;
           }    
       }
       if(switchNum1 >= 0 && switchNum2 >= 0){
           if(states[i] == 0){   
               solver.addClause(~mkLit(variables[switchNum1]), ~mkLit(variables[switchNum2]));
               solver.addClause(mkLit(variables[switchNum1]), mkLit(variables[switchNum2]));
           }
           else if(states[i] != 0){
               solver.addClause(mkLit(variables[switchNum1]), ~mkLit(variables[switchNum2]));
               solver.addClause(~mkLit(variables[switchNum1]), mkLit(variables[switchNum2]));
           }
       }
       else {
           int x = (switchNum1 == -1) ? switchNum2 : switchNum1;
           if(states[i] == 0){   
               solver.addClause(mkLit(variables[x]));
           }
           else if(states[i] != 0){
               solver.addClause(~mkLit(variables[x]));
           }
       }
   }


   //solve SAT problem
   auto sat = solver.solve();
   if (sat)
   {
       for (i = 0; i < m; ++i)
           answer[i] = (solver.modelValue(variables[i]) == l_True);
       return true;
    }
    return false;
}




