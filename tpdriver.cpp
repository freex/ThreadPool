#include <iostream>
#include <functional>
#include <algorithm>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include "Threadpool.h"

#include <chrono>

using namespace std;

void gentest(string&, vector<string>& new_data, size_t i);

typedef function<void(string&, vector<string>&, size_t)> fnc;
typedef vector<string> strvec;

mutex mtx;
int main(int argc, char const *argv[])
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;

	fnc g = &gentest;

	strvec data;
	strvec new_data;

	data.resize(1000, "new_string");
	new_data.resize(data.size());

	start = std::chrono::steady_clock::now();


	const size_t size = 1000;

	for (int i = 0; i < new_data.size(); ++i)
	{
		int matrix[size][size];

		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				matrix[i][j] = i + j;
			}
		}

		new_data[i] = ("i");

	}

	end = std::chrono::steady_clock::now();
	
	elapsed_seconds = end-start;
	cout << "no_pool::  " << elapsed_seconds.count() * 1000 << "ms" << endl;





	start = std::chrono::steady_clock::now();
	Threadpool<fnc, strvec, strvec> pool(8); // Allocate 8 threads
	
	end = std::chrono::steady_clock::now();

	elapsed_seconds = end-start;
	cout << "constructor::  " << elapsed_seconds.count() * 1000 << "ms" << endl;



	start = std::chrono::steady_clock::now();

	pool.set_function(g);

	end = std::chrono::steady_clock::now();
	
	elapsed_seconds = end-start;
	cout << "set_function::  " << elapsed_seconds.count() * 1000 << "ms" << endl;


	start = std::chrono::steady_clock::now();

	pool.set_input(ref(data));

	end = std::chrono::steady_clock::now();
	
	elapsed_seconds = end-start;
	cout << "set_input::  " << elapsed_seconds.count() * 1000 << "ms" << endl;




	start = std::chrono::steady_clock::now();
	pool.set_output(ref(new_data));

	end = std::chrono::steady_clock::now();
	
	elapsed_seconds = end-start;
	cout << "set_output::  " << elapsed_seconds.count() * 1000 << "ms" << endl;

	//pool.execute_no_atomic();


	start = std::chrono::steady_clock::now();

	pool.execute_atomic();

	end = std::chrono::steady_clock::now();
	
	elapsed_seconds = end-start;
	cout << "execute_atomic::  " << elapsed_seconds.count() * 1000 << "ms" << endl;



	pool.join();

	end = std::chrono::steady_clock::now();
	
	elapsed_seconds = end-start;
	cout << "join::  " << elapsed_seconds.count() * 1000 << "ms" << endl;

	//new_data = pool.get_output();

	for (int i = 0; i < 5; ++i)
	{
		cout << new_data[i] << endl;
	}

	return 0;
}

void gentest(string&, vector<string>& output, size_t i){
	// string i = "3";
	// if(input[0] == output[0] )
	// 	i = "5";
	// int matrix[1000][1000];

		int matrix[1000][1000];

		for (int i = 0; i < 1000; ++i)
		{
			for (int j = 0; j < 1000; ++j)
			{
				matrix[i][j] = i + j;
			}
		}

		output[i] = ("i");

}