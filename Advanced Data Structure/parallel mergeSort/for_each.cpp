#include <vector>
#include <thread>

template<class Iterator, class Function>
Function for_each(Iterator first, Iterator last, Function fn) {
    while (first != last) {
        fn(*first);
        ++first;
    }
    return fn;
}

template<class Iterator, class Function>
Function parallel_for_each(Iterator first, Iterator last, Function fn, int threads_num) {
    std::vector<std::thread> threads;
    Iterator tmp = first;
    int count = 0;
    while (tmp != last) {
        ++tmp;
        ++count;
    }
    int step = (count + threads_num - 1) / threads_num;
    Iterator t_first = first;
    Iterator t_last = first;
    while (t_last != last) {
        for (int i = 0; i < step && t_last != last; ++i) {
            ++t_last;
        }
        threads.emplace_back(std::thread(for_each, t_first, t_last, fn));
        t_first = t_last;
    }

    for (auto &thread: threads) {
        thread.join();
    }
}
