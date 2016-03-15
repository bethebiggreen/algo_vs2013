#include <iostream>

using namespace std;

int main()
{
	printf("happy");
	freopen("input.txt", "r", stdin);
	int  start, end, total, up, down;
	cin >> total >> start >> end >> up >> down;

	if (start > end) {
		int go_up = end / up;
		if ((go_up + 1)*up > total)
			cout << "use the stairs" << endl;

		int remain = (go_up + 1)*up - total;

	}
	else {
		cout << "happy hacking !!" << endl;
	}

	return 0;
}