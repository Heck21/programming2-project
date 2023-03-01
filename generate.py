from random import choice, randint, randrange
from string import ascii_uppercase
#
# Define the list of names
names = [
    "Johnathan Boyd", 
    "Alissa Clarke",
    "Urijah Walker", 
    "Angie Fitzpatrick", 
    "Cristofer Rivera",
    "Heidy Alvarado", 
    "Malik Bond", 
    "Joshua Valenzuela", 
    "Joaquin Howard", 
    "Lorenzo Zavala",
    "Solomon Cochran", 
    "Ulises French", 
    "Willow Lynn", 
    "Laney Rivers", 
    "Wendy Morton", 
    "Elian Shepard",
    "Braylon Marsh", 
    "Izabelle Edwards", 
    "Nikolas Jimenez", 
    "Jayda Rivers", 
    "Amelie Cortez", 
    "Greyson Bond",
    "Giovanna Singleton", 
    "Jan Zimmerman", 
    "Carissa Valenzuela", 
    "Ian Prince", 
    "Danica Griffin",
    "Salvador Gallagher", 
    "Jamiya Stark", 
    "Randall Sloan"
]

# Initialize the dictionary for tracking license plate numbers
license_plates = {}

# Write data to file
with open("data.txt", "w") as f:
    for i in range(50):
        numbers = randint(1, 9999)
        letters = [choice(ascii_uppercase), choice(ascii_uppercase)]
        name = choice(names)
        
        if name not in license_plates:
            license_plate = f"{numbers:04}{letters[0]}{letters[1]}"
            license_plates[name] = license_plate
        else:
            license_plate = license_plates[name]

        payment_method = choice(["CASH", "CARD"])

        amount_spent = randrange(2000, 24200, 5)

        f.write(f"{name}\n")
        f.write(f"{license_plate}\n")
        f.write(f"{payment_method}\n")
        f.write(f"{amount_spent}.00\n")
        f.write("\n")
