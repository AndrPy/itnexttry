#include <iostream>
#include <string>
#include <vector>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

using namespace boost::multi_index;

struct Contact
{
	std::string name;
	std::string number;
};

class Phonebook 
{
public:
	using phonebook_multi_index = multi_index_container <
		Contact, indexed_by <
		ordered_unique <
		member < Contact, std::string, &Contact::name > >,
		random_access <>,
		hashed_unique <
		member < Contact, std::string, &Contact::name > >,
		hashed_unique <
		member < Contact, std::string, &Contact::number > >	>>;

	void insert(Contact contact)
	{
		phonebook.insert(contact);
	}

	std::vector<Contact> get_list()
	{
		auto& sorted_names_index = phonebook.get < 0 >();

		std::vector<Contact> list;

		for (auto n : sorted_names_index)
		{
			list.push_back(n);
		}

		std::cout << std::endl;

		return list;
	}

	Contact operator[]( int index)
	{
		auto& random_access_index = phonebook.get < 1 >();

		return random_access_index[index];
	}

	Contact search_by_name(std::string name)
	{
		auto& hashed_names_index = phonebook.get < 2 >();

		return *hashed_names_index.find(name);
	}

	Contact search_by_number(std::string number)
	{
		auto& hashed_numbers_index = phonebook.get < 3 >();

		return *hashed_numbers_index.find(number);
	}

private:

	phonebook_multi_index phonebook;	
};


int main()
{
	Phonebook phonebook;

	phonebook.insert({ "B", "654" });
	phonebook.insert({ "C", "132" });
	phonebook.insert({ "D", "456" });
	phonebook.insert({ "A", "123" });

	std::vector<Contact> list = phonebook.get_list();

	for (auto n : list)
	{
		std::cout << n.name << ' ' << n.number << '\n';
	}

	std::cout << phonebook[3].name << ' ' << phonebook[3].number << '\n';

	std::cout << phonebook.search_by_name("D").number << ' ' << phonebook.search_by_number("123").name<<std::endl;

	return 0;
}