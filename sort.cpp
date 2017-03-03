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

    void operator=(DoubleLinkedList & other)
    {
        // cout << "equal" << endl;
        head = other.head;
        other.head = nullptr;
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
        cout << endl;
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
    BigNumber & operator= (BigNumber other)
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

private:
    bool isNegative = false;
    DoubleLinkedList data;
};

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

    fstream bigO;

  private:
      //fstream bigO;

  };


      void print(BigNumber *a, int size)
      {
          for (int i = 0; i < size; i++)
          {
              a[i].print();
          }
      }

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

    }
    if (algorithm == "heap")
    {
      //print(a,size);
      sort.heapSort(a,size);
      print(a,size);
    }

    return 0;
}