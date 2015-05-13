#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "struct.h"
/*
cc -Wall -lm correlate_cl.c -o ./correlate.x

*/

float **read_cluster_data(char fname[MAX_FILE_NAME], int *n_item);
void find_closest_linked(float pos[3], float **cluster_data, int n_cluster, float *distance, 
			 int *last_ID, int *n_ID, int *linked_list, int n_side, float cell_size, int *closest, float limit_mass);
void find_second_closest_linked(float pos[3], float mass_1, float mass_2, float **cluster_data, int n_cluster, float *distance, 
				int *last_ID, int *n_ID, int *linked_list, int n_side, float cell_size, int *closest, float limit_mass);
/*Loops over the elements of cluster_data_1 and find its closest neighbors 
  in the list of elements cluster_data_2. Prints the distance, the index of cluster_data_1 and 
  the index of cluster_data_2*/
int main(int argc, char **argv){
    char cl_file_1[MAX_FILE_NAME];
    char cl_file_2[MAX_FILE_NAME];
    char outfile[MAX_FILE_NAME];
    FILE *out;
    float **cluster_data_1;
    float **cluster_data_2;
    int n_cluster_1;
    int n_cluster_2;
    int i,j;
    int int_i, int_j, int_k, index;
    float distance[2];
    float pos[3];
    int n_side; /*grid side for linked list*/
    int *last_ID;/*ID's over a grid*/
    int *link_list_cl;/*to be used as a linked list for cl_file_2*/
    int *n_ID; /*number of ID's in a grid cell*/
    float box_size, cell_size;
    int close_index[2];
    float mass_th;
    float object_mass;
    float mass_1, mass_2;

    if(argc!=7){
	fprintf(stderr, "%s\n",USAGE);
	exit(0);
    }
    
    strcpy(cl_file_1, argv[1]);
    strcpy(cl_file_2, argv[2]);
    strcpy(outfile, argv[3]);
    n_side = atoi(argv[4]);
    box_size = atof(argv[5]);
    mass_th = atof(argv[6]);
    fprintf(stdout, "cl_file_1 (pivot file) %s\n", cl_file_1);
    fprintf(stdout, "cl_file_2              %s\n", cl_file_2);
    fprintf(stdout, "output_file            %s\n", outfile);
    fprintf(stdout, "n_grid                 %d\n", n_side);
    fprintf(stdout, "box_size               %g\n", box_size);
    cell_size = box_size/n_side;
    fprintf(stdout, "cell_size               %g\n", cell_size);
    fprintf(stdout, "mass_th[fraction of pivot mass] %g\n", mass_th);

    /*open the output file*/
    if(!(out  = fopen(outfile, "w"))){
	fprintf(stdout, "problem opening file %s\n",outfile);
	exit(1);
    }

    /*read the cluster data*/
    cluster_data_1 = read_cluster_data(cl_file_1, &n_cluster_1);
    cluster_data_2 = read_cluster_data(cl_file_2, &n_cluster_2);
    
    /*allocate data for linked list over the space grid*/
    if(!(last_ID=malloc(sizeof(int)*n_side*n_side*n_side))){
	fprintf(stderr, "Problem allocating last_ID\n");
	exit(0);
    }	
    if(!(n_ID=malloc(sizeof(int)*n_side*n_side*n_side))){
	fprintf(stderr, "Problem allocating n_ID\n");
	exit(0);
    }	
    /*allocate the linked list*/
    if(!(link_list_cl=malloc(sizeof(int)*n_cluster_2))){
	fprintf(stderr, "Problem allocating linked list\n");
	exit(0);
    }	

    fprintf(stdout, "init initialization linked list\n");
    /*initializing list_ID*/
    for(j=0;j<(n_side*n_side*n_side);j++){
	last_ID[j] = -1;
	n_ID[j] = 0;
    }

    /*initializing linked list*/
    for(j=0;j<n_cluster_2;j++){
	link_list_cl[j] = -1;
    }
    fprintf(stdout, "finished initialization linked list\n");

    fprintf(stdout, "starte making linked list\n");
    /*make the linked list*/
    for(j=0;j<n_cluster_2;j++){
      if(j<100){
	fprintf(stdout, "%d out of %d\n", j, n_cluster_1);fflush(stdout);
      }
      int_i = (int)(cluster_data_2[j][CL_P_X]/cell_size);
	int_j = (int)(cluster_data_2[j][CL_P_Y]/cell_size);
	int_k = (int)(cluster_data_2[j][CL_P_Z]/cell_size);
	if(int_i==n_side) int_i--;
	if(int_j==n_side) int_j--;
	if(int_k==n_side) int_k--;

	//	fprintf(stdout, "iteration %d i, j, k side %d %d %d %d\n", j, int_i, int_j, int_k, n_side);
	//	fflush(stdout);

	index = int_k + n_side*(int_j + n_side*int_i);
	
	n_ID[index]++;
	link_list_cl[j] = last_ID[index];
	last_ID[index] = j;	 	
    }

    fprintf(stdout, "finished linked list\n");
    for(i=0;i<n_cluster_1;i++){
      if(i<100){
	fprintf(stdout, "%d out of %d\n", i, n_cluster_1);fflush(stdout);
      }
	pos[0] = cluster_data_1[i][CL_P_X];
	pos[1] = cluster_data_1[i][CL_P_Y];
	pos[2] = cluster_data_1[i][CL_P_Z];
	object_mass = cluster_data_1[i][CL_MASS];

	find_closest_linked(pos, cluster_data_2, n_cluster_2, distance, 
				      last_ID, n_ID, link_list_cl, n_side, cell_size, close_index, mass_th*object_mass);
	mass_1 = cluster_data_1[i][CL_MASS];
	mass_2 = cluster_data_1[close_index[0]][CL_MASS];

	find_second_closest_linked(pos, mass_1, mass_2, cluster_data_2, n_cluster_2, distance, 
				      last_ID, n_ID, link_list_cl, n_side, cell_size, close_index, mass_th*object_mass);
	
	fprintf(out, "%d %d %d\n", i, close_index[0], close_index[1]);
//	fprintf(out, "%d %d %d %g %g %g %g %g\n", i, close_index[0], close_index[1], distance[0], distance[1], pos[0], pos[1], pos[2]);
	if(!(i%1000)){fprintf(stdout, "%d out of %d\n", i, n_cluster_1);fflush(stdout);}
    }
    fclose(out);
    return 0;    
}

