/* First, the standard lib includes, alphabetically ordered */
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"
#include "list.h"

/* Maximum allowed length of the array */
static const unsigned int MAX_SIZE = 100000u;

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Compute average for the list of numbers in file.\n"
           "\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}


float average(list l) {
    unsigned int largo;
    float elem;
    float r = 0;
    list laux;
    laux = copy_list(l);
    largo = length(l);
    while (!is_empty(laux)) {
        elem = head(laux);
        r = r + elem;
        laux = tail(laux);
    }

    destroy(laux);
    r = r / largo;

    return r;
}

list array_to_list(int array[], unsigned int length) {
    /* Initialize the list */
    list l = NULL;
    l = empty();
    for (unsigned int i = 0u; i < length; ++i) {
        l = addr(l, array[i]);
    }
    /* Return list */
    return l;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];

    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);

    /* show the array in the screen */
    array_dump(array, length);

    /* transform from array to our list type */
    list l = array_to_list(array, length);

    /* call the average function */
    printf("The average is: %.2f \n", average(l));

    /* destruyo la lista */

    destroy(l);

    list l2 = array_to_list((int[]){10, 20, 30, 40, 50, 60}, 6);

    list_elem e = index(l2, 2);
    fprintf(stdout, "\n\n\nImprimo el segundo elemento de la lista l2, espero 20\n");
    fprintf(stdout, "Resultado: %d\n", e);

    list t = take(l2, 2); // espero 10,20
    // fprintf(stdout, "\n\n\nImprimo la lista take, espero 10,20\nResultado: ");
    // print_list(t); 
    
    list d = drop(l2, 2); // espero 30,40,50,60
    fprintf(stdout, "\n\n\nImprimo la lista drop, espero 30,40,50,60\nResultado: ");
    print_list(d);

    list c = concat_list(t,d); // espero 10,20,30,40,50,60
    fprintf(stdout, "\n\n\nImprimo la lista concatenada t y d, espero 10,20,30,40,50,60\nResultado: ");
    print_list(c);
    fprintf(stdout, "\n\n\n");

    

    destroy(l2);
    destroy(d);
    destroy(t);
    destroy(c);

    return (EXIT_SUCCESS);
}
