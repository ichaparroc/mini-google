#include "GettingTxT.h"

int main(int argc, char const *argv[]){
	String pathTo = "/home/victor/Documentos/Algoritmos/Project2/raw.test";

	GettingTxT a = GettingTxT(pathTo);
	a.analyzeArticles();
	//a.feedTrie("foodForTrie.txt");
	a.histogram();

	return 0;
}