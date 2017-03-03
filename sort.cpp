#include <cmath>
#include <cstdio>
#include <iostream>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ostream>
#include <map>
#include "ArgumentManager.h"

using namespace std;

struct Node
{
    long long num = 0;
    string str;
    Node* prev = 0;
    Node* next = 0;
};

class DoubleLinkedList
{
public:
    DoubleLinkedList() {}
    // Destructor
    ~DoubleLinkedList()
    {
        clear();
    }

    void clear()
    {
        while (head != nullptr)
        {
            Node* deleteme = head;
            head = head->next;
            delete deleteme;
        }
    }

    // Copy constructor
    DoubleLinkedList(DoubleLinkedList const & list)
    {
        // cout << "copy" << endl;
    }
    // Build a Double Linked List
    DoubleLinkedList(const std::string& num, int digitsPerNode);

    DoubleLinkedList & operator=(DoubleLinkedList const & other)
    {
        clear();

        // cout << "equal" << endl;
        Node* temp = other.head;
        while (temp != nullptr)
        {
            push_back(temp->str);
            temp = temp->next;
        }
        return *this;
    }

    void push_front(string parted)
    {
        Node*temp = new Node();
        temp->str = parted;
        stringstream ss(parted);
        ss >> temp->num;
        if (head == 0)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            head->prev = temp;
            temp->next = head;
            head = temp;
        }
    }

    void push_back(string parted)
    {
        Node* temp = new Node();
        temp->str = parted;
        stringstream ss(parted);
        ss >> temp->num;
        if (head == 0)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }

    void print() const
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            cout << temp->str;
            temp = temp->next;
        }
    }

    Node at(int index) const
    {
        int i = 0;
        Node* temp = head;
        while (i != index)
        {
            temp = temp->next;
            i++;
        }
        return *temp;
    }

    int size() const
    {
        int count = 0;
        Node* temp = head;
        while (temp != 0)
        {
            temp = temp->next;
            count++;
        }
        return count;
    }

    void swap(DoubleLinkedList & other)
    {
        Node* temp = head;
        head = other.head;
        other.head = temp;
    }

private:
    Node* head = 0;
    Node* tail = 0;
};

class BigNumber
{
public:
    BigNumber() {}
    BigNumber(string num, int digitsPerNode)
    {
        // cout << num << endl;
        if (num[0] == '-')
        {
            isNegative = true;
            num.erase(num.begin());
        }
        int startIndex = num.length() - digitsPerNode;
        while (startIndex >= 0)
        {
            data.push_front(num.substr(startIndex, digitsPerNode));
            startIndex -= digitsPerNode;
        }
        if (startIndex < 0)
        {
            data.push_front(num.substr(0, startIndex + digitsPerNode));
        }
    }
    BigNumber(BigNumber const & other)
    {
        // cout << "big copy" << endl;
    }
    BigNumber & operator= (BigNumber const & other)
    {
        // cout << "operator=" << endl;
        isNegative = other.isNegative;
        data = other.data;
        return *this;
    }
    bool operator< (BigNumber const & other) const
    {
        BigNumber const & a = *this;
        BigNumber const & b = other;

        if (a.isNegative && !b.isNegative)
        {
            return true;
        }
        if (!a.isNegative && b.isNegative)
        {
            return false;
        }

        bool result = false;
        if (a.data.size() < b.data.size())
        {
            //return true;
            result = true;
        }
        else
            if (a.data.size() > b.data.size())
            {
                //return false;
                result = false;
            }
            else
                if (a.data.size() == b.data.size())
                {
                    int index = 0;
                    while (index < a.data.size())
                    {
                        if (a.data.at(index).num < b.data.at(index).num)
                        {
                            //return true;
                            result = true;
                            break;
                        }
                        if (a.data.at(index).num > b.data.at(index).num)
                        {
                            //return false;
                            result = false;
                            break;
                        }
                        if (a.data.at(index).num == b.data.at(index).num)
                        {
                            //Go to the next node
                        }
                        index++;
                    }
                }
        if (isNegative)
        {
            result = !result;
        }
        return result;
    }

    void print() const
    {
        if (isNegative)
        {
            cout << "-";
        }
        data.print();
    }

