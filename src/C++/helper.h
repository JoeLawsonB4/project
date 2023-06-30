/*
 * Helper functions for LTA_cpp
*/

#ifndef HELPER_H
#define HELPER_H

#include <vector>

using namespace std;

// Macros
#ifndef VEC
#define	VEC(type)	vector<type>
#endif

#ifndef VEC2D
#define	VEC2D(type)	vector<vector<type>>
#endif

#ifndef VEC3D
#define	VEC3D(type)	vector<vector<vector<type>>>
#endif

#ifndef MAX
#define	MAX(A, B)	((A) > (B) ? (A) : (B))
#endif

// Compute the Kronecker Product of two matrices 
static VEC2D(double) KroneckerProduct(VEC2D(double) A, VEC2D(double) B, int r_a, int c_a, int r_b, int c_b){ 
    // printf("Kronecker start\n");
    VEC2D(double) K(r_a * r_b, VEC(double)(c_a * c_b,0.0));
    // i loops till r_a 
    for (int i = 0; i < r_a; i++) {
        // j loops till c_a 
        for (int j = 0; j < c_a; j++) { 
            // k loops till r_b 
            for (int k = 0; k < r_b; k++) { 
                // l loops till c_b 
                for (int l = 0; l < c_b; l++) {
                    // Each element of matrix A is 
                    // multiplied by whole Matrix B 
                    // resp and stored as Matrix K
                    K[(i*(r_b)) + k][(j*(c_b)) + l] = A[i][j] * B[k][l];
                    if(K[(i*(r_b)) + k][(j*(c_b)) + l] < 0){
                        printf("a: %f b: %f i: %d j: %d k: %d l: %d\n", A[i][j], B[k][l], i, j, k, l);
                    }
                } 
            } 
        } 
    } 
    // printf("Kronecker done\n");
    return K;
} 

// Find largest element in 2D matrix
static int max_val(VEC2D(int) v, int idx){
    int max = v[0][idx];
    int rows = v.size();
    // int cols = v[0].size();
    for(int i = 0; i < rows; i++){
        max = MAX(v[i][idx],max);
        
    }   
    return max;
}

// Return grid coordinate as a single index
static int grid_coord(int s1, int s2, int row_length){
    return s2 + s1 * row_length;
}

/*
static int grid_coord_multi(int s1, int s2, int s3, int s4, int width, int height, int extraStates){
    return (((s1 * width) + s2) * ((width * height) + extraStates)) + (s3 * width) + s4;
}
*/





/*static int grid_coord_conversion(int s1, int s2, int s3, int s4, int width, int height, int grid_height, int label){
    return grid_coord_multi((s1 % grid_height) + (label * grid_height), s2, (s3 % grid_height) + (label * grid_height), s4, width, height);
}*/

/*static void update_grid(int coord, int i1, int j1, int i2, int j2, int i1_a, int j1_a, int i2_a, int j2_a, int width, int height, int grid_height, int label,
                        VEC2D(double)& P_chain){
    P_chain[grid_coord_multi(i1 + i1_a, j1 + j1_a, i2 + i2_a, j2 + j2_a, width, height)][grid_coord_conversion(i1, j1, i2, j2, width, height, grid_height, label)] = P_chain[grid_coord_multi(i1 + i1_a, j1 + j1_a, i2 + i2_a, j2 + j2_a, width, height)][coord];
    P_chain[grid_coord_multi(i1 + i1_a, j1 + j1_a, i2 + i2_a, j2 + j2_a, width, height)][coord] = coord == grid_coord_conversion(i1, j1, i2, j2, width, height, grid_height, label) ? P_chain[grid_coord_multi(i1 + i1_a, j1 + j1_a, i2 + i2_a, j2 + j2_a, width, height)][coord] : 0;

}*/

/*static int observation_conversion(int obs, int width, int height, int extraStates, int agent){
    int s1 = floor(obs/(static_cast<float>((width * height) + extraStates)));
    int s2 = obs - (s1 *((width * height) + extraStates));

    int result = (agent == 1) ? s1 : s2;
    return result;
}*/
int randm(VEC(double) p){
    int res=0;
    double q=p[0];
    double u = (rand()+0.0)/RAND_MAX;
    while(u>q){
        res++;
        q+=p[res];
    }
    return(res);
}

void HMMsample2agents(VEC2D(double)& P, VEC2D(double) E, int * x1, int * x2,  int * x3, int width, int height, int extraStates, int n){

    int k;
    // Sample first transition
    // (*x)[0] = randm(nu);
    // (*y)[0] = randm(E[(*x)[0]]);
    // (*x)[0] = randm(P[0]);
    // (*y)[0] = randm(E[(*x)[0]]);
    x1[0] = randm(P[0]);
    x2[0] = randm(P[0]);
    x3[0] = randm(P[0]);
    // Sample rest of transitions
    for(k=1; k<n; k++){
        x1[k] = randm(P[x1[k-1]]);
        x2[k] = randm(P[x2[k-1]]);
        x3[k] = randm(P[x3[k-1]]);
    }
    for(k=1; k<n; k++){
        if(x1[k] == 4 && x2[k] == 4 && x3[k] ==4){
            x1[k] = 9;
            x2[k] = 9;
            x3[k] = 9;
        }
    }



}

// Return n x n identity matrix
static VEC2D(double) Identity(int n){
    VEC2D(double) I(n, VEC(double)(n,0.0));
    for (int i = 0; i < n; i++){
        I[i][i] = 1.0;
    }
    return I;
}
#endif // HELPER_H