#ifndef TUTORIALS_WEEK3_CAR_H_
#define TUTORIALS_WEEK3_CAR_H_

#include <string>

class Car {
 	public:
  	// TODO(tutorial): fill me in
		//
		// Default constructor if no values are set
		Car(): Car{"unknown", 4} {}

		// I think this is like the constructor
		Car(const std::string& manufacturer, int n_seats): manufacturer_{manufacturer}, 	
																											 num_seats_{n_seats} {
			++n_objects;
		}

		// Copy and move constructors both create a new object. Overloaded functions
		// for move constructor the moved-from object still exists, so you have an 
		// extra object, but when it is destroyed, the object count should be decremented. 
		// So both copy and move need to increase the object count
		
		Car(const Car& other);
		Car(Car&& other) noexcept;
			
		// Assignments simply overwrite one object with the contents of another. Hence 
		// they don't change the object count
		Car& operator=(const Car&) = default;
		Car& operator=(Car&&) = default;

		// Difference between constructor and assignment operatior is that a constructor
		// creates an instance of an object from nothing, while an assignment operator 
		// overwrites an object with the content from an existing one.
		//
		// Difference between copy and move is that move calls the T&& overload of the
		// function. This is usually the faster implementation, which might do something
		// such as steal memory from the moved-from object instead of allocating more.

		// This is the destructor(/)(jokes idk what this actually does)
		~Car() noexcept;

		// public methods
		const std::string& GetManufacturer() const;
		int GetNumSeats() const;
		static int getObjectCount();
		

 	private:
  	std::string manufacturer_;
  	int num_seats_;
		
		static int n_objects;
};

#endif  // TUTORIALS_WEEK3_CAR_H_
