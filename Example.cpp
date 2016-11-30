#include <iostream>
#include <sstream>
#include <chrono>

using namespace std;

template < class Func, class... Args >
auto logger(Func&& func, Args&&... args)
    -> typename result_of<Func(Args...)>::type
{
    auto result = forward<Func>(func)(forward<Args>(args)...);
    cout << "Execution result: " << result << endl << flush;
    return result;     
}

string getTimestamp()
{
    ostringstream os;

    time_t now = std::chrono::system_clock::to_time_t(chrono::system_clock::now());
    os << now;
    return os.str();
}

int main(int argc, char ** argv)
{
    logger(getTimestamp);

    int x;
    cin >> x;

    return 0;
}