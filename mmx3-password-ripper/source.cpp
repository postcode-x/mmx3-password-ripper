#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>

#define RATE 127
#define RANGE 100000

static uint8_t remap_table[] = { 7, 2, 1, 4, 8, 3, 6, 5,
								6, 5, 4, 1, 7, 8, 3, 2,
								7, 5, 6, 1, 4, 3, 2, 8,
								1, 3, 8, 5, 7, 6, 4, 2,
								2, 3, 5, 7, 4, 6, 1, 8,
								8, 2, 4, 7, 1, 3, 6, 5,
								4, 5, 1, 8, 7, 3, 2, 6,
								4, 8, 5, 7, 1, 2, 3, 6,
								3, 7, 5, 2, 1, 8, 6, 4,
								2, 5, 1, 4, 8, 7, 3, 6,
								8, 7, 2, 6, 4, 1, 5, 3,
								4, 7, 1, 3, 8, 2, 6, 5,
								8, 6, 2, 4, 7, 3, 5, 1,
								2, 5, 1, 3, 6, 4, 7, 8,
								4, 3, 8, 6, 2, 7, 5, 1,
								7, 4, 8, 5, 1, 2, 6, 3 };

static uint8_t hash_table[] = { 0, 32, 0, 4, 1, 0, 0, 2, 128, 0, 0, 8, 64, 0, 16, 0,
						  16, 4, 0, 0, 32, 64, 0, 128, 8, 1, 0, 0, 0, 2, 0, 0,
						  2, 0, 64, 32, 0, 0, 16, 0, 0, 1, 8, 128, 4, 0, 0, 0,
						  0, 128, 0, 16, 4, 0, 0, 32, 8, 0, 1, 0, 0, 0, 2, 64,
						  0, 0, 1, 0, 0, 64, 16, 0, 0, 2, 4, 0, 0, 8, 128, 32,
						  16, 0, 8, 0, 0, 2, 64, 0, 0, 0, 0, 4, 1, 32, 0, 128,
						  56, 104, 152, 200, 35, 75, 115, 155, 12, 10, 12, 10, 10, 12, 10, 12,
						  6, 1, 0, 3, 7, 2, 5, 4, 5, 4, 3, 0, 6, 7, 2, 1,
						  6, 4, 5, 0, 3, 2, 1, 7, 0, 2, 7, 4, 6, 5, 3, 1,
						  1, 2, 4, 6, 3, 5, 0, 7, 7, 1, 3, 6, 0, 2, 5, 4,
						  3, 4, 0, 7, 6, 2, 1, 5, 3, 7, 4, 6, 0, 1, 2, 5,
						  2, 6, 4, 1, 0, 7, 5, 3, 1, 4, 0, 3, 7, 6, 2, 5,
						  7, 6, 1, 5, 3, 0, 4, 2, 3, 6, 0, 2, 7, 1, 5, 4,
						  7, 5, 1, 3, 6, 2, 4, 0, 1, 4, 0, 2, 5, 3, 6, 7,
						  3, 2, 7, 5, 1, 6, 4, 0, 6, 3, 7, 4, 0, 1, 5, 2 };


const int array_size = 16 * sizeof(uint8_t) * (int)( RANGE * 1 / RATE ) + 10000;

uint8_t output_array_1[array_size] = { 0 };
uint8_t output_array_2[array_size] = { 0 };
uint8_t output_array_3[array_size] = { 0 };
uint8_t output_array_4[array_size] = { 0 };


int hash_subroutine(uint8_t* _1e8x, int index, int n) {

	int zf = 0;
	int cf = 0;
	int res1 = 0;
	int res2 = 0;
	int _1e94 = _1e8x[index];
	int tmp = _1e8x[3];
	tmp = tmp >> n;
	int _1e95 = tmp & 1;
	int count_x = 0;
	tmp = _1e94;
	cf = tmp & 1;
	tmp = tmp >> 1;
	if (cf == 1) {
		count_x += 1;
	}
	while (tmp != 0) {
		cf = tmp & 1;
		tmp = tmp >> 1;
		if (cf == 1) {
			count_x += 1;
		}
	}
	res1 = count_x ^ _1e95;
	res2 = res1 & 1;
	cf = res1 & 1;
	if (res2 == 0) {
		zf = 1;
	}

	return zf;
}

// Bruteforces randomly generated passwords to check if they are valid

