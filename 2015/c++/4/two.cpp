#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include<openssl/evp.h>

void GetMd5(unsigned char *data, size_t dataLen, unsigned char* hash) {
	unsigned char *md = NULL;
	EVP_MD_CTX *ctx = NULL;
	const EVP_MD *mdType = EVP_md5();

	ctx = EVP_MD_CTX_create();

	EVP_MD_CTX_init(ctx);
	EVP_DigestInit_ex(ctx, mdType, NULL);
	EVP_DigestUpdate(ctx, data, dataLen);
	EVP_DigestFinal_ex(ctx, hash, NULL);
	EVP_MD_CTX_cleanup(ctx);
	EVP_MD_CTX_destroy(ctx);
}

size_t FindHash(const std::string& prefix) {
	std::stringstream ss;
	std::vector<unsigned char> hash(1024, 0);
	for (size_t i = 0; ; ++i) {
		std::string data = prefix + std::to_string(i);

		GetMd5(reinterpret_cast<unsigned char*>(&data[0]), data.length(), &hash[0]);
		if (hash[0] == 0 && hash[1] == 0 && hash[2] == 0) {
			return i;
		}

		if (i % 10000 == 0) {
			std::cout << i << std::endl;
		}
	}
	return 0;
}

int main() {
	std::ifstream input{"input.txt"};
	std::string line;

	while (input >> line) {
		std::cout << FindHash(line) << std::endl;
	}
}
