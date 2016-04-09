
/*
DMIH 2004 - Prvi dan natjecanja
Srednjoskolska skupina - I. podskupina
Zadatak EDITOR
*/

#if 0
#include <stdio.h>
#include <iostream>
#include <stack>

using namespace std;

stack<char> left_stack, right_stack;
char buff[100002];
int n;

int main(void) {
	freopen("editor.in41", "r", stdin);
#if 0 // Visual studion community does not recognize  'gets'.
	gets(buff);
#else
	scanf("%s", buff);
#endif
	scanf("%d", &n);

	// left_stack �� �ʱⰪ�� ��� �����Ѵ�... ���ÿ� ��?
	// abcd -> dcba ��µȴ�.
	for (char *c = buff; *c; c++) left_stack.push(*c);

	for (int i = 0; i < n; ++i) {
		scanf("%s", buff);
		if (buff[0] == 'L') {
			// �� �ǹ̰� �򰥸�.. left_stack �� empty �� ��찡 �ֳ�?.. ��..�� ��������..empty �ڳ�..empty ����
			// L �� �ǹ̰� ����...�׷���..
			if (left_stack.empty()) continue;
			// �̰� ���� �ǹ̳�.... right stack ���ٰ� ���� �ִµ�, �װ� left staclk ���� ������...?
			// ������...
			right_stack.push(left_stack.top());
			left_stack.pop();
		}
			// right_stack �� empty �̸� �̰Ͷ���... �ǹ̰� ������... continue ..��... �̰� ��...
		if (buff[0] == 'D') {
			if (right_stack.empty()) continue;
			// �������... �Ƴ�... �ڿ���ü��?
			left_stack.push(right_stack.top());
			right_stack.pop();
		}
		if (buff[0] == 'B') {
			if (left_stack.empty()) continue;
			// ��..�ʿ�����ϱ� ��������.. ? ���һ�..
			left_stack.pop();
		}
		if (buff[0] == 'P') {
			scanf("%s", buff);
			// ��..�̰� ����..�ٽ� ���� �ִ´ٰ�?.. ����..��...�׷� �ӵ���?
			left_stack.push(buff[0]);
		}
	}

	while (!left_stack.empty()) {
		right_stack.push(left_stack.top());
		left_stack.pop();
	}
#if _DEBUG
	FILE* fp = fopen("output2.txt", "w");
	while (!right_stack.empty()) {
		fprintf(fp,"%c", right_stack.top());
		right_stack.pop();
	}
	fprintf(fp, "\n");
#else
	while (!right_stack.empty()) {
		printf("%c", right_stack.top());
		right_stack.pop();
	}
	printf("\n");
#endif

	return 0;
}
#endif 