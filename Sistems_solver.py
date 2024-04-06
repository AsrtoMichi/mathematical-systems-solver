#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np


def name_variable(number, number2):
    base_a = ord('a')
    quotient, remainder = divmod(number, 26)
    letter = chr(remainder + base_a)

    while quotient > 0:
        quotient, remainder = divmod(quotient, 26)
        letter = chr(base_a + remainder) + letter

    letter = letter + "'" * number2 + ": "
    return letter


def get_matrix(dim):
    partial = []
    for x in range(dim):
        partial2 = []
        for y in range(dim + 1):
            partial2.append(int(input(f"{name_variable(y, x)}")))
        partial.append(partial2)
    return np.array(partial)


def solve_system(matrix):
    row = matrix.shape[0]
    partial = np.array(matrix)
    last_column = partial[:, row]
    other_determinants = []

    for i in range(row):
        temp = partial[:row, :row].copy()
        temp[:, i] = last_column
        other_determinants.append(np.linalg.det(temp))

    result = []

    for x in range(row):
        determinant = np.linalg.det(partial[:row, :row])
        result.append(other_determinants[x] / determinant)

    return result


if __name__ == "__main__":
    while True:
        dimension = int(input("Number of unknowns: "))
        matrix = get_matrix(dimension)
        results = solve_system(matrix)
        print(results)
