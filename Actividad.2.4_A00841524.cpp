/*
Programa: Algoritmo Knuth-Morris-Pratt (KMP) para búsqueda de patrones
Autores: Alana Martínez Morales
Matricula: A00841524
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
Complejidad: O(m) donde m es la longitud del patrón
 */
void construirLPS(const string& patron, vector<int>& lps) {
	int longitudPatron = patron.length();
	lps[0] = 0;
	int j = 0;

	for (int i = 1; i < longitudPatron; i++) {
		while (j > 0 && patron[i] != patron[j]) {
			j = lps[j - 1];
		}

		if (patron[i] == patron[j]) {
			j++;
		}

		lps[i] = j;
	}
}

/*
complejidad: O(m) donde m es la longitud del patrón
 */
void mostrarArregloLPS(const vector<int>& lps) {
	cout << "LPS: ";
	for (int i = 0; i < lps.size(); i++) {
		cout << lps[i];
		if (i < lps.size() - 1) {
			cout << " ";
		}
	}
	cout << endl;
}

/*
Complejidad: O(n) donde n es la longitud del patrón
 */
vector<int> buscarPatronKMP(const string& texto, const string& patron, const vector<int>& lps) {
	vector<int> indicesEncontrados;
	int longitudTexto = texto.length();
	int longitudPatron = patron.length();
	int j = 0;

	for (int i = 0; i < longitudTexto; i++) {
		while (j > 0 && texto[i] != patron[j]) {
			j = lps[j - 1];
		}

		if (texto[i] == patron[j]) {
			j++;
		}

		if (j == longitudPatron) {
			indicesEncontrados.push_back(i - longitudPatron + 1);
			j = lps[j - 1];
		}
	}

	return indicesEncontrados;
}

/*
complejidad: O(k) donde k es el número de coincidencias encontradas
 */
void mostrarResultados(const vector<int>& indicesEncontrados) {
	if (indicesEncontrados.empty()) {
		cout << "No se encontraron coincidencias" << endl;
	} else {
		for (int indice : indicesEncontrados) {
			cout << "Patron encontrado en indice: " << indice << endl;
		}
	}
}

/*
 complejidad: O(n + m) donde n es la longitud del texto y m es la longitud del patrón
 */
void ejecutarPrueba(int numeroPrueba, const string& texto, const string& patron) {
	cout << "\n Caso de prueba: " << endl;
	cout << "Texto: " << texto << endl;
	cout << "Patron: " << patron << endl;

	vector<int> lps(patron.length());
	construirLPS(patron, lps);
	mostrarArregloLPS(lps);

	vector<int> indicesEncontrados = buscarPatronKMP(texto, patron, lps);
	mostrarResultados(indicesEncontrados);
}


int main() {
	cout << "Algoritmo KMP" << endl;
	cout << "Busqueda eficiente de patrones en texto" << endl;
	cout << "========================================" << endl;

	ejecutarPrueba(1, "ABABDABACDABABCABAB", "ABABCABAB");
	ejecutarPrueba(2, "AAAAAA", "AAA");
	ejecutarPrueba(3, "ABCDEFG", "HIJ");
	ejecutarPrueba(4, "ABCABCABCABC", "ABCABC");

	cout << "\n========================================" << endl;
	cout << "Fin del programa" << endl;

	return 0;
}