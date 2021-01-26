// Copyright
#ifndef SOURCE_B_LINK_HPP_
#define SOURCE_B_LINK_HPP_

#include <utility>
#include <vector>
#include <iostream>
#include <string>

//#define CANTIDAD_PUNTEROS_MAX 4
#define MAX 6 //CANTIDAD_PUNTEROS_MAX+1

namespace EDA {
	namespace Concurrent {

		template <std::size_t B, typename Type>
		class BLinkTree {
		public:
			typedef Type data_type;

			struct Nodo {
				data_type cantidadHijos;
				Nodo* nodoPadre;
				data_type arrayValoresHijos[MAX];
				Nodo* arrayPunterosHijos[MAX];
				Nodo() {
					cantidadHijos = 0;
					nodoPadre = NULL;
					for (data_type i = 0; i < MAX; i++) {
						arrayValoresHijos[i] = INT_MAX;
						arrayPunterosHijos[i] = NULL;
					}
				}
			};

			BLinkTree() {}

			~BLinkTree() {}

			std::size_t size() const {}

			bool empty() const {}

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

			bool search(data_type valorABuscar, std::string mensaje = "sin_mensaje", Nodo* nodoActual = NULL) {
				//std::cout << " V = " << valorABuscar;
				if (!nodoActual) nodoActual = rootNodo;
				int i = 0;
				for (; i <= nodoActual->cantidadHijos; i++) {
					//std::cout << " |iteracion= " << i<<"|";

					if (valorABuscar == nodoActual->arrayValoresHijos[i]) {
						if (mensaje != "not_print")std::cout << " |found_it/id=" << mensaje << "/value=" << valorABuscar << "| ";
						return true;
					}
					if (valorABuscar < nodoActual->arrayValoresHijos[i] && nodoActual->arrayPunterosHijos[i]) {
						return search(valorABuscar, mensaje, nodoActual->arrayPunterosHijos[i]);
					}
					else if (valorABuscar < nodoActual->arrayValoresHijos[i] && !nodoActual->arrayPunterosHijos[i]) {
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

				data_type valorQueAsciende = nodoDerecho->arrayValoresHijos[0];

				//SI NO HAY PADRE
				if (!nodoWorkerIzquierdo->nodoPadre) {
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

					for (tmp01 = 0;nodoWorkerIzquierdo->arrayPunterosHijos[tmp01]; tmp01++) {
						//std::cout << "tmp01 " << tmp01 << std::endl;
						nodoWorkerIzquierdo->arrayPunterosHijos[tmp01]->nodoPadre = nodoWorkerIzquierdo;
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

				data_type valorQueAsciende = nodoDerecho->arrayValoresHijos[0];
				memcpy(&nodoDerecho->arrayValoresHijos, &nodoDerecho->arrayValoresHijos[1], sizeof(int) * (nodoDerecho->cantidadHijos + 1));
				memcpy(&nodoDerecho->arrayPunterosHijos, &nodoDerecho->arrayPunterosHijos[1], sizeof(rootNodo) * (nodoDerecho->cantidadHijos + 1));


				for (tmp01 = 0; nodoWorkerIzquierdo->arrayPunterosHijos[tmp01]; tmp01++) {
					nodoWorkerIzquierdo->arrayPunterosHijos[tmp01]->nodoPadre = nodoWorkerIzquierdo;
				}
				for (tmp01 = 0; nodoDerecho->arrayPunterosHijos[tmp01]; tmp01++) {
					nodoDerecho->arrayPunterosHijos[tmp01]->nodoPadre = nodoDerecho;
				}

				if (!nodoWorkerIzquierdo->nodoPadre) {
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
				else {   

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

			void insert(data_type valueToInsert, std::string mensaje = "sin_mensaje", Nodo* nodoWorkerIzquierdo = NULL) {//const data_type& 
				//std::cout << " |direct_insert_id=" + mensaje + "_val_"<<val<<"| ";
				if (search(valueToInsert,mensaje)) {
					//std::cout << " |Reyect_" << val <<"_id_"<< mensaje <<"| "<< "\n";
					return; }
				//std::cout << " valorIngresado_insert = " << val << "\n";
				if (!nodoWorkerIzquierdo) nodoWorkerIzquierdo = rootNodo;

				for (data_type tmpIndex = 0; tmpIndex <= nodoWorkerIzquierdo->cantidadHijos; tmpIndex++) {
					if (valueToInsert < nodoWorkerIzquierdo->arrayValoresHijos[tmpIndex] && nodoWorkerIzquierdo->arrayPunterosHijos[tmpIndex]) {
						insert(valueToInsert, mensaje,nodoWorkerIzquierdo->arrayPunterosHijos[tmpIndex]);
						if (nodoWorkerIzquierdo->cantidadHijos == CANTIDAD_PUNTEROS_MAX)
							separadorConHijos(nodoWorkerIzquierdo);
						return;
					}
					else if (valueToInsert < nodoWorkerIzquierdo->arrayValoresHijos[tmpIndex] && !nodoWorkerIzquierdo->arrayPunterosHijos[tmpIndex]) {
						swap(nodoWorkerIzquierdo->arrayValoresHijos[tmpIndex], valueToInsert);
						//swap(nodoWorkerIzquierdo->arrayPunterosHijos[tmp01], newChildBlock);
						if (tmpIndex == nodoWorkerIzquierdo->cantidadHijos) {
							nodoWorkerIzquierdo->cantidadHijos++;
							break;
						}
					}
				}

				if (nodoWorkerIzquierdo->cantidadHijos == CANTIDAD_PUNTEROS_MAX) {

					separadorHojasSinHijos(nodoWorkerIzquierdo);
				}

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
							std::cout << "[P]"; }
						else{ std::cout << "[N]";}

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
				std::cout << std::endl;

			}

			void print() {
				std::vector < Nodo* > toPrint;
				toPrint.clear();
				toPrint.push_back(rootNodo);
				real_print(toPrint);
			}

			Nodo* rootNodo = new Nodo();
			int CANTIDAD_PUNTEROS_MAX = B + 1;
		};

	}  // namespace Concurrent
}  // namespace EDA

#endif  // SOURCE_B_LINK_HPP_
