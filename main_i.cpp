#include<string.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
#include"radix_trie.h"

using namespace std;

int main(void)
{
	radix_trie_node * master = new radix_trie_node;
	master->insert("doge",102,102);
	master->insert("dog",101,102);
	master->insert("doctor",103,104);

	master->insert("dogo",2,4);
	master->insert("dogo",1,3);
	master->insert("dacia",3,2);
	master->insert("dacia",1,2);
	master->insert("dacia",2,6);
	master->insert("dacia",3,2);

	master->print_radix_trie_node();

	vector<string> query;
	query.push_back("dogo");
	query.push_back("dacia");

	vector<radix_trie_index*> result_vector;
	radix_trie_index *result_index;

	for(unsigned int i = 0; i < query.size(); i++)
	{
		result_index=master->search(query[i]);
		if(result_index!=NULL)
			result_vector.push_back(result_index);
	}

	result_index=AND_results(result_vector);

	cout<<endl<<"---"<<endl;
	result_index->print_radix_trie_index();

	return 0;
}