void bruteforce(int lower, int upper, bool print, int thread_number) {

	uint8_t password[16];
	uint8_t password_copy[16];

	uint8_t idx = 0;
	uint8_t x, y, item = 0;

	int _1e96 = 15;
	int _1e94 = 0;
	bool _1e94_flag = false;

	uint8_t and_03 = 0;

	int zf = 0;

	int counter = 0;

	for (int u = lower; u < upper; u++) {

		srand(u);

		for (int i = 0; i < 16; i++) {
			uint8_t number = (rand() % 8) + 1;
			password[i] = number;
			password_copy[i] = number;
		}

		// Remap Password

		for (int i = 0; i < 16; ++i) {
			idx = 7;
			while (password[i] != remap_table[idx + 8 * i]) {
				idx -= 1;
			}
			password[i] = idx;
		}

		// Calculate Hash

		uint8_t _1e8x[6] = { 0 };
		x, y, item = 0;

		_1e96 = 15;
		_1e94 = 0;

		_1e94_flag = false;

		while (_1e96 >= 0) {

			_1e94_flag = false;
			y = 0;
			item = password[_1e96];
			item = item << 5;

			_1e94 = item;
			if (_1e94 > 0) {
				_1e94_flag = true;
			}

			for (int k = 0; k < 3; k++) {
				item = 0;
				while (item == 0) {
					item = y;
					item = item << 4;
					item = item + _1e96;
					x = item;
					item = hash_table[x];
					if (item == 0) {
						y += 1;
					}
				}
				x = y;
				_1e94 = _1e94 << 1;
				if (_1e94 >= 256) {
					_1e8x[x] = _1e8x[x] | item;
					if (!_1e94_flag) {
						_1e94 = 0;
					}
					else {
						_1e94 = _1e94 & 0xFF;
					}
				}
				y += 1;
			}

			_1e96 -= 1;
		}

		/*for (int i = 0; i < 6; i++) {
			std::cout << (int)_1e8x[i] << ' ';
		}*/

		// Hash Normalization

		and_03 = _1e8x[3] & 0x03;
		_1e94 = and_03;

		for (int i = 0; i < 4; i++) {
			and_03 = and_03 << 1;
		}

		_1e94 = and_03 | _1e94;
		_1e8x[0] = _1e8x[0] ^ _1e94;
		_1e8x[1] = _1e8x[1] ^ _1e94;
		_1e8x[2] = _1e8x[2] ^ _1e94;
		_1e8x[5] = _1e8x[5] ^ _1e94;
		_1e8x[4] = _1e8x[4] ^ _1e94;

		/*for (int i = 0; i < 6; i++) {
			std::cout << (int)_1e8x[i] << ' ';
		}

		std::cout << std::endl;*/

		// Hash Testing

		zf = hash_subroutine(_1e8x, 0, 3);
		int res = 0;
		if (zf == 1) {
			zf = hash_subroutine(_1e8x, 1, 4);
			if (zf == 1) {
				zf = hash_subroutine(_1e8x, 2, 5);
				if (zf == 1) {
					zf = hash_subroutine(_1e8x, 5, 6);
					if (zf == 1) {
						zf = hash_subroutine(_1e8x, 4, 7);
						if (zf == 1) {
							if ((_1e8x[5] & 64) == 0) {
								_1e94 = _1e8x[5] & 191;
								res = ((_1e8x[0] | _1e8x[1]) | _1e94) | _1e8x[4];
								if (res == 0) {
									memcpy(  thread_number == 1 ? &output_array_1[counter * 16] :
											(thread_number == 2 ? &output_array_2[counter * 16] :
											(thread_number == 3 ? &output_array_3[counter * 16] :
											&output_array_4[counter * 16])), password_copy, 16 * sizeof(uint8_t));
									counter += 1;
								}
							}
							else {
								int last_test = _1e8x[3] & 4;
								if (last_test == 0) {
									memcpy(  thread_number == 1 ? &output_array_1[counter * 16] :
											(thread_number == 2 ? &output_array_2[counter * 16] :
											(thread_number == 3 ? &output_array_3[counter * 16] :
											&output_array_4[counter * 16])), password_copy, 16 * sizeof(uint8_t));
									counter += 1;
								}
							}
						}
					}
				}
			}
		}
	}

	//std::cout << counter << std::endl;
	/*for (int i = 0; i < 16 * counter; i++) {
		if ((i + 1) % 16 == 0)
			std::cout << (int)output_array_1[i] << std::endl;
		else {
			std::cout << (int)output_array_1[i] << " ";
		}
	}*/

	std::string filename = "Thread ";
	filename += std::to_string(thread_number);
	filename += " - Lower ";
	filename += std::to_string(lower);
	filename += " - Upper ";
	filename += std::to_string(upper);
	filename += " - Results ";
	filename += std::to_string(counter);
	filename += ".html";

	std::ofstream myfile(filename.c_str() /*, ios::out | ios::binary*/);
	if (myfile.is_open())
	{
		myfile << "<html>";
		for (int i = 0; i < 16 * counter; i++) {
			myfile << (int) (thread_number == 1 ? output_array_1[i] :
							(thread_number == 2 ? output_array_2[i] :
							(thread_number == 3 ? output_array_3[i] :
							output_array_4[i]))) << " ";
			if ((i + 1) % 16 == 0) {
				myfile << "<br>";
			}
		}
		myfile << "</html>";
		myfile.close();
	}
	else { std::cout << "Unable to open file"; 
	myfile.close();
	}

	std::cout << counter << std::endl;

}

