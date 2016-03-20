/*
0.03 Simple algorithm is finished. Complicated algorithms(one mafia indicates other citizen(s)) will be implemented.
     Setting one mafia causes more decisions. Like, below, make A mafia, could assume that consider B,C,D as citizens. 
       B -> 
	         A -> D
	   C ->

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

using namespace std;

const int MAX_N = 500000+1;
//const int MAX_N = 10;
int sol = 0;
int visited[MAX_N] = { false, };
int suspect[MAX_N] = { false, };
int mafia[MAX_N] = { false , }; // maybe.. it's not needed.
int N = 0;

enum {
	NOIDEA = 0,
	MAFIA = 1,
	CITIZEN = 2,
};
#if 0
node_list who_suspects_me[MAX_N];

struct node {
	int val1;
	int val2;
	node* prev;
	node* next;
	node(int value1, int value2) : val1(value1), val2(value2), prev(NULL), next(NULL) {}
};

struct node_list{
	int size;
	node* head;
	node* tail;

	node_list() : head(NULL), tail(NULL), size(0) {}
	int add(int val1, int val2) {
		node* new_one = new node(val1, val2);

		if (head == NULL) {
			head = new_one;
			tail = new_one;
		}
		else if(head == tail) {
			head->next = new_one;
			new_one->prev = head;
			tail = new_one;
		}
		else {
			new_one->prev =	tail->prev;
			tail->prev->next = new_one;
			tail = new_one;
		}

		return ++size; 
	}

	node get(int idx) {
		node* iter = head;
		for (int cnt = 0; iter != NULL && cnt < idx; iter = iter->next, cnt++);
		return *iter; 
	}

};



bool set_mafia(int man)
{
	node_list history;
	bool need_recover = false;
	
	for (node* iter = who_suspects_me[man].head; iter != NULL ; iter = iter->next) {
			history.add(iter->val1, mafia[iter->val1]);
			if (mafia[iter->val1] == MAFIA) {
				need_recover = true;
				break;
			}
			else {
				mafia[iter->val1] = CITIZEN;
				visited[iter->val1] = true;
			}
	}

	if (need_recover) {
		for (node* iter = history.head; iter != NULL; iter = iter->next) {
			visited[iter->val1] = false;
			mafia[iter->val1] = iter->val2;
		}
		return false;
	}
	else {
		mafia[man] = MAFIA;
		return true;
	}

}


// TO BE CONTINUED
bool unset_mafia(int man)
{
	for (int i = 1; i <= N; i++)
		if (suspect[i] == man)
			mafia[i] = NOIDEA;

	mafia[man] = NOIDEA;
}
#endif

void traverse(int, int);
// It must be called with not-visited vertex.
void spawn_traverse(int root)
{
	traverse(0, root);
}

void update_solution()
{
	int num_mafia = 0;
	for (int i = 1; i <= N; i++)
		if (mafia[i] == MAFIA)
			num_mafia++;

	if (sol < num_mafia)
		sol = num_mafia;
}

// It has to traverse both cases (chosen or not chosen)
void traverse(int prev, int cur)
{
	visited[cur] = true;
	int next = suspect[cur];
	if (!visited[next]) {
		if (mafia[prev] != MAFIA) {
			mafia[cur] = MAFIA;
			traverse(cur, next);
			mafia[cur] = NOIDEA;
			traverse(cur, next);
		}
		else {
			mafia[cur] = NOIDEA;
			traverse(cur, next);
		}
	}
	else {
		if (mafia[prev] != MAFIA && mafia[next] != MAFIA)
			mafia[cur] = MAFIA;

		//prepare spawning
		int next_root = 0;
		bool found = false;
		for (next_root = 1; next_root <= N; next_root++) {
			if (!visited[next_root]) {
				found = true;
				break;
			}
		}

		if (found) 
			spawn_traverse(next_root);
		else { //finish one itinerary
			update_solution();
		}
	}

	// Recover previous status
	if (mafia[cur] == MAFIA)
		mafia[cur] = NOIDEA;
	visited[cur] = false;
}

void do_something(void)
{
	spawn_traverse(1);
}

void input_proc(void)
{
	freopen("input.txt", "r", stdin);
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> suspect[i];
		//who_suspects_me[i].add(suspect[i], -1);
	}
}

void output_proc(void)
{
	cout << sol;
}

int main(void)
{
	input_proc();
	do_something();
	output_proc();
	return 0;

}