#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <thread>
#include <math.h>
#include <em-odp.h>

class determinantCounterEm {
public:
    int determinant(std::vector<std::vector<int>> matrix, int n) {
        int det = 0;
        std::vector<std::vector<int>> submatrix(n);
        if (n == 2)
            return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
        else {
            for (int x = 0; x < n; x++) {
                int subi = 0;
                for (int i = 1; i < n; i++) {
                    int subj = 0;
                    for (int j = 0; j < n; j++) {
                        if (j == x)
                            continue;
                        submatrix[subi][subj] = matrix[i][j];
                        subj++;
                    }
                    subi++;
                }
                det = det + (pow(-1, x) * matrix[0][x] * determinant(submatrix, n - 1));
            }
        }
        return det;
    }

    void determinantHandler(int id, std::vector<std::vector<std::vector<int>>> matrices, int taskCores) {
        std::vector<std::thread> threads;
        threads.reserve(taskCores);

        std::vector<int> results(matrices.size());

        em_odp_init();
        em_odp_set_num_threads(taskCores);

        for (int i = 0; i < matrices.size(); ++i) {
            em_odp_spawn([&matrices, &results, i, this] {
                results[i] = this->determinant(matrices[i], matrices[i].size());
            });
        }

        em_odp_sync();
        em_odp_finalize();
    }
};

class determinantCounter {
public:
    int determinant(std::vector<std::vector<int>> matrix, int n) {
        int det = 0;
        std::vector<std::vector<int>> submatrix(n);
        if (n == 2)
            return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
        else {
            for (int x = 0; x < n; x++) {
                int subi = 0;
                for (int i = 1; i < n; i++) {
                    int subj = 0;
                    for (int j = 0; j < n; j++) {
                        if (j == x)
                            continue;
                        submatrix[subi][subj] = matrix[i][j];
                        subj++;
                    }
                    subi++;
                }
                det = det + (pow(-1, x) * matrix[0][x] * determinant( submatrix, n - 1 ));
            }
        }
        return det;
    }

    void determinantHandler(std::vector<std::vector<std::vector<int>>> matrices, int taskCores) {
        std::vector<std::thread> threads;
        threads.reserve(taskCores);

//    std::vector<std::vector<std::vector<int>>> matrices = data.get<std::vector<std::vector<std::vector<int>>>>();

        std::vector<int> results(matrices.size());

        for (int i = 0; i < matrices.size(); ++i) {
            threads.emplace_back([this, &matrices, &results, i] {
                results[i] = this->determinant(matrices[i], matrices[i].size());
            });

            if (threads.size() == taskCores || i == matrices.size() - 1) {
                for (auto &t : threads) {
                    t.join();
                }
                threads.clear();
            }
        }
    }

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
