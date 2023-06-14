

//ʾ��1.����������һ���������飬������Ҫ�������������ÿ��Ԫ�ص�ƽ���͡�
// 
//���ȣ�����������Map�׶εĴ���ʾ����

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


//�����������ǿ���Reduce�׶εĴ���ʾ���������ʾ���У�Reduce��������һ������������Ϊ���룬���������е�����Ԫ�ؽ�����Ͳ�����
#include <iostream>
#include <vector>

int Reduce(const std::vector<int>& input) {
    int sum = 0;
    for (int num : input) {
        sum += num;
    }
    return sum;
}

//������ǽ��������׶����������
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

//��main�����У��������ȶ�����������������input��Ȼ�����ǵ���Map�������������ݽ���ӳ��������õ�һ���µ�����mapped�������������ǽ�mapped���鴫�ݸ�Reduce������������й�Լ�������õ����յĽ��reduced����ƽ���͡�������ǽ������ӡ�����
//
//��ע�⣬���ʾ����һ���򻯵�MapReduceʾ����ʵ�ʵ�MapReduceʵ��ͨ���漰�������ӵķֲ�ʽ�����ܺ����ݴ�����ơ����ǣ�ͨ������򵥵����ӣ�����Գ����˽�MapReduce�Ļ���˼��ʹ���ʵ�֡�








//ʾ��2������������һ�����������ı��ļ������ݼ���������Ҫ������Щ�ļ���ÿ�����ʵĳ��ִ�����
//
//���ȣ�����������Map�׶εĴ���ʾ����
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>

std::unordered_map<std::string, int> Map(const std::string& input) {
    std::unordered_map<std::string, int> wordCount;
    std::istringstream iss(input);
    std::string word;

    while (iss >> word) {
        // �Ƴ������ź�ת��ΪСд�Խ��е��ʼ���
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



//�����������ǿ���Reduce�׶εĴ���ʾ����
//�����ʾ���У� Reduce��������һ��������� wordCountӳ���������Ϊ���롣 ������ÿ��ӳ�䣬�������Ǻϲ�Ϊһ�����յ� wordCountӳ�䡣 ����ÿ�����ʣ������ۼӲ�ͬӳ���еļ���ֵ��
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
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
    // Map�׶εĴ���
}

std::unordered_map<std::string, int> Reduce(const std::vector<std::unordered_map<std::string, int>>& input) {
    // Reduce�׶εĴ���
}

int main() {
    // �������ݼ���׼��
    std::vector<std::string> inputFiles = { "file1.txt", "file2.txt", "file3.txt" };
    std::string mergedInput;

    for (const std::string& file : inputFiles) {
        // ��ȡ�ļ����ݲ�����ϲ�Ϊһ���ַ���
        // ʡ���ļ���ȡ�ͺϲ��Ĵ��룬�����Ѿ������ݴ洢����mergedInput��
    }

    // ִ��Map�׶�
    std::unordered_map<std::string, int> mappedResult = Map(mergedInput);

    // ִ��Reduce�׶�
    std::unordered_map<std::string, int> reducedResult = Reduce({ mappedResult });

    // ������
    for (const auto& pair : reducedResult) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}
//
//����1:
//�� main�����У���������׼�����������ݼ�������򵥵�ʹ����һ�������ļ����������������ļ����ݺϲ�Ϊһ���ַ�����ʵ�����������Ҫ�����ӵ��ļ���ȡ�ʹ����裩��
//
//����2 :
//Ȼ�����ǵ��� Map�����Ժϲ���������ַ���ִ��ӳ������������һ������ÿ�����ʼ�����mappedResultӳ�䡣
//
//����3 :
//�����������ǽ�mappedResultӳ�䴫�ݸ�Reduce������������й�Լ�������õ����յĵ��ʼ������reducedResult��
//
//����4 :
//������ǽ������������

//������Ӹ�����ʵ�ʵ�MapReduceӦ�ã�ͨ�����ı����ݷ�Ϊ����鲢�ڷֲ�ʽ�����д�������ʵ�ָ���Ч�ļ���ʹ�����ģ���ݼ���������
//Ȼ��������MapReduce��ʵ��ʵ��ͨ�������ڷֲ�ʽ�����ܣ���Hadoop��Spark����Ҫ��������úʹ��������������ֲ�ʽ���㻷����
//���ϵ�ʾ�����������Ϊ�˰��������MapReduce�Ļ�������͹���ԭ��



