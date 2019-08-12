#include <iostream>
#include <fstream>
#include <curl/curl.h>

size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userp)
{
	static_cast<std::string*>(userp)->append(static_cast<char*>(contents), size * nmemb);

	return size * nmemb;
}

size_t ReadCallBack(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	FILE *readhere = (FILE *)userdata;
	curl_off_t nread;

	/* copy as much data as possible into the 'ptr' buffer, but no more than
	'size' * 'nmemb' bytes! */
	size_t retcode = fread(ptr, size, nmemb, readhere);

	nread = (curl_off_t)retcode;

	fprintf(stderr, "*** We read %" CURL_FORMAT_CURL_OFF_T" bytes from file\n", nread);
	return retcode;
}

int main(void)
{
	CURL* curl = curl_easy_init();
	CURLcode res;
	std::string readBuffer;

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, ReadCallBack);

		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);

		// std::cout << readBuffer.c_str() << std::endl;
	}

	return 0;
}