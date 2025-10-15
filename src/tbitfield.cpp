// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < -1) throw -1;
    BitLen = len;

    MemLen = (BitLen + 31) / 32;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << (n % 32);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0) throw - 1;
    if (n > BitLen - 1) throw - 1;
    if ((pMem[n / 32] >> (n % 32)) & 1) return;
    pMem[n / 32] += (1 << (n % 32));
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0) throw - 1;
    if (n > BitLen - 1) throw - 1;
    if ((pMem[n / 32] >> (n % 32)) & 1)
        pMem[n / 32] -= (1 << (n % 32));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0) throw - 1;
    if (n > BitLen - 1) throw - 1;
    if ((pMem[n / 32] >> (n % 32)) & 1)
        return 1;
    else return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (this == &bf) return *this;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
    return *this;

}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.BitLen) return 0;
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return 0;
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.BitLen) return 1;
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return 1;
    return 0;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    if (MemLen > bf.MemLen) {
        TBitField res(BitLen);
        for (int i = 0; i < bf.MemLen; i++)
            res.pMem[i] = pMem[i] | bf.pMem[i];
        for (int i = bf.MemLen; i < MemLen; i++) {
            res.pMem[i] = pMem[i];
        }
        return res;
    }
    else {
        TBitField res(bf.BitLen);
        for (int i = 0; i < MemLen; i++)
            res.pMem[i] = pMem[i] | bf.pMem[i];
        for (int i = MemLen; i < bf.MemLen; i++) {
            res.pMem[i] = bf.pMem[i];
        }
        return res;
    }
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    if (BitLen > bf.BitLen) {
        TBitField res(BitLen);
        for (int i = 0; i < bf.MemLen; i++)
            res.pMem[i] = pMem[i] & bf.pMem[i];
        return res;
    }
    else {
        TBitField res(bf.BitLen);
        for (int i = 0; i < MemLen; i++)
            res.pMem[i] = pMem[i] & bf.pMem[i];
        return res;
    }
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(BitLen);
    for (int i = 0; i < BitLen; i++) {
        if (GetBit(i) == 0)
            res.SetBit(i);
    }
    return res;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) {
        ostr << bf.GetBit(i);
    }
    ostr << endl;
    return ostr;
}