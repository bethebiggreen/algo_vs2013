
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

	// left_stack 에 초기값을 모두 저장한다... 스택에 왜?
	// abcd -> dcba 출력된다.
	for (char *c = buff; *c; c++) left_stack.push(*c);

	for (int i = 0; i < n; ++i) {
		scanf("%s", buff);
		if (buff[0] == 'L') {
			// 이 의미가 헷갈림.. left_stack 이 empty 인 경우가 있나?.. 아..다 지워지면..empty 겠네..empty 면은
			// L 의 의미가 없지...그렇지..
			if (left_stack.empty()) continue;
			// 이게 무슨 의미냐.... right stack 에다가 집어 넣는데, 그걸 left staclk 에서 꺼낸다...?
			// 에레이...
			right_stack.push(left_stack.top());
			left_stack.pop();
		}
			// right_stack 이 empty 이면 이것또한... 의미가 없으니... continue ..흠... 이건 뭐...
		if (buff[0] == 'D') {
			if (right_stack.empty()) continue;
			// 여기또한... 아놔... 자웅동체냐?
			left_stack.push(right_stack.top());
			right_stack.pop();
		}
		if (buff[0] == 'B') {
			if (left_stack.empty()) continue;
			// 아..필요없으니깐 빼버린다.. ? 맙소사..
			left_stack.pop();
		}
		if (buff[0] == 'P') {
			scanf("%s", buff);
			// 흠..이건 뭐지..다시 집어 넣는다고?.. 설마..왜...그럼 속도는?
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