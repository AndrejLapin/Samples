#include "pch.h"
#include "Asynchronous.h"

void TestTreadWork()
{
    using namespace std::literals::chrono_literals;

    while (true)
    {
        std::cout << "Tread id=" << std::this_thread::get_id() << " working.\n";
        std::this_thread::sleep_for(1s);
    }
}

static std::mutex s_OutputMutex;

void PrimeFactor(int upTo)
{
    std::ostringstream consoleOutput;

    s_OutputMutex.lock();
    std::cout << "Thread(" << std::this_thread::get_id() << "): Started.\n";
    s_OutputMutex.unlock();
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    int primeNumbersFound = 0;
    int current = 2;

    start = std::chrono::high_resolution_clock::now();
    while (current < upTo)
    {
        int currentFactor = current - 1;
        while (currentFactor > 1 && current % currentFactor != 0)
        {
            currentFactor--;
        }
        /*if (currentFactor <= 1)
        {
            primeNumbersFound++;
            std::cout << current << ", ";
        }*/
        primeNumbersFound += currentFactor <= 1;
        current++;
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    s_OutputMutex.lock();
    std::cout << "Thread(" << std::this_thread::get_id() << "): Amount of prime numbers up to " << upTo << " found: " << primeNumbersFound << "\n"
    << "Thread(" << std::this_thread::get_id() << "): Result found in " << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_seconds).count() << " nanoseconds.\n";
    s_OutputMutex.unlock();
}

void ThreadCalcPrime()
{
    PrimeFactor(100000);
}

void StartThreads(int threadAmount)
{
    std::cout << "Starting threads.\n";
    std::vector<std::thread> threads;
    threads.reserve(threadAmount);

    for (int i = 0; i < threadAmount; i++)
    {
        threads.emplace_back(std::thread(ThreadCalcPrime));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }
    std::cout << "Threads joined.\n";
}

class Functor
{
public:
    Functor() = default;
    Functor(int privateNumber) :m_PrivateNumber(privateNumber) {}
    ~Functor() = default;

    void operator()(int inputNumber)
    {
        std::cout << "Functor private number " << m_PrivateNumber << ". Input number " << inputNumber << "\n";
    }
private:
    int m_PrivateNumber;
};

void StartTasks(int taskAmount)
{
    std::cout << "Starting tasks.\n";
    std::vector<std::future<void>> asyncResults;
    asyncResults.reserve(taskAmount);

    for (int i = 0; i < taskAmount; i++)
    {
        asyncResults.emplace_back(std::async(std::launch::async, PrimeFactor, 100000));
    }
    std::cout << "Tasks launched.\n";
}

void Asynchronous::program()
{
    //StartThreads(50);
    //StartTasks(50);
    Functor coolFunctor(39);
    auto task = std::async(std::launch::async, coolFunctor, 4);
}
