#pragma once
using namespace std;

const int n = 320; //x of the map
const int m = 180; //y of the map
static int map[n][m]; //use map cause x and y graph has 2 axis
static int closed_nodes_map[n][m]; // map of checked nodes
static int open_nodes_map[n][m]; // map of not tried nodes
static int dir_map[n][m]; // map of directions
const int dir = 8; // this is the number of possible directions to go to at any position, can be 4
static int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 }; // direction x axis
static int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 }; // direction y axis

class node
{
private:
	//current position
	int xPos;
	int yPos;
	// the total distance alr travelled to reach the node
	int level;
	// priority = level + remaining distance estimate (ALSO KNOWN AS THE HEURISTICS)
	int priority; //obv, smaller means higher priority due to lower cost

public:
	//intialization... obviously..
	node(int xp, int yp, int d, int p);
	//getters
	int getxPos() const { return xPos; }
	int getyPos() const { return yPos; }
	int getLevel() const { return level; }
	int getPriority() const { return priority; }

	//update priority of the thingy, which is the estimation of distance between start and end + the cost it takes to reach that node from the prev
	void updatePriority(const int & xDest, const int & yDest);

	// give better priority to going strait instead of diagonally
	void nextLevel(const int & i); // i: direction

	// Estimation function for the remaining distance to the goal.
	const int & estimate(const int & xDest, const int & yDest) const;
};

bool operator<(const node & a, const node & b);
string pathFind(const int & xStart, const int & yStart, const int & xFinish, const int & yFinish);
string initializePathFind(const int & xs, const int & ys, const int & xf, const int & yf);