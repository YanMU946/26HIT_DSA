#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

int main() {
    std::vector<int> nums;
    // 生成 -10000 到 10000 的数，但跳过 0
    for (int i = -10000; i <= 10000; ++i) {
        if (i == 0) continue; // 坚决不要 0！
        nums.push_back(i);
    }

    // 随机打乱顺序
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(nums.begin(), nums.end(), g);

    // 截取前 10000 个写入文件
    int count = 10000;
    std::ofstream outfile("unsorted.in");
    if (outfile.is_open()) {
        outfile << count << std::endl; 
        for (int i = 0; i < count; ++i) {
            outfile << nums[i];
            if (i < count - 1) outfile << " ";
        }
        outfile.close();
        std::cout << "成功生成 data.txt！(已剔除所有的 0，共 " << count << " 个不重复整数)" << std::endl;
    }
    return 0;
}
