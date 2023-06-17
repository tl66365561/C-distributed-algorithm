//一致性哈希（Consistent Hashing）是一种哈希算法，用于将数据分布到多个节点（服务器）上，同时在节点的增删时最小化数据的迁移量。
//下面是一个简单的C++代码示例，演示了一致性哈希算法的基本实现。


#include <iostream>
#include <map>
#include <string>
#include <functional>

// 哈希函数
typedef std::function<unsigned int(const std::string&)> HashFunction;

// 节点类
class Node {
public:
    Node(const std::string& name) : name(name) {}
    std::string getName() const { return name; }
private:
    std::string name;
};

// 一致性哈希环类
class ConsistentHashRing {
public:
    ConsistentHashRing(const HashFunction& hashFunction) : hashFunction(hashFunction) {}

    // 添加节点
    void addNode(const Node& node) {
        nodes[hashFunction(node.getName())] = node;
    }

    // 移除节点
    void removeNode(const Node& node) {
        nodes.erase(hashFunction(node.getName()));
    }

    // 查找节点
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

// 哈希函数实现：使用C++标准库提供的哈希函数
unsigned int hashFunction(const std::string& key) {
    std::hash<std::string> hasher;
    return hasher(key);
}

int main() {
    // 创建一致性哈希环
    ConsistentHashRing ring(hashFunction);

    // 添加节点
    Node node1("Node 1");
    Node node2("Node 2");
    Node node3("Node 3");
    ring.addNode(node1);
    ring.addNode(node2);
    ring.addNode(node3);

    // 根据键查找节点
    std::string key = "example_key";
    Node node = ring.findNode(key);
    std::cout << "Key '" << key << "' is mapped to Node: " << node.getName() << std::endl;

    // 移除节点
    ring.removeNode(node2);

    // 再次查找节点
    node = ring.findNode(key);
    std::cout << "After removing Node 2, Key '" << key << "' is now mapped to Node: " << node.getName() << std::endl;

    return 0;
}

//
//一致性哈希算法具有以下优点：
//
//数据平衡：一致性哈希算法将数据均匀地分布在节点上，减少了数据倾斜的可能性。当节点数量发生变化时，只需要迁移部分数据，而不是全部数据，从而减少了数据迁移的开销。
//
//扩展性：添加或删除节点时，只会影响相邻节点的数据迁移，而不会影响其他节点，因此可以实现动态的扩展和收缩。
//
//容错性：当节点发生故障时，只需要重新映射受影响的部分数据，而不会影响其他正常节点的数据，从而提高了系统的容错性。
//
//缓存命中率：一致性哈希算法在缓存系统中常被使用，因为它可以将相同的请求映射到相同的节点，提高了缓存命中率，减少了数据的重复计算或访问后端存储的次数。
//
//一致性哈希算法也存在一些缺点：
//
//节点的平衡性：一致性哈希算法在节点数量较少时可能导致数据分布不均匀，某些节点上的数据负载可能过大，而其他节点上的数据负载较轻。
//
//增删节点的开销：当添加或删除节点时，需要进行数据的迁移操作，涉及网络传输和数据同步，可能会带来一定的开销和延迟。
//
//哈希冲突：不同的键可能哈希到同一个节点，这可能导致节点上的负载不平衡。为了解决这个问题，可以采用虚拟节点的技术，即为每个节点引入多个虚拟节点，增加哈希的随机性和平衡性。
//
//需要根据具体的应用场景和需求来评估一致性哈希算法的适用性。在大规模分布式系统中，一致性哈希算法通常被广泛应用，并且可以结合其他技术和优化策略来解决其缺点。