void find_closest_linked(float pos[3], float **cluster_data, int n_cluster, float *distance, 
			int *last_ID, int *n_ID, int *linked_list, int n_side, float cell_size, int *closest, float limit_mass)
{
    int i, j, k, m;
    float min_dist, new_dist;
    int min_index;
    int second_min_index;
    int int_i, int_j, int_k, index;
    int min_i, min_j, min_k;
    int max_i, max_j, max_k;
    int next_ID;
    int delta_n;
    int eff_i, eff_j, eff_k;
    float my_pos[3];
    float l_box;
    float second_min_dist;
    float my_mass;
    float my_radius;

    delta_n = 3;

    l_box = cell_size*n_side;    
    min_dist = 100.0*l_box;
    second_min_dist = min_dist;


    int_i = (int)(pos[0]/cell_size);
    int_j = (int)(pos[1]/cell_size);
    int_k = (int)(pos[2]/cell_size);
    

    min_i = int_i-delta_n; max_i = int_i+delta_n;
    min_j = int_j-delta_n; max_j = int_j+delta_n;
    min_k = int_k-delta_n; max_k = int_k+delta_n;
    


/*
    fprintf(stdout, "x y z [%d %d] [%d %d] [%d %d]\n",
	    min_i, max_i, min_j, max_j, min_k, max_k);
*/

    min_index = -1;
    second_min_index = -1;
    /*loop over the selected patch in space*/
    for(k=min_k;k<max_k;k++){
	for(i=min_i;i<max_i;i++){
	    for(j=min_j;j<max_j;j++){
		
		/*here I need to take into account the boundary  conditions*/
		eff_i = (i + n_side)%n_side;
		eff_j = (j + n_side)%n_side;
		eff_k = (k + n_side)%n_side;

		index =  eff_k + n_side*(eff_j + n_side*eff_i);
		/*loop over the particles in the cell*/
		next_ID = last_ID[index];
		while(next_ID > -1){			    			    
		    my_pos[0] = cluster_data[next_ID][CL_P_X];
		    my_pos[1] = cluster_data[next_ID][CL_P_Y];
		    my_pos[2] = cluster_data[next_ID][CL_P_Z];
		    my_mass = cluster_data[next_ID][CL_MASS];
		    my_radius = cluster_data[next_ID][CL_R_VIR]/1000.0; /*This is valif if the data comes in kpc*/

		    if(eff_i>i){
			my_pos[0] -= l_box;
		    }else if(eff_i<i){
			my_pos[0] += l_box;
		    }

		    if(eff_j>j){
			my_pos[1] -= l_box;
		    }else if(eff_j<j){
			my_pos[1] += l_box;
		    }

		    if(eff_k>k){
			my_pos[2] -= l_box;
		    }else if(eff_k<k){
			my_pos[2] += l_box;
		    }
	    
		    new_dist = 0.0;	
		    for(m=0;m<3;m++){
			new_dist += pow((my_pos[m] - pos[m]),2.0);
		    }
		    new_dist = sqrt(new_dist);			    
		    if(new_dist<min_dist && my_mass > limit_mass && new_dist > my_radius){
			min_dist = new_dist;
			min_index = next_ID;
		    }			

		    next_ID = linked_list[next_ID];
		}		    
	    }
	}
    }

    closest[0] = min_index;
    distance[0] = min_dist;    
}


