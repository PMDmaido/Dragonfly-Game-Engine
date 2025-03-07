//
// ObjectList.cpp
//

#include "ObjectList.h"
#include "LogManager.h"
using namespace df;

ObjectList::ObjectList() {
	count = 0;
}

int ObjectList::insert(Object* p_o) {
	if (isFull() || p_o == nullptr) {
		return -1;
	}
	p_obj[count] = p_o;
	count++;
	return 0;
}

int ObjectList::remove(Object* p_o) {
	if (isEmpty() || p_o == nullptr) {
		return -1; 
	}

	for (int i = 0; i < count; i++) {
		if (p_obj[i] == p_o) {
			for (int j = i; j < count - 1; j++) {
				p_obj[j] = p_obj[j + 1];
			}
			count--; 
			return 0;
		}
	}
	
	return -1;
}

void ObjectList::clear() {
	count = 0;
}

int ObjectList::getCount() const {
	return count;
}

bool ObjectList::isEmpty() const {
	return count == 0;
}

bool ObjectList::isFull() const {
	return count >= MAX_OBJECTS;
}

Object*& ObjectList::operator[](int index) {
	return p_obj[index];
}
