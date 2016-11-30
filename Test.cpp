/*
    Copyright 2016 Daniel Trugman

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <sstream>
#include <functional>
#include <chrono>

#include "catch.hpp"

using namespace std;

ostringstream _out;

template < class Func, class... Args >
auto logger(Func&& func, Args&&... args)
    -> typename result_of<Func(Args...)>::type
{
    auto result = forward<Func>(func)(forward<Args>(args)...);
    _out << "Execution result: " << result << endl << flush;
    return result;     
}

string getTimestamp()
{
    ostringstream os;

    time_t now = std::chrono::system_clock::to_time_t(chrono::system_clock::now());
    os << now;
    return os.str();
}

TEST_CASE("Basic test", "[sanity]")
{
    _out.clear();
    _out.str("");

    SECTION("Different execution thread")
    {
        auto result = logger(getTimestamp);
        REQUIRE(!_out.str().empty());
    }
}