void find_second_closest_linked(float pos[3], float mass_1, float mass_2, float **cluster_data, int n_cluster, float *distance, 
				int *last_ID, int *n_ID, int *linked_list, int n_side, float cell_size, int *closest, float limit_mass)
{
    int i, j, k, m;
    float min_dist, new_dist;
    int min_index;
    int second_min_index;
    int int_i, int_j, int_k, index;
    int min_i, min_j, min_k;
    int max_i, max_j, max_k;
    int next_ID;
    int delta_n;
    int eff_i, eff_j, eff_k;
    float my_pos[3];
    float l_box;
    float second_min_dist;
    float my_mass;
    float my_radius;

    delta_n = 3;

    l_box = cell_size*n_side;    
    min_dist = 100.0*l_box;
    second_min_dist = min_dist;


    int_i = (int)(pos[0]/cell_size);
    int_j = (int)(pos[1]/cell_size);
    int_k = (int)(pos[2]/cell_size);
    

    min_i = int_i-delta_n; max_i = int_i+delta_n;
    min_j = int_j-delta_n; max_j = int_j+delta_n;
    min_k = int_k-delta_n; max_k = int_k+delta_n;
    
/*
    fprintf(stdout, "x y z [%d %d] [%d %d] [%d %d]\n",
	    min_i, max_i, min_j, max_j, min_k, max_k);
*/

    min_index = -1;
    second_min_index = -1;
    /*loop over the selected patch in space*/
    for(k=min_k;k<max_k;k++){
	for(i=min_i;i<max_i;i++){
	    for(j=min_j;j<max_j;j++){
		
		/*here I need to take into account the boundary  conditions*/
		eff_i = (i + n_side)%n_side;
		eff_j = (j + n_side)%n_side;
		eff_k = (k + n_side)%n_side;

		index =  eff_k + n_side*(eff_j + n_side*eff_i);
		/*loop over the particles in the cell*/
		next_ID = last_ID[index];
		while(next_ID > -1){			    			    
		    my_pos[0] = cluster_data[next_ID][CL_P_X];
		    my_pos[1] = cluster_data[next_ID][CL_P_Y];
		    my_pos[2] = cluster_data[next_ID][CL_P_Z];		    
		    my_mass = cluster_data[next_ID][CL_MASS];
		    my_radius = cluster_data[next_ID][CL_R_VIR]/1000.0; /*valid if radius comes in kpc/h*/

		    if(eff_i>i){
			my_pos[0] -= l_box;
		    }else if(eff_i<i){
			my_pos[0] += l_box;
		    }

		    if(eff_j>j){
			my_pos[1] -= l_box;
		    }else if(eff_j<j){
			my_pos[1] += l_box;
		    }

		    if(eff_k>k){
			my_pos[2] -= l_box;
		    }else if(eff_k<k){
			my_pos[2] += l_box;
		    }
	    
		    new_dist = 0.0;	
		    for(m=0;m<3;m++){
			new_dist += pow((my_pos[m] - pos[m]),2.0);
		    }
		    new_dist = sqrt(new_dist);			    
		    
		    if(new_dist < min_dist && next_ID!=closest[0] && my_mass>mass_1&& my_mass>mass_2 && new_dist > my_radius){
			min_dist = new_dist;
			min_index = next_ID;
		    }			


		    next_ID = linked_list[next_ID];
		}		    
	    }
	}
    }

    closest[1]  = min_index;        
    distance[1] = min_dist;
}



 float **read_cluster_data(char fname[MAX_FILE_NAME], int *n_item)
{
    FILE *filein;
    char line[MAX_FILE_NAME*2];
    int  c, num_lines, i, n_halos, j;
    float box_size, redshift, dm_particle_mass;
    float **dummy;
    char *cptr, *strtokbuf;

    

    if(!(filein = fopen(fname, "r"))){
	printf("problem opening file in read cluster data%s\n", fname);
    }

    num_lines = 0;
    /*count the lines*/
    do {
	c = fgetc(filein);
	if (c == '\n')
	    num_lines++;
    } while (c != EOF);
    
    rewind(filein);


    printf("file %s | n_lines %d\n", fname, num_lines);
    n_halos = num_lines ;

    /* memory allocation*/    
    if(!(dummy = malloc((n_halos)*sizeof(float *))))
    {
	printf("problem with the memory allocation for halo DATA\n");
    }
    
    for(i=0;i<n_halos;i++)
    {
	if(!(dummy[i] = malloc((HALO_DATA_N_COL)*sizeof(float))))
	{
	    printf("problem with the memory allocation for halo DATA in halo number %d\n",i);
	}
    }


    for(i=0;i<n_halos;i++)
    {
	/*read the line*/
	fgets(line, MAX_FILE_NAME, filein);
	//	fprintf(stdout, "%s\n", line);
	/*parse the elements in the line*/
	cptr=strtok_r(line, " ", &strtokbuf);
	dummy[i][0] = (float)(atof(cptr));
	for(j=1;j<HALO_DATA_N_COL;j++)
	{
	    cptr=strtok_r(NULL, " ", &strtokbuf) ;
	    dummy[i][j] = (float)(atof(cptr));
	}
    }
    fclose(filein);    

    *n_item = n_halos;
    return dummy;
}
