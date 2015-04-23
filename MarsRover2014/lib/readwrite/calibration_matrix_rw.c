

#include <stdio.h>
#include "calibration_matrix_rw.h"


void read_calibration_matrix(float *matrix){
    
    FILE *fp;
    int i = 0;
    char line[10];
        
    fp = fopen(CALIBRATION_FILE, "r");
        
    while(fgets(line, 10, fp) != NULL && i < MATSIZE)
    {
        sscanf (line, "%f", (matrix + (i++)));         
    }
    
    fclose(fp);
    
}

void write_calibration_matrix(float *matrix){
    
    FILE *fp;
    int i;
    
    fp = fopen(CALIBRATION_FILE, "w");
    
    for (i = 0; i < MATSIZE; i++){
        fprintf(fp, "%f\n", matrix[i]);
    }
    
    fclose(fp);
    
}

#ifdef TESTPC

void main(void){
 
    int i;
    float mat2write[MATSIZE], mat2read[MATSIZE];
    
    for (i=0; i<MATSIZE; i++){
        mat2write[i] = (float)i;
    }
    
    write_calibration_matrix(mat2write);
    
    read_calibration_matrix(mat2read);
    
    for (i=0; i<MATSIZE; i++){
        printf("%f\n", mat2read[i]);
    }
    
}

#endif
