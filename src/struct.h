#define MAX_TASK_LENGTH 8192
#define MAX_FILE_NAME 1024
#define MAX_FILENAME_SIZE 1024
#define HALO_DATA_N_COL 14
#define MAX(x,y) x>y?x:y
#define MIN(x,y) x>y?y:x
#define CL_P_X 0  /*in h^-1 Mpc*/
#define CL_P_Y 1
#define CL_P_Z 2
#define CL_V_X 3 /*in km/s*/
#define CL_V_Y 4
#define CL_V_Z 5
#define CL_MASS_BOUND 6
#define CL_MASS 7/*in M_sun/h*/
#define CL_R_VIR 8
#define CL_V_RMS 9
#define CL_V_CIRC 10
#define CL_HALO_ID 11
#define CL_C_VIR 12
#define CL_NPART 13
#define CORR_PIVOT_INDEX 1
#define CORR_PARTNER_INDEX 2
#define CORR_PARTNER2_INDEX 3
#define CORR_DATA_N_COL 3
#define USAGE "USAGE: ./correlate.x cl_pivot_file cl_file_2 output_file n_grid box_size mass_threshold"
#define BUFFER_SIZE 2000
#define PI 3.14159

