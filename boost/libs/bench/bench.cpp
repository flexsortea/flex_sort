
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <sstream>

#include <boost/timer.hpp>

#include <boost/random.hpp>

#include <boost/algorithm/sorting/utils.hpp>
#include <boost/algorithm/sorting/flex_sort.hpp>

using namespace std;
using namespace boost;

struct result
{
	double _value;
	bool _check;
	string _comment;
};

result make_result(double v, bool c, const string & comment)
{
	result r;
	r._value = v;
	r._check = c;
	r._comment = comment;
	return r;
}

typedef list<result> results_type;

template <typename SortFunctor>
void benchmark(SortFunctor f, results_type & results)
{

	results.clear();

	vector<size_t> sizes_to_use;

	sizes_to_use.push_back(0);
	sizes_to_use.push_back(1);
	sizes_to_use.push_back(10);
	sizes_to_use.push_back(100);
	sizes_to_use.push_back(10000);
//	sizes_to_use.push_back(1000000);
//	sizes_to_use.push_back(10000000);

	for(vector<size_t>::const_iterator it = sizes_to_use.begin();
		it != sizes_to_use.end();
		++it)
	{
		vector<unsigned long> v(*it);

		mt19937 rng;
		uniform_int<> everything(0, numeric_limits<long>::max());      
		variate_generator<mt19937&,uniform_int<> > gen(rng, everything);  

		generate(v.begin(), v.end(), gen);

		double elapsed = 0.0;

		timer t;

		for(int i = 0; i < 10000; ++i)
		{
			vector<unsigned long> copy(v.begin(), v.end());
			t.restart();
			f(copy.begin(), copy.end());
			elapsed += t.elapsed();
		}
		

		std::stringstream ss1;
		ss1 << "random vector : " << v.size();

		results.push_back(make_result(elapsed, is_ordered(v.begin(), v.end()), ss1.str()));

		f(v.begin(), v.end());

		for(int i = 0; i < 10000; ++i)
		{
			f(v.begin(), v.end());
		}

		elapsed = t.elapsed();

		std::stringstream ss2;
		ss2 << "ordered vector : " << v.size();

		results.push_back(make_result(elapsed, is_ordered(v.begin(), v.end()), ss2.str()));


	}

	BOOST_ASSERT(!results.empty());
	

}

struct std_sort
{
	template <typename Iterator>
	void operator()(Iterator first, Iterator last)
	{
		::std::sort(first, last);
	}
};

int main(int, char **, char *)
{

	results_type flex_results;	
	benchmark(flex_sort(), flex_results);

	results_type std_results;
	benchmark(std_sort(), std_results);

	BOOST_ASSERT(flex_results.size() == std_results.size());

	for(results_type::const_iterator it_flex = flex_results.begin(), it_std = std_results.begin();
		it_flex != flex_results.end();
		++it_flex, ++it_std)
	{
		cout << "---" << endl;
		cout << "flex : " << it_flex->_value << " ok : " << it_flex->_check << " " << it_flex->_comment.c_str() << endl;
		cout << "std : " << it_std->_value << " ok : " << it_std->_check << " " << it_std->_comment.c_str() << endl;

		cout << endl;
		cout << "gain : " << 100.0 - it_flex->_value / it_std->_value * 100.0 << " %" << endl << endl;
	}


	return 0;
}