    void swap(BigNumber & other)
    {
        std::swap(isNegative, other.isNegative);
        data.swap(other.data);
    }
    // bool operator>= (BigNumber const & other) const
    // {
    //     return !operator< (other);
    // }

private:
    bool isNegative = false;
    DoubleLinkedList data;
};


      void print(BigNumber *a, int size)
      {
          for (int i = 0; i < size; i++)
          {
              a[i].print();
          }
          cout << endl;
      }


class Sort
{
public:
    Sort(){}
    ~Sort(){}
    void selectionSort(BigNumber *a,int size)
    {
      //cout << "Entering Selection Sort" << endl;
      int comparisons = 0;
      int countSwap = 0;
      int iSmallest;
      for (int  i = 0; i < size-1; i++)
      {
          iSmallest = i;
          for (int j = i + 1; j < size; j++)
          {
              if (a[j] < a[iSmallest])
              {
                  iSmallest = j;
              }

          }
          if (iSmallest!=i) {
            countSwap++;
            a[iSmallest].swap(a[i]);
          }
          comparisons++;
      }
      countSwap=countSwap-1;

      //print(a, size);
      bigO<< "select" <<"         "<< size<< "             "<<comparisons<<"            "<< countSwap<<endl;
    }
    void quickSort(BigNumber *a,int left, int right)
    {
      //cout<<"In quickSort"<<endl;
          int i = left;
          int j = right;
          int g=right-1;
          int countSwap=0;
          int pivot =(right+g) / 2; //pivot is in the middle
          /* partition */
          while(left<j || i<right)
    {
        while(a[i]<a[pivot])
        i++;
        while(a[pivot]<a[j])
        j--;

        if(i<= j){
            a[j].swap(a[i]);
            countSwap++;
            i++;
            j--;
        }
        else{
            if(left<j)
                quickSort(a, left, j);
            if(i<right)
                quickSort(a,i,right);
            return;
        }
    }
        }
    void heapify(BigNumber *a, int size, int i, int comparisons, int countSwap)
    {
        int largest = i;  // Initialize largest as root
        int left = 2*i + 1;  // left = 2*i + 1
        int right = 2*i + 2;  // right = 2*i + 2

        // If left child is larger than root
        if (size > left) {
            if(a[largest] < a[left]) {
              largest = left;
              comparisons++;
            }
          }

        // If right child is larger than largest so far
        if (size > right) {
            if(a[largest] < a[right]) {
              largest = right;
              comparisons++;
            }
          }
        // If largest is not root
        if (largest != i)
        {
            comparisons++;
            a[i].swap(a[largest]);
            // Recursively heapify the affected sub-tree
            heapify(a, size, largest, comparisons, countSwap);
        }
    }

    void heapSort(BigNumber *a, int size)
    {
      int countSwap = 0;
      int comparisons = 0;
        // Build heap (rearrange array)
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(a, size, i, comparisons, countSwap);
    }
        // One by one extract an element from heap
        for (int i=size-1; i>=0; i--)
        {
            // Move current root to end
            a[0].swap(a[i]);
            comparisons++;
            // call max heapify on the reduced heap
            heapify(a, i, 0, comparisons, countSwap);
            countSwap++;
        }
        bigO<<"heap" <<"        "<< size-1 <<"                 "<< comparisons-1<< "            "<< countSwap-2 <<endl;
    }

    void primer_insertion(BigNumber *a, int size)
        {
            int i = 0;
            int j = 0;
            int countSize = 0; //Number of integers sorted
            int countComparisons = 0; //Number of comparisons to complete the sort
            int countSwaps = 0; //Number of swaps to complete the sort
            int bigOComparisons = 0; //Number of comparisons needed in the worst case
            int bigOSwaps = 0; //Number of swaps needed in the worst case
            insertion_sort(a, size, i, j, countSize, countComparisons, countSwaps, bigOComparisons, bigOSwaps);
        }

    void insertion_sort(BigNumber *a, int size, int i, int j, int countSize, int countComparisons, int countSwaps, int bigOComparisons, int bigOSwaps)
    {
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = i; j < size; j++)
            {
                countComparisons++;
                if (a[j] < a[i])
                {
                    a[i].swap(a[j]);
                    countSwaps++;
                }
            }
        }
      bigO<< "insert" <<"        "<< size-1 <<"               "<< countComparisons<< "            "<< countSwaps <<endl;
    }

    
