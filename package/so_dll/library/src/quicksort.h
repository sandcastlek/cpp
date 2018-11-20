
template<typename T>
void swap(T* arr, const size_t first, const size_t second)
{
	T tmp = arr[first];
	arr[first] = arr[second];
	arr[second] =  tmp;
}

template<typename T>
size_t partition(T* arr, const int start_idx, const int end_idx)
{
	T* pivot_val = arr + end_idx;
	size_t lower_max_idx = start_idx -1;
	for(size_t current_idx=start_idx; current_idx < end_idx; current_idx++) {
		if( arr[current_idx] >= *pivot_val)
			continue;
		lower_max_idx++;
		swap(arr,lower_max_idx,current_idx);
	}
	lower_max_idx++;
	swap(arr,lower_max_idx,end_idx);
	return lower_max_idx;
}

template<typename T>
void quicksort_impl(T* arr, const int start_idx, const int end_idx)
{
	if( (end_idx > start_idx) && (end_idx > 0) && (start_idx > 0) )
	{
		int pivot_idx = partition(arr, start_idx, end_idx);
		quicksort_impl(arr, 0, pivot_idx - 1);
		quicksort_impl(arr, pivot_idx + 1, end_idx);
	}
}

template<typename T>
void quicksort(T* arr, const size_t len)
{
	quicksort_impl(arr, 0, len-1);
}

