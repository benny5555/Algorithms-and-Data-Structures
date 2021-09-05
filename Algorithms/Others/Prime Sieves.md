# Introduction

Think about the question: given an integer N, please output all the prime numbers which are less or equal to N/please output the N-th prime numbers.



Here are some solutions to these questions.



# Prime Sieve (Eratosthenes Sieve)

Good to solve the first question, key idea is simple: to make use of the previous known prime numbers to mark the latter ones.
$$
Space Complexity: O(n), Time Complexity: O(n \cdot logn\cdot logn)\approx O(n)
$$
(Only for Prime judgement itself)

It can also be used for calculating the minimum prime factor 

Here are the codes.

~~~C++
class EratoSieve {
public:
	vector<bool> primes(int n) {
		vector<bool> prime(n + 1, true);
		prime[0] = prime[1] = false;
		for (int i = 2; i * i <= n; ++i) {
			if (prime[i]) {
				for (int j = i * i; j <= n; j += i) {
					prime[j] = false;
				}
			}
		}

		return prime;
        //vector<int> prime(n + 1, 0);
		//for (int i = 2; i <= n; ++i) {
		//	if (prime[i]) continue;
		//	prime[++prime[0]] = i;
		//	int x = n / i;
		//	for (int j = i; j <= x; ++j) {
		//		prime[i * j] = 1;
		//	}
		//}
		//return prime;
	}
    

	vector<int> minPF(int n) {
		vector<int> minPF(n + 1, 0);
		for (int i = 2; i <= n; ++i) {
			if (minPF[i]) continue;
			int x = n / i;
			for (int j = 1; j <= x; ++j) {
				if (minPF[j * i]) continue;
				minPF[j * i] = i;
			}
		}
		return minPF;
	}
};
~~~

Notice that primes function repeatedly marked a lot of marked numbers. Here is a better solution to the questions.



# Linear Sieve (Euler Sieve)

$$
Space Complexity: O(n), Time Complexity:O(n)
$$

We want to use an integer M to mark a composite number N,  where some features must be met:

* Get p, which is the minimum prime in N
* N can be represented as p*m
* p must be less or equal to the minimum prime factor in M, namely, M is the maximum factor except for N
* Get a set that includes all minimum prime factors <= M, and make use of M*P' to mark N's.

Key idea: **When it meets the maximum factor except for an integer itself, use that factor to mark this integer.**

For example: given an N=30, we can find the p=2, M=15. That means only if we meet 15, then we mark N.

~~~C++
class LinearSieve {
public:
	int sieve(int n) {
		vector<int> prime(n + 1, 0);
		for (int i = 2; i <= n; ++i) {
            //if it is prime number.
			if (!prime[i]) prime[++prime[0]] = i;
            //j represents p while i represents M.
			for (int j = 1; j <= prime[0]; ++j) {
				if (prime[j] * i > n) break;
				prime[prime[j] * i] = 1;
                //p must be less or equal to the minimum prime factor of M.
				if (i % prime[j] == 0) break;
			}
		}
		return prime[0];
	}
};
~~~



## Number of factors for each number

Introduce the [number of factors formula](https://byjus.com/maths/factors-of-a-number/).

For example: 12 = 2\*2\*3 = 2^2 * 3, therefore, the number_of_factors[12] = (2+1) * (1+1) = 6.

From the introduction above can we assume that, for number of factors of a number i, there will be:
$$
f(i)=(a_1+1)\times(a_2+1)\times...
$$
We then make:
$$
M'=(a_2+1)\times...
$$
Then we have 
$$
M' = \frac{f(i)}{(a_1+1)}
$$
From the previous chapter can we know this formula when prime[j] and i are **not co-primes.**
$$
f(prime[j]\times i)=(a_1+1+1)\times(a_2+1)\times...=(a_1+2)\times M'
$$
Therefore, we can get:
$$
f(prime[j]\times i)=\frac{f(i)}{(a_1+1)\times(a_1+2)}
$$
where a1 is the smallest factor of an integer N.



When they are co-primes, 
$$
f(prime[j]\times i) = f[prime[j]]\times f[i]
$$
Codes here:

~~~C++
	vector<int> factors(int n) {
		vector<int> prime(n + 1, 0),
			f(n + 1, 0), power(n + 1, 0);
		for (int i = 2; i <= n; ++i) {
			//is prime
			if (!prime[i]) {
				prime[++prime[0]] = i;
				f[i] = 2;//factors of a prime must be 2
				power[i] = 1;//the power of a prime must be 1
			}
			for (int j = 1; j <= prime[0]; ++j) {
				if (prime[j] * i > n) break;
				prime[prime[j] * i] = 1;
				if (i % prime[j] == 0) {
					f[prime[j] * i] = f[i] / (power[i] + 1) * (power[i] + 2);
					power[prime[j] * i] = power[i] + 1;
					break;
				}
				//co-primes
				else {
					f[prime[j] * i] = f[prime[j]] * f[i];
					power[prime[j] * i] = 1;
				}
			}
		}
		return f;
	}
~~~



## Sum of the factors of every number

Make s[i] represent the sum of factors of integer i, we can get that:

12 = 2^2*3;

s[12]=2^0+2^1+2^2+3^0+3^1=28

Note that we can use [Geometric progression - Wikipedia](https://en.wikipedia.org/wiki/Geometric_progression) here.



When they are not co-primes, we can get that:
$$
s(i)=(a_1^0+a_1^1+...)\times M=\frac{1-q^n}{1-q}=\frac{1-power[i]}{1-q}\times M
$$
where M = (a_2^0+a_2^1+..)\*(a_3^0+...)\*...

We can know that when a and b are co-primes, assuming s(a) is the sum of factors of a, then we have:
$$
s(a\times b)=s(a)\times s(b)
$$


Then we get:
$$
s(prime[j]*i)=(a_1^0+a_1^1+a_1^2+...)\times M =  \frac{1-power[i]\times q}{1-q}\times \frac{s(i)}{\frac{1-power[i]}{1-q}}=s(i)\times \frac{1-power[i]\times q}{1-power[i]}
$$

~~~C++
	vector<int> sumOfFactors(int n) {
		vector<int> prime(n + 1, 0),
			s(n + 1, 0), power(n + 1, 0);
		for (int i = 2; i <= n; ++i) {
			if (!prime[i]) {
				prime[++prime[0]] = i;
				s[i] = i + 1;
				power[i] = i * i;//q^n. where n here is 2
			}
			for (int j = 1; j <= prime[0]; ++j) {
				if (prime[j] * i > n) break;
				prime[prime[j] * i] = 1;
				if (i % prime[j] == 0) {
					s[prime[j] * i] = s[i] * (power[i] * prime[j] - 1) / (power[i] - 1);
					power[prime[j] * i] = power[i] * prime[j];
					break;
				}
				else {
					s[prime[j] * i] = s[i] * s[prime[j]];
					power[prime[j] * i] = prime[j] * prime[j];
				}
			}
		}
		return s;
	}
~~~

