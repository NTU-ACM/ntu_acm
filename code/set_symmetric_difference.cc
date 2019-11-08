//有序数列异或 ab可为两个vector
std::vector<int> v_symDifference;
std::set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(),std::back_inserter(v_symDifference));