#include <iostream>
#include "string.h"
/// <summary> Деструктор </summary>
String::~String(){
    delete [] Data;
}
/// <summary> Конструктор по умолчанию </summary>
String::String() : Data(nullptr)
{}
/// <summary> Конструктор копирования </summary>
/// <param name="rhs">Объект, который копируем </param>
String::String(const String& rhs){
	Data = new char[this->Size() + 1];
	std::copy(rhs.Data, rhs.Data + rhs.Size(), Data);
}
/// <summary> Пользовательский конструктор </summary>
/// <param name="data">Данные, которые требуется поместить в создаваемый объект </param>
String::String(const char * data){
    size_t len = 0;
    for (; data[len]; len++)
    { }
    Data = new char[len + 1];
    memcpy(Data, data, len);
    Data[len] = '\0';
}
/// <summary> Оператор присваивания </summary>
/// <param name="data">Объект, который копируем </param>
/// <returns>Возвращаем ссылку на себя</returns>
String& String::operator=(const String& rhs){
    if (this != &rhs){
        Data = new char[this->Size() + 1];
        std::copy(rhs.Data, rhs.Data + rhs.Size(), Data);
    }
    return *this;
}
/// <summary> Оператор += </summary>
/// <param name="rhs">Объект, который стоит после знака '+=' </param>
/// <returns>Возвращаем ссылку на себя</returns>
String& String::operator+=(const String& rhs){
    Data = new char[this->Size() + rhs.Size() + 1];
    std::copy(rhs.Data, rhs.Data + rhs.Size(), Data + this->Size());
    return *this;
}
/// <summary> Оператор == </summary>
/// <param name="rhs">Объект, который стоит после знака '==' </param>
/// <returns>Возвращаем значения равенства двух строк</returns>
bool String::operator==(const String& rhs) const{
    if (this->Size() != rhs.Size()){
        return false;
    }
    else{
        for (int i = 0; i < this->Size(); i++){
            if (Data[i] != rhs.Data[i]){
                return false;
                break;
            }
        }
        return true;
    }
}
/// <summary> Оператор &lt; </summary>
/// <param name="rhs">Объект, который стоит после знака "&lt;" </param>
/// <returns>Возвращаем значения сравнения двух строк</returns>
bool String::operator<(const String& rhs) const {
	int i = 0;
	while (rhs.Data[i] == Data[i]) {
		i++;
	}
	if (Data[i] > rhs.Data[i]) {
		return false;
	}else{
		return true;
	}
}
/// <summary> Функция поиска подстроки</summary>
/// <param name="substr">Подстрока, которую необходимо найти </param>
/// <returns>Возвращаем позицию substr. Если подстрока не найдена, то возвратить -1</returns>
size_t String::Find(const String& substr) const{
    auto pFirst = strstr(Data, substr.Data);
    if (pFirst == NULL){
        return -1;
    }else{
        return (size_t)pFirst;
    }
}
/// <summary> Функция замены букв </summary>
/// <param name="oldSymbol">Символ, который требуется заменить </param>
/// <param name="newSymbol">Символ, на который требуется заменить </param>
void String::Replace(char oldSymbol, char newSymbol){
    for (int i = 0; i < this->Size(); i++){
        if (Data[i] == oldSymbol){
            Data[i] = newSymbol;
        }
    }
}
/// <summary> Функция возвращает длину строки </summary>
/// <returns>Возвращаем длину строки</returns>
size_t String::Size() const{
    size_t len = 0;
    auto temp = Data;
    while(*temp++) ++len;
    return len;
}
/// <summary> Функция для определения пуста ли строка </summary>
bool String::Empty() const{
    if (this->Size() == 0){
        return true;
    }
    return false;
}
/// <summary> Оператор [] </summary>
/// <param name="index"> Индекс символа </param>
/// <returns> Значение символа в строке с индексом index</returns>
char String::operator[](size_t index) const{
    return Data[index];
}
/// <summary> Оператор [] </summary>
/// <param name="index"> Индекс символа </param>
/// <returns> Ссылка на символ в строке с индексом index</returns>
char& String::operator[](size_t index){
    return Data[index];
}
/// <summary> Смотри пример </summary>
/// <example>
/// <code>
/// String str = "___some string___";
/// str.RTrim('_'); // теперь переменная str равна "___some string"
/// </code>
/// </example>
/// <param name="symbol"> Значение символов, которе отрезаем </param>
void String::RTrim(char symbol){
    int temp = 0;
    for (int i = (int)this->Size() - 1; i >= 0; i--){
        if (Data[i] == symbol){
            temp = (int)(this->Size() - 1) - i;
        }else{
            break;
        }
    }
    char * test = new char[temp + 1];
    std::copy(Data, Data + temp, test);
    Data = test;
    delete [] test;
}
/// <summary> Смотри пример </summary>
/// <example>
/// <code>
/// String str = "___some string___";
/// str.LTrim('_'); // теперь переменная str равна "some string___"
/// </code>
/// </example>
/// <param name="symbol"> Значение символов, которе отрезаем </param>
void String::LTrim(char symbol){
    int temp = 0;
    for (int i = 0; i < (int)this->Size(); i++){
        if (Data[i] == symbol){
            temp = i;
        }else{
            break;
        }
    }
    char * test = new char[this->Size() - temp];
    std::copy(Data + temp, Data + this->Size(), test);
    Data = test;
    delete [] test;
}
/// <summary> Оператор +</summary>
/// <returns>Возвращаем строку равную a + b</returns>
String operator+(const String& a, const String& b) {
	String c(a);
	return c += b;
}
/// <summary> Оператор !=</summary>
bool operator!=(const String& a, const String& b) {
	return !(a == b);
}
/// <summary> Оператор &gt;</summary>
bool operator>(const String& a, const String& b) {
	if (a == b) {
		return false;
	}
	return !(a < b);
}
/// <summary> Оператор вывода </summary>
/// <param name="out">Поток куда выводим строку </param>
/// <param name="str">Строка, которую выводим </param>
/// <returns>Возвращаем ссылку на поток</returns>
std::ostream & operator<<(std::ostream& out, const String& str) {
	for (size_t i = 0; i < str.Size(); i++) {
		out << str.Data[i];
	}
	return out;
}
