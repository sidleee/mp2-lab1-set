// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(-1)
{
    MaxPower = mp;
    BitField = TBitField(MaxPower);
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(-1)
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(-1)
{
    MaxPower = bf.GetLength();
    BitField = bf;
}

TSet::operator TBitField()
{
    return FAKE_BITFIELD;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem > MaxPower - 1) return 0;
    if (BitField.GetBit(Elem)) return 1;
    return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    if (this == &s) return *this;
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    if (MaxPower != s.MaxPower) return 0;
    if (BitField == s.BitField) return 1;
    return 0;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    if (MaxPower != s.MaxPower) return 1;
    if (BitField == s.BitField) return 0;
    return 1;
}

TSet TSet::operator+(const TSet& s) // объединение
{
    if (MaxPower > s.MaxPower) {
        TSet res(MaxPower);
        res.BitField = BitField | s.BitField;
        return res;
    }
    else {
        TSet res(s.MaxPower);
        res.BitField = BitField | s.BitField;
        return res;
    }
    
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet res(*this);
    res.BitField.SetBit(Elem);
    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet res(*this);
    res.BitField.ClrBit(Elem);
    return res;

}

TSet TSet::operator*(const TSet& s) // пересечение
{
    if (MaxPower > s.MaxPower) {
        TSet res(MaxPower);
        res.BitField = BitField & s.BitField;
        return res;
    }
    else {
        TSet res(s.MaxPower);
        res.BitField = BitField & s.BitField;
        return res;
    }
}

TSet TSet::operator~(void) // дополнение
{
    TSet res(MaxPower);
    res.BitField = ~BitField;
    return res;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    return ostr;
}
