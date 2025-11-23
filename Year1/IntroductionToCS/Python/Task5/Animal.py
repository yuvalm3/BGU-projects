from Exceptions import *
from abc import ABC, abstractmethod


class Animal(ABC):

    def __init__(self, name, age, directionH, x, y):

        # valid input conditions:
        if name == 7:
            raise InvalidInputException
        #if directionH != (0 or 1):
         #   raise InvalidInputException

        self.name = name
        self.age = age
        self.directionH = directionH
        self.x = x
        self.y = y
        self.food = 10
        self.width = 8
        self.height = 5


    def __str__(self):
        return f'{self.name} is {self.age} years old and has {self.food} food.'


    @abstractmethod
    def get_animal(self):
        pass


    @abstractmethod
    def __repr__(self):
        pass


    def get_position(self):
        temp = (self.x, self.y)
        return temp



    def get_directionH(self):
        return self.directionH


    def get_size(self):
        return (self.width, self.height)


    def dec_food(self):
        self.food = self.food - 1
        pass


    def add_food(self, amount):
        self.food += amount




    def inc_age(self):
        self.age += 1



    def move(self):
        if self.directionH == 0:
            self.x -= 1
        else:
            self.x += 1



    def set_directionH(self, directionH):
        self.directionH = directionH



    def starvation(self):
        if self.food == 0:
            print(f' {self.name} died at the age of {self.age} years because it ran out of food.')
            return True
        else:
            return False



    def die(self):
        if self.age >= 120:
            print(f'{self.name} died in a good health.')
            return True
        else:
            return False





#if ((x <= 0) or (y <= 0) or not isinstance(x or y or age or directionH, int) or (name == []) or (age <= 0) or
     #age >= 120):
    #if directionH != (0 or 1):