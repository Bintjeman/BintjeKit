/*!
 * @author bintjeman
 * @date 19.06.25
 * @name time.cpp
 */
#include "time/time.hpp"
template class bnjkit::time::Clock<std::chrono::milliseconds>;
template class bnjkit::time::Clock<std::chrono::microseconds>;
template class bnjkit::time::Clock<std::chrono::nanoseconds>;
template class bnjkit::time::Pulser<std::chrono::milliseconds>;
template class bnjkit::time::Pulser<std::chrono::microseconds>;
template class bnjkit::time::Pulser<std::chrono::nanoseconds>;
