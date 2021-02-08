// Copyright
#ifndef SOURCE_B_LINK_HPP_
#define SOURCE_B_LINK_HPP_

#include <utility>
#include <vector>
#include <iostream>
#include <string>

#define MAX 6 //sometimes we need more space before split and avoid find out null pointers
int cantidadNodos = 0;

namespace EDA {
	namespace Concurrent {

		template <std::size_t B, typename Type>
		class BLinkTree {
		public:
			typedef Type data_type;

			struct Nodo {
				data_type cantidadHijos;
				Nodo* nodoPadre;
				Nodo* link;
				data_type arrayValoresHijos[MAX];
				Nodo* arrayPunterosHijos[MAX];
				int nodoID;
				Nodo() {
					cantidadHijos = 0;
					nodoPadre = NULL;
					link = NULL;
					cantidadNodos++;
					nodoID = cantidadNodos;
					for (data_type i = 0; i < MAX; i++) {
						arrayValoresHijos[i] = INT_MAX;
						arrayPunterosHijos[i] = NULL;
					}
				}
			};

			BLinkTree() {}

			~BLinkTree() { delete[] rootNodo; }

			std::size_t size() const { return cantidadDatos; }

			bool empty() const {
				if (rootNodo->cantidadHijos) return true; else { return false; }
			}

			void swap(data_type& a, data_type& b) {
				data_type tmp = a;
				a = b;
				b = tmp;
			}

			void swap(Nodo*& a, Nodo*& b) {
				Nodo* tmp = a;
				a = b;
				b = tmp;
			}

			bool search(data_type valorABuscar, std::string mensaje = "sin_mensaje", Nodo* nodoActual = NULL) const	 {
				if (mensaje != "not_print")std::cout << " |searching_value=" << valorABuscar << "_id=" << mensaje << "_| " << std::endl;

				if (!nodoActual) nodoActual = rootNodo; // only once over here
				
				for (int tmpIndex = 0; tmpIndex <= nodoActual->cantidadHijos; tmpIndex++) {

					if (valorABuscar == nodoActual->arrayValoresHijos[tmpIndex]) {
						if (mensaje != "not_print")std::cout << " |found_it_id=" << mensaje << "_value=" << valorABuscar << "| ";
						return true;
					}
					if (valorABuscar < nodoActual->arrayValoresHijos[tmpIndex] && nodoActual->arrayPunterosHijos[tmpIndex]) {
						return search(valorABuscar, mensaje, nodoActual->arrayPunterosHijos[tmpIndex]);
					}
					else if (valorABuscar < nodoActual->arrayValoresHijos[tmpIndex] && !nodoActual->arrayPunterosHijos[tmpIndex]) {
						//std::cout << " |NO_1_id_" << mensaje << "_" << valorABuscar << "_| ";
						return false;
					}
				}
				if (nodoActual->cantidadHijos == CANTIDAD_PUNTEROS_MAX) {
					return search(valorABuscar, mensaje, nodoActual);
				}
				//std::cout << " |NO_2_id_" << mensaje << "_" << valorABuscar << "_| ";
				return false;
			}

			bool search_(data_type valorABuscar, std::string mensaje = "sin_mensaje", Nodo* nodoActual = NULL) const	 {
				if (mensaje != "not_print")std::cout << " |searching_value=" << valorABuscar << "_id=" << mensaje << "_| " << std::endl;

				if (!nodoActual) nodoActual = rootNodo; // only once over here
				
				for (int tmpIndex = 0; tmpIndex <= nodoActual->cantidadHijos; tmpIndex++) {

					if (valorABuscar == nodoActual->arrayValoresHijos[tmpIndex]) {
						if (mensaje != "not_print")std::cout << " |found_it_id=" << mensaje << "_value=" << valorABuscar << "| ";
						return true;
					}
					if (valorABuscar < nodoActual->arrayValoresHijos[tmpIndex] && nodoActual->arrayPunterosHijos[tmpIndex]) {
						return search(valorABuscar, mensaje, nodoActual->arrayPunterosHijos[tmpIndex]);
					}
					else if (valorABuscar < nodoActual->arrayValoresHijos[tmpIndex] && !nodoActual->arrayPunterosHijos[tmpIndex]) {
						//std::cout << " |NO_1_id_" << mensaje << "_" << valorABuscar << "_| ";
						return false;
					}
				}
				if (nodoActual->cantidadHijos == CANTIDAD_PUNTEROS_MAX) {
					return search(valorABuscar, mensaje, nodoActual);
				}
				//std::cout << " |NO_2_id_" << mensaje << "_" << valorABuscar << "_| ";
				return false;
			}

