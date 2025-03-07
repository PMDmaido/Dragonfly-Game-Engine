#pragma once
// 
// ObjectList.h
//

#include "Object.h"

namespace df {
	const int MAX_OBJECTS = 2000;

	class ObjectList {

	private:
		int count;					//Count of objects in list
		Object* p_obj[MAX_OBJECTS];	//Array of points to objects.

	public:
		ObjectList();

		// Insert object pointer in list.Return 0 if ok, else -1.
		int insert(Object* p_o);

		// Remove object pointer from list. Return 0 if found, else -1.
		int remove(Object* p_o);

		// Clear list (setting count 0).
		void clear();

		// Return count of number of objects in list.
		int getCount() const;

		// Return true if list is empty, else false.
		bool isEmpty() const;

		// Return true if list full, else false.
		bool isFull() const;

		// Index into list.
		Object*& operator[](int index);

	};

}