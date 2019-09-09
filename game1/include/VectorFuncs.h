#ifndef VECTORFUNCS_H
#define VECTORFUNCS_H

template<typename T>
void DeleteFromVector(std::vector<T>& vector, T const& value)
{
    vector.erase(std::remove(begin(vector), end(vector), value), end(vector));
}

#endif