// Performs a fast test to check if a given password is valid. If all tests are ok then the same password is printed

void fast_test(uint8_t* password, bool print) {

	uint8_t password_copy[16];
	memcpy(password_copy, password, 16 * sizeof(uint8_t));

	uint8_t idx = 0;
	uint8_t x, y, item = 0;

	int _1e96 = 15;
	int _1e94 = 0;
	bool _1e94_flag = false;

	uint8_t and_03 = 0;

	int zf = 0;

	// Remap Password

	for (int i = 0; i < 16; ++i) {
		idx = 7;
		while (password[i] != remap_table[idx + 8 * i]) {
			idx -= 1;
		}
		password[i] = idx;
	}

	// Calculate Hash

	uint8_t _1e8x[6] = { 0 };
	x, y, item = 0;

	_1e96 = 15;
	_1e94 = 0;

	_1e94_flag = false;

	while (_1e96 >= 0) {

		_1e94_flag = false;
		y = 0;
		item = password[_1e96];
		item = item << 5;

		_1e94 = item;
		if (_1e94 > 0) {
			_1e94_flag = true;
		}

		for (int k = 0; k < 3; k++) {
			item = 0;
			while (item == 0) {
				item = y;
				item = item << 4;
				item = item + _1e96;
				x = item;
				item = hash_table[x];
				if (item == 0) {
					y += 1;
				}
			}
			x = y;
			_1e94 = _1e94 << 1;
			if (_1e94 >= 256) {
				_1e8x[x] = _1e8x[x] | item;
				if (!_1e94_flag) {
					_1e94 = 0;
				}
				else {
					_1e94 = _1e94 & 0xFF;
				}
			}
			y += 1;
		}

		_1e96 -= 1;
	}

	/*for (int i = 0; i < 6; i++) {
		std::cout << (int)_1e8x[i] << ' ';
	}*/

	// Hash Normalization

	and_03 = _1e8x[3] & 0x03;
	_1e94 = and_03;

	for (int i = 0; i < 4; i++) {
		and_03 = and_03 << 1;
	}

	_1e94 = and_03 | _1e94;
	_1e8x[0] = _1e8x[0] ^ _1e94;
	_1e8x[1] = _1e8x[1] ^ _1e94;
	_1e8x[2] = _1e8x[2] ^ _1e94;
	_1e8x[5] = _1e8x[5] ^ _1e94;
	_1e8x[4] = _1e8x[4] ^ _1e94;

	/*for (int i = 0; i < 6; i++) {
		std::cout << (int)_1e8x[i] << ' ';
	}

	std::cout << std::endl;*/

	// Hash Testing

	zf = hash_subroutine(_1e8x, 0, 3);
	int res = 0;
	if (zf == 1) {
		zf = hash_subroutine(_1e8x, 1, 4);
		if (zf == 1) {
			zf = hash_subroutine(_1e8x, 2, 5);
			if (zf == 1) {
				zf = hash_subroutine(_1e8x, 5, 6);
				if (zf == 1) {
					zf = hash_subroutine(_1e8x, 4, 7);
					if (zf == 1) {
						if ((_1e8x[5] & 64) == 0) {
							_1e94 = _1e8x[5] & 191;
							res = ((_1e8x[0] | _1e8x[1]) | _1e94) | _1e8x[4];
							if (res == 0) {
								if (print) {
									for (int i = 0; i < 16; i++) {
										std::cout << (int)password_copy[i] << ' ';
									}
									std::cout << std::endl;
								}
							}
						}
						else {
							int last_test = _1e8x[3] & 4;
							if (last_test == 0) {
								if (print) {
									for (int i = 0; i < 16; i++) {
										std::cout << (int)password_copy[i] << ' ';
									}
									std::cout << std::endl;
								}
							}
						}
					}
				}
			}
		}
	}
}

int main() {

	auto start = std::chrono::high_resolution_clock::now();

	//uint8_t password[16] = { 7, 3, 5, 7, 5, 3, 6, 3, 6, 4, 6, 2, 7, 8, 4, 1 };
	//fast_test(password, true);

	std::thread th1(bruteforce, 0, RANGE, false, 1);
	std::thread th2(bruteforce, RANGE, 2 * RANGE, false, 2);
	std::thread th3(bruteforce, 2 * RANGE, 3 * RANGE, false, 3);
	std::thread th4(bruteforce, 3 * RANGE, 4 * RANGE, false, 4);

	th1.join();
	th2.join();
	th3.join();
	th4.join();

	auto end = std::chrono::high_resolution_clock::now();
	auto int_s = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cout << "Elapsed time is " << int_s.count() << " seconds" << std::endl;

	return 0;

}

