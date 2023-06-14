

//示例1.假设我们有一个整数数组，我们想要计算这个数组中每个元素的平方和。
// 
//首先，我们来看看Map阶段的代码示例：

#include <iostream>
#include <vector>

std::vector<int> Map(const std::vector<int>& input) {
    std::vector<int> output;
    for (int num : input) {
        int square = num * num;
        output.push_back(square);
    }
    return output;
}


//接下来，我们看看Reduce阶段的代码示例：在这个示例中，Reduce函数接受一个整数数组作为输入，并对数组中的所有元素进行求和操作。
#include <iostream>
#include <vector>

int Reduce(const std::vector<int>& input) {
    int sum = 0;
    for (int num : input) {
        sum += num;
    }
    return sum;
}

//最后，我们将这两个阶段组合起来：
#include <iostream>
#include <vector>

std::vector<int> Map(const std::vector<int>& input) {
    std::vector<int> output;
    for (int num : input) {
        int square = num * num;
        output.push_back(square);
    }
    return output;
}

int Reduce(const std::vector<int>& input) {
    int sum = 0;
    for (int num : input) {
        sum += num;
    }
    return sum;
}

int main() {
    std::vector<int> input = { 1, 2, 3, 4, 5 };

    std::vector<int> mapped = Map(input);
    int reduced = Reduce(mapped);

    std::cout << "Result: " << reduced << std::endl;

    return 0;
}

//在main函数中，我们首先定义了输入数据数组input。然后，我们调用Map函数对输入数据进行映射操作，得到一个新的数组mapped。接下来，我们将mapped数组传递给Reduce函数，对其进行归约操作，得到最终的结果reduced，即平方和。最后，我们将结果打印输出。
//
//请注意，这个示例是一个简化的MapReduce示例，实际的MapReduce实现通常涉及到更复杂的分布式计算框架和数据传输机制。但是，通过这个简单的例子，你可以初步了解MapReduce的基本思想和代码实现。








//示例2：假设我们有一个包含大量文本文件的数据集，我们想要计算这些文件中每个单词的出现次数。
//
//首先，我们来看看Map阶段的代码示例：
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>

std::unordered_map<std::string, int> Map(const std::string& input) {
    std::unordered_map<std::string, int> wordCount;
    std::istringstream iss(input);
    std::string word;

    while (iss >> word) {
        // 移除标点符号和转换为小写以进行单词计数
        std::string cleanedWord;
        for (char ch : word) {
            if (std::isalpha(ch))
                cleanedWord += std::tolower(ch);
        }

        if (!cleanedWord.empty())
            wordCount[cleanedWord]++;
    }

    return wordCount;
}



//接下来，我们看看Reduce阶段的代码示例：
//在这个示例中， Reduce函数接受一个包含多个 wordCount映射的向量作为输入。 它遍历每个映射，并将它们合并为一个最终的 wordCount映射。 对于每个单词，它将累加不同映射中的计数值。
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
#include <iostream>
#include <unordered_map>
#include <string>

std::unordered_map<std::string, int> Reduce(const std::vector<std::unordered_map<std::string, int>>& input) {
    std::unordered_map<std::string, int> wordCount;

    for (const auto& wordMap : input) {
        for (const auto& pair : wordMap) {
            const std::string& word = pair.first;
            int count = pair.second;
            wordCount[word] += count;
        }
    }

    return wordCount;
}







#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <vector>

std::unordered_map<std::string, int> Map(const std::string& input) {
    // Map阶段的代码
}

std::unordered_map<std::string, int> Reduce(const std::vector<std::unordered_map<std::string, int>>& input) {
    // Reduce阶段的代码
}

int main() {
    // 输入数据集的准备
    std::vector<std::string> inputFiles = { "file1.txt", "file2.txt", "file3.txt" };
    std::string mergedInput;

    for (const std::string& file : inputFiles) {
        // 读取文件内容并将其合并为一个字符串
        // 省略文件读取和合并的代码，假设已经将内容存储在了mergedInput中
    }

    // 执行Map阶段
    std::unordered_map<std::string, int> mappedResult = Map(mergedInput);

    // 执行Reduce阶段
    std::unordered_map<std::string, int> reducedResult = Reduce({ mappedResult });

    // 输出结果
    for (const auto& pair : reducedResult) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}
//
//步骤1:
//在 main函数中，我们首先准备了输入数据集，这里简单地使用了一个包含文件名的向量，并将文件内容合并为一个字符串（实际情况可能需要更复杂的文件读取和处理步骤）。
//
//步骤2 :
//然后，我们调用 Map函数对合并后的输入字符串执行映射操作，并获得一个包含每个单词计数的mappedResult映射。
//
//步骤3 :
//接下来，我们将mappedResult映射传递给Reduce函数，对其进行归约操作，得到最终的单词计数结果reducedResult。
//
//步骤4 :
//最后，我们将结果逐个输出。

//这个例子更贴近实际的MapReduce应用，通过将文本数据分为多个块并在分布式环境中处理，可以实现更高效的计算和处理大规模数据集的能力。
//然而，由于MapReduce的实际实现通常依赖于分布式计算框架，如Hadoop或Spark，需要更多的配置和代码来建立整个分布式计算环境。
//以上的示例代码仅仅是为了帮助你理解MapReduce的基本概念和工作原理。



