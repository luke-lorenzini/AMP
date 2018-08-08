#pragma once
#include "neuron.h"

template <class type_t>
class logistic_neuron :
	public neuron<type_t>
{
public:
	logistic_neuron(int input, int output);
	~logistic_neuron();

#ifndef _ARRAYS
protected:
	void activate();
	void activate_der();
	void init_rand_real(int size, std::vector<type_t> &vect);
#endif
};

template <class type_t>
logistic_neuron<type_t>::logistic_neuron(int input, int output) :
	neuron(input, output)
{
}

template <class type_t>
logistic_neuron<type_t>::~logistic_neuron()
{
}

#ifndef _ARRAYS
template <class type_t>
void logistic_neuron<type_t>::activate()
{
	nnet_math<type_t>::logistic(ar_z, ar_y);
}

template <class type_t>
void logistic_neuron<type_t>::activate_der()
{
	nnet_math<type_t>::matrix_sub(ar_ones, ar_y, ar_t_y);

	nnet_math<type_t>::matrix_prod(ar_y, ar_t_y, ar_t_e0);
}

template <class type_t>
void logistic_neuron<type_t>::init_rand_real(int size, std::vector<type_t> &vect)
{
#ifdef _USE_FIXED_RAND
	/* Always generate the same random numbers */
	std::mt19937 gen(1);
#else
	/* Always generate different random numbers */
	std::mt19937 gen(rd());
#endif

	std::uniform_real_distribution<type_t> distReal(0, 1);
	const type_t sigma = sqrt((type_t)2 / size);
	std::normal_distribution<type_t> distNorm(0, sigma);

	for (int i = 0; i < size; i++)
	{
		vect.push_back(distReal(gen));
	}
}
#endif