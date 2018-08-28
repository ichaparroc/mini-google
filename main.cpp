#include<string.h>
#include<stdio.h>
#include<string.h>
#include<iostream.h>

using namespace std;

class radix_trie_node
{
	radix_trie_index index;

	vector<string> words;
	vector<radix_trie_node*> pointers;

	void insert(radix_trie_node *node , string word , string id_file, float relevance)
	{
		if(word != "") //no encontro donde aun
		{
			if(words.size()>0) //si tiene hijos
			{
				int equals;
				int match=0;
				int pos=0;

				while(pos < node->words.size() && word[0] >= node->words[i][0])
				{
					equals = compare_word(node->words[i] , word)
					if(equals == 0)
					else if(equals < node->words[i].size()) //SPLIT
					{
						match=1;

						radix_trie_node father = new radix_trie_node;

						father->words.push_back(node->words[i].substr(equals));
						father->pointers.push_back(node->pointers[i]);

						node->words[i]=node->words[i].substr(0,equals);
						node->pointers[i]=father;

						break;
					}
					else //equals == node->words[i].size() //EXACTO
					{
						match=1;
						insert(radix_trie_node->pointers[i] , word.substr(equals) , id_file relevance);
						break;
					}
					pos++;
				}
				if(match==0)  //debo insertar en i
				{
					node->words.push_back(node->words.last);
					node->pointers.push_back(node->pointers.last);

					for(int i=pos ; i < node->words.size()-1 ; ++i)
					{
						node->words[i+1]=node->words[i];
						node->pointers[i+1]=node->pointers[i];
					}

					node->words[pos]=word;

					index->id_file.pushback(id_file);
					index->relevance.pushback(relevance);

					radix_trie_node child = new radix_trie_node;
					child->index = index;

					node->pointers[pos]=child;
					//TODO asegurrarnos que se mantienen en orden los pointers de nodo
				}
			}
			else //si no tiene hijos
			{
				radix_trie_index index = new radix_trie_index;
				index->id_file.pushback(id_file);
				index->relevance.pushback(relevance);

				radix_trie_node child = new radix_trie_node;
				child->index = index;

				node->pointers.pushback(child);
			}
		}
		else // word==""
		{
			nodo->index->id_file.pushback(id_file);
			nodo->index->relevance.pushback(relevance);
		}
	}

	radix_trie_index search(radix_trie_index *node,string word);
	{
		
	}
}

class radix_trie_index
{
	vector<string> id_file;
	vector<float> relevance;
}

int	compare_word(string word_node,string word_insert)
{
	int i;
	for(i=0;i<word_node.size();i++)
		if(word_node[i]!=word_insert[i])
			break;
	return i;
}

int main(void)
{
	radix_trie * master = new radix_trie;
	master.insert("dog","1.txt",1.15);
}
