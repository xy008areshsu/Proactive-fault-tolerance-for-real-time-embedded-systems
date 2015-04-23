
#ifdef TESTPC
#define CALIBRATION_FILE "c:\\class\\work\\test.txt"
#else
#define CALIBRATION_FILE "/home/pi/calibration.txt"
#endif

#define MATSIZE 9


void read_calibration_matrix(float *matrix);


void write_calibration_matrix(float *matrix);
