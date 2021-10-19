#include "library.h"


MySet::MySet() {
 // конструктор класса
}

MySet::~MySet() {
  // деструктор класса
}


// boolean

MySet MySet::boolean() { // буллеан множества
    MySet booleanMySet; // само булеан множество
    MySet bufer; // буферное мнжество 
    sets buferElement;
    buferElement.flag = false;
    booleanMySet += "{{}}";
    for (int x = 0; x < this->masElement.size(); x++) { // сначал формируем накладные например ( {1,2,3} ) - {1} {1,2} {1,2,3}
        buferElement.elements.clear();
        for (int y = x; y < this->masElement.size(); y++) {
            buferElement.elements.push_back(this->masElement[y]);
            booleanMySet.masElement.push_back(buferElement);
        }
    }
    for (int x = 0; x < this->masElement.size(); x++) { // затем формируем комбинации {1,3} 
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
MySet MySet::operator - (MySet& value) { // работае по принципу переписываем все множество кроме данного элемента
    MySet difference;
    for (auto x : this->masElement)
        if (!check(value.masElement, x))
            difference.masElement.push_back(x);
    return difference;
}
MySet differenceSet(MySet& valueOne, MySet& valueTwo) { // использует выше указанную функцию
    MySet difference;
    difference = valueOne - valueTwo;
    return difference;
}
void MySet::operator -= (std::string& line) { // использует выше описанную функцию
    MySet value;
    value.setter(line);
    *this = *this - value;
}
void MySet::differenceElement(std::string& line) {
    *this -= line;
}





// cross
MySet MySet::operator * (MySet& value) { // пересечение проверяет если элементы схожи то записываем 
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
MySet MySet::operator+(MySet& value) { // проверяет если элементы отсутствуют у друг друга тто записываем
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
bool MySet::check(sets& valueOne, sets& valueTwo) { // проверка на схожесть элементов
    if ((valueOne.flag + valueTwo.flag) % 2 == 0) // если элементы разного типа элемент и множество как элемент
        if (valueOne.flag) { // если элемент то проверям их значения 
            return valueOne.element == valueTwo.element;
        }
        else
            return check(valueOne.elements, valueTwo.elements) && check(valueTwo.elements, valueOne.elements); // если множества то запускаем проверку на схожесть множеств
    return false;
}
bool MySet::check(std::vector<sets>& valueOne, std::vector<sets>& valueTwo) { // схожесть множеств
    bool flag = false;
    for (auto x : valueOne) { // по всем элементам одного 
        for (auto y : valueTwo) // и другого 
            if (check(x, y)) { // если равны их элементы 
                flag = true;
                break;
            }
        if (!flag)
            return false;
        flag = false;
    }
    return true;
}
bool MySet::check(std::vector<sets>& valueOne, sets& valueTwo) { // проверка на принадлежность элемента ко множеству 
    for (auto x : valueOne) { // если элемент массива 
        if (check(x, valueTwo)) // схожи с данным  возвращаем true
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
