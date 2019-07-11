// Book_main.cpp
#include "tutorials/week4/Book.h"

#include <vector>
#include <algorithm>
#include <iostream>

void print(const std::string& title, const std::vector<Book>& books) {
	std::cout << title << "\n";
	for (const auto& b:books) {
		std::cout << "\t";
		std::cout << b << "\n";
	}

	std::cout << "\n";
}

int main (void) {
	std::vector<Book> books1 {
		Book{"Book1", "Author1", 1, 10},
		Book{"Book2", "Author2", 2, 10},
		Book{"Book3", "Author3", 3, 20}
	};

	std::vector<Book> books2 {
		Book{"Book1", "Author1", 1, 10},
		Book{"Book2", "Author2", 2, 10},
		Book{"Book3", "Author3", 3, 20}
	};

	// Test your < operator using std::sort
	print("Books: ", books1);

	// calls the std::vector equal overload comparison
	std::cout << "Vector books are equal: "
						<< "books1 " << (books1 == books2 ? "==" : "!=")
						<< " books2\n\n";

	std::sort(books1.begin(), books2.end());
	print("Default IBSN sorted books: ", books1);

	std::cout << "Vector books are no longer equal: "
						<< "books1 " << (books1 == books2 ? "==" : "!=")
						<< " books2\n\n";

	std::sort(books1.begin(), books2.end(), []
			(const Book& a, const Book& b) { return a.GetPrice() < b.GetPrice(); }
			);

	print("Price sorted books: ", books1);
}
