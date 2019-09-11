#include <vector>

#ifndef VECTORFUNCS_H_
#define VECTORFUNCS_H_

template <typename T>
void DeleteFromVector(std::vector<T>& vector, T const& value) {  // NOLINT (runtime/references)
    vector.erase(std::remove(begin(vector), end(vector), value), end(vector));
}

#endif  // VECTORFUNCS_H_
