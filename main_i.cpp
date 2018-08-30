#include<string.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<vector>
#include <omp.h>
#include"radix_trie.h"

using namespace std;

int main(void)
{
	radix_trie_node * master = new radix_trie_node;

	ifstream file;
	string line;
	string word;

	string palabra;
	int      id;
	float value;

	int i = 0;

	file.open("foodForTrie.txt");
	while ( getline(file,line) && i<1000000 ){

		istringstream iss(line);
		getline(iss, word,'\t');
        palabra = word;
		getline(iss, word,'\t');
		id = stoi(word);
		getline(iss, word,'\t');
		value = stof(word);

		//if( i%100000 == 0) 
		cout << ++i << endl ;

		master->insert(palabra,id,value);
	}
	file.close();

/*
	master->insert("doge",102,102);
	master->insert("dog",101,102);
	master->insert("doctor",103,104);

	master->insert("dogo",2,4);
	master->insert("dogo",1,3);
	master->insert("dacia",3,2);
	master->insert("dacia",1,2);
	master->insert("dacia",2,6);
	master->insert("dacia",3,2);
*/
	//master->print_radix_trie_node();

	vector<string> query;
	double start_time = omp_get_wtime();
	query.push_back("iglesia");
	query.push_back("nieves");
	double _time = omp_get_wtime() - start_time;

    std::cout << "Tiempo de ejecucion: " << _time << std::endl; 

	vector<radix_trie_index*> result_vector;
	radix_trie_index *result_index;

	for(unsigned int i = 0; i < query.size(); i++)
	{
		result_index=master->search(query[i]);
		if(result_index!=NULL)
		{
			result_index->print_radix_trie_index();
			result_vector.push_back(result_index);
		}
	}

	result_index=AND_results(result_vector);

	cout<<endl<<"---"<<endl;
	if(result_index!=NULL)
		result_index->print_radix_trie_index();
	else
		cout<<"no se han encontrados resultados";

	return 0;
}
