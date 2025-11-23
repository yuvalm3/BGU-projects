from Animal import Animal
from Exceptions import InvalidInputException

class Fish(Animal):

    def __init__(self, name, age, directionH, x, y, directionV):

        super().__init__(name, age, directionH, x, y)
        if not isinstance(directionV, int):
            raise InvalidInputException
        if (directionV != 0) and (directionV != 1):
            raise InvalidInputException
        self.directionV = directionV


    def get_directionV(self):
        return self.directionV



    def move(self):
        super().move()
        if self.directionV == 0:
            self.y += 1
        else:
            self.y -= 1



    def set_directionV(self, directionV):
        self.directionV = directionV



