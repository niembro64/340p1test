#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;



const int SIZES[] = { 30, 60, 90, 120, 150 };
const int NUM_SIZES = sizeof(SIZES) / sizeof(int);

void insertionSort(string arr[], int n)
{
	string temp;
	int i, j;

	for (i = 1; i < n; ++i) {
		j = i;

		while (j > 0 && arr[j] < arr[j - 1]) {
			temp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = temp;
			j--;
		}
	}
}

void merge(string arr[], int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	string *L = new string[n1], *R = new string[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];

	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}


	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}

	delete[] L;
	delete[] R;
}

void mergeSort(string arr[], int l, int r)
{
	if (l < r)
	{

		int m = l + (r - l) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

void MaxHeapify(string a[], int i, int n)
{
	int j;
	string temp;
	temp = a[i];
	j = 2 * i;

	while (j <= n)
	{
		if (j < n && a[j + 1] > a[j])
			j = j + 1;

		if (temp > a[j])
			break;

		else if (temp <= a[j])
		{
			a[j / 2] = a[j];
			j = 2 * j;
		}
	}
	a[j / 2] = temp;
	return;
}

void HeapSort(string a[], int n)
{
	int i;
	string temp;

	for (i = n; i >= 2; i--)
	{

		temp = a[i];
		a[i] = a[1];
		a[1] = temp;

		MaxHeapify(a, 1, i - 1);
	}
}

void Build_MaxHeap(string  a[], int n)
{
	int i;
	for (i = n / 2; i >= 1; i--)
		MaxHeapify(a, i, n);
}

void test(bool sorted, ofstream& fout)
{
	cout << (sorted ? "SORTED" : "PERMUTED") << " runtime plot" << endl;
	cout << setw(10) << "Size" << setw(15) << "Insertion sort"
		<< setw(15) << "Merge sort" << setw(15) << "Build heap"
		<< setw(15) << "Heap sort" << endl;
	cout << fixed << showpoint << setprecision(3);


	fout << (sorted ? "SORTED" : "PERMUTED") << " runtime plot" << endl;
	fout << setw(10) << "Size" << setw(15) << "Insertion sort"
		<< setw(15) << "Merge sort" << setw(15) << "Build heap"
		<< setw(15) << "Heap sort" << endl;
	fout << fixed << showpoint << setprecision(3);

	for (int i = 0; i < NUM_SIZES; i++)
	{
		int n = SIZES[i] * 1000;
		string *arr = NULL;
		string *cpy = NULL;
		string file = (sorted ? "sorted" : "perm") + to_string(SIZES[i]) + "K.txt";
		ifstream inputfile;
		int counter = 0;
		clock_t begin, end;
		double runtime;
		string line;

		inputfile.open(file.c_str());

		if (!inputfile)
		{
			cout << "Error: could not open file '" << file << "'" << endl;
			exit(1);
		}

		arr = new string[n];

		if (arr == NULL)
		{
			cout << "Error: memory allocation failed" << endl;
			exit(1);
		}

		cpy = new string[n];

		if (cpy == NULL)
		{
			cout << "Error: memory allocation failed" << endl;
			exit(1);
		}

		while (getline(inputfile, line))
		{
			arr[counter] = line;
			counter++;
		}

		inputfile.close();

		if (counter != n)
		{
			cout << "Error: size did not match" << endl;
			exit(1);
		}

		cout << setw(9) << SIZES[i] << "K";
		fout << setw(9) << SIZES[i] << "K";

		std::copy(arr, arr + n, cpy);
		begin = clock();
		insertionSort(cpy, n);
		end = clock();
		runtime = double(end - begin) / CLOCKS_PER_SEC;
		cout << setw(15) << runtime;
		fout << setw(15) << runtime;

		std::copy(arr, arr + n, cpy);
		begin = clock();
		mergeSort(arr, 0, n - 1);
		end = clock();
		runtime = double(end - begin) / CLOCKS_PER_SEC;
		cout << setw(15) << runtime;
		fout << setw(15) << runtime;

		std::copy(arr, arr + n, cpy);
		begin = clock();
		Build_MaxHeap(arr, n - 1);
		end = clock();
		runtime = double(end - begin) / CLOCKS_PER_SEC;
		cout << setw(15) << runtime;
		fout << setw(15) << runtime;

		HeapSort(arr, n - 1);
		end = clock();
		runtime = double(end - begin) / CLOCKS_PER_SEC;
		cout << setw(15) << runtime << endl;
		fout << setw(15) << runtime << endl;

		delete[] arr;
		delete[] cpy;
	}

	cout << endl;
	fout << endl;
}





int main()
{
	

	char algorithm;
	int size, yes;
	bool sorted;
	string s;
	string line;
	ofstream fout;

	fout.open("plot.txt");

	if (!fout)
	{
		cout << "Error: could not open file 'plot.txt'" << endl;
		return 1;
	}

	test(true, fout);
	test(false, fout);

	fout.close();

	cout << "Select sorting algorithm\na) InsertionSort\nb) MergeSort\nc) HeapSort\n" << endl;
	cin >> algorithm;
	cout << "Enter file size(30/60/90/120/150): " << endl;
	cin >> size;
	cout << "Sorted? 1. Yes, 2. No\n";
	cin >> yes;
	if (yes == 1) {
		sorted = true;
		s = "sorted";
	}
	else if (yes == 2) {
		sorted = false;
		s = "perm";
	}
	string *array = new string[size * 1000];
	string *copy = new string[size * 1000];

	int c = 0;
	string filename = s + to_string(size) + "K.txt";
	ifstream input(filename);
	while (getline(input, line)) {
		array[c] = line;
		c++;
	}
	std::copy(array, array + (size * 1000), copy);
	clock_t b, e;
	if (algorithm == 'a') {
		b = clock();
		insertionSort(copy, size * 1000);
		e = clock();
	}
	else if (algorithm == 'b') {
		b = clock();
		mergeSort(copy, 0, (size * 1000) - 1);
		e = clock();
	}
	else if (algorithm == 'c') {
		b = clock();
		Build_MaxHeap(copy, (size * 1000) - 1);
		HeapSort(copy, (size * 1000) - 1);
		e = clock();
	}
	time_t t = clock();
	string output = "output" + to_string(t) + ".txt";
	ofstream outputstream(output);
	for (int i = 0; i<size * 1000; i++) {
		outputstream << copy[i] << endl;
	}
	outputstream.close();
	delete[] array;
	delete[] copy;
	cout << "Run time: " << double(e - b) / CLOCKS_PER_SEC << endl;
	cout << "File name: " << output << endl;

	cout << "hello" << endl << endl;
	
	system("pause");

	return 0;
}