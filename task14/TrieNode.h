#pragma once
#define ALPHABET_SIZE 26
#include <string>

struct TrieNode
{
	struct TrieNode* children[ALPHABET_SIZE];
	bool isEndOfWord;
};

TrieNode* getNewNode(void);
void insert(TrieNode* root, std::string key);
bool search(struct TrieNode* root, std::string key);
bool isEmpty(TrieNode* root);
TrieNode* remove(TrieNode* root, std::string key, int depth);
void findMinPrefixes(TrieNode* root, char buf[], int ind, std::string& res);
void search2(TrieNode* node, int& index, int& words, std::string& key);
void search_words(TrieNode* node, std::string key);