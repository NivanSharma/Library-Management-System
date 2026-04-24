// Initializing C++

#include <iostream>
#include <string>
using namespace std;

class Item { // Item Class

protected:
    int id;
    string title;
    string publisher;
    int year;
    bool borrowed;

public:
    Item(int i, string t, string p, int y) { // Constructor
        id = i;
        title = t;
        publisher = p;
        year = y;
        borrowed = false;
    }

    virtual void displayInfo() = 0;

    virtual void borrow() {
        if (!borrowed) {
            borrowed = true;
            cout << "Item borrowed\n";
        }
        else
            cout << "Item already borrowed\n";
    }

    virtual void returnItem() {
        borrowed = false;
        cout << "Item returned\n";
    }

    string getTitle() {
        return title;
    }
};

class Book : public Item { // Derived Class Book

private:
    string author;

public:
    Book(int i, string t, string p, int y, string a) : Item(i, t, p, y) { // Constructor
        author = a;
    }

    void displayInfo() {
        cout << "\nBook\n";
        cout << id << endl;
        cout << title << endl;
        cout << author << endl;
        cout << publisher << endl;
        cout << year << endl;
    }
};

class Magazine : public Item { // Derived Class Magazine

private:
    int issue;

public:
    Magazine(int i, string t, string p, int y, int is) : Item(i, t, p, y) { // Constructor
        issue = is;
    }

    void displayInfo() {
        cout << "\nMagazine\n";
        cout << id << endl;
        cout << title << endl;
        cout << publisher << endl;
        cout << year << endl;
        cout << issue << endl;
    }
};

class Member { // Member Base Class

protected:
    int memberID;
    string name;
    string email;
    int maxBooks;

public:
    Member(int id, string n, string e, int max) { // Constructor
        memberID = id;
        name = n;
        email = e;
        maxBooks = max;
    }

    virtual void borrowItem(Item*) = 0;

    virtual void returnItem(Item*) = 0;

    string getName() {
        return name;
    }
};

class StudentMember : virtual public Member { // Inheritance Class StudentMember

protected:
    Item* borrowedItems[10];
    int count;

public:
    StudentMember(int id, string n, string e) : Member(id, n, e, 3) { // Constructor
        count = 0;
    }

    void borrowItem(Item* item) {
        if (count < maxBooks) {
            item->borrow();
            borrowedItems[count] = item;
            count++;
        }
        else
            cout << "Limit reached\n";
    }

    void returnItem(Item* item) {
        item->returnItem();
        count--;
    }
};

class TeacherMember : virtual public Member { // Inheritance Class TeacherMember

protected:
    Item* borrowedItems[10];
    int count;

public:
    TeacherMember(int id, string n, string e) : Member(id, n, e, 5) { // Constructor
        count = 0;
    }

    void borrowItem(Item* item) {
        if (count < maxBooks) {
            item->borrow();
            borrowedItems[count] = item;
            count++;
        }
        else 
            cout << "Limit reached\n";
    }

    void returnItem(Item* item) {
        item->returnItem();
        count--;
    }
};

class SpecialMember : public StudentMember, public TeacherMember { // Multiple Inheritance 

public:
    SpecialMember(int id, string n, string e) : Member(id, n, e, 7), StudentMember(id, n, e), TeacherMember(id, n, e) { // Multiple Constructors
    }

    void borrowItem(Item* item) {
        item->borrow();
        cout << "Special member borrowed item\n";
    }

    void returnItem(Item* item) {
        item->returnItem();
        cout << "Special member returned item\n";
    }
};

class Transaction { // Transaction Base Class

private:
    Member* member;
    Item* item;
    string type;

public:
    Transaction(Member* m, Item* i, string t) { // Constructor
        member = m;
        item = i;
        type = t;
    }

    void display() {
        cout << "\nTransaction\n";
        cout << member->getName() << endl;
        cout << item->getTitle() << endl;
        cout << type << endl;
    }
};

int main() { // Main Function
    
    Book b1(1, "Computer Science: An Overview (13th Edition)", "Pearson", 2018, "Glenn BrookShear");
    Magazine m1(2, "Software Developer Today", "IT Press", 2023, 12);
    StudentMember s1(100, "Nivan Sharma", "NivanSharma@gmail.com");
    TeacherMember t1(200, "John Smith", "JohnSmith@gmail.com");
    SpecialMember sp1(300, "Alex Weinberg", "AlexWeinberg@gmail.com");

    Item* i1 = &b1;
    Item* i2 = &m1;

    Member* mem1 = &s1;
    Member* mem2 = &t1;
    Member* mem3 = &sp1;

    mem1->borrowItem(i1);
    mem2->borrowItem(i2);
    mem3->borrowItem(i2);

    Transaction t(mem1, i1, "Borrow");

    t.display();

    mem1->returnItem(i1);

    return 0;

}