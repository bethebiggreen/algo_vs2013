#include <iostream>

using namespace std;

int T = 0;
const int MAX_N = 10;
int a[MAX_N];
int b[MAX_N];
double sol[MAX_N];
const int SIZE_PRIME_NUM = 10;
const int TOTAL = 30;
int prime_num[SIZE_PRIME_NUM] = { 2,3,5,7,11,13,17,19,23,29 };

void input_proc(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	cin >> T;
	for (int i = 0; i < T; i++)
		cin >> a[i] >> b[i];
}

double get_proability_internal(const double probability)
{
	double prob_of_happen = probability;
	double prob_of_no_happend = (double)1.0 - probability;
	double ret = 0.0;
	for (int i = 0; i < SIZE_PRIME_NUM; i++) {
		double case_num = 1.0;
		for (int j = 0; j < prime_num[i]; j++)
			case_num *= (TOTAL - j);
		for (int j = 0; j < prime_num[i]; j++)
			case_num /= (prime_num[i] - j);
		for (int j = 0; j < prime_num[i]; j++)
			prob_of_happen *= probability;
		for (int j = 0; j < TOTAL- prime_num[i]; j++)
			prob_of_no_happend *= ((double)1.0 - probability);

		ret += case_num*(prob_of_happen*prob_of_no_happend);
	}

	return ret;
}

double get_probability(const double a, const double b)
{
	return get_proability_internal(a) + get_proability_internal(b);
}

void do_something(void)
{
	for (int i = 0; i < T; i++)
		sol[i] = get_probability(a[i]/(double)100, b[i]/(double)100);
}

void output_proc(void)
{
	for (int i = 0; i < T; i++)
		cout << sol[i] << endl;
}

int main()
{
	double a = 0.5;
	input_proc();
	do_something();
	output_proc();
	return 0;
}
