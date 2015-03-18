#include <vector>

using namespace std;

/* box stacking :h x w x d boxes
  maybe more of one type
  the question is to build highest tower
  we assume that in the input we already have every box stored
  in all three possible directions, always with w>d
*/
class box{
  public:
  int h; int w; int d;
  bool operator< (const box & b) const {
    return (w*d>b.w*b.d);
  }
};
int boxstacking(vector<box> & boxes) {
  sort(boxes.begin(), boxes.end()); //decreasing order
  vector<int> maxHeight(boxes.size()); //highest tower from first i boxes
  int bestHeight = 0;
  for(unsigned int i = 0; i<boxes.size(); i++) {
    for(unsigned int j = 0; j<i; j++) {
      if(boxes[j].w>boxes[i].w && boxes[j].d>boxes[i].d) {
        maxHeight[i] = max(maxHeight[i], maxHeight[j]);
      }
    }
    maxHeight[i] += boxes[i].h;
    bestHeight = max(bestHeight, maxHeight[i]);
  }
  return bestHeight;
}
