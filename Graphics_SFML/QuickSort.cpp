#include "QuickSort.hpp"

QuickSort::QuickSort(const unsigned sleepTime)
{
	m_sleepTime = sleepTime;
	m_name = "Quick sort";
}

void QuickSort::sort(std::vector<Sortable>& array) {
	quickSort(array, 0, array.size() - 1);
}

void QuickSort::quickSort(std::vector<Sortable>& array, int p, int q) {
	int r;
	if (p < q) {
		r = partition(array, p, q);
		quickSort(array, p, r);
		quickSort(array, r+1, q);
	}
}

int QuickSort::partition(std::vector<Sortable>& array, int p, int q) {
	
	int i = p;
	int j;

	for (j = p + 1; j < q; j++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(m_sleepTime));
		// original if : array[j]<=x
		if (compare(array[j], array[p]) < 0) {
			i = i + 1;
			swap(array[i], array[j]);
		}
	}

	swap(array[i], array[p]);
	return i;

}