			void separadorHojasSinHijos(Nodo* nodoWorkerIzquierdo) {
				//std::cout << "ELEMTONS EN SPLIT " << nodoWorkerIzquierdo->arrayValoresHijos[0] << "|" << nodoWorkerIzquierdo->arrayValoresHijos[1] << "|" << nodoWorkerIzquierdo->arrayValoresHijos[2] << "|"        << nodoWorkerIzquierdo->arrayValoresHijos[3] <<"|"          << std::endl;

				data_type cantidadHijosALosLados, tmp01, tmp02;

				if (CANTIDAD_PUNTEROS_MAX % 2)
					cantidadHijosALosLados = (CANTIDAD_PUNTEROS_MAX + 1) / 2;
				else cantidadHijosALosLados = CANTIDAD_PUNTEROS_MAX / 2;

				Nodo* nodoDerecho = new Nodo();

				nodoWorkerIzquierdo->cantidadHijos = cantidadHijosALosLados;
				nodoDerecho->cantidadHijos = CANTIDAD_PUNTEROS_MAX - cantidadHijosALosLados;
				nodoDerecho->nodoPadre = nodoWorkerIzquierdo->nodoPadre;

				for (tmp01 = cantidadHijosALosLados, tmp02 = 0; tmp01 < CANTIDAD_PUNTEROS_MAX; tmp01++, tmp02++) {
					nodoDerecho->arrayValoresHijos[tmp02] = nodoWorkerIzquierdo->arrayValoresHijos[tmp01];
					nodoWorkerIzquierdo->arrayValoresHijos[tmp01] = INT_MAX;
				}
				//B-LINK IMPLEMENTATION
				if (nodoWorkerIzquierdo->link) nodoDerecho->link = nodoWorkerIzquierdo->link;
				nodoWorkerIzquierdo->link = nodoDerecho;
				//B-LINK IMPLEMENTATION

				data_type valorQueAsciende = nodoDerecho->arrayValoresHijos[0];

				if (!nodoWorkerIzquierdo->nodoPadre) { //SI NO HAY PADRE
					Nodo* nodoPadre = new Nodo();
					nodoPadre->nodoPadre = NULL;
					nodoPadre->cantidadHijos = 1;
					nodoPadre->arrayValoresHijos[0] = valorQueAsciende;

					nodoPadre->arrayPunterosHijos[0] = nodoWorkerIzquierdo;
					nodoPadre->arrayPunterosHijos[1] = nodoDerecho;

					nodoWorkerIzquierdo->nodoPadre = nodoDerecho->nodoPadre = nodoPadre;
					rootNodo = nodoPadre;
					return;
				}
				else {   //SI HAY PADRE

					nodoWorkerIzquierdo = nodoWorkerIzquierdo->nodoPadre;

					for (tmp01 = 0; tmp01 <= nodoWorkerIzquierdo->cantidadHijos; tmp01++) {
						if (valorQueAsciende < nodoWorkerIzquierdo->arrayValoresHijos[tmp01]) {
							swap(nodoWorkerIzquierdo->arrayValoresHijos[tmp01], valorQueAsciende);
						}
					}

					nodoWorkerIzquierdo->cantidadHijos++;

					for (tmp01 = 0; tmp01 < nodoWorkerIzquierdo->cantidadHijos; tmp01++) {
						if (nodoDerecho->arrayValoresHijos[0] < nodoWorkerIzquierdo->arrayPunterosHijos[tmp01]->arrayValoresHijos[0]) {
							//std::cout << "A " << nodoWorkerIzquierdo->arrayPunterosHijos[tmp01]->arrayValoresHijos[0] << std::endl;
							//std::cout << "B "<<newChildBlock->arrayValoresHijos[0] <<std::endl;
							swap(nodoWorkerIzquierdo->arrayPunterosHijos[tmp01], nodoDerecho);
							//std::cout << "A " << nodoWorkerIzquierdo->arrayPunterosHijos[tmp01]->arrayValoresHijos[0] << std::endl;
							//std::cout << "B " << newChildBlock->arrayValoresHijos[0] << std::endl;
						}
					}
					nodoWorkerIzquierdo->arrayPunterosHijos[tmp01] = nodoDerecho;

					for (tmp01 = 0; nodoWorkerIzquierdo->arrayPunterosHijos[tmp01]; tmp01++) {
						nodoWorkerIzquierdo->arrayPunterosHijos[tmp01]->nodoPadre = nodoWorkerIzquierdo;//error here
					}
				}

			}

