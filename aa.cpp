#include <iostream>


// template<int n>
// constexpr int fibonacci() { // 著名的斐波那契数列
// 	if constexpr (n >= 2) //constexpr 如果结合if 使模板编写更加简单 
// 		return fibonacci<n - 1>() + fibonacci < n - 2>(); //依次递归模板参数
// 	else
// 		return n;
// }


int main()
{
    std::cout << __cplusplus << std::endl;
    // std::cout << fibonacci<10>() << std::endl;
    return 0;
}