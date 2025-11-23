def colcat(mat_a, mat_b):
    return rec_helper_colcat(mat_a, mat_b, 0, [])


def rec_helper_colcat(mat_a: list, mat_b: list, i: int, final_mat: list):
    if i == len(mat_a):
        return final_mat
    final_mat.append(mat_a[i] + mat_b[i])
    rec_helper_colcat(mat_a, mat_b, i + 1, final_mat)
    return final_mat


# g = colcat([[6], [7]], [[0, 1], [2, 3]])
# print(g)


def vertical_split(input_mat: list):
    return rec_vertical_split(input_mat, [], [], 0)


def rec_vertical_split(input_mat: list, mat_a: list, mat_b: list, i: int):
    if i == len(input_mat):
        return mat_a, mat_b

    mat_a.append(input_mat[i][: ((len(input_mat[0])) // 2)])
    mat_b.append(input_mat[i][(len(input_mat[0])) // 2:])
    rec_vertical_split(input_mat, mat_a, mat_b, i + 1)
    return (mat_a, mat_b)


# gp = vertical_split([[1,2,3,4,5],[6,7,8,9,10],[11,12,13,14,15],[16,17,18,19,20]])
# print('mat A: ', gp[0], 'mat B:', gp[1])
# print(type(gp))
















