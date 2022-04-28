
#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>
#include <iostream>

class Animal
{
protected:
	std::string _type;

public:
	Animal();
	Animal(std::string type);
	Animal(const Animal &obj);
	virtual ~Animal();

	Animal &operator=(Animal const &other);
	virtual std::string makeSound() const;
	void setType(std::string type);
	std::string getType() const;
};

#endif //ANIMAL_HPP