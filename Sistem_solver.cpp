#include <iostream>
#include <vector>

std::string name_variable(int number, int number2) {
    char base_a = 'a';
    std::string letter;
    int quotient = number;
    int remainder;

    do {
        remainder = quotient % 26;
        letter = static_cast<char>(base_a + remainder) + letter;
        quotient /= 26;
    } while (quotient > 0);

    letter += std::string(number2, '\'') + ": ";
    return letter;
}

double calculate_determinant( std::vector<std::vector<double>>& matrix) {
    int n = matrix.size();
    double det = 1.0;

    for (int j = 0; j < n; ++j) {
        int pivot_row = j;
        while (pivot_row < n && matrix[pivot_row][j] == 0.0) {
            ++pivot_row;
        }

        if (pivot_row == n) {
            return 0.0;
        }


        for (int i = j + 1; i < n; ++i) {
            double ratio = matrix[i][j] / matrix[j][j];
            for (int k = j; k < n; ++k) {
                matrix[i][k] -= ratio * matrix[j][k];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        det *= matrix[i][i];
    }

    return det;
}

std::vector<std::vector<double>> get_matrix(int dim) {
    std::vector<std::vector<double>> partial(dim, std::vector<double>(dim + 1));

    for (int x = 0; x < dim; ++x) {
        for (int y = 0; y <= dim; ++y) {
            std::cout << name_variable(y, x);
            std::cin >> partial[x][y];
        }
    }

    return partial;
}

std::vector<double> solve_system(const std::vector<std::vector<double>>& matrix) {
    int row = matrix.size();
    std::vector<std::vector<double>> partial(matrix);
    std::vector<double> last_column(row);
    std::vector<double> other_determinants;

    for (int i = 0; i < row; ++i) {
        last_column[i] = partial[i][row];
        std::vector<std::vector<double>> temp(partial);
        for (int j = 0; j < row; ++j) {
            temp[j][i] = last_column[i];
        }
        other_determinants.push_back(calculate_determinant(temp));
    }

    std::vector<double> result;

    for (int x = 0; x < row; ++x) {
        double determinant = calculate_determinant(partial);
        result.push_back(other_determinants[x] / determinant);
    }

    return result;
}

int main() {
    while (true) {
        int dimension;
        std::cout << "Number of unknowns: ";
        std::cin >> dimension;

        std::vector<std::vector<double>> matrix = get_matrix(dimension);
        std::vector<double> results = solve_system(matrix);

        std::cout << "Solutions:";
        for (double res : results) {
            std::cout << " " << res;
        }
        std::cout << std::endl;
    }

    return 0;
}
