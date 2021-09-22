# Concepts

* Internal Sorting: all the data can be loaded into the memory of a computer
* External Sorting: data is too huge to be loaded into the memory of a computer and is usually dealt with on the hard disks.
* Stable Sorting: if the values of the two elements are the same, their orders won't be changed..
* Unstable Sorting: if the values of the two elements are the same, it is not guaranteed that their orders won't be changed.

Notes: the implementation of the algorithms here assume that the user would pass on the "end" of an array, which means the rightmost-index + 1.



# Comparison

## Stable Sorting Algorithms

| Stable Sorting Algorithms | Time Complexity | Space Complexity |
| ------------------------- | --------------- | ---------------- |
| Insertion Sorting         | O(n^2)          | O(1)             |
| Bubble Sorting            | O(n^2)          | O(1)             |
| Merge Sorting             | O(n*logn)       | O(n)             |

### Insertion Sorting

Just imagine that somebody wants to jump into the line and does not want to provoke those who are stronger than him. He started from the end of the queue, and compares himself with the victim standing in front of him, if the victim is weaker, he is going to make that victim back. Then we can get this bastard's index of the final place: after a stronger person, but there is still a problem: we do not know whether the person standing in front of him now is the strongest person.



Therefore, we can imagine that we can start from the beginning of the line, and consider the first person is "sorted", and each time we move backward to get a new person and compare their strength.



Time Complexity: for the first move of comparisons, it at most compares once, for the second move of comparisons, it at most compares twice, ... Therefore, it compares 1+2+3+4..+N-1 = N*(N-1)/2 times. Therefore, the time complexity is 
$$
O(n^2)
$$
However, it is the fastest sorting algorithm compared with other sorting algorithms under O(n^2) time complexity introduced here, and it is rather efficient under a nearly sorted array, because it is more "comparing" rather than "swapping" compared to other algorithms.



Insertion Sorting obviously doesn't use extra spaces but only some variables spaces, the space complexity is O(1).



### Bubble Sorting

You can imagine that a bubble from the bottom of the lake is floating upward: the biggest bubble will finally get to the water surface.



Idea: each time compares the nearby elements and if it is satisfying the situation, swap them.



Time Complexity: each time, there will be a smallest/largest element to be put to the end of the array, therefore, for the first time, there will be n-1 times of comparisons, for the second move there will be n-2 times of comparisons, the total comparisons sum up to N*(N-1)/2, and the time complexity is
$$
O(n^2)
$$
However, because it is usually swapping, the actual efficiency is considered the lowest among the three O(n^2) algorithms introduced here.



The space complexity is O(1).



### Merge Sort

Each time we are going to separate the array into two parts and once we get the bottom (two elements), we compare them and put them into the correct orders, then we compare the two-element array with another array within two elements. 



Some intuitive graphs and procedures can be found [here](https://www.geeksforgeeks.org/merge-sort/).



Merge Sort is rather rapid and can be used for external sorting within I/O operations for the files. We usually consider "merge sort" as "two-way merge", and this "divide and conquer" idea can be used on "k-way merge" as well.



Time Complexity: 
$$
O(nlogn) (best/worst/average)
$$
Space Complexity:
$$
O(n)
$$
More analysis can be seen  [here](https://stackoverflow.com/questions/10342890/merge-sort-time-and-space-complexity)



## Unstable Sorting Algorithms

| Unstable Sorting Algorithms | Time Complexity | Space Complexity |
| --------------------------- | --------------- | ---------------- |
| Selection Sorting           | O(n^2)          | O(1)             |
| Quick Sort                  | O(nlogn)-O(n^2) | O(logn)-O(n)     |

### Selection Sorting

The idea is simple: every time we throw a smallest/largest element to the end of the array.

Time Complexity:
$$
O(n^2)
$$
Space Complexity
$$
O(1)
$$


It has slightly less efficiency than insertion sort.



### Quick Sort

Every time we are going to choose a pivot value (usually it is the leftmost-indexed or rightmost-indexed value). Then we are going to maintain two pointers. When we find a value smaller/larger than the pivot value from the two pointers, we swap the value.



Notes:

* pivot value can be randomly chosen to prevent it from descending to O(n^2), some good ways including using rand() function, or using median of the first, last, and mid-indexed value in the array.
* a trick can be used for reducing the resources used for function callings.
* we can give up checking the boarder and make it less comparisons.

More intuitive explanations can be found [here](https://www.geeksforgeeks.org/quick-sort/).



Time Complexity:
$$
O(nlogn)-O(n^2)
$$
Space Complexity:
$$
O(logn)-O(n)
$$
