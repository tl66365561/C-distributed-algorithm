//һ���Թ�ϣ��Consistent Hashing����һ�ֹ�ϣ�㷨�����ڽ����ݷֲ�������ڵ㣨���������ϣ�ͬʱ�ڽڵ����ɾʱ��С�����ݵ�Ǩ������
//������һ���򵥵�C++����ʾ������ʾ��һ���Թ�ϣ�㷨�Ļ���ʵ�֡�


#include <iostream>
#include <map>
#include <string>
#include <functional>

// ��ϣ����
typedef std::function<unsigned int(const std::string&)> HashFunction;

// �ڵ���
class Node {
public:
    Node(const std::string& name) : name(name) {}
    std::string getName() const { return name; }
private:
    std::string name;
};

// һ���Թ�ϣ����
class ConsistentHashRing {
public:
    ConsistentHashRing(const HashFunction& hashFunction) : hashFunction(hashFunction) {}

    // ��ӽڵ�
    void addNode(const Node& node) {
        nodes[hashFunction(node.getName())] = node;
    }

    // �Ƴ��ڵ�
    void removeNode(const Node& node) {
        nodes.erase(hashFunction(node.getName()));
    }

    // ���ҽڵ�
    Node findNode(const std::string& key) const {
        unsigned int hash = hashFunction(key);
        auto it = nodes.lower_bound(hash);
        if (it == nodes.end()) {
            it = nodes.begin();
        }
        return it->second;
    }

private:
    HashFunction hashFunction;
    std::map<unsigned int, Node> nodes;
};

// ��ϣ����ʵ�֣�ʹ��C++��׼���ṩ�Ĺ�ϣ����
unsigned int hashFunction(const std::string& key) {
    std::hash<std::string> hasher;
    return hasher(key);
}

int main() {
    // ����һ���Թ�ϣ��
    ConsistentHashRing ring(hashFunction);

    // ��ӽڵ�
    Node node1("Node 1");
    Node node2("Node 2");
    Node node3("Node 3");
    ring.addNode(node1);
    ring.addNode(node2);
    ring.addNode(node3);

    // ���ݼ����ҽڵ�
    std::string key = "example_key";
    Node node = ring.findNode(key);
    std::cout << "Key '" << key << "' is mapped to Node: " << node.getName() << std::endl;

    // �Ƴ��ڵ�
    ring.removeNode(node2);

    // �ٴβ��ҽڵ�
    node = ring.findNode(key);
    std::cout << "After removing Node 2, Key '" << key << "' is now mapped to Node: " << node.getName() << std::endl;

    return 0;
}

//
//һ���Թ�ϣ�㷨���������ŵ㣺
//
//����ƽ�⣺һ���Թ�ϣ�㷨�����ݾ��ȵطֲ��ڽڵ��ϣ�������������б�Ŀ����ԡ����ڵ����������仯ʱ��ֻ��ҪǨ�Ʋ������ݣ�������ȫ�����ݣ��Ӷ�����������Ǩ�ƵĿ�����
//
//��չ�ԣ���ӻ�ɾ���ڵ�ʱ��ֻ��Ӱ�����ڽڵ������Ǩ�ƣ�������Ӱ�������ڵ㣬��˿���ʵ�ֶ�̬����չ��������
//
//�ݴ��ԣ����ڵ㷢������ʱ��ֻ��Ҫ����ӳ����Ӱ��Ĳ������ݣ�������Ӱ�����������ڵ�����ݣ��Ӷ������ϵͳ���ݴ��ԡ�
//
//���������ʣ�һ���Թ�ϣ�㷨�ڻ���ϵͳ�г���ʹ�ã���Ϊ�����Խ���ͬ������ӳ�䵽��ͬ�Ľڵ㣬����˻��������ʣ����������ݵ��ظ��������ʺ�˴洢�Ĵ�����
//
//һ���Թ�ϣ�㷨Ҳ����һЩȱ�㣺
//
//�ڵ��ƽ���ԣ�һ���Թ�ϣ�㷨�ڽڵ���������ʱ���ܵ������ݷֲ������ȣ�ĳЩ�ڵ��ϵ����ݸ��ؿ��ܹ��󣬶������ڵ��ϵ����ݸ��ؽ��ᡣ
//
//��ɾ�ڵ�Ŀ���������ӻ�ɾ���ڵ�ʱ����Ҫ�������ݵ�Ǩ�Ʋ������漰���紫�������ͬ�������ܻ����һ���Ŀ������ӳ١�
//
//��ϣ��ͻ����ͬ�ļ����ܹ�ϣ��ͬһ���ڵ㣬����ܵ��½ڵ��ϵĸ��ز�ƽ�⡣Ϊ�˽��������⣬���Բ�������ڵ�ļ�������Ϊÿ���ڵ�����������ڵ㣬���ӹ�ϣ������Ժ�ƽ���ԡ�
//
//��Ҫ���ݾ����Ӧ�ó���������������һ���Թ�ϣ�㷨�������ԡ��ڴ��ģ�ֲ�ʽϵͳ�У�һ���Թ�ϣ�㷨ͨ�����㷺Ӧ�ã����ҿ��Խ�������������Ż������������ȱ�㡣