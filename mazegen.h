
#ifndef _MAZE_H_
#define _MAZE_H_

#include <vector>
#include "disjointsets.h"
#include <stdio.h>    
#include <stdlib.h>    
#include <time.h>
#include "png.h" 
#include <stack>  
using std::vector;
using std::stack;
class MazeGen
{
	public :
	void generate(int width,int height);
	bool validStep(int x,int y,int dir)const;
	PNG *drawUnsolved()const;	
	void makeWall(int x,int y,int dir,bool exists);
	vector< int > findPath();
	PNG * drawSolved();


	private:
	class cell
	{
	public:
	bool rightexists;
	bool downexists;
	cell();		
	};
	int mazewidth;
	int mazeheight;
	size_t destx;
	size_t desty;
	vector<cell> mymaze;
	DisjointSets myset;



};
#endif


