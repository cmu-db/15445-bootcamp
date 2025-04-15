/**
 * @file auto.cpp
 * @author Abigale Kim (abigalek)
 * @brief 使用 auto 关键字的教程代码。
 */

// 引入 std::cout（用于输出）用于演示目的。
#include <iostream>
// 引入 std::set 库。
#include <set>
// 引入 C++ 字符串库。
#include <string>
// 引入 std::vector 库。
#include <vector>
// 引入 std::unordered_map 库。
#include <unordered_map>

// C++ 的 auto 关键字是一种告诉编译器通过初始化表达式来推断变量类型的关键字。
// 它非常有用，可以提高开发效率（开发者不再需要写出冗长、复杂的类型名）。
// 在 for-each 循环中也很有用。
// 但是，使用 auto 存在风险 —— 开发者可能不清楚自己正在使用的类型，
// 从而容易写出有 bug 或无法正常工作的代码。因此请小心使用！

// 一个带模板参数且名字非常长的基本类，用来展示 auto 的好处。
template <typename T, typename U>
class Abcdefghijklmnopqrstuvwxyz {
   public:
    Abcdefghijklmnopqrstuvwxyz(T instance1, U instance2)
        : instance1_(instance1), instance2_(instance2) {}

    void print() const {
        std::cout << "(" << instance1_ << "," << instance2_ << ")\n";
    }

   private:
    T instance1_;
    U instance2_;
};

// 一个模板函数，返回该类的对象（类名非常长）。
template <typename T>
Abcdefghijklmnopqrstuvwxyz<T, T> construct_obj(T instance) {
    return Abcdefghijklmnopqrstuvwxyz<T, T>(instance, instance);
}

int main() {
    // 使用 auto 关键字初始化变量 a。这里，类型会被推断为 int。
    auto a = 1;

    // 下面是使用 auto 声明基本变量的更多示例。
    // 根据使用的 IDE 不同，它可能会显示 a、b、c 的推断类型。
    auto b = 3.2;
    auto c = std::string("Hello");

    // 对于上述示例来说，auto 并不是特别有用。
    // 正如你所见，直接写 int a = 1;、float b = 3.2;、
    // std::string c = "Hello"; 并不会带来太大负担。
    // 但在类型名很长或模板嵌套复杂时，auto 就很有用了。
    Abcdefghijklmnopqrstuvwxyz<int, int> obj = construct_obj<int>(2);
    auto obj1 = construct_obj<int>(2);

    // 也许一行代码看不出 auto 的优势，
    // 但如果你需要频繁使用这种名字很长的类，那么 auto 将极大减少输入量！

    // 关于 auto 的一个重要注意点是：
    // 默认情况下 auto 会复制对象，这可能会影响性能。
    // 下面这个例子中我们构造了一个 int 类型的 vector，
    // 并想定义一个引用它的变量。

    std::vector<int> int_values = {1, 2, 3, 4};

    // 下面这行代码会将 int_values 深拷贝到 copy_int_values 中，
    // 因为 auto 推断的类型是 std::vector<int>，不是引用 std::vector<int>&。
    auto copy_int_values = int_values;

    // 但是下面这行代码定义了 ref_int_values，它是 int_values 的引用，
    // 所以不会深拷贝 vector。
    auto& ref_int_values = int_values;

    // auto 关键字在遍历 C++ 容器时也非常有用。
    // 例如，我们构造一个 unordered_map，键为 std::string，值为 int，
    // 然后看看不同的遍历方式。

    std::unordered_map<std::string, int> map;
    map.insert({{"andy", 445}, {"jignesh", 645}});

    // unordered_map.cpp 中提到的一种方式是使用 iterator 进行遍历。
    // 比较下面两个循环的可读性。

    std::cout << "Printing elements in map...\n";
    for (std::unordered_map<std::string, int>::iterator it = map.begin();
         it != map.end(); ++it) {
        std::cout << "(" << it->first << "," << it->second << ")"
                  << " ";
    }
    std::cout << std::endl;

    std::cout << "Printing elements in map with auto...\n";
    for (auto it = map.begin(); it != map.end(); ++it) {
        std::cout << "(" << it->first << "," << it->second << ")"
                  << " ";
    }
    std::cout << std::endl;

    // 也可以使用 auto 来遍历 vector 和 set。
    std::vector<int> vec = {1, 2, 3, 4};
    std::cout << "Printing elements in vector with auto...\n";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::set<int> set;
    for (int i = 1; i <= 10; ++i) {
        set.insert(i);
    }

    std::cout << "Printing elements in set with auto...\n";
    for (const auto& elem : set) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 总的来说，auto 是 C++ 中一个非常实用的关键字，
    // 可以帮助我们写出更高效、更整洁、更易读的代码。
    // 实践中，使用 auto 来遍历容器会让代码更清晰。
    // 但如果你不确定变量的实际类型，回退到显式声明也是完全没问题的。

    return 0;
}
