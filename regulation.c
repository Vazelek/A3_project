    #include <stdio.h>
	 #include <stdlib.h>
    #include "regulation.h"

	float regulation(int regul, float consigne,float* tabT, int nT){
        if (regul==1){
            if (consigne > tabT[nT-1]){
                return 50;
            }
            else{
                return 0;
            }
        }
        else{
            
        }
}
	 
	float regulationTest(int regul,float consigne,float* tabT, int nT){
		float cmd;
		
		return cmd;
	}
    
  
