/*

  At least, probability n(A), n(B) -> 1 - n(Ac and Bc) 
  So, prime numbers are under 30 -> 2,3,5,7,11,13,17,19,23,29
                      Complement -> 1,4,6,8,9,10, ... , 30

  Ac and Bc 
   A(1)*B(1) + A(1)*B(4) + ... + A(1)*B(30)
   + A(2)*B(1) + A(2)*B(4) + ... + A(2)*B(30)
   ...
   + A(30)*B(1) + A(30)*B(4) + ... + A(30)*B(30)
 
  A(1) : (0.5)^0*(1-0.5)^30 + (0.5)^1*(1-0.5)^29 + (0.5)^2*(1-0.5)^28 + ... + (0.5)^30*(1-0.5)^0

*/

#include <iostream>
using namespace std;

const int N = 30;
int TC_NUM = 0;
int non_prime_nums[20] = {1, 4, 6, 8, 9,
                          10,12,14,15,16,
	                      18,20,21,22,24,
	                      25,26,27,28,30};
const int MAX_N = 10;
double prob_a[MAX_N] = { 0.0, };
double prob_b[MAX_N] = { 0.0, };
double sol[MAX_N] = { 0.0, };

inline double get_proability(int num, double probability)
{
	int occurrence = num;

	// NCnum, 30C2, For example N:30, num:29, 30*29/2*1
	if (num == 1) {
		// Skip		
	}
	else if (N == num) {
		occurrence = 1;
	}
	else if (N != num) {
		for (int i = N; i > (N - num); i--)
			occurrence *= (N - i);
		for (int i = N-num+1; i > 1; i--)
			occurrence /= i;
	}
		
	double temp1 = probability;
	double temp2 = 1.0 - probability;
	for (int j = 0; j < num; j++)
		temp1 *= probability; // temp = 3*3*3*3
	for (int j = 0; j < N-num; j++)
		temp2 *= (1.0-probability);
	
	return occurrence*temp1*temp2;
}

void input_proc(void)
{
#if _DEBUG
	freopen("inp.txt", "r", stdin);
#endif
	cin >> TC_NUM;
	for (int i = 0; i < TC_NUM; i++) {
		cin >> prob_a[i] >> prob_b[i];
		prob_a[i] /= 100;
		prob_b[i] /= 100;
	}
}

void output_proc(void)
{
	for (int i = 0; i < TC_NUM; i++)
		printf("%1.6f\n");
	//cout << sol[i] << endl;

}

double get_solution(int tc)
{
	double prob = 0.0;
	for (int i = 0; i < 20; i++) 
		for (int j = 0; j < 20; j++) 
			prob += (get_proability(non_prime_nums[i], prob_a[tc])*get_proability(non_prime_nums[j],prob_b[tc]));
	
	return 1.0 - prob;
}

void do_something(void)
{
	for (int tc = 0; tc < TC_NUM; tc++) 
		sol[tc] = get_solution(tc);
}

int main()
{
	input_proc();
	do_something();
	output_proc();
	return 0;
}