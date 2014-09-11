#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define USAGE "./pair.x list_index"
/*
  DESCRIPTION:
  taking  a list of two indexes, searches for repeating pairs 
  (in both directions). Assumes that the first index is ordered, and 
  that the second index correspond to the 0-based rank of the first index.

  COMPILATION:
  cc -Wall -lm quick_pair.c  -o pair.x

*/

int main(int argc, char **argv){
    FILE *in;
    int n_lines, c;
    int *first_index;
    int *second_index;
    int *third_index;
    int *found;
    int i;
    if(argc!=2){
	fprintf(stderr, "%s\n", USAGE);
	exit(1);
    }
    
    if(!(in=fopen(argv[1], "r"))){
	fprintf(stderr, "problem opening file %s\n", argv[1]);
	exit(1);
    }
    n_lines = 0;
    do{
	c = fgetc(in);
	if(c=='\n')
	    n_lines++;
    }while(c!=EOF);
    rewind(in);
    fprintf(stderr, "%d lines\n", n_lines);   


    if(!(first_index=malloc(n_lines*sizeof(int)))){
	fprintf(stderr, "allocation problem\n");
	exit(1);
    }
    if(!(second_index=malloc(n_lines*sizeof(int)))){
	fprintf(stderr, "allocation problem\n");
	exit(1);
    }
    if(!(third_index=malloc(n_lines*sizeof(int)))){
	fprintf(stderr, "allocation problem\n");
	exit(1);
    }

    if(!(found=malloc(n_lines*sizeof(int)))){
	fprintf(stderr, "allocation problem\n");
	exit(1);
    }

    for(i=0;i<n_lines;i++){
	fscanf(in, "%d %d %d\n", &(first_index[i]), &(second_index[i]), &(third_index[i]));
	found[i] = 0 ;
	if(i<10){
	  //	  fprintf(stderr, "%d %d %d\n", first_index[i], second_index[i], third_index[i]);
	}
    }
    fclose(in);

    for(i=0;i<n_lines;i++){
	if(second_index[second_index[i]]==first_index[i] && !found[i]){
	    found[i] = 1;
	    found[second_index[i]] = 1;
	    fprintf(stdout, "%d %d %d\n", first_index[i], second_index[i], third_index[i]);
	}
    }

    return 0;
}
