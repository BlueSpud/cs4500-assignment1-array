//lang::CwC
#pragma once
#include <stddef.h>

/**
 * Object: An object. All classes inherit from Object.
 * author: shetty.y@husky.neu.edu, eldrid.s@husky.neu.edu
*/
class Object {
public:

	/**
	 * Constructor.
	*/
	Object() {
	}


	/**
	 * Generates a unique hash for this Object.
	*/
	virtual size_t hash() { return (size_t)this; }

	/**
	 * Destructor.
	*/
	virtual ~Object(){};

	/**
	 * Testing for equality with the given object.
	 * @arg other: the Object you're testing equality against. 
	*/
	virtual bool equals(Object *other) { return other == this; }
};