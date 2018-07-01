#ifndef TENSOR
#include <random>
#include <string>
#include <cstring>
#include <stdexcept>
#include <cmath>
#include <utility>
#include <iostream>
#define TENSOR
class Tensor
{
private:
	int n,m;
	double value;
	double** matrix;
	bool ismat;
public:
	Tensor():n(0),m(0),value(0),matrix(nullptr),ismat(false){};
	
	Tensor(const double val):Tensor(){value=val;}
	
	Tensor(const int _n,const int _m,double (**mat)=nullptr):n(_n),m(_m),ismat(true),value(0)
	{
		matrix=new double*[n];
		for(int i=0;i<n;i++)
			matrix[i]=new double[m];
		if(mat!=nullptr)
		{
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
					matrix[i][j]=mat[i][j];
		}
	}
	
	Tensor(Tensor&& t):ismat(t.ismat),n(t.n),m(t.m),value(t.value),matrix(t.matrix)
	{
		if(t.ismat)t.matrix=nullptr;
	}
	
	Tensor(const Tensor& t):ismat(t.ismat),n(t.n),m(t.m),value(t.value),matrix(nullptr)
	{
		if(t.ismat)
		{
			matrix=new double*[n];
			for(int i=0;i<n;i++)
				matrix[i]=new double[m];
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
					matrix[i][j]=t.matrix[i][j];
		}
	}
	
	Tensor(const int _n,const int _m,int (*rand)()):Tensor(_n,_m)
	{
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				matrix[i][j]=((*rand)() / double(RAND_MAX) - 0.5)/100; // 这里修改了！
	}
	
	Tensor& operator =(const Tensor& a); 
	Tensor& operator +=(const Tensor& a); 
	Tensor& operator -=(const Tensor& a);
	Tensor& operator /=(const Tensor& a); 
	Tensor& operator *=(const Tensor& a); 
	
	int N()const
	{
		if(!ismat)
			throw std::runtime_error("Error : Try to get N from Tensor(Number)!");
		return n;
	}
	int M()const
	{
		if(!ismat)
			throw std::runtime_error("Error : Try to get M from Tensor(Number)!");
		return m;
	}

	operator double() {
		if(ismat)
			throw std::runtime_error("Error : Try to convert to double from Tensor(matrix)!");
		return value;
	}

	bool operator <(const Tensor &b) const{
		if(ismat||b.ismat)
			throw std::runtime_error("Error : Try to convert to double from Tensor(matrix)!");
		return value < b.value;
	}

	bool operator >(const Tensor &b) const{
		if(ismat||b.ismat)
			throw std::runtime_error("Error : Try to convert to double from Tensor(matrix)!");
		return value > b.value;
	}

	bool operator <= (const Tensor &b) const{
		return !(*this>b);
	}

	bool operator >= (const Tensor &b) const{
		return !(*this<b);
	}

	bool Type()const{return ismat;}
	double Value()const;
	double** Matrix()const;
	std::string PrintType()const;
	std::string Print(int cnt=6)const;
	
	~Tensor()
	{
		if(matrix==nullptr)return;
		for(int i=0;i<n;i++)
			delete[] matrix[i];
		delete[] matrix;
	}
	
	double Quadratic_Cost()const
	{
		double ans=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				ans+=matrix[i][j]*matrix[i][j];
		return ans;
	}
	void Sigmoid()
	{
		if(ismat)
		{
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
					matrix[i][j]=1/(1+exp(-matrix[i][j]));
		}else 
			value=1/(1+exp(-value));
	}
	void sig_grad ()
    {
        if(ismat)
        {
            for(int i=0;i<n;i++)
                for(int j=0;j<m;j++)
                    matrix[i][j] = exp(-matrix[i][j]) /((1+exp(-matrix[i][j]))*(1+exp(-matrix[i][j])));
        }else
            value = exp(-value) / ((1+exp(-value)) * (1+exp(-value)));
    }

    int Max () {
        if (!ismat || n != 1)
            throw std::runtime_error(" Error : Try to get max_value from wrong dimension matrix.");

        double tmp = matrix[0][0];
        int index = 0;
        for (int i = 1; i < m; i++) {
            if (matrix[0][i] > tmp) {
                tmp = matrix[0][i];
                index = i;
            }
        }
        return index;
    }
    void Transpose(const Tensor& t)
	{
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				matrix[i][j]=t.matrix[j][i];
	}
	friend Tensor operator+(const Tensor&,const Tensor&);
	friend Tensor operator-(const Tensor&,const Tensor&);
	friend Tensor operator*(const Tensor&,const Tensor&);
	friend Tensor operator/(const Tensor&,const Tensor&);
	friend Tensor exp(const Tensor&);
	friend Tensor ln(const Tensor&);
	friend Tensor sin(const Tensor&);
	friend Tensor cos(const Tensor&);
	friend Tensor tan(const Tensor&);
	friend Tensor asin(const Tensor&);
	friend Tensor acos(const Tensor&);
	friend Tensor atan(const Tensor&);
	friend Tensor pow(const Tensor&,const Tensor&);
	friend Tensor pow(const Tensor&,double);
	friend Tensor dmul(const Tensor&, const Tensor&);
	friend void swap(Tensor&,Tensor&);
	friend Tensor concat(const Tensor&, const Tensor&, int concat_dim);
	friend Tensor slice(Tensor&, std::vector<int> begin, std::vector<int> size);

};

#endif
