/*

0.07 O(N+K) can be implemented. 

0.06 int get_one(void) ; // find not visited vertex from 0 to N
     while(1) { int start = get_one(); }  
	 while-loop runs until there is no vertex which is not visited yet.
	 For better performance, we store 0-in-degree on must_mafias array.
	 And, main while-loop peeks it up.	 

0.05 Topological sort is run, in advance. And we will know MAFIAs and citizens, assumely. 
     Other vertex will be visited in order until all vertices are visited.

0.04 Time-out is occured. Complicated algorithm ...

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
int must_mafias[MAX_N] = { false, };
int must_mafias_size = 0;

int N = 0;

enum {
	NOIDEA = 0,
	MAFIA = 1,
	CITIZEN = 2,
};

int calls_of_spwan = 0;
int calls_of_traverse = 0;

struct node {
	int val1; // pointed by 
	int val2; // status
	node* prev;
	node* next;
	node(int value1, int value2) : val1(value1), val2(value2), prev(NULL), next(NULL) {}
};

struct node_list {
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
		else if (head == tail) {
			head->next = new_one;
			new_one->prev = head;
			tail = new_one;
		}
		else {
			new_one->prev = tail->prev;
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

node_list who_suspects_me[MAX_N];

void input_proc(void)
{
	freopen("input.txt", "r", stdin);
	cin >> N;

	for (int i = 1; i <= N; i++) {
		int tmp = 0;
		cin >> tmp;
		suspect[i] = tmp;
		who_suspects_me[tmp].add(i, -1);
	}
}

void output_proc(void)
{
	int num_mafia = 0;

	if (must_mafias_size) {
		for (int i = 1; i <= N; i++)
			if (mafia[i] == MAFIA)
				num_mafia++;
	}
	else
		num_mafia = N / 2;

	cout << num_mafia;
}

bool can_set_mafia(int cur)
{
	if (mafia[suspect[cur]] == MAFIA)
		return false;

	for (node* iter = who_suspects_me[cur].head; iter != NULL; iter = iter->next) {
		if (mafia[iter->val1] == MAFIA)
			return false;
		else {
			mafia[iter->val1] == MAFIA;
			visited[iter->val1] = true;
		}
	}

	return true;
}

// It has to traverse both cases (chosen or not chosen)
void traverse(int cur)
{
	calls_of_traverse++;
	visited[cur] = true;
	int next = suspect[cur];
	if (can_set_mafia(cur)) 
		mafia[cur] = MAFIA;
	else 
		mafia[cur] = CITIZEN;

	if (!visited[next])
		traverse(next);

	return;
}

void init_mafias_and_citizen(void)
{
	for (int i = 1; i <= N; i++) {
		if (0 == who_suspects_me[i].size) {
			int man_no = i;
			mafia[man_no] = MAFIA;
			visited[man_no] = true;
			mafia[suspect[man_no]] = CITIZEN;
			visited[suspect[man_no]] = true;
		}
	}
}

int init_start_candidates(void)
{
	for (int i = 1; i <= N; i++) {
		if (0 == who_suspects_me[i].size) {
			must_mafias[++must_mafias_size] = i;
			mafia[i] = MAFIA;
			visited[i] = true;
		}
	}
}

int get_one()
{
	for (int i = 1; i <= N; i++)
		if (!visited[i])
			return i;

	return 0;
}

void do_something(void)
{
	init_start_candidates();
	if (must_mafias_size) {
		for (int i = 1; i <= must_mafias_size; i++)
			traverse(must_mafias[i]);
	}
	else {
		sol = (N - 1) / 2;
	}
}

int main(void)
{
	input_proc();
	do_something();
	output_proc();
	return 0;
}