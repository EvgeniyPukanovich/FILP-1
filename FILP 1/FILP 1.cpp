#include <iostream>
#include <string>
#include <fstream>
#include <ctime>


using namespace std;

class block
{
public:
	char* str;
	block* next;
	int length;
	block()
	{
		str = new char[100];
		length = 0;
		next = nullptr;
	}

	~block()
	{
		delete[] str;
	}
};

class charList
{
public:
	char* array;
	long length;
	long current_size = 2;

	charList()
	{
		array = new char[2];
		length = 0;
	}

	void add(char a) {
		if (length == current_size) {
			resize();
		}
		array[length] = a;
		length++;
	}

	void resize()
	{
		char* newArray = new char[length * 2];
		for (size_t i = 0; i < length; i++)
		{
			newArray[i] = array[i];
		}
		array = newArray;
		current_size = current_size * 2;
	}

	~charList()
	{
		delete[] array;
	}
};

class token
{
public:
	charList* chArray;

	int cnt;

	token()
	{
		cnt = 0;
		chArray = nullptr;
	}

	token(charList* chA)
	{
		chArray = chA;
		cnt = 1;
	}

	~token()
	{
		delete chArray;
	}
};

class tokenList {
public:
	token* array = new token[2];
	int length = 0;
	long current_size = 2;

	void add(token* a) {
		if (length == current_size)
		{
			resize();
		}
		array[length] = *a;
		length++;
	}

	void resize() {
		token* newArray = new token[length * 2];
		for (size_t i = 0; i < length; i++)
		{
			newArray[i] = array[i];
		}
		current_size = current_size * 2;
		array = newArray;
	}

	void sort()
	{
		for (size_t i = 0; i < length; i++)
		{
			for (size_t j = i; j < length; j++)
			{
				if (array[i].cnt < array[j].cnt)
				{


					token tmp = array[i];
					array[i] = array[j];
					array[j] = tmp;
					tmp = *(new token());

				}
			}
		}
	}
	~tokenList()
	{
		delete array;
	}

};

static bool compare(charList* lst1, charList* lst2) {
	if ((*lst1).length != (*lst2).length)
	{
		return false;
	}
	for (size_t i = 0; i < (*lst1).length; i++)
	{
		if ((*lst2).array[i] != (*lst1).array[i]) {
			return false;
		}
	}
	return true;
}

static void ineffective() {

}

static void effective() {
	ifstream in("C:\\Users\\capybara\\source\\repos\\FILP 1\\FILP 1\\1.txt");
	string tmp = "";

	if (in.is_open())
	{
		char symbol = static_cast<char>(in.get());
		while (!in.eof())
		{
			tmp += symbol;
			//if((int)symbol<)
			symbol = static_cast<char>(in.get());
		}
	}
}


int main()
{
	unsigned int start_time = clock();

	//string line;
	block* block1 = new block();
	block* currentBlock = block1;
	int i = 0;
	ifstream in("C:\\Users\\capybara\\source\\repos\\FILP 1\\FILP 1\\1.txt");

	if (in.is_open())
	{
		char symbol = static_cast<char>(in.get());
		while (!in.eof())
		{
			if (i == 100)
			{
				block* block2 = new block();
				block1->next = block2;
				block1 = block2;
				i = 0;
			}
			else
			{
				block1->str[i] = symbol;
				block1->length++;
				i++;
			}
			symbol = static_cast<char>(in.get());
		}
		in.close();
	}
	charList* lst;
	lst = new charList();
	tokenList* dict;
	dict = new tokenList();

	while (currentBlock != nullptr)
	{

		for (size_t i = 0; i < currentBlock->length; i++)
		{
			if ((int)currentBlock->str[i]>64)
			{
				lst->add(currentBlock->str[i]);
			}
			else if (lst->length != 0)
			{
				bool find = false;
				for (size_t j = 0; j < dict->length; j++)
				{
					charList* tmp = dict->array[j].chArray;
					if (compare(lst, tmp))
					{
						dict->array[j].cnt += 1;
						find = true;
						lst = new charList();
						break;
					}
				}
				if (!find)
				{
					token* new_token = new token(lst);
					dict->add(new_token);
					lst = new charList();
				}
			}
		}
		if (currentBlock->next == nullptr)
		{
			bool find = false;
			for (size_t j = 0; j < dict->length; j++)
			{
				charList* tmp = dict->array[j].chArray;
				if (compare(lst, tmp))
				{
					dict->array[j].cnt += 1;
					find = true;
					lst = new charList();
					break;
				}
			}
			if (!find)
			{
				dict->add(new token(lst));
				lst = new charList();
			}
		}
		block* tmp = currentBlock;
		currentBlock = currentBlock->next;
		delete tmp;
	}
	dict->sort();

	string result = "";
	int end_time = clock(); // конечное время
	int search_time = end_time - start_time; // искомое время
	for (int i = 0; i < dict->length; i++)
	{
		for (size_t j = 0; j < dict->array[i].chArray->length; j++)
		{
			result += dict->array[i].chArray->array[j];
		}
		std::cout << result << std::endl;
		result = "";
	}


	std::cout << search_time << std::endl;


	return 0;
}