			void separadorConHijos(Nodo* nodoWorkerIzquierdo) {
				data_type cantidadHijosALosLados, tmp01, tmp02;

				cantidadHijosALosLados = CANTIDAD_PUNTEROS_MAX / 2;

				Nodo* nodoDerecho = new Nodo();

				nodoWorkerIzquierdo->cantidadHijos = cantidadHijosALosLados;
				nodoDerecho->cantidadHijos = CANTIDAD_PUNTEROS_MAX - cantidadHijosALosLados - 1;//en files intermedias no se copia el valor
				nodoDerecho->nodoPadre = nodoWorkerIzquierdo->nodoPadre;


				for (tmp01 = cantidadHijosALosLados, tmp02 = 0; tmp01 <= CANTIDAD_PUNTEROS_MAX; tmp01++, tmp02++) {
					nodoDerecho->arrayValoresHijos[tmp02] = nodoWorkerIzquierdo->arrayValoresHijos[tmp01];
					nodoDerecho->arrayPunterosHijos[tmp02] = nodoWorkerIzquierdo->arrayPunterosHijos[tmp01];
					nodoWorkerIzquierdo->arrayValoresHijos[tmp01] = INT_MAX;
					if (tmp01 != cantidadHijosALosLados)nodoWorkerIzquierdo->arrayPunterosHijos[tmp01] = NULL;
				}

				//B-LINK IMPLEMENTATION
				if (nodoWorkerIzquierdo->link) nodoDerecho->link = nodoWorkerIzquierdo->link;
				nodoWorkerIzquierdo->link = nodoDerecho;
				//B-LINK IMPLEMENTATION

				data_type valorQueAsciende = nodoDerecho->arrayValoresHijos[0];
				memcpy(&nodoDerecho->arrayValoresHijos, &nodoDerecho->arrayValoresHijos[1], sizeof(int) * (nodoDerecho->cantidadHijos + 1));
				memcpy(&nodoDerecho->arrayPunterosHijos, &nodoDerecho->arrayPunterosHijos[1], sizeof(rootNodo) * (nodoDerecho->cantidadHijos + 1));


				for (tmp01 = 0; nodoWorkerIzquierdo->arrayPunterosHijos[tmp01]; tmp01++) {
					nodoWorkerIzquierdo->arrayPunterosHijos[tmp01]->nodoPadre = nodoWorkerIzquierdo;
				}
				for (tmp01 = 0; nodoDerecho->arrayPunterosHijos[tmp01]; tmp01++) {
					nodoDerecho->arrayPunterosHijos[tmp01]->nodoPadre = nodoDerecho;
				}

				if (!nodoWorkerIzquierdo->nodoPadre) { //SI NO HAY PADRE
					Nodo* nodoPadre = new Nodo();
					nodoPadre->nodoPadre = NULL;
					nodoPadre->cantidadHijos = 1;
					nodoPadre->arrayValoresHijos[0] = valorQueAsciende;
					nodoPadre->arrayPunterosHijos[0] = nodoWorkerIzquierdo;
					nodoPadre->arrayPunterosHijos[1] = nodoDerecho;

					nodoWorkerIzquierdo->nodoPadre = nodoDerecho->nodoPadre = nodoPadre;

					rootNodo = nodoPadre;
					return;
				}
				else { //SI HAY PADRE

					nodoWorkerIzquierdo = nodoWorkerIzquierdo->nodoPadre;

					for (tmp01 = 0; tmp01 <= nodoWorkerIzquierdo->cantidadHijos; tmp01++) {
						if (valorQueAsciende < nodoWorkerIzquierdo->arrayValoresHijos[tmp01]) {
							swap(nodoWorkerIzquierdo->arrayValoresHijos[tmp01], valorQueAsciende);
						}
					}

					nodoWorkerIzquierdo->cantidadHijos++;

					for (tmp01 = 0; tmp01 < nodoWorkerIzquierdo->cantidadHijos; tmp01++) {
						if (nodoDerecho->arrayValoresHijos[0] < nodoWorkerIzquierdo->arrayPunterosHijos[tmp01]->arrayValoresHijos[0]) {
							swap(nodoWorkerIzquierdo->arrayPunterosHijos[tmp01], nodoDerecho);
						}
					}
					nodoWorkerIzquierdo->arrayPunterosHijos[tmp01] = nodoDerecho;

					for (tmp01 = 0; nodoWorkerIzquierdo->arrayPunterosHijos[tmp01]; tmp01++) {
						nodoWorkerIzquierdo->arrayPunterosHijos[tmp01]->nodoPadre = nodoWorkerIzquierdo;
					}
				}

			}

