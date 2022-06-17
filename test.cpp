#include <iostream>
#include <string>
#include <deque>
# ifndef FLAG
#  define FLAG 0
# endif
#if FLAG //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <set>
	#include <stack>
	#include <vector>
	namespace ft = std;
    #define TYPE "STD"
#else
	#include "map.hpp"
	#include "set.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
    #define TYPE "FT"
#endif

#include <fstream>
#include <sys/time.h>
#include <unistd.h>
#include <typeinfo>
#include <algorithm>


long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void map_insertion(ft::map<int, char> &map)
{
	for (int i = 0; i < 100000; ++i)
		map.insert(ft::make_pair<int, char> (i, 'c'));
}

template<typename T>
void print_data(ft::vector<T> &vec, std::ofstream &outf)
{
	for (size_t i = 0; i < vec.size(); ++i)
		outf << i << ": " << vec.at(i) << std::endl;
}


template <typename Key, typename Value>
void print_map(ft::map<Key, Value> &map, std::ofstream &outf)
{
	typename ft::map<Key, Value>::iterator It = map.begin();
	typename ft::map<Key, Value>::iterator Ite = map.end();

	for ( ; It != Ite; ++It)
		outf << "Key: " << It->first << ' ' << "Value: " << It->second << std::endl;
}

int main(int argc, char **argv)
{
	(void)argc;
	std::cout << std::endl << std::endl;
	std::cout << "________________________" << TYPE << "__CONTAINERS________________________" << std::endl << std::endl;

/*__________________________________VECTOR__________________________________*/
	std::cout << "__________________________vector__________________________" << std::endl << std::endl;

	std::string file_name = argv[1];
	std::ofstream outf(file_name, std::ios::app | std::ios::ate);
	if (!outf)
	{
		std::cerr << "Cannot create file\n";
		return (1);
	}

/*__________________________________CONSTRUCTORS_&&_ASSIGNMENT__________________________________*/

	long	starttime = get_time();
	ft::vector<int> vec2;
	ft::vector<int> vec1(ft::vector<int> (1000000, 1000000));
	vec2 = vec1;
	ft::vector<int> vec(vec2.begin() + 900000, vec2.end());


	long	endtime =  get_time();
	std::cout << "CONSTRUCTORS_&&_ASSIGNMENT: "<< endtime - starttime << std::endl;
	print_data(vec, outf);

// /*__________________________________ITERATORS__________________________________*/

	starttime = get_time();
	ft::vector<int> vecForIter(10, 10);
	for (size_t i = 0; i < vecForIter.size(); ++i)
		vecForIter[i] = i;
	ft::vector<int>::iterator It = vecForIter.begin();
	ft::vector<int>::iterator Ite = vecForIter.end();
	outf << *It << std::endl;
	outf << *(It + 5) << std::endl;
	outf << It[5] << std::endl;
	++It;
	It++;
	outf << *It << std::endl;
	--Ite;
	Ite--;
	outf << *Ite << std::endl;
	
	ft::vector<int>::reverse_iterator rIt = vecForIter.rbegin();
	ft::vector<int>::reverse_iterator rIte = vecForIter.rend();

	--rIte;
	rIte--;
	++rIt;
	rIt++;
	outf << *rIt << std::endl;
	outf << *rIte << std::endl;
	outf << rIt[3] << std::endl;

	ft::vector<int>::iterator it = vec.begin();
	ft::vector<int>::const_iterator itc = vec.begin();
	ft::vector<int>::reverse_iterator rit = vec.rbegin();
	ft::vector<int>::const_reverse_iterator ritc = vec.rbegin();

	size_t for_errors = 0;
	if (it == itc)
		++for_errors;
	if (itc == it)
		++for_errors;
	if (rit == ritc)
		++for_errors;
	if (ritc == rit)
		++for_errors;
	ritc = rit;
	itc = it;

	/*Uncomment to see errors*/
	// it = itc;
	// rit = ritc;
	// it == rit;
	// rit == it;
	// ritc == itc;
	// ritc = itc;
	// it = ritc;

	endtime =  get_time();
	std::cout << "ITERATORS: " << endtime - starttime << std::endl;


/*__________________________________CAPACITY__________________________________*/

	starttime = get_time();

	outf << vec.size() << std::endl;
	outf << vec.max_size() << std::endl;
	outf << vec.capacity() << std::endl;

	vec.resize(120000, 228);
	vec1.resize(50000, 228);
	outf << vec.size() << std::endl;
	outf << vec1.size() << std::endl;
	outf << vec.capacity() << std::endl;
	outf << vec1.capacity() << std::endl;
	outf << vec.empty() << std::endl;
	ft::vector<int> empty_vector;
	outf << empty_vector.empty() << std::endl;
	empty_vector.reserve(13);
	outf << empty_vector.capacity() << std::endl;

	endtime =  get_time();
	std::cout << "CAPACITY: " << endtime - starttime << std::endl;

/*__________________________________ELEMENT_ACCESS__________________________________*/

	starttime = get_time();

	outf << vec[0] << std::endl;
	outf << vec[10] << std::endl;
	outf << vec[100] << std::endl;
	outf << vec[1000] << std::endl;
	outf << vec[10000] << std::endl;

	outf << vec.at(0) << std::endl;
	outf << vec.at(10) << std::endl;
	outf << vec.at(100) << std::endl;
	outf << vec.at(1000) << std::endl;
	outf << vec.at(10000) << std::endl;

	try { vec.at(5000000); }
	catch(std::out_of_range &ex) { outf << "Exception is caught" << std::endl; }
	outf << vec.front() << std::endl;
	outf << vec.back() << std::endl;
	outf << vec1.front() << std::endl;
	outf << vec1.back() << std::endl;

	endtime =  get_time();
	std::cout << "ELEMENT_ACCESS: " << endtime - starttime << std::endl;

/*__________________________________MODIFIERS__________________________________*/

	starttime = get_time();

	vec.assign(vec1.begin(), vec1.begin() + 100000);
	vec1.assign(200000, 777);
	print_data(vec, outf);
	print_data(vec1, outf);

	for (size_t i = 0; i < 1000; ++i)
		vec.push_back(vec1.size());
	for (size_t i = 0; i < 1000; ++i)
		vec1.push_back(vec.size());

	print_data(vec, outf);
	print_data(vec1, outf);
	for (size_t i = 0; i < 1000; ++i)
		vec.pop_back();
	for (size_t i = 0; i < 1000; ++i)
		vec1.pop_back();

	vec.insert(vec.begin(), 777777);
	vec.insert(vec.begin() + 10000, 10000, 777777);
	vec1.insert(vec1.begin() + 50000, vec.begin() + 10000, vec.begin() + 20000);

	vec.erase(vec.begin());
	vec.erase(vec.begin() + 5000, vec.begin() + 10000);

	print_data(vec, outf);
	print_data(vec1, outf);

	vec.swap(vec1);

	outf << vec.size() << std::endl;
	outf << vec1.size() << std::endl;
	outf << vec.capacity() << std::endl;
	outf << vec1.capacity() << std::endl;

	vec1.clear();
	vec.clear();
	outf << vec.size() << std::endl;
	outf << vec1.size() << std::endl;
	outf << vec.capacity() << std::endl;
	outf << vec1.capacity() << std::endl;
	endtime =  get_time();
	std::cout << "MODIFIERS: " << endtime - starttime << std::endl;

/*__________________________________RELATIONAL_OPERATORS_AND_ALLOCATOR__________________________________*/

	starttime = get_time();

	outf << typeid(vec.get_allocator()).name() << std::endl;

	outf << (vec1 == vec) << std::endl;
	outf << (vec == vec1) << std::endl;
	outf << (vec < vec1) << std::endl;
	outf << (vec > vec1) << std::endl;
	outf << (vec <= vec1) << std::endl;
	outf << (vec >= vec1) << std::endl;

	outf << vec1.capacity() << std::endl;
	endtime =  get_time();
	std::cout << "RELATIONAL_OPERATORS_AND_ALLOCATOR: " << endtime - starttime << std::endl;




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/*__________________________________CONSTRUCTORS_&&_ASSIGNMENT__________________________________*/

	std::cout << std::endl << std::endl;
	std::cout << "__________________________map__________________________" << std::endl << std::endl;

	starttime = get_time();
	ft::map<int, char> map2;
	ft::map<int, char> map1;
	map_insertion(map1);
	map2 = map1;
	ft::map<int, char> map(map2.begin(), map2.end());


	endtime =  get_time();
	std::cout << "CONSTRUCTORS_&&_ASSIGNMENT: "<< endtime - starttime << std::endl;
	print_map(map, outf);

/*__________________________________ITERATORS__________________________________*/

	starttime = get_time();

	ft::map<int, char> mapForIter;
	for (size_t i = 0; i < 100000; ++i)
		mapForIter[i] = 'c';
	ft::map<int, char>::iterator mIt = mapForIter.begin();
	ft::map<int, char>::iterator mIte = mapForIter.end();
	outf << mIt->first <<  " " << mIt->second << std::endl;
	++mIt;
	mIt++;
	outf << mIt->first <<  " " << mIt->second << std::endl;
	--mIte;
	mIte--;
	outf << mIte->first <<  " " << mIte->second << std::endl;
	
	ft::map<int, char>::reverse_iterator mrIt = mapForIter.rbegin();
	ft::map<int, char>::reverse_iterator mrIte = mapForIter.rend();

	--mrIte;
	mrIte--;
	++mrIt;
	mrIt++;
	outf << mrIt->first <<  " " << mrIt->second << std::endl;
	outf << mrIte->first <<  " " << mrIte->second << std::endl;

	ft::map<int, char>::iterator mit = map.begin();
	ft::map<int, char>::const_iterator mitc = map.begin();
	ft::map<int, char>::reverse_iterator mrit = map.rbegin();
	ft::map<int, char>::const_reverse_iterator mritc = map.rbegin();

	for_errors = 0;
	if (mit == mitc)
		++for_errors;
	if (mitc == mit)
		++for_errors;
	if (mit != mitc)
		++for_errors;
	if (mitc != mit)
		++for_errors;
	if (mrit == mritc)
		++for_errors;
	if (mritc == mrit)
		++for_errors;
	mritc = mrit;
	mitc = mit;

	endtime =  get_time();
	std::cout << "ITERATORS: " << endtime - starttime << std::endl;


// /*__________________________________CAPACITY__________________________________*/

	starttime = get_time();

	outf << map.size() << std::endl;
	outf << map.max_size() << std::endl;

	outf << map.size() << std::endl;
	outf << map1.size() << std::endl;
	outf << map.empty() << std::endl;
	ft::map<int, char> empty_map;
	outf << empty_map.empty() << std::endl;

	endtime =  get_time();
	std::cout << "CAPACITY: " << endtime - starttime << std::endl;

// /*__________________________________ELEMENT_ACCESS__________________________________*/

	starttime = get_time();

	outf << map[0] << std::endl;
	outf << map[10] << std::endl;
	outf << map[100] << std::endl;
	outf << map[1000] << std::endl;
	outf << map[10000] << std::endl;

	outf << map.at(0) << std::endl;
	outf << map.at(10) << std::endl;
	outf << map.at(100) << std::endl;
	outf << map.at(1000) << std::endl;
	outf << map.at(10000) << std::endl;

	try { map.at(500000000); }
	catch(std::out_of_range &ex) { outf << "Exception is caught" << std::endl; }

	endtime =  get_time();
	std::cout << "ELEMENT_ACCESS: " << endtime - starttime << std::endl;

// /*__________________________________MODIFIERS__________________________________*/

	starttime = get_time();

	map.insert(ft::pair<int, char> (777777, 'G'));
	map.insert(ft::pair<int, char> (777777, 'G'));
	map.insert(ft::pair<int, char> (777777, 'G'));
	map.insert(ft::pair<int, char> (777777, 'G'));
	map.insert(ft::pair<int, char> (777777, 'G'));
	map.insert(map.begin(), ft::pair<int, char> (888888, 'G'));
	map1.insert(map.begin(), map.end());

	map.erase(map.begin());
	map.erase(777777);
	map.erase(777777);
	map.erase(777777);
	map.erase(777777);
	map.erase(777777);
	ft::map<int, char>::iterator ItForErase = map.begin();
	for (size_t i = 0; i < 1000; ++i)
		++ItForErase;
	map.erase(map.begin(), ItForErase);

	print_map(map, outf);
	print_map(map1, outf);

	map.swap(map1);

	outf << map.size() << std::endl;
	outf << map1.size() << std::endl;

	map1.clear();
	map.clear();
	outf << map.size() << std::endl;
	outf << map1.size() << std::endl;
	endtime =  get_time();
	std::cout << "MODIFIERS: " << endtime - starttime << std::endl;

/*__________________________________OBSERVERS_&&_ALLOCATOR__________________________________*/

	starttime = get_time();

	map.get_allocator();
	map.key_comp();
	map.value_comp();

	endtime =  get_time();
	std::cout << "OBSERVERS AND ALLOCATOR: " << endtime - starttime << std::endl;

/*__________________________________OPERATIONS__________________________________*/

	starttime = get_time();

	outf << map2.find(1000)->first << map2.find(1000)->first << std::endl;
	outf << map2.find(0)->first << map2.find(0)->first << std::endl;
	outf << map2.find(777)->first << map2.find(777)->first << std::endl;
	map2.find(-1414);
	map2.find(-5000000);
	outf << map2.count(1000)  << std::endl;
	outf << map2.count(0) <<  std::endl;
	outf << map2.count(777) << std::endl;

	map.insert(ft::pair<int, char> (5, 'c'));
	map.insert(ft::pair<int, char> (10, 'c'));

	for (size_t i = 0; i < 9; ++i)
	{
		outf << map.lower_bound(i)->first << map.lower_bound(i)->second << std::endl;
		outf << map.upper_bound(i)->first << map.upper_bound(i)->second << std::endl;
	}
	outf << map.equal_range(5).first->first << map.equal_range(5).second->second << std::endl;

	endtime =  get_time();
	std::cout << "OPERATIONS: " << endtime - starttime << std::endl;

/*__________________________________RELATIONAL_OPERATORS_AND_ALLOCATOR__________________________________*/

	starttime = get_time();

	outf << (map == map1) << std::endl;
	outf << (map1 == map) << std::endl;
	outf << (map < map1) << std::endl;
	outf << (map > map1) << std::endl;
	outf << (map <= map1) << std::endl;
	outf << (map >= map1) << std::endl;
	// std::cout << map.size( ) << std::endl;
	// std::cout << map1.size( ) << std::endl;

	endtime =  get_time();
	std::cout << "RELATIONAL_OPERATORS_AND_ALLOCATOR: " << endtime - starttime << std::endl;







/*__________________________________STACK__________________________________*/


	ft::stack<int> stack;
	outf << stack.empty();
	for (int i = 0; i < 100000; ++i)
		stack.push(i);
	for (int i = 0; i < 50000; ++i)
		stack.pop();
	outf << stack.size();
	outf << stack.top();
	outf << stack.empty();
	ft::stack<int> stack1(stack);
	ft::stack<int> stack2 = stack1;
	outf << stack2.size();
	outf << stack2.top();
	outf << stack2.empty();

	stack1.pop();

	outf << (stack == stack2) << std::endl;
	outf << (stack2 == stack) << std::endl;
	outf << (stack <= stack2) << std::endl;
	outf << (stack <= stack1) << std::endl;
	outf << (stack >= stack2) << std::endl;
	outf << (stack >= stack1) << std::endl;
	outf << (stack2 > stack1) << std::endl;
	outf << (stack2 < stack1) << std::endl;


/*__________________________________SET__________________________________*/
	{
		ft::set<int> mp;
		ft::set<int> mpp;
		for (int i = 0; i < 15; ++i)
			mp.insert(i + 37);
		for (ft::set<int>::iterator sit = mpp.begin(); sit != mpp.end(); sit++) { outf << "set : " << *sit << std::endl; }
		ft::set<int> mp0;
		ft::set<int>::iterator ii = mp0.insert(3).first;
		ii++;
		outf <<"ii " <<* (--ii) << std::endl;
		for (int i = 0; i < 5; ++i)
			mp.insert(i + 10);
		ft::set<int>::reverse_iterator sit = mp.rbegin();
		ft::set<int>::reverse_iterator sit2 = --mp.rend();
		outf <<"it " << *sit << std::endl;
		it++;
		outf <<"it " << *sit2 << std::endl;
		it++;
		it--;
		outf <<"it " << *sit << std::endl;
		for (int i = -500, j = 0; i < 500; ++i, ++j) { mp.insert(i); }
	    ft::set<int, int>::iterator it_f = mp.find(+300);
		outf <<"it " << *it_f << std::endl;
		outf << "number of erase " << mp.erase(-5) << ", current size:" << mp.size() << std::endl;
		outf << "number of erase " << mp.erase(-555) << ", current size:" << mp.size() << std::endl;
	}


	return (0);
}