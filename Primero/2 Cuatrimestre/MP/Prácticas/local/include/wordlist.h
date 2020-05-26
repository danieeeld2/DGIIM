/**
 * @file AnsiTerminal.h
 * @author DECSAI
 * @note Fully implemented. No further implementation required.
 */
#ifndef WORDLIST_H
#define WORDLIST_H

#include <string>
#include <memory> 

/**
 * @brief Translate any word into valid characteres only
 * @param word
 * @return ISO Word
 */
std::string normalizeWord(const std::string & word);
/**
 * @brief Translate a ISO char into UTF
 * @param in the ISO char
 * @return the UTF char(s)
 */
std::string toUTF(char in);
/**
 * @brief Translate a ISO string into a UTF string
 * @param in the ISO string
 * @return the UTF string
 */
std::string toUTF(std::string in);
/**
 * @brief Translate a ISO cstring into a UTF string
 * @param in the ISO cstring
 * @return the UTF string
 */
std::string toUTF(const char * in);
/**
 * @brief Translate a UTF string into a ISO string
 * @param in the UTF string
 * @return the ISO string
 */
std::string toISO(std::string in);
/**
 * @brief Translate a UTF cstring into a ISO string
 * @param in the UTF cstring
 * @return the ISO string
 */
std::string toISO(const char * in);

bool is_utf8(const char * string);


static const std::string ALPHABET= toISO("_ABCDEFGHIJKLMNOPQRSTUVWXYZÑ");
static const int ALPHABET_SIZE=ALPHABET.size();
static const std::string MAGIC="SCRABBLE-MP";

// Trie Node class 
class TrieNode { 

public:
	
	std::shared_ptr<TrieNode> *children; 

	// Tracks whether If this Node is the end of 
	// any word stored in Trie 

	bool isWord; 

	// Constructor for TrieNode 
	TrieNode(); 
	~TrieNode(); 

}; 


class Trie { 
	
public: 

	Trie();

	~Trie();


	// Insert word function 
	bool insertWord(std::string trieString);

	// Searching for word whether it is 
	// present in Trie 
	bool searchWord(std::string trieString) const;
	
	bool Partdelete(std::string trieString, std::shared_ptr<TrieNode>&	 
													checkout);

	// For ease of recursion; passing 
	// root to Partdelete 
	bool deleteWord(std::string trieString);

	// Checks whether there is no children present 
	bool isEmptyNode(std::shared_ptr<TrieNode> check) const;

	void toWords() const;
	bool toWords(std::string file) const;
	bool fromWords(std::string file);
	void rtoWords(std::ostream&, std::shared_ptr<TrieNode> p, const std::string s, int & wo) const; 
	void rSave(std::ostream &os, std::shared_ptr<TrieNode> p, int level) const ;
	void rLoad(std::istream &is, std::shared_ptr<TrieNode> p, int level, int &clevel);
	bool save(std::string filename) const;
	bool load(const std::string filename);
	
	friend std::ostream & operator<<(std::ostream & os, const Trie & s);
	friend std::istream & operator>>(std::istream & os, Trie & s);
	int size() const;

	
private:
	// Storing root of the Trie 
	std::shared_ptr<TrieNode> root; 
	int Total_words;
	
	void clear();
}; 

std::ostream & operator<<(std::ostream & os, const Trie & i);

std::istream & operator>>(std::istream & is, Trie & i);


#endif /* WORDLIST_H */