BigNumber* merge(BigNumber *a, int size, int counter)
{
    //Base case
    if (size == 1) 
    {
        return a;
    }

    //Divide
    int i, j, k;
    int n1 = floor(size / 2);
    int n2 = ceil(size / 2) + size % 2;
    //Create temp arrays
    BigNumber *L = new BigNumber[n1];
    BigNumber *R = new BigNumber[n2];
    //Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
    {
        L[i] = a[i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = a[j + n1];
    }

    //Recursion
    L = merge(L, n1, counter); //Putting in an unsorted L[] and returning a sorted L[]
    R = merge(R, n2, counter); //Putting in an unsorted R[] and returning a sorted R[]

    //Conquer
    //Merge the temp arrays back into arr[l...r]
    i = 0; //Initial index of first subarray
    j = 0; //Initial index of second subarray
    k = 0; //Initial index of merged subarray

    while (i < n1 && j < n2)
    {
        if (L[i] < R[j])
        {
            a[k] = L[i];
            i++;       
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }
    //Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }
    //Copy the remaining elents of R[], if there are any
    while (j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }

    //Merge L[] and R[]
    delete[] L; //Always delete a dynamically allocated array
    delete[] R;
    return a;
}

//l is for left index and r is right index of the sub-array of arr to be sorted
void mergeSort(BigNumber *a, int size)
{
    if (size > 1)
    {
        int counter = 0;
        cout << "start merge" << endl;
        merge(a, size, counter);
    }
}



    bool open_the_bigO()
      {

          fstream testbigo("bigO.txt");
          if(!testbigo) {

            bigO.open("bigO.txt",ios::app);
            bigO << "algorithm   #numbers(n)  #Comparisons   #Swaps"<<endl;

          }
          else {
            testbigo.close();
            bigO.open("bigO.txt",ios::app);
          }

          return true;

      }

    void close_the_file()
    {
        // bigO.close;
    }
    // void primer_selection()
    // {
    //     int i - 0;
    //     int iSmallest = 0;
    //     j = 0;
    //     selectionSort(i, iSmallest, j);
    // }

    // Sort & operator= (Sort & other)
    // {
    //     // cout << "operator=" << endl;
    //     a = other.a;
    //     //data = other.data;
    //     return *this;
    // }

  private:
      fstream bigO;
      BigNumber *a;

  };

      int count_lines(string & filename, int digitsPerNode)
      {
          std::ifstream ifs(filename.c_str());

          int counter = 0;
          while (!ifs.eof())
          {
              string line;
              ifs >> line;
              counter++;
          }

          return counter;
      }
      void input(BigNumber *a, string & filename, int digitsPerNode)
      {
          std::ifstream ifs(filename.c_str());

          int counter = 0;
          while (!ifs.eof())
          {
              string line;
              ifs >> line;
              if(line.size()!=0){
              a[counter] = BigNumber(line, digitsPerNode);
              counter++;
          }
        }
      }

int main(int argc, char* argv[])
{

    if (argc < 2)
    {
        //std::cerr("Usage: infinitearithmetic \"input=xyz.txt;digitsPerNode=<number>\"\n");
        return 1;
    }
    ArgumentManager am(argc, argv);
    std::string filename = am.get("input");
    std::string algorithm = am.get("algorithm");
    int digitsPerNode = std::stoi(am.get("digitsPerNode"));

    int size = count_lines(filename, digitsPerNode);
    BigNumber *a = new BigNumber[size];
    input(a, filename, digitsPerNode);

    Sort sort;
    sort.open_the_bigO();


    if (algorithm == "select")
    {
      sort.selectionSort(a,size);
      print(a, size);

    }
    if (algorithm == "insert")
    {
      sort.primer_insertion(a, size);
      print(a, size);
    }
    if (algorithm == "quick")
    {
      //print(a,size);
      //cout<<endl;
      sort.quickSort(a,0,size-1);
      print(a,size);

    }
    if (algorithm == "merge")
    {
        sort.mergeSort(a, size);
        print(a, size);
    }
    if (algorithm == "heap")
    {
      //print(a,size);
      sort.heapSort(a,size);
      print(a,size);
    }

    return 0;
}