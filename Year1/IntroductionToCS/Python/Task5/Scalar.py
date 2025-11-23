from Animals_lists import scalar_left, scalar_right
from Fish import Fish


class Scalar(Fish):

    #def __init__(self, name, age, x, y, directionH, directionV):

        #super().__init__(name, age, x, y, directionH, directionV)
        #self.directionV = directionV


    def __str__(self):
        return f'The scalar' + super().__str__()



    def get_animal(self):
        if self.directionH == 0:
            return scalar_left
        else:
            return scalar_right


    def __repr__(self):

        if self.directionH == 0:
            new_list = scalar_left
        else:
            new_list = scalar_right

        new_str = ''
        for i in new_list:
            for x in i:
                new_str += f'{x} '
            new_str += '\n'
        temp = new_str
        return temp











yuval = Scalar("Yuval", 25, 3, 4, 0, 1)
a = yuval.__repr__()
print(a)







