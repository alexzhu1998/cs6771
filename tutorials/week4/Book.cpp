#include "tutorials/week4/Book.h"

Book::operator std::string() const {
	return author_ + ", " + name_;
}
