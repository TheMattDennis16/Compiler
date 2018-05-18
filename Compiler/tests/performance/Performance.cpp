#include <hayai/hayai.hpp>

int long_runner(size_t start, size_t end)
{
    for (int i = start; i < end; i++)
    {
    }
    return 0;
}

BENCHMARK(Test, test_long_runner, 5, 10)
{
    long_runner(0, 100);
}

int main()
{
    hayai::ConsoleOutputter consoleOutputter;

    hayai::Benchmarker::AddOutputter(consoleOutputter);
    hayai::Benchmarker::RunAllTests();
    return 0;
}
