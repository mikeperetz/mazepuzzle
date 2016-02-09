
#include "mazegen.h"
MazeGen::cell::cell()
{
	rightexists=true;
	downexists=true;
}
void MazeGen::generate(int width, int height)
{
	int randcell,randwall;
	int size = width*height;
	int deletedwalls=0;
	mazewidth=width;
	mazeheight=height;	
	mymaze.clear();
	myset.remove();
	myset.insert(size);
	srand (time(NULL));

	for(int i=1;i<=size;i++)
	{
		cell a;	
		mymaze.push_back(a);
	}
	
	while(deletedwalls<size-1)
	{
		 randcell = rand() % size;
		 randwall = rand()%2; // 0 for rightwall, 1 for downwall
		 if(randwall==0) // rightwall
		 {
		 	if((randcell+1)%width!=0) //not last column
		 	{
				if(mymaze[randcell].rightexists==true && (myset.search(randcell)!= myset.search(randcell+1)))
				{
					mymaze[randcell].rightexists=false; // delete right wall
					myset.join(randcell,randcell+1);
					deletedwalls++;
				}
		 	}
		 }
		 if(randwall==1) // downwall
		 {
		 	if(randcell<(size-width)) //not last row
		 	{
				if(mymaze[randcell].downexists==true && (myset.search(randcell)!= myset.search(randcell+width)))
				{
					mymaze[randcell].downexists=false; // delete down wall
					myset.join(randcell,randcell+width);
					deletedwalls++;
				}
		 	}
		 }
	 }
}

bool MazeGen::validStep(int x,int y,int dir)	const
{
	int coord=x+(y*mazewidth); // invalid
	if(dir<0 || dir>3)
		return false;
	else if(dir==0) //right 
	{
		return !(mymaze[coord].rightexists);
	}
	else if(dir==1) // down
	{
		return !(mymaze[coord].downexists);	
	}

	else if(dir==2) //left
	{
		if(x%mazewidth==0)//first column
			return false;
		else return !(mymaze[coord-1].rightexists);
	}
	else //up
	{
		if(coord<mazewidth) //first row
			return false;
		else return !(mymaze[coord-mazewidth].downexists);
	}

}


PNG * MazeGen::drawUnsolved()const
{
	std::cout << "+   +";
	for (int j = 1; j < mazeheight; j++){
			std::cout << "---+";
		}
			std::cout << std::endl;

	for (int i = 0; i < mazewidth; i ++){

		std::cout << "|";

		for (int j = 0; j < mazeheight; j++){
			if (mymaze[i*mazewidth + j ].rightexists)
				std::cout << "   |";
			else
				std::cout<<"    ";
		}

		std::cout << std::endl;

		std::cout << "+";
		for (int j = 0; j < mazeheight; j++){
			if(mymaze[i*mazewidth + j ].downexists)
				std::cout << "---+";
			else
				std::cout << "   +";
		}

			std::cout << std::endl;

	}

	
	PNG *mazepic = new PNG((size_t) mazewidth*10+1, (size_t) mazeheight*10+1);
	RGBAPixel black(0,0,0);
	size_t x,y;
	*((*mazepic)(0,0))= black;
	for(size_t i =10;i< mazepic->width();i++)
		*((*mazepic)(i,0))= black;
	for(size_t j =0;j< mazepic->height();j++)
		*((*mazepic)(0,j))= black;
	for(size_t i =0; i< mymaze.size(); i++)
	{
		x= i%mazewidth;
		y= i/mazewidth;
		if (mymaze[i].rightexists)
		{
			for(size_t k=0;k<=10;k++)
			{
				*((*mazepic)((x+1)*10,y*10+k))=black;
			}
		}
		if (mymaze[i].downexists)
		{
			for(size_t k1=0;k1<=10;k1++)
			{
				*((*mazepic)(x*10+k1,(y+1)*10))=black;
			}
		}
	}
	return mazepic;
}


