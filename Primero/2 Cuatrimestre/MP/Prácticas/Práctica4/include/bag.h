/**
 * @file bag.h
 * @author DECSAI
 * @note To be implemented by students
 */
#ifndef BAG_H
#define BAG_H

#include <string>
#include "language.h"
#define MAXBAG 200		/// Max size of the bag of letters

///@warning: Check const methods and parameters
///

/**
 * @class Bag
 * @brief Class to represent the full set of letters of the Scrabble. The
 * number of letters, their score and their frequencies is determined by the
 * rules of the game.
 * 
 * More details https://en.m.wikipedia.org/wiki/Scrabble_letter_distributions
 * 
 * **Please note that all the characters are stored in ISO8859 standard and in uppercase**
*/
class Bag {
private:
	char letters[MAXBAG];		/// Set of letters of the game
	int nletters;					/// Number of available letters
	int id;							/// Aleatorio para el juego
	/**
	 * @brief Returns the position p of the bag
	 * @param p The positon requested
	 * @precond p must be a legal position
	 * @return The character at the position p (ISO)
	 */
	char get(int p) const;		
	/**
	 * @brief Sets the position p of the bag
	 * @param p The positon requested
	 * @param c The character to insert (ISO)
	 * @precond p must be a legal position
	 */
	void set(int p, char c);
public:
	/**
	 * @brief Basic constructor and initializer
	 */
	Bag();
	/**
	 * 
	 */
	void setRandom(int p);
	/**
	 * @brief Define the content of the bag of letters according to 
	 * the rules of the language. See language.h for more details on how to
	 * arrange this set of letters.
	 *		- Language::getLetterSet() returns the set of letters of a given Language
	 *		- Language::getFrequency(char letter) returns the frequency of a letter, that is, the number of times that each letter appears in the bag  
	 * @param l The chosen language
	 */
	void define(const Language &l);	//paso por referencia para no llenar la pila
	/**
	 * @brief Size of the letters set that remain in the bag
	 * @return Number of letters 
	 */
	int size() const;
	/**
	 * @brief Returns the set of letters that remain in the bag
	 * @return The set of letters
	 */
	std::string to_string() const;
	/**
	 * @brief Define, in one step, the full set of letters in the bag 
	 * @param s A string that contains all the letters, and their repetitions
	 */
	void set(std::string s);
	/**
	 * @brief Extracts the first @p n letters remaining in the bag. If the bag
	 * contains less than the required @p n letters, it returns all the remaining letters.
	 * @param n Number of letters to extract
	 * @return The set of the first @p n letters in the bag
	 */
	std::string extract(int n);
};



#endif /* BAG_H */

