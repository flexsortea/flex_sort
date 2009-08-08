
#include <iostream>
#include <vector>

#include <boost/timer.hpp>

#include <boost/random.hpp>

#include <boost/algorithm/sorting/utils.hpp>
#include <boost/algorithm/sorting/flex_sort.hpp>



using namespace std;
using namespace boost;

template <typename SortFunctor>
void benchmark(SortFunctor f)
{

	vector<unsigned long> v(10000000);
	
	mt19937 rng;
	uniform_int<> everything(0, numeric_limits<long>::max());      
	variate_generator<mt19937&,uniform_int<> > gen(rng, everything);  

	generate(v.begin(), v.end(), gen);

	timer t;

	f(v.begin(), v.end());

	cout << " elapsed : " << t.elapsed() << endl;
	cout << " sorted : " << is_ordered(v.begin(), v.end()) << endl;
	

}

struct std_sort
{
	template <typename Iterator>
	void operator()(Iterator first, Iterator last)
	{
		std::sort(first, last);
	}
};

int main(int, char **, char *)
{

	benchmark(std_sort());
	benchmark(flex_sort());

	return 0;
}