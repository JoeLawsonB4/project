/*
 * Benchmark for different sized gridworlds
*/

#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "HMM.h"
#include "HMM_multi.h"
#include "environment.h"
#include "examples.h"
#include "helper.h"
#include <random>
#include <iostream>
using namespace std;

class Benchmark{
public:
    Benchmark(){}

    void run(int grid_type=3, int DFA_states=3, int n = 34, int seq = 275, int maxIt = 25000, double tol = 1e-6, double init_P_est = 1.0, string filename = "", int mode = 0) {
        printf("Benchmarking gridworld %d\n", grid_type);

        // VEC2D(double) SP_init;
        // VEC2D(double) SP_init(N_init, VEC(double)(N_init,init_P_est/(N_init-4)));

        int N_init = 1;

        if (mode == 2) {
            printf("here\n");
            grid_MDP = new Example(grid_type, DFA_states, mode);
            printf("Got matrix\n");

            printf("Reading from file: %s \n", "initial_MDP_est.txt");
            string line;
            ifstream read_file("initial_MDP_est.txt");
            int i = 0;
            VEC2D(double) P(9, VEC(double)(9, 0.0));
            while (getline(read_file, line)) {
                if (i < 9) {

                    // Entries separated by space
                    stringstream ss(line);
                    string s;
                    double sum = 0.0;
                    for (int j = 0; j < 9; j++) {
                        getline(ss, s, ' ');
                        P[i][j] = (double) stod(s.c_str());
                        sum += P[i][j];

                    }
                }
                i++;
            }
            printf("file read\n");

            x_m = (int **) malloc(seq * sizeof(int *));
            for (int i = 0; i < seq; i++) {
                x_m[i] = (int *) malloc(n * sizeof(int));
                for (int j = 0; j < n; j++) {
                    x_m[i][j] = 0;
                }
            }

            x_m1 = (int **) malloc(seq * sizeof(int *));
            for (int i = 0; i < seq; i++) {
                x_m1[i] = (int *) malloc(n * sizeof(int));
                for (int j = 0; j < n; j++) {
                    x_m1[i][j] = 0;
                }
            }

            x_m2 = (int **) malloc(seq * sizeof(int *));
            for (int i = 0; i < seq; i++) {
                x_m2[i] = (int *) malloc(n * sizeof(int));
                for (int j = 0; j < n; j++) {
                    x_m2[i][j] = 0;
                }
            }
            x_m3 = (int **) malloc(seq * sizeof(int *));
            for (int i = 0; i < seq; i++) {
                x_m3[i] = (int *) malloc(n * sizeof(int));
                for (int j = 0; j < n; j++) {
                    x_m3[i][j] = 0;
                }
            }
            y_m = (int **) malloc(seq * sizeof(int *));
            for (int i = 0; i < seq; i++) {
                y_m[i] = (int *) malloc((n+1) * sizeof(int));
                for (int j = 0; j < n+1 ; j++) {
                    y_m[i][j] = 0;
                }
            }
            // VEC2D(int) y_m(seq, VEC(int)(n, 0));
            y_m_1 = (int **) malloc(seq * sizeof(int *));
            for (int i = 0; i < seq; i++) {
                y_m_1[i] = (int *) malloc((n + 1) * sizeof(int));
                for (int j = 0; j < n + 1; j++) {
                    y_m_1[i][j] = 0;
                }
            }

            y_m_2 = (int **) malloc(seq * sizeof(int *));
            for (int i = 0; i < seq; i++) {
                y_m_2[i] = (int *) malloc((n + 1) * sizeof(int));
                for (int j = 0; j < n + 1; j++) {
                    y_m_2[i][j] = 0;
                }
            }
            y_m_3 = (int **) malloc(seq * sizeof(int *));
            for (int i = 0; i < seq; i++) {
                y_m_3[i] = (int *) malloc((n + 1) * sizeof(int));
                for (int j = 0; j < n + 1; j++) {
                    y_m_3[i][j] = 0;
                }
            }


            x_m_ext = (int **) malloc(seq * sizeof(int *));
            for (int i = 0; i < seq; i++) {
                x_m_ext[i] = (int *) malloc((n + 1) * sizeof(int));
                for (int j = 0; j < n + 1; j++) {
                    x_m_ext[i][j] = 0;
                }
            }

            x_m1_ext = (int **) malloc(seq * sizeof(int *));
            for (int i = 0; i < seq; i++) {
                x_m1_ext[i] = (int *) malloc((n + 1) * sizeof(int));
                for (int j = 0; j < n + 1; j++) {
                    x_m1_ext[i][j] = 0;
                }
            }

            x_m2_ext = (int **) malloc(seq * sizeof(int *));
            for (int i = 0; i < seq; i++) {
                x_m2_ext[i] = (int *) malloc((n + 1) * sizeof(int));
                for (int j = 0; j < n + 1; j++) {
                    x_m2_ext[i][j] = 0;
                }
            }

            x_m3_ext = (int **) malloc(seq * sizeof(int *));
            for (int i = 0; i < seq; i++) {
                x_m3_ext[i] = (int *) malloc((n + 1) * sizeof(int));
                for (int j = 0; j < n + 1; j++) {
                    x_m3_ext[i][j] = 0;
                }
            }

            x_m4_ext = (int **) malloc(seq * sizeof(int *));
            for (int i = 0; i < seq; i++) {
                x_m4_ext[i] = (int *) malloc((n + 1) * sizeof(int));
                for (int j = 0; j < n + 1; j++) {
                    x_m4_ext[i][j] = 0;
                }
            }
            x_m5_ext = (int **) malloc(seq * sizeof(int *));
            for (int i = 0; i < seq; i++) {
                x_m5_ext[i] = (int *) malloc((n + 1) * sizeof(int));
                for (int j = 0; j < n + 1; j++) {
                    x_m5_ext[i][j] = 0;
                }
            }

            x_m6_ext = (int **) malloc(seq * sizeof(int *));
            for (int i = 0; i < seq; i++) {
                x_m6_ext[i] = (int *) malloc((n + 1) * sizeof(int));
                for (int j = 0; j < n + 1; j++) {
                    x_m6_ext[i][j] = 0;
                }
            }
            // VEC2D(int) y_m_ext(seq, VEC(int)(n+1, 0));
            int round = 0;
            for (round = 0; round < seq; round++) {
                HMMsample2agents(P, grid_MDP->E_true, x_m1[round], x_m2[round], x_m3[round], grid_MDP->width,
                                 grid_MDP->height, grid_MDP->extraStates, n);
            }
            /*int wins = 0;
            int won = 0;*/

            // Add an aditional element to the front of each observation set

            for (int i = 0; i < seq; i++) {
                x_m1_ext[i][0] = 0;
                for (int j = 1; j < n + 1; j++) {
                    x_m1_ext[i][j] = x_m1[i][j - 1];
                }
            }
            L = grid_MDP->L;
            for (int i = 0; i < seq; i++) {
                x_m2_ext[i][0] = 0;
                for (int j = 1; j < n + 1; j++) {
                    x_m2_ext[i][j] = x_m2[i][j - 1];
                }
            }

            for (int i = 0; i < seq; i++) {
                x_m3_ext[i][0] = 0;
                for (int j = 1; j < n + 1; j++) {
                    x_m3_ext[i][j] = x_m3[i][j - 1];
                }
            }

           /* printf("here\n");
            r_m = (int **) malloc(seq * sizeof(int *));
            for (int i = 0; i < seq; i++) {
                r_m[i] = (int *) malloc((n + 1) * sizeof(int));
                for (int j = 0; j < n + 1; j++) {
                    r_m[i][j] = 0;
                }
            }*/
            int wins = 0;
            for (int i = 0; i<seq; i++){
                int state = 0;
                int won = 0;
                for(int j =0; j<n+1; j++){
/*
                    if(x_m1_ext[i][j] == 3 && (state ==  0 || state == 2)){
                        state += 1;
                    }
                    if(x_m2_ext[i][j] == 2){
                        if(state == 0){
                            state = 2;
                        }else if(state == 1){
                            state = 3;
                        }
                    }
                    if(state == 3 && x_m1_ext[i][j] == 9 && x_m2_ext[i][j] == 9){
                        state = 4;
                    }

                    x_m3_ext[i][j] = x_m1_ext[i][j];
                    x_m4_ext[i][j] = x_m2_ext[i][j];
                    *//*r_m[i][j] = x_m_ext[i][j];*//*
                    if(state == 1 || state ==3){
                        x_m3_ext[i][j] += 10;
                    }
                    if(state == 2|| state ==3){
                        x_m4_ext[i][j] += 10;
                    }
                   *//* if(state == 1){
                        r_m[i][j] += 10;
                    }
                    if(state == 2){
                        r_m[i][j] += 20;
                    }
                    if(state ==3){
                        r_m[i][j] += 30;
                    }*//*
                    if(state == 4){
                        x_m3_ext[i][j] += 20;
                        x_m4_ext[i][j] += 20;

                        wins +=1;
                    }*/
                    if(state == 2 && x_m1_ext[i][j] == 7){
                        won = 1;
                        state = 3;
                        x_m4_ext[i][j] += 20;
                    }
                    if(state == 1 && x_m2_ext[i][j] == 2){
                        printf("hereeee\n");
                        state = 2;
                        x_m5_ext[i][j] += 20;
                        x_m4_ext[i][j] += 10;
                    }
                    if(state == 0 && x_m3_ext[i][j] == 3){
                        state = 1;
                        x_m6_ext[i][j] += 20;
                        x_m5_ext[i][j] += 10;
                    }
                }
                wins += won;
            }


            printf("Win rate: %f\n", (double) wins / seq);


            SP_est1 = (double **) malloc(10 * sizeof(double *));
            SE_est1 = (double **) malloc(10 * sizeof(double *));

            for (int i = 0; i < 10; i++) {
                SP_est1[i] = (double *) malloc(10 * sizeof(double));
                SE_est1[i] = (double *) malloc(10 * sizeof(double));
                for (int j = 0; j < 10; j++) {
                    SP_est1[i][j] = 1.0;
                }
                for (int j = 0; j < 10; j++) {
                    SE_est1[i][j] = grid_MDP->E_true[i][j];
                }
            }

            printf("here\n");

            SP_est2 = (double **) malloc(10 * sizeof(double *));
            SE_est2 = (double **) malloc(10 * sizeof(double *));

            for (int i = 0; i < 10; i++) {
                SP_est2[i] = (double *) malloc(10 * sizeof(double));
                SE_est2[i] = (double *) malloc(10 * sizeof(double));
                for (int j = 0; j < 10; j++) {
                    SP_est2[i][j] = 1.0;
                }
                for (int j = 0; j < 10; j++) {
                    SE_est2[i][j] = grid_MDP->E_true[i][j];
                }
            }

            printf("here\n");

            SP_est3 = (double **) malloc(10 * sizeof(double *));
            SE_est3 = (double **) malloc(10 * sizeof(double *));

            for (int i = 0; i < 10; i++) {
                SP_est3[i] = (double *) malloc(10 * sizeof(double));
                SE_est3[i] = (double *) malloc(10 * sizeof(double));
                for (int j = 0; j < 10; j++) {
                    SP_est3[i][j] = 1.0;
                }
                for (int j = 0; j < 10; j++) {
                    SE_est3[i][j] = grid_MDP->E_true[i][j];
                }
            }

            /*SP_est3 = (double **) malloc(729 * sizeof(double *));
            SE_est3 = (double **) malloc(729 * sizeof(double *));
            VEC2D(double) ident = Identity(729);
            for (int i = 0; i < 729; i++) {
                SP_est3[i] = (double *) malloc(729 * sizeof(double));
                SE_est3[i] = (double *) malloc(729 * sizeof(double));
                for (int j = 0; j < 729; j++) {
                    SP_est3[i][j] = 1.0;
                }
                for (int j = 0; j < 729; j++) {
                    SE_est3[i][j] = ident[i][j];
                }
            }*/
            VEC(int) params_MDP = {10, 10, n, seq};
            printf("here\n");
            hmm_MDP1 = new HMM_multi(P, grid_MDP->E_true, tol, maxIt, params_MDP);
            double l_MDP1 = hmm_MDP1->run(SP_est1, SE_est1, x_m1_ext, 1, 1);
            printf("Log likelihood for spatial MDP1: %f\n", l_MDP1);
            hmm_MDP2 = new HMM_multi(P, grid_MDP->E_true, tol, maxIt, params_MDP);
            double l_MDP2 = hmm_MDP2->run(SP_est2, SE_est2, x_m2_ext, 1, 1);
            printf("Log likelihood for spatial MDP2: %f\n", l_MDP2);
            hmm_MDP3 = new HMM_multi(P, grid_MDP->E_true, tol, maxIt, params_MDP);
            double l_MDP3 = hmm_MDP2->run(SP_est3, SE_est3, x_m3_ext, 1, 1);
            printf("Log likelihood for spatial MDP2: %f\n", l_MDP3);
         /*   VEC(int) params_MDP3 = {729, 729, n, seq};
            hmm_MDP5 = new HMM_multi(P, ident, tol, maxIt, params_MDP3);

            double l_MDP5 = hmm_MDP5->run(SP_est3, SE_est3, x_m_ext, 1, 1);
            printf("Log likelihood for spatial MDP1: %f\n", l_MDP5);*/

            int N_init = 10 * 3;
            /*int N_init2 = 729 * 5;*/
            // VEC2D(double) SP_init(N_init, VEC(double)(N_init,init_P_est/(N_init-4)));

            SP_init1 = (double **) malloc(N_init * sizeof(double *));
            SP_init2 = (double **) malloc(N_init * sizeof(double *));
            SP_init3 = (double **) malloc(N_init * sizeof(double *));
            for (int i = 0; i < N_init; i++) {
                SP_init1[i] = (double *) malloc(N_init * sizeof(double));
                SP_init2[i] = (double *) malloc(N_init * sizeof(double));
                SP_init3[i] = (double *) malloc(N_init * sizeof(double));
                for (int j = 0; j < N_init; j++) {
                    SP_init1[i][j] = init_P_est/(N_init-4);
                    SP_init2[i][j] = init_P_est/(N_init-4);
                    SP_init3[i][j] = init_P_est/(N_init-4);
                }
            }

         /*   SP_init3 = (double **) malloc(N_init2 * sizeof(double *));
            for (int i = 0; i < N_init2; i++) {
                SP_init3[i] = (double *) malloc(N_init2 * sizeof(double));
                for (int j = 0; j < N_init2; j++) {
                    SP_init3[i][j] = init_P_est/(N_init2-4);
                }
            }*/
            // Copy the estimated spatial MDP to an initial estimate of the product MDP
            for (int d = 0; d < 3; d++) {
                for (int i = 0; i < 10; i++) {
                    for (int j = 0; j < 10; j++) {
                        if (SP_est1[i][j] != 0.0) {
                            SP_init1[(d * 10) + i][(d * 10) + j] = SP_est1[i][j];
                        }
                        if (SP_est2[i][j] != 0.0) {
                            SP_init2[(d * 10) + i][(d * 10) + j] = SP_est2[i][j];
                        }
                        if (SP_est3[i][j] != 0.0) {
                            SP_init3[(d * 10) + i][(d * 10) + j] = SP_est3[i][j];
                        }
                    }
                }
            }

            /*for (int d = 0; d < 5; d++) {
                for (int i = 0; i < 729; i++) {
                    for (int j = 0; j < 729; j++) {
                        if (SP_est3[i][j] != 0.0) {
                            SP_init3[(d * 729) + i][(d * 729) + j] = SP_est3[i][j];
                        }
                    }
                }
            }*/

            VEC(double) sum1(N_init, 0.0);
            VEC(double) sum2(N_init, 0.0);
            VEC(double) sum3(N_init, 0.0);
           /* VEC(double) sum3(N_init2, 0.0);*/

            // Normalise entries
            for (int i = 0; i < N_init; i++) {
                //Sum each row
                for (int j = 0; j < N_init; j++) {
                    sum1[i] += SP_init1[i][j];
                    sum2[i] += SP_init2[i][j];
                    sum3[i] += SP_init3[i][j];
                }
                //Normalise row
                for (int j = 0; j < N_init; j++) {
                    SP_init1[i][j] = SP_init1[i][j] / sum1[i];
                    SP_init2[i][j] = SP_init2[i][j] / sum2[i];
                    SP_init3[i][j] = SP_init3[i][j] / sum3[i];

                }
            }

           /* for (int i = 0; i < N_init2; i++) {
                //Sum each row
                for (int j = 0; j < N_init2; j++) {
                    sum3[i] += SP_init3[i][j];
                }
                //Normalise row
                for (int j = 0; j < N_init2; j++) {
                    SP_init3[i][j] = SP_init3[i][j] / sum3[i];
                }
            }*/
            VEC2D(double) I = Identity(10);
            VEC2D(double) kron_arg(3, VEC(double)(2, 0.0));
            for (int i = 0; i < 3- 1; i++) {
                kron_arg[i][0] = 1;
            }
          /*  VEC2D(double) kron_arg2(5, VEC(double)(2,0.0));
            for (int i = 0; i < 5- 1; i++) {
                kron_arg2[i][0] = 1;
            }*/
            kron_arg[3 - 1][1] = 1;
            /*kron_arg2[4][1] = 1;*/
            E_true = KroneckerProduct(kron_arg, I, 3, 2, 10, 10);
           /* E_true2 = KroneckerProduct(kron_arg2, ident, 5,2,729,729);*/
            E_est = (double **) malloc(30 * sizeof(double *));
            for(int i=0; i<30; i++){
                E_est[i] = (double *) malloc(20 * sizeof(double));
                for(int j=0; j<20; j++){
                    E_est[i][j] = E_true[i][j];
                }
            }
           /* printf("GOT HERE BOYSSSSSSSSSSSSSSSSSS \n");
            E_est2 = (double **) malloc(500 * sizeof(double *));
            for(int i=0; i<500; i++){
                E_est2[i] = (double *) malloc(200 * sizeof(double));
                for(int j=0; j<200; j++){
                    E_est2[i][j] = E_true2[i][j];
                }
            }*/
            for (int i = 0; i < seq; i++) {
                for (int j = 0; j < n + 1; j++) {
                    y_m_1[i][j] = randm(E_true[x_m4_ext[i][j]]);
                }
            }
            for (int i = 0; i < seq; i++) {
                for (int j = 0; j < n + 1; j++) {
                    y_m_2[i][j] = randm(E_true[x_m5_ext[i][j]]);
                }
            }
            for (int i = 0; i < seq; i++) {
                for (int j = 0; j < n + 1; j++) {
                    y_m_3[i][j] = randm(E_true[x_m6_ext[i][j]]);
                }
            }
            /*for (int i = 0; i < seq; i++) {
                for (int j = 0; j < n + 1; j++) {
                    y_m[i][j] = randm(E_true2[r_m[i][j]]);
                }
            }*/

            VEC(int) params_MDP2 = {30, 20, n, seq};

            hmm_MDP4 = new HMM_multi(P, E_true, tol, maxIt, params_MDP2);
            printf("loaded HMM\n");
            hmm_MDP4->run(SP_init1, E_est,y_m_1, 0, 1);
            hmm_MDP5 = new HMM_multi(P, E_true, tol, maxIt, params_MDP2);
            printf("loaded HMM\n");
            hmm_MDP5->run(SP_init2, E_est,y_m_2, 0, 1);
            hmm_MDP6 = new HMM_multi(P, E_true, tol, maxIt, params_MDP2);
            printf("loaded HMM\n");
            hmm_MDP6->run(SP_init3, E_est,y_m_3, 0, 1);
            /*VEC(int) params_MDP4 = {500, 200, n, seq};

            hmm_MDP6 = new HMM_multi(P, E_true2, tol, maxIt, params_MDP4);
            printf("loaded HMM\n");
            hmm_MDP6->run(SP_init3, E_est2,y_m, 0, 1);*/


            FILE *f1 = (FILE *) fopen("agent1_run1.txt", "w");

            // fopen("spatial_MDP_est.txt", "w");
            for (int i = 0; i < N_init; i++) {
                for (int j = 0; j < N_init; j++) {
                    fprintf(f1, "%f ", SP_init1[i][j]);
                }
                if (i < N_init - 1) {
                    fprintf(f1, "\n");
                }
            }
            fclose(f1);

            FILE *f2 = (FILE *) fopen("agent2_run2.txt", "w");

            // fopen("spatial_MDP_est.txt", "w");
            for (int i = 0; i < N_init; i++) {
                for (int j = 0; j < N_init; j++) {
                    fprintf(f2, "%f ", SP_init2[i][j]);
                }
                if (i < N_init - 1) {
                    fprintf(f2, "\n");
                }
            }
            fclose(f2);
            FILE *f3 = (FILE *) fopen("agent3_run2.txt", "w");

            // fopen("spatial_MDP_est.txt", "w");
            for (int i = 0; i < N_init; i++) {
                for (int j = 0; j < N_init; j++) {
                    fprintf(f3, "%f ", SP_init3[i][j]);
                }
                if (i < N_init - 1) {
                    fprintf(f3, "\n");
                }
            }
            fclose(f3);

            // printf("File written\n");

            //close file

            //printf("Spatial MDP estimated\n");
            //delete(grid_MDP);
        }else if(mode == 1){
            grid_MDP = new Example(grid_type, DFA_states, mode);
            N = grid_MDP->N;
            M = grid_MDP->M;
            VEC(int) params_MDP = {N,M,n,seq};


            N_init = N * DFA_states;
            SP_init = (double **) malloc(N_init*sizeof(double *));
            for(int i=0; i < N_init; i++){
                SP_init[i] = (double *) malloc(N_init*sizeof(double));
                for(int j=0; j < N_init; j++){
                    SP_init[i][j] = init_P_est/(N_init-4);
                }
            }

            // Initialise estimates
            SP_est = (double **) malloc(N * sizeof(double *));
            SE_est = (double **) malloc(N * sizeof(double *));

            for(int i=0; i<N; i++){
                SP_est[i] = (double *) malloc(N * sizeof(double));
                SE_est[i] = (double *) malloc(M * sizeof(double));
                for(int j=0; j<N; j++){
                    SP_est[i][j] = 1.0;
                }
                for(int j=0; j<M; j++){
                    SE_est[i][j] = grid_MDP->E_true[i][j];
                }
            }
            printf("------------------------------------------------------------------------------------");
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    printf("%f ", SP_est[i][j]);
                }
                if(i<N-1){
                    printf("\n");
                }
            }
            printf("------------------------------------------------------------------------------------");

