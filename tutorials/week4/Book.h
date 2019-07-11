// Book.h
#ifndef TUTORIALS_WEEK4_BOOK_H_
#define TUTORIALS_WEEK4_BOOK_H_

#include <string>
#include <ostream>

class Book {
	// public methods
	public:
		
		// Write a function definition for a constructor that takes values for name, author, 
		// isbn and price and uses a member initilaisation list to set the value for each data 
		// member
		Book(const std::string& name, const std::string& author, int isbn, double price):
			name_{name},
			author_{author},
			isbn_{isbn},
			price_{price} {}
		

		// Write the overloaded == operator to compare if two book objects are identical
		friend bool operator==(const Book& a, const Book& b) {
			return (a.name_ == b.name_) && (a.author_ == b.name_) && 
				(a.isbn_ == b.isbn_) && (a.price_ == b.price_);
		}

		// Write the overloaded != operator that calls the already overloaded == operator 
		friend bool operator!=(const Book& lhs, const Book& rhs) {
			return !(lhs == rhs);
		}

		// Write the overloaded < operator to allow you to sort books by their ISBN no.
		friend bool operator<(const Book& lhs, const Book& rhs) {
			return lhs.isbn_ < rhs.isbn_;
		}

		// Write the overloaded << operator to print out the name, author, isbn and price
		friend std::ostream& operator<<(std::ostream& os, const Book& b) {
			os << "Name: " << b.name_ << "\n" << "Author: " << b.author_ << "\n"
				"ISBN: " << b.isbn_ << "\n" << "Price: " << b.price_ << "\n";
			return os;
		}

		// Write the type conversion operator to enable the conversion of the Book class 
		// so a std::string in the form of "author, name"
		operator std::string() const;

		int GetIsbn() const { return isbn_; }
		double GetPrice() const { return price_; }

	// private attributes
	private:
		std::string name_;
		std::string author_;
		int isbn_;
		double price_;
};

#endif // TUTORIALS_WEEK4_BOOK_H_
