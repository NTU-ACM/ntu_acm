long long gcd(long long x,long long y) {
	if (x<0) x=-x;
	if (y<0) y=-y;
	while (true) {
		if (x==0) return (y);
		if (y==0) return (x);
		if (x>y) x%=y; else y%=x;
	}
}
struct Rational {
	long long p,q;
	Rational() {
		p=0;q=1;
	}
	Rational(long long p) {
		this->p=p;
		this->q=1;
	}
	Rational(long long p,long long q) {
		if (q<0) {
			p=-p;q=-q;
		}
		this->p=p;
		this->q=q;
	}
	Rational operator + (const Rational &x) const {
		return (Rational(p*x.q+q*x.p,q*x.q));
	}
	Rational operator - (const Rational &x) const {
		return (Rational(p*x.q-q*x.p,q*x.q));
	}
	Rational operator * (const Rational &x) const {
		return (Rational(p*x.p,q*x.q));
	}
	Rational operator / (const Rational &x) const {
		return (*this*x.inverse());
	}
	Rational inverse(void) const {
		return (Rational(q,p));
	}
	int compare(const Rational &x) const {
		long long A=p*x.q;
		long long B=q*x.p;
		return ((A>B)-(A<B));
	}
	#define DEF_OPER(x) bool operator x (const Rational &a) const { \
		return (compare(a) x 0); \
	}
	DEF_OPER(<) DEF_OPER(>) DEF_OPER(<=) DEF_OPER(>=) DEF_OPER(==) DEF_OPER(!=)
	#undef DEF_OPER
};

std::ostream& operator << (std::ostream &os,const Rational &x) {
	long long t=gcd(x.p,x.q);
	return (os<<x.p/t<<"/"<<x.q/t);
}