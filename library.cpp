#include "library.h"


MySet::MySet() {

}

MySet::~MySet() {

}


// boolean

MySet MySet::boolean() {
    MySet booleanMySet;
    MySet bufer;
    sets buferElement;
    buferElement.flag = false;
    booleanMySet += "{{}}";
    for (int x = 0; x < this->masElement.size(); x++) {
        buferElement.elements.clear();
        for (int y = x; y < this->masElement.size(); y++) {
            buferElement.elements.push_back(this->masElement[y]);
            booleanMySet.masElement.push_back(buferElement);
        }
    }
    for (int x = 0; x < this->masElement.size(); x++) {
        bufer.clearSet();
        bufer.masElement.push_back({ false, {}, "" });
        bufer.masElement[0].elements.push_back(this->masElement[x]);
        for (int y = x + 1; y < this->masElement.size(); y++) {
            bufer.masElement[0].elements.push_back(this->masElement[y]);
            booleanMySet += bufer;
            bufer.masElement[0].elements.pop_back();
        }
    }
    return booleanMySet;
}

// belong
bool MySet::belongElement(std::string& line) {
    MySet value;
    value.setter(line);
    return this->belongElement(value);
}

// difference
MySet MySet::operator - (MySet& value) {
    MySet difference;
    for (auto x : this->masElement)
        if (!check(value.masElement, x))
            difference.masElement.push_back(x);
    return difference;
}
MySet differenceSet(MySet& valueOne, MySet& valueTwo) {
    MySet difference;
    difference = valueOne - valueTwo;
    return difference;
}
void MySet::operator -= (std::string& line) {
    MySet value;
    value.setter(line);
    *this = *this - value;
}
void MySet::differenceElement(std::string& line) {
    *this -= line;
}





// cross
MySet MySet::operator * (MySet& value) {
    MySet crossing;
    for (auto x : this->masElement)
        if (check(value.masElement, x))
            crossing.masElement.push_back(x);
    return crossing;
}

MySet crossSet(MySet& valueOne, MySet& valueTwo) {
    MySet crossing;
    crossing = valueOne * valueTwo;
    return crossing;
}


// merge
MySet MySet::operator+(MySet& value) {
    MySet merging;
    merging.masElement = this->masElement;
    merging += value;
    return merging;
}
MySet mergeSet(MySet& valueOne, MySet& valueTwo) {
    MySet merging;
    merging = valueOne + valueTwo;
    return merging;
}


// add
bool MySet::add(MySet& value) {
    bool flag = false;
    for (auto x : value.masElement)
        if (!check(this->masElement, x)) {
            this->masElement.push_back(x);
            flag = true;
        }
    return flag;
}

bool MySet::add(std::string& line) {
    MySet value;
    value.setter(line);
    return this->add(value);
}


// check
bool MySet::check(sets& valueOne, sets& valueTwo) {
    if ((valueOne.flag + valueTwo.flag) % 2 == 0)
        if (valueOne.flag) {
            return valueOne.element == valueTwo.element;
        }
        else
            return check(valueOne.elements, valueTwo.elements) && check(valueTwo.elements, valueOne.elements);
    return false;
}
bool MySet::check(std::vector<sets>& valueOne, std::vector<sets>& valueTwo) {
    bool flag = false;
    for (auto x : valueOne) {
        for (auto y : valueTwo)
            if (check(x, y)) {
                flag = true;
                break;
            }
        if (!flag)
            return false;
        flag = false;
    }
    return true;
}
bool MySet::check(std::vector<sets>& valueOne, sets& valueTwo) {
    for (auto x : valueOne) {
        if (check(x, valueTwo))
            return true;
    }
    return false;
}


// getter
std::string MySet::getter() {
    std::string line;
    getter(this->masElement, line);
    return line;
}
void MySet::getter(std::vector<sets>& masElem, std::string& line) {
    line += "{ ";
    for (int x = 0; x < masElem.size(); x++) {
        if (masElem[x].flag)
            line += masElem[x].element;
        else
            getter(masElem[x].elements, line);
        if (x + 1 != masElem.size())
            line += ", ";
    }
    line += " }";
}



// setter
void MySet::setter(std::string& line) {
    for (int i = 0; line[i]; i++)
        if (line[i] == '{') {
            setter(this->masElement, line, i);
            return;
        }
    this->masElement.push_back({ true, {} , line });
}
int MySet::setter(std::vector<sets>& masElem, std::string& line, int n) {
    std::string element = "";
    for (int i = n + 1; line[i]; i++) {

        if (line[i] != ' ' && line[i] != '}' && line[i] != ',' && line[i] != '{')
            element += line[i];
        else {
            if (element != "")
                masElem.push_back({ true, {}, element });
            element = "";
        }

        if (line[i] == '}')
            return i;

        if (line[i] == '{') {
            masElem.push_back({ false, {}, "" });
            i = setter(masElem.back().elements, line, i);
        }

    }
}
