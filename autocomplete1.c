#include <stdio.h>
#include <stdlib.h>
#include "ternarytree.h"
#include "linklist.h"

/* Kenny Lee 801361 3/9/17 */

int
main(int argc, char *argv[]){

/* Checking if the datafile, outputfile and prefix is not NULL */
    char *datafile, *outputfile, *prefix;
    prefix = argv[3];
    outputfile = argv[2];
    datafile = argv[1];

    if(prefix == NULL || outputfile == NULL || datafile == NULL){
        printf("STDIN FAILURE\n");
        exit(EXIT_FAILURE);
    }

/* Opening datafile and output file to read and write */
    FILE *ifp, *ofp;

    ifp = fopen(datafile, "r");
    if(ifp == NULL){
        fprintf(stderr, "INPUT FILE FAIL\n");
        exit(EXIT_FAILURE);
    }

    ofp = fopen(outputfile, "w");
    if(ofp == NULL){
        fprintf(stderr, "OUTPUT FILE FAIL\n");
        exit(EXIT_FAILURE);
    }

/* Creating a space for words that form the ternary tree */
    char *word;

    word = malloc(MAXCHAR*sizeof(char));
    if(word == NULL){
        printf("MALLOC FAILURE\n");
        exit(EXIT_FAILURE);

    }

/* Reading the file into a ternary tree */
    struct node *pNode = NULL;
    int weight;

    while(fscanf(ifp, "%d;%250[^\n]", &weight, word) != EOF){
        pNode = insert(pNode, word, weight);

    }

/* Writing the results to the output file */
    fprintf(ofp, "Prefix:  %s\n", prefix);

    struct link_list *list = NULL;
    list = find_and_traverse(pNode, prefix, ofp);

    if(list != NULL){
        while(list->next != NULL){
            fprintf(ofp, "key:  %s%s ---> weight:  %d\n", prefix, list->buffer,
            list->weight);

            list = list->next;

        }
        fprintf(ofp, "key:  %s%s ---> weight:  %d\n", prefix, list->buffer,
        list->weight);

    }

    fclose(ifp);
    fclose(ofp);

    return 0;
}
