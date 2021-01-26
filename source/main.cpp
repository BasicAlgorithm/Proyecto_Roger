// Copyright 2021 Roger Peralta Aranibar
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <string>

#include "b-link.hpp"

std::size_t NUMBER_THREADS = 8;//8

const std::size_t NUMBER_OPERATIONS = 25;//10000

int MIN_VALUE = 1;
int MAX_VALUE = 50;//15000

std::random_device rd;

//std::size_t order_array[10];

class TreeSearcher {
public:
	TreeSearcher(unsigned int id, EDA::Concurrent::BLinkTree<3, int>* b_link)
		: id_(id), b_link_(b_link) {}

	void operator()() {
		std::uniform_int_distribution<int> distribution(MIN_VALUE, MAX_VALUE);
		for (std::size_t i = 0; i < NUMBER_OPERATIONS; ++i) {
			//std::cout << distribution(rd) << "\n";
			std::string mensaje = std::to_string(i);
			b_link_->search(distribution(rd), mensaje);
		}
	}

private:
	unsigned int id_;
	EDA::Concurrent::BLinkTree<3, int>* b_link_;
};

void sequential_insert(EDA::Concurrent::BLinkTree<3, int>* b_link) {
	std::uniform_int_distribution<int> distribution(MIN_VALUE, MAX_VALUE);
	for (std::size_t i = 0; i < NUMBER_OPERATIONS; ++i) {
		//std::cout << "seq " << distribution(rd) << "\n";
		//std::cout << "A seq "<<i+1<<std::endl;

		//std::string mensaje = std::to_string(i); to track operation_id
		std::string mensaje = "not_print"; // to avoid print repeteded insert

		b_link->insert(distribution(rd),mensaje);

	}
}

void run_test() {
	EDA::Concurrent::BLinkTree<3, int> b_link;

	sequential_insert(&b_link);

	b_link.print();

	std::thread* threads = new std::thread[NUMBER_THREADS];

	for (std::size_t i = 0; i < NUMBER_THREADS; ++i) {
		threads[i] = std::thread(TreeSearcher(i, &b_link));
	}
	for (std::size_t i = 0; i < NUMBER_THREADS; ++i) {
		threads[i].join();
	}

	//std::cout<<"\nvalue [1][0] "<<b_link.rootNodo->arrayPunterosHijos[1]->arrayValoresHijos[0];
}

int main() {
	run_test();
	return 0;
}
