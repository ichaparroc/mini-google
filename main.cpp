#include<string.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>

using namespace std;

int	compare_word(string word_node,string word_insert)
{
	unsigned int i;
	for(i=0 ; i<word_node.size() ; i++)
		if(word_node[i] != word_insert[i])
			break;
	return i;
}


class radix_trie_index
{
	public:
	vector<string> id_file;
	vector<float> relevance;

	unsigned int elements=0;

	void print_radix_trie_index(radix_trie_index *index)
	{
		cout<<"{";
		for(unsigned int i=0 ; i < index->id_file.size() ; i++)
			cout<< index->id_file[i] << ":" << index->relevance[i] << endl;
		cout << "}";
	}


};

class radix_trie_node
{
	public:
	radix_trie_index *index=NULL;

	unsigned int elements=0;

	vector<string> words;
	vector<radix_trie_node*> pointers;

	void insert(radix_trie_node *node , string word , string id_file, float relevance)
	{
		if(word != "") //no encontro donde aun
		{
			if(node->words.size()>0) //si tiene hijos
			{
				unsigned int equals;
				int match=0;
				unsigned int pos=0;

				while(pos < node->words.size() && word[0] >= node->words[pos][0])
				{
					equals = compare_word(node->words[pos] , word);
					if(equals == 0) {}
					else if(equals < node->words[pos].size()) //SPLIT
					{
						match=1;

						radix_trie_node *father = new radix_trie_node;

						father->words.push_back(node->words[pos].substr(equals));
						father->pointers.push_back(node->pointers[pos]);
						father->elements++;

						node->words[pos]=node->words[pos].substr(0,equals);
						node->pointers[pos]=father;

						insert(node->pointers[pos] , word.substr(equals) , id_file , relevance);

						break;
					}
					else //equals == node->words[i].size() //EXACTO
					{
						match=1;
						insert(node->pointers[pos] , word.substr(equals) , id_file , relevance);
						break;
					}
					pos++;
				}
				if(match==0)  //tiene hijos y no hay match, inserta
				{
					node->words.push_back(node->words.back());
					node->pointers.push_back(node->pointers.back());
					node->elements++;

					for(int i=(int)node->words.size()-2 ; i >= (int)pos ; i--)
					{
						node->words[i+1]=node->words[i];
						node->pointers[i+1]=node->pointers[i];
					}

					radix_trie_node *child = new radix_trie_node;
					radix_trie_index *index = new radix_trie_index;
					child->index=index;

					child->index->id_file.push_back(id_file);
					child->index->relevance.push_back(relevance);
					child->index->elements++;

					node->words[pos] = word;
					node->pointers[pos] = child;
				}
			}
			else //si no tiene hijos
			{
				radix_trie_node *child = new radix_trie_node;
				radix_trie_index *index = new radix_trie_index;
				child->index=index;

				child->index->id_file.push_back(id_file);
				child->index->relevance.push_back(relevance);
				child->index->elements++;

				node->words.push_back(word);
				node->pointers.push_back(child);
				node->elements++;
			}
		}
		else // word==""
		{
			if(node->index==NULL)
			{
				radix_trie_index *index = new radix_trie_index;
				node->index=index;
			}
			node->index->id_file.push_back(id_file);
			node->index->relevance.push_back(relevance);
			node->index->elements++;
		}
	}

	radix_trie_index *search(radix_trie_node *node , string word)
	{
		if(word != "")
		{
			unsigned left=0;
			unsigned right=node->elements-1;
			unsigned pos=(left+right)/2;
			int find=0;
			while(left<=right)
			{
				if(word[0] < node->words[pos][0])
					right=pos-1;
				else if(word[0] > node->words[pos][0])
				{
					left=pos+1;
				}
				else
				{
					find=1;
					int equals = compare_word(node->words[pos] , word);
					node->search(node->pointers[pos],word.substr(equals));
				}
				pos=(left+right)/2;
			}
			if(find==0)
				return NULL;
		}
		else
		{
			return node->index;
		}
	}

	void print_radix_trie_node(radix_trie_node *node)
	{
		cout << endl << "(" << node->elements << ")";
		for(unsigned int i=0 ; i < node->words.size() ; i++)
		{
			cout << endl << node->words[i]  << endl;
			node->index->print_radix_trie_index(node->pointers[i]->index);
			print_radix_trie_node(node->pointers[i]);
		}
	}

};


int main(void)
{
	radix_trie_node * master = new radix_trie_node;
	master->insert(master,"doge","doge.txt",1);
	master->insert(master,"dog","dog.txt",2);
	master->insert(master,"dogo","dogo.txt",3);
	master->insert(master,"doctor","doctor.txt",4);
	master->insert(master,"dacia","dacia.txt",5);
	radix_trie_index *result;
	result=master->search(master,"doge");
	cout<<"algo";
	result->print_radix_trie_index(result);
	return 0;
}
