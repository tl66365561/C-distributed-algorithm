#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

// 节点状态
enum class NodeState {
    Follower,
    Candidate,
    Leader
};

// 节点结构体
struct Node {
    NodeState state;
    int term;
    int votesReceived;

    Node() : state(NodeState::Follower), term(0), votesReceived(0) {}
};

// 模拟选举过程
void simulateElection(std::vector<Node>& nodes) {
    // 随机选举超时时间
    srand(time(nullptr));
    int electionTimeout = rand() % 5000 + 3000;

    int leaderNodeIndex = -1;  // 记录选举出的领导者节点索引

    while (leaderNodeIndex == -1) {
        for (int i = 0; i < nodes.size(); ++i) {
            Node& node = nodes[i];

            switch (node.state) {
            case NodeState::Follower:
                // 检测是否超过选举超时时间，超时则转为Candidate状态
                if (/* 检测是否超时 */) {
                    node.state = NodeState::Candidate;
                    node.term++;
                    node.votesReceived = 1;
                    // 向其他节点发送选举请求
                    // ...
                }
                break;

            case NodeState::Candidate:
                // 检测是否获得超过半数的选票，是则成为Leader状态
                if (/* 检测是否获得超过半数选票 */) {
                    node.state = NodeState::Leader;
                    leaderNodeIndex = i;
                    // 向其他节点发送成为Leader的消息
                    // ...
                }
                else {
                    // 检测是否收到了新的Leader节点消息，是则转为Follower状态
                    // ...
                }
                break;

            case NodeState::Leader:
                // 执行Leader节点的操作，例如日志复制等
                // ...
                break;
            }
        }

        // 模拟等待一段时间，继续下一轮选举
        // ...
    }

    std::cout << "Leader Node: " << leaderNodeIndex << std::endl;
}

int main() {
    // 创建3个节点
    std::vector<Node> nodes(3);

    // 模拟选举过程
    simulateElection(nodes);

    return 0;
}
