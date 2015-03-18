#include <vector>
using namespace std;

//0-1 Knapsack problem
int knapsack01(vector<int> &values, vector<int> & weights, int K) { //K: max capacity
  //optValue[i][w] : max value if weight must be at most w and we may choose from first i objects
  vector<vector<int> > optValue(values.size()+1, vector<int> (K+1,0));
  for(unsigned int i = 1; i <= values.size(); i++) {
    for(int w = 1; w <= K; w++) {
      optValue[i][w] = optValue[i-1][w];
      if(weights[i-1] <= w ) {
        optValue[i][w] = max(optValue[i][w], values[i-1] + optValue[i-1][w-weights[i-1]]);
      }
    }
  }
  return optValue[values.size()][K];
}

//multiple knapsack problem: we have any number of each object
int knapsack(vector<int> &values, vector<int> & weights, int K) {
  //optValue[w] max value of knapsack with at most w weight
  vector<int> optValue(K+1);
  for(int w = 1; w <= K; w++) {
    optValue[w] = optValue[w-1];
    for(unsigned int j = 0; j<values.size(); j++) {
      if(weights[j] <= w) {
        optValue[w] = max(optValue[w], optValue[w-weights[j]]+values[j]);
      }
    }
  }
  return optValue[K];
}

//subset sum / balanced partition problem
void subsetsum(vector<int> & A) { //currently works only for nonnegative elements
  int K = 0;
  for(unsigned int i = 0; i<A.size(); i++) { K += A[i];}
  bool P[A.size()+1][K+1]; //P[i][j] true iff j is a possible sum from first i elements
  for(unsigned int i = 0; i<=A.size(); i++) {
    for(int j = 0; j<=K; j++) {
      P[i][j] = false;
      if(j==0) {
        P[i][j] = true;
      }else if (i>=1 && P[i-1][j]) {
        P[i][j] = true;
      }else if (i>=1 && A[i-1] <= 0 && P[i-1][j-A[i-1]]) {
        P[i][j] = true;
      }
    }
  }
}

//coin change: minimum number of coins needed
int coinChange(vector<unsigned int> & coins, unsigned int sumToPay) {
  vector<int> minCoins(sumToPay+1);
  for(unsigned int i = 1; i<=sumToPay; i++) {
    minCoins[i] = i;
    for(unsigned int j = 0; j<coins.size(); j++) {
      if(coins[i]<=j) {
        minCoins[i] = min(minCoins[i], minCoins[j-coins[i]]+1);
      }
    }
  }
  return minCoins[sumToPay];
}

//number of possible ways to pay sum
int numChange(vector<int> & coins, int sumToPay) {
  // M[i][j]: number of ways to pay j with first i type of coins
  vector<vector<int> > M(coins.size(), vector<int> (sumToPay+1) );
  for(unsigned int i = 0; i<coins.size(); i++) {
    for(int j = 0; j<=sumToPay; j++) {
      if(i==0) {
        M[i][j] = j; M[0][0] = 1;
      }else {
        for(int k = 0; k*coins[i] <= j; k++) {
          M[i][j] += M[i-1][j-k*coins[i]];
        }
      }
    }
  }
  return M[coins.size()-1][sumToPay];
}
