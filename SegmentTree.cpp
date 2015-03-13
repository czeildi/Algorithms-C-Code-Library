#include <vector>
#include <fstream>

using namespace std;
/*This Segment Tree supports asking the sum of an interval.
  With small changes you can alter it to support other queries.*/
int intervalLength;
vector<int> baseInterval;
vector<int> treeNodeValues;

void initialize(string inputFileName) {
  ifstream in(inputFileName);
  in>>intervalLength;
  for(int i=0; i<intervalLength; i++) {
    int temp;
    in>>temp;
    baseInterval.push_back(temp);
  }
  /*For simplicity, we always use the maximum length needed,
  if size is of the form 2^k+1, we need an array of size almost
  4*length*/
  treeNodeValues.resize(4*intervalLength,0);
}
//'right' points to one place after the right end of the current interval
void build (int treeIndex=1, int left=0, int right=intervalLength) {
  if (left+1 == right) {
    treeNodeValues[treeIndex] = baseInterval[left];
    return;
  }
  int middle = (left+right)/2;
  build(treeIndex*2, left, middle);
  build (treeIndex*2+1, middle, right);
  treeNodeValues[treeIndex] = treeNodeValues[treeIndex*2] + treeNodeValues[treeIndex*2+1];
}
/*'left' and 'right' correspond to the endpoints of the interval
  we are currently processing */
int query(int treeIndex, int queryLeft, int queryRight, int left, int right){
  if(queryLeft == left && queryRight == right) {
    return treeNodeValues[treeIndex];
  }
  int middle = (left+right)/2;
  int partialAnswer = 0;
  if (left < middle) {
    partialAnswer += query(treeIndex*2, queryLeft, min(middle,queryRight), left, middle);
  }
  if (middle < right) {
    partialAnswer += query(treeIndex*2+1, max(queryLeft,middle), queryRight, middle, right);
  }
  return partialAnswer;
}
/* 'left' and 'right' correspond to the interval at the current tree node */
void update(int index, int value, int treeIndex = 1, int left = 0, int right = intervalLength) {
  if(left +1 == right ) {
    baseInterval[index] = value;
    treeNodeValues[treeIndex] = value;
    return;
  }
  int middle = (left + right)/2;
  if (index<middle) {
    update(index, value, treeIndex*2, left, middle);
  }else {
    update(index,value, treeIndex*2+1, middle, right);
  }
  treeNodeValues[treeIndex] = treeNodeValues[treeIndex*2] + treeNodeValues[treeIndex*2+1];
}
