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
        std::cerr << "Не удалось открыть файл!" << std::endl;
        return 1;
    }
    std::vector<int> content_file;

    // Чтение количества вершин
    int numVertices;
    file >> numVertices;

    // Чтение количества ребер
    int numEdges;
    file >> numEdges;

    // Чтение ребер
    std::vector<std::vector<int>> matrix(numVertices, std::vector<int>(numVertices, 0));

    for (int i = 0; i < numEdges; ++i)
    {
        int vertex_1, vertex_2;
        file >> vertex_1 >> vertex_2;
        matrix.at(vertex_1).at(vertex_2) = 1;
        if (matrix.at(vertex_2).at(vertex_1) == 0) matrix.at(vertex_2).at(vertex_1) = 1;
    }

    // Чтение начальной вершины
    int startVertex;
    file >> startVertex;

    file.close();

    std::unordered_map<int, int> lengths_path;
    std::queue<int> queue;

    for (size_t i = 0; i < matrix.size(); ++i) {
        lengths_path[i] = -1; // -1, т.е. вершина еще не посещена
    }

    lengths_path[startVertex] = 0; // Расстояние до себя
    queue.push(startVertex);

    while (!queue.empty()) {
        int currentVertex = queue.front(); // Берем вершину из очереди
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
