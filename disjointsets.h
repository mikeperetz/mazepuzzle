#ifndef _DSETS_H_
#define _DSETS_H_

#include <vector>
using std::vector;

class  DisjointSets
{
	public :


	int search(int elem);
	void insert(int num);
	void join(int a,int b);
	void remove();
	


	private:

	/*the forest of uptrees if the node is
	 *if the node is a root, the value will be -1 */
	vector<int> set;


};
#endif

