#include "Animal.hpp"
#include "vector.hpp"
#include <vector>

Animal::Animal() : _type("Animal") {
	std::cout << "Default constructor called (Animal)" << std::endl;
}

Animal::Animal(std::string type) : _type(type) {
	std::cout << "Constructor called (Animal)" << std::endl;
}

Animal::Animal(const Animal &obj) {
	std::cout << "Copy constructor called (Animal)" << std::endl;
	*this = obj;
}

Animal::~Animal() {
	std::cout << "Destructor called (Animal)" << std::endl;
}

void Animal::setType(std::string type) {
	this->_type = type;
}

std::string Animal::getType() const { return (this->_type); }

Animal &Animal::operator=(const Animal &other) {
	std::cout << "Assignation operator called (Animal)" << std::endl;
	this->_type = other.getType();
	return (*this);
}

std::string Animal::makeSound() const {
	return "PHHH-HHH";
}

int main()
{
	Animal cat;
	std::cout << "________________________________________\n";
    {
		ft::vector<Animal> arr(3, cat);
		std::cout << arr.size() <<std::endl;
	}
	std::cout << "________________________________________\n";
	{
		std::vector<Animal> arr(3, cat);
		std::cout << arr.size() <<std::endl;
	}

    return 0;
}