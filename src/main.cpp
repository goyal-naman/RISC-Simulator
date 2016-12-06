/*Copyright (C) 2016, IIT Ropar
 * This file is part of SimpleRISC simulator.
 *
 * SimpleRISC simulator is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SimpleRISC simulator is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Naman Goyal (email: 2015csb1021@iitrpr.ac.in)
 */

#include <iostream>
#include <ctime>

#include "Core.h"
#include "Memory.h"
#include "Register.h"
#include "PipelineRegister.h"

using namespace std;

int MEM_CAPACITY = 100000;
int debugLevel = 0;

int main(int argc, char *argv[])
{
	clock_t begin = clock();

	if (argc<2){
		cout<<"Please provide Instruction MEM file as an argument"<<endl;
		return 1;
	}

	bool to_pipeline = false;	

	if (argc > 2){
		if (argv[2][0] == '1'){
			to_pipeline = true;
		}

	}

	if (argc > 3){
		if (argv[3][0] == '1'){
			debugLevel = 1;
		}
		else if (argv[3][0] > '1'){
			debugLevel = 2;
		}

	}

	Core simulator(to_pipeline);

	simulator.load_program_memory(argv[1]);

	simulator.reset_proc();

	simulator.run_simplesim();

	simulator.write_data_memory();

	simulator.write_state();

	clock_t end = clock();
	double time = double(end - begin) / CLOCKS_PER_SEC;

	dprint(2)<<endl<<"Running time: "<<dec<<time<<endl;

    return 0;
}
