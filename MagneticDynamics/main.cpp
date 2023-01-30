#include <iostream>
#include <fstream>
#include<chrono>
#include<cstdlib>
#include "matrices.hpp"
#include "functions.hpp"
#include <ctime>
#include "plotting.h"
#include <algorithm>

#define PI 3.14159265359

// double* function::test(std::pair<double*, double>x, double* param)
// {
// 	double* y = new double;
// 	*y = 3.0*sin(x.second)+1.5*sin(2.0*x.second)+0.75*sin(3.0*x.second)+0.375*sin(4.0*x.second)+0.01*sin(8.0*x.second);
// 	return y;
// }
std::pair<double,double> largestElement(solution<double>& X)
{
	std::pair<double,double> max = X.data[0];
	for(uint i = 1; i < X.get_n_iterations(); i++)
	{
		if(max.first < X.data[i].first)
		{
			max = X.data[i];
		}
	}
	return max;
}
void ClientCode(std::unique_ptr<Solver>& method, void (*func) (std::pair<double*, double>, double*,double*&), std::pair<double*, double> x0, double* param, double t_initial, double t_final, double h, uint dim)
{
    method->Method(func,x0,param,t_initial, t_final, h, dim);
}
void simpleFilter(solution<double>& x, std::vector<std::pair<double,double>>& accepted)
{
	// std::vector<std::pair<double,double>>* accepted= new std::vector<std::pair<double,double>>; 
	// std::pair<double,double>* max = new std::pair<double,double>;
	// max = largestElement(x);
	// std::cout<<max.first*0.5<<'\n';
	for(uint i = 0; i < x.get_n_iterations(); i++)
	{
		if(x.data[i].first/largestElement(x).first >= 0.50)
		{
			accepted.emplace_back(x.data[i]);
		}
	}
	// delete max;
	// return accepted;
}

