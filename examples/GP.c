#include "common.h"
#include "function.h"
#include "gp.h"

int main(){
    SearchSpace *s = NULL;
    
    int min_depth = 1, max_depth = 3, n_terminals = 2, i;
    int n_functions = 3, m = 10, n = 2;
    char **terminal = NULL, **function = NULL;
    double *constant = NULL;
    
    /* loading set of terminals */
    terminal = (char **)malloc(n_terminals*sizeof(char *));
    for(i = 0; i < n_terminals; i++)
        terminal[i] = (char *)malloc(TERMINAL_LENGTH*sizeof(char));
    strcpy(terminal[0], "(x,y)");
    strcpy(terminal[1], "CONST");
    /****************************/
    
    /* loading set of functions */
    function = (char **)malloc(n_functions*sizeof(char *));
    for(i = 0; i < n_functions; i++)
        function[i] = (char *)malloc(TERMINAL_LENGTH*sizeof(char));
    strcpy(function[0], "SUM");
    strcpy(function[1], "SUB");
    strcpy(function[2], "MUL");
    /****************************/
    
    /* loading constants */
    constant = (double *)malloc(N_CONSTANTS*sizeof(double));
    for(i = 0; i < N_CONSTANTS; i++)
        constant[i] = GenerateUniformRandomNumber(0,10);
    /*********************/
        
    /* It creates a GP seach space with 10 agents (trees), 2 dimensions,
    trees with minimum depth of min_depth and maximum depth of max_depth, 2 functions (+ and -), 2 terminals (x and y) and 100 constants chosen
    at random within [0,10]*/
    s = CreateSearchSpace(m, n, _GP_, min_depth, max_depth, n_terminals, N_CONSTANTS, n_functions, terminal, constant, function);
    s->iterations = 10;
    
    /* Initializing lower and upper bounds */
    for(i = 0; i < s->n; i++){
        s->LB[i] = -5.0;
        s->UB[i] = 5.0;
    }
    
    InitializeSearchSpace(s, _GP_); /* It initalizes the search space */
         
    //s->pReproduction = 0.3; /* Setting up the probability of reproduction */
    s->pMutation = 0.4; /* Setting up the probability of mutation */
    s->pCrossover = 1-(s->pReproduction+s->pMutation); /* Setting up the probability of crossover */
    
    if (CheckSearchSpace(s, _GP_)) runGP(s, Sphere); /* It minimizes function Sphere */
    else fprintf(stderr,"\nPlease, check your GP configuration prior running it.\n");

    PrintTree2File(s, s->T[s->best], "best_tree.txt");

    DestroySearchSpace(&s, _GP_);
    
    return 0;
}

