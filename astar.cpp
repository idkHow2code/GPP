#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <cmath>
#include "astar.h"

using namespace std;



	//intialization... obviously..
	node::node(int xp, int yp, int d, int p)
	{
		xPos = xp; yPos = yp; level = d; priority = p;
	}
	//getters

	//update priority of the thingy, which is the estimation of distance between start and end + the cost it takes to reach that node from the prev
	void node::updatePriority(const int & xDest, const int & yDest)
	{
		priority = level + estimate(xDest, yDest) * 10;
	}

	// give better priority to going strait instead of diagonally
	void node::nextLevel(const int & i) // i: direction
	{
		level += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
	}

	// Estimation function for the remaining distance to the goal.
	const int & node::estimate(const int & xDest, const int & yDest) const
	{
		static int xd, yd, d;
		xd = xDest - xPos;
		yd = yDest - yPos;

		// Euclidian Distance, diagonal works
		d = static_cast<int>(sqrt(xd*xd + yd*yd));


		return(d);
	}

// reverse priority lower cost = higher on list
bool operator<(const node & a, const node & b)
{
	return a.getPriority() > b.getPriority();
}

string pathFind(const int & xStart, const int & yStart, const int & xFinish, const int & yFinish)
{
	static priority_queue<node> pq[2]; // <-the list of not yet searched nodes
	static int pqi; //priority q index
	static node* n0; //node 0 @ x
	static node* m0; //node 0 @ y
	static int i, j, x, y, xdx, ydy;
	static char c;
	pqi = 0;

	//resetting the node map
	for (y = 0; y < m; y++)
	{
		for (x = 0; x < n; x++)
		{
			closed_nodes_map[x][y];
			open_nodes_map[x][y];
		}
	}

	//create the start node and push it into the list of open nodes (not yet searched)
	n0 = new node(xStart, yStart, 0, 0); //level travelled will be 0 when initialized starting node cause obv it hasnt travelled anywhere yet
	n0->updatePriority(xFinish, yFinish);  //update priority (cost) of node
	pq[pqi].push(*n0); // pushes the nodes into the list of not yet searched nodes
	open_nodes_map[x][y] = n0->getPriority(); //this marks it       

	while (!pq[pqi].empty())
	{
		// get the current node w/ the highest priority lowest number!!
		// from the list of open nodes
		n0 = new node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(), pq[pqi].top().getLevel(), pq[pqi].top().getPriority());
		x = n0->getxPos();
		y = n0->getyPos();
		pq[pqi].pop(); // remove the node from the open list
		open_nodes_map[x][y] = 0;
		closed_nodes_map[x][y] = 1;

		// quit searching when the goal state is reached
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if (x == xFinish && y == yFinish)
		{
			// generate the path from finish to start
			// by following the directions
			string path = "";
			while (!(x == xStart && y == yStart))
			{
				j = dir_map[x][y];
				c = '0' + (j + dir / 2) % dir;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}

			// garbage collection
			delete n0;
			// empty the leftover nodes
			while (!pq[pqi].empty()) pq[pqi].pop();
			return path;
		}
		// generate moves (child nodes) in all possible directions
		for (i = 0; i<dir; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx>n - 1 || ydy<0 || ydy>m - 1 || map[xdx][ydy] == 1
				|| closed_nodes_map[xdx][ydy] == 1))
			{
				// generate a child node
				m0 = new node(xdx, ydy, n0->getLevel(),
					n0->getPriority());
				m0->nextLevel(i);
				m0->updatePriority(xFinish, yFinish);

				// if it is not in the open list then add into that
				if (open_nodes_map[xdx][ydy] == 0)
				{
					open_nodes_map[xdx][ydy] = m0->getPriority();
					pq[pqi].push(*m0);
					// mark its parent node direction
					dir_map[xdx][ydy] = (i + dir / 2) % dir;
				}
				else if (open_nodes_map[xdx][ydy]>m0->getPriority())
				{
					// update the priority info
					open_nodes_map[xdx][ydy] = m0->getPriority();
					// update the parent direction info
					dir_map[xdx][ydy] = (i + dir / 2) % dir;

					// replace the node
					// by emptying one pq to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while (!(pq[pqi].top().getxPos() == xdx &&
						pq[pqi].top().getyPos() == ydy))
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop(); // remove the wanted node

								   // empty the larger size pq to the smaller one
					if (pq[pqi].size()>pq[1 - pqi].size()) pqi = 1 - pqi;
					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0); // add the better node instead
				}
				else delete m0; // garbage collection
			}
		}
		delete n0; // garbage collection
	}
	return ""; // no route found
}

string initializePathFind(const int & xs, const int & ys, const int & xf, const int & yf)
{
	//create empty map
	for (int y = 0; y<m; y++)
	{
		for (int x = 0; x<n; x++) map[x][y] = 0;
	}
	// fillout the map matrix with a '+' pattern
	for (int x = n / 8; x<n * 7 / 8; x++)
	{
		map[x][m / 2] = 1;
	}
	for (int y = m / 8; y<m * 7 / 8; y++)
	{
		map[n / 2][y] = 1;
	}

	string route = pathFind(xs, ys, xf, yf);
	return route;

}