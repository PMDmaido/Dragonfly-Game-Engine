#pragma once

// ObjectList.cpp

// Engine includes
#include "ObjectList.h"
#include <stdexcept>

namespace df {
	// Default constructor.
	ObjectList::ObjectList() {
		m_count = 0;
		m_p_obj[m_count];
	}

	// Insert object pointer in list.
	// Return 0 if ok, else -1.
	int ObjectList::insert(Object* p_o) {
		if (isFull())
			return -1;
		m_p_obj[m_count] = p_o;
		m_count++;
		return 0;
	}

	// Remove object pointer from list.
	// Return 0 if found, else -1.
	int ObjectList::remove(Object* p_o) {
		int index = -1;
		// Find object location in list.
		for (int i = 0; i < m_count; i++) {
			if (m_p_obj[i] == p_o) {
				index = i;
				break;
			}
		}
		// If not found, return -1.
		if (index == -1)
			return -1;

		/* // Replace with last element (faster but changes order).
		for (int i = 0; i < m_count; i++) {
		if (m_p_obj[i] == p_o) { // Found object
			m_p_obj[i] = m_p_obj[m_count - 1]; // Swap last element in place
			m_count--;
			return 0;
		}
	}		*/

	// Shift list elements down. Slower but keep order.
		for (int i = index; i < m_count - 1; i++) {
			m_p_obj[i] = m_p_obj[i + 1];
		}
		// Reduce count.
		m_count--;
		return 0;
	}

	// Clear list (setting count to 0).
	void ObjectList::clear() {
		m_count = 0;
	}
	// Return count of number of objects in list.
	int ObjectList::getCount() const {
		return m_count;
	}
	// Return true if list is empty, else false.
	bool ObjectList::isEmpty() const {
		return m_count == 0;
	}
	// Return true if list is full, else false.
	bool ObjectList::isFull() const {
		return m_count == MAX_OBJECTS;
	}
	// Index into list.
	Object* ObjectList::operator [](int index) const {
		// Bounds check.
		if (index < 0 || index >= m_count) {
			throw std::out_of_range("Invalid index!");
		}
		return m_p_obj[index];
	}

	// Index into list.
	Object*& ObjectList::operator [](int index) {
		// Bounds check.
		if (index < 0 || index >= m_count) {
			throw std::out_of_range("Invalid index!");
		}
		return m_p_obj[index];
	}

} // end of namespace df