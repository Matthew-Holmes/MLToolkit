#ifndef MLTOOLKIT_TRAINER_H
#define MLTOOLKIT_TRAINER_H

#include "model.h"
#include "modelmutator.h"
#include "neuralnetworkmutator.h"
#include "data.h"

#include <utility>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <functional>
#include <mutex>


namespace mltoolkit {

// WARNING - ModelMutator<MOD> may be getting sliced down

template <typename MOD>
class Trainer;


template <typename MOD>
class ListenerTask
{
public:
	ListenerTask() = delete;
	ListenerTask(bool& b, std::mutex& m, Trainer<MOD>& t)
		: done(b), model_mutex(m), trainer(t) {};
	void operator() () const;
private:
	bool& done;
	std::mutex& model_mutex;
	Trainer<MOD>& trainer;
};

template <typename MOD>
class Trainer {
	friend class ListenerTask<MOD>;
public:
	Trainer(MOD& mod, std::unique_ptr<Data> train, std::unique_ptr<Data> test, int max_it = 9999999)
		: model_ref(std::ref(mod)),
		  model_mut_uptr(std::make_unique<ModelMutator<MOD>>()),
		  train_data_uptr(std::move(train)),
		  test_data_uptr(std::move(test)),
		  it_limit(max_it) {}
	// constructor that takes a ModelMutator
	Trainer(MOD& mod, std::unique_ptr<ModelMutator<MOD>> mut_uptr, std::unique_ptr<Data> train,
		    std::unique_ptr<Data> test, int max_it = 9999999)
		: model_ref(std::ref(mod)),
		  model_mut_uptr(std::move(mut_uptr)),
		  train_data_uptr(std::move(train)),
		  test_data_uptr(std::move(test)),
		  it_limit(max_it) {}

	void do_training();
	void evaluate(int limit = 0);
	void set_it_limit(int max_it) { it_limit = max_it; }
private:
	MOD& model_ref; // works on a copy of the model passed
	std::unique_ptr<ModelMutator<MOD>> model_mut_uptr;
	std::unique_ptr<Data> train_data_uptr;
	std::unique_ptr<Data> test_data_uptr;
	int it_limit;
};




template <typename MOD>
void Trainer<MOD>::do_training() {
	// todo generalise for input/output values
	std::pair<std::vector<double>, std::vector<double>> in_out_vecs;

	// setup for listen->evaluate thread
	std::mutex model_mutex; // mutex for the model data so it can't be copied mid update
	bool done = false; ListenerTask l(done, model_mutex, *this);
	std::thread listening_thread(std::ref(l));
	std::unique_lock<std::mutex> lock(model_mutex); // this thread gets a lock on the model mutex at the start

	int cnt = 0;
		while (*train_data_uptr >> in_out_vecs && cnt < it_limit) {
			if (!lock.owns_lock()) lock.lock(); // only continue if the model data is ok to modify
			cnt++;
			model_mut_uptr->training_mutate(model_ref, in_out_vecs, cnt, it_limit);
			lock.unlock();
		}
	std::cout << "trained for " << cnt << " iterations" << std::endl;
	done = true;
	listening_thread.join();
}

template <typename MOD>
void Trainer<MOD>::evaluate(int limit) {
	std::pair<std::vector<double>, std::vector<double>> test_pair;
	std::vector<double> predicted;

	int cnt = 0; double total_error = 0.0; // for average error

	while (*test_data_uptr >> test_pair && cnt < it_limit) {
		predicted = model_ref.predict(test_pair.first);
		auto it1 = predicted.begin();
		auto it2 = test_pair.second.begin();
		while (	it1 != predicted.end()) {
			total_error += (*it1 - *it2) * (*it1 - *it2);
			it1++; it2++;
		}
		cnt++;
	}
	std::cout << "evaluated on " << cnt << " datapoints" << std::endl;
	std::cout << "average MSE: " << total_error / (predicted.size() * cnt) << std::endl;
}

template <typename MOD>
void ListenerTask<MOD>::operator() () const
{
	//std::thread cin_thread([&c]() { std::cin.get(c); std::cin.putback(c); return; });
	//std::thread cin_thread([&c]() { c = std::cin.peek(); return; });
	//cin_thread.detach(); // TODO maybe flush buffer after this?
	// little thread to keep input ameanable to cin input, puts it back once its got something
	std::string s;
	while (!done) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		// so thread chills out in the background most of the time
		while (std::getline(std::cin, s)) {
			if (done) {
				std::cout << "sorry training finished - this input will be discarded" << std::endl;
				break;
			}
			else if (s == "Y" || s == "y") {
				std::unique_lock<std::mutex> lock(model_mutex);
				Trainer<MOD> tmp(trainer.model_ref, nullptr, std::move(trainer.test_data_uptr)); // copies model data at this point in time
				lock.unlock(); // now the training can continue
				std::cout << "evaluating on 100 datapoints" << std::endl;
				tmp.evaluate(100);
				trainer.test_data_uptr = std::move(tmp.test_data_uptr); // puts it back (we are in a friend class)
				// TODO save this if the user wants
			}
			else {
				std::cout << "sorry only \' y \' inputs are accepted" << std::endl;
			}
		}


	}
	// std::cin.putback('q'); 
	//std::cin.rdbuf()->sputc('x'); 
	//cin_thread.join();
}



} // namespace mltoolkit

#endif // MLTOOLKIT_TRAINER_H
