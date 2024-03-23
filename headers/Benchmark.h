#pragma once
#ifndef BENCHMARK
#define BENCHMARK
#include <string>
#include <chrono>
#include <vector>

class Benchmark
{
public:
	Benchmark();
	Benchmark(const Benchmark&) = delete;
	Benchmark(Benchmark&&) = delete;
	~Benchmark() = default;
	// starts the timer
	void start();
	// calculates delta and writes it to m_entries
	void reset();
	// write to file
	void write(const std::string& filepath);
private:
	std::vector<double> m_entries;
	std::chrono::steady_clock::time_point m_t1;
	std::chrono::steady_clock::time_point m_t2;
};
#endif // !BENCHMARK
