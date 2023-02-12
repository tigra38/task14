#include <iostream>
#include <string>
#include "TrieNode.h"

using namespace std;

TrieNode* getNewNode(void)
{
    struct TrieNode* pNode = new TrieNode;
    pNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;
    return pNode;
}

/*void insert(TrieNode* root, string key)
{
    TrieNode* node = root;
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
        {
            std::cout << index << std::endl;
            node->children[index] = new TrieNode;
            node = node->children[index];
        }
    }
    node->isEndOfWord = true;
}*/

void insert(TrieNode* root, string key)
{
    TrieNode* node = root;
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            node->children[index] = getNewNode();
        node = node->children[index];
    }
    node->isEndOfWord = true;
}

bool search(struct TrieNode* root, string key)
{
    TrieNode* node = root;
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

char words_array[10][32];
std::string words_list[10];
    //TrieNode* node = root;
void search2(TrieNode* node, int& index, int& words, std::string& key)
{
    if (words > 10) return;
    if (!key.empty() && index < key.length()) {
        for (int letters_to_root = 0; letters_to_root <= index; letters_to_root++)
        {
//            std::cout << "copy0: " << words << "-" << letters_to_root << ": " << key[letters_to_root] << std::endl;
            words_array[words][letters_to_root] = key[letters_to_root];
        }
        if (node->isEndOfWord)
        {
            words_array[words][index + 1] = 0;
            words_list[words] = words_array[words];
            words++;
            for (int letters_to_root = 0; letters_to_root <= index; letters_to_root++)
            {
//                std::cout << "copy00: " << words << "-" << letters_to_root << ": " << key[letters_to_root] << std::endl;
                words_array[words][letters_to_root] = words_array[words - 1][letters_to_root];
            }
            
            //index++;
//            std::cout << "word!!!" << std::endl;
        }
    }
    index++;
//    std::cout << "index+: " << index << std::endl;
    int node_num = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (words > 10)
        {
            //                   std::cout << "break 10" << std::endl;
            break;
        }
        if (node->children[i]) {
 //           std::cout << "find children " << (char)(i + 'a') << std::endl;
            if (node_num > 0)
            {
                for (int letters_to_root = 0; letters_to_root < index; letters_to_root++)
                {
 //                   std::cout << "copy: " << words << "-" << letters_to_root << ": " << words_array[words - 1][letters_to_root] << std::endl;
                    words_array[words][letters_to_root] = words_array[words - 1][letters_to_root];
                }
            }
            node_num++;
            words_array[words][index] = i + 'a';
 //           std::cout << "words_list " << words << "-" << index << ": " << (char)(i + 'a') << std::endl;
            if (node->children[i]->isEndOfWord) {
                words_array[words][index + 1] = 0;
                words_list[words] = words_array[words];
//                std::cout << "end " << words_list[words] << std::endl;
                words++;
                for (int letters_to_root = 0; letters_to_root <= index; letters_to_root++)
                {
 //                   std::cout << "copy2: " << words << "-" << letters_to_root << ": " << words_array[words - 1][letters_to_root] << std::endl;
                    words_array[words][letters_to_root] = words_array[words - 1][letters_to_root];
                }
            }
            search2(node->children[i], index, words, key);
            index--;
//            std::cout << "index-: " << index << std::endl;
        }
            
    }
    
}

void search_words(TrieNode* node, std::string key)
{
    TrieNode* current = node;
    //char* words_array[32];
    int words = 0;
    int index = -1;

    bool exist = true;
    for (int i = 0; i < key.length(); i++)
    {
        if (!current->children[key[i] - 'a'])
        {
            std::cout << "Not exist. Try again." << std::endl;
            exist = false;
            break;
        }
        current = current->children[key[i] - 'a'];
    }

    if (exist) {
        index += key.length();
        search2(current, index, words, key);
    }
    else return;

    if (words > 10)
    {
        std::cout << "Too much variants. Try again." << std::endl;
    }
    else {
        for (int variants = 0; variants < words; variants++) {
            std::cout << variants << ": " << words_list[variants] << std::endl;
        }
        int user_variant;
        std::cin >> user_variant;
        if (user_variant >= words) std::cout << "Incorrect choise" << std::endl;
            else std::cout << words_list[user_variant] << std::endl;
    }
    //return (node != nullptr && node->isEndOfWord);
}

bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

TrieNode* remove(TrieNode* root, string key, int depth = 0)
{
    if (!root)
        return nullptr;
    if (depth == key.size()) {
        if (root->isEndOfWord)
            root->isEndOfWord = false;
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }
    return root;
}

string last2[10];
int last_num = 0;

void findMinPrefixes(TrieNode* root, char buf[], int ind, string& res)
{
    TrieNode* node = root;
    for (int i = 0; i < 26; i++)
    {
        if (node->children[i])
        {
            buf[ind] = i + 'a';
            ind++;
            //std::cout << i << "(" << (char)(i + 'a') << ")-in-" << ind << "-" << std::endl;
            if (node->children[i]->isEndOfWord == true)
            {
                std::cout << "End!" << std::endl;

                //buf[ind]=32;
                buf[ind] = 0;
                last2[last_num] = buf;
                //res += buf;
                std::cout << last_num << ": " << buf << std::endl;
                last_num++;
                //return;
            }
            findMinPrefixes(node->children[i], buf, ind, res);

            //std::cout << i << "(" << (char)(i + 'a') << ")-out-" << ind << "-" << std::endl;
            //buf[ind]= 0;
            ind--;
            if (ind == 0)
            {
                std::cout << "ind" << std::endl;
                if (last_num <= 1) // || last2[0].length()==1
                {
                    std::cout << "000:" << last2[0][0] << std::endl;
                    res += last2[0][0];
                    res += " ";
                }
                else
                {
                    for (int j = 0; j < last_num - 1; j++)
                    {
                        std::cout << j << ": " << last2[j] << std::endl;
                        for (int k = 0; k < last2[j].length(); k++)
                        {
                            std::cout << "k:" << k << std::endl;
                            if (last2[j][k] != last2[j + 1][k])
                            {
                                if (j == 0)
                                {
                                    //if (!res.empty()) res+= " ";
                                    res += last2[j].substr(0, k + 1);
                                    std::cout << "j=0" << last2[j].substr(0, k + 1) << std::endl;
                                    res += " ";
                                }

                                std::cout << j << last2[j + 1].substr(0, k + 1) << std::endl;

                                res += last2[j + 1].substr(0, k + 1);
                                res += " ";
                                break;
                            }
                            if (k == last2[j].length() - 1 && last2[j][k] == last2[j + 1][k])
                            {
                                res += last2[j + 1].substr(0, k + 2);
                                res += " ";
                            }
                        }
                    }
                }

                std::cout << "res: " << res << std::endl;
                last_num = 0;
            }
        }
    }
}
