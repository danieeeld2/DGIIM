import random

def main():
    # Define an empty rocklist to append rocks to, define random integers, call functions
    rockList = []
    randPile = random.randint(2, 5)
    randRock = random.randint(1, 9)
    name1, name2 = get_players()

    player = name1 # Set current player to 1 (for switching later)
    
    get_board(rockList, randPile, randRock, player) # Set initial board

    play_again(rockList, randPile, randRock, name1, name2, player) 

# Post: takes no arguments and returns the player names as strings entered by the user            
def get_players():
    return input("Enter player 1 name: "), input("Enter player 2 name: ")

# Pre : accepts empty rockList, random pile and rock as integers, current player as string
# Post: modifies rockList with random piles and stones, prints initial starting board
def get_board(rockList, randPile, randRock, player):

    # Get initial board
    print("Let's look at the board now.")
    print("-" * 25)
    for i in range(0, randPile):
        randRock = random.randint(1, 8)
        print('Pile {}: {}'.format(i + 1, 'O' * randRock))
        rockList.append(randRock)
    print("-" * 25)

    # Call nim function to display computer hints
    nim_sum(rockList, randPile)

# Pre : accepts modified rockList, random integer for piles, current player as string
# Post: returns a string when input is invalid, updates game board for following turns
def get_valid_input(rockList, randPile, player):

    # Begin loop that tests for valid input - if valid, break loop - if not, keep asking
    while True:
        stones = input('{}, how many stones to remove? '.format(player))
        piles = input('Pick a pile to remove from: ')

        # If all condiitons for input are CORRECT, break out of loop
        if (stones and piles) and (stones.isdigit()) and (piles.isdigit()):
            if (int(stones) > 0) and (int(piles) <= len(rockList)) and (int(piles) > 0):
                if (int(stones) <= rockList[int(piles) - 1]):
                    if (int(stones) != 0) and (int(piles) != 0):
                        break
        
        # If not, display this statement
        print("Hmmm. You entered an invalid value. Try again, {}.".format(player))
        
    # Update state
    rockList[int(piles) - 1] -= int(stones)

    # Keep playing game
    continue_game(rockList, randPile, player)

# Pre : accepts modified rockList, random integer for piles, current player as string
# Post: prints out updated game board after moves have been made, displays computer hint
def continue_game(rockList, randPile, player): 
    print("Let's look at the board now.")
    print("-" * 25)
    for i in range(0, randPile):
        print("Pile {}: {}".format(i + 1, 'O' * rockList[i]))

    print("-" * 25)

    # In the case when game is over, do not display computer hint for empty board
    if rockList != [0] * len(rockList):
        nim_sum(rockList, randPile)

    #print(rockList)

# Pre : accepts modified rockList, random integer for piles, names of players, current palyer as string
# Post: prints winner of game, asks if players want to play game again, determine current player
def play_again(rockList, randPile, randRock, name1, name2, player):

    # Begin loop to initiate player switching
    while True:
        get_valid_input(rockList, randPile, player)
        
        # To determine winner, check if rockList contains all 0's on that player's turn
        if rockList == [0] * len(rockList):
            print("{} is the winner of this round!".format(player))
            user = input("Do you want to play again? Enter y for yes, anything for no: ")

            if user.lower() == 'y':
                # reset all conditions, start the game again
                rockList = []
                randPile = random.randint(2, 5)
                name1, name2 = get_players()
                player = name1
                get_board(rockList, randPile, randRock, player)
                get_valid_input(rockList, randPile, player)
                
            else:
                break
            
        # switch players 2->1, 1->2 
        if player == name1:
            player = name2

        else:
            player = name1

# Pre : accepts modified rockList, random integer for piles
# Post: calculates nim sum and prints the computer hint for optimal moves
def nim_sum(rockList, randPile):
    nim = 0

    # Calculate nim sum for all elements in the rockList
    for i in rockList:
        nim = nim ^ i
        
    print("Hint: nim sum is {}.".format(nim))

    # Determine how many rocks to remove from which pile
    stones_to_remove = max(rockList) - nim
    stones_to_remove = abs(stones_to_remove)    

    # Logic for certain configurations on determining how many stones to remove from which pile
    # "rockList.index(max(rockList))+ 1 )" determines the index in rockList at which the biggest
    # pile of stones exists.
    if (nim > 0) and (len(rockList) > 2) and (nim != max(rockList)) and (nim !=1):
        print("Pick {} stones from pile {}".format(stones_to_remove, rockList.index(max(rockList))+ 1 ))

    if (nim > 0) and (len(rockList) > 2) and (nim == max(rockList)) and (nim !=1):
        print("Pick {} stones from pile {}.".format(nim, rockList.index(max(rockList))+ 1 ))

    if nim > 0 and len(rockList) <= 2 and (stones_to_remove != 0):
        print("Pick {} stones from pile {}".format(stones_to_remove, rockList.index(max(rockList))+ 1 ))

    if nim > 0 and len(rockList) <= 2 and (stones_to_remove == 0):
        print("Pick {} stones from pile {}".format(nim, rockList.index(max(rockList))+ 1 ))

    elif (nim == 1) and (len(rockList) <= 2):
        print("Pick {} stones from pile {}".format(nim, rockList.index(max(rockList))+ 1 ))

    if (nim == 1) and (nim == max(rockList)) and (nim != 0) and (len(rockList) > 2):
        print("Pick {} stones from pile {}".format(nim, rockList.index(max(rockList))+ 1))
        
    if nim == 0:
        print("Pick all stones from pile {}.".format(rockList.index(max(rockList))+ 1 ))

main()
