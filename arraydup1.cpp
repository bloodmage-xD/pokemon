// this program deletes all duplicates found in an array by shifting. 
// it does this by performing a merge sort the swaping the duplicates and shifting it in the array to the end
// time - N log N 
// space - N 
#include <iostream>

template<typename T>
void merge(T array[],T size, T low, T middle, T  high){   // takes turns swapping elements from partitions into new array
    T temp[size];
    for (std::size_t i = low; i <= high; i++)
        temp[i] = array[i];
    T i = low;
    T j = middle + 1;
    T k = low;
	while (i <= middle && j <= high){
	if (temp[i] <= temp[j]){
            array[k] = temp[i];
            ++i;   
        }
        else{
            array[k] = temp[j];
            j++;
        }
	k++;
	}
        while (i <= middle){
            array[k] = temp[i];
            k++; i++;
            
        }
        
}
template<typename T>
void mergesort(T array[],T size, T  low , T high){
    if (high > low){                   // does most of the recursive calls
        int middle = (low + high) / 2;    
        mergesort( array, size, low, middle);
        mergesort( array, size , middle+1, high);
        merge(array, size, low, middle, high);
    }
    
}


int main()
{
  //int array[10] = {0,2,3,4,5,3,2,3,4,5};
  int array[10];
  std::cout << "enter 10 elements into array" << std::endl;
  for (int i = 0; i < 9; i++)
  	std::cin >> array[i];
 

  int size = 10;
  int count = 9;
  mergesort(array, size, 0, 9); 
   for (int i = 0; i<size-2; i++){
	if (array[i] == array[i+1]){        // performs a swap if there is a duplicates so all the duplicates will be at the end of the array
		std::swap(array[i+1], array[size-count]);
		
		//array[i+1] = 0;
	}
  	else{
		count--;
	}
}
 std::cout << std::endl;
	


  for (int i = 0; i < size - count; i++)
	std::cout << array[i] << std::endl;

//  for (int i = 0; i < size; i++){
//    if (array[i] ^ 0 != 0)
//	std::cout << array[i];
//	}
}

