#include "GettingTxT.h"

int main(int argc, char const *argv[]){
	String pathTo = "/home/victor/Documentos/Algoritmos/Project2/raw.es";

	GettingTxT a = GettingTxT(pathTo);
	a.analyzeArticles();

	return 0;
}