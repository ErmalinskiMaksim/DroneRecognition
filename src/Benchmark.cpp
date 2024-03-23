#include "../headers/Benchmark.h"
#include <numeric>
#include <fstream>

Benchmark::Benchmark()
	: m_t1{}, m_t2{}
{
	m_entries.reserve(10000);
}

void Benchmark::start()
{
	m_t1 = std::chrono::high_resolution_clock::now();
}

void Benchmark::reset()
{
	m_t2 =std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> ms_duration2 = m_t2 - m_t1;
	m_entries.push_back(ms_duration2.count());
	m_t1 = {};
	m_t2 = {};
}

void Benchmark::write(const std::string& filepath)
{
	std::ofstream fout(filepath);
	int size = m_entries.size();
	for (int i = 0; i < size; ++i)
		fout << i << '\t' << m_entries[i] << '\n';
	fout << "Takes on average " << std::accumulate(m_entries.begin(), m_entries.end(), 0) / size << "ms\n";
	fout.close();
}