            hmm_MDP = new HMM(grid_MDP->P,grid_MDP->E_true,tol,maxIt,params_MDP);
            learn_spatial_MDP(grid_type, DFA_states, n, seq, maxIt, tol, init_P_est, hmm_MDP, SP_init);

            // free allocated objects
            for(int i=0; i<N_init; i++){
                free(SP_init[i]);
            }
            free(SP_init);
            // printf("SP_init freed\n");
            for(int i=0; i<N; i++){
                free(SP_est[i]);
                free(SE_est[i]);
            }
            free(SP_est);
            free(SE_est);
            // printf("SP_est freed\n");
            delete(hmm_MDP);
            // printf("hmm_MDP freed\n");
            delete(grid_MDP);
            // printf("grid_MDP freed\n");
        }
        else{

        // Create example
        grid = new Example(grid_type, DFA_states, 0);
        N = grid->N;
        M = grid->M;

        VEC(int) params = {N,M,n,seq};
        
        // printf("Initialising guesses\n");

        printf("DFA states: %d\n", DFA_states);
        printf("init_P_est: %f\n", init_P_est);
        
        // Initialise estimates
        P_est = (double **) malloc(N * sizeof(double *));
        E_est = (double **) malloc(N * sizeof(double *));

        for(int i=0; i<N; i++){
            P_est[i] = (double *) malloc(N * sizeof(double));
            E_est[i] = (double *) malloc(M * sizeof(double));
            double sum = 0.0;
            for(int j=0; j<N; j++){
                if(grid->P_init[i][j] > 0){
                    P_est[i][j] = grid->P_init[i][j];
                }
                else{
                    P_est[i][j] = init_P_est/(N-4);
                }
                sum += P_est[i][j];
            }
            // Normalise probabilities
            for(int j=0; j<N; j++){
                P_est[i][j] /= sum;
            }         
            for(int j=0; j<M; j++){
                E_est[i][j] = grid->E_true[i][j];
            }
        }

        printf("Initializing HMM\n");
        //Run HMM
        printf("tol: %f\n", tol);
        if(mode == 1){
            hmm = new HMM(grid->P,grid->E_true,tol,maxIt,params,"spatial_MDP_est.txt");
        }
        else{
            hmm = new HMM(grid->P,grid->E_true,tol,maxIt,params,filename);
        }
        
        // printf("Running HMM\n");
        int uniform = 0;
        if(init_P_est == 0.0 && mode == 0){
            uniform = 1;
        }
        double l = hmm->run(P_est,E_est,uniform,0);
        printf("Log likelihood: %f\n", l);
        
        delete(hmm);
        for(int i=0; i<N; i++){
            free(P_est[i]);
            free(E_est[i]);
        }
        free(P_est);
        free(E_est);
        delete(grid);

        }

        return;
    }
    
    void learn_spatial_MDP(int grid_type=3, int DFA_states=3, int n = 34, int seq = 275, int maxIt = 25000, double tol = 1e-6, double init_P_est = 1.0, HMM * hmm_MDP = NULL, double ** SP_init = NULL){
        // Create example
        // N = grid_MDP->N;
        // M = grid_MDP->M;

        VEC(int) params = {N,M,n,seq};
        
        printf("Learning spatial MDP\n");

        // Run HMM learning with uniform prior to learn the spatial MDP
        double l_MDP = hmm_MDP->run(SP_est,SE_est,1,1);
        printf("Log likelihood for spatial MDP: %f\n", l_MDP);

        // Copy learnt spatial MDP but add small probabilities to zero entries
        int N_init = N * DFA_states;
        // VEC2D(double) SP_init(N_init, VEC(double)(N_init,init_P_est/(N_init-4)));
        VEC(double) sum(N,0.0);

        // Copy the estimated spatial MDP to an initial estimate of the product MDP
        for(int d=0; d<DFA_states; d++){
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    if(SP_est[i][j] != 0.0){
                        SP_init[(d*N)+i][(d*N)+j] = SP_est[i][j];
                    }
                }
            }
        }

        // printf("Estimated spatial MDP copied\n");

        // Normalise entries
        for(int i=0; i<N_init; i++){
            //Sum each row
            for(int j=0; j<N_init; j++){
                sum[i] += SP_init[i][j];
            }
            //Normalise row
            for(int j=0; j<N_init; j++){
                SP_init[i][j] = SP_init[i][j] / sum[i];
            }
        }

        // printf("Entries normalised\n");

        // write P_est to file
        FILE * f = (FILE *) fopen("spatial_MDP_est.txt","w");
        
        // fopen("spatial_MDP_est.txt", "w");
        for(int i=0; i<N_init; i++){
            for(int j=0; j<N_init; j++){
                fprintf(f, "%f ", SP_init[i][j]);
            }
            if(i<N_init-1){
                fprintf(f, "\n");
            }
        }

        // printf("File written\n");

        // //close file
        fclose(f);
        printf("Spatial MDP estimated\n");
    }
