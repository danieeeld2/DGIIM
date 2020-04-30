/**
 * @file player.h
 * @author DECSAI
 * @note To be implemented by students
 */

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "bag.h"

#define MAXPLAYER 7 /// Max number of letters available for the player

/**
 * @class Player
 * @brief Class used to store the letters owned by the player, which is continuosly changing according to the evolution of the game.
 * It is stored as a CSTRING, with a \0 delimiter and all the internal operations must be carried out EXCLUSIVELY with the functions
 * provided in <cstring> See http://www.cplusplus.com/reference/cstring/ for details about cstrings
 * 
 * All the operations in this class must leave the set of letters ordered lexicographically
 * 
 **Please note that all the characters are stored in ISO8859 standard and in uppercase**
 */
class Player {
private:
	char letters[MAXPLAYER+1]; /// Static vector to store a CSTRING
public:
	/**
	 * @brief Basic constructor and initializer. 
	 */
	Player();
	/**
	 * @brief Returns the number of letters stored.
	 * @return The number of letters
	 */
	int size() const;
	/**
	 * @brief Returns the number of letters stored. Although internally this set is stored in a CSTRING, the return value must be a STRING 
	 * @return The set of letters
	 */
	std::string to_string() const;
	/**
	 * @brief Resets the set of letters to 0 components 
	 */
	void clear();
	/**
	 * @brief Query if a given movement can be supported for the existing letters. That is, all the letters in the movement, including possible 
	 * repetitions, must be present in the stored letters. 
	 * @param s The string that is queried
	 * @return @retval true if the move can be supported by the stored letters, @retval false otherwise
	 */
	bool isValid(const std::string s) const;
	/**
	 * @brief Remove the set of letters of the movement, including possible repetitions, from the set of stored letters
	 * @param m The string that is to be removed
	 * @return @retval true if the move can be supported by the stored letters, @retval false otherwise
	 */
	bool extract(const std::string s);
	/**
	 * @brief Adds a set of additional letters to the existing letters whenever there
	 * is room for them. If the set of additional letters is too large, it does nothing
	 * @param frombag Set of letters to add
	 */
	void add(std::string frombag);
        
};

#endif /* PLAYER_H */

