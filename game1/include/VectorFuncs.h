#include <vector>

#ifndef VECTORFUNCS_H_
#define VECTORFUNCS_H_

template <typename T>
void DeleteFromVector(const std::vector<T>& vector, T const& value) {
    vector.erase(std::remove(begin(vector), end(vector), value), end(vector));
}

#endif  // VECTORFUNCS_H_
