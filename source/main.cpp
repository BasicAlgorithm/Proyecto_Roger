// Copyright 2021 Roger Peralta Aranibar
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <string>
#include <sstream>

#include "b-link.hpp"

std::size_t NUMBER_THREADS = 8;

const std::size_t NUMBER_OPERATIONS = 100000;

int MIN_VALUE = 1;
int MAX_VALUE = 15000;

std::random_device rd;

void test(EDA::Concurrent::BLinkTree<3, int>* b_link) {
	std::string mensaje = "not_print"; // to avoid print repeteded 
	b_link->insert(19, mensaje);
	b_link->insert(31, mensaje);
	b_link->insert(34, mensaje);
	b_link->insert(2, mensaje);
	b_link->insert(46, mensaje);
	b_link->insert(11, mensaje);
	b_link->insert(15, mensaje);
	b_link->insert(27, mensaje);
	b_link->insert(5, mensaje);
	b_link->insert(5, mensaje);
	b_link->insert(23, mensaje);
	b_link->insert(38, mensaje);
	b_link->insert(38, mensaje);
	b_link->insert(37, mensaje);
	b_link->insert(16, mensaje);

	std::cout << "TEST 00:   |<espected print>| \n \n"
		<< "{[P]31[P]} \n \n"
		<< "{[P]15[P]23[P]} {[P]38[P]} \n \n"
		<< "{[N]2[N]5[N]11[N]}  {[N]15[N]16[N]19[N]}  {[N]23[N]27[N]}  {[N]31[N]34[N]37[N]}  {[N]38[N]46[N]} \n"
		<< std::endl;

	std::cout << "TEST 01: print horizontal nivel 02\n    |<espected> 15 23 38 |    "
		<< " |<actual> "
		<< b_link->rootNodo->arrayPunterosHijos[0]->arrayValoresHijos[0]
		<< " "
		<< b_link->rootNodo->arrayPunterosHijos[0]->arrayValoresHijos[1]
		<< " "
		<< b_link->rootNodo->arrayPunterosHijos[0]->link->arrayValoresHijos[0]
		<< "|"
		<< std::endl << std::endl;

	std::cout << "TEST 02: print horizontal nivel 01\n    |<espected> 2 5 11 15 16 19 23 27 31 34 37 38 46 |    "
		<< " |<actual> "
		<< b_link->rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->arrayValoresHijos[0]
		<< " "
		<< b_link->rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->arrayValoresHijos[1]
		<< " "
		<< b_link->rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->arrayValoresHijos[2]
		<< " "
		<< b_link->rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->link->arrayValoresHijos[0]
		<< " "
		<< b_link->rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->link->arrayValoresHijos[1]
		<< " "
		<< b_link->rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->link->arrayValoresHijos[2]
		<< " "
		<< b_link->rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->link->link->arrayValoresHijos[0]
		<< " "
		<< b_link->rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->link->link->arrayValoresHijos[1]
		<< " "
		<< b_link->rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->link->link->link->arrayValoresHijos[0]
		<< " "
		<< b_link->rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->link->link->link->arrayValoresHijos[1]
		<< " "
		<< b_link->rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->link->link->link->arrayValoresHijos[2]
		<< " "
		<< b_link->rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->link->link->link->link->arrayValoresHijos[0]
		<< " "
		<< b_link->rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->link->link->link->link->arrayValoresHijos[1]
		<< "|"
		<< std::endl;
}

class TreeSearcher {
public:
	TreeSearcher(unsigned int id, EDA::Concurrent::BLinkTree<3, int>* b_link)
		: id_(id), b_link_(b_link) {}

	void operator()() {
		std::uniform_int_distribution<int> distribution(MIN_VALUE, MAX_VALUE);
		for (std::size_t i = 0; i < NUMBER_OPERATIONS; ++i) {
			//std::cout << distribution(rd) << "\n";
			//std::string mensaje = std::to_string(i); to know id
			std::string mensaje = "not_print"; // to avoid print
			b_link_->search(distribution(rd), mensaje);
		}
	}

private:
	unsigned int id_;
	EDA::Concurrent::BLinkTree<3, int>* b_link_;
};

void sequential_insert(EDA::Concurrent::BLinkTree<3, int>* b_link) {
	std::uniform_int_distribution<int> distribution(MIN_VALUE, MAX_VALUE);
	
	//RANDOM INSERT
	for (std::size_t i = 0; i < NUMBER_OPERATIONS; ++i) {
		
		// to track operation_id
		//std::string mensaje = std::to_string(i);

		// to avoid print repeteded insert with ***SI***
		std::string mensaje = "not_print"; 
		
		b_link->insert(distribution(rd),mensaje);
	}//RANDOM INSERT
}

void run_test() {
	EDA::Concurrent::BLinkTree<3, int> b_link;

	sequential_insert(&b_link);

	//PRINT b-link tree
	//b_link.print();
	//PRINT b-link tree
	
	std::thread* threads = new std::thread[NUMBER_THREADS];

	for (std::size_t i = 0; i < NUMBER_THREADS; ++i) {
		threads[i] = std::thread(TreeSearcher(i, &b_link));
	}
	for (std::size_t i = 0; i < NUMBER_THREADS; ++i) {
		threads[i].join();
	}
	
	//TEST UNIT WITH FULL PRINTED TO PROVE B-LINK TREE WORK
	//test(b_link);
	//TEST UNIT

	//std::cout << "nodos = " << cantidadNodos << "\n";
}

//FINAL TEST ALL ABOVE FROM HERE

