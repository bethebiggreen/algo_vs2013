/*
https://www.acmicpc.net/problem/9012
*/
#include <stdio.h>

/*
	LIFO , Last-In-First-Out, AKA Stack.
*/
template<typename T>
class stack {
public :
	const static int default_max_ = 10000;
	int begin_;
	int end_;
	int size_;
	T* inner_queue_;

	stack<T>(int in_size = default_max_) : begin_(0), end_(-1), size_(in_size)
	{
		inner_queue_ = new T[size_];
		for (int i = 0; i < size_; i++)
			inner_queue_[i] = static_cast<char>('\0');
	}

	~stack()
	{
		if (inner_queue_)
			delete[] inner_queue_;
		inner_queue_ = NULL;
	}

	bool push(T data)
	{
		if (end_-1 >= size_)
			if (!resize(size_*2))
				return false;

		inner_queue_[++end_] = data;
		return true;
	}

	T pop(void)
	{
		if (end_ < begin_)
			return NULL;
		int ret = inner_queue_[end_];
		inner_queue_[end_--] = '\0';
		return ret;
	}

	int const length(void)
	{
		return end_ + 1;
	}

private:
	// TODO
	bool resize(int size)
	{
		return false;
	}
};

bool do_something(void)
{
	const char OPEN = '(';
	const char CLOSE = ')';
	const int MAX_CHAR_IN_A_LINE = 50 + 1;

	char input[MAX_CHAR_IN_A_LINE] = { 0, }; 
	stack<char> line;
	scanf("%s", input);
	int iter = 0;
	char chr = 0;
	while ((chr = input[iter++])) {
		switch (chr) {
		case OPEN:
			line.push(chr);
			break;
		case CLOSE:
			if (OPEN != line.pop())
				return false;
			break;
		default:
			break;
		}
	}

	return (line.length() == 0) ? true : false;
}

int main()
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		if (do_something()) 
			printf("YES\n");
		else 
			printf("NO\n");
	}

	return 0;
}