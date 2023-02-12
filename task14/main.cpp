#include <iostream>
#include <string>
#include "TrieNode.h"

int main()
{
	char buf2[10];
	for (int i = 0; i < 10; i++)
	{
		buf2[i] = 0;
	}
	int ind2 = 0;
	std::string res2 = "";
	TrieNode* node = getNewNode();
	
	insert(node, "zadnitsa");
	insert(node, "zapor");
	insert(node, "zarya");
	insert(node, "zarnitsa");
	insert(node, "zayats");
	insert(node, "zoloto");
	insert(node, "zebra");
	insert(node, "zad");
	insert(node, "arka");
	
	while (1)
	{
		std::cout << "Enter part of word or press 0 for exit: ";
		std::string user_string = "";
		std::cin >> user_string;
		if (user_string[0] == '0') break;
		if (user_string[0] >= '1' && user_string[0] <= '9') continue;
		search_words(node, user_string);
	}
	
	//search2(node);
	//findMinPrefixes(node, buf2, ind2, res2);
	return 0;
}