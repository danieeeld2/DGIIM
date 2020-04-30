/**
 * @file movelist.h
 * @author DECSAI
 * @note To be implemented by students
 * @warning Review data types, consts and references
 */

#ifndef MOVELIST_H
#define MOVELIST_H

#include "move.h"
#include "language.h"

/**
 * @class Movelist
 * @brief Class used to store a sequence of single movements, where every movement is described in move.h
 * @warning Review data types, consts and references
 */
class Movelist {
public:
	/**
	 * @brief Basic constructor and initializer
	 */
	Movelist();

	/**
	 * @brief Constructor for @p n number of movements
	 * @param nmov Number of movements to store
	 */
	Movelist(int nmov);

	/**
	 * @brief Copy constructor
	 * @param orig The list of movements to be copied
	 */
	Movelist(const Movelist& orig); 

	/**
	 * @brief Destructor
	 */
	~Movelist(); 

	/**
	 * @brief Overloads the assignment operator
	 * @param orig Right hand side of the assignement
	 * @return this Left hand side of the assignement
	 */
	Movelist operator=(const Movelist& orig); 

	/**
	 * @brief Query the set of movements stored
	 * @param p The position of the set, numbered from 0 to size()-1
	 * @precond @p p must be in the interval [0, size()) otherwise, it throws an exception
	 * @return A copy of the movement in the position p.
	 */
	 Move get(int p) const;
        
	/**
	 * @brief Inserts a new movement in the (already existing) position of the set of movements
	 * @param p The position to insert the movement.
	 * @precond @p p must be in the interval [0, size()) otherwise, it throws an exception
	 * @param m The movement to insert
	 */
	void set(int p, const Move &m);

	/**
	 * @brief Query the number of existing movements in the class 
	 * @return The size of the set of movements
	 */
	inline int size() const {return nMove;};

	/**
	 * @brief Searches a movement in the set of recorded movements. Two movements are equal if all their data members coincide.
	 * @param mov The movement to be seeked
	 * @return The position of the movement in the set, @retval -1 when the movement is not found
	 */
	int find(const Move &mov) const;

	/**
	 * @brief Adds a copy of the movement at the end of the existing set, incrementing its size in one more movement
	 * @param mov The new movement
	 */
	void add(const Move &mov);
	/**
	 * @brief Remove the movement from the list and reduces the size in one less movement. If the specified movement
	 * does not exist, the method does nothing 
	 * @param mov The movement to be removed
	 */
	void remove(const Move &mov);
	/**
	 * @brief Remove the movement stored in the position p and reduces the size in one less movement.
	 * @param p The position to be removed
	 * @precond @p p must be in the interval [0, size()) otherwise, it throws an exception
	 */
	void remove(int p);
	/**
	 *	@brief Removes all the movements that contain a word that does not have at least 2 letters
	 * or that does not exist in the given language 
	 * @param l The language 
	 */
	void zip(const Language &l);

	/**
	 * @brief Resets the set and leaves it empty 
	 */
        void clear();
	/**
	 * @brief Computes the whole score of the list of movements by adding the individual scores of each movement contained in the set
	 * of movements. It does not need the language to compute the scores because this is done inside each movement. 
	 * See move.h for more details. If at least one movement scores -1, then 
	 * the full list of movements will score -1.
	 * @return The score of the full set of movements
	 */
	int getScore() const;
	/**
	 * @brief Insert the data of the list of movements into an ostream (either cout or file)
	 * @param os The ostream
	 * @param scores If true, it prints the scores of every single movement. False by default
	 * @return true if there was no problen inserting/writing data
	 */
	bool print(std::ostream &os, bool scores=false) const;
	/**
	 * @brief Reads the movement from an istream until the last movement is marked
	 * as a "H 0 0 @" movement, that is, "H 0 0 _" normalized
	 * @param is The istream
	 * @return True if there was no problem reading data, false otherwise.
	 */
	bool read(std::istream &is);
	

private:
	Move* moves;		/// Dynamic vector of movements
	int nMove;		/// Number of recorded movements
	/**
	 * @brief Allocates memory
	 * @param n The number of movements to be reserved
	 */
	void allocate(int n);
	/**
	 * @brief Frees the memory reserved
	 */
	void deallocate();
	/**
	 * @brief Copy an existing set of movements
	 * @param ml The set of movements to be copied
	 */
	void copy(const Movelist& ml);


};

#endif
