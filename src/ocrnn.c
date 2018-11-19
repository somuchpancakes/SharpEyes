#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "matrix/matrix.h"
#include "neural_net/nn.h"

#define saveFile "weights.se"

int main(){
  srand (time(NULL));

  /*int EPOCHS = 10000;

  if(argc == 2){
    EPOCHS = atoi(argv[1]);
  }*/
  /*
   * y = xor(X) = [[0],
   *               [1],
   *               [1],
   *               [0]]
   */
  Matrix y;
  initMatrix(&y, 4, 1, false);
  y.data[0].data[0] = 0.0;
  y.data[1].data[0] = 1.0;
  y.data[2].data[0] = 1.0;
  y.data[3].data[0] = 0.0;


  NN xorNet;
  xorNet.layers = 2;

  xorNet.weights = (Matrix *) calloc (xorNet.layers, sizeof(Matrix));
  xorNet.part_d = (Matrix *) calloc (xorNet.layers, sizeof(Matrix));

  printf("loading Weights in %s\n", saveFile);

  loadWeights(&xorNet, saveFile);

  //initMatrix(&xorNet.weights[0], 2, 4, true);
  //initMatrix(&xorNet.weights[1], 4, 1, true);

  

  printf("---------Output---------\n");

  Matrix x;
  initMatrix(&x, 1, 2, false);
  x.data[0].data[0] = 0.0;
  x.data[0].data[1] = 0.0;
  printf("Xor(0, 0) = %lf ( expected : %lf )\n", forward(xorNet, x).data[0].data[0], y.data[0].data[0]);

  x.data[0].data[0] = 1.0;
  x.data[0].data[1] = 0.0;
  printf("Xor(1, 0) = %lf ( expected : %lf )\n", forward(xorNet, x).data[0].data[0], y.data[1].data[0]);

  x.data[0].data[0] = 0.0;
  x.data[0].data[1] = 1.0;
  printf("Xor(0, 1) = %lf ( expected : %lf )\n", forward(xorNet, x).data[0].data[0], y.data[2].data[0]);

  x.data[0].data[0] = 1.0;
  x.data[0].data[1] = 1.0;
  printf("Xor(1, 1) = %lf ( expected : %lf )\n", forward(xorNet, x).data[0].data[0], y.data[3].data[0]);

  freeMatrix(x);
  freeMatrix(y);

  freeNeuralNet(xorNet);

  return 0;
}
