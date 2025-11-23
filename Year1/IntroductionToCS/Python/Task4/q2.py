def estate_homogeneity(divisions, total_area):
    pass






def check_list (small_list: list, area_after_div: int, curr_indx: int):
    if type(small_list[curr_indx]) == int:
        if area_after_div // len(small_list) == small_list[curr_indx]:
            return True
        else:
            return False
    check_list(small_list[curr_indx], area_after_div // len(small_list), curr_indx) and check_list(small_list[curr_indx], area_after_div // len(small_list), curr_indx + 1)


c = check_list([[50, 50], 100, [25, 25, 25, 24]], 300, 0)
print(c)
