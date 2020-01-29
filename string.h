//lang::CwC 
#pragma once

#include <cstring>
#include <cstdlib>
#include "object.h"

/**
 * String: a class that represents a string as a character array.
 * author: shetty.y@husky.neu.edu, eldrid.s@husky.neu.edu
*/
class String : public Object {
public:
	char* val_; //val_ is to be owned by string, no one else has a pointer to it.
	size_t size_; 

	/**
	 * Constructor.
	 * @arg c: the character array.  
	*/
	String(const char* c) {
	    size_ = strlen(c);
	    val_ = new char[size_ + 1];
	    strcpy(val_, c);
	}

	/**
	 * Overriding the hash from Object class. Generates a unique hash for this String.
	*/
	virtual size_t hash() {
        // Hashing algorithm is djb2 from http://www.cse.yorku.ca/~oz/hash.html
        size_t hash = 5381;
        for (int i = 0; i < size_; i++) {
            hash = ((hash << 5) + hash) + (size_t)val_[i];
        }
        return hash;
	}

	/**
	 * Overriding the equals from Object class. Tests is this String is equal to other.
	 * @arg other: the Object you're testing equality against. 
	*/
	virtual bool equals(Object * other) {
	    String* otherString = dynamic_cast<String*>(other);
	    if (otherString) {
	        return !strcmp(otherString->val_, val_);
	    }
	    return false;
	}

	/**
	 * Compare this string to another to determine order.
	 * Returns a negative value if this comes before, 0 if they're the same, 
	 * positive value if it comes after.
	 * @arg s: the String you're comparing against. 
	*/
    virtual int compare(String *s) {
        return strcmp(val_, s->val_);
    }

	/**
	 * Concatenate the value of this String to the value of the given String.
	 * Return the concatenated char array wrapped in a new String object.
	 * @arg s: the String you want to concatenate. 
	*/
    virtual String* concat(String *s) {
        char* str = new char[size_ + s->size_ + 1];
        strcpy(str, val_);
        strcat(str, s->val_);

        String* newStr = new String(str);
        delete [] str;

        return newStr;
    }

    // compares the strings based on alphabetical order
    virtual int cmp(String *that) { return compare(that); }

	/**
	 * Destructor for this String class.
	*/
	virtual ~String() {
	    delete [] val_;
	}
};