void parallel_insert(EDA::Concurrent::BLinkTree<3, int>* b_link,size_t id) {
	std::uniform_int_distribution<int> distribution(MIN_VALUE, MAX_VALUE);
	for (std::size_t i = 0; i < NUMBER_OPERATIONS; ++i) {
		int value = distribution(rd);
		//std::cout << value << "| \n";
		
		// to track operation_id
		//std::string mensaje = std::to_string(id) + "_inserter";

		// to avoid print repeteded insert with ***SI***
		std::string mensaje = "not_print";

		b_link->insert(value,mensaje);
	}
}

void parallel_search(EDA::Concurrent::BLinkTree<3, int>* b_link) {
	std::uniform_int_distribution<int> distribution(MIN_VALUE, MAX_VALUE);
	for (std::size_t i = 0; i < NUMBER_OPERATIONS; ++i) {
		int value = distribution(rd);
		//std::cout << value << "* \n

		// to track operation_id
		//std::string mensaje = std::to_string(i) +"_searcher";

		// to avoid print repeteded insert with ***SI***
		std::string mensaje = "not_print";

		b_link->search(value,mensaje);
	}
}

void run_parallel_asynchronous_test() {
	EDA::Concurrent::BLinkTree<3, int> b_link;

	std::thread* insert_threads = new std::thread[NUMBER_THREADS];
	std::thread* search_threads = new std::thread[NUMBER_THREADS];

	for (std::size_t i = 0; i < NUMBER_THREADS; ++i) {
		insert_threads[i] = std::thread(parallel_insert, &b_link,i);
		search_threads[i] = std::thread(parallel_search, &b_link);
	}
	for (std::size_t i = 0; i < NUMBER_THREADS; ++i) {
		insert_threads[i].join();
		search_threads[i].join();
	}
	
	//PRINT b-link tree
	//b_link.print();
	//PRINT b-link tree
	//std::cout << "nodos = " << cantidadNodos << "\n";

}

int* LAST_VALUE_INSERTED;
std::mutex* MUTEX;
std::condition_variable* VALUE_INSERTED;


void insert_and_notify(EDA::Concurrent::BLinkTree<3, int>* b_link, int id) {
	std::uniform_int_distribution<int> distribution(MIN_VALUE, MAX_VALUE);
	for (std::size_t i = 0; i < NUMBER_OPERATIONS; ++i) {
		std::unique_lock<std::mutex> lock(MUTEX[id]); 
		
		int value = distribution(rd);

		//IMPLEMENTATION OF MESSAGE
		// to track operation_id
		//std::string mensaje = std::to_string(id) + "_inserter";
		// to avoid print repeteded insert with ***SI***
		std::string mensaje = "not_print";
		//IMPLEMENTATION OF MESSAGE

		b_link->insert(value, mensaje);
		
		LAST_VALUE_INSERTED[id] = value;
		//std::cout << "inserted: " <<LAST_VALUE_INSERTED[id] << "\n";
		VALUE_INSERTED[id].notify_one();

		//NEW IMPLEMENTATION
		//{
		//	std::unique_lock<std::mutex> lock(MUTEX[id]);
		//	VALUE_INSERTED[id].wait(lock, [] {return processed; });
		//	processed = false;
		//}
		//NEW IMPLEMENTATION

	}
	std::stringstream stream;
	stream << " Insert finished for thread: " << id << "\n";
	std::cout << stream.str() << "\n";
}

void search_when_notified(EDA::Concurrent::BLinkTree<3, int>* b_link, int id) {
	while (true) {
		//std::cout<<"----------------------------------------------------------- HERE"<<std::endl;
		std::unique_lock<std::mutex> lock(MUTEX[id]);
		VALUE_INSERTED[id].wait(lock);

		//NEW IMPLEMENTATION
		//VALUE_INSERTED[id].wait(lock, [] {return ready; });
		//NEW IMPLEMENTATION

		//std::cout << "----------------------------------------------------------- INSIDE" << std::endl;

		//std::cout << "Searcher: " << LAST_VALUE_INSERTED[id] << "\n";
		
		//IMPLEMENTATION OF MESSAGE
		// to track operation_id
		//std::string mensaje = std::to_string(id) + "_searcher";
		// to avoid print repeteded insert with ***SI***
		std::string mensaje = "not_print";
		//IMPLEMENTATION OF MESSAGE

		if (!b_link->search(LAST_VALUE_INSERTED[id], mensaje)) {
		  std::stringstream stream;
		 stream << " Value not found in B Link: " << LAST_VALUE_INSERTED[id]<< "\n";
		  std::cerr << stream.str() << "\n";
		}
	}
}

void run_parallel_synchronous_test() {
	LAST_VALUE_INSERTED = new int[NUMBER_THREADS];
	MUTEX = new std::mutex[NUMBER_THREADS];
	VALUE_INSERTED = new std::condition_variable[NUMBER_THREADS];

	EDA::Concurrent::BLinkTree<3, int> b_link;

	std::thread* insert_threads = new std::thread[NUMBER_THREADS];
	std::thread* search_threads = new std::thread[NUMBER_THREADS];

	for (std::size_t i = 0; i < NUMBER_THREADS; ++i) {
		search_threads[i] = std::thread(search_when_notified, &b_link, i);
		insert_threads[i] = std::thread(insert_and_notify, &b_link, i);
	}
	for (std::size_t i = 0; i < NUMBER_THREADS; ++i) {
		insert_threads[i].join();
		// do not uncomment the following line
		//search_threads[i].join();
	}
	

	//PRINT b-link tree
	//b_link.print();
	//PRINT b-link tree
	//std::cout << "nodos = " << cantidadNodos << "\n";
}

int main() {

	//PARCIAL TEST - RUN PERFECTLY
	//run_test(); 
	
	//FINAL TEST
	run_parallel_asynchronous_test();
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	run_parallel_synchronous_test();
	
	return 0;
}
