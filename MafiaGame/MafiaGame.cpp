/*
0.02 Algotihms finished
     1. Grab the first vertex of the array. It will be root of our tree.
	 2. We will check both treat 'MAFIA' or 'CITIZEN'.
	 3. The one concrete fact is MAFIA does not point at another MAFIA.
	 4. Traversing is keeping continues until iterator meets selected vertex, which represents cycle.
	 5. After recognizing a cycle, it spawns another itinernary.
	 6. Root will be choonse among unvisited vertex.
	 7. It will keep until all vertex are visited.
	 8. After, finishing all itinerary, the num of maximum MAFIA is returned.

0.01 from https://www.acmicpc.net/problem/10542

*/

#include <iostream>
const int MAX_N = 500000+1;
bool suspect[MAX_N] = { false, };
int sol = 0;

using namespace std;

int main(void)
{
	freopen("input.txt", "r", stdin);
	int N = 0;
	cin >> N;
	
	for (int i = 1; i <= N; i++) {
		int who;
		cin >> who;
		if (!suspect[who]) {
			suspect[who] = true;
			sol++;
		} 
	}
	cout << sol;
	return 0;
}