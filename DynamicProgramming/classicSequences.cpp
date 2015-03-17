#include <vector>
#include <algorithm>

using namespace std;

//longest strictly increasing subsequence in O(nlogn)
vector<int> lis(vector<int> & A) 
{
	vector<int> indexes; //jth element: index of currently known smallest element at the end of a j long IS
	vector<int> previous(A.size()); //index of previous element of LIS ending at A[k]
	int u, v; //endpoints of binary search
  indexes.push_back(0);

	for (unsigned int i = 1; i < A.size(); i++) {
      if (A[indexes.back()] < A[i]) {
        previous[i] = indexes.back();
        indexes.push_back(i);
        continue;
      }
      // Binary search to find the smallest element referenced by indexes which is not smaller than A[i]
      //current element can be placed after before this
      for (u = 0, v = indexes.size()-1; u < v;) {
        int c = (u + v) / 2;
        if (A[indexes[c]] < A[i]) { u = c+1; }
        else { v = c;}
      }
      // Update iff new element would be a smaller last element 
      if (A[i] < A[indexes[u]]) {
        if (u > 0) {previous[i] = indexes[u-1];}
        indexes[u] = i;
      }
  }
  //read LIS from vector of predecessors
	for (u = indexes.size(), v = indexes.back(); u--; v = previous[v]) {indexes[u] = v;}
	return indexes;
}

//max sum continuous subsequence: modifies the input sequence!
int mscs(vector<int> & A) {
  int result = max(0,A[0]);
  for(unsigned int i = 1; i<A.size(); i++) {
    A[i] = max(A[i], A[i]+A[i-1]);
    result = max(result,A[i]);
  }
  return result;
}

//max sum continous subsequence with indices
pair<int,int> MSCS(vector<int> & A) {
  int leftIndex = -1; int rightIndex = -1; 
  int currLeftIndex = -1;
  int result = 0;
  if(A[0]>result) {
  	result = A[0];
  	leftIndex = 0; rightIndex = 0; currLeftIndex = 0;
  }
  for(unsigned int i = 1; i<A.size(); i++) {
    if(A[i-1]>0) {A[i] += A[i-1]; }
    if(A[i-1]<=0) {currLeftIndex = i;}
    if(A[i]>result) {result = A[i]; rightIndex = i; leftIndex = currLeftIndex;}
  }
  //returns (-1,-1) if every element is nonpositive
  return make_pair(leftIndex,rightIndex);
}

//longest common subsequence
int lcs(vector<int> & A, vector<int> & B) {
  int L[A.size()+1][B.size()+1]; //L[i][j]: lcs in A[0..i-1] and B[0..j-1]
  for(unsigned int i = 0; i <= A.size(); i++) {
    for(unsigned int j = 0; j <= B.size(); j++) {
      if(i == 0 || j == 0) {
      	L[i][j]=0;
      }else if (A[i-1] == B[j-1]) {
      	L[i][j] = L[i-1][j-1]+1;
      }else {
      	L[i][j] = max(L[i-1][j],L[i][j-1]); 
      }
    }
  }
  return L[A.size()][B.size()];
}

//edit distance of two words (e.g. DNA sequences)
int editDistance(string & A, string & B, int insertionCost, int replacementCost, int deletionCost) {
  int T[A.size()+1][B.size()+1]; //min cost to transform A[0..i-1] to B[0..j-1]
  for(unsigned int i = 0; i <= A.size(); i++) {
    for(unsigned int j = 0; j <= B.size(); j++) {
      if(i == 0 && j == 0) {
      	T[i][j]=0;
      }else if (i==0) {
      	T[i][j] = T[i][j-1] + insertionCost;
      }else if (j==0) {
      	T[i][j] = T[i-1][j] + deletionCost;
      }else if (A[i-1]==B[j-1]) {
      	T[i][j] = T[i-1][j-1];
      }else {
      	T[i][j] = min(min(T[i-1][j-1] + replacementCost, T[i][j-1] + insertionCost), T[i-1][j] + deletionCost);
      }
    }
  }
  return T[A.size()][B.size()];
}

//max sum subrectangle in O(N^2*M)
int maxSumSubRectangle(vector<vector<int> > & A) {
  int result = 0;
  for(unsigned int i = 0; i<A.size(); i++) { //index of top row
    vector<int> t(A[0].size());
    for(unsigned int j = i; j<A.size(); j++) { //index of bottom row
      for(unsigned int k = 0; k<A[0].size(); k++) {
        t[k] += A[j][k];
      }
      //mscs(t) selects the best column interval for this choice of rows
      result = max(mscs(t),result);
    }
  }
  return result;
}
