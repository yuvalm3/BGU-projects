import Exceptions
from Maabada8 import Hotel


class NotInMiniBarError(Exceptions):

    def __str__(self):
        return f'The item {self.item} does not exist in the mini bar.'
