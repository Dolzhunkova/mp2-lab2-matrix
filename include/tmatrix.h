// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (size > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size should not be greater than max size");
    if (size == 0)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[size]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      this->sz = v.sz;
      this->pMem = new T[this->sz];
      for (int i = 0; i < sz; i++)
          this->pMem[i] = v.pMem[i];
  }
  
  ~TDynamicVector()
  {
      if (pMem != NULL)
      {
          delete[] pMem;
          pMem = NULL;
          sz = 0;
      }
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
     if (this != &v)
      {
          if (sz != v.sz)
          {
              delete[] pMem;
              sz = v.sz;
              pMem = new T[sz];
          }
          for (int i = 0; i < sz; i++)
              pMem[i] = v.pMem[i];
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v)
      {
          if (sz != v.sz)
          {
              delete[] pMem;
              sz = v.sz;
              pMem = new T[sz];
          }
          for (int i = 0; i < sz; i++)
              pMem[i] = v.pMem[i];
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind < 0 || ind >= sz)
          abort(); // принудительное завершение программы
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind < 0 || ind >= n)
          abort(); // принудительное завершение программы
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz || ind < 0) throw "Index error";
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz || ind < 0) throw "Index error";
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this->sz != v.sz) return false;
      else 
          for (int i = 0; i < this->sz; i++) {
              if (this->pMem[i] != v.pMem[i]) return false;
          }
      return true;


  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (this->sz != v.sz) return true;
      else
          for (int i = 0; i < this->sz; i++) {
              if (this->pMem[i] != v.pMem[i]) return true;
          }
      return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector t1(this->size());
      for (int i = 0; i < this->size(); i++) {
          t1.pMem[i] = this->pMem[i] + val;
      }
      return t1;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector t1(this->size());
      for (int i = 0; i < this->size(); i++) {
          t1.pMem[i] = this->pMem[i] - val;
      }
      return t1;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector t1(this->size());
      for (int i = 0; i < this->size(); i++) {
          t1[i] = this->pMem[i] * val;
      }
      return t1;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (this->sz != v.sz) throw "Должна быть одинаковая размерность";
      TDynamicVector<int> res(v.sz);
      for (int i = 0; i < v.sz; i++)
          res[i] = v.pMem[i] + this->pMem[i];
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (this->sz != v.sz) throw "Должна быть одинаковая размерность";
      TDynamicVector<int> res(v.sz);
      for (int i = 0; i < v.sz; i++)
          res[i] = v.pMem[i] - this->pMem[i];
      return res;
  }
  T operator*(const TDynamicVector& v)
  {
      if (this->sz != v.sz) throw "Должна быть одинаковая размерность";
      T res = 0;
      for (int i = 0; i < v.sz; i++)
          res += v.pMem[i] * this->pMem[i];
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s > MAX_MATRIX_SIZE)
          throw out_of_range("Matrix size should be smaller than max size");

    for (size_t i = 0; i < s; i++)
      pMem[i] = TDynamicVector<T>(s);
  }

  size_t size() const noexcept { 
      size_t pSize = pMem[0].size();
      return pMem[0].size();
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (this->sz != m.sz) return false;
      else
          for (int i = 0; i < this->sz; i++)
              if (this->pMem[i] != m.pMem[i]) return false;
      return true;
  }
  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      if (this->sz != m.sz) return true;
      else
          for (int i = 0; i < this->sz; i++)
              if (this->pMem[i] != m.pMem[i]) return true;
      return false;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix m1(this->size());
      for (int i = 0; i < this->size(); i++) {
          m1[i] = this->pMem[i] * val;
      }
      return m1;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (v.size() != this->pMem[0].size())
      {
          throw out_of_range("Matrix should be equal size with vector");
      }
      int vSize = v.size();
      TDynamicVector<int> res(vSize);
      for (int i = 0; i < vSize; i++)
          for (int j = 0; j < vSize; j++)
              res[i] += v.pMem[j] * this->pMem[i][j];
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (m.pMem[0].size() != this->pMem[0].size())
      {
          throw out_of_range("Matrices should be equal sizes");
      }
      int mSize = m.pMem[0].size();
      TDynamicMatrix res(mSize);
      for (int i = 0; i < mSize; i++)
          for (int j = 0; j < mSize; j++)
              res.pMem[i][j] = this->pMem[i][j] + m.pMem[i][j];
      return res;
  }

  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (m.pMem[0].size() != this->pMem[0].size())
      {
          throw out_of_range("Matrices should be equal sizes");
      }
      int mSize = m.pMem[0].size();
      TDynamicMatrix res(mSize);
      for (int i = 0; i < mSize; i++)
          for (int j = 0; j < mSize; j++)
              res.pMem[i][j] = this->pMem[i][j] - m.pMem[i][j];
      return res;
      /*if (this.str != m.str || this.stlb != this.stlb)
      {
          cout << "Должна быть одинаковая размерность" << endl;
          break;
      }
      T** res = new T[this.str][this.stlb];
      for (int i = 0; i < this.str; i++)
          for (int j = 0; j < this.stlb; j++)
              res.pMem[i][j] = this.pMem[i][j] - m.pMem[i][j];
      return res;*/
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (this.str != m.stlb || this.stlb != m.str)
      {
          cout << "Число столбцов m1 должно совпадать с числом строк m2, а число строк m1 должно совпадать с числом столбцов m2" << endl;
          break;
      }
      T** res = new T[this.str][m.stlb];
      for (int i = 0; i < this.str; i++)
          for (int j = 0; j < m.stlb; j++)
              for (int k = 0; k < this.stlb; k++)
                  res[i][j] += this.pMem[i][k] * m.pMem[k][j];
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      int str_;
      int stlb_;
      cout << "Введите количество строк:";
      istr >> str_;
      cout << endl << "Введите количество строк:";
      istr >> stlb_;
      if (v.str != str_ || v.stlb != stlb_)
      {
          if (v.pMem != NULL)
              for (int i = 0; i < stlb; i++)
              {
                  delete[] v.pMem[i];
              }
          delete[] v.pMem;
          v.str = str_;
          v.stlb = stlb_;
          v.pMem = new T[str_][stlb_];
      }
      for (int i = 0; i < v.str; i++)
          for (int j = 0; j < v.stlb; j++)
          {
              cout << endl << "Введите значение:";
              istr >> v.pMem[i][j];
          }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
     /* for (int i = 0; i < v.str; i++)
      {
          ostr << "(";
          for (int j = 0; j < v.stlb; j++)
              ostr << v.pMem[i][j] << " ";
          ostr << ")" << endl;
      }
      ostr << endl;*/
      return ostr;
  }

};

#endif