int main(void)
{
	auto start = std::chrono::high_resolution_clock::now(); 

	std::srand(time(0));
	// double* y = new double[5];
	
	// auto x = std::make_unique<std::vector<double>>();

	// std::vector<double> y  = *x->data();

	// std::cout<<*x->data(1)<<"\n";
	// x->data[2] = 5.0;
	// std::cout<<x->data[2];
	// std::unique_ptr<double*> x;

	// x.get() = y;
	// x.get(0);

	double* param = new double[3];
	param[0] = 10.0;
	param[1] = 8.0/3.0;
	param[2] = 28.0;
	Lorenz fun = Lorenz(param);
	double* coord = new double[3];
	coord[0] = 1.0;
	coord[1] = 1.0;
	coord[2] = 1.0;

	std::pair<double*,double > x = std::make_pair(coord,0);
	
	std::unique_ptr<Solver> solver = std::make_unique<RK45thSolver>();
	ClientCode(solver,Lorenz::lorenz_equation, x, param,0.0,500.0,1e-3,3);

	std::string testeFactory = "testeFactoryrk45.txt";
	solver->rk_int->printSolutionDoublePtr(testeFactory);

	free(param);
	free(coord);

	// free(solver);;
	// double* (*func) (std::pair<double*, double>, double*), std::pair<double*, double> x0, double* param, double t_initial, double t_final, double h, uint dim
	// ClienteCode(*solver, Lorenz::lorenz_equation, x, fun.get_param(),0.0,10.0, 0.1, 3);

	// ptr = std::unique_ptr<double*>(new double);
	 
	
	// x.set_dim(2); 
	// for(auto i: *x)
	// {
	// 	std::cout<<i <<"\n";
	// }
	// x.time = 5;

	// function testFunc = function::test(); 
	// double* x = new double[1]; 
	// solution<double*>* signal = function::createSignal(testFunc, x,0, 10,0.01,1);
	// testFunc.rk_int = signal;
	// testFunc.rk_int->t0 = signal->t0;  
	// testFunc.rk_int->tf = signal->tf; 
	// solution<double>* four = testFunc.applyFourierTransform(0,10,0.001);
	// std::string fourierzin = "FourierTest.txt";

	// four->printSolutionDouble(fourierzin);



	////////////////////////////////////////////////////////////////////////

	// double* x = new double[2]{1.0,0.0};
 	// std::fstream plot; 
	// double step = 0.025;
	// double* param = new double[2];
	// std::vector<std::pair<double,double>> filtered;
	// plot.open("bifucacao.txt",std::fstream::out);
	
	// std::unique_ptr<function> f = std::make_unique<function>(function::magenticDipole,2,2,param);

	// std::pair<double*,double> X = std::make_pair(x,0); 
	// for(int j = -100; j < 100; j++)
	// {
	// 	param[0] = 1.0;
	// 	param[1] = j*step;
	// 	f->set_param(param);    
	// 	f->applyRunge_kutta4th(X,0,100,1e-2);
	// 	// solution<double>* four = new solution<double>;
	// 	f->applyFourierTransform(-2,2,0.01);
	// 	simpleFilter(*f->fourier_transform,filtered);
	// 	f->rk_int->data.clear();
	// 	f->fourier_transform->data.clear();

	// 	plot.open("bifucacao.txt",std::fstream::app);

	// 	for(auto k : filtered)
	// 	{
	// 		plot<<j*step<<" "<<k.first<<" "<<k.second<<"\n";
	// 	}
	// 	plot.close();

	// 	filtered.clear();
	// }
	// // std::cout<<"salve!\n";
	// free(x);
	//////////////////////////////////////////////////////////////////


	// free(param);
	// free(f);

	// double* param = new double[2]{1.0, 0.5};
	// function* f = new function();
	// *f = function(function::magenticDipole,2,2,param);

	// solution<double*>* y = new solution<double*>;
	// y = f->applyRunge_kutta4th(std::make_pair(x,0),0,50,1e-4);
	// solution<double>* four = new solution<double>;
	// four = f->applyFourierTransform(-2,2,0.01);
	
	// // for(auto i : filtered)
	// // {
	// // 	std::cout<<i.first<<" "<<i.second<<"\n";
	// // }
	
	// std::string rk = "Teste.txt";
	// std::string fourierzin = "FourierTest.txt";
	// y->printSolutionDoublePtr(rk);
	// four->printSolutionDouble(fourierzin);
    
	// std::fstream plot; 
	// plot.open("Dat/Grafico.txt",std::fstream::out);
    // for(uint i = 0; i < y->n_iterations; i++)
    // {
    //     plot<<y->data[i].second <<" "<<y->data[i].first[0]<<" "<<y->data[i].first[1]<<" "<<y->data[i].first[2] <<std::endl; 
    // }
    // plot.close();

	// std::cout<<d->size<<"\n";
	//std::vector<double> x = { 1.0,0.01,0.1};
	//std::vector<double> lorenzParams = {10.0,8./3.0,28.0};
	//function f = function(function::lorenz_equation, lorenzParams, 3, 3);
	//std::vector<std::pair<std::vector<double>, double>> y = f.runge_kutta4th(make_pair(x, 0), 100, 0.001);
	//matrix::printMatrixToFile(y, "lorenz.txt");
	//plot3D("lorenz", "lorenz", "Sistema de Lorenz", "2:3:4");
	
	/////////////////////////////////////////////////////////////
	//// Dipolo magn�tico
	//std::vector<double> x = { 1.0,0.0 };
	//std::vector<double> pendulumParams = { 1.0,2.5};
	//
	//function magenticDipole = function(function::magenticDipole, pendulumParams, 2);
	//
	//std::vector<std::pair<std::vector<double>, double>> y = magenticDipole.runge_kutta4th(make_pair(x, 0), 100, 0.001);
	//matrix::printMatrixToFile(y, "./Dat/dipole_001_f2.5.txt");
	//
	//plotting::plot2D("dipole_001_f2.5", "./Dat/dipole_001_f2.5", "Magnetic dipole in an osciling magnectic field with frequency of 2.5", "1:2");
	///////////////////////////////////////////////////////////////


	// double* x = new double[2];
	// x[0] = 1.0;
	// x[1] = 0.0;
	// double* pendulumParams =new double[2];	
	// pendulumParams[0] = 1.0;
	// pendulumParams[1] = 0.75;

	// function dipole = function(function::magenticDipole, std::make_pair(x,0),pendulumParams,2);
	// solution y = *dipole.applyRunge_kutta4th(std::make_pair(x,0),0.0, 100.0*PI,1e-3);
	
	// std::fstream plot; 
	// plot.open("Dat/Grafico.txt",std::fstream::out);
	// for(uint i = 0; i < y.n_iterations; i++)
	// {
	// 	plot<<y.data[i].second;
	// 	for(uint j = 0; j < y.sysDim; j++)
	// 	{
	// 		plot<<" "<<y.data[i].first[j];
	// 	}
	// 	plot<<"\n";
	// }
	// plot.close();
	
	// dipole.printRungeKutta("Dat/Grafico.txt");
	// dipole.fourierTransformRange(1e-3,0.0,2.0);
	// dipole.printFourierTransformRange("Dat/frequenciesTest1.txt");
	// std::vector<std::pair<double,double>>frequencies = dipole.findFrquenciesFourier(0.00001);
	
	// for(uint i = 0; i<frequencies.size(); i ++)
	// {
	// 	std::cout<<i << " "<<frequencies[i].first<<" "<<frequencies[i].second<<"\n";
	// }

	// std::fstream mainFrq;
	// mainFrq.open("Dat/mainfrequencies1.txt", std::fstream::out);
	
	// std::vector<std::pair<double,double>> F(n);
	// F[0].first = std::pow(std::norm(dipole.fourierTransform(0)),2);
	// F[1].second = 0.0;

	// double step = 1e-3;
	// double treshold =0.0001;
	// std::vector<std::pair<double,double>> mfreq; 
	// std::vector<std::pair<double,double>>v; 

	// for(int i = 0 ; i < n; i++)
	// {
	// 	F[i].first = std::pow(std::norm(dipole.fourierTransform(i*step)),2);
	// 	F[i].second = i*step;
	// 	frequencies<<F[i].first << " " <<F[i].second <<std::endl;
	// }
	// frequencies.close();

	// for(int i = 0; i < n; i++)
	// {
	// 	while(F[i].first < treshold && i < n)
	// 	{ i++;}
	// 	while (F[i].first >= treshold )
	// 	{
	// 		v.emplace_back(F[i]);
	// 		// std::cout<<"i: "<< i <<" " <<v.back().first <<" " <<v.back().second<<"\n";
	// 		i++;
	// 	}
	// 	if(v.size() > 1)
	// 	{
	// 		mfreq.emplace_back(function::peakSearch(v,0,v.size()));
	// 		v.clear();
	// 	}
	// }

	// for(uint i = 0; i < mfreq.size(); i++)
	// {
	// 	mainFrq<<mfreq[i].first<<" "<< mfreq[i].second<<"\n";
	// }
	// mainFrq.close();


	// double* v = new double[5];
	// v[0] = 1.0;
	// v[1] = 2.0;
	// v[2] = 1.0;
	// v[3] = 3.0;
	// v[4] = 1.0;
	// std::cout<<"Pico "<<peakSearch(v,0,5);
	// std::fstream output;
	// output.open("Dat/teste1.txt", std::fstream::out);
	// for(uint i = 0; i < dipole.solved.size; i++)
	// {
	// 	output<<rk.data[i].first[0]<<", "<<rk.data[i].first[1]<<", "<<rk.data[i].second<<std::endl;
	// }
	// output.close();


	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	
	std::cout << "\n Time taken by the program: " << duration.count() << " miliseconds" << "\n";

	return 0;
}