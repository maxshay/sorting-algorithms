#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include "../../Sort.hpp"

/**
* Selection sort implementation
*/
class QuickSort : public Sort
{
public:
	/**
	* Constructor, sets waiting time between algorithm steps
	*
	* @param sleepTime Time between each algorithm step in milliseconds
	*/
	QuickSort(const unsigned sleepTime);

	/**
	* Overrides the Sort::sort() method
	*/
	void sort(std::vector<Sortable>& array) override;

private: 
	void quickSort(std::vector<Sortable>& array, int p, int q);
	int partition(std::vector<Sortable>& array, int p, int q);
};

#endif // QUICKSORT_HPP