void MazeGen::makeWall(int x,int y,int dir,bool exists )
{
	int coord= x+(y*mazewidth);

		if(dir==0)
			mymaze[coord].rightexists=exists;
		else if(dir==1)
			mymaze[coord].downexists=exists;
	

}
vector< int >MazeGen::findPath()
{
        vector<bool> row;
	vector<int> convertans;
	vector<int> bestans;
	vector<int> truepath;
	stack<int> traverse;
	int visited=0;
	int x,y;
	for(int i=0;i<mazewidth*mazeheight;i++)
	{
		row.push_back(false); //set to true when visited
	}

	traverse.push(0);
	while(visited<mazewidth)
	{ 
		bool a=false,b=false,c=false,d=false;
		int top = traverse.top();//check if truepath
		
			row[top] = true;
			truepath.push_back(top);	
			x= top%mazewidth;
			y= top/mazewidth;
			if(validStep(x,y,0) && row[top + 1] == false ) //right
			{
				traverse.push(top+1);
				a = true;
			}
			if(validStep(x,y,1) && row[top + mazewidth] == false) //down
			{
				traverse.push(top+mazewidth);
				b = true;
			}

			if(validStep(x,y,2) && row[top - 1] == false) //left
			{
				traverse.push(top-1);
				c = true;
			}
			if(validStep(x,y,3) && row[top - mazewidth] == false) //up
			{
				traverse.push(top-mazewidth);
				d = true;
			}
			
			if((truepath.back()/mazewidth)==(mazeheight-1)) // hit a cell in the last row
			{	
					row[truepath.back()]= true;
					visited++;
				
					if(visited==1)
						bestans=truepath;
					if((truepath.size() > bestans.size()) || ((truepath.size()==bestans.size())&& (truepath.back()< bestans.back())))
					{
						bestans = truepath;	
					}
			
			}
		
		

			if((!(a||b||c||d)) && visited<mazewidth ) // you cant move in any direction 
			{
			
				while(truepath.back()==traverse.top()) //backtracking until you have a different option in traverse
				{
					truepath.pop_back();
					traverse.pop();
				}

			
			}
				
	}
		
	for(size_t i=1;i<bestans.size();i++)
	{
		if((bestans[i-1]+1) == bestans[i])
			convertans.push_back(0); // right
		else if(bestans[i-1] == (bestans[i]+1))
			convertans.push_back(2); //left
		else if((bestans[i-1]+mazewidth) == bestans[i])
			convertans.push_back(1); //down
		else if(bestans[i-1] == (bestans[i]+mazewidth))
			convertans.push_back(3); //up	
	}
	destx=bestans.back()%mazewidth;
	desty=bestans.back()/mazewidth;
	return convertans;					
		
}	

PNG * MazeGen::drawSolved()
{
	PNG *solpic= drawUnsolved();
	vector<int>godir = findPath();
	size_t x=5;
	size_t y =5;
	RGBAPixel red(255,0,0);
	RGBAPixel white(255,255,255);

	int index = 0;
 
	std::cout << "+   +";
	for (int j = 1; j < mazeheight; j++){
			std::cout << "---+";
		}
			std::cout << std::endl;

	for (int i = 0; i < mazewidth; i ++){

		std::cout << "|";

		for (int j = 0; j < mazeheight; j++){
			if (mymaze[i*mazewidth + j ].rightexists)
				std::cout << "   |";
			else
				std::cout<<"    ";
		}

		std::cout << std::endl;

		std::cout << "+";
		for (int j = 0; j < mazeheight; j++){
			if(mymaze[i*mazewidth + j ].downexists)
				std::cout << "---+";
			else
				std::cout << "   +";
		}

			std::cout << std::endl;

	}

	for(size_t i=0;i<godir.size();i++)
	{
		for(int j=0;j<11;j++)
		{
			if(godir[i]==0)
			{
				*((*solpic)(x,y))=red; //right
				if(j<10)
					++x;
			}
			else if(godir[i]==1)
			{
				*((*solpic)(x,y))=red; //down
				if(j<10)
					++y;
			}
			else if(godir[i]==2)
			{
				*((*solpic)(x,y))=red;//left
				if(j<10)
					--x;
			}
			else if(godir[i]==3)
			{
				*((*solpic)(x,y))=red; //up
				if(j<10)
					--y;
			}
		}
	}
	for(size_t k=1;k<=9;k++)
	{
		*((*solpic)(destx*10+k, (desty+1)*10))= white;
	}
	return solpic;
}
	


			
			
	
			
		
	
	

		
		
		

	
	
	


		 

		
	
	



	
		
