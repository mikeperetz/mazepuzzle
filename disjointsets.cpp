
#include "disjointsets.h"
int DisjointSets::search(int elem)
{
	if (set[elem]<0)
		return elem;
	else return set[elem]=search(set[elem]);	//path compression
}

void DisjointSets::join(int a,int b)
{
	int root1=search(a);
	int root2=search(b);
	int newsize = set[root1]+set[root2];
	if(set[root2]<set[root1]) //root2 set is bigger
	{
		set[root1]= root2; //root1 points to root2
		set[root2]=newsize; 
	}
	else
	{
		set[root2]=root1;
		set[root1]=newsize;
	}
	
}

void DisjointSets::insert(int num)
{
	for(int i=0;i<num;i++)
		set.push_back(-1);
}	
		
void DisjointSets::remove()
{
	set.clear();
}
	

