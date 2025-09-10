#include <iostream>
#include <string>

using namespace std;

class DynamicStringArray {
private:
    string* dynamicArray;
    int size;
public:

	// Big tree decleration
    DynamicStringArray();
    DynamicStringArray(const DynamicStringArray& copy);
    ~DynamicStringArray();

	// Member function decleration

    DynamicStringArray& operator=(const DynamicStringArray& equal);

    int getSize() const { return size; }

    void addEntry(const string& entry);

    bool deleteEntry(const string& entry);
	
    string getEntry(int index) const;

};

int main() {

    DynamicStringArray names;

    // List of names
    names.addEntry("Frank");
    names.addEntry("Wiggum");
    names.addEntry("Nahasapeemapetilon");
    names.addEntry("Quimby");
    names.addEntry("Flanders");
    
	// Output list
    cout << "List of names:" << endl;
    for (int i = 0; i < names.getSize(); i++) {
        cout << names.getEntry(i) << endl;
    }

    cout << endl;
    
	// Add and remove some names
    names.addEntry("Spuckler");
    
	cout << "After adding a name:" << endl;
    for (int i = 0; i < names.getSize(); i++) {
        cout << names.getEntry(i) << endl;
    }

    cout << endl;
    names.deleteEntry("Nahasapeemapetilon");
    cout << "After removing a name:" << endl;
    
	for (int i = 0; i < names.getSize(); i++) {
        cout << names.getEntry(i) << endl;
    }

    cout << endl;
    names.deleteEntry("Skinner");
    
	cout << "After removing a name that isn't on the list:" << endl;
    
	for (int i = 0; i < names.getSize(); i++) {
        cout << names.getEntry(i) << endl;
    }
    
	cout << endl;
    names.addEntry("Muntz");
    cout << "After adding another name:" << endl;
    
	for (int i = 0; i < names.getSize(); i++) {
        cout << names.getEntry(i) << endl;
    }
    cout << endl;
    
	// Remove all of the names by repeatedly deleting the last one
    
	while (names.getSize() > 0) {
        names.deleteEntry(names.getEntry(names.getSize() - 1));
    }
    
	cout << "After removing all of the names:" << endl;
    for (int i = 0; i < names.getSize(); i++) {
        cout << names.getEntry(i) << endl;
    }
    cout << endl;
    
	names.addEntry("Burns");
    cout << "After adding a name:" << endl;
    for (int i = 0; i < names.getSize(); i++) {
        cout << names.getEntry(i) << endl;
    }
    cout << endl;
    
	
	cout << "Testing copy constructor" << endl;
    DynamicStringArray names2(names);
    
	
	// Remove Burns from names
    names.deleteEntry("Burns");
    cout << "Copied names:" << endl;
    for (int i = 0; i < names2.getSize(); i++) {
        cout << names2.getEntry(i) << endl;
    }
    cout << endl;
    cout << "Testing assignment" << endl;
    
	
	DynamicStringArray names3 = names2;
    // Remove Burns from names2
    names2.deleteEntry("Burns");
    cout << "Copied names:" << endl;
    for (int i = 0; i < names3.getSize(); i++) {
        cout << names3.getEntry(i) << endl;
    }
    cout << endl;
    cout << "Enter a character to exit." << endl;
    char wait;
    cin >> wait;


	
    return 0;
}



// Big tree implemantation

DynamicStringArray::DynamicStringArray(){
	dynamicArray = NULL;
	size = 0;
}

DynamicStringArray::DynamicStringArray(const DynamicStringArray& copy){

	size = copy.size;
    dynamicArray = new string[size];

    for (int i = 0; i < size; i++) {
        dynamicArray[i] = copy.dynamicArray[i];
    }
}

DynamicStringArray::~DynamicStringArray(){
	delete[] dynamicArray;
}

// Member function implementation

DynamicStringArray& DynamicStringArray::operator=(const DynamicStringArray& equal) {
    
 // controlling objects are different
	if (this != &equal) {
        delete[] dynamicArray;
        size = equal.size;
        dynamicArray = new string[size];
        for (int i = 0; i < size; i++) {
                dynamicArray[i] = equal.dynamicArray[i];
        }
    }
    return *this;
}

void DynamicStringArray::addEntry(const string& entry){

    string* new_array = new string[size + 1];
        
	for (int i = 0; i < size; i++) {
        new_array[i] = dynamicArray[i];
    }
        
	new_array[size] = entry;
    delete[] dynamicArray;
    dynamicArray = new_array;
    size++;
}


bool DynamicStringArray::deleteEntry(const string& entry) {
    
	int index = -1;
        
	for (int i = 0; i < size; i++) {
        if (dynamicArray[i] == entry) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return false;
    }

    string* new_array = new string[size - 1];
        
	for (int i = 0; i < index; i++) {
        new_array[i] = dynamicArray[i];
    }
    for (int i = index + 1; i < size; i++) {
        new_array[i - 1] = dynamicArray[i];
    }

    delete[] dynamicArray;
        
	dynamicArray = new_array;
    size--;
        
	return true;
}

string DynamicStringArray::getEntry(int index) const {
    
	if (index < 0 || index >= size) {
        return NULL;
    }
    return dynamicArray[index];
}
	