			void insert_(data_type valueToInsert, std::string mensaje = "sin_mensaje", Nodo* nodoWorkerIzquierdo = NULL) {
				
				if (mensaje != "not_print")std::cout << " valueToInsert inside " << valueToInsert << std::endl;

				if (search_(valueToInsert, mensaje)) {
					//std::cout << " |Reyect_" << valueToInsert <<"_id_"<< mensaje <<"| "<< "\n";
					return;
				}
				if (!nodoWorkerIzquierdo) nodoWorkerIzquierdo = rootNodo;

				for (data_type tmpIndex = 0; tmpIndex <= nodoWorkerIzquierdo->cantidadHijos; tmpIndex++) {
					if (valueToInsert < nodoWorkerIzquierdo->arrayValoresHijos[tmpIndex] && nodoWorkerIzquierdo->arrayPunterosHijos[tmpIndex]) {
						insert_(valueToInsert, mensaje, nodoWorkerIzquierdo->arrayPunterosHijos[tmpIndex]);
						if (nodoWorkerIzquierdo->cantidadHijos == CANTIDAD_PUNTEROS_MAX)
							separadorConHijos(nodoWorkerIzquierdo);
						return;
					}
					else if (valueToInsert < nodoWorkerIzquierdo->arrayValoresHijos[tmpIndex] && !nodoWorkerIzquierdo->arrayPunterosHijos[tmpIndex]) {
						swap(nodoWorkerIzquierdo->arrayValoresHijos[tmpIndex], valueToInsert);
						if (tmpIndex == nodoWorkerIzquierdo->cantidadHijos) {
							nodoWorkerIzquierdo->cantidadHijos++;
							break;
						}
					}
				}

				if (nodoWorkerIzquierdo->cantidadHijos == CANTIDAD_PUNTEROS_MAX) {

					separadorHojasSinHijos(nodoWorkerIzquierdo);
				}
				if (mensaje != "not_print")std::cout << " |ValorInsertado=" << valueToInsert << "_id=" << mensaje << "_| " << std::endl;
			}

			void eliminar(const data_type& arrayValoresHijos) {}

			void real_print(std::vector < Nodo* > vectorImprimiendose) {

				std::vector < Nodo* > vectorSiguienteParaImprimir;

				for (data_type i = 0; i < vectorImprimiendose.size(); i++) {

					Nodo* nodoImprimiendose = vectorImprimiendose[i];

					std::cout << "{";
					data_type tmpIndex;
					for (tmpIndex = 0; tmpIndex < nodoImprimiendose->cantidadHijos; tmpIndex++) {
						if (nodoImprimiendose->arrayPunterosHijos[tmpIndex]) {
							vectorSiguienteParaImprimir.push_back(nodoImprimiendose->arrayPunterosHijos[tmpIndex]);
							std::cout << "[P]";
						}
						else { std::cout << "[N]"; }

						std::cout << nodoImprimiendose->arrayValoresHijos[tmpIndex] << "";

					}
					if (nodoImprimiendose->arrayValoresHijos[tmpIndex] == INT_MAX && nodoImprimiendose->arrayPunterosHijos[tmpIndex]) {
						std::cout << "[P]";
						vectorSiguienteParaImprimir.push_back(nodoImprimiendose->arrayPunterosHijos[tmpIndex]);
					}
					else
					{
						std::cout << "[N]";
					}

					//if (nodoParaImprimir.back()->arrayValoresHijos[j]==)
					std::cout << "}   ";
				}std::cout << std::endl;

				if (vectorSiguienteParaImprimir.size() == 0) {

					vectorImprimiendose.clear();
				}
				else {
					std::cout << std::endl;

					real_print(vectorSiguienteParaImprimir);
				}

			}

			void insert(data_type valueToInsert, std::string mensaje = "sin_mensaje", Nodo* nodoWorkerIzquierdo = NULL) {
				mtx.lock();

				//std::cout << "|INGRESO " << valueToInsert<< std::endl;
				insert_(valueToInsert, mensaje);
				//std::cout << " SALIO|" << std::endl;

				mtx.unlock();
			}

			void print() {
				if (empty()) {
					std::cout << "\n ---------------------- " << "\n";
					std::cout << "     B-LINK TREE EMPTY" << "\n";
					std::cout << "\n ---------------------- " << "\n";
				}
				else
				{
					std::cout << "\n ---------------------------------------------------------------------------------------------------------- " << "\n";
					std::cout << "                                     PRINT OF B-LINK TREE " << "\n";
					std::cout << " ---------------------------------------------------------------------------------------------------------- " << "\n";
					std::vector < Nodo* > toPrint;
					toPrint.clear();
					toPrint.push_back(rootNodo);
					real_print(toPrint);
					std::cout << " ---------------------------------------------------------------------------------------------------------- " << "\n";
				}
			}

			Nodo* rootNodo = new Nodo();
			int CANTIDAD_PUNTEROS_MAX = B + 1;
			std::mutex mtx;
		};

	}  // namespace Concurrent
}  // namespace EDA

#endif  // SOURCE_B_LINK_HPP_
