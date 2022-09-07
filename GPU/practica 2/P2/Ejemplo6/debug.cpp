#include <CL/sycl.hpp>
using namespace cl::sycl;

#define SIZE 16

void compute(int input[], int output[]) {
	range<1> range{SIZE};
	buffer<int, 1> buffer_in{input, range};
	buffer<int, 1> buffer_out{output, range};

	queue Q{ host_selector{} };
	std::cout << "Selected device: " <<
		Q.get_device().get_info<info::device::name>() << "\n";

	Q.submit([&](handler& h) {
		auto in = buffer_in.get_access<access::mode::read>(h);
		auto out = buffer_out.get_access<access::mode::write>(h);

		h.parallel_for(SIZE, [=](id<1> index) {
			int point = in[index];
			if (index % 2 == 0)
				point = point + 1000; // then-branch
			else
				point = -1; // else-branch
			out[index] = point;
		});
	});
}

int main() {
	int input[SIZE];
	int output[SIZE];

	// Initialize the input
	for (unsigned int i = 0; i < SIZE; i++)
		input[i] = i + 100;

	compute(input, output);
	return 0; // end of main
}
