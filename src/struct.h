#define MAX_TASK_LENGTH 8192
#define MAX_FILE_NAME 1024
#define MAX_FILENAME_SIZE 1024
#define HALO_DATA_N_COL 13
#define TREES_PER_PROC  500 
#define INIT_TREE_INDEX    1 
#define UNCLAIMED -1
#define MAX_HALO_LINE  40000 /*maximum number of halos at a given level in the history of the tree*/
#define MAX(x,y) x>y?x:y
#define MIN(x,y) x>y?y:x
#define CL_INDEX 0
#define CL_P_X 1  /*in h^-1 Mpc*/
#define CL_P_Y 2
#define CL_P_Z 3
#define CL_V_X 4 /*in km/s*/
#define CL_V_Y 5
#define CL_V_Z 6
#define CL_N_PART 7
#define CL_MASS 8/*in M_sun/h*/
#define CL_SIGMA 9
#define CL_SIGMA_V 10
#define CL_R_SPH 11
#define CL_DELTA 12
#define CL_LAMBDA 13
#define CORR_PIVOT_INDEX 1
#define CORR_PARTNER_INDEX 2
#define CORR_PARTNER2_INDEX 3
#define CORR_DATA_N_COL 3
#define USAGE_DENS "USAGE: ./correlate.x cl_file index_file output_file n_grid box_size radius_size"
#define USAGE_DENS_PLANE "USAGE: ./plane_delta_dens.x cl_file output_file n_grid box_size radius_size min_x min_y min_z max_x max_y max_z delta_x delta_y delta_z"
#define USAGE0 "USAGE0: ./find_props.x cl_searched_file cl_dummy_file output_file n_grid box_size center_x center_y center_z delta_r"
#define USAGE "USAGE: ./correlate.x cl_pivot_file cl_file_2 output_file n_grid box_size mass_threshold"
#define USAGE2 "USAGE: ./physical.x cl_pivor_file cl_file_2 input_corr_file output_file boxsize"
#define USAGE3 "USAGE: ./find.x cl_FOF_1_file cl_FOF_2_file output_file n_grid box_size mass_threshold vel_treshold"
#define USAGE4 "USAGE: ./print_find.x cl_FOF_1_file cl_FOF_2_file input_file output_file"
#define USAGE5 "./write_phys_search.x [cl_file_0] [cl_file_1] [cl_file_2] [search_file_1] [search_file_2] [output] box_size"
#define BUFFER_SIZE 2000
#define PI 3.14159

