import Animal

class InvalidInputException(Exception):
    pass


class NotAvailablePlace(Exception):
    pass


class TooSmallAquariumSize(Exception):
    pass


class InvalidAnimalType(Exception):

    def __str__(self):
        return f'Error: {Animal} is an invalid animal type. The valid animal types are: molly, scalar, ocypode, shrimp .'




# try:
#    raise InvalidAnimalType("cat")
# except Exception as e:
#    print(e)


