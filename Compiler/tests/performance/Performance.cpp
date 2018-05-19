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

// BOOST_AUTO_TEST_CASE(Performance_Tiny)
// {
// 	std::array<unsigned long long, MAX_RUN_COUNT> times{ };
// 	for (int i = 0; i < 5; i++)
// 	{
// 		Compiler compiler;
// 		auto t1 = TestingTools::getCurrentTime();
// 		compiler.parseFile("TestFiles/Performance/tiny.a");
// 		auto t2 = TestingTools::getCurrentTime();
// 		auto delta = TestingTools::getTimeDelta(t1, t2);
// 		times[i] = delta;
// 		std::cout << "(" << i << ") " << "Tiny time elapsed: " << delta << std::endl;
// 		printf("\n\n");
// 	}
// 	unsigned long long avg = average(times);
// 	std::cout << "Average: " << avg << "microseconds " << (avg / 1000) << "milliseconds\n\n" << std::endl;
// }
//
// BOOST_AUTO_TEST_CASE(Performance_Small)
// {
// 	std::array<unsigned long long, MAX_RUN_COUNT> times{ };
// 	for (int i = 0; i < MAX_RUN_COUNT; i++)
// 	{
// 		Compiler compiler;
// 		auto t1 = TestingTools::getCurrentTime();
// 		compiler.parseFile("TestFiles/Performance/small.a");
// 		auto t2 = TestingTools::getCurrentTime();
// 		auto delta = TestingTools::getTimeDelta(t1, t2);
// 		times[i] = delta;
// 		std::cout << "(" << i << ") " << "Small time elapsed: " << TestingTools::getTimeDelta(t1, t2) << std::endl;
// 		printf("\n\n");
// 	}
// 	unsigned long long avg = average(times);
// 	std::cout << "Average: " << avg << "microseconds " << (avg / 1000) << "milliseconds\n\n" << std::endl;
// }
//
// BOOST_AUTO_TEST_CASE(Performance_Medium)
// {
// 	std::array<unsigned long long, MAX_RUN_COUNT> times{ };
// 	for (int i = 0; i < MAX_RUN_COUNT; i++)
// 	{
// 		Compiler compiler;
// 		auto t1 = TestingTools::getCurrentTime();
// 		compiler.parseFile("TestFiles/Performance/medium.a");
// 		auto t2 = TestingTools::getCurrentTime();
// 		auto delta = TestingTools::getTimeDelta(t1, t2);
// 		times[i] = delta;
// 		std::cout << "(" << i << ") " << "Medium time elapsed: " << TestingTools::getTimeDelta(t1, t2) << std::endl;
// 		printf("\n\n");
// 	}
// 	unsigned long long avg = average(times);
// 	std::cout << "Average: " << avg << "microseconds " << (avg / 1000) << "milliseconds\n\n" << std::endl;
// }
//
// BOOST_AUTO_TEST_CASE(Performance_Large)
// {
// 	std::array<unsigned long long, MAX_RUN_COUNT> times{ };
// 	for (int i = 0; i < MAX_RUN_COUNT; i++)
// 	{
// 		Compiler compiler;
// 		auto t1 = TestingTools::getCurrentTime();
// 		compiler.parseFile("TestFiles/Performance/large.a");
// 		auto t2 = TestingTools::getCurrentTime();
// 		auto delta = TestingTools::getTimeDelta(t1, t2);
// 		times[i] = delta;
// 		std::cout << "(" << i << ") " << "Large time elapsed: " << TestingTools::getTimeDelta(t1, t2) << std::endl;
// 		printf("\n\n");
// 	}
// 	unsigned long long avg = average(times);
// 	std::cout << "Average: " << avg << "microseconds " << (avg / 1000) << "milliseconds\n\n" << std::endl;
// }
int main()
{
    hayai::ConsoleOutputter consoleOutputter;

    hayai::Benchmarker::AddOutputter(consoleOutputter);
    hayai::Benchmarker::RunAllTests();
    return 0;
}
