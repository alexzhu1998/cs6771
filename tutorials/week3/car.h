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
		Car(const std::string& manufacturer, int n_seats): manufacturer_{manufacturer}, num_seats_{n_seats} {
			++n_objects;
		}

		// Generates exception
		~Car() noexcept;

		const std::string& GetManufacturer() const;
		int GetNumSeats() const;
	
		static int GetNumCars();
		

 	private:
  	std::string manufacturer_;
  	int num_seats_;
		
		static int n_objects;
};

#endif  // TUTORIALS_WEEK3_CAR_H_
