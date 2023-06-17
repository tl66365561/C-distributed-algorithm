#include <iostream>
#include <string>
#include <hiredis/cluster.h>

int main() {

    // 创建 Redis 集群上下文
    redisClusterContext* clusterContext = redisClusterContextInit();

    // 设置 Redis 集群节点信息
    redisClusterSetOptionAddNodes(clusterContext, "node1:port,node2:port,node3:port");

    // 设置连接超时时间
    struct timeval timeout = { 2, 0 };
    redisClusterSetOptionConnectTimeout(clusterContext, timeout);

    // 连接 Redis 集群
    if (redisClusterConnect2(clusterContext) != REDIS_OK) {
        std::cout << "Failed to connect to Redis cluster!" << std::endl;
        return 1;
    }

    // 写入数据
    std::string key = "mykey";
    std::string value = "myvalue";
    redisReply* reply = (redisReply*)redisClusterCommand(clusterContext, "SET %s %s", key.c_str(), value.c_str());
    if (reply == nullptr) {
        std::cout << "Failed to execute SET command!" << std::endl;
        redisClusterFree(clusterContext);
        return 1;
    }

    // 检查写入结果
    if (reply->type == REDIS_REPLY_STATUS && std::string(reply->str) == "OK") {
        std::cout << "Data written successfully!" << std::endl;
    }
    else {
        std::cout << "Failed to write data!" << std::endl;
    }
    freeReplyObject(reply);

    // 读取数据
    reply = (redisReply*)redisClusterCommand(clusterContext, "GET %s", key.c_str());
    if (reply == nullptr) {
        std::cout << "Failed to execute GET command!" << std::endl;
        redisClusterFree(clusterContext);
        return 1;
    }

    // 处理读取结果
    if (reply->type == REDIS_REPLY_STRING) {
        std::string result(reply->str, reply->len);
        std::cout << "Read data: " << result << std::endl;
    }
    else {
        std::cout << "Failed to read data!" << std::endl;
    }
    freeReplyObject(reply);

    // 关闭连接
    redisClusterFree(clusterContext);

    return 0;
}


//能否看到某条记录写入到了集群中的哪个几点

//
//在 Redis 集群中，具体的数据写入到哪个节点是由集群的数据分片策
//
//要查看某条记录写入到了集群中的哪个节点，可以使用 Redis 的  CLUSTER 命令来获取槽位的映射信息。
//
//下面是一个示例，展示了如何通过 Redis 命令行客户端查看某个键的槽位映射信息：
//

//
//$ redis - cli
//> CLUSTER KEYSLOT mykey
//(integer) 12182
//> CLUSTER NODES
//...（输出节点信息，包括节点的 IP 和端口）...
//
//在上面的示例中，我们使用  CLUSTER KEYSLOT 命令获取了键 mykey 的槽位，得到的槽位号是 12182。然后使用 CLUSTER NODES 命令查看节点信息，找到对应槽位的节点，即可确定该条记录写入到了哪个节点。
//
//请注意，这种方式仅适用于手动查看特定键的槽位映射信息。 在实际应用中，可以使用 Redis 的客户端库来执行这些命令，并通过程序来获取和处理节点信息，以满足具体的需求。