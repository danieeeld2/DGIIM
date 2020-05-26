/**
 * @file language.h
 * @author DECSAI
 * @brief Fully functional static library to handle languages, which are
 * represented as a full list of allowed words, stored as a tree to make 
 * search efficient O(n) being n the number of letters in the word to 
 * be loocked up
 * @note Fully implemented. No further implementation required.
 */

#ifndef LANGUAGE_H
#define LANGUAGE_H
#include <vector>
#include "wordlist.h"

/**
 * @class Language
 * @brief Class fully implemented. It is used to store and manage all the details concerning 
 * a given language. It includes and make it publicily available some functions in wordlist.h 
 * like those to change the encoding of characters. **All the characters stored in memory use the ISO8859 standard**
 * but characters read from keyboard might follow the UTF standard. These functions allow to change from one to another.
 * - std::string ISO8859toUTF8(const char * in);
 * - std::string UTF8toISO8859(const char * in);
 *  
 * **Please note that all characters are stored in uppercase**
 */
class Language{
public:
	/**
	 * @brief Basic constructor and initializer 
	 */
	Language(); 
	/**
	 * @brief Basic constructor and initializer 
	 * @param language Language chosen according to international rules ISO639-1 https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes
	 * @note If the language chosen does not exists in the folder <root>/languages it throws an exception and stops the program
	 */
	Language(std::string language); 
	/**
	 * @brief Query if a given word exists in the given language 
	 * @param word The word to be queried 
	 * @return @retval true if the word exists in the recorded language, @retval false otherwise
	 */
	bool query(std::string word) const;
	/**
	 * @brief Returns the ISO690 identifier of the language 
	 * @return A string with the ID of the language https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes
	 */
	std::string getLanguage() const;
	/**
	 * @brief Loads the chosen language, which must be under <root>/languages folder
	 * @param lang The ID of the language
	 * @note If the language chosen does not exists in the folder <root>/languages it throws an exception and stops the program
	 */
	void setLanguage(std::string lang);
	/**
	 * @brief Query the frecuency of appearance in Scrabble of the given letter, according to the chosen language 
	 * @param letter	The letter to query
	 * @return The frequency of appearance of the letter in the Scrabble of the given language. It returns @retval 0 if the letter does not appear in the language
	 */
	int getFrequency(char letter) const;
	/**
	 * @brief Query the score in Scrabble of the given letter, according to the chosen language 
	 * @param letter	The letter to query
	 * @return The number of points of the letter in the Scrabble of the given language. It returns @retval 0 if the letter does not appear in the language
	 */
	int getScore(char letter) const;
	/**
	 * @brief Query the full set of available letters (without repetitions) in a given language 
	 * @return A string containing the letters available in ISO8859
	 */
	std::string getLetterSet() const;
private:
	std::string language;	/// Descriptor of the language according to international rules ES (Spanish) EN (English) FR (French)
	Trie wordlist;				/// Tree to efficiently store all the words known for a given language
	std::string letterset;	/// Set of letters defined for the given language. See https://en.m.wikipedia.org/wiki/Scrabble_letter_distributions for more details
	std::vector <int> frequencies,	/// Frecuencies of appearance of each letter according the rules of Scrabble
	scores;									/// Score of each letter according to the rules of Scrabble
	
};


#endif