private:
    Example * grid;
    int N;
    int M;
    double ** P_est;
    double ** E_est;
    double ** E_est2;
    HMM * hmm;
    // Spatial MDP variables
    double ** SP_init;
    double ** SP_init1;
    double ** SP_init2;
    double ** SP_init3;
    double ** SP_est;
    double ** SE_est;
    double ** SP_est1;
    double ** SE_est1;
    double ** SP_est2;
    double ** SE_est2;
    double ** SP_est3;
    double ** SE_est3;
    HMM * hmm_MDP;
    HMM_multi * hmm_MDP1;
    HMM_multi * hmm_MDP2;
    HMM_multi * hmm_MDP3;
    HMM_multi * hmm_MDP4;
    HMM_multi * hmm_MDP5;
    HMM_multi * hmm_MDP6;
    Example * grid_MDP;
    int ** x_m;
    int ** x_m1;
    int ** x_m2;
    int ** x_m3;
    int ** x_m_ext;
    int ** x_m1_ext;
    int ** x_m2_ext;
    int ** x_m3_ext;
    int ** x_m4_ext;
    int ** x_m5_ext;
    int ** x_m6_ext;
    int ** r_m;
    int ** y_m_1;
    int ** y_m_2;
    int ** y_m_3;
    int ** y_m_ext;
    int ** y_m;
    int ** L;
    VEC2D(double) E_true;
    VEC2D(double) E_true2;
};

#endif // BENCHMARK_H