#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>

int main()
{
    std::ifstream file("graph.txt");

    if (!file.is_open()) {
        std::cerr << "�� ������� ������� ����!" << std::endl;
        return 1;
    }
    std::vector<int> content_file;

    // ������ ���������� ������
    int numVertices;
    file >> numVertices;

    // ������ ���������� �����
    int numEdges;
    file >> numEdges;

    // ������ �����
    std::vector<std::vector<int>> matrix(numVertices, std::vector<int>(numVertices, 0));

    for (int i = 0; i < numEdges; ++i)
    {
        int vertex_1, vertex_2;
        file >> vertex_1 >> vertex_2;
        matrix.at(vertex_1).at(vertex_2) = 1;
        if (matrix.at(vertex_2).at(vertex_1) == 0) matrix.at(vertex_2).at(vertex_1) = 1;
    }

    // ������ ��������� �������
    int startVertex;
    file >> startVertex;

    file.close();

    std::unordered_map<int, int> lengths_path;
    std::queue<int> queue;

    for (size_t i = 0; i < matrix.size(); ++i) {
        lengths_path[i] = -1; // -1, �.�. ������� ��� �� ��������
    }

    lengths_path[startVertex] = 0; // ���������� �� ����
    queue.push(startVertex);

    while (!queue.empty()) {
        int currentVertex = queue.front(); // ����� ������� �� �������
        queue.pop();

        for (size_t neighbor = 0; neighbor < matrix[currentVertex].size(); ++neighbor) {
            if (matrix[currentVertex][neighbor] == 1 && lengths_path[neighbor] == -1) {
                lengths_path[neighbor] = lengths_path[currentVertex] + 1;
                queue.push(neighbor);
            }
        }
    }

    for (const auto& pair : lengths_path) {
        std::cout << pair.second << std::endl;
    }
    return 0;
}
